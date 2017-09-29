#define PROGRAM_NAME "nand_erase"
#define VERSION "2"

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <glib.h>

#include <common.h>
#include <crc32.h>
#include <libmtd.h>

#include <mtd/mtd-user.h>
#include <mtd/jffs2-user.h>
#include <event/Event.h>
#include <event/EasternEvent.h>

static int quiet;    /* true -- don't output progress */

static void show_progress(struct mtd_dev_info *mtd, uint64_t start, int eb, int eb_start, int eb_cnt)
{
    bareverbose(!quiet, "\rErasing %d Kibyte @ %"PRIx64" -- %2i %% complete ",
            mtd->eb_size / 1024, start, ((eb - eb_start) * 100) / eb_cnt);
    fflush(stdout);
}
int nand_erase(const char *mtd_device, int start_block, int block_count, int *ratio, int *percent)
{
    libmtd_t mtd_desc;
    struct mtd_dev_info mtd;
    int fd;
    unsigned int eb, eb_start, eb_cnt;
    int isNAND;
    uint64_t offset = 0;
    int badblock;
    int count = 0;


    eb_start = start_block;
    eb_cnt   = block_count;

    /*
     * Locate MTD and prepare for erasure
     */
    mtd_desc = libmtd_open();
    if (mtd_desc == NULL) {
        fprintf(stderr, "can't initialize libmtd\n");
        return -1;
    }

    if ((fd = open(mtd_device, O_RDWR)) < 0) {
        fprintf(stderr, "can't open %s\n", mtd_device);
        return -1;
    }

    if (mtd_get_dev_info(mtd_desc, mtd_device, &mtd) < 0) {
        fprintf(stderr, "mtd_get_dev_info failed\n");
        return -1;
    }

    isNAND = mtd.type == MTD_NANDFLASH ? 1 : 0;

    /*
     * Now do the actual erasing of the MTD device
     */
    for (eb = eb_start; eb < eb_start + eb_cnt; eb++) {
        offset = (uint64_t)eb * mtd.eb_size;

        if ((badblock = mtd_is_bad(&mtd, fd, eb)) < 0) {
            fprintf(stderr, "%s: Bad block check fail.\n", mtd_device);
            close(fd);
            return -1;
        }

        if (badblock) {
            fprintf(stderr, "Skipping bad block at 0x%08llx\n", (long long)offset);
            eb_cnt++;
            continue;
        }

        show_progress(&mtd, offset, eb, eb_start, eb_cnt);

        if (mtd_erase(mtd_desc, &mtd, fd, eb) != 0) {
            fprintf(stderr, "%s: MTD Erase failure", mtd_device);
            close(fd);
            return -1;
        }

        if(count++ >= *ratio)
        {
            if(*percent < 20)
            {
                int *pPercent = g_new0(int, 1);
                *pPercent = (*percent)++;
                event_send(QUEUE_APPMGR, QUEUE_QT_CORE, Send_QT_UPGRADE_PROGRESS, pPercent, g_free, NULL);
            }
            count = 0;
        }
    }

    show_progress(&mtd, offset, eb, eb_start, eb_cnt);
    bareverbose(!quiet, "\n");

    return 0;
}
int nand_erase_no_skip_badblock(const char *mtd_device, int start_block, int block_count)
{
    libmtd_t mtd_desc;
    struct mtd_dev_info mtd;
    int fd;
    unsigned int eb, eb_start, eb_cnt = 0x0;
    int isNAND;
    uint64_t offset = 0;
    int badblock;


    eb_start = start_block;
    // eb_cnt   = block_count;

    /*
     * Locate MTD and prepare for erasure
     */
    mtd_desc = libmtd_open();
    if (mtd_desc == NULL) {
        fprintf(stderr, "can't initialize libmtd\n");
        return -1;
    }

    if ((fd = open(mtd_device, O_RDWR)) < 0) {
        fprintf(stderr, "can't open %s\n", mtd_device);
        return -1;
    }

    if (mtd_get_dev_info(mtd_desc, mtd_device, &mtd) < 0) {
        fprintf(stderr, "mtd_get_dev_info failed\n");
        return -1;
    }

    isNAND = mtd.type == MTD_NANDFLASH ? 1 : 0;

    /*
     * Now do the actual erasing of the MTD device
     */
    for (eb = eb_start; eb < eb_start + block_count; eb++) {
        if (eb > block_count - 2) {
            show_progress(&mtd, offset, eb, eb_start, block_count-1);
            break;
        }

        offset = (uint64_t)eb * mtd.eb_size;

        if ((badblock = mtd_is_bad(&mtd, fd, eb)) < 0) {
            fprintf(stderr, "%s: Bad block check fail.\n", mtd_device);
            close(fd);
            return -1;
        }

        if (badblock) {
            fprintf(stderr, "fount bad block at 0x%08llx\n", (long long)offset);
            eb_cnt++;
            continue;
        }

        show_progress(&mtd, offset, eb, eb_start, block_count-1);

        if (mtd_erase(mtd_desc, &mtd, fd, eb) != 0) {
            fprintf(stderr, "%s: MTD Erase failure", mtd_device);
            close(fd);
            return -1;
        }
    }

    show_progress(&mtd, offset, eb, eb_start, block_count-1);
    bareverbose(!quiet, "\n");
    fprintf(stderr, "fount bad block Count %d\n", eb_cnt);

    return 0;
}
