/******************************************************************************
  Hisilicon HI3531D sample programs head file.

  Copyright (C), 2010-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2011-2 Created
******************************************************************************/

#ifndef __HI3531D_H__
#define __HI3531D_H__

#include "hi_common.h"
#include "hi_comm_sys.h"
#include "hi_comm_vb.h"
#include "hi_comm_vi.h"
#include "hi_comm_vo.h"
#include "hi_comm_venc.h"
#include "hi_comm_vpss.h"
#include "hi_comm_vdec.h"
#include "hi_comm_vda.h"
#include "hi_comm_region.h"
#include "hi_comm_adec.h"
#include "hi_comm_aenc.h"
#include "hi_comm_ai.h"
#include "hi_comm_ao.h"
#include "hi_comm_aio.h"
#include "hi_comm_hdmi.h"
#include "hi_defines.h"

#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_vi.h"
#include "mpi_vo.h"
#include "mpi_venc.h"
#include "mpi_vpss.h"
#include "mpi_vdec.h"
#include "mpi_vda.h"
#include "mpi_region.h"
#include "mpi_adec.h"
#include "mpi_aenc.h"
#include "mpi_ai.h"
#include "mpi_ao.h"
#include "mpi_hdmi.h"

#include "hifb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/*******************************************************
    macro define 
*******************************************************/
#define HI_MAX_CH					32
#define HI_MAX_CHIP					4
#define HI_MAX_VO_DEV				8
#define HI_MAX_VI_CH				16
#define HI_MAX_VPSS_BLOCK			2		// Live+Enc & Dec
#define HI_MAX_VENC_BLOCK			2		// Major & Minor

#define ALIGN_BACK(x, a)            ((a) * (((x) / (a))))
#if 1 // GyverJeong [19/08/20]
#define HI3531D_SYS_ALIGN_WIDTH      16
#else
#define HI3531D_SYS_ALIGN_WIDTH      64
#endif
#define HI3531D_PIXEL_FORMAT         PIXEL_FORMAT_YUV_SEMIPLANAR_420
#define HI3531D_VI_GetSubChn(x)		(x+16)

#define HI3531D_VO_DEV_DHD0         0
#define HI3531D_VO_DEV_DHD1         1
#define HI3531D_VO_DEV_DSD0         2
#define HI3531D_VO_DEV_VIRT0        3
#define HI3531D_VO_DEV_DSD1        -1

#if 1 // GyverJeong [19/08/07]
#define HI3531D_VO_LAYER_VHD0       0
#define HI3531D_VO_LAYER_VHD1       1
#define HI3531D_VO_LAYER_VPIP       2
#define HI3531D_VO_LAYER_VSD0       3
#define HI3531D_VO_LAYER_VIRT0      4

#define HI3531D_GRAPH_LAYER_G0      0
#define HI3531D_GRAPH_LAYER_G1      1
#define HI3531D_GRAPH_LAYER_G2      2
#define HI3531D_GRAPH_LAYER_HC0     3
#define HI3531D_GRAPH_LAYER_HC1     4

#define VO_LAYER_PIP                     2
#define VO_LAYER_PIP_STA                 2
#define VO_LAYER_PIP_END                 2
#define VO_DEV_HD_END                    2

#define HI3531D_VO_WBC_BASE              0
#define HI3531D_VO_LAYER_PRIORITY_BASE   0
#define HI3531D_VO_LAYER_PRIORITY_PIP    1
//#define GRAPHICS_LAYER_HC0 3

#define HI3531D_AUDIO_PTNUMPERFRM        320
#define HI3531D_AUDIO_TLV320_AI_DEV      2
#define HI3531D_AUDIO_TLV320_AO_DEV      0

#define HI3531D_AUDIO_INNER_HDMI_AO_DEV  2
#define HI3531D_AUDIO_HDMI_AO_DEV        1
#define HI3531D_AUDIO_AI_DEV             AI_DEV
#define HI3531D_AUDIO_AO_DEV             AO_DEV
#else
#define HI3531D_VO_DEV_DSD1         3
#define HI3531D_VO_DEV_DSD2         4
#define HI3531D_VO_DEV_DSD3         5
#endif

#define HI3531D_FHD_WIDTH           1920
#define HI3531D_FHD_HEIGHT          1080

#define HI3531D_AO_DEV			2
#define HI3531D_AI_DEV			1

#define HI3531D_HDMI_AO_DEV      3

#define HI3531D_AUDIO_LOCAL_DEV	0
#define HI3531D_AUDIO_HDMI_DEV	1

