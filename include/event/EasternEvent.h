#ifndef _EASTERN_EVENT_H_
#define _EASTERN_EVENT_H_

#include <sys/time.h>
#include <DVR.h>
#include <glib.h>

enum SendQTEvent {
    Send_QT_INIT = 0,
    Send_QT_DISK,
    Send_QT_LIVE,
    Send_QT_PLAYER,
    Send_QT_KEYPAD,
    Send_QT_SEARCH_CALENDAR,
    Send_QT_SEARCH_TIMELINE,
    Send_QT_SEARCH_EVENT,
    Send_QT_DISK_STATE,
    Send_QT_DISK_FORMAT_PROCESS,
    Send_QT_PLAYER_STOP,
    Send_QT_TIME_CHANGE,
    Send_QT_BACKUP_LOG,
    Send_QT_BACKUP_MEDIA,
    Send_QT_SEARCH_AUDIO_TIMELINE,
    Send_QT_STATUSBAR_STATE,
    Send_QT_UPDATE_CONFIG,
    Send_QT_EVENT_POPUP,
    Send_QT_BACKUP_CALCULATION,
    Send_QT_EVENT_LOG_COUNT,
    Send_QT_EVENT_LOG_DATA,
    Send_QT_EVENT_LOG_BACKUP,
    Send_QT_EVENT_SATA_LINK_UP,
    Send_QT_EVENT_SATA_LINK_DOWN,
    Send_QT_EVENT_IO_ERROR,
    Send_QT_UPGRADE_PROGRESS,
    Send_QT_REMOVE_USB_MEMORY,
    Send_QT_ACC_POWER_OFF,
    Send_QT_MAX,
};

enum AppMgrEvent {
    APPMGR_EVENT_START_INIT = 0,
    APPMGR_EVENT_DISK_STATE,
    APPMGR_EVENT_FORMAT_PROCESS,
    APPMGR_EVENT_FORMAT_OK,
    APPMGR_EVENT_PBTIME,
    APPMGR_EVENT_PBEXIT,
    APPMGR_EVENT_DISK_INFO,
    APPMGR_EVENT_DISKMGR_REC_STATUS,
    APPMGR_EVENT_KEEP_ALIVE,
    APPMGR_EVENT_GET_DISK_RECYCLE,
    APPMGR_EVENT_DISK_TIME_MISMATCH,
    APPMGR_EVENT_REC_START_END_TIME,
    APPMGR_EVENT_UPDATE_CONFIG,
    APPMGR_EVENT_DELETE_FILE,
    APPMGR_EVENT_UPGRADE_FIRMWARE_BY_APP,
    APPMGR_EVENT_DATA_NOTIFY,
    APPMGR_EVENT_DISK_DETACH,
    APPMGR_EVENT_FORMAT_FAIL,
    APPMGR_EVENT_START_THREAD_SATA_LINK,
    APPMGR_EVENT_MAX
};

enum NetMgrEvent {
    NETMGR_EVENT_DHCP_START,
    NETMGR_EVENT_DHCP_STOP,
    NETMGR_EVENT_SET_INTERFACE,
    NETMGR_EVENT_SET_GATEWAY,
    NETMGR_EVENT_MAX,
};

typedef struct _DataNotify {
    int                status;
    char               text[4096];
} DataNotify;

enum InitProgress  {
    INIT_NONE = 0,              /* 0 */
    INIT_START,
    INIT_CHECK_DISK,
    INIT_RECORDER,
    INIT_PLAYER,
    INIT_LIVE,                  /* 5 */
    INIT_USB_STICK,
    INIT_UART,
    INIT_NETWORK,
    INIT_CANCEL,
    INIT_COMPLETE,              /* 10 */
    INIT_PROGRESS,
    INIT_MAX,
};

