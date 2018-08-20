#include <QtGui>
#include <QtGui/QApplication>
#include <QPalette>
#include <QScreen>
#include <QTextCodec>
#include "mainwidget.h"
#include "statusbardialog.h"
#include "playbardialog.h"
#include "search/searchdialog.h"
#include "search/backupdialog/backupdialog.h"
#include "dvrsetup/setup/setupdialog.h"
#include "videopane.h"
#include "login/logindialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "dvrsetup/device/diskformat/diskformatprocess.h"
#include "languagedefine.h"
#include "mainglobal.h"
#include "dev/Ver.h"
#include "dev/DevMgr.h"
#include "dev/Rtc.h"
#include "dev/gps.h"
#include "utils/utils.h"
#include "core/Core.h"
#include "aifbackup2.h"
#include "aifrecord.h"

int                             operationMode,
                                systemLocked,
                                DateFormat,
                                SelectPbSplit,
                                EventSearchPB,
                                msgBoxEsckey,
                                mdinVideoOutput,
                                loadedLanguage,
                                DiskFormatNum,
                                currentSplit,
                                currentChannelNum,
                                splitStartChNum,
                                splitFlag,
                                mainWidth,
                                mainHeight,
                                calendarSearchFlag,
                                recorddialogFps,
                                currentSplitOld,
                                splitStartChNumOld,
                                mouseDoubleClickedFlag,
                                backupPopupShow,
                                archiveBackupFlag,
                                search_playback_start,
                                pbState,
                                record_icon_draw;

bool                            initializeSystemFlag;

//////////////////////////////////////////////////////////////// // Configuration
cfg_setup_data_t                cfgSetup;
cfg_setup_data_t                cfgMain;

cfg_dvr_device_info_t           devInfo; // Ready Only !!!! - Don't modify!

system_property_t               SystemCfg;
system_property_t               SystemCfgTemp;
system_status_t                 SystemCfgInfo;

storage_property_t              StorageCfg;
storage_property_t              StorageCfgTemp;

device_property_t               DeviceCfg;

display_property_t              DisplayCfg;

record2_property_t              RecordCfg;
//////////////////////////////////////////////////////////////// // Search data
time_t                          eventLogSelTime,
                                archiveLogSelTime,
                                timeLogSelTime,
                                syslogSelTime,
                                calSelTime,
                                eventBackupStartTime = 0,
                                eventBackupEndTime   = 0;

int                             eventLogCount,
                                calDataCount,
                                isEventSearch        = 0;

struct _time_search_info_ext    timeLog[25];

EVENT_LOG_DATA_S                gEventLog[MAX_EVENT_LOG_PAGE_DATA];
SYSTEM_LOG_DATA_S               gSystemLog[SYSTEM_LOG_COUNT_PER_PAGE];

struct _eventlog_info           eventLog[MAX_EVENT_SEARCH_LOG];
struct _caldata                 calendarData[MAX_CAL_MONTH_DATA];

dls_convert_info_t              dlsLive;
dls_convert_info_t              dlsPlayback;

