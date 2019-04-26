#ifndef __DVR_H__
#define __DVR_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <time.h>

//=============================================================================================
// DVR Status
//=============================================================================================
#define DVR_OK                         0
#define DVR_ERR                        (-1)
#define DVR_ERR_NODEVICE               (-2)
#define DVR_ERR_NOSPACE                (-3)
#define DVR_ERR_WRONGDEVICE            (-4)
#define DVR_ERR_NEEDTOFORMAT           (-5)
#define DVR_ERR_NOINTERNALSPACE        (-6)

#define DVR_NOT_INITIALIZED            (-2)
#define DVR_NOT_STARTED                (-3)

//=============================================================================================
// OEM CODE
//=============================================================================================
#define OEM_EASTERN                    0
#define OEM_ESTNKOR                    1
#define OEM_DAEJI                      2

//=============================================================================================
// Define
//=============================================================================================
#define MAX_YEAR                       2038

#define MAX_VIDEO_CH                   16
#define MAX_AUDIO_CH                   4
#define MAX_ALARM_OUT                  4
#define MAX_SENSOR_IN                  16
#define	MAX_HDD_COUNT                  1

#define MAX_DIV4_PAGE                  5
#define MAX_DIV9_PAGE                  3

#define ALL_CIF_4CH_NTSC               120
#define ALL_HALF_D1_4CH_NTSC           240
#define ALL_D1_4CH_NTSC                480
#define ALL_MIX_4CH_NTSC               480

#define ALL_CIF_4CH_PAL                100
#define ALL_HALF_D1_4CH_PAL            200
#define ALL_D1_4CH_PAL                 400
#define ALL_MIX_4CH_PAL                400

#define ALL_CIF_8CH_NTSC               240
#define ALL_HALF_D1_8CH_NTSC           480
#define ALL_D1_8CH_NTSC                480
#define ALL_MIX_8CH_NTSC               480

#define ALL_CIF_8CH_PAL                200
#define ALL_HALF_D1_8CH_PAL            400
#define ALL_D1_8CH_PAL                 400
#define ALL_MIX_8CH_PAL                400

#define ALL_CIF_16CH_NTSC              480
#define ALL_HALF_D1_16CH_NTSC          480
#define ALL_D1_16CH_NTSC               440
#define ALL_MIX_16CH_NTSC              400

#define ALL_CIF_16CH_PAL               400
#define ALL_HALF_D1_16CH_PAL           400
#define ALL_D1_16CH_PAL                360
#define ALL_MIX_16CH_PAL               320

/* audio mode */
#define AUDIO_LIVE                     0
#define AUDIO_PB                       1
#define AUDIO_LIVE_MUTE                2

/* audio state */
#define LIVE_AUDIO_MUTE                0
#define LIVE_AUDIO_MIX                 1
#define LIVE_AUDIO_SINGLE_1            2
#define LIVE_AUDIO_SINGLE_2            3
#define LIVE_AUDIO_SINGLE_3            4
#define LIVE_AUDIO_SINGLE_4            5
#define LIVE_AUDIO_SINGLE_5            6
#define LIVE_AUDIO_SINGLE_6            7
#define LIVE_AUDIO_SINGLE_7            8
#define LIVE_AUDIO_SINGLE_8            9
#define LIVE_AUDIO_SINGLE_9            10
#define LIVE_AUDIO_SINGLE_10           11
#define LIVE_AUDIO_SINGLE_11           12
#define LIVE_AUDIO_SINGLE_12           13
#define LIVE_AUDIO_SINGLE_13           14
#define LIVE_AUDIO_SINGLE_14           15
#define LIVE_AUDIO_SINGLE_15           16
#define LIVE_AUDIO_SINGLE_16           17

