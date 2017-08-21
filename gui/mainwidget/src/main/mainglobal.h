#ifndef MAINGLOBAL_H
#define MAINGLOBAL_H

#include "DVR.h"
#include "appmgr.h"

extern int      operationMode;
extern int      systemLocked;
extern int      DateFormat;
extern int      SelectPbSplit;
extern int      EventSearchPB;
extern int      msgBoxEsckey;
extern int      loadedLanguage;
extern int      DiskFormatNum;
extern int      currentSplit;
extern int      currentChannelNum;
extern int      splitStartChNum;
extern int      splitFlag;
extern int      mainWidth;
extern int      mainHeight;
extern int      calendarSearchFlag;
extern int      recorddialogFps;
extern int      currentSplitOld;
extern int      splitStartChNumOld;
extern int      mouseDoubleClickedFlag;
extern int      backupPopupShow;
extern int      archiveBackupFlag;
extern int      search_playback_start;
extern int      pbState;
extern int      record_icon_draw;

extern bool     initializeSystemFlag;

extern time_t   mainBackupStartTime;
extern time_t   mainBackupEndTime;

////////////////////////////////////////////////////////////////
// Configuration
extern cfg_setup_data_t                cfgSetup;
extern cfg_setup_data_t                cfgMain;
extern cfg_dvr_device_info_t           devInfo; // Ready Only !!!! - Don't modify!
extern network_property_t              NetCfg;
extern network_status_t                NetCfgInfo;
extern system_property_t               SystemCfg;
extern system_property_t               SystemCfgTemp;
extern system_status_t                 SystemCfgInfo;
extern storage_property_t              StorageCfg;;
extern storage_property_t              StorageCfgTemp;
extern display_property_t              DisplayCfg;
extern record2_property_t              RecordCfg;
extern device_property_t               DeviceCfg;

////////////////////////////////////////////////////////////////
// Search data
extern time_t                          eventLogSelTime;
extern time_t                          archiveLogSelTime;
extern time_t                          timeLogSelTime;
extern time_t                          syslogSelTime;
extern time_t                          calSelTime;
extern time_t                          eventBackupStartTime;
extern time_t                          eventBackupEndTime;

extern int                             eventLogCount;
extern int                             calDataCount;
extern int                             isEventSearch;

extern struct _time_search_info_ext    timeLog[25];
extern struct _eventlog_info           eventLog[MAX_EVENT_SEARCH_LOG];
extern struct                          _caldata calendarData[MAX_CAL_MONTH_DATA];

extern dls_convert_info_t              dlsLive;
extern dls_convert_info_t              dlsPlayback;

#endif // MAINGLOBAL_H