enum DiskMessage {
    DISK_NOT_EXIST = 0,         /* 0 */
    DISK_REMOVE_ERR,
    DISK_SB_RECOVER_ERR,
    DISK_SB_RECOVER_SUCCESS,
    DISK_FAIL_REPEATED,
    DISK_READ_ERR,              /* 5 */
    DISK_WRITE_ERR,
    DISK_NOT_DVRFS_ERR,
    DISK_MKFS_ERR,
    DISK_FS_BROKEN,
    DISK_TIME_ERR_1,            /* 10 */
    DISK_TIME_ERR_2,
    DISK_MOUNT_ERR,
    DISK_UNMOUNT_ERR,
    DISK_INDEXING_ERR,
    DISK_RECORD_PAUSE,          /* 15 */
    DISK_RECORD_RESUME,
    DISK_NEED_RECYCLE,
    DISK_RECYCLE_ERR,
    DISK_RECYCLE_DONE,
    DISK_CHANGE_ERR,            /* 20 */
    DISK_CHANGE_DONE,
    DISK_FULL_STOP_RECORD,
    DISK_FORMAT_END,
    DISK_MAX,
};

enum SearchEvent { 
    SEARCH_REC_TIME = 0, 
    SEARCH_EVENT_LOG, 
    SEARCH_ARCHIVE_LOG, 
    SEARCH_SYSTEM_LOG,
    SEARCH_POS_LOG,
    SEARCH_MAX,
};

enum UsbEvent {
    USB_DETECT_SUCCESS = 101,       /* 0 */
    USB_DETECT_ERROR,
    USB_MOUNT_SUCCESS,
    USB_MOUNT_ERROR,
    USB_UNMOUNT_SUCCESS,
    USB_UNMOUNT_ERROR,              /* 5 */
    USB_NOT_ENOUGH_SPACE,
    USB_FILE_NOT_FOUND,
    USB_INVALID_FILE,
    USB_CREATE_DIR_SUCCESS,
    USB_CREATE_DIR_ERROR,           /* 10 */
    USB_FILE_OPEN_SUCCESS,
    USB_FILE_OPEN_ERROR,
    USB_FILE_READ_ERROR,
    USB_FILE_WRITE_ERROR,
    USB_SAVE_SYSTEM_LOG,            /* 15 */
    USB_SAVE_EVENT_LOG,
    USB_SAVE_CONFIG,
    USB_LOAD_CONFIG,
    USB_BACKUP_MEDIA,
    USB_BACKUP_PROCESS
};

typedef struct _InitEvent {
    int                initType;    // INIT_CHECK_DISK ~ INIT_NETWORK
    char               progress;    // 0 ~ 100
    int                dialog_hide; // 1 is hide, 0 is show.
} InitEvent;

typedef struct _CalculationEvent {
    int                deviceFreeMb; // device free space
    unsigned long      mediaBytes;
    unsigned long      indexBytes;
} CalculationEvent;

typedef struct _KeepAliveEvent {
    int                node;
    time_t             timestamp;
} KeepAliveEvent;

typedef struct {
    unsigned long      requestTime;
    unsigned long      requestEndTime;
    int                channel;
} RequestKeyFrameInfo;

typedef struct {
    unsigned long      requestTime;
    int                channel;
    unsigned char      pMediaBuffer [16000];
    int                bytesMedia;
    int                fragment;
} ReplyKeyFrame;

typedef struct {
    unsigned long      requestTime;
    unsigned long      requestEndTime;
    int                channel;
} RequestAudioSampleInfo;

typedef struct {
    unsigned long      requestTime;
    int                channel;
    unsigned char      buf [16000];
    int                bufsiz;
    int                fragment;
} ReplyAudioSample;

typedef enum {
    CORE_EVENT_DISPLAY_CASCADE_LIVE,
    CORE_EVENT_DISPLAY_CASCADE_PB,
    CORE_EVENT_DISPLAY_CASCADE_SPLIT,
    CORE_EVENT_DISPLAY_CASCADE_DESTROY,
    CORE_EVENT_DISPLAY_CASCADE_BIND,
    CORE_EVENT_SET_ZOOM,
    CORE_EVENT_SET_VIDEO_LOSS,
    CORE_EVENT_INIT_DONE,
    CORE_EVENT_MAX,
    CORE_EVENT_MIN = CORE_EVENT_DISPLAY_CASCADE_LIVE
} CORE_EVENT_E;