#define HI3531D_VPSS_DEV0		0
#define HI3531D_VPSS_DEV1		1
#define HI3531D_VPSS_DEV2		2

/*** for init global parameter ***/
#define HI3531D_ENABLE 		    1
#define HI3531D_DISABLE 		    0
#define HI3531D_NOUSE 		    -1

#define HI_LIVE_MODE			0
#define HI_PLAYBACK_MODE		1
#define HI_QUICKSEARCH_MODE	2

#define GET_RESIZE_1280_SD(x)		((x*100)/180)
#define GET_RESIZE_1280_960(x)		((x*3)/4)

#define GET_RESIZENTSC_720_SD(y)	(y*2/3)
#define GET_RESIZEPAL_720_SD(y)		((y*8)/10)

#define GET_RESIZE_SD(x)			((x*100)/273)
#define GET_RESIZE_960(x)			((x)/2)

#define GET_RESIZENTSC_SD(x)		((x*100)/225)
#define GET_RESIZEPAL_SD(x)			((x*100)/188)

#define GET_RESIZE_720_HD(x)	((x*3)/2)
#define GET_RESIZE_1080_HD(x)	((x/3)*2)

#define DBG_PRINT(fmt...)   \
    do {\
        printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
        printf(fmt);\
       }while(0)

#define IS_ERR(rv)		(HI_SUCCESS != rv)
/******************************************************/
/*	Old stuffs										  */
/******************************************************/
typedef enum {
	VI_MODE_P720,
	VI_MODE_P720_HALF,
	VI_MODE_1080,
	VI_MODE_1080_HALF,
	VI_MODE_D1,
} VI_MODE_E;

typedef enum {
    VO_DEV_HD  = 0,                 /* high definition device */
    VO_DEV_AD  = 1,                 /* assistant device */
    VO_DEV_SD  = 2,                 /* spot device */
    VO_DEV_MAX
} VO_DEV_E;

typedef enum {
	HIDEV_VI_CHN = 0,
	HIDEV_VO_CHN_HD,
	HIDEV_VO_CHN_AD,
	HIDEV_VO_CHN_SD,
	HIDEV_VE_CHN,
	HIDEV_VD_CHN,
	HIDEV_AI_CHN,
	HIDEV_AO_CHN,
	HIDEV_AE_CHN,
	HIDEV_AD_CHN,
	HIDEV_MAX
} HIDEV_INDEX_E;

typedef enum {
    PIC_EA_QCIF = 0,                        /* 0 */
    PIC_EA_CIF,
    PIC_EA_2CIF,
    PIC_EA_HD1,
    PIC_EA_D1,
    PIC_EA_QVGA,    /*  320 * 240  */      /* 5 */
    PIC_EA_VGA,     /*  640 * 480  */
    PIC_EA_XGA,     /* 1024 * 768  */
    PIC_EA_SXGA,    /* 1400 * 1050 */
    PIC_EA_UXGA,    /* 1600 * 1200 */
    PIC_EA_QXGA,    /* 2048 * 1536 */      /* 10 */
    PIC_EA_WVGA,    /*  854 * 480  */
    PIC_EA_WSXGA,   /* 1680 * 1050 */
    PIC_EA_WUXGA,   /* 1920 * 1200 */
    PIC_EA_WQXGA,   /* 2560 * 1600 */
    PIC_EA_HD720,   /* 1280 * 720  */      /* 15 */
    PIC_EA_HD1080,  /* 1920 * 1080 */
    PIC_MAX,
} PIC_SIZE_EA;

typedef enum {
    VO_EA_OUTPUT_PAL           = 0,		/* 0 */
    VO_EA_OUTPUT_NTSC          = 1,
    VO_EA_OUTPUT_720P60        = 2,
    VO_EA_OUTPUT_1080I50       = 3,
    VO_EA_OUTPUT_1080I60       = 4,
    VO_EA_OUTPUT_1080P25       = 5,		/* 5 */
    VO_EA_OUTPUT_1080P30       = 6,
    VO_EA_OUTPUT_800x600_60    = 7,
    VO_EA_OUTPUT_1024x768_60   = 8,
    VO_EA_OUTPUT_1280x1024_60  = 9,
    VO_EA_OUTPUT_1366x768_60   = 10,	/* 10 */
    VO_EA_OUTPUT_1440x900_60   = 11,
    VO_EA_OUTPUT_USER          = 12,
    VO_EA_OUTPUT_MAX
} VO_INTF_SYNC_EA;

