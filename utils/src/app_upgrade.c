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
#include <sys/mount.h>
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
#include <ctype.h>

//----------------------------------------------------------------------------
// Project include files:
//----------------------------------------------------------------------------
#include "utils.h"
#include <eaimage.h>

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------
#define __DEV             "/dev"
#define __MOUNT_POINT     "/mnt"
#define __UPDIR           "/mnt/upgrade"
#define MAX_UPFILES       64
#define MAX_UPFILE_NAME   128

static char               device_node [32];
static char               upfold_name [128];
static char               upfile_name [MAX_UPFILES][MAX_UPFILE_NAME];
static const char        *file_prefix [] = { "mdvr", "cardvr", "bootld", "kernel", "btlogo", "rootfs", NULL };

//----------------------------------------------------------------------------
// Internal function body:
//----------------------------------------------------------------------------
static int file_check(const char *file_name)
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
//----------------------------------------------------------------------------
// external function body:
//----------------------------------------------------------------------------
int utils_appup_device_check()
{
    int      n  =  0;
    int      rv = -1;
    char     line     [1024];
    char     root     [16];
    char     hdd_list [256];
    char    *blank;
    char    *tmp;
    FILE    *fp;

    // Make Storage list
    bzero(hdd_list, sizeof(hdd_list));

    fp = popen("/bin/mount | grep estn", "r");

    if(fp)
    {
        while (!feof(fp))
        {
            if(fgets(line, sizeof(line), fp))
            {
                tmp = strstr(line, "sd");

                if(tmp)
                {
                    tmp[4] = '\0';
                    n += sprintf(hdd_list+n, "%s ", tmp);
                }
            }
        }

        pclose(fp);
    }

    fprintf(stderr, "%s:%d - HDD list (%s)\n", __FILE__, __LINE__, hdd_list);

    fp = fopen("/proc/diskstats", "r");

    if(fp == NULL)
    {
        return -1;
    }

    bzero(device_node, sizeof(device_node));
    bzero(root, sizeof(root));

    while (!feof(fp))
    {
        if(fgets(line, sizeof(line), fp))
        {
            tmp = strstr(line, "sd");

            if(tmp)
            {
                // Save name of root device
                blank  = strchr(tmp, ' ');
                *blank = '\0';
                sprintf(root, "%s", tmp);

                // Skip if HDD
                if(strstr(hdd_list, root))
                {
                    continue;
                }

                // Use it if USB with partition
                if(fgets(line, sizeof(line), fp))
                {
                    tmp = strstr(line, root);

                    if(tmp)
                    {
                        blank  = strchr(tmp, ' ');
                        *blank = '\0';
                        sprintf(device_node, "%s/%s", __DEV, tmp);
                    }
                    else
                    {
                        sprintf(device_node, "%s/%s", __DEV, root);
                    }
                }
                else
                {
                    sprintf(device_node, "%s/%s", __DEV, root);
                }

                // Select first device found
                fprintf(stderr, "%s:%d - selected USB node is %s\n", __FILE__, __LINE__, device_node);
                rv = 0;
                break;
            }
        }
    }

    fclose(fp);

    return rv;
}
int utils_appup_device_mount()
{
    int     ii;
    int     rv = -1;
    char    syscmd[128];

    for(ii=0; ii < 3; ii++)
    {
        memset(syscmd, 0, sizeof(syscmd));

        sprintf(syscmd, "/usr/sbin/ntfs-3g %s %s", device_node, __MOUNT_POINT);

        rv = utils_system(syscmd);

        if(rv != 0)
        {
            fprintf(stderr, "%s: NTFS mount fail. <%s %s> \n", __func__, device_node, __MOUNT_POINT);

            rv = mount(device_node, __MOUNT_POINT, "vfat", 0, NULL);
        }

        if(rv < 0)
        {
            if(errno != EBUSY)
            {
                fprintf(stderr, "%s: failed. mount rv.%d errno.%d\n", __func__, rv, errno);
                perror("** MOUNT-1 ** : ");
                rv = -1;
            }
            else
            {
                fprintf(stderr, "%s: maybe already mounted. <%s> \n", __func__, __MOUNT_POINT);
                perror("** MOUNT-2 ** : ");
                rv = 0;
            }
        }

        if(rv == 0)
        {
            fprintf(stderr, "%s: mount ok. <%s %s> \n", __func__, device_node, __MOUNT_POINT);
            return rv;
        }

        usleep(1000*100);
    }

    if(ii >= 3)
    {
        fprintf(stderr, "%s: mount fail. <%s %s> \n", __func__, device_node, __MOUNT_POINT);
    }

    return rv;
}
int utils_appup_device_unmount(void)
{
    int    rv;
    int    ii;

    for(ii = 0; ii < 5; ii++)
    {
        rv = umount2(__MOUNT_POINT, MNT_FORCE);

        if(rv < 0)
        {
            fprintf(stderr, "Unmount Fail. errno=%d\n", errno);
        }
        else
        {
            fprintf(stderr, "%s(): Unmount Success\n", __func__);
            break;
        }
    }

    return rv;
}
//------------------------------------------------------------------------------
// Return Value
//  -1 : FOLDER NOT FOUND
//  -2 : FILE NOT FOUND
//  -3 : INVALID FILE
//  -4 : BUFFER OVER
//------------------------------------------------------------------------------
int utils_appup_file_check(char *fname, int len)
{
    DIR                  *dp;
    struct dirent         recur;
    struct dirent        *dent;
    FILE                 *fp;
    ea_image_header_t     ihdr;
    int                   model_type;
    int                   upfile_nums;
    int                   ii;
    int                   n;

    model_type = utils_get_model_num();

    upfile_nums = 0;
    bzero(upfile_name[0], MAX_UPFILES*MAX_UPFILE_NAME);

    bzero(upfold_name, sizeof(upfold_name));
    strcpy(upfold_name, __UPDIR);

    chdir(upfold_name);

    dp = opendir(upfold_name);

    if(!dp)
    {
        printf("Fail to open dir (%s)\n", upfold_name);
        return -1;
    }

    for(;;)
    {
        readdir_r(dp, &recur, &dent);

        if(dent == NULL)
        {
            break;
        }

        if(file_check(dent->d_name) != 0)
        {
            continue;
        }

        fp = fopen(dent->d_name, "r");

        if(!fp)
        {
            continue;
        }

        if(strncmp(dent->d_name, "name", 4) != 0)
        {
            fread(&ihdr, 1, sizeof(ihdr), fp);

            fclose(fp);

            if((ihdr.version != EA_IMAGE_VERSION) || (ihdr.magic != EA_IMAGE_MAGIC))
            {
                continue;
            }
        }

        if(strncmp(dent->d_name, "btlogo", 6) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
        else if(strncmp(dent->d_name, "mdvr", 4) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
        else if(strncmp(dent->d_name, "cardvr", 6) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
        else if(strncmp(dent->d_name, "bootld", 6) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
        else if(strncmp(dent->d_name, "kernel", 6) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
        else if(strncmp(dent->d_name, "rootfs", 6) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
        else
        {
            if(ihdr.model == model_type)
            {
                sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
            }
        }

        if(upfile_nums >= MAX_UPFILES)
        {
            printf("MAX_UPFILES REACHED (%d) %s-%d\n", upfile_nums, __func__, __LINE__);
            break;
        }
    }

    chdir("/");

    closedir(dp);

    if(upfile_nums == 0)
    {
        return -2; // file not found
    }

    for(ii = 0, n = 0; ii < upfile_nums; ii++)
    {
        if(len <= n+strlen(upfile_name[ii]))
        {
            return -4; // buffer overflow
        }

        if(ii == 0)
        {
            n += sprintf(fname + n, "%s", upfile_name[ii]);
        }
        else
        {
            n += sprintf(fname + n, "\n%s", upfile_name[ii]);
        }
    }
    return 0;
}
int utils_test_get_firmware_model(int *model)
{
    *model = -1;

    return 0;
}
int utils_test_file_check(char *fname, int len)
{
    DIR                 *dp;
    struct dirent        recur;
    struct dirent       *dent;
    FILE                *fp;
    ea_image_header_t    ihdr;
    int                  model_type;
    int                  upfile_nums;
    int                  ii;
    int                  n;
    char                 buf [128];

    bzero(upfold_name, sizeof(upfold_name));

    strcpy(upfold_name, __UPDIR);

    model_type = utils_get_model_num();

    chdir(upfold_name);

    dp = opendir(upfold_name);

    if(!dp)
    {
        printf("Fail to open dir (%s)\n", upfold_name);
        return -1;
    }

    upfile_nums = 0;

    bzero(upfile_name[0], MAX_UPFILES*MAX_UPFILE_NAME);

    for(;;)
    {
        readdir_r(dp, &recur, &dent);

        if(dent == NULL)
        {
            break;
        }

        if(file_check(dent->d_name) != 0)
        {
            continue;
        }

        fp = fopen(dent->d_name, "r");

        if(!fp)
        {
            continue;
        }

        fread(&ihdr, 1, sizeof(ihdr), fp);

        fclose(fp);

        if((ihdr.version != EA_IMAGE_VERSION) || (ihdr.magic != EA_IMAGE_MAGIC))
        {
            continue;
        }

        if(strncmp(dent->d_name, "btlogo", 6) == 0)
        {
            sprintf(upfile_name[upfile_nums++], "%s", dent->d_name);
        }
    }

    chdir("/");

    closedir(dp);

    if(upfile_nums == 0)
    {
        return -2; // file not found
    }

    for(ii = 0, n = 0; ii < upfile_nums; ii++)
    {
        if(ii == 0)
        {
            n += sprintf(buf+n, "%s", upfile_name[ii]);
        }
        else
        {
            n += sprintf(buf+n, "\n%s", upfile_name[ii]);
        }
    }

    snprintf(fname, len, "%s", buf);

    return 0;
}
int utils_appup_file_copy()
{
    FILE    *fp_src;
    FILE    *fp_dst;
    char     path [128];
    char     wbuf [4096];
    int      fsize;
    int      mock;
    int      rest;
    int      total;
    int      bytes;
    int      ii;

    chdir(upfold_name);

    for(ii = 0; ii < MAX_UPFILES; ii++)
    {
        if(upfile_name[ii][0] == 0)
        {
            break;
        }

        fp_src = fopen(upfile_name[ii], "r");

        if(!fp_src)
        {
            return -1;
        }

        fseek(fp_src, 0, SEEK_END);

        fsize = ftell(fp_src);

        fseek(fp_src, 0, SEEK_SET);

        mock = fsize / sizeof(wbuf);
        rest = fsize % sizeof(wbuf);

        bzero(path, sizeof(path));
        sprintf(path, "%s/%s", EA_UPGRADE_DIR, upfile_name[ii]);

        fp_dst = fopen(path, "w");

        if(!fp_dst)
        {
            fclose(fp_src);
            return -1;
        }

        total = 0;

        for(;;)
        {
            if(total >= fsize)
            {
                break;
            }

            bytes = fread(wbuf, 1, sizeof(wbuf), fp_src);

            fwrite(wbuf, 1, bytes, fp_dst);

            total += bytes;
        }

        fclose(fp_src);
        fclose(fp_dst);
        sync();
    }

    return 0;
}
int utils_appup_file_copy_target(const char *fname, int len)
{
    FILE    *fp_src;
    FILE    *fp_dst;
    char     path      [128];
    char     path_file [256];
    char     wbuf      [4096];
    int      fsize;
    int      mock;
    int      rest;
    int      total;
    int      bytes;
    int      ii;

    //chdir(upfold_name);
    chdir("/");

    for(ii = 0; ii < MAX_UPFILES; ii++)
    {
        if(upfile_name[ii][0] == 0)
        {
            break;
        }
        else if(strncmp(upfile_name[ii], fname, len) != 0)
        {
            continue;
        }

        bzero(path_file, sizeof(path_file));
        sprintf(path_file, "%s/%s", upfold_name, upfile_name[ii]);

        fp_src = fopen(path_file, "r");

        if(!fp_src)
        {
            fprintf(stderr, "%s:%d - fopenfail (%s)\n", __FILE__, __LINE__, path_file);
            return -1;
        }

        fseek(fp_src, 0, SEEK_END);

        fsize = ftell(fp_src);

        fseek(fp_src, 0, SEEK_SET);

        mock = fsize / sizeof(wbuf);
        rest = fsize % sizeof(wbuf);

        bzero(path, sizeof(path));

        if(strrchr(upfile_name[ii], '/')!=NULL)
        {
            fprintf(stderr, "%s:%d - / Found (%s)->(%s)\n", __FILE__, __LINE__, upfile_name[ii], strrchr(upfile_name[ii], '/'));
            sprintf(path, "%s%s", EA_UPGRADE_DIR, strrchr(upfile_name[ii], '/'));
            fprintf(stderr, "%s:%d - path is (%s)\n", __FILE__, __LINE__, path);
        }
        else
        {
            sprintf(path, "%s/%s", EA_UPGRADE_DIR, upfile_name[ii]);
        }

        fp_dst = fopen(path, "w");

        if(!fp_dst)
        {
            fprintf(stderr, "%s:%d - fopen W fail (%s)\n", __FILE__, __LINE__, path);
            fclose(fp_src);
            return -1;
        }

        total = 0;

        for(;;)
        {
            if(total >= fsize)
            {
                break;
            }

            bytes = fread(wbuf, 1, sizeof(wbuf), fp_src);

            fwrite(wbuf, 1, bytes, fp_dst);

            total += bytes;
        }

        fclose(fp_src);

        fclose(fp_dst);

        sync();
    }

    return 0;
}
#if 0
//----------------------------------------------------------------------------
// For test:
//----------------------------------------------------------------------------
int main(void)
{
    char    fname [128];

    //--------------------------------------------
    // search device
    //--------------------------------------------
    if(utils_appup_device_check() < 0)
    {
        printf("USB NOT Found!\n");
        return -1;
    }

    //--------------------------------------------
    // mount device
    //--------------------------------------------
    if(utils_appup_device_mount() < 0)
    {
        printf("USB Mount Fail!  errno=%d\n", errno);
        return -1;
    }

    //--------------------------------------------
    // check file
    //--------------------------------------------
    bzero(fname, sizeof(fname));

    if(utils_appup_file_check(fname, sizeof(fname)-1) < 0)
    {
        printf("File NOT Found!\n");
        return -1;
    }

    printf("File Name : %s\n", fname);

    //--------------------------------------------
    // copy file
    //--------------------------------------------
    if(utils_appup_file_copy() < 0)
    {
        printf("Fail to copy file!\n");
        return -1;
    }

    return 0;
}
#endif
