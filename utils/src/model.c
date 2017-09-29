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
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//----------------------------------------------------------------------------
// Project include files:
//----------------------------------------------------------------------------
#include "utils.h"
#include "model_util.h"

//----------------------------------------------------------------------------
// Global Variables:
//----------------------------------------------------------------------------
static char    _l_model_name [128];

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Internal function body:
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// External function body:
//----------------------------------------------------------------------------
int utils_get_model_num(void)
{
    FILE    *fp;
    int      val    = -1;

    fp = fopen("/tmp/MODEL_NUM", "r");

    if(fp)
    {
        fscanf(fp, "%d", &val);
        fclose(fp);
    }

    return val;
}
int utils_get_sub_model(void)
{
    FILE    *fp;
    int      val    = -1;

    fp = fopen("/tmp/SUB_MODEL", "r");

    if(fp)
    {
        fscanf(fp, "%d", &val);
        fclose(fp);
    }

    return val;
}
int utils_get_oem_num(void)
{
    FILE    *fp;
    int      val    = -1;

    fp = fopen("/tmp/OEM_NUM", "r");

    if(fp)
    {
        fscanf(fp, "%d", &val);
        fclose(fp);
    }

    return val;
}
int utils_get_sub_oem(void)
{
    FILE    *fp;
    int      val    = -1;

    fp = fopen("/tmp/SUB_OEM", "r");

    if(fp)
    {
        fscanf(fp, "%d", &val);
        fclose(fp);
    }

    return val;
}
char *utils_get_model_name(void)
{
    int    model_num;
    int    model_sub;
    int    model_oem;
    int    sub_oem;

    if((model_num = utils_get_model_num()) < 0)
    {
        return (char *)"Unknown Model";
    }

    if((model_sub = utils_get_sub_model()) < 0)
    {
        return (char *)"Unknown Sub Model";
    }

    if((model_oem = utils_get_oem_num()) < 0)
    {
        return (char *)"Not Defined OEM";
    }

    if((sub_oem = utils_get_sub_oem()) < 0)
    {
        return (char *)"Not Defined SUB OEM";
    }

    FILE *fp = fopen("/tmp/sysname", "r");

    if(!fp)
    {
        return (char *)MODEL_NAME;
    }
    else
    {
        bzero(_l_model_name, sizeof(_l_model_name));

        fscanf(fp, "sysname=%s", _l_model_name);

        fclose(fp);

        if(_l_model_name[0])
        {
            return (char *)_l_model_name;
        }
        else
        {
            return (char *)MODEL_NAME;
        }
    }
}