MainWidget::MainWidget(int fbWidth, int fbHeight)
{
    qDebug("[MAINWIDGET SIZE] %d, %d", fbWidth, fbHeight);
    setWindowFlags(Qt::WindowSystemMenuHint | Qt::FramelessWindowHint);

    mainWidth = fbWidth;
    mainHeight = fbHeight;

    appmgr_set_mainwidget_size(mainWidth, mainHeight);
    appmgr_set_screen_size(mainWidth, mainHeight);

    //qDebug("size %d, %d\n", mainWidth, mainHeight);
    QColor barColor(50,57,83);

    setPalette(QPalette(QColor(20, 22, 24)));
    setAutoFillBackground(true);

    initializeSystemFlag        = false;

    systemLocked                = 0;
    SelectPbSplit               = 0;
    EventSearchPB               = 0;
    playBarEnable               = 0;

    msgBoxEsckey                = 0;
    searchMenu                  = -1;
    calendarSearchFlag          = 0;

    mainPbChannel               = -1;
    backupPopupShow             = -1;
    archiveBackupFlag           = -1;

    sensorEventPopupCh          = 0;

    search_playback_start       = 0;
    record_icon_draw            = 0;

    m_selectOther               = false;

    loadedLanguage              = -1;
    selTranslator               = NULL;
    controlBarAutoHide          = 1;
    statusBarEnable             = 0;
    isDisk                      = 1;
#if 1 // GyverJeong [18/03/15]
    isDrawRecordIcon            = 1;
#endif

    (void) appmgr_set_control_bar_auto_Hide(controlBarAutoHide);

    isfactoryDefault            = loadData();

    leftstatusBarEnable         = 0;

    statusBar                   = NULL;
    playBar                     = NULL;
    searchDialog                = NULL;
    setupDialog                 = NULL;
    backupDialog                = NULL;
    loginDialog                 = NULL;
    diskformatprocessDialog     = NULL;
    timeSetDialog               = NULL;
    rtcSetDialog                = NULL;
    msgBox                      = NULL;
    msgBoxDisk                  = NULL;

    getConfigString();

    for(int i = 0; i < MAX_VIDEO_CH+1; i++)
    {
        videoPane[i] = NULL;
    }

    createVideoPane(0);

    setDateFormat();
    setStrogeOverwirte();

    connect(this, SIGNAL(resolutionChangeNotify(int)), this, SLOT(ResolutionChange(int)));

    currentSplit = -1;
    currentSplitOld = getMaxSplit();

    loadStyleSheet();

    operationMode = OPMODE_NONE;
    SetOperationMode(operationMode);

    eventThread = new EventRecvThread();
    connect(eventThread, SIGNAL(eventReady(Event *)), this, SLOT(doDvrEvent(Event *)));
    connect(eventThread, SIGNAL(timerReady()), this, SLOT(doUpdateDvrTime()));
    eventThread->start();

    appmgr_set_send_event_ready(1);

    move(0, 0);
    resize(mainWidth, mainHeight);

    splitFlag = 0;
    isTrigger = 0;

    qDebug("init.... start");

    QTimer::singleShot(100 , this, SLOT(initializeSystem()));
}
void MainWidget::onSaveSystemPage(int type, int val)
{
    qDebug("setup.............> system setting");

    if(type > 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "System Setting");
    }

    if(type == 1 && val != 0)
    {
        char tmp[64];
        qDebug("setup.............> time setting");

        utils_cfg_get_item("sys.time_format", tmp);
        if(memcmp(tmp, SystemCfg.time_format, strlen(SystemCfg.time_format)))
        {
            QString timeFormat = QString("Time Format: %1").arg(QString::fromUtf8(SystemCfg.time_format));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, timeFormat.toStdString().c_str());
        }

        utils_cfg_get_item("sys.gps_sync", tmp);
        if(memcmp(tmp, SystemCfg.gps_sync, strlen(SystemCfg.gps_sync)))
        {
            QString gps = QString("GPS Sync: %1").arg(QString::fromUtf8(SystemCfg.gps_sync));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, gps.toStdString().c_str());
        }

        utils_cfg_get_item("sys.time_zone", tmp);
        if(memcmp(tmp, SystemCfg.time_zone, strlen(SystemCfg.time_zone)))
        {
            QString timeZone = QString("Time Zone: %1").arg(QString::fromUtf8(SystemCfg.time_zone));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, timeZone.toStdString().c_str());
        }

        QString timeSet = QString("TimeSet %1 and Reboot").arg(QString::fromUtf8(atime(val)));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, timeSet.toStdString().c_str());

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
        this->Delay(3000);

        sync(); sync(); sync();

        ParkingSystem();

        appmgr_set_system_rtc_time(val);

        system_state = SYSTEM_TIME_SET;
        sleep(2);
        systemReboot();
        return;
    }
    else if(type == 2)
    {
        char tmp[64];
        utils_cfg_get_item("sys.time_format", tmp);
        if(memcmp(tmp, SystemCfg.time_format, strlen(SystemCfg.time_format)))
        {
            QString timeFormat = QString("Time Format: %1").arg(QString::fromUtf8(SystemCfg.time_format));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, timeFormat.toStdString().c_str());
        }

        utils_cfg_get_item("sys.gps_sync", tmp);
        if(memcmp(tmp, SystemCfg.gps_sync, strlen(SystemCfg.gps_sync)))
        {
            QString gps = QString("GPS Sync: %1").arg(QString::fromUtf8(SystemCfg.gps_sync));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, gps.toStdString().c_str());
        }

        utils_cfg_get_item("sys.time_zone", tmp);
        if(memcmp(tmp, SystemCfg.time_zone, strlen(SystemCfg.time_zone)))
        {
            QString timeZone = QString("Time Zone: %1").arg(QString::fromUtf8(SystemCfg.time_zone));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, timeZone.toStdString().c_str());
        }

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();

        statusBar->setTimeFormat(DateFormat);
    }
    else if(type == 3) // License Plate
    {
        QByteArray text = QByteArray::fromHex(SystemCfg.license_plate);
        QString    str  = QString("License Plate: %1").arg(QString::fromUtf8(text.data()));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
    }
    else if(type == 4) // Factory Default
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Factory Default and then Reboot");
        this->Delay(3000);
        sync(); sync(); sync();
        ParkingSystem();

        qDebug("setup : factory default");

        system_state = SYSTEM_LOAD_FACTORY_DEFAULT;

        appmgr_sysinfo_set_factory_default();

        sleep(1);

        utils_system("rm -rf /cfg/*");

        systemReboot();
        sleep(3);
    }
    else if(type == 5) // Security
    {
        char tmp[64];
        utils_cfg_get_item("sys.system_lock", tmp);
        if(memcmp(tmp, SystemCfg.system_lock, strlen(SystemCfg.system_lock)))
        {
            QString lock = QString("System Lock: %1").arg(QString::fromUtf8(memcmp(SystemCfg.system_lock,"NO",strlen(SystemCfg.system_lock))==0?"Off":"On"));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, lock.toStdString().c_str());
        }

        utils_cfg_get_item("sys.admin_passwd", tmp);
        if(memcmp(tmp, SystemCfg.admin_passwd, strlen(SystemCfg.admin_passwd)))
        {
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Password Change");
        }

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
    }
    else if(type == 6) // Language
    {
        QString str = QString("Language Change: %1").arg(QString::fromUtf8(SystemCfg.language));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        setConfigString();
        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
        sync(); sync(); sync();

        ParkingSystem();

        qDebug("setup : change language");
        //system_state = SYSTEM_CHANGE_LANGUAGE;

        systemReboot();
    }
    else if(type == 7) // Load config
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Load Config andThen Reboot");
        this->Delay(3000);
        sync(); sync(); sync();

        ParkingSystem();

        qDebug("setup : load config");

        system_state = SYSTEM_LOAD_CONFIG;

        sleep(1);

        systemReboot();

        sleep(3);
    }
    else if(type == 8) // Firmware Upgrade
    {
        sync(); sync(); sync();
        ParkingSystem();

        qDebug("setup : firmware upgrade");

        system_state = SYSTEM_SOFTWARE_UPGRADE;

        sleep(1);

        systemReboot();

        sleep(3);
    }
    else
    {
        memcpy(&cfgSetup, &cfgMain, sizeof(cfg_setup_data_t));
        getConfigString();
        appmgr_cfg_change();
    }
}
void MainWidget::onSaveRecordPage(int type)
{
    if(type > 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Record Setting");

        if(type == 1)
        {
            for(int ch = 0; ch < devInfo.videoNum; ch++)
            {
                QString str = QString("Normal: ch:%1 F:%2 Q:%3 R:%4 A:%5").arg(
                        QString::number(ch+1),
                        QString::number(cfgSetup.rec.record_main.fr_hd[ch]),
                        QString::fromUtf8(cfgSetup.rec.record_main.quality[ch]==QUALITY_ULTRA?"High":cfgSetup.rec.record_main.quality[ch]==QUALITY_HIGH?"Middle":"Low"),
                        QString::fromUtf8(cfgSetup.rec.record_type[ch]==false?"Off":"On"),
                        QString::fromUtf8(cfgSetup.rec.audio[ch]==false?"Off":"On"));
                appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
            }
        }
        else if(type == 2)
        {
            QString str = QString("Event: D:%1 I:%2 T:%3").arg(
                    QString::number(cfgSetup.rec.post_record[0]*2),
                    QString::fromUtf8(RecordCfg.event_impact),
                    QString::fromUtf8(RecordCfg.event_trigger));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        }

        setConfigString();
        appmgr_cfg_change();

        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
    }
    else // Cancel
    {
        memcpy(&cfgSetup, &cfgMain, sizeof(cfg_setup_data_t));
        getConfigString();
        appmgr_cfg_change();
    }
}
void MainWidget::onSaveDevicePage(int type)
{
    if(type > 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Device Setting");
    }

    if(type == 1) // Disk Format
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Format Start");
        DiskFormatNum = 0;
        DiskFormatNum |= (1 << 0);
        DiskFormatProcessDlgOpen();

        operationMode = OPMODE_LIVE;
        SetOperationMode(operationMode);

        return;
    }
    else if(type == 2) // Buzzer Output
    {
        QString str = QString("Buzzer Output: %1").arg(QString::fromUtf8(DeviceCfg.buzzer_output));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
    }
    else if(type == 3) // Gsensor Output
    {
        QString str = QString("Impact Sensitivity: %1").arg(QString::fromUtf8(DeviceCfg.gsensor_level));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
        appmgr_gsensor_config();
    }
    else if(type == 4) // Trigger Input
    {
        for(int ii=0; ii < 4; ii++)
        {
            QString str = QString("Trg%1 S:%2 D:%3 P:%4 A:%5").arg(
                    QString::number(ii+1),
                    QString::fromUtf8(DeviceCfg.trigger1_source+ii*8),
                    QString::fromUtf8(DeviceCfg.trigger1_delay+ii*8),
                    QString::fromUtf8(DeviceCfg.trigger1_priority+ii*8),
                    QString::fromUtf8(DeviceCfg.trigger1_audio+ii*8));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        }

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
    }
    else if(type == 5) // Video Input
    {
        for(int ii=0; ii < devInfo.videoNum; ii++)
        {
            QString str = QString("VI%1 M:%2 F:%3").arg(
                    QString::number(ii+1),
                    QString::fromUtf8(DeviceCfg.camera_mirror00+ii*8),
                    QString::fromUtf8(DeviceCfg.camera_flip00+ii*8));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        }

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();
        appmgr_config_videoIn();
    }
    else // Cancel
    {
        memcpy(&cfgSetup, &cfgMain, sizeof(cfg_setup_data_t));
        getConfigString();
        appmgr_cfg_change();
    }
}
void MainWidget::onSaveDisplayPage(int type)
{
    if(type > 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Display Setting");
    }

    if(type == 1) // Channel Name
    {
        qDebug("setup.............> Channel Name change");

        for(int ii = 0; ii < devInfo.videoNum; ii++)
        {
            QByteArray CamName = QByteArray::fromHex((char *)DisplayCfg.channel_name[ii]);
            QString str = QString("CAM%1 Name: %2").arg(QString::number(ii+1), QString::fromUtf8(CamName));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        }

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            QByteArray text = QByteArray::fromHex((char *)DisplayCfg.channel_name[i]);
            QString str = QString::fromUtf8(text.data());
            videoPane[i]->setChannelName(str);
        }

        showOsd(cfgMain.live.osd_status);
    }
    else if(type == 2) // Video Output HDMI
    {
        qDebug("setup.............> resolution change");
        QString str = QString("VO HDMI: %1, Rebooting").arg(QString::fromUtf8(DisplayCfg.video_output_hdmi));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();

        sync(); sync(); sync();

        ParkingSystem();

        sleep(1);

        system_state = SYSTEM_VGA_RESOLUTION;

        systemReboot();
        sleep(3);
    }
    else if(type == 3) // Video Output CVBS
    {
        qDebug("setup.............> video out cvbs change");
        char *x = cfgSetup.gbl.ntsc?DisplayCfg.cvbs_ntsc_x_value     :DisplayCfg.cvbs_pal_x_value;
        char *y = cfgSetup.gbl.ntsc?DisplayCfg.cvbs_ntsc_y_value     :DisplayCfg.cvbs_pal_y_value;
        char *w = cfgSetup.gbl.ntsc?DisplayCfg.cvbs_ntsc_width_value :DisplayCfg.cvbs_pal_width_value;
        char *h = cfgSetup.gbl.ntsc?DisplayCfg.cvbs_ntsc_height_value:DisplayCfg.cvbs_pal_height_value;
        QString str = QString("VO CVBS: %1 X=%2 Y=%3 W=%4 H=%5").arg(
                QString::fromUtf8(DisplayCfg.video_output_cvbs),
                QString::fromUtf8(x),
                QString::fromUtf8(y),
                QString::fromUtf8(w),
                QString::fromUtf8(h));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();

        appmgr_config_cvbs();
    }
    else if(type == 4) // OSD
    {
        QString str = QString("OSD CAM:%1 NoV:%2 Bar:%3 Rec:%4").arg(
                QString::fromUtf8(DisplayCfg.osd_chname),
                QString::fromUtf8(DisplayCfg.osd_viloss),
                QString::fromUtf8(DisplayCfg.osd_status),
                QString::fromUtf8(DisplayCfg.osd_record));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());

        setConfigString();
        appmgr_cfg_change();
        memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
        appmgr_save_setup(0, &cfgMain);
        appmgr_cfg_sync();

        showOsd(cfgMain.live.osd_status);
    }
    else // Cancel
    {
        memcpy(&cfgSetup, &cfgMain, sizeof(cfg_setup_data_t));
        getConfigString();
        appmgr_cfg_change();
    }
}
void MainWidget::closeEvent(QCloseEvent *event)
{
    appmgr_close_sensorlog();
    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "System Shutdown by Menu");
    appmgr_deinit_systemstate(system_state);

    operationMode = OPMODE_MESSAGE;
    SetOperationMode(operationMode);

    if(!msgBox)
    {
        msgBox = new TextMessageDialog(tr("POWER OFF"), tr("\t\t\t\tNOTICE\n\n" "System was shutdown successfully.\n" "Turn off the power."), 13, this);
    }

    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

    while(1)
    {
        msgBox->exec();
    }

    delete msgBox;
    msgBox = NULL;

    event->accept();
}
QSize MainWidget::sizeHint() const
{
    return QSize(mainWidth, mainHeight);
}
void MainWidget::loadStyleSheet()
{
    QFile file;

    file.setFileName(":/qss/darkstyle.qss");

#if 1   //yjsin [17/09/14] if text is long, change button font size 48px->44px
    if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 || utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0 || utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            file.setFileName("/tmp/eastern/usr/lib/darkstyle_button_font_small.qss");
            qDebug("load darkstyle_button_font_small.qss from nfs");
        }
        else
        {
            file.setFileName("/usr/lib/darkstyle_button_font_small.qss");
            qDebug("load darkstyle_button_font_small.qss");
        }
    }
