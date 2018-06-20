#ifndef __SYSTEM_LOG_H__
#define __SYSTEM_LOG_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "sqlite3.h"

int    system_log_init           (void);
int    system_log_end            (void);
int    system_log_event_start    (int hddNum);

#ifdef __cplusplus
}
#endif
#endif // __SYSTEM_LOG_H__