enum {
	HI_EN_RESOLUTION_D1 = 0,
	HI_EN_RESOLUTION_CIF,
	HI_EN_RESOLUTION_QCIF
};

enum {
	HI_EN_ATTR_TARGET_FRAMRATE,
	HI_EN_ATTR_GOP,
	HI_EN_ATTR_BITRATE,
	HI_EN_ATTR_ENMODE, /*0-VBR, 1-CBR, 2-ABR, 3-FIXQP */
	HI_EN_ATTR_RESOLUTION,
	HI_EN_ATTR_QUALITY,
	HI_EN_ATTR_MAX,
};

enum {
	CHIP_MA = 1,
	CHIP_S1 = 2,
	CHIP_S2 = 3,
	CHIP_S3 = 4,
	CHIP_S4 = 5,
	CHIP_EA = 6,
};

enum {
	HD_MA_VO_CH_NUM = 3,
	HD_S1_VO_CH_NUM	= 0,
	HD_S2_VO_CH_NUM	= 1,
	HD_S3_VO_CH_NUM	= 2,
};

enum {
	HD_VO_LIVE_BIND = 0,
	HD_VO_DEC_BIND  = 1,
};

enum {
	HD_VO_SCREEN_QUAD = 0,
	HD_VO_SCREEN_FULL = 1,
};

#define SD_VO_LIVE_BIND	0
#define SD_VO_DEC_BIND  1

// Encoder Attribute
#define VIDEO_FULL_WIDTH	640
#define VIDEO_HALF_WIDTH	320
#define VIDEO_LOW_WIDTH	160
#define VIDEO_QUAD_WIDTH	(VIDEO_FULL_WIDTH/4)
#define VIDEO_FULL_HEIGHT	480
#define VIDEO_HALF_HEIGHT	240
#define VIDEO_LOW_HEIGHT	120
#define VIDEO_QUAD_HEIGHT	(VIDEO_FULL_HEIGHT/4)

// Audio
#define AUDIO_ADPCM_TYPE	ADPCM_TYPE_DVI4	/* ADPCM_TYPE_IMA, ADPCM_TYPE_DVI4*/
#define AUDIO_AAC_TYPE		AAC_TYPE_AACLC		/* AAC_TYPE_AACLC, AAC_TYPE_EAAC, AAC_TYPE_EAACPLUS*/
#define G726_BPS			MEDIA_G726_16K		/* MEDIA_G726_16K, MEDIA_G726_24K ... */
#define AMR_FORMAT			AMR_FORMAT_MMS	/* AMR_FORMAT_MMS, AMR_FORMAT_IF1, AMR_FORMAT_IF2*/
#define AMR_MODE			AMR_MODE_MR74		/* AMR_MODE_MR122, AMR_MODE_MR102 ... */
#define AMR_DTX				0

#define MAX_VIDEO	16
#define MAX_VDEC	16
#define VDEC_INSTANCE_MAX	(MAX_VDEC)
#define VDEC_INSTANCE_PANORAMA	VDEC_INSTANCE_MAX+1
/******************************************************/
/*	Old stuffs										  */
/******************************************************/
/*******************************************************
    enum define 
*******************************************************/
typedef enum {
	BOARD_SD 	 = 0,
	BOARD_960H 	 = 1,
	BOARD_HD 	 = 2,
	BOARD_IP 	 = 3,
	BOARD_HYBRID = 4,
	BOARD_HD_MULTI = 5,
	BOARD_AHD720 = 6,
} HI3531D_BOARD_TYPE;

typedef enum sample_vi_mode_e
{
    HI3531D_VI_MODE_1_D1 = 0,
    HI3531D_VI_MODE_4_D1,
    HI3531D_VI_MODE_8_D1,
    HI3531D_VI_MODE_16_D1,
    HI3531D_VI_MODE_4_960H,
    HI3531D_VI_MODE_8_960H,
    HI3531D_VI_MODE_16_960H,
    HI3531D_VI_MODE_4_720P,
    HI3531D_VI_MODE_4_1080P,
    HI3531D_VI_MODE_4_1080I,
    HI3531D_VI_MODE_8_720P,
    HI3531D_VI_MODE_8_1080P,
    HI3531D_VI_MODE_8_1080I, 
    HI3531D_VI_MODE_AHD720,
    HI3531D_VI_MODE_960H_2MUX
}HI3531D_VI_MODE_E;