typedef struct _CoreEvent {
    int                startChannel;
    int                splitChannel;
    int                covertChannelBit;

    struct motion_evt {
        int            channel;
        char           Map [28][18];
        int            partial;
        int            sens_value;
        int            width;
        int            height;
    } motionEvt;

    struct alarm_evt_t {
        int            channel;
        int            is_on;
    } alarmEvt;

    struct encode_evt_t {
        int            from;
    } encodeEvt;

} CoreEvent;

typedef struct _MotionEvent {
    int                channel;
} MotionEvent;

typedef struct _CoreZoomEvent {
    int                x;
    int                y;
    int                width;
    int                height;
} CoreZoomEvent;

typedef struct _CoreVoEvent {
    int                type;
    int                hdmi;
} CoreVoEvent;

typedef enum {
    ENCODE_EVENT_START,
    ENCODE_EVENT_STOP,
    ENCODE_EVENT_SET_CHANNEL_CONFIG,
    ENCODE_EVENT_GET_CHANNEL_CONFIG,
    ENCODE_EVENT_PING,
    ENCODE_EVENT_SET_WM,
    ENCODE_EVENT_SET_AUDIO_CHANNEL,
    ENCODE_EVENT_MAX,
    ENCODE_EVENT_MIN = ENCODE_EVENT_START
} ENCODE_EVENT_E;

typedef enum {
    MOTION_EVENT_INIT,
    MOTION_EVENT_DEINIT,
    MOTION_EVENT_START,
    MOTION_EVENT_STOP,
    MOTION_EVENT_SET_SENSITIVITY,
    MOTION_EVENT_REPORT,
    MOTION_EVENT_MAX,
    MOTION_EVENT_MIN = MOTION_EVENT_INIT
} MOTION_EVENT_E;

enum {
    FROM_HOST,
    FROM_SLAV,
    FROM_DISKMGR
};

typedef struct _EncodeEvent {
    int                channel;
    int                dual;
    int                nochange;
    int                from;
    int                is_playback;
    int                audio_channel;

    struct Encode_Config {
        unsigned long  type;
        unsigned long  encodeType;
        unsigned long  value;
    } encodeConfig;

} EncodeEvent;

typedef struct _WaterMark {
    int                channel;
    int                vech;
    unsigned char      au8Key  [16];
    unsigned char      au8User [32];
} WaterMark;

typedef enum {
    WORK_EVENT_LINK_UP,
    WORK_EVENT_LINK_DOWN,
    WORK_EVENT_LOCAL_PB_CONNECT,
    WORK_EVENT_LOCAL_PB_START,
    WORK_EVENT_LOCAL_PB_DISCONNECT,
    WORK_EVENT_LOCAL_PB_SPEED,
    WORK_EVENT_LOCAL_PB_DIRECTION,
    WORK_EVENT_LOCAL_PB_DEFAULT,
    WORK_EVENT_LOCAL_PB_STEP,
    WORK_EVENT_LOCAL_PB_JUMP,
    WORK_EVENT_LOCAL_PB_SETTIME,
    WORK_EVENT_LOCAL_PB_TIME,
    WORK_EVENT_LOCAL_PB_EXIT,
    WORK_EVENT_LOCAL_PB_START2,
    WORK_EVENT_LOCAL_PB_START_REAL,
    WORK_EVENT_LOCAL_PB_STOP,
    WORK_EVENT_LOCAL_PB_AUDIO_OUTPUT_CHANNEL,
    WORK_EVENT_SET_LOCAL_EVENT_SEARCH,
    WORK_EVENT_MAX,
    WORK_EVENT_MIN = WORK_EVENT_LINK_UP
} WORK_EVENT_E;

