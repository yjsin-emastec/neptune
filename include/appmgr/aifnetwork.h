#ifndef __AIFNETWORK_H__
#define	__AIFNETWORK_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_NET_VALUE_LEN	32

//----------------------------------------------------------------------------
// Structure of the Network status
//----------------------------------------------------------------------------
typedef struct
{
    char type          [MAX_NET_VALUE_LEN];	// network type, "dhcp" or "static"
    char ipaddr        [MAX_NET_VALUE_LEN];	// ip address
    char netmask       [MAX_NET_VALUE_LEN];	// subnet mask
    char gateway       [MAX_NET_VALUE_LEN];	// default gateway
    char dns1          [MAX_NET_VALUE_LEN];	// primary dns
    char dns2          [MAX_NET_VALUE_LEN];	// secondary dns
} network_property_t;

typedef struct
{
    char ipaddr        [MAX_NET_VALUE_LEN]; // ip address
    char netmask       [MAX_NET_VALUE_LEN]; // subnet mask
    char gateway       [MAX_NET_VALUE_LEN]; // default gateway
    char dns1          [MAX_NET_VALUE_LEN]; // primary dns
    char dns2          [MAX_NET_VALUE_LEN]; // secondary dns
} network_status_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int aif_network_init(void);
int aif_network_set_property(network_property_t *prop);
int aif_network_get_property(network_property_t *prop);

#ifdef __cplusplus
}
#endif

#endif /* __AIFNETWORK_H__ */