typedef enum 
{
    VI_DEV_BT656_D1_1MUX = 0,
    VI_DEV_BT656_D1_4MUX,
    VI_DEV_BT656_960H_1MUX,
    VI_DEV_BT656_960H_4MUX,
    VI_DEV_720P_HD_1MUX,
    VI_DEV_1080P_HD_1MUX,
    VI_DEV_BUTT
}HI3531D_VI_DEV_TYPE_E;

typedef enum sample_vi_chn_set_e
{
    VI_CHN_SET_NORMAL = 0, /* mirror, flip close */
    VI_CHN_SET_MIRROR,				// 16D1 is 0,2,4,6ROR,      /* open mirror */
    VI_CHN_SET_FLIP,		/* open flip */
    VI_CHN_SET_FLIP_MIRROR,		/*open mirror open flip */
    VI_CHN_SET_CROP
}HI3531D_VI_CHN_SET_E;

typedef enum sample_vo_mode_e
{
    VO_MODE_1MUX  = 0,
    VO_MODE_4MUX = 1,
    VO_MODE_8MUX = 2,
    VO_MODE_9MUX = 3,
    VO_MODE_16MUX = 4,
    VO_MODE_1_7MUX = 17,
    VO_MODE_BUTT
}HI3531D_VO_MODE_E;

typedef enum sample_rc_e
{
    HI3531D_RC_CBR = 0,
    HI3531D_RC_VBR,
    HI3531D_RC_AVBR,
    HI3531D_RC_FIXQP
}HI3531D_RC_E;

typedef enum sample_rgn_change_type_e
{
    RGN_CHANGE_TYPE_FGALPHA = 0,
    RGN_CHANGE_TYPE_BGALPHA,
    RGN_CHANGE_TYPE_LAYER
}HI3531D_RGN_CHANGE_TYPE_EN;

typedef enum sample_bind_info_e
{
    HI3531D_BIND_NONE= 0, 
	HI3531D_BIND_VPSS_CL0 = 0, 
	HI3531D_BIND_VPSS_CL1 
}HI3531D_BIND_INFO_E; 
/******************************************************** 
  structure define 
 *******************************************************/ 
typedef struct sample_vi_param_s 
{ 
	HI_S32 s32ViDevCnt;			// VI Dev Total Count 
	HI_S32 s32ViDevInterval;	// Vi Dev Interval 
	HI_S32 s32ViChnCnt;			// Vi Chn Total Count 
	HI_S32 s32ViChnInterval;	// VI Chn Interval 
}HI3531D_VI_PARAM_S; 
typedef struct sample_vo_param_s
{
    VO_DEV VoDev;
    HI_CHAR acMmzName[20];
    HI_U32 u32WndNum;
    HI3531D_VO_MODE_E enVoMode;
    VO_PUB_ATTR_S stVoPubAttr;
    HI_BOOL bVpssBind;
}HI3531D_VO_PARAM_S;

typedef struct sample_video_loss_s
{
    HI_BOOL bStart;
    pthread_t Pid;
    HI3531D_VI_MODE_E enViMode;
} HI3531D_VIDEO_LOSS_S;


typedef struct sample_venc_getstream_s
{
     HI_BOOL bThreadStart;
     HI_S32  s32Cnt;
}HI3531D_VENC_GETSTREAM_PARA_S;

//////////////////////////////////////////
// Eastern defined
//////////////////////////////////////////
typedef enum enc_cmd_e
{
    HI3531D_CFG_CMD_FR=0, 
    HI3531D_CFG_CMD_GOP, 
    HI3531D_CFG_CMD_BPS, 
    HI3531D_CFG_CMD_RC, 
    HI3531D_CFG_CMD_RESOL, 
    HI3531D_CFG_CMD_QT,
    HI3531D_CFG_CMD_ENCTYPE
} ENC_CFG_CMD_E; 
struct _stEncCfg {
	int ch;
	int fr;
	int gop;
	int bps;
	int rc;			// rate control(CBR,VBR,etc)
	int resol;
	int qt;
	int type;

	int req_start;

	ENC_CFG_CMD_E	cmd;
};
typedef struct _stEncCfg EncCfg;