#endif

    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
    qDebug("-------------------- Dark Style");
}
void MainWidget::createStatusBar(int isReset)
{
    qDebug("%s + \n", __func__);

    statusBar = new StatusBarDialog(0, this);

    if(isReset)
    {
        systemLocked = cfgMain.gbl.lock;

        memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);

        appmgr_get_disk_info(diskInfo);

        if(diskInfo[0].hddCount != 0)
        {
            statusBar->updateDiskProgress(liveEvent.diskSize, liveEvent.diskFree);
        }
    }

    statusBar->setTimeFormat(DateFormat);

    statusBar->move((mainWidth-(statusBar->width()))/2, mainHeight-(statusBar->height()));

    if(!isReset)
    {
        statusBar->show();
    }

    statusBar->raise();
    statusBar->activateWindow();

    qDebug("%s - \n", __func__);
}
void MainWidget::createPlayBar()
{
    qDebug("%s + \n", __func__);

    if(playBar)
    {
        delete playBar;
        playBar = NULL;
    }

    playBar = new PlayBarDialog(this);

    connect(playBar, SIGNAL(exitSearchBar()),            this,    SLOT(stopPlayback()));
    connect(playBar, SIGNAL(backupClicked()),            this,    SLOT(runBackup()));
    connect(playBar, SIGNAL(channelClicked(int)),        this,    SLOT(oneChannelSplit(int)));
    connect(playBar, SIGNAL(setAudio1()),                this,    SLOT(onSetAudio1()));
    connect(playBar, SIGNAL(setAudio2()),                this,    SLOT(onSetAudio2()));
    connect(playBar, SIGNAL(setAudio3()),                this,    SLOT(onSetAudio3()));
    connect(playBar, SIGNAL(setAudio4()),                this,    SLOT(onSetAudio4()));
    connect(playBar, SIGNAL(setAudioMute()),             this,    SLOT(onSetAudioMute()));
    connect(this,    SIGNAL(playbackTimeNotify(time_t)), playBar, SLOT(playbackTimeUpdate(time_t)));
    connect(this,    SIGNAL(searchDataReady(int)),       playBar, SLOT(searchDataUpdate(int)));
    connect(this,    SIGNAL(playbackStopNotify()),       playBar, SLOT(closeSearchBar()));
    connect(this,    SIGNAL(splitChangeNotify(int)),     playBar, SLOT(splitChanged(int)));

    playBar->move((mainWidth - playBar->width())/2, mainHeight-playBar->height());
    playBar->hide();
    playBar->setTimeFormat(DateFormat);

    qDebug("%s - \n", __func__);
}
void MainWidget::createMainMenu()
{
    qDebug("%s + \n", __func__);

    mainMenu = new MainMenu(this);

    connect(mainMenu, SIGNAL(setupClicked()),    this, SLOT(runSetup()));
    connect(mainMenu, SIGNAL(searchClicked()),   this, SLOT(runSearch()));
    connect(mainMenu, SIGNAL(shutdownClicked()), this, SLOT(systemShutdown()));
    connect(mainMenu, SIGNAL(setAudioMute()),    this, SLOT(onSetAudioMute()));
    connect(mainMenu, SIGNAL(setAudio1()),       this, SLOT(onSetAudio1()));
    connect(mainMenu, SIGNAL(setAudio2()),       this, SLOT(onSetAudio2()));
    connect(mainMenu, SIGNAL(setAudio3()),       this, SLOT(onSetAudio3()));
    connect(mainMenu, SIGNAL(setAudio4()),       this, SLOT(onSetAudio4()));
    connect(mainMenu, SIGNAL(enterMainMenu()),   this, SLOT(onHideStatusBar()));
    connect(mainMenu, SIGNAL(exitMainMenu()),    this, SLOT(onShowStatusBar()));
    connect(this,     SIGNAL(updateAudioButton()), mainMenu, SLOT(onUpdateAudioButton()));

    qDebug("%s - \n", __func__);
}
void MainWidget::createPopupDialog()
{
    qDebug("%s + \n", __func__);

    if(!setupDialog)
    {
        setupDialog = new SetupDialog(this);

        connect(setupDialog, SIGNAL(setupChangeSplit(int)),    this,        SLOT(splitChannelBySetup(int)));
        connect(setupDialog, SIGNAL(saveSystemPage(int, int)), this,        SLOT(onSaveSystemPage(int, int)));
        connect(setupDialog, SIGNAL(saveRecordPage(int)),      this,        SLOT(onSaveRecordPage(int)));
        connect(setupDialog, SIGNAL(saveDisplayPage(int)),     this,        SLOT(onSaveDisplayPage(int)));
        connect(setupDialog, SIGNAL(saveDevicePage(int)),      this,        SLOT(onSaveDevicePage(int)));
        connect(this,        SIGNAL(configProgress(int, int)), setupDialog, SLOT(updateConfigProgress(int, int)));
        connect(this,        SIGNAL(upgradeProgress(int)),     setupDialog, SLOT(onUpgradeProgress(int)));

        setupDialog->resize(1280, 720);
        setupDialog->frame->setGeometry(4, 4, setupDialog->width()-8, setupDialog->height()-8);

        qDebug("setupDialog size ESTN : %d, %d", setupDialog->width(), setupDialog->height());

        setupDialog->updateConfig(0);
    }

    if(!searchDialog)
    {
        searchDialog = new SearchDialog(this);

        connect(this, SIGNAL(searchDataReady(int)),     searchDialog, SLOT(onSearchDataUpdate(int)));
        connect(this, SIGNAL(searchCalendarReady(int)), searchDialog, SLOT(onSearchCalendarUpdate(int)));
        connect(this, SIGNAL(queryLogCount()),          searchDialog, SLOT(onQueryLogCount()));
        connect(this, SIGNAL(queryLogData()),           searchDialog, SLOT(onQueryLogData()));
        connect(this, SIGNAL(queryLogBackup()),         searchDialog, SLOT(onQueryLogBackup()));
        connect(this, SIGNAL(systemLogCount  ()),       searchDialog, SLOT(onSystemLogCount  ()));
        connect(this, SIGNAL(systemLogData   ()),       searchDialog, SLOT(onSystemLogData   ()));
        connect(this, SIGNAL(systemLogBackup ()),       searchDialog, SLOT(onSystemLogBackup ()));
    }

    if(!backupDialog)
    {
        backupDialog = new BackupDialog(this);

        connect(this, SIGNAL(backupProgress(int, int)),                             backupDialog, SLOT(updateBackupProgress(int, int)));
        connect(this, SIGNAL(backupCalculation(int, unsigned long, unsigned long)), backupDialog, SLOT(updateBackupCalcution(int, unsigned long, unsigned long)));
    }
    else
    {
        backupDialog->updateBackupDialog();
    }

    if(!loginDialog)
    {
        loginDialog = new LoginDialog(this);
        loginDialog->updateConfig(CHECK_SETUP);
    }

    if(!diskformatprocessDialog)
    {
        diskformatprocessDialog = new DiskFormatProcessDialog(this);

        connect(this, SIGNAL(diskformatProgress(int, unsigned long, unsigned long, unsigned long)), diskformatprocessDialog, SLOT(onDiskFormatupdateprocess(int, unsigned long, unsigned long, unsigned long)));
        connect(this, SIGNAL(diskformatEnd()), diskformatprocessDialog, SLOT(onDiskFormatupdateEnd()));
        connect(diskformatprocessDialog, SIGNAL(diskformatReboot()), this, SLOT(DiskFormatSystemReboot()));
    }

    qDebug("%s - \n", __func__);
}
bool MainWidget::checkPassword(int mode, int *userId)
{
    int checkPw = 0;

    switch(mode)
    {
        case CHECK_SETUP:
        case CHECK_SEARCH:
        case CHECK_RECORD_OFF:
        case CHECK_POWER_OFF:
        case CHECK_LOCK:
        case CHECK_UNLOCK:
        case CHECK_FORMAT:
            checkPw = 1;
            break;
        case CHECK_POWER_ON:
        case CHECK_BACKUP:
            break;
    }

    if(!checkPw)
    {
        *userId = 0;
    }
    else
    {
        operationMode = OPMODE_LOGIN;
        SetOperationMode(operationMode);

        if(!loginDialog)
        {
            loginDialog = new LoginDialog(this);
            loginDialog->updateConfig(mode);
        }

        loginDialog->updateConfig(mode);
        loginDialog->move((mainWidth - loginDialog->size().width()) / 2, (mainHeight - loginDialog->size().height()) / 2);

        if(loginDialog->exec())
        {
            if(loginDialog->selUserId == 0)
            {
                *userId = loginDialog->selUserId;
            }
            else
            {
                *userId = loginDialog->selUserId - 1;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}
void MainWidget::systemShutdown()
{
    int userId = 0;

    if(operationMode != OPMODE_LIVE)
    {
        return;
    }

    int ret = 0;
    operationMode = OPMODE_MESSAGE;
    SetOperationMode(operationMode);
    msgBoxEsckey = 1;

    if(!msgBox)
    {
        msgBox = new TextMessageDialog(tr("POWER OFF"), tr("\t\t\t\tWARNING\n\n" "Do you want to shutdown the system?"), 0, this);
    }

    msgBox->buttonCancel->setFocus();
    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
    ret = msgBox->exec();

    delete msgBox;
    msgBox = NULL;

    msgBoxEsckey = 0;

    if(!ret)
    {
        qDebug("%s => NO", __func__);
        operationMode = OPMODE_LIVE;
        SetOperationMode(operationMode);
        this->onShowStatusBar();
        return;
    }
    else
    {
        qDebug("%s => YES", __func__);
    }

    if(utils_cfg_cmp_item(SystemCfg.system_lock, "YES") == 0)
    {
        if(!checkPassword(CHECK_POWER_OFF, &userId))
        {
            operationMode = OPMODE_LIVE;
            SetOperationMode(operationMode);
            this->onShowStatusBar();
            return;
        }
    }

    time_t          gpsTime;
    struct tm       tmGps;
    struct tm      *ptmGps;

    ret = gps_get_time(&gpsTime);

    if(ret)
    {
        ptmGps = localtime_r(&gpsTime, &tmGps);
        fprintf(stderr,"============================\n");
        fprintf(stderr, "GPS TIME : [%04d/%02d/%02d %02d:%02d:%02d]\n", tmGps.tm_year+1900, tmGps.tm_mon+1, tmGps.tm_mday, tmGps.tm_hour, tmGps.tm_min, tmGps.tm_sec);
        fprintf(stderr,"============================\n");

        if(utils_cfg_cmp_item(SystemCfg.gps_sync, "ON") == 0)
        {
            if(gpsTime >= RTC_BASE_TIME && gpsTime < RTC_Y2K38_TIME)
            {
                rtc_set_time(gpsTime);
                fprintf(stderr, "Synchronize RTC with GPS time and then Shut down system\n");
            }
        }
    }

    statusBar->hide();

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->systemShutdownIconClean();
    }

    system_state = SYSTEM_SHUTDOWN;
    QTimer::singleShot(500 , this, SLOT(close()));

    return;
}
void MainWidget::ParkingSystem(void)
{
    appmgr_close_sensorlog();
    appmgr_deinit_systemstate(SYSTEM_SHUTDOWN);
    qDebug("Parking System Success!!");
}
void MainWidget::onHideStatusBar(void)
{
    this->StatusBarHide();
}
void MainWidget::onShowStatusBar(void)
{
    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        this->StatusBarShow();
    }
    else if(utils_cfg_cmp_item(DisplayCfg.osd_status, "ON") == 0)
    {
        this->StatusBarHide();
    }
}
void MainWidget::StatusBarHide(void)
{
    if(operationMode == OPMODE_LIVE)
    {
        controlBarAutoHide = 0;

        statusBarEnable = 1;
        playBarEnable   = 1;

        statusBar->hide();

        (void) appmgr_set_control_bar_auto_Hide(controlBarAutoHide);
    }
}
void MainWidget::StatusBarShow(void)
{
    if(operationMode == OPMODE_LIVE)
    {
        controlBarAutoHide = 0;

        statusBarEnable = 1;
        playBarEnable  = 1;

        statusBar->show();

        (void) appmgr_set_control_bar_auto_Hide(controlBarAutoHide);
    }
}
void MainWidget::controlBarAutoHideChange()
{
    if(operationMode != OPMODE_LIVE)
    {
        return;
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        return;
    }

    if(controlBarAutoHide)
    {
        controlBarAutoHide = 0;
    }
    else
    {
        controlBarAutoHide = 1;
    }

    statusBarEnable = 1;
    playBarEnable   = 1;

    statusBar->show();

    (void) appmgr_set_control_bar_auto_Hide(controlBarAutoHide);
}
void MainWidget::controlBarChange()
{
    if(operationMode != OPMODE_LIVE)
    {
        return;
    }

    if(statusBar->isVisible())
    {
        statusBar->hide();
    }
    else
    {
        statusBar->show();
    }

    controlBarAutoHide = 0;
    statusBarEnable    = 1;
    playBarEnable      = 1;
    (void)appmgr_set_control_bar_auto_Hide(controlBarAutoHide);
}
void MainWidget::playBarChange()
{
    if(operationMode != OPMODE_PLAYBACK)
    {
        return;
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        return;
    }

    if(statusBarEnable)
    {
        statusBarEnable = 0;
        playBarEnable   = 0;
        playBar->hide();
    }
    else
    {
        statusBarEnable = 1;
        playBarEnable   = 1;
        playBar->show();
    }

    if(controlBarAutoHide == 0)
    {
        controlBarAutoHide = 1;
        (void) appmgr_set_control_bar_auto_Hide(controlBarAutoHide);
    }
}
void MainWidget::runSetup()
{
    QString          strPassword;

    int              userId                    = 0,
                     OverwriteRecordLimitDays  = 0,
                     overwrite                 = 0,
                     limithour                 = 0,
                     setupReturn               = 0,
                     ii                        = 0;

    unsigned char    pre_record_mode[16];

    if(operationMode != OPMODE_LIVE)
    {
        return;
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        this->StatusBarHide();
    }

    memset(&cfgSetup, 0x0, sizeof(cfg_setup_data_t));
    appmgr_load_run_config(&cfgSetup);

    if(utils_cfg_cmp_item(SystemCfg.system_lock, "YES") == 0)
    {
        if(!checkPassword(CHECK_SETUP, &userId))
        {
            operationMode = OPMODE_LIVE;
            SetOperationMode(operationMode);
            this->onShowStatusBar();
            return;
        }
    }

    operationMode = OPMODE_SETUP;
    SetOperationMode(operationMode);

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Setup Enter");

    latestChannelNum       = currentChannelNum;
    latestSplit            = currentSplit;
    latestSplitStartChNum  = splitStartChNum;
    getConfigString();

    for(ii = 0; ii < devInfo.videoNum; ii++)
    {
        pre_record_mode[ii] = cfgSetup.rec.record_mode[ii];
    }

    if(!setupDialog)
    {
        setupDialog = new SetupDialog(this);

        setupDialog->resize(1280, 720);
        qDebug("setupDialog size ESTN : %d, %d", setupDialog->width(), setupDialog->height());
    }

    appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, audioStatus-2);

    setupDialog->updateConfig(userId);
    setupDialog->move(((appmgr_get_mainwidget_width()-setupDialog->width())/2), ((appmgr_get_mainwidget_height()-setupDialog->height())/2));
    setupReturn = setupDialog->exec();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Setup Exit");

    operationMode = OPMODE_LIVE;
    SetOperationMode(operationMode);

    if(OverwriteRecordLimitDays)
    {
        if(utils_cfg_cmp_item(StorageCfg.overwrite, "ON") == 0)
        {
            overwrite = 0;
        }
        else
        {
            overwrite = 1;
        }

        limithour = 0;

        qDebug("Change OverwriteRecordLimitDays overwrite(%d), limithour(%d) \n", overwrite, limithour);

        appmgr_set_overwrite(overwrite, limithour);
        setStrogeOverwirte();
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        this->StatusBarShow();
    }

    if(audioStatus != LIVE_AUDIO_MUTE)
    {
        appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
    }
}
void MainWidget::runBackup()
{
    int       rv       = 0,
              type     = 0,
              channel  = ver_get_video(),
              split    = ver_get_video();

    time_t    now      = time(NULL);

    backupType         = 0;

    if(operationMode == OPMODE_BACKUP)
    {
        qDebug("%s: running backup.\n", __func__);
        return;
    }

    if(splitFlag)
    {
        fprintf(stderr, "\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        playBar->resumePlayback(0, 0);
        return;
    }

    backupPopupShow = -1;

    if(operationMode != OPMODE_LIVE)
    {
        backupType = 1;
        type       = 1;
        now        = playBar->curPbTime;
    }

    channel = currentChannelNum;
    split   = currentSplit;

    operationMode = OPMODE_BACKUP;
    SetOperationMode(operationMode);

    if(!backupDialog)
    {
        backupDialog = new BackupDialog(this);
    }
    else
    {
        backupDialog->updateBackupDialog();
    }

    qDebug("%s: type.%d, split.%d, channel.%d, timestamp.%s \n", __func__, type, split, channel, atime(now));

    backupDialog->setCaptureMode(type, channel, split, now);

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Backup Enter");

    rv = backupDialog->exec();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Backup Exit");

    if(playBar->indexAudio == 1)
    {
        playBar->OutputAudio(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }
    else
    {
        if(currentSplit == Split_1)
        {
            playBar->OutputAudio(currentChannelNum);
            appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
        }
        else if(currentSplit == Split_4)
        {
            playBar->OutputAudio(playBar->indexAudio-2);
            appmgr_search_set_audio_mute_on_off(AUDIO_PB, playBar->indexAudio-2);
        }
    }

    if(type == 1) 
    {
        if(backupPopupShow == 0)
        {
            backupPopupShow = -1;
            return;
        }
        else
        {
            operationMode = OPMODE_PLAYBACK;
            SetOperationMode(operationMode);
        }

        if(searchDialog->pbType == SEARCH_MENU_EVENT)
        {
            if(searchDialog->recType == RECORD_MOTION || searchDialog->recType == RECORD_SENSOR)
            {
                playBar->resumePlayback(0, 30);
            }
            else
            {
                playBar->resumePlayback(0, 0);
            }
        }
        else
        {
            playBar->resumePlayback(0, 0);
#if 1 // GyverJeong [17/12/05]
            playBar->displaySpeed();
#endif
        }
    }
    else
    {
        if(backupPopupShow == 0)
        {
            backupPopupShow = -1;
            return;
        }
        else
        {
            operationMode = OPMODE_LIVE;
            SetOperationMode(operationMode);
        }
    }
}
void MainWidget::runSearch()
{
    int userId = 0;

    if(operationMode != OPMODE_LIVE)
    {
        return;
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        this->StatusBarHide();
    }

    memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);

    appmgr_get_disk_info(diskInfo);

    if(diskInfo[0].hddCount == 0)
    {
        operationMode = OPMODE_MESSAGE;
        SetOperationMode(operationMode);
        msgBoxEsckey = 1;

        if(!msgBox)
        {
            msgBox = new TextMessageDialog(tr("SEARCH"),
                    tr("WARNING\n\n"
                        "No SSD"),
                    2, this);
            msgBox->setMsgAlignment(Qt::AlignCenter);
        }

        if(msgBox->exec())
        {
            ;
        }

        delete msgBox;
        msgBox = NULL;

        msgBoxEsckey  = 0;
        operationMode = OPMODE_LIVE;
        SetOperationMode(operationMode);
        return;
    }

    if(utils_cfg_cmp_item(SystemCfg.system_lock, "YES") == 0)
    {
        if(!checkPassword(CHECK_SEARCH, &userId))
        {
            operationMode = OPMODE_LIVE;
            SetOperationMode(operationMode);
            this->onShowStatusBar();
            return;
        }
    }

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
    }

    appmgr_set_zoom(0, 0, 0, 0);

    operationMode = OPMODE_SEARCH;
    SetOperationMode(operationMode);

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Search Enter");

    if(!searchDialog)
    {
        searchDialog = new SearchDialog(this);
    }

    appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, audioStatus-2);

    searchDialog->buttonNormal->setFocus();
    searchDialog->move((appmgr_get_mainwidget_width() - searchDialog->size().width())/2, (appmgr_get_mainwidget_height() - searchDialog->size().height()) / 2);

    if(searchDialog->exec())
    {
        startPlayback();
    }
    else
    {
        for(int i = 0; i < devInfo.videoNum; i++)
        {
            videoPane[i]->zoomAction = false;
        }

        appmgr_set_zoom(0, 0, 0, 0);

        searchDialog->buttonNormal->setFocus();

        operationMode = OPMODE_LIVE;
        SetOperationMode(operationMode);

        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Search Exit");

        if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
        {
            this->StatusBarShow();
        }

        if(audioStatus != LIVE_AUDIO_MUTE)
        {
            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
            videoPane[audioStatus-2]->setAudioOutput(1);
        }
    }

    noDataUpdate(1);
}
void MainWidget::startPlayback()
{
    int i = 0;

#if 1 // GyverJeong [17/12/04]
    if(playBar->isHidden())
    {
        playBarState(1);
        appmgr_set_playber_bar_status(1);
    }
    else if(playBar->isVisible())
    {
        playBarState(0);
        appmgr_set_playber_bar_status(0);
    }
#endif
    for(i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
    }

    appmgr_set_zoom(0, 0, 0, 0);

    search_playback_start = 1;

    operationMode = OPMODE_PLAYBACK;
    SetOperationMode(operationMode);

    for(i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->setPlaybackMode(1);
    }

    statusBar->hide();

    latestChannelNum       = currentChannelNum;
    latestSplit            = currentSplit;
    latestSplitStartChNum  = splitStartChNum;

    if(searchDialog)
    {
        qDebug("\n\t START	 startPlayback -> setSplitScreen");

        for(i = 0; i < devInfo.videoNum; i++)
        {
            if(searchDialog->pbChBit & ( 1 << i))
            {
                break;
            }
        }

        qDebug("\n\t END    startPlayback -> setSplitScreen");

        if(searchDialog)
        {
            setSplitScreen(i, i, searchDialog->pbSplit);
            appmgr_search_play_start_real();

            playBar->setMaxSplit(i, searchDialog->pbSplit);

        }
    }

    playBar->setTimeFormat(DateFormat);
    playBar->show();
    playBar->raise();
    playBar->activateWindow();
    playBar->updateTimeLine();

    search_playback_start = 0;
}
void MainWidget::stopPlayback()
{
    int i = 0;

    for(i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->setZoomOut();
    }

    appmgr_set_zoom(0, 0, 0, 0);

    appmgr_search_stop();
    operationMode = OPMODE_SEARCH;
    SetOperationMode(operationMode);

    for(i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->setPlaybackMode(0);
    }

    playBar->hide();

    qDebug("         stopPlayback -> setSplitScreen");

    splitFlag = 0;
    setSplitScreen(latestSplitStartChNum, latestChannelNum, latestSplit);

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "ON") == 0)
    {
        if(statusBarEnable)
        {
            statusBar->show();
        }

        statusBar->raise();
        statusBar->activateWindow();
    }

    noDataUpdate(1);

    if(!searchDialog)
    {
        searchDialog = new SearchDialog(this);
    }

    int res = searchDialog->exec();

    if(res == -1)
    {
        fprintf(stderr, "\n\n\t %s(), QDialog::exec: Recursive call detected res = %d \n", __func__, res);
    }
    else if(res)
    {
        startPlayback();
    }
    else
    {
        for(i = 0; i < devInfo.videoNum; i++)
        {
            videoPane[i]->labelNameEnable(1);
        }

        for(i = 0; i < devInfo.videoNum; i++)
        {
            videoPane[i]->zoomAction = false;
        }

        appmgr_set_zoom(0, 0, 0, 0);

        operationMode = OPMODE_LIVE;
        SetOperationMode(operationMode);

        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Search Exit");

        if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
        {
            this->StatusBarShow();
        }

        if(audioStatus != LIVE_AUDIO_MUTE)
        {
            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
            videoPane[audioStatus-2]->setAudioOutput(1);
        }

    }
    noDataUpdate(1);
}
void MainWidget::playbackOneChannel(int ch)
{
    currentChannelNum = ch;

    if(currentSplit == Split_1)
    {
        currentSplit = Split_4;
    }

    splitScreen(Split_1);
}
void MainWidget::systemReboot()
{
    if(system_state != SYSTEM_BOOTING_FORMAT)
    {
        statusBar->hide();

        for(int ch = 0; ch < devInfo.videoNum; ch++)
        {
            videoPane[ch]->systemShutdownIconClean();
        }
    }

    this->Delay(2000);
    appmgr_reboot_system(system_state);

    return;
}
void MainWidget::splitChannelBySetup(int ch)
{
    qDebug("splitChannelBySetup : %d", ch);

    if(ch >= 0)
    {
        oneChannelSplit(ch);
    }
    else
    {
        setSplitScreen(latestSplitStartChNum, latestChannelNum, latestSplit);
    }
}
void MainWidget::setOverwrite()
{
    int overwrite = 0, limithour = 0;

    if(utils_cfg_cmp_item(StorageCfg.overwrite, "ON") == 0)
    {
        overwrite = 0;
    }
    else
    {
        overwrite = 1;
    }

    limithour = 0;

    qDebug("\t Init OverwriteRecordLimitDays overwrite(%d), limithour(%d) \n", overwrite, limithour);

    appmgr_set_overwrite(overwrite, limithour);
    setStrogeOverwirte();
}
void MainWidget::setDateFormat()
{
    if(utils_cfg_cmp_item(SystemCfg.date_format, "YYYY/MM/DD") == 0)
    {
        DateFormat = 0;
    }
    else if(utils_cfg_cmp_item(SystemCfg.date_format, "MM/DD/YYYY") == 0)
    {
        DateFormat = 1;
    }
    else if(utils_cfg_cmp_item(SystemCfg.date_format, "DD/MM/YYYY") == 0)
    {
        DateFormat = 2;
    }
    else if(utils_cfg_cmp_item(SystemCfg.date_format, "YYYY-MM-DD") == 0)
    {
        DateFormat = 3;
    }
    else if(utils_cfg_cmp_item(SystemCfg.date_format, "MM-DD-YYYY") == 0)
    {
        DateFormat = 4;
    }
    else if(utils_cfg_cmp_item(SystemCfg.date_format, "DD-MM-YYYY") == 0)
    {
        DateFormat = 5;
    }
    else
    {
        DateFormat = 0;
    }
}
void MainWidget::setStrogeOverwirte()
{
	if(utils_cfg_cmp_item(StorageCfg.overwrite, "ON") == 0)
    {
        StorageOverwrite = 1;
    }
	else
    {
        StorageOverwrite = 0;
    }

	if(utils_cfg_cmp_item(StorageCfg.recording_limit, "ON") == 0)
    {
        StorageRecordingLimit = 1;
    }
	else
    {
        StorageRecordingLimit = 0;
    }
}
void MainWidget::ResolutionChange(int hdmi)
{
    QScreen *screen      = QScreen::instance();
    bool     playBarOn   = false;
    bool     statusBarOn = false;

    if(hdmi)
    {
        screen->setMode (1280, 720, 16);
    }
    else
    {
        screen->setMode (1280, 1024, 16);
    }

    qDebug("\n\n\t ResolutionChange() width = %d, height = %d \n", screen->width(), screen->height());

    mainWidth  = screen->width();
    mainHeight = screen->height();

    appmgr_set_mainwidget_size(mainWidth, mainHeight);
    appmgr_set_screen_size(mainWidth, mainHeight);

    qDebug("size %d, %d\n", mainWidth, mainHeight);

    if(playBar->isHidden() == 0)
    {
        playBarOn = true;
    }

    if(statusBar->isHidden() == 0)
    {
        statusBarOn = true;
    }

    statusBar->hide();
    playBar->hide();

    statusBar->move((mainWidth - statusBar->width()) / 2, mainHeight - statusBar->height());
    playBar->move((mainWidth   - playBar->width())   / 2, mainHeight - playBar->height());

    if(operationMode == OPMODE_PLAYBACK)
    {
        if(playBarEnable == 1)
        {
            playBar->show();
            playBar->raise();
            playBar->activateWindow();
        }
    }
    else if(operationMode == OPMODE_BACKUP)
    {
        if(playBarOn == true)
        {
            playBar->show();
            playBar->raise();
            playBar->activateWindow();
        }
        else if(statusBarOn == true)
        {
            statusBar->show();
            statusBar->raise();
            statusBar->activateWindow();
        }
    }
    else
    {
        if(statusBarEnable == 1)
        {
            statusBar->show();
            statusBar->raise();
            statusBar->activateWindow();
        }
    }

    if(operationMode == OPMODE_SETUP)
    {
        setupDialog->move((mainWidth  - setupDialog->size().width())  / 2, (mainHeight - setupDialog->size().height())  / 2);
    }
    else if(operationMode == OPMODE_BACKUP)
    {
        backupDialog->move((mainWidth - backupDialog->size().width()) / 2, (mainHeight - backupDialog->size().height()) / 2);
    }
    else if(operationMode == OPMODE_SEARCH)
    {
        searchDialog->move((mainWidth - searchDialog->size().width()) / 2, (mainHeight - searchDialog->size().height()) / 2);
    }
    else if(operationMode == OPMODE_LOGIN)
    {
        loginDialog->move((mainWidth  - loginDialog->size().width())  / 2, (mainHeight - loginDialog->size().height())  / 2);
    }

    resize(mainWidth, mainHeight);

    setSplitScreen(splitStartChNum, currentChannelNum, currentSplit);
}
void MainWidget::translatorChange(int lang)
{
    time_t now;
    int fontsize = 20;

    if(lang < 0 || lang > LANGUAGE_MAX)
    {
        return;
    }

    if(loadedLanguage == lang)
    {
        return;
    }

    now = time(0);
    qDebug("translatorChange loadedLanguage(%d), lang(%d) \n", loadedLanguage, lang);

    if(selTranslator)
    {
        QCoreApplication::removeTranslator(selTranslator);
        delete selTranslator;
        selTranslator = NULL;
    }

    loadedLanguage = -1;

    selTranslator = new QTranslator;

    fontsize = 20;

    QFont myfont("unifont");
    myfont.setPointSize(fontsize);
    qDebug(" ================== UniFont ============== ");
    QApplication::setFont(myfont);

    if(lang == LANGUAGE_ENGLISH)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_english");
            qDebug("load English from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_english");
            qDebug("load English");
        }
    }
    else if(lang == LANGUAGE_KOREAN)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_korean");
            qDebug("load Korean from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_korean");
            qDebug("load Korean");
        }
    }
    else if(lang == LANGUAGE_SPANISH)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_spanish");
            qDebug("load Spanish from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_spanish");
            qDebug("load Spanish");
        }
    }
    else if(lang == LANGUAGE_FRENCH)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_french");
            qDebug("load French from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_french");
            qDebug("load French");
        }
    }
    else if(lang == LANGUAGE_ITALIAN)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_italian");
            qDebug("load Italian from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_italian");
            qDebug("load Italian");
        }
    }
    else if(lang == LANGUAGE_PORTUGUESE)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_portuguese");
            qDebug("load Portuguese from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_portuguese");
            qDebug("load Portuguese");
        }
    }
    else if(lang == LANGUAGE_JAPANESE)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_japanese");
            qDebug("load Japanese from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_japanese");
            qDebug("load Japanese");
        }
    }
    else if(lang == LANGUAGE_GERMAN)
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_german");
            qDebug("load German from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_german");
            qDebug("load German");
        }
    }
    else
    {
        if(access("/tmp/eastern", F_OK) == 0)
        {
            selTranslator->load("/tmp/eastern/usr/lib/translator/language_english");
            qDebug("load English from nfs");
        }
        else
        {
            selTranslator->load("./translator/language_english");
            qDebug("load English");
        }
        selTranslator->load("./translator/language_english");
        qDebug("unknown language(%d)selected....load english", lang);
        lang = 0;
    }

    QCoreApplication::installTranslator(selTranslator);
    loadedLanguage = lang;

}
int MainWidget::LanguageValueTransformation(void)
{
    int val = LANGUAGE_ENGLISH;

    aif_system_get_property(&SystemCfg);

    if(utils_cfg_cmp_item(SystemCfg.language, "ENGLISH") == 0)
    {
        val = LANGUAGE_ENGLISH;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "KOREAN")  == 0)
    {
        val = LANGUAGE_KOREAN;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH")  == 0)
    {
        val = LANGUAGE_SPANISH;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH")  == 0)
    {
        val = LANGUAGE_FRENCH;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN")  == 0)
    {
        val = LANGUAGE_ITALIAN;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE")  == 0)
    {
        val = LANGUAGE_PORTUGUESE;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE")  == 0)
    {
        val = LANGUAGE_JAPANESE;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN")  == 0)
    {
        val = LANGUAGE_GERMAN;
    }

    return val;
}
void MainWidget::statusBarState(int state)
{
    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "ON") == 0)
    {
        if(state)
        {
            if(statusBar->isHidden() == 1)
            {
                statusBarEnable = 1;
                statusBar->show();
            }
        }
        else
        {
            if(statusBar->isHidden() == 0)
            {
                statusBarEnable = 0;
                statusBar->hide();
            }
        }
    }
}
void MainWidget::playBarState(int state)
{
    if(state)
    {
        if(playBar->isHidden() == 1)
        {
            playBarEnable = 1;
            playBar->show();
        } 
    }
    else
    {
        if(playBar->isHidden() == 0)
        {
            playBarEnable = 0;
            playBar->hide();
            noDataUpdate(0);
        } 
    }
}
void MainWidget::SetOperationMode(int mode)
{
    if(mode == OPMODE_LIVE)
    {
        noDataUpdate(1);
    }

    appmgr_set_operationMode(mode);
}
void MainWidget::DiskFormatProcessDlgOpen()
{
    if(!diskformatprocessDialog)
    {
        diskformatprocessDialog = new DiskFormatProcessDialog(this);

        connect(this, SIGNAL(diskformatProgress(int, unsigned long, unsigned long, unsigned long)), diskformatprocessDialog, SLOT(onDiskFormatupdateprocess(int, unsigned long, unsigned long, unsigned long)));
        connect(this, SIGNAL(diskformatEnd()), diskformatprocessDialog, SLOT(onDiskFormatupdateEnd()));
        connect(diskformatprocessDialog, SIGNAL(diskformatReboot()), this, SLOT(DiskFormatSystemReboot()));
    }

    diskformatprocessDialog->move((appmgr_get_mainwidget_width()-diskformatprocessDialog->sizeHint().width())/2,(appmgr_get_mainwidget_height()-diskformatprocessDialog->sizeHint().height())/2);

    diskformatprocessDialog->DiskFormatInit();

    diskformatprocessDialog->StartFormat();

    if(diskformatprocessDialog->exec())
    {
        ;
    }
}
void MainWidget::Delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void MainWidget::DiskFormatSystemReboot()
{
    if(diskformatprocessDialog)
    {
        delete diskformatprocessDialog;
        diskformatprocessDialog = NULL;
    }

    if(appmgr_get_format_result() == 0) // Fail, It will retry a disk format after reserves more memory
    {
        utils_set_disk_format(1);
    }
    else // Success
    {
        utils_set_disk_format(0);
    }

    system_state = SYSTEM_BOOTING_FORMAT;
    systemReboot();
}
void MainWidget::DiskFormatSystemShutdown()
{
    if(diskformatprocessDialog)
    {
        delete diskformatprocessDialog;
        diskformatprocessDialog = NULL;
    }

    appmgr_format_cancel_and_reboot();
}
void MainWidget::setConfigString()
{
    appmgr_get_cfg_display();

    aif_system_set_property(&SystemCfg);
    aif_record2_set_property(&RecordCfg);
    aif_storage_set_property(&StorageCfg);
    aif_storage_get_property(&StorageCfgTemp);
    aif_display_set_property(&DisplayCfg);
    aif_device_set_property(&DeviceCfg);
}
void MainWidget::getConfigString()
{
    aif_system_get_property(&SystemCfg);
    aif_record2_get_property(&RecordCfg);
    aif_storage_get_property(&StorageCfg);
    aif_storage_get_property(&StorageCfgTemp);
    aif_display_get_property(&DisplayCfg);
    aif_device_get_property(&DeviceCfg);
}	
void MainWidget::noDataUpdate(int live)
{	
    int i = 0, cur = 0;

    if(live)
    {
        mainPbChannel = - 1;

        for(i = 0; i < devInfo.videoNum; i++)
        {
            videoPane[i]->setNoRecordVideoDetect(0);
            cur = (liveEvent.cameraLoss & (1<<i));
            videoPane[i]->setVideoLossDetect(cur);
        }
    }
    else
    {
        for(int i = 0; i < devInfo.videoNum; i++)
        {
            if(mainPbChannel & (0x01 << i))
            {
                videoPane[i]->setNoRecordVideoDetect(0);
            }
            else
            {
                videoPane[i]->setNoRecordVideoDetect(1);
            }
        }
    }
}
void MainWidget::onSetAudioMute()
{
    for(int ch = 0; ch < devInfo.videoNum; ch++)
    {
        videoPane[ch]->setAudioOutput(0);
    }

    if(operationMode == OPMODE_PLAYBACK || operationMode == OPMODE_BACKUP)
    {
        return;
    }

    audioStatus          = LIVE_AUDIO_MUTE;
    cfgMain.gbl.audioOut = audioStatus;

    appmgr_save_setup(3, &cfgMain);

    (void) utils_set_audio_output(LIVE_AUDIO_MUTE);

    appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, currentChannelNum);
}
void MainWidget::onSetAudio1()
{
    for(int ch = 0; ch < devInfo.videoNum; ch++)
    {
        videoPane[ch]->setAudioOutput(0);
    }
    videoPane[0]->setAudioOutput(1);

    if(operationMode == OPMODE_PLAYBACK || operationMode == OPMODE_BACKUP)
    {
        return;
    }

    audioStatus          = LIVE_AUDIO_SINGLE_1;
    cfgMain.gbl.audioOut = audioStatus;

    appmgr_save_setup(3, &cfgMain);

    (void) utils_set_audio_output(LIVE_AUDIO_SINGLE_1);

    appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
}
void MainWidget::onSetAudio2()
{
    for(int ch = 0; ch < devInfo.videoNum; ch++)
    {
        videoPane[ch]->setAudioOutput(0);
    }
    videoPane[1]->setAudioOutput(1);

    if(operationMode == OPMODE_PLAYBACK || operationMode == OPMODE_BACKUP)
    {
        return;
    }

    audioStatus          = LIVE_AUDIO_SINGLE_2;
    cfgMain.gbl.audioOut = audioStatus;

    appmgr_save_setup(3, &cfgMain);

    (void) utils_set_audio_output(LIVE_AUDIO_SINGLE_2);

    appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
}
void MainWidget::onSetAudio3()
{
    for(int ch = 0; ch < devInfo.videoNum; ch++)
    {
        videoPane[ch]->setAudioOutput(0);
    }
    videoPane[2]->setAudioOutput(1);

    if(operationMode == OPMODE_PLAYBACK || operationMode == OPMODE_BACKUP)
    {
        return;
    }

    audioStatus          = LIVE_AUDIO_SINGLE_3;
    cfgMain.gbl.audioOut = audioStatus;

    appmgr_save_setup(3, &cfgMain);

    (void) utils_set_audio_output(LIVE_AUDIO_SINGLE_3);

    appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
}
void MainWidget::onSetAudio4()
{
    for(int ch = 0; ch < devInfo.videoNum; ch++)
    {
        videoPane[ch]->setAudioOutput(0);
    }
    videoPane[3]->setAudioOutput(1);

    if(operationMode == OPMODE_PLAYBACK || operationMode == OPMODE_BACKUP)
    {
        return;
    }

    audioStatus          = LIVE_AUDIO_SINGLE_4;
    cfgMain.gbl.audioOut = audioStatus;

    appmgr_save_setup(3, &cfgMain);

    (void) utils_set_audio_output(LIVE_AUDIO_SINGLE_4);

    appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
}
void MainWidget::setAudioOut()
{
    fprintf(stderr, "new setAudioOut() audioStatus = %d \n", audioStatus);

    audioStatus++;

    if(audioStatus == LIVE_AUDIO_MIX)
    {
        audioStatus = LIVE_AUDIO_SINGLE_1;
    }

    if(audioStatus > devInfo.audioNum + 1)
    {
        audioStatus = LIVE_AUDIO_MUTE;
    }

    switch(audioStatus)
    {
        case LIVE_AUDIO_MUTE:     { onSetAudioMute(); break; }
        case LIVE_AUDIO_SINGLE_1: { onSetAudio1();    break; }
        case LIVE_AUDIO_SINGLE_2: { onSetAudio2();    break; }
        case LIVE_AUDIO_SINGLE_3: { onSetAudio3();    break; }
        case LIVE_AUDIO_SINGLE_4: { onSetAudio4();    break; }
    }
}
void MainWidget::setAudioMode()
{
    fprintf(stderr, "new setAudioMode() audioStatus = %d \n", audioStatus);

    switch(audioStatus)
    {
        case LIVE_AUDIO_MUTE:     { onSetAudioMute(); break; }
        case LIVE_AUDIO_SINGLE_1: { onSetAudio1();    break; }
        case LIVE_AUDIO_SINGLE_2: { onSetAudio2();    break; }
        case LIVE_AUDIO_SINGLE_3: { onSetAudio3();    break; }
        case LIVE_AUDIO_SINGLE_4: { onSetAudio4();    break; }
    }
}
void MainWidget::setAudioOutCh(int ch)
{
    switch(ch)
    {
        case LIVE_AUDIO_MUTE:     { onSetAudioMute(); break; }
        case LIVE_AUDIO_SINGLE_1: { onSetAudio1();    break; }
        case LIVE_AUDIO_SINGLE_2: { onSetAudio2();    break; }
        case LIVE_AUDIO_SINGLE_3: { onSetAudio3();    break; }
        case LIVE_AUDIO_SINGLE_4: { onSetAudio4();    break; }
        default :   { onSetAudioMute(); break; }
    }
}
