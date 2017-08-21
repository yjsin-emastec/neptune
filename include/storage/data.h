#ifndef _DATA_H_
#define	_DATA_H_

#define	HDD_MAXIMUM 10	

typedef struct {
    unsigned char    magic        [ 4]; // 'e' 's' 't' 'n'
    unsigned char    version      [ 4]; // digit(zero padding)
    unsigned char    kind         [ 1]; // digit : '0'(active) / '1'(backup)
    unsigned char    inform1      [ 1]; // unused
    unsigned char    inform2      [ 1]; // unused
    unsigned char    inform3      [ 1]; // unused
    unsigned char    inform4      [ 1]; // unused
    unsigned char    nextHDD      [ 1]; // unused
    unsigned char    lastHDD      [ 1]; // unused
    unsigned char    isMaster     [ 1]; // unused : digit : '1'(master) / '0'(others)
    unsigned char    fromHour     [ 8]; // digit(YYMMDDhh)
    unsigned char    toHour       [ 8]; // digit(YYMMDDhh)
    unsigned char    makeTime     [12]; // digit(YYMMDDhhmmss)
    unsigned char    reserve      [84]; //
    unsigned char    reserve1     [ 4]; //
    unsigned char    hStart       [ 8]; // lastHourStart
    unsigned char    hEnd         [ 8]; // lastHourEnd
    unsigned char    saveStart    [ 8]; // saveHourStart
    unsigned char    saveEnd      [ 8]; // saveHourEnd
    unsigned char    reserve2     [48]; //
} DataDiskHeader;

typedef struct {
    char serial[32][128];
} DataSerial;

#define DATA_PRE_RECORD_MAXIMUM_MINUTE    24
#define DATA_PLAYBACK_UNIT_SECOND         15
#define DATA_UNIT_HOUR                    24
#define DATA_LAST_HOUR                    23
#define DATA_MAXIMUM_YEAR                 50
#define DATA_CHANNEL_MAXIMUM              40
#define DATA_CHANNEL_EVENT                16
#define DATA_CHANNEL_TOTAL                144
#define DATA_CHANNEL_SELF                 43
#define DATA_INDEX_SELF                   3
#define DATA_LENGTH_SELF                  64
#define DATA_CHANNEL_SYSLOG               40
#define DATA_CHANNEL_EVENTLOG             41
#define DATA_CHANNEL_ARCHIVE              42

// Y[0..DATA_MAXIMUM_YEAR-1] = year%DATA_MAXIMUM_YEAR, M[0..11], D[0..31], h[0..24], m[0..59], s[0..59], z[0..999] = miliSecond
typedef int DataTimeYMD;
typedef int DataTimeYMDh;
typedef int DataTimeYMDhm;
typedef int DataTimeYMDhms;
#define DataTimeEncodeYMD(Y,M,D)                 (Y*12+M)*32+D
#define DataTimeEncodeYMDh(Y,M,D,h)             ((Y*12+M)*32+D)*DATA_UNIT_HOUR+h
#define DataTimeEncodeYMDhm(Y,M,D,h,m)         (((Y*12+M)*32+D)*DATA_UNIT_HOUR+h)*60+m
#define DataTimeEncodeYMDhms(Y,M,D,h,m,s)     ((((Y*12+M)*32+D)*DATA_UNIT_HOUR+h)*60+m)*60+s
#define DataTimeDecodeYMD(v,Y,M,D,t)          int t= v/32,Y=t/12,M=t%12,D = v%32;
#define DataTimeDecodeYMDh(v,Y,M,D,h,t)       int t= v/DATA_UNIT_HOUR,Y,M,D = t%32, h = v%DATA_UNIT_HOUR; t /= 32; Y = t/12; M = t%12;
#define DataTimeDecodeYMDhm(v,Y,M,D,h,m,t)    int t= v/60,Y,M,D,h = t%DATA_UNIT_HOUR, m = v%60; t /= DATA_UNIT_HOUR; D = t%32; t /= 32; Y = t/12; M = t%12;
#define DataTimeDecodeYMDhms(v,Y,M,D,h,m,s,t) int t= v/60,Y,M,D,h, m=t%60, s=v%60; t /= 60; h = t%DATA_UNIT_HOUR; t /= DATA_UNIT_HOUR; D = t%32; t /= 32; Y =t/12; M = t%12;

