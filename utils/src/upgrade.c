//----------------------------------------------------------------------------
// Standard include files:
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <termio.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <glib.h>

//----------------------------------------------------------------------------
// Project include files:
//----------------------------------------------------------------------------
#include <eaimage.h>
#include <linux/ioctl.h>
#include "utils.h"
#include <event/Event.h>
#include <event/EasternEvent.h>

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------
#define EA_IMAGE_MAX        8
#define EA_BUFF_SIZE        (64*1024)
#define NAND_ROOTFS_SIZE    0x7800000
#define NAND_BLOCK_SIZE     0x20000

ea_image_info_t eaImageInfo[EA_IMAGE_MAX] =
{
    { "bootld.img",  "/dev/mtd0" ,  0 },
    { "envval.img",  "/dev/mtd1" ,  1 },
    { "config.img",  "/dev/mtd2" ,  2 },
    { "kernel.img",  "/dev/mtd3" ,  3 },
    { "btlogo.img",  "/dev/mtd4" ,  4 },
    { "rootfs.img",  "/dev/mtd5" ,  5 },
    { "rootfs.img",  "/dev/mtd6" ,  6 },
    { "miscfs.img",  "/dev/mtd7" ,  7 },
};
static const char *file_prefix[] =
{
    "mdvr", "cardvr", "bootld", "kernel", "btlogo", "rootfs", NULL
};

//----------------------------------------------------------------------------
// Global Variables:
//----------------------------------------------------------------------------
static int    g_model_type;
static int    g_file_size;

