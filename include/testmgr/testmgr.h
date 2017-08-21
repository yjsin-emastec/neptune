#ifndef __TEST_MANAGER_H__
#define __TEST_MANAGER_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <time.h>
#include <DVR.h>
#include <event/EasternEvent.h>

#define MAX_VIDEO_CH 16

typedef struct test_disk_info_s {
    int            totalSize [MAX_HDD_COUNT];
    int            freeSize  [MAX_HDD_COUNT];
    time_t         startTime;
    time_t         lastTime;
    int            hddCount;
    int            recycleSize;
    int            hddIndex;
    SmartInfo_t    smartInfo [MAX_HDD_COUNT];
    DiskInfo_t     hddInfo   [MAX_HDD_COUNT];
} test_disk_info_t, *ptest_disk_info_t;

int             testmgr_init                       (void);
void            testmgr_deinit                     (void);
int             testmgr_set_rtc                    (int Rtc);
void            testmgr_checking_resolution        (int *mainW, int *mainH);
int             testmgr_disk_format                (int disk_num);
int             testmgr_get_format_result          (void);
int             testmgr_ping_test                  (void);
void            testmgr_factory_default            (void);
time_t          testmgr_get_rtc                    (void);
void            testmgr_keypad_event_control       (int enable);
void            testmgr_reboot                     (void);
int             testmgr_get_boot_format_state      (void);
void            testmgr_wait_diskmgr_boot          (void);
void            testmgr_wait_diskmgr_disk_state    (void);
unsigned int    testmgr_get_trigger                (void);
void            testmgr_set_audio                  (int mode, int channel);
int             testmgr_gsensor_data_read          (int *x, int *y, int *z);
int             testmgr_buzzer_ctrl                (int onoff);
int             testmgr_led_ctrl                   (int sel);

#ifdef __cplusplus
}
#endif

#endif //__TEST_MANAGER_H__
