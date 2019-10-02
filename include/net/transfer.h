#ifndef __TRANSFER_H__
#define __TRANSFER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>

#define NON_BLOCK

#define FREE_MEM(p)                     \
    do {                                \
        if (p) free(p);                 \
    } while (0)

#define CLOSE_SOCK(sd)                  \
    do {                                \
        if (sd) netipc_sock_close(sd);  \
    } while (0)

#define CHECK_SOCK_AND_RETURN(rv)       \
    do {                                \
        if (rv < 0) {                   \
            return -1;                  \
        }                               \
    } while (0)

#define CHECK_SOCK_CLOSE_AND_RETURN(rv,sd)  \
    do {                                    \
        if (rv < 0) {                       \
            CLOSE_SOCK(sd);                 \
            return -1;                      \
        }                                   \
    } while (0)

#define CHECK_SOCK_CLOSE_AND_FREE_RETURN(rv,sd,p1,p2)  \
    do {                                               \
        if (rv < 0) {                                  \
            CLOSE_SOCK(sd);                            \
            FREE_MEM(p1);                              \
            FREE_MEM(p2);                              \
            return -1;                                 \
        }\
    } while (0)

#define CHECK_SOCK_AND_FREE_RETURN(rv,p1,p2)    \
    do {                                        \
        if (rv < 0) {                           \
            FREE_MEM(p1);                       \
            FREE_MEM(p2);                       \
            return -1;                          \
        }                                       \
    } while (0)

typedef int (*pserver_function_t)(int sock, void *arg);

#define NETIPC_JPEG_PORT_BASE          53000
#define NETIPC_DISKMGR_BACKUP_PORT     54000

int netipc_tcp_server(const char *ip, int port, void *func, void *func_arg);
int netipc_tcp_connect(const char *ip, int port);
int netipc_sock_error(int sock);
int netipc_sock_write(int sock, unsigned char *data, int len);
int netipc_sock_read (int sock, unsigned char *data, int len);
int netipc_sock_close(int sock);

unsigned long str2ulong(char *str);
char * ulong2str(unsigned long n);

#endif
