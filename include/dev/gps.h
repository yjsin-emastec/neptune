#ifndef _GPS_H_
#define _GPS_H_

#ifdef __cplusplus
extern "C"{
#endif

int gps_init      (void);
int gps_get_data  (double *latitude, double *longitude, double *speed);
int gps_get_time  (time_t *t);
int gps_get_time2 (time_t *t);

#ifdef __cplusplus
}
#endif

#endif /* _GPS_H_*/