/* disk state */
#define	DS_CODE_HDD_NORMAL             0x5000
#define	DS_CODE_HDD_NOT_FOUND          0x5010
#define	DS_CODE_HDD_NOT_FORMATED       0x5012
#define	DS_CODE_BAD_FILESYSTEM         0x5014
#define	DS_CODE_HDD_FORMAT_START       0x5016
#define	DS_CODE_HDD_FORMAT_END         0x5018
#define	DS_CODE_HDD_FORMAT_NEED        0x501A
#define	DS_CODE_BAD_MAGIC              0x5020
#define	DS_CODE_MASTER_NOT_FOUND       0x5030
#define	DS_CODE_MASTER_MOVED           0x5032
#define	DS_CODE_DATA_OLD               0x5040
#define	DS_CODE_DATA_LOST              0x5042
#define DS_CODE_HDD_DETACHED           DS_CODE_DATA_LOST
#define	DS_CODE_HDD_INSERTED           0x5070
#define	DS_CODE_SLAVE_CHANGED          0x5072
#define	DS_CODE_FILESYSTEM_BROKEN      0x5073
#define	DS_CODE_MULTI_MASTER           0x5074
#define DS_CODE_SERIAL_MISMATCH        0x5075
#define DS_CODE_DISK_FULL              0x6000
#define DS_CODE_RECYCLE                0x6001
#define DS_CODE_RECYCLE_DONE           0x6002
#define DS_CODE_CHANGE                 0x6003
#define DS_CODE_CHANGE_DONE            0x6004

#define	DS_ACT_POWER_OFF               0x0010
#define	DS_ACT_DATA_DELETE             0x0020

/* file system error */
#define FS_TIME_MISMATCH               0x100
#define FS_TIME_MISMATCH_DONE          0x101

#define FS_DISK_DETACH                 0x200
#define FS_DISK_DETACH_DONE            0x201

/* string length */
#define MAX_FILEPATH_LEN               100
#define MAX_CFG_STR_LEN                50

/* video output device */
#define MODE_PAL_CVBS                  0
#define MODE_NTSC_CVBS                 1
#define MODE_PAL_VGA                   2
#define MODE_NTSC_VGA                  3
#define MODE_PAL_HDMI                  2
#define MODE_NTSC_HDMI                 3

/* osd status */
#define OSD_HIDE                       0
#define OSD_MIN                        1
#define OSD_MAX                        2

/* system state */
#define SYSTEM_SHUTDOWN                0
#define SYSTEM_FORMAT                  1
#define SYSTEM_TIME_SET                2
#define SYSTEM_LOAD_DEFAULT            3
#define SYSTEM_LOAD_FACTORY_DEFAULT    4
#define SYSTEM_TEST_MODE               5
#define SYSTEM_LOAD_CONFIG             6
#define SYSTEM_BOOTING_SHUTDOWN        7
#define SYSTEM_BOOTING_FORMAT          8
#define SYSTEM_SOFTWARE_UPGRADE        9
#define SYSTEM_VGA_RESOLUTION          10
#define SYSTEM_RESTART                 11

/* save type FIXME */
#define SAVE_TYPE_FILE                 1
#define SAVE_TYPE_BCAST                2
#define SAVE_TYPE_BOTH                 3

/* Search Menu */
#define SEARCH_MENU_TIMELINE           (0)
#define SEARCH_MENU_EVENT              (1)

/* RECORD TYPE */
#define RECORD_NONE                    0
#define RECORD_CONTINUE                1
#define RECORD_MOTION                  2
#define RECORD_SENSOR                  3
#define RECORD_SCHEDULE                4
#define RECORD_MANUAL                  5

/* date format */
#define DF_A_YYYY_MM_DD                0x00 // YYYY/MM/DD
#define DF_A_MM_DD_YYYY                0x01 // MM/DD/YYYY
#define DF_A_DD_MM_YYYY                0x02 // DD/MM/YYYY
#define DF_B_YYYY_MM_DD                0x03 // YYYY-MM-DD
#define DF_B_MM_DD_YYYY                0x04 // MM-DD-YYYY
#define DF_B_DD_MM_YYYY                0x05 // DD-MM-YYYY

/* LED */
#define LED_RECORD                     0x10000

#define FILTER_MAX_SIZE                128

#define LOG_STRING_LEN                 56
#define MAX_CAL_MONTH_DATA             60

