#ifndef __NAND_H__
#define __NAND_H__

#ifdef __cplusplus
extern "C"{
#endif

int nand_erase(const char *mtd_device, int start_block, int block_count);
int nand_erase_no_skip_badblock(const char *mtd_device, int start_block, int block_count);
int nand_write(const char *mtd_device, int ifd, int isize);
int nand_read(const char *mtddev, long long start, int length, char *rbuf);

#ifdef __cplusplus
}
#endif

#endif