typedef struct
{
	VPSS_GRP_ATTR_S	group;
	VPSS_CHN_ATTR_S aChannel[5];
	int 			enChannel[5];
} HiDevVpssAttr;
typedef struct 
{
	int				alignByte;
} HiDevSys; 
typedef struct 
{
	VIDEO_NORM_E	vis;					// get from input signal 
	char 			*decoderName;			// "TP2827"
	int				xDev;
	int				xCh;					
	int				width;					// 720
	int				height;					// NTSC(480), PAL(576)
	int				nFrameRate;
	int				loss;					// video loss
	HI3531D_VI_CHN_SET_E				attr;					// attr
    ROTATE_E        rotate;
	// Video cascade features
	int cascade_device_channel;			// Host(2), Slaves(None)
} HiDevVi; 
typedef struct 
{
	int				nFrameRate;				// 30
	int				nChannel;				// 16
	int				width;					// 720
	int				height;					// 480(576)

	int				vpssSubChannel;			// VPSS_PRE0_CHN(HDMI)/VPSS_PRE1_CHN(VGA)/VPSS_BYPASS_CHN(SD0)
											// xDevVo0 -> VPSS_PRE0_CHN
											// xDevVo1 -> VPSS_PRE1_CHN
											// xDevVo2 -> VPSS_BYPASS_CHN or WBC

	HI3531D_VO_MODE_E split;					// Default VO_MODE_16MUX 
	HI3531D_VO_MODE_E splitRequested;		//  
	int				splitStart;				// Default CH0
	int				splitStartRequested;	// 

	int				enableVoZoom;			//ZOOM ENABLE
	int 			enableVoRatio;			//ZOOM RATIO

	int				CovertChn;				// LIVE OR PLAYBACK COVERT CHANNEL
	int				lossChannelBit;			// VIDEO LOSS CHANNEL BIT MASK
	int				channelShowStatusBit;
	int				playbackpause;			//PLAYBACK PAUSE STATE

		// Video cascade features
		int				cascade_device;
		int				cascade_slave;		// Host(None)
		int				cascade_pattern;	
	
	VO_INTF_TYPE_E	intf;					// VO_INTF_HDMI
	VO_INTF_SYNC_E	sync;					// VO_OUTPUT_1080P60
	VO_PUB_ATTR_S	attr;
		VO_ZOOM_ATTR_S	zoomAttr;
		VO_CAS_ATTR_S	casAttr;
	VO_WBC_ATTR_S 	wbcAttr;
	VO_CSC_S 		csc;
	VO_CSC_S 		sdCsc;
	VO_CSC_S 		sd2Csc;
	VO_VGA_PARAM_S 	vgaCsc;
} HiDevVo; 
typedef struct 
{
	int				nGroup;					// pHiDev->nInputTotal
	int				nSubChannel;			// 4 
	int				offsetGroup;			// block0 is always 0, block1 depends on channel mode(16D1,8D1).
											// block1 is 8 or 16. 8D1 -> 8 16D1 -> 16
	int				pipChannel;
	HiDevVpssAttr	aAttr[16];
} HiDevVpss; 
typedef struct 
{
	int				fd;
	int				channel;				// 0(Major) or 16(Minor)
	PAYLOAD_TYPE_E	payload;	
	PIC_SIZE_E		pictureSize;
	HI3531D_RC_E		rateControl;        	// HI3531D_RC_CBR/VBR
	int				bitrate;
	int				frameRate;
	int				vi_frameRate;
	int				gop;
	int				quality;				// for VBR(Qp level)
#if 1 // GyverJeong [19/08/12]
	int				VpssChn;                // for VPSS SCALE
#else
	int				vpsschannel;			// for VPSS SCALE
#endif

    VENC_CHN_ATTR_S 		channelAttr;
} HiDevVenc; 
typedef struct 
{
	int				nChannel;
	int				width;
	int				height;
	PAYLOAD_TYPE_E	payload;
} HiDevVdec; 
typedef struct 
{
	int				xAiDev;
	int				nChannel;
	int				nFrame;
	int				aFd[16];
	AIO_ATTR_S 		stAioAttr;
} HiDevAi; 
typedef struct 
{
	int				xAoDev;
	int				nChannel;
	int				nFrame;
	int				output_channel;
	AIO_ATTR_S 		stAioAttr;
} HiDevAo; 
typedef struct 
{
	int				xCh;
	SIZE_S			picture_t;
} HiDevVda; 