#define MAX_CAPTURE_LOG                (200) // (4*1024)
#define MAX_EVENT_SEARCH_LOG           (200) // (4*1024)
#define MAX_EVENT_LOG_PAGE_DATA        (20)
#define MAX_SYSTEM_LOG                 (200) // (4*1024)

#define	DATA_EVENT_DATA_LEN            (8)

#define	MJPEG_DIR                      "/dev/mjpeg"

#define EVENT_LOG_ALL                  1
#define EVENT_LOG_IMPACT               2
#define EVENT_LOG_TRIGGER              3
#define EVENT_LOG_TRIGGER1             4
#define EVENT_LOG_TRIGGER2             5
#define EVENT_LOG_TRIGGER3             6
#define EVENT_LOG_TRIGGER4             7
#define EVENT_LOG_PARKING              8
#define EVENT_LOG_MOTION               9

#define EVENT_LOG_DESC                 1
#define EVENT_LOG_ASC                  2

#define SYSTEM_LOG_DESC                "DESC"
#define SYSTEM_LOG_ASC                 "ASC"
#define SYSTEM_LOG_MAX_LEN             40
#define SYSTEM_LOG_COUNT_PER_PAGE      15

//=============================================================================================
// Types and Enumerate
//=============================================================================================
enum {
    RESOLUTION_QUAD                  = 0, // 352*240
    RESOLUTION_HALF,                      // 352*480
    RESOLUTION_FULL,                      // 704*480
    RESOLUTION_QUAD_QUAD,                 // 176*120
    RESOLUTION_MAX,
};

enum {
    RESOLUTION_HD_1280x720           = 0,
    RESOLUTION_HD_640x360,
    RESOLUTION_HD_1920x1080,
    RESOLUTION_HD_960x540,
    RESOLUTION_HD_MAX,
};

enum {
    RESOLUTION_HD_NET_640x360        = 0,
    RESOLUTION_HD_NET_320x180,
    RESOLUTION_HD_NET_MAX,
};

enum {
    QUALITY_ECONOMY                  = 0, // LEVEL 1 (L)
    QUALITY_STANDARD                 = 1, // LEVEL 2
    QUALITY_HIGH                     = 2, // LEVEL 3
    QUALITY_SUPER                    = 3, // LEVEL 4
    QUALITY_ULTRA                    = 4, // LEVEL 5 (H)
    QUALITY_MAX,
};

enum {
    Split_1                          = 1,
    Split_4,
    Split_9,
    Split_16,
    Split_10                         = 10,
    Split_17                         = 17,
    SPLIT_MAX
};

enum {
    OPMODE_NONE                      = 0,
    OPMODE_GOTEST,
    OPMODE_FIRSTRUN,
    OPMODE_INIT,
    OPMODE_LIVE,
    OPMODE_LOGIN,
    OPMODE_SETUP,
    OPMODE_BACKUP,
    OPMODE_BACKUP_START,
    OPMODE_SEARCH,
    OPMODE_PLAYBACK,
    OPMODE_MESSAGE,
    OPMODE_INFO,
    OPMODE_WAIT,
};

typedef enum _PBSPEED {
    PB_SPEED_1                       = 1,
    PB_SPEED_2                       = 2,
    PB_SPEED_4                       = 4,
    PB_SPEED_8                       = 8,
    PB_SPEED_16                      = 16,
    PB_SPEED_32                      = 32,
    PB_SPEED_64                      = 64,
    PB_SPEED_128                     = 128,
    PB_SPEED_256                     = 256,
    PB_SPEED_512                     = 512,
    PB_SPEED_1024                    = 1024,
    PB_SPEED_0_5                     = -1,
    PB_SPEED_0_25                    = -2,
} PBSPEED;

typedef enum _PBSTATE {
    PB_PAUSE                         = 0,
    PB_PLAY                          = 1,
    PB_STOP                          = 2,
    PB_PLAY_READY                    = 3,
} PBSTATE;

typedef enum _PBDIRECTION {
    PB_REW                           = 0,
    PB_FF                            = 1,
} PBDIRECTION;

