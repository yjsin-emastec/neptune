#ifndef _RTC_H_
#define _RTC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <sys/time.h>
#include <time.h>

#define RTC_BASE_TIME     1451606400
#define RTC_Y2K38_TIME    2145916800

void   rtc_set_time (time_t SetTime);
time_t rtc_get_time (void);
int    rtc_init     (void);

#ifdef __cplusplus
}
#endif

#endif /* _RTC_H_*/