typedef enum {
    AUDIO_EVENT_PUT_STREAM,
    AUDIO_EVENT_ON,
    AUDIO_EVENT_OFF,
    AUDIO_EVENT_EXIT,
    AUDIO_EVENT_VENC_START,
    AUDIO_EVENT_VENC_STOP,
    AUDIO_EVENT_MAX,
    AUDIO_EVENT_MIN = AUDIO_EVENT_PUT_STREAM
} AUDIO_EVENT_E;

typedef struct _VdecStatus {
    int                node;
    int                channel;
    unsigned long      u32LeftStreamBytes;
} VdecStatus;

typedef struct _KeepAliveStatus {
    int                videoloss;
    int                highlight;
    int                sensor;
    int                motion;
    int                alarm;
    int                record   [16];
    int                motionCh [16];
    unsigned char      ch_name  [MAX_VIDEO_CH][MAX_CFG_STR_LEN];
    int                realsensor;
    int                realmotion;
    int                realalarm;
} KeepAliveStatus;

typedef struct _WorkEvent {
    int                DeviceType;
    int                data;
    int                direct; // 0 : BOTH, 1 : ENC, 2 : DEC
} WorkEvent;

typedef struct _WorkPlayEvent {
    int                videoChannelBit;
    int                audioChannelBit;
    unsigned long      playTime;
    int                duration;
    int                playSpeed;
    int                playDirection;
    int                jmpLevel;
    int                videoExit;
    int                audioOutputChannel;
    int                delay;
} WorkPlayEvent;

typedef struct _WorkTimeEvent {
    int                pbchnn;
    unsigned long      pbtime;
} WorkTimeEvent;

typedef enum {
    DISKMGR_EVENT_GET_CALENDAR_DATA,
    DISKMGR_EVENT_GET_EVENT_DATA,
    DISKMGR_EVENT_GET_TIMELINE_DATA,
    DISKMGR_EVENT_GET_DAYLINE_DATA,
    DISKMGR_EVENT_DISK_FORMAT,
    DISKMGR_EVENT_PRE_RECORD,
    DISKMGR_EVENT_WRITE_LOG_CHANNEL,
    DISKMGR_EVENT_SET_DISK_RECYCLE,
    DISKMGR_EVENT_GET_LOG,
    DISKMGR_EVENT_USER_FILE_DELETION,
    DISKMGR_EVENT_GET_REC_START_END_TIME,
    DISKMGR_EVENT_SHUTDOWN,
    DISKMGR_EVENT_USER_DISK_DETACH_CONFIRM,
    DISKMGR_EVENT_INFORM_HOST_OPMODE,
    DISKMGR_EVENT_MAX,
    DISKMGR_EVENT_MIN = DISKMGR_EVENT_GET_CALENDAR_DATA
} DISKMGR_EVENT_E;

typedef struct _EventStartEndTime {
    time_t             start;
    time_t             end;
} EventStartEndTime;

typedef struct _CalendarEvent {
    int                Type;
    int                Dest;
    int                dls;
    time_t             dlsBegin;
    time_t             dlsEnd;
} CalendarEvent;

typedef struct _TimelineEvent {
    int                Type;
    int                Dest;
    time_t             Now;
    int                dlsType;
} TimelineEvent;

typedef struct _PreRecordEvent {
    int                channel;
    unsigned long      seconds;
    int                prerecord;
} PreRecordEvent_t;

typedef struct _DiskInfo {
    char               model [32]; // model name
    int                slot;       // slot number [1~8]
    int                size;       // unit: gigabytes
    int                kind;       // 0: normal, 1: format required
} DiskInfo_t;

typedef struct _DiskState {
    int                code;
    int                actKind;
    int                hddIndex;
    int                hourStart;
    int                hourEnd;
    DiskInfo_t         hddInfo [MAX_HDD_COUNT];
} DiskState_t;

typedef struct _BackupStreamState {
    int                channel;         // Backup Channel
    int                duration;        // Backup Duration
    time_t             start_time;      // Backup Start Time
    long               streamTotalSize; // Backup Data Total Size
    unsigned long long channel_mask;    // Backup Data Exist Mask
} __attribute__ ((packed)) BackupStreamState_t;

