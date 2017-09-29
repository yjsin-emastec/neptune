#define PROGRAM_NAME "nand_write"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <getopt.h>
#include <glib.h>

#include <asm/types.h>
#include "mtd/mtd-user.h"
#include "common.h"
#include <libmtd.h>
#include <event/Event.h>
#include <event/EasternEvent.h>


static bool         quiet          = false;
static bool         writeoob       = false;
static bool         rawoob         = false;
static bool         markbad        = true;
static bool         noecc          = false;
static bool         noskipbad      = false;
static bool         pad            = true;
static int          blockalign     = 1;    /* default to using actual block size */

static void erase_buffer(void *buffer, size_t size)
{
    const uint8_t kEraseByte = 0xff;

    if (buffer != NULL && size > 0) {
        memset(buffer, kEraseByte, size);
    }
}

int nand_write(const char *mtd_device, int ifd, int isize, int *ratio, int *percent)
{
    int cnt = 0;
    int fd = -1;
    int imglen = isize;
    int pagelen;
    bool baderaseblock = false;
    long long blockstart = -1;
    struct mtd_dev_info mtd;
    long long offs;
    int ret;
    int oobinfochanged = 0;
    struct nand_oobinfo old_oobinfo;
    bool failed = true;
    // contains all the data read from the file so far for the current eraseblock
    unsigned char *filebuf = NULL;
    size_t filebuf_max = 0;
    size_t filebuf_len = 0;
    // points to the current page inside filebuf
    unsigned char *writebuf = NULL;
    // points to the OOB for the current page in filebuf
    unsigned char *oobreadbuf = NULL;
    unsigned char *oobbuf = NULL;
    libmtd_t mtd_desc;
    int ebsize_aligned;
    long long mtdoffset = 0;
    int count = 0;


    if (pad && writeoob) {
        fprintf(stderr, "Can't pad when oob data is present.\n");
        return -1;
    }

    /* Open the device */
    if ((fd = open(mtd_device, O_RDWR)) == -1) {
        perror(mtd_device);
        return -1;
    }

    mtd_desc = libmtd_open();
    if (!mtd_desc) {
        fprintf(stderr, "can't initialize libmtd\n");
        close(fd);
        return -1;
    }
    /* Fill in MTD device capability structure */
    if (mtd_get_dev_info(mtd_desc, mtd_device, &mtd) < 0) {
        fprintf(stderr, "mtd_get_dev_info failed\n");
        libmtd_close(mtd_desc);
        close(fd);
        return -1;
    }

    /*
     * Pretend erasesize is specified number of blocks - to match jffs2
     *   (virtual) block size
     * Use this value throughout unless otherwise necessary
     */
    ebsize_aligned = mtd.eb_size * blockalign;

    if (mtdoffset & (mtd.min_io_size - 1)) {
        fprintf(stderr, "The start address is not page-aligned !\n"
                "The pagesize of this NAND Flash is 0x%x.\n",
                mtd.min_io_size);
        goto closeall;
    }

    pagelen = mtd.min_io_size + ((writeoob) ? mtd.oob_size : 0);

    // Check, if file is page-aligned
    if ((!pad) && ((imglen % pagelen) != 0)) {
        fprintf(stderr, "Input file is not page-aligned. Use the padding "
                "option.\n");
        goto closeall;
    }

    // Check, if length fits into device
    if (((imglen / pagelen) * mtd.min_io_size) > (mtd.size - mtdoffset)) {
        fprintf(stderr, "Image %d bytes, NAND page %d bytes, OOB area %d"
                " bytes, device size %lld bytes\n",
                imglen, pagelen, mtd.oob_size, mtd.size);
        perror("Input file does not fit into device");
        goto closeall;
    }

    /*
     * Allocate a buffer big enough to contain all the data (OOB included)
     * for one eraseblock. The order of operations here matters; if ebsize
     * and pagelen are large enough, then "ebsize_aligned * pagelen" could
     * overflow a 32-bit data type.
     */
    filebuf_max = ebsize_aligned / mtd.min_io_size * pagelen;
    filebuf = xmalloc(filebuf_max);
    erase_buffer(filebuf, filebuf_max);

    oobbuf = xmalloc(mtd.oob_size);
    erase_buffer(oobbuf, mtd.oob_size);

    /*
     * Get data from input and write to the device while there is
     * still input to read and we are still within the device
     * bounds. Note that in the case of standard input, the input
     * length is simply a quasi-boolean flag whose values are page
     * length or zero.
     */
    while (((imglen > 0) || (writebuf < (filebuf + filebuf_len)))
            && (mtdoffset < mtd.size)) {
        /*
         * New eraseblock, check for bad block(s)
         * Stay in the loop to be sure that, if mtdoffset changes because
         * of a bad block, the next block that will be written to
         * is also checked. Thus, we avoid errors if the block(s) after the
         * skipped block(s) is also bad (number of blocks depending on
         * the blockalign).
         */
        while (blockstart != (mtdoffset & (~ebsize_aligned + 1))) {
            blockstart = mtdoffset & (~ebsize_aligned + 1);
            offs = blockstart;

            // if writebuf == filebuf, we are rewinding so we must not
            // reset the buffer but just replay it
            if (writebuf != filebuf) {
                erase_buffer(filebuf, filebuf_len);
                filebuf_len = 0;
                writebuf = filebuf;
            }

            baderaseblock = false;
#if 0
            if (!quiet)
                fprintf(stdout, "Writing data to block %lld at offset 0x%llx\n",
                        blockstart / ebsize_aligned, blockstart);
#endif

            /* Check all the blocks in an erase block for bad blocks */
            if (noskipbad)
                continue;
            do {
                if ((ret = mtd_is_bad(&mtd, fd, offs / ebsize_aligned)) < 0) {
                    fprintf(stderr, "%s: MTD get bad block failed\n", mtd_device);
                    goto closeall;
                } else if (ret == 1) {
                    baderaseblock = true;
                    if (!quiet)
                        fprintf(stderr, "Bad block at %llx, %u block(s) "
                                "from %llx will be skipped\n",
                                offs, blockalign, blockstart);
                }

                if (baderaseblock) {
                    mtdoffset = blockstart + ebsize_aligned;
                }
                offs +=  ebsize_aligned / blockalign;
            } while (offs < blockstart + ebsize_aligned);

        }

        // Read more data from the input if there isn't enough in the buffer
        if ((writebuf + mtd.min_io_size) > (filebuf + filebuf_len)) {
            int readlen = mtd.min_io_size;

            int alreadyread = (filebuf + filebuf_len) - writebuf;
            int tinycnt = alreadyread;

            while (tinycnt < readlen) {
                cnt = read(ifd, writebuf + tinycnt, readlen - tinycnt);
                if (cnt == 0) { // EOF
                    break;
                } else if (cnt < 0) {
                    perror("File I/O error on input");
                    goto closeall;
                }
                tinycnt += cnt;
            }

            /* No padding needed - we are done */
            if (tinycnt == 0) {
                /*
                 * For standard input, set imglen to 0 to signal
                 * the end of the "file". For nonstandard input,
                 * leave it as-is to detect an early EOF.
                 */
                if (ifd == STDIN_FILENO) {
                    imglen = 0;
                }
                break;
            }

            /* Padding */
            if (tinycnt < readlen) {
                if (!pad) {
                    fprintf(stderr, "Unexpected EOF. Expecting at least "
                            "%d more bytes. Use the padding option.\n",
                            readlen - tinycnt);
                    goto closeall;
                }
                erase_buffer(writebuf + tinycnt, readlen - tinycnt);
            }

            filebuf_len += readlen - alreadyread;
            if (ifd != STDIN_FILENO) {
                imglen -= tinycnt - alreadyread;
            }
            else if (cnt == 0) {
                /* No more bytes - we are done after writing the remaining bytes */
                imglen = 0;
            }
        }

        if (writeoob) {
            oobreadbuf = writebuf + mtd.min_io_size;

            // Read more data for the OOB from the input if there isn't enough in the buffer
            if ((oobreadbuf + mtd.oob_size) > (filebuf + filebuf_len)) {
                int readlen = mtd.oob_size;
                int alreadyread = (filebuf + filebuf_len) - oobreadbuf;
                int tinycnt = alreadyread;

                while (tinycnt < readlen) {
                    cnt = read(ifd, oobreadbuf + tinycnt, readlen - tinycnt);
                    if (cnt == 0) { // EOF
                        break;
                    } else if (cnt < 0) {
                        perror("File I/O error on input");
                        goto closeall;
                    }
                    tinycnt += cnt;
                }

                if (tinycnt < readlen) {
                    fprintf(stderr, "Unexpected EOF. Expecting at least "
                            "%d more bytes for OOB\n", readlen - tinycnt);
                    goto closeall;
                }

                filebuf_len += readlen - alreadyread;
                if (ifd != STDIN_FILENO) {
                    imglen -= tinycnt - alreadyread;
                }
                else if (cnt == 0) {
                    /* No more bytes - we are done after writing the remaining bytes */
                    imglen = 0;
                }
            }

            if (!noecc) {
                int i, start, len;
                int tags_pos = 0;
                /*
                 * We use autoplacement and have the oobinfo with the autoplacement
                 * information from the kernel available
                 *
                 * Modified to support out of order oobfree segments,
                 * such as the layout used by diskonchip.c
                 */
                if (!oobinfochanged && (old_oobinfo.useecc == MTD_NANDECC_AUTOPLACE)) {
                    for (i = 0; old_oobinfo.oobfree[i][1]; i++) {
                        /* Set the reserved bytes to 0xff */
                        start = old_oobinfo.oobfree[i][0];
                        len = old_oobinfo.oobfree[i][1];
                        if (rawoob)
                            memcpy(oobbuf + start,
                                    oobreadbuf + start, len);
                        else
                            memcpy(oobbuf + start,
                                    oobreadbuf + tags_pos, len);
                        tags_pos += len;
                    }
                } else {
                    /* Set at least the ecc byte positions to 0xff */
                    start = old_oobinfo.eccbytes;
                    len = mtd.oob_size - start;
                    memcpy(oobbuf + start, oobreadbuf + start, len);
                }
            }
            /* Write OOB data first, as ecc will be placed in there */
            if (mtd_write_oob(mtd_desc, &mtd, fd, mtdoffset, mtd.oob_size, noecc ? oobreadbuf : oobbuf)) {
                fprintf(stderr, "%s: MTD writeoob failure\n", mtd_device);
                goto closeall;
            }
        }

        /* Write out the Page data */
        if (mtd_write(&mtd, fd, mtdoffset / mtd.eb_size, mtdoffset % mtd.eb_size, writebuf, mtd.min_io_size)) {
            int i;
            if (errno != EIO) {
                fprintf(stderr, "%s: MTD write failure\n", mtd_device);
                goto closeall;
            }

            /* Must rewind to blockstart if we can */
            writebuf = filebuf;

            fprintf(stderr, "Erasing failed write from %#08llx to %#08llx\n",
                    blockstart, blockstart + ebsize_aligned - 1);
            for (i = blockstart; i < blockstart + ebsize_aligned; i += mtd.eb_size) {
                if (mtd_erase(mtd_desc, &mtd, fd, mtd.eb_size)) {
                    int errno_tmp = errno;
                    fprintf(stderr, "%s: MTD Erase failure\n", mtd_device);
                    if (errno_tmp != EIO) {
                        goto closeall;
                    }
                }
            }

            if (markbad) {
                fprintf(stderr, "Marking block at %08llx bad\n", mtdoffset & (~mtd.eb_size + 1));
                if (mtd_mark_bad(&mtd, fd, mtdoffset / mtd.eb_size)) {
                    fprintf(stderr, "%s: MTD Mark bad block failure\n", mtd_device);
                    goto closeall;
                }
            }
            mtdoffset = blockstart + ebsize_aligned;

            continue;
        }

        if(count++ >= *ratio)
        {
            if(*percent < 85)
            {
                int *pPercent = g_new0(int, 1);
                *pPercent = (*percent)++;
                event_send(QUEUE_APPMGR, QUEUE_QT_CORE, Send_QT_UPGRADE_PROGRESS, pPercent, g_free, NULL);
            }
            count = 0;
        }

        mtdoffset += mtd.min_io_size;
        writebuf += pagelen;
    }

    failed = false;

closeall:
#if 0
    // The calling function will close it.
    close(ifd);
#endif

    libmtd_close(mtd_desc);
    free(filebuf);
    free(oobbuf);

    close(fd);

    if (failed
            || ((ifd != STDIN_FILENO) && (imglen > 0))
            || (writebuf < (filebuf + filebuf_len))) {
        perror("Data was only partially written due to error\n");
        return -1;
    }

    /* Return happy */
    return 0;
}
