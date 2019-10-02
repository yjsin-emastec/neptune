#ifndef __EA_BACKUP_H__
#define __EA_BACKUP_H__

#define EABACKUP_DAYLINE_BUFFER_SIZE	(750) //(25*240/8)

typedef struct {
	int channel;
	int flagCheck;
	unsigned long startTime;
	unsigned long endTime;
} EaBackupSetup;

typedef struct {
	int channel;
	int eos;
	unsigned int marker1nal5miliSecond10;
	long long pts;
	unsigned long second;
	unsigned long milisecond;
	int type;
	int bytes;
	int bytesMaximum;
	int offsetVideo;
	int offsetAudio;
	unsigned char *pMediaBuffer;
} EaBackupMedia;

typedef struct {
	int year;
	int month;
	int nChannel;
	int dls;
	unsigned long dlsBegin;
	unsigned long dlsEnd; 
	unsigned long dayBits; // NOTE: need swap(endian mode)
} EaBackupCalendar;

typedef struct {
	int year;
	int month;
	int day;
	int channel;
	int dls;
	unsigned long dlsBegin;
	unsigned long dlsEnd; 
	unsigned char pBuffer[EABACKUP_DAYLINE_BUFFER_SIZE]; // NOTE: need swap(endian mode);
	int bytesBuffer;
} EaBackupDayline;

typedef struct {
	int year;
	int month;
	int day;
	int type;
	int dls;
	int count;
	int offset;
	unsigned long dlsBegin;
	unsigned long dlsEnd; 
	unsigned char pBuffer[512*1024];
	int bytesBuffer;
	int total_count;
	int logcount;
	int logoffset;
} EaBackupEventLog;

unsigned long eaBackupOpen(void);
int eaBackupClose(unsigned long instance);
int eaBackupSetup(unsigned long instance, EaBackupSetup *pSetup);
int eaBackupNextMedia(unsigned long instance, EaBackupMedia *pMedia);
int eaBackupGetCalendar(EaBackupCalendar *pCalendar, int type);
int eaBackupGetDayline(EaBackupDayline *pDayline);
void eaBackupGetEventLog(EaBackupEventLog *pEventLog);

#endif