typedef struct _DataChannel         DataChannel;
typedef struct _DataChannelEvent    DataChannelEvent;

#define DATA_SECOND_SET         0x03FF    // nal8 : seconds
#define DATA_2SECOND_OVER       0x03FE    // 2 seconds over : app proc
#define DATA_INDEX_AUDIO        0xFC00    // nal8 : FF
#define DATA_NULL_VIDEO         0x0000    // nal8 : 00
#define DATA_MASK_NAL           0x7C00
#define DATA_MASK_MILISECOND    DATA_SECOND_SET
#define DATA_NAL_PFRAME         0x0400
#define DATA_NAL_SPS            0x1C00
#define DATA_NAL_IFRAME         0x1400

typedef struct {
    unsigned short    marker1nal5miliSecond10;    // miliSecond 4 align
    unsigned short    size;
} DataIndexMedia; // size : 4

typedef struct {
    unsigned short    marker1nal5miliSecond10;    // miliSecond 4 align
    unsigned short    size;
    unsigned long     offset;
    long long         pts;
} DataIndexMedia2; // size : 4

#define DATA_PRESENT_VIDEO0    0x01    //  0 - 14
#define DATA_PRESENT_AUDIO0    0x02    //  0 - 14
#define DATA_PRESENT_VIDEO1    0x04    // 15 - 29
#define DATA_PRESENT_AUDIO1    0x08    // 15 - 29
#define DATA_PRESENT_VIDEO2    0x10    // 30 - 44
#define DATA_PRESENT_AUDIO2    0x20    // 30 - 44
#define DATA_PRESENT_VIDEO3    0x40    // 45 - 59
#define DATA_PRESENT_AUDIO3    0x80    // 45 - 59

typedef struct {
    unsigned char    minutePresent[60];
} DataExistMinuteInHour;

typedef struct {
    DataExistMinuteInHour    aExistMinuteInHour [25];
    DataTimeYMDhm            minuteFrom;
    DataTimeYMDhm            minuteTo;
    DataTimeYMDhm            minuteDay;
    DataTimeYMDhm            minuteStart;
    DataTimeYMDhm            minuteEnd;
    time_t                   secondLastRequest;
} DataExistCache;

typedef struct {
    DataTimeYMDhm            minuteStart;                                        //  0 : for exist
    DataTimeYMDhm            minuteEnd;                                          //  4 : for exist
    unsigned long            bytesDataVideo;                                     //  8 : for record
    DataTimeYMDhms           secondWritingVideo;                                 // 12 : for record : unused
    unsigned long            bytesDataAudio;                                     // 16 : for record
    DataTimeYMDhms           secondWritingAudio;                                 // 20 : for record : unused
    unsigned long            bytesDataIndex;                                     // 24 : for record
    DataTimeYMDhms           secondWritingIndex;                                 // 28 : for record
    DataTimeYMDh             hourRecycle;                                        // 32 : for recycling(inform)
    DataTimeYMDhms           secondPostRecord;                                   // 36 : for preRecord inform
    unsigned long            existDay [DATA_MAXIMUM_YEAR][12];                   // 40 : [year][month]
    DataTimeYMDh             hourExistCurrent;                                   // for buffering
    DataExistMinuteInHour    existMinuteInCurrent;                               // for buffering
    DataTimeYMDh             hourExistBefore;                                    // for buffering : future implement
    DataExistMinuteInHour    existMinuteInBefore;                                // for buffering : future implement
    unsigned char            aPresentPreRecord [DATA_PRE_RECORD_MAXIMUM_MINUTE]; // for saving
    DataTimeYMDhm            aMinutePreRecord  [DATA_PRE_RECORD_MAXIMUM_MINUTE]; // for saving
    unsigned char            nMinutePreRecord;                                   // for saving
    unsigned char            existBits;                                          // for saving
    unsigned char            existBitsPreRecord;                                 // for saving
    unsigned char            filler9;                                            //
    DataTimeYMDh             hourHDD [HDD_MAXIMUM][2];                           // unused : channel 0 only
    DataTimeYMDh             hourLastHDD;                                        // unused : channel 0 only
    DataTimeYMDh             hourPersistent;                                     // unused : channel 0 only : future implement
    DataTimeYMDh             hourLastWrite;                                      // unused : channel 0 only : future thinking
    DataIndexMedia           aIndexMedia [128];                                  // unused : for buffering : future implement
    unsigned char            nIndexMedia;                                        // unused : for buffering : future implement
    unsigned char            fullHDD [HDD_MAXIMUM];                              // unused : channel 0 only
    unsigned long            totalVideo;                                         // unused
    unsigned long            totalAudio;                                         // unused
    unsigned long            totalIndex;                                         // unused
    unsigned char            filler11;
    unsigned char            filler12;
    unsigned char            filler13;
    DataTimeYMDh             filler21;                                           // hourFirstHDD; // channel 0 only
    unsigned char            filler;
} DataPresent; // size : 4096

