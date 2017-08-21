#ifndef __EVENT_SQL_H__
#define __EVENT_SQL_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "sqlite3.h"

int event_sql_init(int hddNum);

#ifdef __cplusplus
}
#endif
#endif // __EVENT_SQL_H__
