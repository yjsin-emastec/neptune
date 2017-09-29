//----------------------------------------------------------------------------
// Standard include files:
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mount.h>
#include <pthread.h>

#include <errno.h>

//----------------------------------------------------------------------------
// Project include files:
//----------------------------------------------------------------------------
#include "utils.h"

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------
#define SAV_CONFIG_FILE     "/cfg/sav_config.txt"
#define RUN_CONFIG_FILE     "/dev/run_config.txt"
#define RUN_SETUP_CFG       "/dev/run_setup.cfg"
#define RES_CONFIG_FILE     "/dev/res_config.txt"
#define RES_SETUP_CFG       "/dev/res_setup.cfg"

#define LOC_CONFIG_FILE     "/dev/loc_config.txt"
#define CFG_SIZE_MAX        (262144)

//----------------------------------------------------------------------------
// Internal function prototypes:
//----------------------------------------------------------------------------
static int utils_cfg_copy(const char *src, const char *dst);

//----------------------------------------------------------------------------
// Globals:
//----------------------------------------------------------------------------
static pthread_mutex_t cfg_lock;

//----------------------------------------------------------------------------
// Internal function body:
//----------------------------------------------------------------------------
static int utils_cfg_copy(const char *src, const char *dst)
{
    FILE    *fsrc;
    FILE    *fdst;
    char     line [1024];

    fsrc = fopen(src, "r");

    if(!fsrc)
    {
        printf("[cfg] fail to open \"%s\"!\n", src);
        return -1;
    }

    fdst = fopen(dst, "w+");

    if(!fdst)
    {
        printf("[cfg] fail to open \"%s\"!\n", dst);
        fclose(fsrc);
        return -1;
    }

    for(;;)
    {
        if(!fgets(line, sizeof(line), fsrc))
        {
            break;
        }

        fputs(line, fdst);
    }

    fclose(fsrc);
    fclose(fdst);

    return 0;
}
//----------------------------------------------------------------------------
// External function body:
//----------------------------------------------------------------------------
void utils_cfg_init_mutex(void)
{
    pthread_mutex_init(&cfg_lock, NULL);
}
int utils_cfg_init(void)
{
    FILE    *sav_config_file;
    char     cmd [1024];

    sav_config_file = fopen(SAV_CONFIG_FILE, "r");

    if(sav_config_file)
    {
        fclose(sav_config_file);
        sprintf(cmd, "cp -a %s %s\n", SAV_CONFIG_FILE, RUN_CONFIG_FILE);
        utils_system(cmd);
    }
    else
    {
        sprintf(cmd, "touch %s\n", RUN_CONFIG_FILE);
        utils_system(cmd);
    }

    utils_cfg_init_mutex();

    utils_cfg_init_lock();

    return 0;
}
int utils_cfg_set_item(char *item, const char *value)
{
    FILE    *fp;
    char     wbuf [CFG_SIZE_MAX];
    char     line [128];
    int      len;
    int      found    = 0;

    pthread_mutex_lock(&cfg_lock);

    fp = fopen(RUN_CONFIG_FILE, "r");

    if(!fp)
    {
        printf("[cfg] fail to open \"%s\"! from utils_cfg_set_item errno:%d\n", RUN_CONFIG_FILE, errno);
        pthread_mutex_unlock(&cfg_lock);
        return -1;
    }

    bzero(wbuf, sizeof(wbuf));

    len = 0;

    for(;;)
    {
        if(!fgets(line, sizeof(line), fp))
        {
            break;
        }

        if(strstr(line, item))
        {
            len += sprintf(wbuf+len, "%s=%s\n", item, value);
            found = 1;
        }
        else
        {
            len += sprintf(wbuf+len, "%s", line);
        }
    }

    fclose(fp);

    if(!found)
    {
        len += sprintf(wbuf+len, "%s=%s\n", item, value);
    }

    fp = fopen(RUN_CONFIG_FILE, "w+");

    if(!fp)
    {
        printf("[cfg] fail to open \"%s\"! from utils_cfg_set_item errno:%d\n", RUN_CONFIG_FILE, errno);
        pthread_mutex_unlock(&cfg_lock);
        return -1;
    }

    fwrite(wbuf, 1, len, fp);

    fclose(fp);

    sync();

    pthread_mutex_unlock(&cfg_lock);

    return 0;
}
int utils_cfg_get_item(char *item, char *value)
{
    FILE    *fp;
    char    *str;
    char    *chr;
    char     rbuf [CFG_SIZE_MAX];

    pthread_mutex_lock(&cfg_lock);

    fp = fopen(RUN_CONFIG_FILE, "r");

    if(!fp)
    {
        printf("[cfg] fail to open \"%s\"! from utils_cfg_get_item error:%d\n", RUN_CONFIG_FILE, errno);
        pthread_mutex_unlock(&cfg_lock);
        return -1;
    }

    fread(rbuf, 1, sizeof(rbuf), fp);

    fclose(fp);

    str = strstr(rbuf, item);

    if(str)
    {
        chr  = strchr(str, '\n');
        *chr = 0;
        chr  = strchr(str, '=');

        sprintf(value, "%s", chr+1);

        pthread_mutex_unlock(&cfg_lock);

        return 0;
    }

    *value = '\0';
    pthread_mutex_unlock(&cfg_lock);

    return -1;
}
int utils_cfg_cpy_item(char *dst, const char *src)
{
    strcpy(dst, src);

    return 0;
}
int utils_cfg_cmp_item(const char *item1, const char *item2)
{
    return strcmp(item1, item2);
}
int utils_cfg_save(void)
{
    int    rv;

    pthread_mutex_lock(&cfg_lock);

    rv = utils_cfg_copy(RUN_CONFIG_FILE, SAV_CONFIG_FILE);

    pthread_mutex_unlock(&cfg_lock);

    return rv;
}
int utils_cfg_backup(const char *dst)
{
    int    rv;

    pthread_mutex_lock(&cfg_lock);

    rv = utils_cfg_copy(SAV_CONFIG_FILE, dst);

    pthread_mutex_unlock(&cfg_lock);

    return rv;
}
int utils_cfg_restore(const char *src)
{
    int    rv;

    pthread_mutex_lock(&cfg_lock);

    rv = utils_cfg_copy(src, SAV_CONFIG_FILE);

    pthread_mutex_unlock(&cfg_lock);

    return rv;
}
void utils_cfg_remove(void)
{
    pthread_mutex_lock(&cfg_lock);
    remove(SAV_CONFIG_FILE);
    pthread_mutex_unlock(&cfg_lock);
}
void utils_cfg_set_lock(int flag)
{
    FILE    *fp    = fopen(LOC_CONFIG_FILE, "w+");

    if(fp)
    {
        fprintf(fp, "%d", flag);
        fclose(fp);
    }
}
int utils_cfg_get_lock(void)
{
    FILE    *fp;
    int      flag    = EA_CONFIG_LOCK;

    fp = fopen(LOC_CONFIG_FILE, "r");

    if(fp)
    {
        fscanf(fp, "%d", &flag);
        fclose(fp);
    }

    return flag;
}
void utils_cfg_init_lock(void)
{
    utils_cfg_set_lock(EA_CONFIG_FREE);
}
void utils_cfg_get_from_res(void)
{
    char    syscmd [64];

    pthread_mutex_lock(&cfg_lock);

    sprintf(syscmd, "cp -a %s %s\n", RES_SETUP_CFG, RUN_SETUP_CFG);
    utils_system(syscmd);

    utils_cfg_copy(RES_CONFIG_FILE, RUN_CONFIG_FILE);

    pthread_mutex_unlock(&cfg_lock);
}
void utils_cfg_set_to_res(void)
{
    char    syscmd [64];

    pthread_mutex_lock(&cfg_lock);

    sprintf(syscmd, "cp -a %s %s\n", RUN_SETUP_CFG, RES_SETUP_CFG);
    utils_system(syscmd);

    utils_cfg_copy(RUN_CONFIG_FILE, RES_CONFIG_FILE);

    pthread_mutex_unlock(&cfg_lock);
}
void utils_cfg_erase(void)
{
    const char    configMtdDevice []    = "/dev/mtd2";
    const char    mountPoint      []    = "/cfg";
    const int     configSize            = 2 * 1024 * 1024;
    const int     nandBlockSize         = 128 * 1024;
    int           rv = -1;
    int           ii;

    pthread_mutex_lock(&cfg_lock);

    for(ii = 0; ii < 5; ii++)
    {
        if(umount2(mountPoint, MNT_FORCE) < 0)
        {
            fprintf(stderr, "Unmount Fail. errno=%d\n", errno);
        }
        else
        {
            fprintf(stderr, "%s(): Unmount Success\n", __func__);
            break;
        }
    }

    fprintf(stderr, "%s() : erase flash ...\n", __func__); fflush(stdout);

    rv = nand_erase_no_skip_badblock(configMtdDevice, 0, (configSize/nandBlockSize + 1));

    if(rv < 0)
    {
        fprintf(stderr, "%s() : erase flash Fail...!!\n", __func__);
        pthread_mutex_unlock(&cfg_lock);
        return;
    }

    fprintf(stderr, "%s() : erase flash Success...!!\n", __func__);

    pthread_mutex_unlock(&cfg_lock);
}