enum
{
    DLS_OFF                          = 0,
    DLS_DAY,
    DLS_START_DAY,
    DLS_END_DAY,
    DLS_START_END_DAY
};

enum {
    BACKUP_NO_DATA                   = 0,
    BACKUP_JPEG,
    BACKUP_AVI,
    BACKUP_NSF,
    BACKUP_H264
};

enum {
    FW_UPGRADE_READY                 = 0,
    FW_UPGRADE_DEVICE_CHECK_OK,
    FW_UPGRADE_DEVICE_CHECK_FAIL,
    FW_UPGRADE_DEVICE_MOUNT_OK,
    FW_UPGRADE_DEVICE_MOUNT_FAIL,
    FW_UPGRADE_FILE_CHECK_OK,
    FW_UPGRADE_FILE_CHECK_FAIL,
    FW_UPGRADE_FILE_COPY_OK,
    FW_UPGRADE_FILE_COPY_FAIL,
    FW_UPGRADE_OK,
    FW_UPGRADE_DURING,
    FW_UPGRADE_FAIL,
};

//=============================================================================================
// Types and Struct
//=============================================================================================
typedef struct _dls_convert_info {
    unsigned int             isChecked;
    unsigned int             isDlsEnabled;
    time_t                   tDlsBegin;
    time_t                   tDlsEnd;
    int                      dlsCheckYear;
    int                      dlsBeginMonth;
    int                      dlsBeginDay;
    int                      dlsBeginHour;
    int                      dlsEndMonth;
    int                      dlsEndDay;
    int                      dlsEndHour;
} dls_convert_info_t;


typedef struct _avi_smi_filter_info {
    char                     filter_magic_code [4];
    char                     filter_ver;
    char                     filter_encryption;
    char                     filter_reserved   [2];
    int                      filter_size;
    char                     filter_text       [116];
} avi_smi_filter_info;

typedef struct _disk_used_info {
    int                      totalSize;
    int                      freeSize;
    time_t                   startTime;
    time_t                   lastTime;
    int                      hddCount;
    int                      recycleSize;

    int                      smartInfo_flag;
    char                     smartInfo_model [24];
    int                      smartInfo_slot;
    int                      smartInfo_power_on_hours;
    int                      smartInfo_temperature;
    int                      smartInfo_reallocated_sectors;
    int                      smartInfo_pending_sectors;
    int                      smartInfo_uncorrectable_sectors;
    int                      smartInfo_spin_retry_count;
    int                      smartInfo_ata_id;

    char                     hddInfo_model   [32];       // model name
    int                      hddInfo_slot;               // slot number [1~8]
    int                      hddInfo_size;               // unit: gigabytes
    int                      hddInfo_kind;               // 0: normal, 1: format required

    int                      hddIndex;                   // DS_CODE_BAD_MAGIC, DS_CODE_DATA_OLD

} disk_used_info_t;

typedef struct _live_event_info {
    unsigned int             cameraLoss;
    unsigned int             cameraViError;
    unsigned int             cameraVis;
    unsigned int             recordOn;
    unsigned int             prerecordOn;
    unsigned int             diskSize;
    unsigned int             diskFree;
    unsigned int             diskRecycle;
    unsigned int             diskFull;
    time_t                   detectTime;
    unsigned int             changeRecordType;
} live_event_t;

typedef struct _time_change {
    time_t                   now;
} time_change_event_t;

typedef struct _cfg_dvr_device_info {
    unsigned char            videoNum;
    unsigned char            audioNum;
    unsigned char            sensorNum;
    unsigned char            alarmNum;
    unsigned char            maxHddNum;
    unsigned char            maxFps;
    unsigned char            model;
    unsigned char            oem;
    unsigned char            videoD1Num;
    unsigned char            videoHDNum;
    unsigned char            videoIPNum;
    unsigned char            subModel;
    unsigned char            region;
    unsigned char            subOem;
} cfg_dvr_device_info_t;

