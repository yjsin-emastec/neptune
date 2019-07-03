#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui>
#include "DVR.h"
#include "eventrecvthread.h"
#include "mainMenu.h"

class MainMenu;
class SetupDialog;
class SearchDialog;
class PlayBarDialog;
class BackupDialog;
class LoginDialog;
class StatusBarDialog;
class TextMessageDialog;
class VideoPane;
class DiskFormatProcessDialog;
class TimeSetDialog;
class RtcSetDialog;

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(int fbWidth, int fbHeight);
    QSize sizeHint() const;
    void Delay(int millisecondsToWait);

signals:
    void initEvent(int type, int initType, int progress);
    void playbackTimeNotify(time_t pbTime);
    void searchDataReady(int type);
    void searchCalendarReady(int type);
    void saveLogProgress(int logType, int progress);
    void configProgress(int cfgType, int progress);
    void backupProgress(int msg, int progress);
    void backupCalculation(int deviceFreeMb, unsigned long mediaBytes, unsigned long indexBytes);
    void diskformatProgress(int disk, unsigned long total, unsigned long percent, unsigned long remain_time);
    void upgradeProgress(int percent);
    void diskformatEnd();
    void playbackStopNotify();
    void timeChangeNotify();
    void archiveProgress(int msg, int progress);
    void resolutionChangeNotify(int hdmi);
    void splitChangeNotify(int split);
    void queryLogCount();
    void queryLogData();
    void queryLogBackup();
    void updateAudioButton();
    void systemLogCount     (void);
    void systemLogData      (void);
    void systemLogBackup    (void);
    void updateSplitButton();
    void updateTriggerState(int);

public slots:
    void videoPaneClicked(int ch);
    void videoPaneDoubleClicked(int ch);
    void videoPaneRightClicked(int ch);
    void onSetAudioMute();
    void onSetAudio1();
    void onSetAudio2();
    void onSetAudio3();
    void onSetAudio4();
    void setAudioOut();
    void setAudioMode();
    void runSetup();
    void runBackup();
    void runSearch();
    void stopPlayback();
    void doDvrEvent(Event *e);
    void doUpdateDvrTime();
    void initializeSystem();
    void systemShutdown();
    void systemReboot();
    void splitChannelBySetup(int ch);
    void ResolutionChange(int hdmi);
    void controlBarAutoHideChange();
    void controlBarChange();
    void playBarChange();
    void DiskFormatProcessDlgOpen();
    void DiskFormatSystemReboot();
    void DiskFormatSystemShutdown();
    void oneChannelSplit(int ch);
    void playbackOneChannel(int ch);
    void updateGpsStatus();
    void eventPopupOneChannel(int type, int ch);
    void onSaveSystemPage(int type, int val);
    void onSaveRecordPage(int type);
    void onSaveDisplayPage(int type);
    void onSaveDevicePage(int type);
    int  splitScreen(int split);
    void onChangeSplit(int startCh, int selectCh, int split);

protected:
    void closeEvent(QCloseEvent *event);
    void rotateSplit();
    void setSplitScreen(int startCh, int selectCh, int split);
    void rotateOneChannel(int ch);
    void startPlayback();
    void keypadEvent(unsigned char code);
    bool checkPassword(int mode, int *userId);
    int  customSplitScreen(int split);

private:
    void createStatusBar(int isReset);
    void createPlayBar();
    void createPopupDialog();
    void createVideoPane(int isReset);
    void createMainMenu(void);
    void loadStyleSheet();
    void showOsd(int show);
    void passNumpadKeypadEvent(unsigned char code);
    void passKeypadEvent(unsigned char code);
    void updateDvrEvent(live_event_t *live);
    void setOverwrite();
    void setDateFormat();
    void statusBarState(int state);
    void playBarState(int state);
    void translatorChange(int lang);
    void setStrogeOverwirte();
    void SetOperationMode(int mode);
    void setConfigString();
    void getConfigString();
    void noDataUpdate(int live);
    void audioSetting(int preChannel, int curChannel);
    void StatusBarShow(void);
    void StatusBarHide(void);
    int  LanguageValueTransformation();
    int  isMaxSplit();
    int  loadData();
    int  getMaxSplit();
    void ParkingSystem(void);
    void setAudioOutCh(int ch);
    void triggerAudioOut(int ch);

    MainMenu                    *mainMenu;
    StatusBarDialog             *statusBar;
    PlayBarDialog               *playBar;
    SetupDialog                 *setupDialog;
    SearchDialog                *searchDialog;
    BackupDialog                *backupDialog;
    LoginDialog                 *loginDialog;
    TimeSetDialog               *timeSetDialog;
    RtcSetDialog                *rtcSetDialog;
    TextMessageDialog           *msgBox,
                                *msgBoxDisk;
    DiskFormatProcessDialog     *diskformatprocessDialog;
    EventRecvThread             *eventThread;
    QTranslator                 *selTranslator;
    VideoPane                   *videoPane[MAX_VIDEO_CH+1];
    live_event_t                 liveEvent;

    int                          preAudio,
                                 keyAudio,
                                 StorageOverwrite,
                                 StorageRecordingLimit,
                                 controlBarAutoHide,
                                 searchMenu,
                                 mainPbChannel,
                                 sensorEventPopupCh,
                                 isfactoryDefault,
                                 latestChannelNum,
                                 latestSplit,
                                 latestSplitStartChNum,
                                 isShowOsd,
                                 audioStatus,
                                 statusBarEnable,
                                 playBarEnable,
                                 leftstatusBarEnable,
                                 isTrigger,
                                 isDisk,
                                 backupType,
                                 isDrawRecordIcon,
                                 previousAudioCh,
                                 previousSplit;

    bool                         audioEnable,
                                 m_selectOther;

    disk_used_info_t             diskInfo[MAX_HDD_COUNT];

private slots:
    void onHideStatusBar(void);
    void onShowStatusBar(void);
};
#endif // MAINWIDGET_H