struct _HiDev 
{
	int 				model;
		int 				chip_id;
		int 				is_cas_master;			// Who feeds video clock(id:0(8CH) or id:2(16CH))
		int					base_channel;			// ∞¢ chip¿« base channel number
	HI3531D_BOARD_TYPE	boardType;
	int					isException;				// 1(disk format mode), 0(normal)
	int					nInputTotal;				// 16
	int					nVideoTotal;				// 16
	int 				nAudioTotal;				// 4(????)
	int					isPlayback;					// 0(Host), others is not implemented yet.
	VIDEO_NORM_E		vis;						// configured from app
	int		        aVisChannel[HI_MAX_VI_CH];	// get form vi module
	PIC_SIZE_E			aPicSize[HI_MAX_VI_CH];
	int					nViDevTotal;				// 16D1 is 4, 8D1 is 2
	int					nVoDevTotal;				// 8
	int					nVencMajor;					// Major 16ch 
	int					nVencMinor;					// Minor 16ch 
	int					nVdecDevTotal;				// 16 
	int					nVpssBlockTotal;			// max three blocks
	int					xVoDev;						// global vo device number

	PIXEL_FORMAT_E		pixelFormat;
	HI3531D_VI_MODE_E	aViWorkMode[HI_MAX_VI_CH];
	VO_INTF_SYNC_E		voOutputMode;				// VO_OUTPUT_1080P60 ....
	int					voWidth;					// 1920/1280
	int					voHeight;					// 1080/1024/720
	int					mainDisplay;				// 0:HDMI, 1:VGA
	int					isDualDisplay;				// USE VGA SPOT
	int					spotDev;
	int					enableSpot;
	int					enableWbc;					//WBC ENABLE or DISABLE
	int					enPipDevice;				//PIP DEVICE ENABLE or DISABLE
	int 				aChnnelToViDevice[16];
	int					isInstantPbDisplay;			//Instant Playback State..
	int					instantPbchannel;
	unsigned char		MotionSearchMap[22*15];
	int					MotionSearchSensitivity;
	int					splitSeqReq[4];
	int					splitSeq[4];
	HiDevSys	sys;
	HiDevVi		vi[16];								// 16ch
		// Video cascade input device
		HiDevVi		cas_vi[1];							// Only host, slaves isn't required.
	HiDevVo		vo[8];								// HD0/1, SD0/1/2/3/4/5
	HiDevVpss	vpss[3];							// two blocks, one(live+encode), the other(playback)
	HiDevVenc	venc_a[16];							// major 16ch 
	HiDevVenc	venc_b[16];							// minor 16ch 
	HiDevVdec	vdec[17];							// 16ch 
	HiDevAi		ai;									// SIO4(LOCAL)
	HiDevAo		ao[2];								// SIO4(LOCAL), SIO5(HDMI)
	HiDevVda	vda[16];
};

typedef struct _HiDev HiDev;

typedef struct hiDevPb_context_s {
	HI_S32 initialize;
	HI_S32 run;
	HI_S32 video;
	HI_S32 vpssOffset;
	HI_S32 displayMask;
	HI_S32 pausedisplay;
	HI_S32 enPipDevice;
	HI_S32 zoom_enable;
	HI_S32 zoom_channel;
	HI_S32 zoom_width[16];
	HI_S32 zoom_height[16];
	HI_S32 isAllplayback;
	HI_S32 instantPbchannel;
	HI_S32 instantPbenable;
	VIDEO_FRAME_INFO_S stVdecData[16];
	pthread_t tid;
} hiDevPb_context_t;


//Special Split def
typedef struct {
	int 	nSplit;
	int 	xTotal;
	int 	yTotal;
	int 	ax[16];
	int 	ay[16];
	int 	aWidth[16];
	int 	aHeight[16];
} EaSpecialSplit;

// Eastern SYS
HI_S32 hiSysInit(HiDev *pHiDev, VB_CONF_S *pstVbConf);
HI_S32 hiMppConfig(HiDev *pHiDev);

// Eastern VI
HI_S32 hiViStart(HiDev *pHiDev);
HI_S32 hiViDestroy(HiDev *pHiDev);
HI_S32 hiViBindVpss(HiDev *pHiDev, int xBlock);
HI_S32 hiViUnBindVpss(HiDev *pHiDev, int xBlock);
HI_S32 hiViMemConfig(HiDev *pHiDev);
HI_S32 hiVideoInChange(HiDev *pHiDev, HI3531D_VI_MODE_E preViMode, HI_U32 vis, HI3531D_VI_MODE_E curViMode, HI_U32 channel);
HI_S32 hiViBindVpssEach(HiDev *pHiDev, int xBlock, int channel);
HI_S32 hiViUnBindVpssEach(HiDev *pHiDev, int xBlock, int channel);
#if 1 // GyverJeong [19/10/10]
ROTATE_E *hiViGetRotate(void);
#endif

