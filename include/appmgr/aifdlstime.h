#ifndef __AIFDLSTIME_H__
#define	__AIFDLSTIME_H__

#ifdef __cplusplus
extern "C"{
#endif

int  get_dls_start_end_time       (cfg_dls_t *dls, int year, time_t *tDlsBegin, time_t *tDlsEnd);
int  make_dls_time_info           (cfg_dls_t *dls, int year, int isLive, dls_convert_info_t *dlsCheck);
int  get_days_of_month            (int year, int month);
int  apply_dls_to_calendar_log    (cfg_dls_t *dls, caldata_t *calLog, int count);

#ifdef __cplusplus
}
#endif

#endif /* __AIFDLSTIME_H__ */
