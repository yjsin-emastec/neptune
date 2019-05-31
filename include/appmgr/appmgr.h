#ifndef __APPMGR_H__
#define __APPMGR_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <DVR.h>

#include "syslog.h"
#include <event/EasternEvent.h>
#include <utils/utils.h>
#include "aifnetwork.h"
#include "aifsystem.h"
#include "aifconfig.h"
#include "aifstorage.h"
#include "storage/data.h"
#include "aifdlstime.h"
#include "aifdisplay.h"
#include "aifrecord2.h"
#include "aifdevice.h"

#define ESTN_HCMD_MASTER_PASSWORD   "43211243"
#define ESTN_HCMD_GOTO_TEST_MODE    "67761010"
#define ESTN_HCMD_SET_OSD_VIS       "67762011"
#define ESTN_HCMD_RES_OSD_VIS       "67762010"
#define ESTN_HCMD_SET_IMPACT_TEST   "67762021"
#define ESTN_HCMD_RES_IMPACT_TEST   "67762020"

#define RECORD_OFF                  0
#define PRE_RECORD                  1
#define RECORD_ON                   2

#define BEEP_DURATION_MAX           0x7fffffff

enum {
    ALARM_EVENT_TYPE_V_LOSS,
    ALARM_EVENT_TYPE_SENSOR,
    ALARM_EVENT_TYPE_MOTION,
    ALARM_EVENT_TYPE_HEALTH_CHECK,
    ALARM_EVENT_TYPE_RESTART,
    ALARM_EVENT_TYPE_SHUTDOWN,
    ALARM_EVENT_TYPE_PANIC_RECORD,
    ALARM_EVENT_TYPE_HDD_TEMPERATURE,
    ALARM_EVENT_TYPE_HDD_BAD_SECTOR,
    ALARM_EVENT_TYPE_HDD_ALMOST_FULL,
    ALARM_EVENT_TYPE_HDD_FULL,
    ALARM_EVENT_TYPE_HDD_FAILURE,
    ALARM_EVENT_TYPE_TEST,
};

enum {
    EVENT_POPUP_SENSOR_ON,
    EVENT_POPUP_SENSOR_OFF,
    EVENT_POPUP_MOTION_ON,
    EVENT_POPUP_MOTION_OFF,
};

enum {
    APPMGR_DEFAULT_REC_D1,
    APPMGR_DEFAULT_REC_960H,
    APPMGR_DEFAULT_REC_HD,
    APPMGR_DEFAULT_REC_FULLHD,
};

typedef enum {
    APPMGR_CALLBACK_POPUP_HIDE_SHOW = 0,
    APPMGR_CALLBACK_MAX
} APPMGR_CALLBACK_E;

typedef int (*pappmgr_callback_function)(void *arg);

extern cfg_dvr_device_info_t _devInfo;