typedef struct _search_data{
    int                      type;                                // enum SearchEvent
    time_t                   now;                                 // search request time
    int                      dataCount;                           // log count // exist time bit if Time Line
    void                    *dataBuffer;                          // search data buffer
} search_data_t;

typedef struct _play_state_info {
    int                      type;                                // enum PlayEvent
    time_t                   now;                                 // playback time
    int                      ch;                                  // number of channel when event occur
} play_state_info_t;

typedef struct _caldata{
    int                      year;
    int                      month;
    int                      data [32];
} caldata_t;

typedef struct _time_search_info_ext {
    int                      channel [240];                       // 0 bit : video, 16 bit : audio /1 hour
} time_search_info_ext_t;

typedef struct _time_search_info {
    short                    channel [240];                       // (60sec/15sec) * 60min	//  0 bit : video, 16 bit : audio /1 hour
} time_search_info_t;

typedef struct {
    time_t                   timeT;
    unsigned char            category;
    unsigned char            type;
    unsigned char            filler1;
    unsigned char            filler2;
    unsigned char            data[DATA_EVENT_DATA_LEN];
} DataEvent;

typedef struct {	
    char                     ch;
    unsigned char            category;
    unsigned char            type;
    time_t                   timeT;
    time_t                   arch_timeT;
    char                     duration;
} DataEvent_Arch;

typedef struct _eventlog_info {
    unsigned char            ch;                                 // CH1 ~ CH16 : 0 ~ 15, SYSTEM START : 16
    unsigned char            rtype;                              // LOG_REC_TYPE_XXX
    unsigned char            status;                             // 0:off 1:on
    unsigned char            rev2;
    unsigned long            t;

    unsigned char            prerecord;                          // PreRecord Interval
    unsigned char            postrecord;                         // PostRecord Interval
} eventlog_info_t;

typedef struct _EVENT_LOG_DATA_S {
    char                     event_time [20];
    int                      total;
    int                      count;
    unsigned char            log_type;
    unsigned char            event_type;
    char                     filler     [2];
} EVENT_LOG_DATA_S;

typedef struct _SYSTEM_LOG_DATA_S {
    char                     time   [20];
    char                     log    [48];
    char                     filler [4];
    int                      total;
    int                      count;
} SYSTEM_LOG_DATA_S;

typedef struct _EVENT_LOG_QUERY_S {
    char                     start_time [20];
    char                     end_time   [20];
    int                      log_type;
    int                      log_sort;
    int                      offset;
    int                      nLog;
} EVENT_LOG_QUERY_S;

typedef struct _SYSTEM_LOG_QUERY_S {
    char                     start [20];
    char                     end   [20];
    char                     filter[20];
    int                      type;
    char                     sort  [8];
    int                      offset;
    int                      nLog;
} SYSTEM_LOG_QUERY_S;

typedef struct _syslog_info {
    unsigned int             rev;
    unsigned int             type;
    unsigned int             filler1;
    unsigned int             filler2;
    unsigned long            t;
    char                     strlog [LOG_STRING_LEN];
    unsigned char            ipaddr [4];
} syslog_info_t;

typedef struct _EVENT_LOG_OCCUR_S {
    struct tm                event_time;
    int                      event_type;
} EVENT_LOG_OCCUR_S;

typedef struct _SYSTEM_LOG_S {
    unsigned int             type;
    char                     log    [48];
    char                     filler [8];
} SYSTEM_LOG_S;

//=============================================================================================
// Global
//=============================================================================================
typedef struct _cfg_global {
    unsigned char            ntsc;                             // 0:PAL 1:NTSC 2:PAL_VGA 3:NTSC_VGA 4:PAL_HDMI 5:NTSC_HDMI
    unsigned char            manualRec;                        // 0:not_manual 1:manual_record
    unsigned char            alarmEnable;                      // 0:disable_alarm_out 1:enable_alarm_out
    unsigned char            sequence;                         // 0:off 1:on
    unsigned char            liveDivision;                     // 0:single 1:4-multi
    unsigned char            focusChannel;                     // channel number
    unsigned char            audioOut;
    unsigned char            lock;                             // 0:off 1:on
} cfg_global_t;

