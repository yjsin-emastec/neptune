#ifndef __AIFSYSTEM_H__
#define	__AIFSYSTEM_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_SYS_VALUE_LEN  	64

//----------------------------------------------------------------------------
// Structure of the System Property
//----------------------------------------------------------------------------
typedef struct
{
    char license_plate     [MAX_SYS_VALUE_LEN];
    char language          [MAX_SYS_VALUE_LEN];
    char date_format       [MAX_SYS_VALUE_LEN];
    char time_format       [MAX_SYS_VALUE_LEN];
    char time_zone         [MAX_SYS_VALUE_LEN];
    char dls               [MAX_SYS_VALUE_LEN];
    char gps_sync          [MAX_SYS_VALUE_LEN];
    char admin_passwd      [MAX_SYS_VALUE_LEN];
    char system_lock       [MAX_SYS_VALUE_LEN];
} system_property_t;

typedef struct
{
    char sw_version        [MAX_SYS_VALUE_LEN];
} system_status_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  aif_system_init                (void);
int  aif_system_set_property        (system_property_t *prop);
int  aif_system_get_property        (system_property_t *prop);
int  aif_system_get_status          (system_status_t *status);
int  aif_system_adjust_time         (void);
int  aif_system_get_default_item    (char *item, char *dflt);

#ifdef __cplusplus
}
#endif

#endif /* __AIFSYSTEM_H__ */
