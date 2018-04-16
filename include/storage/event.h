#ifndef __EVENT_SQL_H__
#define __EVENT_SQL_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "sqlite3.h"

int    event_sql_init    (int hddNum);
int    event_sql_end     (void);

#ifdef __cplusplus
}
#endif
#endif // __EVENT_SQL_H__