int           load_config                               (void);
int           set_live_property                         (cfg_setup_data_t *cfgChanged);
int           set_record_property                       (cfg_record_t *cfgPrevRec, cfg_live_t *cfgPrevLive);
int           video_loss_event_detect                   (unsigned int prev, unsigned int now);
int           alarm_event_detect                        (int alarmOut, int type, int ch);
int           alarm_clear_check                         (int ch);
int           appmgr_load_run_config                    (cfg_setup_data_t *cfg);
int           appmgr_init                               (int *width, int *height);
void          appmgr_record_start                       (void);
void          appmgr_deinit                             (void);
void          appmgr_deinit_systemstate                 (int state);
void          appmgr_close_sensorlog                    (void);
void          appmgr_start_system                       (void);
int           appmgr_start_system_done                  (void);
int           appmgr_reboot_system                      (int state);
int           appmgr_is_system_started                  (void);
int           appmgr_get_device_info                    (cfg_dvr_device_info_t *devInfo);
int           appmgr_make_dls_time_info                 (int year, int isLive, dls_convert_info_t *dlsCheck);
int           appmgr_make_dls_time_info_local           (int year, int isLive, cfg_dls_t* dls, dls_convert_info_t *dlsCheck);
int           appmgr_apply_dls_to_calendar_log          (caldata_t *calLog, int count);
int           appmgr_get_days_of_month                  (int year, int month);
int           appmgr_conv_SearchEventLog                (DataEvent* pDataEvent, struct _eventlog_info* eventLog, int count);
int           appmgr_conv_SystemLog                     (DataEvent* pDataEvent, struct _syslog_info* sysLog, int count);
int           appmgr_get_system_version                 (char *hwVer, char *swVer);
int           appmgr_get_disk_info                      (disk_used_info_t *diskInfo);
int           appmgr_disk_format                        (int disk_num);
int           appmgr_disk_file_deletion                 (time_t start, time_t end, int isForce);
int           appmgr_disk_detach_confirm                (void);
int           appmgr_firstrun_setting                   (time_t now, int lang);
int           appmgr_set_system_rtc_time                (time_t now);
int           appmgr_go_testmode                        (void);
int           appmgr_go_appmode                         (void);
void          appmgr_keypad_power_off                   (void);
void          appmgr_set_beep_duration                  (int duration);
void          appmgr_set_beep_no_disk                   (int val);
void          appmgr_watchdog_enable                    (void);
void          appmgr_watchdog_disable                   (void);
int           appmgr_get_prerecord_interval             (int ch);
int           appmgr_get_postrecord_interval            (int ch);
int           appmgr_set_video_split                    (int startChNum, int split);
int           appmgr_set_video_property                 (int ch, int type, unsigned char brightness, unsigned char contrast, unsigned char hue, unsigned char saturation);
int           appmgr_set_audio_output_mix               (int mode, int ch);
int           appmgr_set_zoom                           (int x, int y, int width, int height);
int           appmgr_change_videoOut_channel            (int firstVi, int firstVo, int secVi, int secVo);
int           appmgr_get_config                         (cfg_setup_data_t *cfg);
int           appmgr_setup_enter                        (void);
int           appmgr_setup_leave                        (void);
int           appmgr_save_setup                         (int loadDefault, cfg_setup_data_t *cfg);
int           appmgr_still_image                        (int ch, int live, time_t captureTime, int split);
int           appmgr_backup_still_image                 (int storage, int opt);
int           appmgr_backup_video_clip                  (int ch, int startTime, int endTime, int storage, int mediaType, int opt);
int           appmgr_usb_save_or_load                   (int workType, void *pLogData, int count);
int           appmgr_jpeg_snap                          (int screen, int channel, int width, int height, int quality, unsigned char **data, int *size);
int           appmgr_search_enter                       (void);
int           appmgr_search_leave                       (void);
int           appmgr_search_stop                        (void);
int           appmgr_set_playback_deinterace            (int mode);
int           appmgr_search_get_date                    (int type, int destQueue);
int           appmgr_search_get_log                     (int type, int destQueue, time_t now, int dlsType, int nextLog);
int           appmgr_search_display_jpeg                (time_t now);
int           appmgr_search_goto                        (int type, time_t now);
int           appmgr_search_get_first_rec_time          (time_t *now);
int           appmgr_search_get_last_rec_time           (time_t *now);
int           appmgr_search_play_start                  (int ch, int split, time_t now, int duration);
int           appmgr_search_play_start_real             (void);
int           appmgr_search_set_time                    (time_t now);
int           appmgr_search_set_speed                   (int pbSpeed, int videoChannelBits);
int           appmgr_search_set_default                 (void);
int           appmgr_search_set_direction               (int pbDirection);
int           appmgr_search_set_step                    (void);
int           appmgr_search_set_jump                    (int direction);
int           appmgr_search_set_jump_level              (int direction, int jmp_level);
int           appmgr_search_select_ch                   (int ch);
int           appmgr_search_set_audio_output_channel    (int ch);
int           appmgr_search_set_audio_mute_on_off       (int mode, int ch);
int           appmgr_search_get_rec_start_end_time      (time_t *firstTime, time_t *lastTime);
int           appmgr_search_get_mode                    (void);
int           appmgr_search_set_pause_state             (int state);
void          appmgr_set_overwrite                      (int overwrite, int limithour);
void          appmgr_set_live_system_time               (time_t now);
time_t        appmgr_get_live_system_time               (void);
int           appmgr_password_check                     (char *pwd, int mode);
void          appmgr_set_send_event_ready               (int on);
void          appmgr_led_off                            (void);
void          appmgr_set_usb_flag                       (int value);
void          appmgr_set_split                          (int split);
int           appmgr_get_split                          (void);
void          appmgr_set_boot_disk_state                (int);
int           appmgr_get_boot_disk_state                (void);
void          appmgr_set_boot_fs_state                  (int boot_fs_state);
int           appmgr_get_boot_fs_state                  (void);
int           appmgr_get_video                          (void);
int           appmgr_get_vis                            (void);
void          appmgr_hwcursor_position                  (int x, int y);
void          appmgr_set_playber_bar_status             (int val);
void          appmgr_set_control_bar_auto_Hide          (int val);
void          appmgr_set_operationMode                  (int mode);
void          appmgr_set_screen_size                    (int width, int height);
void          appmgr_get_screen_size                    (int *width, int *height);
void          appmgr_get_key_frame                      (int channel, time_t start, time_t end, unsigned char *buffer, int *length);
void          appmgr_get_current_vislist                (int *parData);
void          appmgr_cfg_change                         (void);
void          appmgr_cfg_sync                           (void);
void          appmgr_get_cfg_display                    (void);
void          appmgr_create_rs_config                   (void);
void          appmgr_wait_diskmgr_boot                  (void);
void          appmgr_wait_diskmgr_filesystem_init       (int time_mismatch, int disk_detach);
void          appmgr_wait_diskmgr_disk_state            (void);
void          appmgr_set_mainwidget_size                (int width, int height);
int           appmgr_get_mainwidget_width               (void);
int           appmgr_get_mainwidget_height              (void);
int           appmgr_get_color_key                      (void);
int           appmgr_get_typeRecord                     (int ch);
int           appmgr_get_eventMotion                    (int ch);
int           appmgr_get_eventSensor                    (int ch);
int           appmgr_get_disk_detached_number           (void);
char         *appmgr_get_disk_detached_serial           (int i);
int           appmgr_get_upgrade_result                 (void);
void          appmgr_set_upgrade_result                 (int result);
int           aif_usb_cp                                (const char *src, const char *dst);
int           aif_usb_umount                            (const char *mpoint);
unsigned int  appmgr_get_ui_event_count                 (void);
int           appmgr_get_rtc_init_state                 (void);
void          appmgr_set_vo_ratio                       (int enable);
int           appmgr_usb_device_check                   (void);
void          appmgr_disk_recovery                      (int manual);
void          appmgr_set_save_disk_info                 (int state);
int           appmgr_get_save_disk_info                 (void);
int           appmgr_get_format_result                  (void);
int           appmgr_register_callback_function         (APPMGR_CALLBACK_E enType, pappmgr_callback_function func);
int           appmgr_format_cancel_and_reboot           (void);
int           aif_set_encodeType_minor                  (int encType);
void          appmgr_set_camera_vis                     (unsigned int val);
void          appmgr_config_cvbs                        (void);
void          appmgr_config_videoIn                     (void);
int           appmgr_get_max_fps                        (int streamtype, int ch, int resolution);
int           appmgr_get_default_rec_type               (int ch);
int           appmgr_set_event_popup_split              (int *chSeq, int split);
void          appmgr_gsensor_config                     (void);
int           appmgr_get_gps_connected                  (void);
int           appmgr_get_board_temperature              (void);
int           appmgr_sysinfo_set_factory_default        (void);
int           appmgr_get_sata_phy                       (void);
int           appmgr_write_system_log                   (SYSTEM_LOG_TYPE_E type, const char *log);
int           appmgr_close_circle_image                 (void);

#ifdef __cplusplus
}
#endif
#endif /* __APPMGR_H__ */