// Eastern VDEC
HI_S32 hiVdecConfig(HiDev *pHiDev);
HI_S32 hiVdecMemConfig(HiDev *pHiDev);
HI_S32 hiVdecStart(HiDev *pHiDev);
HI_S32 hiVdecBindVpss(HiDev *pHiDev, int xVpssBlock);
HI_S32 hiVdecUnBindVpss(HiDev *pHiDev, int xVpssBlock);
HI_S32 hiVdecPause(int channel);
HI_S32 hiVdecBindVpssWait(int offsetGroup, int ch, int wait);
HI_S32 hiVdecRestart(HiDev *pHiDev);
HI_S32 hiVdecSendStream(HI_U32 channel, HI_U32 bytes, HI_U8 *pBuffer, HI_U32 block);
HI_S32 hiVdecStartEach(HiDev *pHiDev, int ch);
HI_S32 hiVdecStopEach(HiDev *pHiDev, int ch);
HI_S32 hiVdecRestartChannel(HiDev *pHiDev, int channel);

// Eastern VO
HI_S32 hiVoConfig(HiDev *pHiDev, int xVoDev, int simultaneous);
HI_S32 hiVoStart(HiDev *pHiDev, int xVoDev);
HI_S32 hiVoDestroy(HiDev *pHiDev, int xVoDev);
HI_S32 hiVoBindVpss(HiDev *pHiDev, int xVoDev, int xVpssBlock);
HI_S32 hiVoBindWbc(HiDev *pHiDev, int xVoDev);
HI_S32 hiVoUnBindVpss(HiDev *pHiDev, int xVoDev, int xVpssBlock);
HI_S32 hiVoMemConfig(HiDev *pHiDev);
HI_S32 hiVoSplit(HiDev *pHiDev, int xVoDev);
HI_S32 hiVoSpotSplit(HiDev *pHiDev, int xVoDev, int enable);
HI_S32 hiVoDisplayMode(HiDev *pHiDev, HI_S32 isPlayback);
HI_S32 hiVoUnBindWbc(HiDev *pHiDev, int xVoDev);
HI_S32 hiSrcBindVpssEach(HiDev *pHiDev, int xBlock, int channel, int mode);
HI_S32 hiSrcUnBindVpssEach(HiDev *pHiDev, int xBlock, int mode);
HI_S32 hiVoZoom(HiDev *pHiDev, int ch, int x, int y, int width, int height);
HI_S32 hiVoSetRatio(HiDev *pHiDev, int enable);
HI_S32 hiVoSetFreeze(HiDev *pHiDev, int onOff);
HI_S32 hiVoSetCSC(int xVoDev,VO_CSC_S *pstVoCSC);
HI_S32 hiVoGetCSC(int xVoDev,VO_CSC_S *pstVoCSC);
HI_S32 hiVoSetVgaCSC(int xVoDev,VO_VGA_PARAM_S *pstVoVgaCSC);
HI_S32 hiVoGetVgaCSC(int xVoDev,VO_VGA_PARAM_S *pstVoVgaCSC);
HI_S32 hiVoSetCovert(HiDev *pHiDev, int ch);
HI_S32 hiVoZoomResize(HiDev * pHiDev, RECT_S * stSrcRect, RECT_S * stDstRect);
HI_S32 hiVoSetZoom(HiDev *pHiDev, int x, int y, int width, int height);
HI_S32 hiVoQuickSearchStart(HiDev *pHiDev, int xVoDev);
HI_S32 hiVoShowChannel(HiDev *pHiDev);
HI_S32 hiVoWbcForceMode(HiDev *pHiDev, int xVoDev, int enable);
HI_S32 hiVoSetDisplayChannel(HiDev *pHiDev, int start, int split);
HI_S32 hiVoBufferClear(int xVoDev, int channel);
HI_S32 hiVoSetForceSendVideo(int enable);
HI_S32 hiCvbsSetPosition(HiDev *pHiDev, int x, int y, int w, int h);

// Eastern VENC
HI_S32 hiVencStart(HiDev *pHiDev, HI_S32 channel);
HI_S32 hiVencCreate(HiDev *pHiDev, HI_S32 channel);
HI_S32 hiVencDestroy(HiDev *pHiDev, HI_S32 channel);
HI_S32 hiVencConfig(int cmd, HiDev *pHiDev, HiDevVenc *pVenc);
HI_S32 hiVencMemConfig(HiDev *pHiDev);
HI_S32 hiVencStartReceivePicture(HiDev *pHiDev, int channel, int bStart);