typedef struct {
    int               nIndex;
    DataIndexMedia   *aIndex;
    unsigned char    *buffer;
    DataTimeYMDhms    second;
    int               bytesVideo;
    int               bytesAudio;
    unsigned char    *bufferAudio;
} DataMediaList;

#define DATA_FLAG_VIDEO    0x1
#define DATA_FLAG_AUDIO    0x2
#define DATA_FLAG_BOTH     (DATA_FLAG_VIDEO | DATA_FLAG_AUDIO)

typedef struct {
    // request
    int                bytesMaximum;    // unused : maximum bytes for data
    // response
    unsigned long      bytesAudio;      // unused : overFlag: refer countRow & countS5
    unsigned long      bytesVideo;      // unused : overFlag: refer countRow & countS5
    unsigned short     totalRow;        // return row total
    short              startRow;        // unused : return row start
    short              endRow;          // unused : return row count
    DataIndexMedia2   *aIndexRow;
    unsigned short     nIndexSplit;
    unsigned short    *aIndexSplit;
    unsigned char     *aSecondSplit;
    unsigned char      exist;
    // internal used
    unsigned long     *aOffsetSplit;
    int                fdVideo;
    int                fdAudio;
    DataChannel       *pChannel;        // NULL is empty
    unsigned short     indexMy;         // my index
    int                flags;
    DataTimeYMDhm      minuteNext;
    DataTimeYMDhm      minutePrevious;
    int                uncheckExist;
    int                fdIndex;
    DataTimeYMDhm      minuteIndex;
    off_t              sizeIndex;
    long long          ptsCurrent;
    long long          ptsNext;
    char               fileNameAudio [64];
} DataReadInfo;

#define DATA_PAYLOADTYPE_AUDIO_G711    0
#define DATA_PAYLOADTYPE_VIDEO_H264    96
#define DATA_PAYLOADTYPE_VIDEO_JPEG    26
#define DATA_PAYLOADTYPE_VIDEO_MPEG    33
#define DATA_STATUS_UNUSED             0
#define DATA_STATUS_RUN                1
#define DATA_STATUS_PRE_RECORD         2

struct _DataChannel {
    // settable value
    unsigned char     isRecycleNone;
    unsigned char     status;              // see above
    unsigned short    hourFixedRecycle;    // 0 is NON/AUTO
    int               channel;
    int               fdPresent;
    DataTimeYMDh      hourReport;
    unsigned long     bytesReport;
    // initialize
    unsigned char     payloadTypeVideo;
    unsigned char     payloadTypeAudio;
    unsigned char     minutePreRecord;     // 0 ~ 24
    unsigned short    alignSize;
    int               channelIntensive;
    // supported information
    DataPresent      *pPresent;
    unsigned char     minuteLastWrite;
    DataTimeYMDh      hourLastWrite;
    DataTimeYMDhms    secondLastWrite;
    DataTimeYMDhm     minuteEndForSend;
    // internal used
    int               fdVideo;
    int               fdAudio;
    int               fdIndex;
    int               fdExist;
    int               waitFlag;
    int               countError;
    int               secondPreRecord;
    int               waitPreRecord;
    int               flushPreRecord;
    unsigned char     aExistPreRecord [DATA_PRE_RECORD_MAXIMUM_MINUTE];
    int               fdExistRead;
    DataIndexMedia2   aIndexMedia     [2][6000];
    DataReadInfo      aReadInfo       [2];
    long long         aPtsSecond      [2];
    DataReadInfo      aReadInfoLocal  [2];
    int               flagAudio;
    DataExistCache    existCache;
    int               reverse_record_flag_I_frame;
};

