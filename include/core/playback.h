
#ifndef __PLAYBACK_H__
#define __PLAYBACK_H__

#include <time.h>
#include <sys/time.h>

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------

typedef enum {
	pb_pause = 0,
	pb_x1    = 1,
	pb_x2    = 2,
	pb_x4    = 4,
	pb_x8    = 8,
	pb_x16   = 16,
	pb_x32   = 32,
	pb_x64   = 64,
	pb_x0_5  = -1,
	pb_x0_25 = -2
} pb_speed_e;

typedef enum {
	pb_rew = 0,
	pb_ff	
} pb_direction_e;

typedef struct pb_property_s {
	int speed;
	int direction;
} pb_property_t, *ppb_property_t;

typedef struct pb_callback_s {
	int sessionId;
	int channel;
	int type;			// 0: pbtime, 1: video, 2: audio, 3: video exit
	int   sizStream;
	void *bufStream;
	int markerAnd;
	void *pWork; 		// for remote playback
	struct timeval *pts;
	int slice;
	time_t pbtime;
} pb_callback_info_t, *ppb_callback_info_t;

typedef int (*pplaybackCallbackFunction_t)(pb_callback_info_t *pCallbackInfo);

typedef enum {
	pb_callback_vdec_start_recv_stream,
	pb_callback_vdec_stop_recv_stream
} pb_callback_e;

typedef int (*pplaybackCallbackFunctionVdecStartRecvStream_t)(int VdChn);
typedef int (*pplaybackCallbackFunctionVdecStopRecvStream_t )(int VdChn);

//----------------------------------------------------------------------------
// External function prototypes:
//----------------------------------------------------------------------------

int pb_init(void);
int pb_deinit(void);
int pb_create_session(int backup, int remote, int video, time_t req_time, time_t end, void *callback, void *pWork);
int pb_delete_session(int session_id);
int pb_set_property(int session_id, pb_property_t  property);
int pb_get_property(int session_id, pb_property_t *property);
int pb_start(int session_id);
int pb_stop(int session_id);
int pb_step(int session_id);
int pb_jump(int session_id, int jmp_level, int direction);
int pb_settime(int session_id, time_t req_time);
int pb_reg_callback(pb_callback_e type, void *callback);

#endif

