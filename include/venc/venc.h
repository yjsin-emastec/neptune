#ifndef __VENC_H__
#define __VENC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define MAX_CHANNEL_NUM         (32)
#define MINOR_CHANNEL_BASE      (16)

#define PASSIVE_STREAMING       (0)
#define ACTIVE_STREAMING        (1)

#define NAL_NUM                 (64)
typedef struct {
    unsigned char   *userData;
    struct timeval   timeValue;
    unsigned long    timestamp [8];
    int              lens      [NAL_NUM];
    unsigned char   *datas     [NAL_NUM];
    unsigned char    types     [NAL_NUM];
    int              index;
    int              line;
    int              channel;
} venc_data;

#define VENC_SLICE_MAX           64

typedef struct venc_stream_info_s {
    int                 channel;
    int                 pt;
    int                 bufsiz;
    unsigned long       timestamp;
    unsigned long long  u64PTS;
    int                 line;
    int                 lens  [VENC_SLICE_MAX];
    int                 types [VENC_SLICE_MAX];
    unsigned char      *datas [VENC_SLICE_MAX];
    unsigned char      *buf;
    unsigned long long  u64PTSAudio;
} venc_stream_info_t, *pvenc_stream_info_t;

typedef enum {
    RESOLUTION_D1 = 0,
    RESOLUTION_CIF,
    RESOLUTION_QCIF
} VIDEO_RESOLUTION_TYPE;

typedef enum {
    ATTR_TARGET_FRAMRATE,
    ATTR_GOP,
    ATTR_BITRATE,
    ATTR_ENMODE, /*0-VBR, 1-CBR, 2-ABR, 3-FIXQP */
    ATTR_RESOLUTION,
    ATTR_QUALITY,
    ATTR_SLICE,
    ATTR_MAX,
} VIDEO_ATTR_TYPE;

int            venc_init                    (void);
int            venc_deinit                  (void);
int            venc_encode_start            (int VeChn);
int            venc_encode_stop             (int VeChn);
int            venc_encode_start_diskmgr    (int VeChn);
int            venc_encode_stop_diskmgr     (int VeChn);
int            venc_get_stream              (venc_stream_info_t *pSi);
int            venc_getStream               (int channel, char *data, unsigned long long *pEncPTS);
int            venc_set_channel_config      (int VeChn, int Type, int Encode_Type, int Value);
int            venc_get_channel_config      (int VeChn, int Type, int Encode_Type);
unsigned long  venc_find_freq_VI            (void);
void           venc_set_start               (int channel, int start);

#define STREAM_AUDIO_MAXIMUM    32768
#define STREAM_INDEX_MAXIMUM    256
#define STREAM_BIT_CHANGE_GOP   0x01
#define STREAM_BIT_IN_AUDIO     0x02
#define STREAM_GOP_BUFF_N       4

typedef struct {
    int                 flagDataFlush;
    int                 flagTimeover;
    int                 abnormal;
    int                 noDisk;
    int                 stop;
    int                 bits;
    int                 countGop;
    int                 indexWrite;
    int                 indexCurrent;
    unsigned long long  ptsGopSecond[STREAM_GOP_BUFF_N];
    int                 status[STREAM_GOP_BUFF_N];

    int                 ptsVideoCompensate;
    unsigned long long  ptsVideoBase;
    unsigned long long  ptsVideoLast;
    int                 dropVideo;
    int                 alignVideo;
    int                 maximumVideo;
    int                 offsetVideo [STREAM_GOP_BUFF_N];
    int                 countVideo  [STREAM_GOP_BUFF_N];
    unsigned char      *bufferVideo [STREAM_GOP_BUFF_N];
    unsigned long       sizeVideo   [STREAM_GOP_BUFF_N][STREAM_INDEX_MAXIMUM];
    unsigned long long  ptsVideo    [STREAM_GOP_BUFF_N][STREAM_INDEX_MAXIMUM];

    int                 ptsAudioCompensate;
    unsigned long long  ptsAudioBase;
    int                 maximumAudio;
    int                 offsetAudio [STREAM_GOP_BUFF_N];
    int                 countAudio  [STREAM_GOP_BUFF_N];
    unsigned char      *bufferAudio [STREAM_GOP_BUFF_N];
    unsigned long       sizeAudio   [STREAM_GOP_BUFF_N][STREAM_INDEX_MAXIMUM];
    unsigned long long  ptsAudio    [STREAM_GOP_BUFF_N][STREAM_INDEX_MAXIMUM];

    unsigned char      *bufferAudioLive;
    int                 sizeAudioLive;
    unsigned long long  ptsAudioLive;

    int                 yeVideoCount;
    int                 yeAudioCount;
    unsigned long long  yePtsVideo;
    unsigned long long  yePtsAudio;
    unsigned long long  yePtsLast;
    time_t              yeSecond;
} EaStreamInfo;
//int                   nextWrite;   // -1: None
//unsigned char        *bufferVideoUsed[3];
//unsigned char        *bufferAudioUsed[3];
//int                   countAudioCurrent[EASTREAM_INDEX_MAXIMUM];

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