typedef struct {
    unsigned short    year;       // 0 ~ 49
    unsigned short    month;      // 0 ~ 11
    unsigned char     day [32];   // 1: exist
} DataCalendar;

typedef struct {
    unsigned short    year   [2]; // 0 ~ 49
    unsigned char     month  [2]; // 0 ~ 11
    unsigned char     day    [2]; // 1 ~ 31
    unsigned char     hour   [2]; // 0 ~ 23
    unsigned char     minute [2]; // 0 ~ 59
} DataTimeRange; // [0] : Start, [1] : End

typedef int (*DataCallback)(int status, const char *text);

typedef struct {
    // initialize
    int                 nHDD;
    int                 nReadInfo; // maximum playback(video&audio)
    DataReadInfo       *aReadInfo;
    int                 nChannel;
    DataChannel        *paChannel [DATA_CHANNEL_MAXIMUM];
    int                 nChannelEvent;
    DataChannelEvent   *paChannelEvent [DATA_CHANNEL_EVENT];
    // DataChannelEvent channelSelf;
    int                 recycleMegaBytes;
    int                 fullMegaBytes;
    unsigned char       isIntensive; // untested
    // notify information
    int                 statusNotify; // 0:unsendable/usable, 1:sendable/unusable
    unsigned long       totalMegaBytes  [HDD_MAXIMUM];
    unsigned long       remainMegaBytes [HDD_MAXIMUM];
    unsigned char       fullHDD         [HDD_MAXIMUM];
    int                 nCalendar;
    DataCalendar        aCalendar [60];
    DataTimeRange       range;
    DataTimeYMDh        hourRecycle; // if(0) no recycle else recycle hour
    // internal used
    pthread_mutex_t     lock;
    pthread_mutex_t     lock_calendar;
    char                directoryInfo [32];
    int                 fdLog;
    unsigned long       bytesLog;
    int                 alignSize;
    DataCallback        pCallback;
    int                 runManager;
    int                 pauseManage;
} DataDomain;

// Time
extern DataTimeYMD      dataPreviousDay  (DataTimeYMD day);
extern DataTimeYMD      dataNextDay      (DataTimeYMD day);
extern DataTimeYMDh     dataPreviousHour (DataTimeYMDh hour);
extern DataTimeYMDh     dataNextHour     (DataTimeYMDh hour);
extern DataTimeYMDhm    dataAddMinute    (DataTimeYMDhm minute, int add); // add : -59 ~ 59

// Calendar/Timebar
typedef struct {
    unsigned char     minutePresent [DATA_UNIT_HOUR][60]; // 0 : [hour][minute]
} DataExistMinuteInDay;

extern int dataSearchPresent          (DataChannel *pChannel, DataExistMinuteInHour *pExistMinuteInHour, DataTimeYMDh hour); //return:>0(exist),0(unexist),<0:eror
extern int dataSearchForTimeBar       (int channel, DataExistMinuteInDay *pExistMinuteInDay, int Y, int M, int D);
extern int dataSearchForEventCalendar (int channel, DataCalendar *aCalendar);
extern int dataReadExistMedia         (DataChannel *pChannel, DataTimeYMDh YMDh, DataExistMinuteInHour *pExistMinuteInHour, int nHour);
extern int dataReadExistEvent         (DataChannelEvent *pChannel, DataTimeYMDh YMDh, char *p, int nHour);

// video/audio
extern struct tm *dataCurrentTime(DataChannel *pChannel, struct timeval *ptv, struct timeval *ptvOld, DataMediaList *pMediaList, int isStart); // for dataWriteMedia

#define DATA_WRITE_AUDIO    0
#define DATA_WRITE_VIDEO    1
#define DATA_WRITE_START    3