// Eastern VPSS
HI_S32 hiVpssMemConfig(HiDev *pHiDev, int xBlock);
HI_S32 hiVpssConfig(HiDev *pHiDev, int xBlock);
HI_S32 hiVpssStart(HiDev *pHiDev, int xBlock);
HI_S32 hiVpssRestart(HiDev *pHiDev, int xBlock);
HI_S32 hiVpssDestroy(HiDev *pHiDev, int xBlock);
HI_S32 hiVpssSetAttr(HiDev *pHiDev, int xBlock, int channel);
HI_S32 hiVpssSetCrop(HiDev *pHiDev, int xBlock, int enable);
HI_S32 hiVpssSetCropChannel(HiDev *pHiDev, int xBlock, int enable, int channel);

HI_S32 hiVpssDisablePreScale(HiDev *pHiDev, int xBlock, int group, PIC_SIZE_E picSize);
HI_S32 hiVpssEnablePreScale(HiDev *pHiDev, int xBlock, int group, PIC_SIZE_E picSize);

//Eastern REGION
HI_S32 hiRegionMemConfig(HiDev *pHiDev);
HI_S32 hiRegionStart(HiDev *pHiDev);
HI_S32 hiRegionSet(HiDev *pHiDev, int channel, int layer, int x, int y, int width, int height);
HI_S32 hiRegionClear(HiDev *pHiDev, int channel, int layer);

// Eastern AUDIO
HI_S32 hiAudioInStart(HiDev *pHiDev);
HI_S32 hiAudioOutStart(HiDev *pHiDev, int xAoDev);
HI_S32 hiAudioInGetStream(HiDev *pHiDev, int channel, AUDIO_FRAME_S *pAudioStream);
HI_S32 hiAudioPutStream(HiDev *pHiDev, int xAoDev, AUDIO_FRAME_S *pAudioStream);

// FB
HI_S32 hiFbSetConfig(HiDev *pHiDev);
HI_S32 hiFbCloseCircleImage(void);

HI_S32 hiFbSetAlpha(int Alpha);
// VDA
HI_S32 hiStartVda(HiDev *pHiDev);
HI_S32 hiStartVdaRecvPic(HiDev *pHiDev);
HI_S32 hiStartVdaChannel(HiDev *pHiDev, HI_S32 channel, HI_S32 width, HI_S32 height);
HI_S32 hiStopVdaChannel(HiDev *pHiDev, HI_S32 channel);
HI_S32 hiSetAttrVdaChannel(HiDev *pHiDev, HI_S32 channel, HI_S32 width, HI_S32 height);

int hiBoardInitialize(int *pX, int *pY, int *pVis, HI3531D_BOARD_TYPE type);
int hiBoardStart(void);
int hiBoardSplit(int start, int split);
int hiBoardSplitSlave(int start, int split);
int hiBoardVoCovert(int ch);
int hiBoardVoChannelLoss(int channelBit);
int hiBoardVoZoom(int x, int y, int width, int height);
int hiBoardDisplayMode(int isPlayback);
int hiBoardVdecRestart(void);
int hiBoardVdecRestartChannel(int channel);
int hiBoardVdecGetBufferSize(void);
int hiBoardVencCreate(int channel);
int hiBoardVencDestroy(int channel);
int hiBoardVencStart(int channel, int bStart);
int hiBoardVencConfig(int channel, EncCfg *pCfg);
int hiBoardVoRatio(int enable);

int hiBoardAioStart(void);


int hiBoardQuickSearchStart(void);
int hiBoardQuickSearch(unsigned char *payload, int len, int pos);
int hiBoardVoFreeze(int onOff);
int hiBoardVoRatio(int enable);
int hiBoardRegionSet(int channel, int layer, int x, int y, int width, int height);
int hiBoardRegionClear(int channel, int layer);
int hiBoardJpegSnap(int screen, int channel, int width, int height, int quality, unsigned char **data, int *size);
int hiBoardVdaStart(void);
int hiBoard_pip_display(int channel, int x, int y, int width, int height, int enable);  
void hiBoardVoClear(int channel);
int hiBoardChannelMode(int ch, int enable, int mode);

int hiBoardCvbsSetPosition(int x, int y, int w, int h);
int hiBoardViSetFlip_Mirror(void);

int hiBoardMotionCheck(void);
int hiBoardSetMotionSearchConfig(unsigned char *motionCfg, int sensitivity);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __HI3531D_H__ */
