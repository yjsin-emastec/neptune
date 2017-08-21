#ifndef __AIFBACKUP2_H__
#define __AIFBACKUP2_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <time.h>
#include <sys/time.h>
#include <glib.h>
#include <pthread.h>
#include <DVR.h>
#include <event/Event.h>
#include <event/EasternEvent.h>
#include <storage/data.h>

#define BACKUP_STATE_READY              0
#define BACKUP_STATE_RUN                1
#define BACKUP_STATE_STOP               2
#define BACKUP_STATE_DONE               3

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------
typedef enum {
    AIF_BACKUP_START = 0,
    AIF_BACKUP_CAPTURE,
    AIF_BACKUP_READ_MEDIA,
    AIF_BACKUP_ARCHIVING,
    AIF_BACKUP_DEVICE_READY,
    AIF_BACKUP_DEVICE_MOUNT,                           // 5
    AIF_BACKUP_MEDIA_INFO,
    AIF_BACKUP_DEVICE_CHECK,
    AIF_BACKUP_SIZE_CHECK,
    AIF_BACKUP_OPEN_DEVICE,
    AIF_BACKUP_SAVE2DEVICE,                            // 10
    AIF_BACKUP_CLOSE_DEVICE,
    AIF_BACKUP_CLOSE_FILE,
    AIF_BACKUP_NO_CHANNEL_SELECTED,
    AIF_BACKUP_END,
    AIF_BACKUP_FAILED,                                 // 15
    AIF_BACKUP_SUCCESS,
    AIF_HUGE_BACKUP_ALREADY_RUNNING,
    AIF_HUGE_BACKUP_DEVICE_NOT_FOUND,
    AIF_HUGE_BACKUP_UNKNOW_FILESYSTEM,		
    AIF_HUGE_BACKUP_NOT_ALREADY,                       // 20
    AIF_BACKUP_BURN,
    AIF_BACKUP_CHANNEL_CLEAR,
    AIF_BACKUP_CHANNEL_0,
    AIF_BACKUP_CHANNEL_1,
    AIF_BACKUP_CHANNEL_2,                              // 25
    AIF_BACKUP_CHANNEL_3,
    AIF_BACKUP_CHANNEL_4,
    AIF_BACKUP_CHANNEL_5,
    AIF_BACKUP_CHANNEL_6,
    AIF_BACKUP_CHANNEL_7,                              // 30
    AIF_BACKUP_CHANNEL_8,
    AIF_BACKUP_CHANNEL_9,
    AIF_BACKUP_CHANNEL_10,
    AIF_BACKUP_CHANNEL_11,
    AIF_BACKUP_CHANNEL_12,                             // 35
    AIF_BACKUP_CHANNEL_13,
    AIF_BACKUP_CHANNEL_14,
    AIF_BACKUP_CHANNEL_15,
} AIF_BACKUP_PROGRESS_E;

typedef enum {
    AIF_BACKUP_TYPE_LIVE_STILL,                        // LIVE: jpeg capture -> archive2diskmgr -> write2device
    AIF_BACKUP_TYPE_PLAYBACK_STILL,                    // PLAY: jpeg capture -> archive2diskmgr -> write2device
    AIF_BACKUP_TYPE_PLAYBACK_VIDEO,                    // PLAY: jpeg capture -> archive2diskmgr -> read(video) data & write2device
    AIF_BACKUP_TYPE_PLAYBACK_VIDEO_AVI,                // PLAY AVI: jpeg capture -> archive2diskmgr -> read(video) data & write2device
    AIF_BACKUP_TYPE_PLAYBACK_VIDEO_AVI_TIMESTAMP,      // PLAY AVI: jpeg capture -> archive2diskmgr -> read(video) data & write2device
    AIF_BACKUP_TYPE_ARCHIVE_VIDEO,                     // ARCH: read(video) data & write2device
    AIF_BACKUP_TYPE_ARCHIVE_VIDEO_AVI,                 // ARCH AVI: read(video) data & write2device
    AIF_BACKUP_TYPE_ARCHIVE_VIDEO_AVI_TIMESTAMP,       // ARCH AVI: read(video) data & write2device
    AIF_BACKUP_TYPE_ARCHIVE_STILL_LIVE,                // ARCH: read(jpeg) data -> write2device
    AIF_BACKUP_TYPE_ARCHIVE_STILL_PLAYBACK,            // ARCH: read(jpeg) data -> write2device
    AIF_BACKUP_TYPE_SYSTEM_LOG,                        // SYSL: write2device
    AIF_BACKUP_TYPE_EVENT_LOG,                         // EVTL: write2device
} AIF_BACKUP_TYPE_E;

typedef enum {
    AIF_BACKUP_DEVICE_USB,
} AIF_BACKUP_DEVICE_E;

typedef struct aif_backup_context_s {

    AIF_BACKUP_TYPE_E     eType;                       // backup type
    AIF_BACKUP_DEVICE_E   eDevice;                     // backup device

    int                   progressEventQid;            // QUEUE_QT_CORE
    int                   progressEventType;           // Send_QT_BACKUP_MEDIA, Send_QT_BACKUP_LOG

    int                   channel;                     // backup channel
    int                   split1;                      // is full screen
    int                   channelMask;                 // video only
    int                   dls;                         // dls flag
    int                   volume;

    time_t                timestampNow;
    time_t                timestampPbStart;
    time_t                timestampPbEnd;

    int                   fdMedia;                     // *.jpg, *.h264
    int                   fdIndex;                     // *.index

    int                   discStatus;
    int                   nextTrack;

    int                   deviceFreeMb;                // device free space
    char                  strDirYmd [32];
    char                  strDirHms [32];
    char                  strFile   [32];

    unsigned char        *pMediaData;
    unsigned long         mediaBytes;
    unsigned long         indexBytes;

    void                 *pLogData;
    int                   countLog;
    int                   calculation;

    pthread_t             tid;                         // backup thread id

    int                   exe_backup_flag;             // 0: ready 1: start 2: end
    unsigned long long    exe_player;
    unsigned long long    exe_data_size  [32];
    unsigned long long    exe_index_size [32];
    unsigned long long    exe_status     [32];
    unsigned long long    exe_backup_totalsize;
    unsigned long long    exe_error_flag;

} aif_backup_context_t, *paif_backup_context_t;

typedef struct backup_clip_player_file_info_s {
    unsigned long long    player;
    unsigned long long    dll;
    unsigned long long    data;
    unsigned long long    index;
} backup_clip_player_file_info_t;

//----------------------------------------------------------------------------
// External function prototypes:
//----------------------------------------------------------------------------
int aif_backup_start(aif_backup_context_t *pBackupContext);

#ifdef __cplusplus
}
#endif

#endif