extern int           dataWriteMedia    (DataChannel *pChannel, DataMediaList *pMediaList, int kind); // return : > 0(writeBytes), < 0 : error
extern int           dataPreRecord     (DataChannel *pChannel, DataTimeYMDhms secondPreRecord, DataTimeYMDhms secondPostRecord); // return : 0(OK), < 0 : eror
extern DataReadInfo *dataOpenPlayback  (DataChannel *pChannel); // NULL:error
extern void          dataClosePlayback (DataReadInfo *pReadInfo);
extern int           dataPrepareMedia  (DataChannel *pChannel, DataReadInfo *pReadInfo, DataTimeYMDhm minute);
extern void          dataDecrypt       (unsigned char *data);

//// Event
#define DATA_EVENT_RECORD_SIZE     16
#define DATA_EVENT_BUFFER_COUNT    96

typedef struct {
    DataTimeYMDh      hourStart;                                                        //    0 : for exist
    DataTimeYMDh      hourEnd;                                                          //    4 : for exist
    unsigned long     filler1;                                                          //    8 : for record : unused
    DataTimeYMDhms    filler2;                                                          //   12 : for record : unused
    unsigned long     filler3;                                                          //   16 : for record : unused
    DataTimeYMDhms    filler4;                                                          //   20 : for record : unused
    unsigned long     bytesDataEvent;	                                                //   24 : for record : unused (alternative : file size check)
    DataTimeYMDh      hourWritingEvent;                                                 //   28 : for record : unused (alternative : hourEnd)
    DataTimeYMDh      hourRecycle;                                                      //   32 : for recycling(inform)
    DataTimeYMDhms    filler7;                                                          //   36 : for pre record : unused
    unsigned long     existDay [DATA_MAXIMUM_YEAR][12];                                 //   40 : [year][month]
    unsigned long     nEventBuffer;                                                     // 1968 : implement after
    unsigned char     aEventBuffer [DATA_EVENT_BUFFER_COUNT][DATA_EVENT_RECORD_SIZE];   //      : implement after
    unsigned char     filler;
} DataPresentEvent;

struct _DataChannelEvent {
    // settable value
    unsigned char       isRecycleNone;    // unused
    unsigned char       status;           // unused
    unsigned short      hourFixedRecycle; // unused
    // fixed information
    int                 recordBytes;
    // supported information
    DataPresentEvent   *pPresent;
    // internal used
    int                 fdEvent;
    int                 channel;
    int                 fdPresent;
    int                 fdExist;
    int                 calendarSetHour;
};

#define DATA_SELF_KIND_INFORM     0
#define DATA_SELF_KIND_RECYCLE    1
#define DATA_SELF_KIND_RECOVER    2
#define DATA_SELF_KIND_START      3
#define DATA_SELF_KIND_END        4
#define DATA_SELF_KIND_FORMAT     5
#define DATA_SELF_KIND_DROP       6

typedef struct {
    unsigned char   kind;
    unsigned char   channel;
    unsigned char   minute;
    unsigned char   second;
    DataTimeYMDh    hourInfo;
    unsigned char   text[56];
} DataEventSelf;

typedef struct {
    // request
    DataTimeYMDh    hour;
    int             startRow;
    // response
    int             nEvent;
    void           *aEvent;
    int             totalRow;
    // internal used
    int             fdEvent;
} DataEventInfo;

extern char            *dataGetLastHourDirectory  (DataTimeYMDh YMDh);
extern int              dataEventWrite            (DataChannelEvent *pChannel, DataEventInfo *pEventInfo); // return : >= 0(writeBytes), < 0 : error
extern int              dataEventRead             (DataChannelEvent *pChannel, DataEventInfo *pEventInfo, int maximumList); // return : >= 0(readBytes), < 0 : error
extern int              dataEventNext             (DataChannelEvent *pChannel, DataEventInfo *pEventInfo, int maximumList); // return : >= 0(readBytes), < 0 : error

// Control
       int              dataCheckDetach           (void);
       char            *dataDetachSerial          (int i);
       int              dataGetMaster             (void);
       void             dataClearRangeAfterDelete (void);

