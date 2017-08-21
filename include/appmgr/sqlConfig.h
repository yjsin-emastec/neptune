#ifndef __SQL_CONFIG_H__
#define __SQL_CONFIG_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "eaSqlite3.h"

#define EA_CFG_SYSTEM_                              "system."
#define EA_CFG_RECORD_                              "record."
#define EA_CFG_DISPLAY_                             "display."
#define EA_CFG_DEVICE_                              "device."
#define EA_CFG_NETWORK_                             "network."
#define EA_CFG_LIVE_                                "live."
#define EA_CFG_GLOBAL_                              "global."

int  config_get_integer_from_cfg     (char *where);
int  config_get_text_from_cfg        (char *where, char *buf);
int  config_get_int_text_from_cfg    (char *where, int *buf);
int  config_set_integer_to_cfg       (char *where, int value);
int  config_set_text_to_cfg          (char *where, char *buf);
int  config_set_int_text_to_cfg      (char *where, char *buf, int valueType);

int  config_get_integer_from_dev     (char *where);
int  config_get_text_from_dev        (char *where, char *buf);
int  config_get_int_text_from_dev    (char *where, int *buf);
int  config_set_integer_to_dev       (char *where, int value);
int  config_set_text_to_dev          (char *where, char *buf);
int  config_set_int_text_to_dev      (char *where, char *buf, int valueType);

int  config_init_sql                 (void);

#ifdef __cplusplus
}
#endif
#endif // __SQL_CONFIG_H__