//=============================================================================================
// Live
//=============================================================================================
typedef struct _cfg_live {
    unsigned char            rotation_on;                      // seq button in the front enable/disable
    unsigned char            rotation_time;                    // 2,3,5,10,15,20,30 second
    unsigned char            rotation_magic   [4];
    unsigned char            rotation_channel [4];
    unsigned char            osd_status;                       // OSD_HIDE, OSD_MAX, OSD_MIN
    unsigned char            videoOutput_cvbs;                 // language
    unsigned char            key_beep;                         // true, false
    unsigned char            event_beep;                       // true, false

    // channel layout
    unsigned char            display_layout_4div  [MAX_DIV4_PAGE][4];
    unsigned char            display_layout_9div  [MAX_DIV9_PAGE][9];
    unsigned char            display_layout_full  [MAX_VIDEO_CH];
    unsigned char            display_layout_16div [MAX_VIDEO_CH];

    // layout indexing key
    unsigned char            key_layout_4div  [MAX_DIV4_PAGE][MAX_VIDEO_CH];
    unsigned char            key_layout_9div  [MAX_DIV9_PAGE][MAX_VIDEO_CH];
    unsigned char            key_layout_full  [MAX_VIDEO_CH];
    unsigned char            key_layout_16div [MAX_VIDEO_CH];

    unsigned char            display_ch  [MAX_VIDEO_CH];       // true, false
    unsigned char            rotation_ch [MAX_VIDEO_CH];       // true, false
    unsigned char            ch_name     [MAX_VIDEO_CH][MAX_CFG_STR_LEN];
} cfg_live_t;

//=============================================================================================
// Stream
//=============================================================================================
typedef struct _cfg_stream {
    unsigned char            resolution    [MAX_VIDEO_CH];
    unsigned char            quality       [MAX_VIDEO_CH];
    unsigned char            fr_hd         [MAX_VIDEO_CH];     // 720P/1080P HD full, quater
    unsigned char            fr_ntsc       [MAX_VIDEO_CH];     // ntsc : 30 fps
    unsigned char            fr_pal        [MAX_VIDEO_CH];     // pal  : 25 fps
    unsigned char            fr_full_ntsc  [MAX_VIDEO_CH];     // ntsc : 704*480 max. 30 fps
    unsigned char            fr_half1_ntsc [MAX_VIDEO_CH];     // ntsc : 352*480 max. 30 fps
    unsigned char            fr_quad_ntsc  [MAX_VIDEO_CH];     // ntsc : 352*240 max. 30 fps
    unsigned char            fr_full_pal   [MAX_VIDEO_CH];     // pal  : 704*576 max. 25 fps
    unsigned char            fr_half1_pal  [MAX_VIDEO_CH];     // pal  : 352*576 max. 25 fps
    unsigned char            fr_quad_pal   [MAX_VIDEO_CH];     // pal  : 752*288 max. 25 fps
} cfg_stream_t;

//=============================================================================================
// Record
//=============================================================================================
typedef struct _cfg_record {
    unsigned char           disk_save_type;                    // CFG_REC_SAVE_TYPE_FILE, CFG_REC_SAVE_TYPE_BCAST, CFG_REC_SAVE_TYPE_BOTH
    cfg_stream_t            record_main;
    unsigned int            record_days;
    unsigned char           record_type [MAX_VIDEO_CH];        // RECORD_NONE, RECORD_CONTINUE, RECORD_MOTION, RECORD_SENSOR, RECORD_SCHEDULE
    unsigned char           audio       [MAX_VIDEO_CH];        // on:true off:false
    unsigned char           record_mode [MAX_VIDEO_CH];        // on:true off:false
    unsigned char           pre_record  [MAX_VIDEO_CH];        // pre. recording time
    unsigned int            post_record [MAX_VIDEO_CH];        // recording time if event happen
} cfg_record_t;

