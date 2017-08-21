#ifndef __CORE_H__
#define __CORE_H__

#include <time.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------
#define CORE_UTIL_ERR_BASE								(0xcaf10000)
#define CORE_MBS2_ERR_BASE								(0xcaf20000)
#define CORE_VOUT_ERR_BASE								(0xcaf30000)

#define CORE_OK											(HI_SUCCESS)
#define CORE_ERR_BASE									(0xcafe0000)
#define CORE_ERR_OUT_OF_MEMORY							(CORE_ERR_BASE+0x01)
#define CORE_ERR_NULL_PARAMETER							(CORE_ERR_BASE+0x02)
#define CORE_ERR_INVALID_ID								(CORE_ERR_BASE+0x03)
#define CORE_ERR_OUT_OF_PARAMETER						(CORE_ERR_BASE+0x04)
#define CORE_ERR_INVALID_STATE							(CORE_ERR_BASE+0x05)
#define CORE_ERR_NOT_SUPPORT 							(CORE_ERR_BASE+0x06)
#define CORE_ERR_BUSY 									(CORE_ERR_BASE+0x07)
#define CORE_ERR_OSAL 									(CORE_ERR_BASE+0x08)
#define CORE_ERR_TIMEOUT								(CORE_ERR_BASE+0x09)
#define CORE_ERR_INVALID_MODE 							(CORE_ERR_BASE+0x0a)

typedef enum {
	core_display_none,
	core_display_live,
	core_display_live_stream,
	core_display_playback,
	core_display_panorama,
	core_display_jpeg
} core_display_e;
typedef enum {
	coreProperty_All,
	coreProperty_Brightness,
	coreProperty_Contrast,
	coreProperty_Hue,
	coreProperty_Saturation
} coreProperty_t;

typedef enum {
	SD_DECODER_TYPE_NONE,
	SD_DECODER_TYPE_TW2868,
	SD_DECODER_TYPE_CX26828,
	SD_DECODER_TYPE_IDEN1100,
	SD_DECODER_TYPE_NAP9004,
	SD_DECODER_TYPE_TW2960,
	SD_DECODER_TYPE_NVP,
	SD_DECODER_TYPE_NVP6114,
	SD_DECODER_TYPE_ES8323,
	SD_DECODER_TYPE_MAX
} core_sd_decoder_type;


typedef struct camera_property_s {
	int hue;
	int brightness;
	int contrast;
	int saturation;
} camera_property_t, *pcamera_property_t;

typedef struct jpeg_header_s {
	int channel;
	int width;
	int height;
	int quality;
} jpeg_header_t, *pjpeg_header_t;

typedef struct video_buf_s {
	char *buffer;
	int width;
	int height;
	int stride;
} video_buf_t, *pvideo_buf_t;

typedef enum {
	core_channel_instantPb,
	core_channel_motionSearch
} core_channel_display_type;


//----------------------------------------------------------------------------
// External function prototypes:
//----------------------------------------------------------------------------
int core_set_display_destroy(void);
int core_set_display_bind(int split, int startChannel);
int core_set_display_split(int split, int startChannel);
int core_set_display_loss_hide(int channelLossBit);
int core_set_mode_display(int mode);
int core_set_alpha(int alpha);
int core_set_freeze(int onOff);
int core_set_bind_sequence(int firstVi, int firstVo, int secondVi, int secondVo);
int core_set_live_audio(int mode, int channel);
int core_set_live_audio_testmgr(int mode, int channel);

int core_set_camera_property(int ch, coreProperty_t type, camera_property_t property);

int core_get_color_key(void);
int core_get_display_split(int *nSplit);
int core_video_loss_get_loss(int *loss);
int core_video_get_current_vislist(int *vislist);
int core_decode_frame(unsigned char *pMediaBuffer, int bytesMedia, int position);
int core_decode_output_bind(int ch, unsigned char *payload, int length, int frameType, int marker, int clearBuffer, int block);
int core_decode_output_bind_audio(int ch, unsigned char *payload, int length, int block);
int core_decode_get_stat(int ch);
int core_init(int *width, int *height, int *vis);
int core_deinit(void);
int core_jpeg_snap(int screen, int channel, int width, int height, int quality, unsigned char **data, int *size);
int core_jpeg_sender_new(int channel);
void core_decode_output_clear(int channel);

int core_pip_display(int srcCh, int x, int y, int width, int height, int layer);
int core_set_playback_pause_state(int state);
void core_config_cvbs(int cvbs_mode, int x, int y, int w, int h);
void core_config_videoIn(void); 
int core_set_evnet_popup_split(int split, int *seqCh); 

unsigned int nvp6124_get_current_video_list(int *vislist);

#ifdef __cplusplus
};
#endif

#endif