//----------------------------------------------------------------------------
// Internal function body:
//----------------------------------------------------------------------------
static int upgrade_file_check(const char *file_name)
{
    int    ii;

    for(ii = 0; file_prefix[ii]; ii++)
    {
        if(ii == 0)
        {
            if(strncmp(file_name, file_prefix[ii], 4) == 0)
            {
                return 0;
            }
        }
        else
        {
            if(strncmp(file_name, file_prefix[ii], 6) == 0)
            {
                return 0;
            }
        }
    }

    return -1;
}
extern unsigned long ea_crc32 (unsigned long crc, const unsigned char *buf, unsigned int len);
static int upgrade_file_verify(const char *file_name)
{
    ea_image_header_t    ihdr;
    unsigned long        cksum;
    FILE                *fp;
    int                  bytes, total, mock, rest, ii;
    char                 buf [4096];
    int                  count      = 0;
    int                  percent    = 0;
    int                  ratio      = 0;

    if(!(fp = fopen(file_name, "rb")))
    {
        return FU_FILE_NOT_OPEN;
    }

    fseek(fp, 0, SEEK_END);
    g_file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    printf("upgrade file - name(%s) size(%d)\n", file_name, g_file_size);

    ratio = (g_file_size/4906)/15;

    total = 0;

    for(;;)
    {
        if(total >= g_file_size)
        {
            break;
        }

        bytes = fread(&ihdr, 1, sizeof(ihdr), fp);
        total += bytes;

        if((ihdr.version != EA_IMAGE_VERSION) || (ihdr.magic != EA_IMAGE_MAGIC))
        {
            fclose(fp);
            return FU_IMAGE_INVALID;
        }

#if 0 // jungyver [16/12/22]
        if(strncmp(file_name, "btlogo", 6))
        {
            if(ihdr.model != g_model_type)
            {
                fclose(fp);
                return FU_IMAGE_INVALID;
            }
        }
#endif

        printf("%s found.\n", eaImageInfo[ihdr.itype].name);

        mock = ihdr.fsize / sizeof(buf);
        rest = ihdr.fsize % sizeof(buf);

        cksum = 0;

        for(ii = 0; ii < mock; ii++)
        {
            bytes  = fread(buf, 1, sizeof(buf), fp);
            total += bytes;
            cksum  = ea_crc32(cksum, (unsigned char *)buf, (unsigned int)bytes);

            if(count++ >= ratio)
            {
                if(percent < 15)
                {
                    int    *pPercent    = g_new0(int, 1);

                    *pPercent           = percent++;

                    event_send(QUEUE_APPMGR, QUEUE_QT_CORE, Send_QT_UPGRADE_PROGRESS, pPercent, g_free, NULL);
                }

                count = 0;
            }
        }

        if(rest)
        {
            bytes  = fread(buf, 1, rest, fp);
            total += bytes;
            cksum  = ea_crc32(cksum, (unsigned char *)buf, (unsigned int)bytes);

            if(count++ >= ratio)
            {
                if(percent < 15)
                {
                    int    *pPercent    = g_new0(int, 1);

                    *pPercent           = percent++;

                    event_send(QUEUE_APPMGR, QUEUE_QT_CORE, Send_QT_UPGRADE_PROGRESS, pPercent, g_free, NULL);
                }

                count = 0;
            }
        }

        if(cksum != ihdr.cksum)
        {
            printf("checksum mismatch : img(0x%08lx) cal(0x%08lx)\n", ihdr.cksum, cksum);

            fclose(fp);

            return FU_IMAGE_CKSUM_MISMATCH;
        }
    }

    fclose(fp);

    return FU_SUCCESS;
}
static int upgrade_test_file_verify(const char *file_name)
{
    ea_image_header_t    ihdr;
    unsigned long        cksum;
    FILE                *fp;
    int                  bytes, total, mock, rest, ii;
    char                 buf [4096];

    if(!(fp = fopen(file_name, "r")))
    {
        return FU_FILE_NOT_OPEN;
    }

    fseek(fp, 0, SEEK_END);

    g_file_size = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    printf("upgrade file - name(%s) size(%d)\n", file_name, g_file_size);

    total = 0;

    for(;;)
    {
        if(total >= g_file_size)
        {
            break;
        }

        bytes = fread(&ihdr, 1, sizeof(ihdr), fp);
        total += bytes;

        if((ihdr.version != EA_IMAGE_VERSION) || (ihdr.magic != EA_IMAGE_MAGIC))
        {
            fclose(fp);
            return FU_IMAGE_INVALID;
        }

        if(strncmp(file_name, "btlogo", 6))
        {
            fclose(fp);
            return FU_IMAGE_INVALID;
        }

        printf("%s found.\n", eaImageInfo[ihdr.itype].name);

        mock = ihdr.fsize / sizeof(buf);
        rest = ihdr.fsize % sizeof(buf);

        cksum = 0;

        for(ii = 0; ii < mock; ii++)
        {
            bytes  = fread(buf, 1, sizeof(buf), fp);
            total += bytes;
            cksum  = ea_crc32(cksum, (unsigned char *)buf, (unsigned int)bytes);
        }

        if(rest)
        {
            bytes  = fread(buf, 1, rest, fp);
            total += bytes;
            cksum  = ea_crc32(cksum, (unsigned char *)buf, (unsigned int)bytes);
        }

        if(cksum != ihdr.cksum)
        {
            printf("checksum mismatch : img(0x%08lx) cal(0x%08lx)\n", ihdr.cksum, cksum);

            fclose(fp);

            return FU_IMAGE_CKSUM_MISMATCH;
        }
    }

    fclose(fp);

    return FU_SUCCESS;
}
static int upgrade_file_write_verify(const char *file_name)
{
    ea_image_header_t    ihdr;
    const char          *mtd_device;
    unsigned long        cksum;
    char                 rbuf [NAND_BLOCK_SIZE];
    int                  ii, mock, rest, restcnt;
    int                  total;
    int                  bb, mtd;
    int                  fd;
    int                  rv;
    int                  nErase = 0, count = 0, percent = 15, ratio = 0;

    bb = utils_get_bootbank();

    if(bb < 0)
    {
        return FU_BOOTBANK_INVALID;
    }

    bb ^= 1; // bootbank toggle

    if((fd = open(file_name, O_RDONLY)) < 0)
    {
        return FU_FILE_NOT_OPEN;
    }

    total   = 0;
    restcnt = 1;

    for(;;)
    {
        if(total >= g_file_size)
        {
            break;
        }

        total += read(fd, &ihdr, sizeof(ihdr));

        mtd = ihdr.itype;

        if(ihdr.itype == 5)
        {
            mtd += bb;
        }

        mtd_device = eaImageInfo[mtd].mtdblock;

        if(mtd_device == NULL)
        {
            total += ihdr.fsize;

            lseek(fd, total, SEEK_SET);

            continue;
        }

        printf("\n");
        printf("-------------------------------------------------------\n");
        printf("image type : %d\n", ihdr.itype);
        printf("image name : %s\n", eaImageInfo[ihdr.itype].name);
        printf("image size : %ld\n", ihdr.fsize);
        printf("mtd_device : %s\n", mtd_device);
        fflush(stdout);

        printf("erase flash.\n"); fflush(stdout);

        if(ihdr.itype == 5)
        {
            ratio = (NAND_ROOTFS_SIZE/NAND_BLOCK_SIZE)/3;

            rv = nand_erase(mtd_device, 0, (NAND_ROOTFS_SIZE/NAND_BLOCK_SIZE), &ratio, &percent);
        }
        else
        {
            ratio = (ihdr.fsize/NAND_BLOCK_SIZE+1)/1;

            rv = nand_erase(mtd_device, 0, (ihdr.fsize/NAND_BLOCK_SIZE + 1), &ratio, &percent);
        }

        if((ihdr.itype == 5) && (rv < 0))
        {
            do {

                nErase++;

                ratio = ((NAND_ROOTFS_SIZE/NAND_BLOCK_SIZE)-nErase)/3;

                rv = nand_erase(mtd_device, 0, (NAND_ROOTFS_SIZE/NAND_BLOCK_SIZE)-nErase, &ratio, &percent);

                if(nErase >= 100)
                {
                    break;
                }

            } while(rv != 0);
        }

        if(rv < 0)
        {
            close(fd);
            return FU_FAIL_ERASE;
        }

        printf("write flash.\n"); fflush(stdout);

        ratio = (g_file_size/2048)/65;
        count = 0;

        rv = nand_write(mtd_device, fd, ihdr.fsize, &ratio, &percent);

        if(rv < 0)
        {
            close(fd);
            return FU_FAIL_WRITE;
        }

        sync();

        mock = ihdr.fsize / sizeof(rbuf);
        rest = ihdr.fsize % sizeof(rbuf);

        printf("verify flash.\n"); fflush(stdout);

        ratio = (g_file_size/NAND_BLOCK_SIZE)/15;
        count = 0;
        cksum = 0;

        for(ii = 0; ii < mock; ii++)
        {
            rv = nand_read(mtd_device, rbuf, ii*NAND_BLOCK_SIZE, sizeof(rbuf));

            if(rv < 0)
            {
                close(fd);
                return FU_FAIL_READ;
            }

            if(rv == 1)
            {
                // skip bad block
                mock++;
                continue;
            }

            cksum = ea_crc32(cksum, (unsigned char *)rbuf, (unsigned int)sizeof(rbuf));

            if(count++ >= ratio)
            {
                if(percent < 99)
                {
                    int *pPercent = g_new0(int, 1);

                    *pPercent = percent++;

                    event_send(QUEUE_APPMGR, QUEUE_QT_CORE, Send_QT_UPGRADE_PROGRESS, pPercent, g_free, NULL);
                }

                count = 0;
            }
        }

        if(rest)
        {
rest_skipbad:
            rv = nand_read(mtd_device, rbuf, ii*NAND_BLOCK_SIZE, sizeof(rbuf));

            if(rv < 0)
            {
                close(fd);
                return FU_FAIL_READ;
            }

            if(rv == 1)
            {
                ii++;
                goto rest_skipbad;
            }

            cksum = ea_crc32(cksum, (unsigned char *)rbuf, (unsigned int)rest);

            if(count++ >= ratio)
            {
                if(percent < 99)
                {
                    int *pPercent = g_new0(int, 1);

                    *pPercent = percent++;

                    event_send(QUEUE_APPMGR, QUEUE_QT_CORE, Send_QT_UPGRADE_PROGRESS, pPercent, g_free, NULL);
                }

                count = 0;
            }
        }

        if(cksum != ihdr.cksum)
        {
            printf("checksum mismatch : img(0x%08lx) cal(0x%08lx)\n", ihdr.cksum, cksum);
            close(fd);
            printf("-------------------------------------------------------\n");
            fflush(stdout);

            return FU_IMAGE_CKSUM_MISMATCH;
        }

        printf("checksum ok.\n"); fflush(stdout);

        if(ihdr.itype == 5)
        {
            char cmd[64];
            sprintf(cmd, "miscflash 1 1 %d NULL", bb);
            utils_system(cmd);
            utils_set_bootbank(bb);
            printf("boot bank is changed to \"%d\"\n", bb);
            fflush(stdout);
        }

        total += ihdr.fsize;

        lseek(fd, total, SEEK_SET);
    }

    close(fd);

    return FU_SUCCESS;
}
//----------------------------------------------------------------------------
// External function body:
//----------------------------------------------------------------------------
int utils_upgrade_firmware_pre_check(int *main_exist)
{
    DIR              *dp;
    struct dirent     recur;
    struct dirent    *dent;
    int               rv;

    chdir(EA_UPGRADE_DIR);

    g_model_type = utils_get_model_num();

    if(g_model_type < 0)
    {
        return FU_FAIL_GET_MODEL_TYPE;
    }

    dp = opendir(EA_UPGRADE_DIR);

    if(!dp)
    {
        printf("fail to open dir (%s)\n", EA_UPGRADE_DIR);
        return -1;
    }

    rv = FU_FILE_NOT_FOUND;

    for(;;)
    {
        readdir_r(dp, &recur, &dent);

        if(dent == NULL)
        {
            break;
        }

        if(!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
        {
            rv = FU_FILE_NOT_FOUND;
            continue;
        }

        if(!strcmp(dent->d_name, "name.txt"))
        {
            rv = FU_SUCCESS;
            continue;
        }

        if(upgrade_file_check(dent->d_name) != FU_SUCCESS)
        {
            rv = FU_FILE_INVALID;
            continue;
        }

        rv = upgrade_file_verify(dent->d_name);

        if(rv != FU_SUCCESS)
        {
            break;
        }

        if(!strncmp(dent->d_name, "cardvr", 6) || !strncmp(dent->d_name, "mdvr", 4))
        {
            *main_exist = 1;
        }
    }

    closedir(dp);

    return rv;
}
int utils_upgrade_firmware_check(void)
{
    int      rv;
    char     fileName [128];
    FILE    *fp    = fopen("/tmp/fuFileName", "r");

    if(!fp)
    {
        fprintf(stderr, "[Error] %s Not open fuFileName\n", __func__);
        return FU_FILE_NOT_OPEN;
    }

    fscanf(fp, "%s", fileName);

    fclose(fp);

    chdir(EA_UPGRADE_DIR);

    rv = FU_SUCCESS;

    if(upgrade_file_check(fileName) != FU_SUCCESS)
    {
        rv = FU_FILE_INVALID;
        return rv;
    }

    if(upgrade_file_verify(fileName) != FU_SUCCESS)
    {
        rv = FU_FILE_INVALID;
        return rv;
    }

    return rv;
}
int utils_test_upgrade_firmware_check(void)
{
    DIR              *dp;
    struct dirent     recur;
    struct dirent    *dent;
    int               rv;

    chdir(EA_UPGRADE_DIR);

    g_model_type = utils_get_model_num();

    if(g_model_type < 0)
    {
        return FU_FAIL_GET_MODEL_TYPE;
    }

    dp = opendir(EA_UPGRADE_DIR);

    if(!dp)
    {
        printf("fail to open dir (%s)\n", EA_UPGRADE_DIR);
        return -1;
    }

    rv = FU_FILE_NOT_FOUND;

    for(;;)
    {
        readdir_r(dp, &recur, &dent);

        if(dent == NULL)
        {
            break;
        }

        if(!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
        {
            rv = FU_FILE_NOT_FOUND;
            continue;
        }

        if(upgrade_file_check(dent->d_name) != FU_SUCCESS)
        {
            rv = FU_FILE_INVALID;
            continue;
        }

        rv = upgrade_test_file_verify(dent->d_name);

        if(rv != FU_SUCCESS)
        {
            break;
        }
    }

    closedir(dp);

    return rv;
}
int utils_upgrade_firmware(void)
{
    int      rv;
    FILE    *fp;
    char     cmd [128];

    chdir(EA_UPGRADE_DIR);

    fp = fopen("/tmp/fuFileName", "r");

    if(!fp)
    {
        fprintf(stderr, "[Error] %s Not open fuFileName\n", __func__);
        return FU_FILE_NOT_OPEN;
    }

    fscanf(fp, "%s", cmd);

    fclose(fp);

    rv = upgrade_file_write_verify(cmd);

    return rv;
}
int utils_test_upgrade_firmware(void)
{
    DIR              *dp;
    struct dirent     recur;
    struct dirent    *dent;
    int               rv;

    chdir(EA_UPGRADE_DIR);

    g_model_type = utils_get_model_num();

    if(g_model_type < 0)
    {
        return FU_FAIL_GET_MODEL_TYPE;
    }

    dp = opendir(EA_UPGRADE_DIR);

    if(!dp)
    {
        printf("fail to open dir (%s)\n", EA_UPGRADE_DIR);
        return -1;
    }

    rv = FU_FILE_NOT_FOUND;

    for(;;)
    {
        readdir_r(dp, &recur, &dent);

        if(dent == NULL)
        {
            break;
        }

        if(!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
        {
            rv = FU_FILE_NOT_FOUND;
            continue;
        }

        if(upgrade_file_check(dent->d_name) != FU_SUCCESS)
        {
            rv = FU_FILE_INVALID;
            continue;
        }

        rv = upgrade_test_file_verify(dent->d_name);

        if(rv != FU_SUCCESS)
        {
            break;
        }

        rv = upgrade_file_write_verify(dent->d_name);

        if(rv != FU_SUCCESS)
        {
            break;
        }
    }

    closedir(dp);

    return rv;
}
