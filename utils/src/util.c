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
#include <sys/vfs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <time.h>

//----------------------------------------------------------------------------
// Project include files:
//----------------------------------------------------------------------------
#include <eaVersion.h>
#include "utils.h"

//----------------------------------------------------------------------------
// Global Variable:
//----------------------------------------------------------------------------
static int    _hw_revision          = 0;
static int    work_link_up_ready    = 1;
static int    audio_output          = 0;

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Internal function body:
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// External function body:
//----------------------------------------------------------------------------
char *atime(time_t time)
{
    struct tm      recur;
    struct tm     *tm;
    static char    __str [4][30];
    static char   *s;
    static int     x    = 0;

    tm = localtime_r((time_t *)&time, &recur);

    s = __str[x];

    if(++x == 4)
    {
        x = 0;
    }

    sprintf(s, "%4d-%02d-%02d-%02d:%02d:%02d",1900+tm->tm_year,1+tm->tm_mon,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec);

    return s;
}
char *atime_absolute(time_t time)
{
    struct tm      recur;
    struct tm     *tm;
    static char    __str [4][30];
    static char   *s;
    static int     x    = 0;

    tm = localtime_r((time_t *)&time, &recur);

    s = __str[x];

    if(++x == 4)
    {
        x = 0;
    }

    sprintf(s, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);

    return s;
}
time_t tm2time(int year, int mon, int day, int hour, int min, int sec)
{
    struct tm    tm;

    tm.tm_year  = year-1900;
    tm.tm_mon   = mon-1;
    tm.tm_mday  = day;
    tm.tm_hour  = hour;
    tm.tm_min   = min;
    tm.tm_sec   = sec;
    tm.tm_isdst = 0;

    return mktime(&tm);
}
int utils_get_hdd_nums(void)
{
    FILE    *fp;
    int      hdd;

    fp = fopen("/tmp/num_of_hdd", "r");

    if(fp == NULL)
    {
        printf("Fail to open %s.\n", "/tmp/num_of_hdd");
        return -1;
    }

    fscanf(fp, "%d", &hdd);

    fclose(fp);

    return hdd;
}
int utils_get_password(char *userid, char *passwd)
{
    int    rcode    = 0;

    if(!strncmp(userid, "admin", 5))
    {
        utils_cfg_get_item((char *)"sys.admin_passwd", passwd);
    }
    else
    {
        rcode = -1;
    }

    return rcode;
}
void utils_swap_int(char *p)
{
    p[0] = p[0];
}
void utils_swap_int_array(int *p, int count)
{
    int    ii;

    for(ii = 0; ii < count; ii++)
    {
        utils_swap_int((char *)&p[ii]);
    }
}
void utils_swap_short(char *p)
{
    p[0] = p[0];
}
int utils_get_vis_from_file(void)
{
    int    vis    = 1; // ntsc

    FILE *fp = fopen("/tmp/vis", "r");

    if(fp)
    {
        fscanf(fp, "%d", &vis);
        fclose(fp);
    }

    return vis;
}
int utils_check_uplink(void)
{
    FILE    *fp;
    int      link    = 0;

    utils_system("rtl8366 link > /tmp/uplink");

    fp = fopen("/tmp/uplink", "r");

    if(fp)
    {
        fscanf(fp, "PHY[0] : %d", &link);
        fclose(fp);
    }

    return link;
}
int utils_get_bootbank(void)
{
    int     bank    = -1;
    FILE    *fp     = fopen("/tmp/bootbank.txt", "r");

    if(fp)
    {
        fscanf(fp, "bootbank=%d", &bank);
        fclose(fp);
    }

    return bank;
}
void utils_set_bootbank(int bank)
{
    char    cmd [32];

    if(bank == 0 || bank == 1)
    {
        bzero(cmd, sizeof(cmd));
        sprintf(cmd, "fw_setenv bootbank %d\n", bank);
        utils_system(cmd);
    }
}
int utils_get_bootmode(void)
{
    FILE    *fp;
    char     buf [16];
    int      mode    = 1;

    bzero(buf, sizeof(buf));

    fp = fopen("/tmp/bootmode.txt", "r");

    if(fp)
    {
        fscanf(fp, "bootmode=%s", buf);
        fclose(fp);

        if(!strcmp(buf, "test"))
        {
            mode = 0;
        }
        else if(!strcmp(buf, "appl"))
        {
            mode = 1;
        }
    }

    return mode;
}
int utils_getpid_host(void)
{
    int      pid    = -1;
    FILE    *fp     = fopen("/tmp/host.pid", "r");

    if(fp)
    {
        fscanf(fp, "%d", &pid);
        fclose(fp);
    }

    return pid;
}
int utils_set_sw_version(void)
{
    FILE    *fp    = fopen("/tmp/sysinfo/sw_version", "w+");

    if(fp)
    {
        fprintf(fp, "%s", FIRMWARE_VERSION);
        fclose(fp);
        return 0;
    }

    return -1;
}
int utils_get_sw_version(char *ver)
{
    FILE    *fp    = fopen("/tmp/sysinfo/sw_version", "r");

    if(fp)
    {
        fscanf(fp, "%s", ver);
        fclose(fp);
        return 0;
    }

    return -1;
}
int utils_get_normal_total_size(char *pTotalGigaBytes)
{
    unsigned long    totalMegaBytes;
    struct statfs    bufStatfs;
    int              rv    = statfs("/storage/estn0/1/normal", &bufStatfs);

    if(rv == 0)
    {
        long long    blockK    = (long long)bufStatfs.f_bsize / 1024LL;
        long long    totalM    = ((long long)bufStatfs.f_blocks + (long long)bufStatfs.f_bavail - (long long)bufStatfs.f_bfree) * blockK / 1024LL;
        #if 0 // jungyver [17/04/08]
        long long    remainM   = (long long)bufStatfs.f_bavail * blockK / 1024LL;
        #endif
        totalMegaBytes         = (unsigned long)(totalM  & 0xFFFFFFFF);
        sprintf(pTotalGigaBytes, "%lu %s", totalMegaBytes/1024, "GigaByte");
    }
    else
    {
        sprintf(pTotalGigaBytes, "%s", "No Disk");
        fprintf(stderr, "[%s] statfs error...\n", "/storage/estn0/1/normal");
        return -1;
    }

    return 0;
}
int utils_get_event_total_size(char *pTotalGigaBytes)
{
    unsigned long    totalMegaBytes;
    struct statfs    bufStatfs;
    int              rv    = statfs("/storage/estn0/2/event", &bufStatfs);

    if(rv == 0)
    {
        long long    blockK    = (long long)bufStatfs.f_bsize / 1024LL;
        long long    totalM    = ((long long)bufStatfs.f_blocks + (long long)bufStatfs.f_bavail - (long long)bufStatfs.f_bfree) * blockK / 1024LL;
        #if 0 // jungyver [17/04/08]
        long long    remainM   = (long long)bufStatfs.f_bavail * blockK / 1024LL;
        #endif
        totalMegaBytes         = (unsigned long)(totalM  & 0xFFFFFFFF);
        sprintf(pTotalGigaBytes, "%lu %s", totalMegaBytes/1024, "GigaByte");
    }
    else
    {
        sprintf(pTotalGigaBytes, "%s", "No Disk");
        fprintf(stderr, "[%s] statfs error...\n", "/storage/estn0/2/event");
        return -1;
    }

    return 0;
}
int utils_set_hw_revision(int rev)
{
    FILE    *fp    = fopen("/tmp/sysinfo/hw_revision", "w+");

    if(fp)
    {
        fprintf(fp, "%d", rev);
        fclose(fp);
        _hw_revision = rev;
    }

    return 0;
}
int utils_get_hw_revision(void)
{
    return _hw_revision;
}
int utils_get_work_link_up_ready(void)
{
    return work_link_up_ready;
}
int utils_set_work_link_up_ready(int num)
{
    work_link_up_ready = num;

    return work_link_up_ready;
}
void utils_set_audio_output(int status)
{
    audio_output = status;
    fprintf(stderr, "%s: TODO: audio_output = %d \n", __func__, audio_output);
}
int utils_get_audio_output(void)
{
    return audio_output;
}
int utils_get_disk_format(void)
{
    int      format    = -1;
    FILE    *fp        = fopen("/tmp/disk_format", "r");

    if(fp)
    {
        fscanf(fp, "%d", &format);
        fclose(fp);
    }

    return format;
}
void utils_set_disk_format(int format)
{
    char    cmd [32];

    if(format == 0 || format == 1)
    {
        bzero(cmd, sizeof(cmd));
        sprintf(cmd, "fw_setenv disk_format %d\n", format);
        utils_system(cmd);
    }
}
unsigned int utils_get_mouse_event_count(void)
{
    unsigned int     val    = 0;
    FILE            *fp     = fopen("/proc/mouse_events/total", "r");

    if(fp)
    {
        fscanf(fp, "%u", &val);
        fclose(fp);
    }

    return val;
}
//-----------------------------------------------------------------------------
// DHCP Daemon
//-----------------------------------------------------------------------------
static int utils_dhcpd_config(const char *interface, const char *ip, const char *nmask)
{
    char             cmd       [128];
    char             conf_file [128];
    unsigned int     addr[4];
    FILE            *fp;

    if(ip == NULL)
    {
        return -1;
    }

    bzero(cmd, sizeof(cmd));
    sprintf(cmd, "ifconfig %s %s netmask %s", interface, ip, nmask);

    if(0 != utils_system(cmd))
    {
        bzero(cmd, sizeof(cmd));
        sprintf(cmd, "ifconfig %s 0.0.0.0", interface);
        utils_system(cmd);
        return -1;
    }

    sscanf(ip, "%d.%d.%d.%d", &addr[0], &addr[1], &addr[2], &addr[3]);
    addr[3] = (addr[3] + 10) & 0xff;

    bzero(conf_file, sizeof(conf_file));
    sprintf(conf_file, "/tmp/udhcpd-%s.conf", interface);

    fp = fopen(conf_file, "w+");

    if(!fp)
    {
        return -1;
    }

    fprintf(fp, "interface      %s\n", interface);
    fprintf(fp, "lease_file     /cfg/udhcpd-%s.leases\n", interface);
    fprintf(fp, "pidfile        /tmp/udhcpd-%s.pid\n", interface);
    fprintf(fp, "start          %u.%u.%u.%u\n",  addr[0], addr[1], addr[2], addr[3]);
    fprintf(fp, "end            %u.%u.%u.254\n", addr[0], addr[1], addr[2]);
    fprintf(fp, "option router  %s\n", ip);
    fprintf(fp, "option dns     %s\n", ip);
    fprintf(fp, "option subnet  %s\n", nmask);
    fprintf(fp, "option domain  local\n");
    fprintf(fp, "option lease   1576800000\n"); // 50 years
    fprintf(fp, "option ntpsrv  %s\n", ip);
    fclose(fp);

    bzero(cmd, sizeof(cmd));
    sprintf(cmd, "/usr/sbin/udhcpd %s", conf_file);

    utils_system(cmd);

    return 0;
}
#define MAXLINE        1024
#define SERVER_FILE    "/tmp/DomainSock"
int utils_system(const char *command)
{
    int                   rv;
    int                   client_len;
    int                   client_sockfd;

    char                  buf [MAXLINE];

    struct sockaddr_un    clientaddr;

    client_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if(client_sockfd == -1)
    {
        perror("socket error : ");
        return -1;
    }

    bzero(&clientaddr, sizeof(clientaddr));

    clientaddr.sun_family = AF_UNIX;

    strcpy(clientaddr.sun_path, SERVER_FILE);

    client_len = sizeof(clientaddr);

    if(connect(client_sockfd, (struct sockaddr *)&clientaddr, client_len) < 0)
    {
        perror("connect error : ");
        return -1;
    }

    memset(buf, 0x00, MAXLINE);
    sprintf(buf, "%s", command);

    write(client_sockfd, buf, strlen(buf));

    memset(buf, 0x00, MAXLINE);

    read(client_sockfd, buf, MAXLINE);

    rv = (int)strtol(buf, NULL, 10);

    printf("cmdClient : rv=%d\n", rv);

    close(client_sockfd);

    return rv;
}
int utils_read_date_file(int *year, int *mon, int *day, int *hour, int *min, int *sec)
{
    FILE    *fp    = fopen("/tmp/date.txt", "r");

    if(!fp)
    {
        return -1;
    }

    fscanf(fp, "YEAR=%d:MON=%d:DAY=%d:HOUR=%d:MIN=%d:SEC=%d", year, mon, day, hour, min, sec);

    fclose(fp);

    return 0;
}
int utils_mark_skip_timemismatch(void)
{
    int    fd    = open("/cfg/forced_data_erase", O_CREAT | O_SYNC, 0755);

    close(fd);

    return 0;
}
int utils_get_1st_ifname(char *ifname)
{
    FILE    *fp    = fopen("/etc/ifname1.conf", "r");

    if(fp)
    {
        fscanf(fp, "%s", ifname);
        fclose(fp);
        return 0;
    }

    return -1;
}
int utils_get_2nd_ifname(char *ifname)
{
    FILE    *fp    = fopen("/etc/ifname2.conf", "r");

    if(fp)
    {
        fscanf(fp, "%s", ifname);
        fclose(fp);
        return 0;
    }

    return -1;
}
int utils_get_sata_link(void)
{
    int      rv    = 0;
    FILE    *fp    = NULL;
    char    *str;
    char     sBuf [256];
    char     ata1 [ 16];
    char     ata2 [ 16];

    memset(sBuf, 0, sizeof(sBuf));
    memset(ata1, 0, sizeof(ata1));
    memset(ata2, 0, sizeof(ata2));

    fp = fopen("/tmp/sata_link", "r");

    if(fp == NULL)
    {
        printf("%s fail to open %s.\n", __func__, "/tmp/sata_link");
        return -1;
    }

    if(!fgets(sBuf, sizeof(sBuf), fp))
    {
        return -1;
    }

    str = strstr(sBuf, "ata1: SATA link");

    if(str)
    {
        sscanf(str, "ata1: SATA link %s", ata1);
    }

    if(!fgets(sBuf, sizeof(sBuf), fp))
    {
        return -1;
    }

    str = strstr(sBuf, "ata2: SATA link");

    if(str)
    {
        sscanf(str, "ata2: SATA link %s", ata2);
    }

    fclose(fp);

    if(strcmp(ata1, "up") == 0)
    {
        rv = 1;
    }
    else if(strcmp(ata2, "up") == 0)
    {
        rv = 2;
    }

    return rv;
}
int utils_exist_usb_stick(void)
{
    FILE    *fp;
    char    *str;
    char     sbuf [512];
    char     tmp  [ 64];
    int      isUsb    = 0;

    memset(sbuf, 0, sizeof(sbuf));

    fp = fopen("/proc/scsi/scsi", "r");

    if(fp == NULL)
    {
        printf("[%s] fail to open %s.\n", "/proc/scsi/scsi", __func__);
        return -1;
    }

    while(fgets(sbuf, sizeof(sbuf), fp))
    {
        str = strstr(sbuf, "Vendor:");

        if(str)
        {
            memset(tmp, 0, 64);
            sscanf(str, "Vendor: %s", tmp);

            if(strcmp(tmp, "ATA") != 0)
            {
                isUsb = 1;
            }
        }
    }

    fclose(fp);

    return isUsb;
}
int utils_get_last_scsi_id(void)
{
    int     ii;
    char    tmp [16];

    for(ii = 25; ii >= 0; ii--)
    {
        memset(tmp, 0, 16);
        sprintf(tmp, "/dev/sd%c", 'a'+ii);

        if(access(tmp, F_OK) == 0)
        {
            break;
        }
    }

    return ii;
}