typedef struct _cfg_dls {
    unsigned char           dls_flag;                          // DLS on(true)/off(false)/us(united state)/EU/other
    unsigned char           gmt_area;                          // gmt time area -12< x <12
    unsigned char           dls_start_mm;                      // DLS Start Month    : 0 ~ 11
    unsigned char           dls_start_dd;                      // DLS Start Week/Day : 0 ~ 4 (first,2th,3th,4th,last)/0~6(Sun~Sat)
    unsigned char           dls_start_hh;                      // DLS Start Hour     : 0 ~ 23
    unsigned char           dls_end_mm;                        // DSL Start Month    : 0 ~ 11
    unsigned char           dls_end_dd;                        // DLS Start Week/Day : 0 ~ 6 (first,2th,3th,4th,5th,6th,last)/0~6(Sun~Sat)
    unsigned char           dls_end_hh;                        // DLS Start Hour     : 0 ~ 23
} cfg_dls_t;

//=============================================================================================
// System
//=============================================================================================
typedef struct _cfg_system {
    unsigned char           remote_id;                         // 0 ~ 99
    unsigned char           date_format;                       // 0:yyyy/mm/dd 1:mm/dd/yyyy 2:dd/mm/yyyy 3:yyyy-mm-dd 4:mm-dd-yyyy 5:dd-mm-yyyy
    char                    license_plate [MAX_CFG_STR_LEN];   // license_plate
    cfg_dls_t               dls;
} cfg_system_t;

typedef struct _cfg_lan_static {
    unsigned char           ip_addr [4];                       // ip address
    unsigned char           gateway [4];                       // gateway
    unsigned char           subnet  [4];                       // subnet
    unsigned char           dns     [4];                       // dns server name
    unsigned char           dns2    [4];                       // dns2 server name
} cfg_lan_static_t;

typedef struct _cfg_ethernet {
    unsigned char           type;                              // 0:LAN, 1:DHCP
    cfg_lan_static_t        lan_static;
} cfg_ethernet_t;

//=============================================================================================
// Network
//=============================================================================================
typedef struct _cfg_network {
    cfg_ethernet_t          lan;
} cfg_network_t;

//=============================================================================================
// Storage
//=============================================================================================
typedef struct _cfg_storage {
    unsigned char          file_overwrite;                     // 1:overwrite 0:off Storage Recycle
    unsigned char          limit_recording;                    // 0:off 1:on
    unsigned char          limit_recording_days;
    unsigned char          diskfull_beep;                      // On Disk Full Beep 0:off 1:on
    unsigned char          record_stop_during_backup;          // 0:record_off 1:record_on
} cfg_storage_t;

//=============================================================================================
// Status Info
//=============================================================================================
typedef struct _cfg_status_info {
    char                  serial          [MAX_CFG_STR_LEN];   // mac address
    char                  sw_version      [MAX_CFG_STR_LEN];   // s/w version
    char                  hw_version      [MAX_CFG_STR_LEN];   // h/w version
    char                  ip_address      [MAX_CFG_STR_LEN];   // system ip address
    unsigned char         disk_count;                          // Number of Hdd disk.
    unsigned char         current_rec_hdd;                     // Record disk number
    unsigned char         current_play_hdd;                    // Playback disk number
    int                   Time_Count;						   // Total working time
    time_t                Time_Count_each [MAX_HDD_COUNT];     // each disk working time
    time_t                time_hdd_first;                      // first record time
    time_t                time_hdd_last;                       // last record time
} cfg_status_info_t;

//=============================================================================================
// Setup Data
//=============================================================================================
typedef struct _cfg_setup_data {
    cfg_global_t          gbl;
    cfg_live_t            live;
    cfg_record_t          rec;
    cfg_system_t          system;
    cfg_network_t         net;
    cfg_storage_t         storage;
} cfg_setup_data_t;

//=============================================================================================
// All Data
//=============================================================================================
typedef struct _cfg_all_data {
    cfg_setup_data_t     cfg_setup;
    cfg_status_info_t    cfg_info;
} cfg_all_data_t;

#ifdef __cplusplus
}
#endif

#endif //__DVR_H__
