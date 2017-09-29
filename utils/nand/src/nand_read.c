#define PROGRAM_NAME "nand_read"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <asm/types.h>
#include <mtd/mtd-user.h>
#include "common.h"
#include <libmtd.h>

int nand_read(const char *mtddev, char *rbuf, long long start, int length)
{
    long long ofs, end_addr = 0;
    int fd, bs, badblock = 0;
    struct mtd_dev_info mtd;
    unsigned char *readbuf = NULL;
    libmtd_t mtd_desc;
    long long start_addr = start;
    int bytes;

    /* Initialize libmtd */
    mtd_desc = libmtd_open();
    if (!mtd_desc) {
        fprintf(stderr, "can't initialize libmtd\n");
        return -1;
    }

    /* Open MTD device */
    if ((fd = open(mtddev, O_RDONLY)) == -1) {
        perror(mtddev);
        return -1;
    }

    /* Fill in MTD device capability structure */
    if (mtd_get_dev_info(mtd_desc, mtddev, &mtd) < 0) {
        fprintf(stderr, "mtd_get_dev_info failed\n");
        return -1;
    }

    /* Allocate buffers */
    readbuf = xmalloc(sizeof(readbuf) * mtd.min_io_size);


    /* Initialize start/end addresses and block size */
    if (start_addr & (mtd.min_io_size - 1)) {
        fprintf(stderr, "ERROR: The start address is not page-aligned !\n"
                "The pagesize of this NAND Flash is 0x%x.\n"
                "nandwrite doesn't allow writes starting at this location.\n",
                mtd.min_io_size);
        goto closeall;
    }

    if (length == 0) {
        fprintf(stderr, "ERROR: length is zero.\n");
        goto closeall;
    }

    end_addr = start_addr + length;
    bs = mtd.min_io_size;

    // mtd.min_io_size = 2048

    /* Dump the flash contents */
    bytes = 0;
    for (ofs = start_addr; ofs < end_addr; ofs += bs) {

        /* Check for bad block */
        if ((badblock = mtd_is_bad(&mtd, fd, ofs / mtd.eb_size)) < 0) {
            fprintf(stderr, "libmtd: mtd_is_bad\n");
            goto closeall;
        }

        if (badblock) {
            fprintf(stderr, "skip bad block (0x%08llx)\n", ofs);
            close(fd);
            free(readbuf);
            return 1;
        }

        /* Read page data and exit on failure */
        memset(readbuf, 0xff, bs);
        if (mtd_read(&mtd, fd, ofs / mtd.eb_size, ofs % mtd.eb_size, readbuf, bs)) {
            fprintf(stderr, "mtd_read\n");
            goto closeall;
        }

        /* Write out page data */
        memcpy(rbuf+bytes, readbuf, bs);
        bytes += bs;
    }

    /* Close the output file and MTD device, free memory */
    close(fd);
    free(readbuf);

    /* Exit happy */
    return 0;

closeall:
    close(fd);
    free(readbuf);
    return -1;
}
