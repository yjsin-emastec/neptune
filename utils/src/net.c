#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "utils.h"

static struct sockaddr_in    gLiveAddress  [32][2];
static int                   gLiveSocket  [32][2];

static unsigned int i2a(char *dest, unsigned int x)
{
    register unsigned int    tmp    = x;
    register unsigned int    len    = 0;

    if(x >= 100)
    {
        *dest++ = tmp / 100 + '0';
        tmp     = tmp % 100;
        ++len;
    }

    if(x >= 10)
    {
        *dest++ = tmp / 10 + '0';
        tmp     = tmp % 10;
        ++len;
    }

    *dest++ = tmp + '0';

    return len + 1;
}
char *utils_inet_ntoa_r(struct in_addr in, char *buf)
{
    unsigned int      len    = 0;
    unsigned char    *ip     = (unsigned char*)&in;

    len  = i2a(buf,     ip[0]); buf[len] = '.'; ++len;
    len += i2a(buf+len, ip[1]); buf[len] = '.'; ++len;
    len += i2a(buf+len, ip[2]); buf[len] = '.'; ++len;
    len += i2a(buf+len, ip[3]); buf[len] = 0;

    return buf;
}

#if 0
static int check_interface(char *ifname)
{
    struct ifreq     *ifr;
    struct ifconf     ifcfg;
    int               sockfd;
    int               n;
    int               numreqs    = 30;
    int               ret;

    bzero(&ifcfg, sizeof(ifcfg));
    ifcfg.ifc_len = sizeof(struct ifreq) * numreqs;
    ifcfg.ifc_buf = malloc(ifcfg.ifc_len);

    if(!ifcfg.ifc_buf)
    {
        printf("Out of memory!\n");
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("Can't create socket!\n");
        free(ifcfg.ifc_buf);
        return -1;
    }

    // get all information of interface
    ret = ioctl(sockfd, SIOCGIFCONF, (char *)&ifcfg);

    if(ret < 0)
    {
        printf("ioctl error - SIOCGIFCONF\n");
        close(sockfd);
        free(ifcfg.ifc_buf);
        return -1;
    }

    ifr = ifcfg.ifc_req;

    for(n=0; n<ifcfg.ifc_len; n+=sizeof(struct ifreq))
    {
        if(strcmp(ifr->ifr_name, ifname) == 0)
        {
            // found
            close(sockfd);
            free(ifcfg.ifc_buf);
            return 0;
        }

        ifr++;
    }

    // not found
    close(sockfd);
    free(ifcfg.ifc_buf);
    return -1;
}
#endif
int utils_net_updown_interface(char *ifname, int updown)
{
    struct ifreq     ifr;
    int              sockfd;
    int              ret;

#if 0
    if(check_interface(ifname) < 0)
    {
        printf("\"%s\" is an unknown interface name!\n", ifname);
        return -1;
    }
#endif

    // create a channel to the NET kernel
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("Can't create socket!\n");
        return -1;
    }

    // set interface name
    ifr.ifr_name[IFNAMSIZ-1] = '\0';
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    // get flags
    ret = ioctl(sockfd, SIOCGIFFLAGS, &ifr);

    if(ret < 0)
    {
        printf("ioctl error - SIOCGIFFLAGS\n");
        close(sockfd);
        return -1;
    }

    // set flags
    if(updown)
    {
        // interface up
        ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
    }
    else
    {
        // interface down
        ifr.ifr_flags &= ~(IFF_UP | IFF_RUNNING);
    }

    ret = ioctl(sockfd, SIOCSIFFLAGS, &ifr);

    if(ret < 0)
    {
        printf("ioctl error - SIOCSIFFLAGS\n");
        close(sockfd);
        return -1;
    }

    close(sockfd);

    return 0;
}
int utils_net_set_interface(char *ifname, char *ip, char *mask)
{
    struct ifreq          ifr;
    struct sockaddr_in    sin;
    struct in_addr        addr;
    int                   sockfd;
    int                   ret;

#if 0
    if(check_interface(ifname) < 0)
    {
        printf("\"%s\" is an unknown interface name!\n", ifname);
        return -1;
    }
#endif

    // create a channel to the NET kernel
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("Can't create socket!\n");
        return -1;
    }

    // set interface name
    bzero(&ifr, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    // set ip address
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    inet_aton(ip, &addr);
    sin.sin_addr   = addr;
    memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr));
    ret            = ioctl(sockfd, SIOCSIFADDR, &ifr);

    if(ret < 0)
    {
        printf("ioctl error - SIOCSIFADDR\n");
        close(sockfd);
        return -1;
    }

    // set subnet mask
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    inet_aton(mask, &addr);
    sin.sin_addr   = addr;
    memcpy(&ifr.ifr_netmask, &sin, sizeof(struct sockaddr));
    ret            = ioctl(sockfd, SIOCSIFNETMASK, &ifr);

    if(ret < 0)
    {
        printf("ioctl error - SIOCSIFNETMASK\n");
        close(sockfd);
        return -1;
    }

    close(sockfd);

    return 0;
}
int utils_net_get_interface(char *ifname, char *ip, char *mask)
{
    int                    fd;
    struct ifreq           ifr;
    struct sockaddr_in    *pin;

    ip[0]   = '\0';
    mask[0] = '\0';

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd < 0)
    {
        return -1;
    }

    ifr.ifr_addr.sa_family = AF_INET;
    sprintf(ifr.ifr_name, "%s", ifname);

    if(ioctl(fd, SIOCGIFADDR, &ifr) < 0)
    {
        close(fd);
        return -1;
    }

    pin = (struct sockaddr_in *)&ifr.ifr_addr;

    utils_inet_ntoa_r(pin->sin_addr, ip);

    if(ip[0] == '\0')
    {
        sprintf(ip, "%s", "0.0.0.0");
    }

    if(ioctl(fd, SIOCGIFNETMASK, &ifr) < 0)
    {
        close(fd);
        return -1;
    }

    pin = (struct sockaddr_in *)&ifr.ifr_netmask;
    utils_inet_ntoa_r(pin->sin_addr, mask);

    if(mask[0] == '\0')
    {
        sprintf(mask, "%s", "0.0.0.0");
    }

    close(fd);

    return 0;
}
int utils_net_set_gateway(char *gw)
{
    int                   sockfd;
    struct rtentry        rt;
    struct sockaddr_in    sin;
    int                   err;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("Can't create socket!\n");
        return -1;
    }

    sin.sin_family      = AF_INET;
    sin.sin_addr.s_addr = inet_addr(gw);
    sin.sin_port        = 0;

    bzero(&rt, sizeof(rt));
    ((struct sockaddr_in *)&rt.rt_dst)->sin_family      = AF_INET;
    ((struct sockaddr_in *)&rt.rt_dst)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *)&rt.rt_dst)->sin_port        = 0;

    ((struct sockaddr_in *)&rt.rt_genmask)->sin_family      = AF_INET;
    ((struct sockaddr_in *)&rt.rt_genmask)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *)&rt.rt_genmask)->sin_port        = 0;

    memcpy((void *)&rt.rt_gateway, &sin, sizeof(sin));
    rt.rt_flags = RTF_UP | RTF_GATEWAY;
    err         = ioctl(sockfd, SIOCADDRT, &rt);

    if(err < 0)
    {
        printf("ioctl error - SIOCADDRT\n");
        close(sockfd);
        return -1;
    }

    close(sockfd);

    return 0;
}
int utils_net_del_gateway(char *gw)
{
    int                   sockfd;
    struct rtentry        rt;
    struct sockaddr_in    sin;
    int                   err;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("Can't create socket!\n");
        return -1;
    }

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(gw);
    sin.sin_port = 0;

    bzero(&rt, sizeof(rt));
    ((struct sockaddr_in *)&rt.rt_dst)->sin_family      = AF_INET;
    ((struct sockaddr_in *)&rt.rt_dst)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *)&rt.rt_dst)->sin_port        = 0;

    ((struct sockaddr_in *)&rt.rt_genmask)->sin_family      = AF_INET;
    ((struct sockaddr_in *)&rt.rt_genmask)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *)&rt.rt_genmask)->sin_port        = 0;

    memcpy((void *)&rt.rt_gateway, &sin, sizeof(sin));
    rt.rt_flags = RTF_UP | RTF_GATEWAY;
    err         = ioctl(sockfd, SIOCDELRT, &rt);

    if(err < 0)
    {
        printf("ioctl error - SIOCDELRT\n");
        close(sockfd);
        return -1;
    }

    close(sockfd);

    return 0;
}
int utils_net_get_gateway(char *gw)
{
    FILE          *fp;
    char           buf   [256];
    static char    iface [256];
    unsigned       destination;
    unsigned       gateway;
    unsigned       flags;
    unsigned       refcnt;
    unsigned       use;
    unsigned       metric;
    unsigned       mask;
    int            ret;

    fp = fopen("/proc/net/route", "r");

    if(!fp)
    {
        return -1;
    }

    while(fgets(buf, sizeof(buf)-1, fp))
    {
        if(!strncmp(buf, "Iface", 5))
        {
            continue;
        }

        ret = sscanf(buf, "%s\t%x\t%x\t%d\t%d\t%d\t%d\t%x", iface, &destination, &gateway, &flags, &refcnt, &use, &metric, &mask);

        if(ret < 8)
        {
            fprintf(stderr, "ERROR: line read error\n");
            continue;
        }

        if(destination != 0)
        {
            continue;
        }

        if(mask != 0)
        {
            continue;
        }

        sprintf(gw, "%u.%u.%u.%u",
                *(((unsigned char *)(&gateway)) + 0),
                *(((unsigned char *)(&gateway)) + 1),
                *(((unsigned char *)(&gateway)) + 2),
                *(((unsigned char *)(&gateway)) + 3));
    }

    fclose(fp);

    return 0;
}
int utils_net_get_hwaddr(char *ifname, char *mac)
{
    FILE    *fp;
    int      p [6];

    if(ifname)
    {
        fprintf(stderr, "utils_net_get_hwaddr() of %s\n", ifname);
    }

    fp = fopen("/tmp/ethaddr", "r");

    if(fp)
    {
        fscanf(fp, "ethaddr=%02x:%02x:%02x:%02x:%02x:%02x", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5]);

        sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", p[0], p[1], p[2], p[3], p[4], p[5]);

        fclose(fp);

        return 0;
    }

    return -1;
}
int utils_net_get_hwaddr1(char *ifname, char *mac)
{
    FILE    *fp;
    int      p [6];
    int      ii;

    if(ifname)
    {
        fprintf(stderr, "utils_net_get_hwaddr() of %s\n", ifname);
    }

    fp = fopen("/tmp/ethaddr", "r");

    if(fp)
    {
        fscanf(fp, "ethaddr=%02x:%02x:%02x:%02x:%02x:%02x", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5]);

        fclose(fp);

        for(ii = 0; ii < 6; ii++)
        {
            mac[ii] = (unsigned char)p[ii];
        }

        return 0;
    }

    return -1;
}
int utils_net_set_hwaddr(char *ifname, char *mac)
{
    int             sockfd;
    int             ii;
    struct ifreq    ifr;
    unsigned        m [6];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("Can't create socket!\n");
        return -1;
    }

    // set interface name
    bzero(&ifr, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);
    ifr.ifr_addr.sa_family = ARPHRD_ETHER;

    sscanf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]);

    for(ii = 0; ii < 6; ii++)
    {
        ifr.ifr_hwaddr.sa_data[ii] = m[ii];
    }

    if(ioctl(sockfd, SIOCSIFHWADDR, &ifr) < 0)
    {
        printf("ioctl error - SIOCSIFHWADDR\n");
    }

    close(sockfd);

    return 0;
}
void utils_net_local_live_send(unsigned char *buf, int len, int channel, int mainStream)
{
    int    size    = buf[2] * 256 + buf[3];

    if(len != (size + 4))
    {
        printf("utils_net_local_live_send buf error : len=%d size=%d\n", len, size);
    }

    size = sendto(gLiveSocket[channel][mainStream], buf, len, 0, (const struct sockaddr *)&gLiveAddress[channel][mainStream], sizeof(struct sockaddr_in));

    if(len != size)
    {
        printf("utils_net_local_live_send sendto error : len=%d size=%d\n", len, size);
    }
}
void utils_net_local_live_initialize(int count, int portStart)
{
    int    ii, jj;

    for(ii = 0; ii < count; ii++)
    {
        for(jj = 0; jj < 2; jj++)
        {
            gLiveSocket [ii][jj]                  = socket(PF_INET, SOCK_DGRAM, 0);
            gLiveAddress[ii][jj].sin_addr.s_addr  = inet_addr("127.0.0.1");
            gLiveAddress[ii][jj].sin_family       = AF_INET;
            gLiveAddress[ii][jj].sin_port         = htons(portStart + jj * 32 + ii);
        }
    }
}
