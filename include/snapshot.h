#ifndef	__SNAPSHOT_H__
#define	__SNAPSHOT_H__

#ifdef __cplusplus
extern "C"{
#endif

#define	EA_SNAPSHOT_PORT			50010
#define	EA_SNAPSHOT_WIDTH			352
#define	EA_SNAPSHOT_HEIGHT			240
#define	EA_SNAPSHOT_QUALITY			0

#define	EA_SNAPSHOT_CHANNEL_ALL		90
#define	EA_SNAPSHOT_CHANNEL_OSD		91

#define	EA_SNAPSHOT_MAGIC			0x6573746e
#define	EA_SNAPSHOT_MSG_START		1
#define	EA_SNAPSHOT_MSG_DONE		2
#define	EA_SNAPSHOT_MSG_ERROR		3

typedef struct
{
	unsigned long	magic;
	unsigned long	channel;
	unsigned long	width;
	unsigned long	height;	
	unsigned long	quality;
	unsigned long	message;

} ea_snapshot_t;

#ifdef __cplusplus
}
#endif

#endif