typedef struct _DiskFormat {
    int                disk;
    unsigned long      total_file_count;
    unsigned long      remove_file_count;
    unsigned long      percent;
    unsigned long      remain_time;
} DiskFormat_t;

typedef struct _FileDeletion {
    time_t             start_time;
    time_t             end_time;
    int                isForce; // minute
} FileDeletion_t;

typedef struct _FileSystemError {
    int                time_mismatch;
    int                file_broken;
    int                disk_detach;
    int                detached_number;
    char               serial [8][128];
} FileSystemError_t;

typedef struct _DiskmgrRecStatus {
    unsigned long      type;
    unsigned long      data [127];
} DiskmgrRecStatus_t;

enum {
    LOG_MIN = 89,
    LOG_SYS,
    LOG_EVENT,
    LOG_CAPTURE,
    LOG_MAX
};

enum {
    LOG_CAPTURE_LIVE = 0,
    LOG_CAPTURE_PLAY,
    LOG_CAPTURE_VIDEO,
    LOG_CAPTURE_VIDEO_AVI,
    LOG_CAPTURE_VIDEO_AVI_TIMESTAMP,
    LOG_CAPTURE_VIDEO_EXE
};

#define MAX_WRITELOGDATA_SIZE        (4096-96)
typedef struct _WriteLogData {
    unsigned int       type;
    unsigned int       size;  // Bytes
    unsigned int       day;
    unsigned int       offset;
    unsigned int       count; // Packets
    char               data [MAX_WRITELOGDATA_SIZE];
} WriteLogData_t;

typedef struct _LowWantedEvent {
    unsigned int       type;
    unsigned int       offset;
    unsigned int       count;
    unsigned int       day;
    unsigned int       next;
    unsigned long      filter;
    int                dlsType;
} LogWantedEvent_t;

typedef struct _SmartInfo {
    int                flag;
    char               model[24];
    int                slot;
    int                power_on_hours;
    int                temperature;
    int                reallocated_sectors;
    int                pending_sectors;
    int                uncorrectable_sectors;
    int                spin_retry_count;
    unsigned long long total_sectors;
} SmartInfo_t;

typedef struct _DiskInfoEvent {
    int                totalSize [MAX_HDD_COUNT];
    int                freeSize  [MAX_HDD_COUNT];
    time_t             startTime;
    time_t             lastTime;
    int                hddCount;
    int                recycleSize;
    char               hddFull   [MAX_HDD_COUNT];
    time_t             recycleTime;
    time_t             addTime   [MAX_VIDEO_CH];
    SmartInfo_t        smartInfo [MAX_HDD_COUNT];
} DiskInfoEvent_t;

typedef struct _DiskRecycleEvent {
    int                recycle_none;  // 0: recycle on, 1: recycle no
    int                limit_hour;    // 0: record limit off , > 0: record limit days
} DiskRecycleEvent_t;

typedef struct _DiagDiskInfo {
    unsigned int       disk_total;
    unsigned int       port_num;
    unsigned long      arCapacity[8];
} stDiagDiskInfo;

typedef struct _StatusBarState {
    int                state;
    int                operationMode;
} StatusBarState_t;

typedef struct _EventPopup {
    int                type;
    int                ch;
} EventPopup_t;

typedef enum {
    EVENT_LOG_OCCUR_IMPACT = 0,
    EVENT_LOG_OCCUR_TRIGGER1,
    EVENT_LOG_OCCUR_TRIGGER2,
    EVENT_LOG_OCCUR_TRIGGER3,
    EVENT_LOG_OCCUR_TRIGGER4,
    EVENT_LOG_QUERY_COUNT,
    EVENT_LOG_QUERY_DATA,
    EVENT_LOG_QUERY_BACKUP,
} GSENSOR_GPS_EVENT_E;

#endif /* _EASTERN_EVENT_H_ */
