#ifndef __NETMGR_H__
#define __NETMGR_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
    char xfer_mode    [64];
    char ip_noti      [64];
    char event_alarm  [64];
    char to           [64];
    char server       [64];
    char id           [64];
    char password     [64];
    char from         [64];
} netmgr_event_mail_t;

typedef struct
{
    char pri_server   [64];
    char snd_server   [64];
    char time_zone    [64];
    char conn_mode    [64];
    char conn_period  [64];
} netmgr_event_sntp_t;

typedef struct
{
    int  type;
    char server       [64];
    char userid       [64];
    char passwd       [64];
    int  period;
    char hostname     [64];
    char update       [64];
    char ezddns       [64];
    int port;
    int use_login;
} netmgr_event_ddns_t;

typedef struct
{
    char ipaddr       [32];
    char netmask      [32];
    char gateway      [32];
    char dns1         [32];
    char dns2         [32];
    char sport        [16];
    char wport        [16];
} netmgr_event_nets_t;

typedef struct
{
    int 				enable1;
    unsigned char		PhoneNumber1[32];
    int 				enable2;
    unsigned char		PhoneNumber2[32];
    int 				enable3;
    unsigned char		PhoneNumber3[32];
    int 				enable4;
    unsigned char		PhoneNumber4[32];
} netmgr_event_pushevent_t;

typedef struct
{
    char				type1;
    char				startstop1;
    unsigned char		PhoneID1[256];
    char				type2;
    char				startstop2;
    unsigned char		PhoneID2[256];
    char				type3;
    char				startstop3;
    unsigned char		PhoneID3[256];
    char				type4;
    char				startstop4;
    unsigned char		PhoneID4[256];
} netmgr_event_pushevent_ex_t;

typedef struct
{
    char				hostname[256];
}netmgr_event_commax_ddns_check_t;
//----------------------------------------------------------------------------
// External reference function prototypes
//----------------------------------------------------------------------------
int netmgr_init(void);
int netmgr_deinit(void);
int netmgr_nefind_init();

#ifdef __cplusplus
}
#endif

#endif	/* __NETMGR_H__ */
