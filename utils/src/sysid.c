//----------------------------------------------------------------------------
// Standard include files:
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

//----------------------------------------------------------------------------
// Project include files:
//----------------------------------------------------------------------------
#include <eaVersion.h>

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Global Variables:
//----------------------------------------------------------------------------
static int    __unitid    = -1;
static int    __video_mask;
static int    __node_mask;

//----------------------------------------------------------------------------
// External function body:
//----------------------------------------------------------------------------
int utils_sysid_get_unitid(unsigned *unitid)
{
    if(__unitid == -1)
    {
        FILE        *fp;
        unsigned     tmp;

        fp = fopen("/dev/unitid", "r");

        if(fp == NULL)
        {
            printf("Fail to open %s.\n", "/dev/unitid");
            return -1;
        }

        fscanf(fp, "%u", &tmp);

        fclose(fp);

        __unitid = *unitid = tmp;
    }
    else
    {
        *unitid = __unitid;
    }

    return 0;
}
int utils_sysid_get_unitid_host(unsigned *unitid)
{
    *unitid = 7;

    return 0;
}
int utils_sysid_get_unitid_slav(unsigned *unitid)
{
    *unitid  = 7;

    return 0;
}
int utils_sysid_get_unitid_nnas(unsigned *unitid)
{
    *unitid  = 7;

    return 0;
}
int utils_sysid_get_hw_version(char *ver)
{
    sprintf(ver, "%s", "1.0.0");

    return 0;
}
int utils_sysid_get_sw_version(char *ver)
{
    sprintf(ver, "%s", FIRMWARE_VERSION);

    return 0;
}
int utils_get_video_mask(void)
{
    return  __video_mask;
}
int utils_set_video_mask(int mask)
{
    return (__video_mask = mask);
}
int utils_get_node_mask(void)
{
    return  __node_mask;
}
int utils_set_node_mask(int mask)
{
    return (__node_mask = mask);
}