extern int              dataStart                 (DataDomain *pDomain, int nReadInfo, int alignSize); // return : 0(OK), < 0 : error
extern void             dataEnd                   (void);
extern void             dataSetVerbose            (int mode);
extern DataDomain      *dataGetDomain             (void);
extern void             dataManage                (void);
extern int              dataDelete                (DataTimeYMDhm YMDhm);
extern char            *dataDeleteEvent           (DataTimeYMDhm YMDhm);

// Format
extern int              data_Format               (char *volume);
extern unsigned long    data_dir_parser           (char *volume, char *dir_name);
extern unsigned long    data_remove_file          (char *volume, char *dir_name);
extern unsigned long    dataGetTotalCount         (void);
extern unsigned long    dataGetRemoveCount        (void);
extern void             dataGetDiskInfo           (int *hddCount, int *totalSize, int *freeSize);
extern int              dataResetReadInfo         (DataReadInfo *pReadInfo);
extern int              dataGetKeyFrame2          (int channel, time_t requestTime, time_t requestEnd, unsigned char *pMediaBuffer, int *bytesMedia);
extern int              dataGetAudioSample        (int channel, time_t requestTime, time_t requestEnd, unsigned char *pMediaBuffer, int *bytesMedia);

// Event
extern DataTimeYMDhm    dataExistMediaFromEvent   (DataChannel *pChannel, DataTimeYMDhm minute, int forward);
extern int              dataMediaGetFromEvent     (DataChannel *pChannel, DataReadInfo *pReadInfo, DataTimeYMDhm minute);

// event
int                     event_delete_redundancy_data        (DataTimeYMDhm minuteCurrent);

// Error Code
#define DATA_OK                        0
#define DATA_ERROR_ENOMEM             -1            /* No Memory */
#define DATA_ERROR_ENOSPACE           -2            /* No Space */
#define DATA_ERROR_EWRITER_ALREADY    -3            /* There is another Writer */
#define DATA_ERROR_EINTERNAL          -4            /* DVR File System Internal Error */
#define DATA_ERROR_EPERM              -5            /* Permission Error */
#define DATA_ERROR_ENOINDEX           -6            /* No Index exist */
#define DATA_ERROR_EBADD              -7            /* Bad Descriptor */
#define DATA_ERROR_EWOULDBLOCK        -8            /* Write would block */
#define DATA_ERROR_ENEEDRECYCLE       -9            /* DVRFS Need Recycle */
#define DATA_ERROR_EINVALID           -10           /* Invalid argument */
#define DATA_ERROR_EINUSE             -11           /* DVR FS is in use */
#define DATA_ERROR_ENODVRFS           -12           /* No  DVR FS in System */
#define DATA_ERROR_EBROKEN            -13           /* DVR File system Broken */
#define DATA_ERROR_ENODISK            -14           /* No Hard Disk Found */
#define DATA_ERROR_ENEED_FSCK         -15           /* Need File System Check */
#define DATA_ERROR_EALREADY_LOCKED    -16           /* DVR_FS Already Locked */
#define DATA_ERROR_EDISKACCESS        -17           /* DVR met DISK Error */
#define DATA_ERROR_ENODRIVER          -18           /* DVR File System Driver Not Loaded */
#define DATA_ERROR_EMOUNTED           -19           /* DVR File System is already Mounted */
#define DATA_ERROR_EVERSION           -20           /* DVR File System Version Mismatch */
/* DVR FS Internal ERROR NUMBER */
#define DATA_ERROR_EFREEMAP           -50           /* Free Block Map Error */
#define DATA_ERROR_ECHECKSUM          -51           /* Check Sum Error */
#define DATA_ERROR_EDATAOFFSET        -52           /* Data offset Error */
#define DATA_ERROR_ECHANNELNUMBER     -53           /* Channel Number mismatch */
#define DATA_ERROR_ENOBACKUPDATA      -54           /* No Backup Data */
#define DATA_ERROR_UNOPEN            (-2001)
#define DATA_ERROR_WRITE_INDEX       (-2004)
#define DATA_ERROR_WRITE_DATA        (-2005)
#define DATA_ERROR_UNEXIST           (-2006)
#define DATA_ERROR_REMOVE_FILE       (-2007)
#define DATA_ERROR_RENAME_FILE       (-2008)
#define DATA_ERROR_MAKE_DIRECTORY    (-2009)

#endif
