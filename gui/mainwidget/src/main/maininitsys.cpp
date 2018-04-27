#include <QtGui>
#include "mainwidget.h"
#include "statusbardialog.h"
#include "videopane.h"
#include "firstcheck/timesetdialog.h"
#include "firstcheck/rtcsetdialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "login/logindialog.h"
#include "mainglobal.h"
#include "languagedefine.h"
#include "DVR.h"
#include "dev/Ver.h"
#include "utils/utils.h"

int MainWidget::loadData()
{
    int ch = 0, ret = 0;
    int arVIS[MAX_VIDEO_CH];

    // CAUTION!!!! - devInfo is Read Only !!!! Don't modify the value of devInfo
    memset(&devInfo, 0, sizeof(cfg_dvr_device_info_t));
    appmgr_get_device_info(&devInfo);

    memset(&cfgSetup, 0, sizeof(cfg_setup_data_t));
    memset(&cfgMain, 0,  sizeof(cfg_setup_data_t));

    ret = appmgr_get_config(&cfgSetup);

    ver_get_vis_list(arVIS);

    for(ch = 0; ch < MAX_VIDEO_CH; ch++)
    {
        if(arVIS[ch] == ver_vis_hd_720_25p || arVIS[ch] == ver_vis_hd_720_50p || arVIS[ch] == ver_vis_hd_720_30p || arVIS[ch] == ver_vis_hd_720_60p)
        {
            if(cfgSetup.rec.record_main.resolution[ch] == RESOLUTION_HD_1920x1080)
            {
                cfgSetup.rec.record_main.resolution[ch] = RESOLUTION_HD_1280x720;
            }

            if(cfgSetup.rec.record_main.resolution[ch] == RESOLUTION_HD_1920x540)
            {
                cfgSetup.rec.record_main.resolution[ch] = RESOLUTION_HD_640x360;
            }
        }

        if(arVIS[ch] == ver_vis_hd_720_25p  || arVIS[ch] == ver_vis_hd_720_50p || arVIS[ch] == ver_vis_hd_1080_25p || arVIS[ch] == ver_vis_hd_1080_i50)
        {
            if(cfgSetup.rec.record_main.fr_hd[ch] == 30)
            {
                cfgSetup.rec.record_main.fr_hd[ch] = 25;
            }
        }
    }

    memcpy(&cfgMain, &cfgSetup, sizeof(cfg_setup_data_t));
    appmgr_save_setup(3, &cfgMain);

    qDebug("load config : ret %d\n", ret);

    translatorChange(LanguageValueTransformation());

    calSelTime = eventLogSelTime = archiveLogSelTime = timeLogSelTime = syslogSelTime = 0;

    eventLogCount = calDataCount = 0;

    memset(timeLog, 0, sizeof(struct _time_search_info_ext) * 25);
    memset(eventLog, 0, sizeof(struct _eventlog_info) * MAX_EVENT_SEARCH_LOG);
    memset(calendarData, 0, sizeof(struct _caldata) * MAX_CAL_MONTH_DATA);
    memset(&liveEvent, 0, sizeof(live_event_t));
    memset(&dlsLive, 0, sizeof(_dls_convert_info));
    memset(&dlsPlayback, 0, sizeof(_dls_convert_info));

    appmgr_make_dls_time_info(0, 1, &dlsLive); // get current year dls info

    return ret;
}
void MainWidget::initializeSystem()
{
    int               ret                  = 0;
    bool              isFormat             = 1;
    int               lang                 = 0;
    time_t            now                  = 0;
    struct tm         when;
    struct timeval    dvrtime;

    qDebug("\n\n\t initializeSystem() +++++ \n");

    appmgr_watchdog_disable();

    // Check Rtc Init Error
    if(appmgr_get_rtc_init_state() != 0)
    {
        qDebug("\n\n\t RTC Init Error !!! \n");

        operationMode = OPMODE_FIRSTRUN;
        SetOperationMode(operationMode);

        if(!rtcSetDialog)
        {
            rtcSetDialog = new RtcSetDialog();
        }

        rtcSetDialog->move((appmgr_get_mainwidget_width()-rtcSetDialog->width())/2, (appmgr_get_mainwidget_height()-rtcSetDialog->height())/2);

        appmgr_set_beep_duration(BEEP_DURATION_MAX);

        if(rtcSetDialog->exec())
        {
            rtcSetDialog->GetTime(&now);

            delete rtcSetDialog;
            rtcSetDialog = NULL;

            qDebug("\n\n\t RTC Init Error: System Reboot, time=[%s]\n", ctime(&now));
            appmgr_set_beep_duration(0);
            appmgr_firstrun_setting(now, LanguageValueTransformation());
            appmgr_reboot_system(0);
            return;
        }
    }

    appmgr_wait_diskmgr_boot();
    appmgr_wait_diskmgr_disk_state();

#if 1 // jungyver [17/07/04] Display hexa code when occuring disk status temporarily
    int rv = appmgr_get_boot_disk_state();
    switch(rv)
#else
    switch(appmgr_get_boot_disk_state())
#endif
    {
        case DS_CODE_HDD_NOT_FOUND:

            break;

#if 1 // GyverJeong [18/04/08] Format a storage over ESC key on remote controller during booting
        case DS_CODE_HDD_FORMAT_NEED:

            if(msgBox == NULL)
            {
                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"),tr("%1\n\n%2").arg(tr("WARNING"), tr("Do you want to format the storage?")), 0, this);
                msgBox->setMsgAlignment(Qt::AlignCenter);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
            }

            if(msgBox->exec())
            {
                if(utils_cfg_cmp_item(SystemCfg.system_lock, "YES") == 0)
                {
                    int userId = 0;

                    if(checkPassword(CHECK_FORMAT, &userId) == 0)
                    {
                        isFormat = 0;
                    }
                }

                if(isFormat)
                {
                    DiskFormatNum  = 0;
                    DiskFormatNum |= (1 << 0);
                    DiskFormatProcessDlgOpen();
                }
            }
            else
            {
                isFormat = 0;
            }

            if(isFormat == 0)
            {
                delete msgBox;
                msgBox = NULL;

                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"),tr("%1\n\n%2").arg(tr("NOTICE"),tr("System will restart.")), 3, this);
                msgBox->setMsgAlignment(Qt::AlignCenter);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
                msgBox->exec();
            }

            delete msgBox;
            msgBox = NULL;

            appmgr_reboot_system(0);

            return;
#endif

        case DS_CODE_FILESYSTEM_BROKEN:
        case DS_CODE_HDD_FORMAT_START:
        case DS_CODE_SERIAL_MISMATCH:
        case DS_CODE_BAD_MAGIC:
        case DS_CODE_DATA_OLD:
        case DS_CODE_MASTER_MOVED:

            if(msgBox == NULL)
            {
#if 1 // jungyver [17/07/04] Display hexa code when occuring disk status temporarily
                QString ss = QString("0x%1").arg(rv, 4, 16, QLatin1Char('0'));
                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"),tr("%1\n\n%2 (%3)\n%4").arg(tr("WARNING"),
                            tr("Storage was not formatted."),
                            tr(ss.toStdString().c_str()),
                            tr("Do you want to format the storage?")), 0, this);
#else
                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"),tr("%1\n\n%2\n%3").arg(tr("WARNING"),
                            tr("Storage was not formatted.         "),
                            tr("Do you want to format the storage?")), 0, this);
#endif

                msgBox->setMsgAlignment(Qt::AlignCenter);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
            }

            if(msgBox->exec())
            {
                DiskFormatNum = 0;
                DiskFormatNum |= (1 << 0);
                DiskFormatProcessDlgOpen();
            }
#if 1 // GyverJeong [18/04/13]
            else
            {
                delete msgBox;
                msgBox = NULL;

                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"),tr("%1\n\n%2").arg(tr("NOTICE"),tr("System will restart.")), 3, this);
                msgBox->setMsgAlignment(Qt::AlignCenter);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
                msgBox->exec();
            }
#endif

            delete msgBox;
            msgBox = NULL;

            appmgr_reboot_system(0);

            return;

        case DS_CODE_HDD_FORMAT_END:

            break;

        case DS_CODE_BAD_FILESYSTEM:

            if(msgBox == NULL)
            {
                msgBox = new TextMessageDialog(tr("STORAGE STATUS"), tr("[5014] Broken Filesystem"), 2, this);
            }

            ret = msgBox->exec();

            if(ret)
            {
                appmgr_reboot_system(0);
                return;
            }

            delete msgBox;
            msgBox = NULL;

            break;

        case DS_CODE_MASTER_NOT_FOUND:

            if(msgBox == NULL)
            {
#if 1 // jungyver [17/07/04] Display hexa code when occuring disk status temporarily
                QString ss = QString("0x%1").arg(rv, 4, 16, QLatin1Char('0'));
                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"),tr("%1\n\n%2 (%3)\n%4").arg(tr("WARNING"),
                            tr("Storage was not formatted."),
                            tr(ss.toStdString().c_str()),
                            tr("Do you want to format the storage?")), 0, this);
#else
                msgBox = new TextMessageDialog(tr("STORAGE FORMAT"), tr("%1\n\n%2\n%3").arg(tr("WARNING"),
                            tr("Storage was not formatted.         "),
                            tr("Do you want to format the storage?")), 0, this);
#endif

                msgBox->setMsgAlignment(Qt::AlignCenter);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
            }

            if(msgBox->exec())
            {
                DiskFormatNum = 0;
                DiskFormatNum |= (1 << 0);
                DiskFormatProcessDlgOpen();
            }

            delete msgBox;
            msgBox = NULL;

            appmgr_reboot_system(0);

            return;

        case DS_CODE_DATA_LOST:

            if(msgBox == NULL)
            {
                msgBox = new TextMessageDialog(tr("STORAGE STATUS"), tr("[5042] Data Lost"), 2, this);
            }

            ret = msgBox->exec();

            if(ret)
            {
                appmgr_reboot_system(0);
                return;
            }

            delete msgBox;
            msgBox = NULL;

            break;

        case DS_CODE_HDD_INSERTED:

            if(msgBox == NULL)
            {
                msgBox = new TextMessageDialog(tr("STORAGE STATUS"), tr("[5070] New HDD Inserted"), 2, this);
            }

            ret = msgBox->exec();

            if(ret)
            {
                appmgr_reboot_system(0);
                return;
            }

            delete msgBox;
            msgBox = NULL;

            break;

        case DS_CODE_SLAVE_CHANGED:

            if(msgBox == NULL)
            {
                msgBox = new TextMessageDialog(tr("STORAGE STATUS"), tr("[5072] Slave HDD Changed"), 2, this);
            }

            ret = msgBox->exec();

            if(ret)
            {
                appmgr_reboot_system(0);
                return;
            }

            delete msgBox;
            msgBox = NULL;

            break;
    }

    appmgr_wait_diskmgr_filesystem_init(1, 0);

    if(appmgr_get_boot_fs_state() == FS_TIME_MISMATCH)
    {
        if(timeSetDialog == NULL)
        {
            timeSetDialog = new TimeSetDialog();
        }

        timeSetDialog->move((appmgr_get_mainwidget_width()-timeSetDialog->width())/2,(appmgr_get_mainwidget_height()-timeSetDialog->height())/2);
        timeSetDialog->DisplayRecordTime();

        operationMode = OPMODE_FIRSTRUN;
        SetOperationMode(operationMode);

        appmgr_set_beep_duration(BEEP_DURATION_MAX);
        timeSetDialog->exec();

        delete timeSetDialog;
        timeSetDialog = NULL;
        appmgr_set_beep_duration(0);
    }

    appmgr_wait_diskmgr_filesystem_init(0, 1);

    if(appmgr_get_boot_fs_state() == FS_DISK_DETACH)
    {
        qDebug("\n\t File System Disk Detach");
        appmgr_reboot_system(0);
    }

    appmgr_wait_diskmgr_filesystem_init(0, 0);

    qDebug("initializeSystem !!!!!!!!!!!!\n");

    if(isfactoryDefault < 0)
    {
        qDebug("Warning... load config failed????? \n");
    }
    else if(isfactoryDefault == 1) // factory default
    {
        operationMode = OPMODE_FIRSTRUN;
        SetOperationMode(operationMode);

        utils_cfg_cpy_item(SystemCfg.language, "ENGLISH");
        aif_system_set_property(&SystemCfg);
        now  = 0;
        lang = LANGUAGE_ENGLISH;
        appmgr_firstrun_setting(now, lang);
    }
    else
    {
        gettimeofday(&dvrtime, NULL);
        localtime_r(&dvrtime.tv_sec, &when);

        fprintf(stderr, "Current time is %d-%d-%d %d:%d\n",when.tm_year,  when.tm_mon, when.tm_mday, when.tm_hour, when.tm_min);

        if(when.tm_year <= 100 && when.tm_mon == 0 && when.tm_mday == 1 && when.tm_hour == 0)
        {
            fprintf(stderr, "Replace battery");

            operationMode = OPMODE_FIRSTRUN;
            SetOperationMode(operationMode);

            if(!rtcSetDialog)
            {
                rtcSetDialog = new RtcSetDialog();
            }

            rtcSetDialog->move((appmgr_get_mainwidget_width()-rtcSetDialog->width())/2, (appmgr_get_mainwidget_height()-rtcSetDialog->height())/2);

            appmgr_set_beep_duration(BEEP_DURATION_MAX);

            if(rtcSetDialog->exec())
            {
                rtcSetDialog->GetTime(&now);
            }

            delete rtcSetDialog;
            rtcSetDialog = NULL;

            qDebug("\n\n\t RTC Init Error: System Reboot: %d, time=[%s]\n", __LINE__, ctime(&now));

            appmgr_set_beep_duration(0);
            appmgr_firstrun_setting(now, -1);
        }
    }

    getConfigString();

    createStatusBar(0);
    createPlayBar(); 
    createMainMenu();

    isShowOsd = 2;
    showOsd(0);

    operationMode = OPMODE_INIT;
    SetOperationMode(operationMode);

    appmgr_watchdog_enable();

    appmgr_start_system();

    showOsd(cfgMain.live.osd_status);

    if(devInfo.videoNum == 4)
    {
        splitScreen(Split_4);
    }
    else if(devInfo.videoNum == 8 || devInfo.videoNum == 9)
    {
        splitScreen(Split_9);
    }
    else  if(devInfo.videoNum == 10)
    {
        splitScreen(Split_10);
    }
    else  if(devInfo.videoNum == 16)
    {
        splitScreen(Split_16);
    }
    else
    {
        splitScreen(Split_1);
    }

    update();
    qDebug("show osd %d", cfgMain.live.osd_status);

    //qDebug(".......................... done");
    appmgr_start_system_done();
    appmgr_record_start();
    operationMode = OPMODE_LIVE;
    SetOperationMode(operationMode);

    audioStatus = cfgMain.gbl.audioOut;

    setAudioMode();

    (void) utils_set_audio_output(audioStatus);

    if(audioStatus == LIVE_AUDIO_MUTE)
    {
        appmgr_set_audio_output_mix(AUDIO_PB, currentChannelNum);
    }
    else
    {
        appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
    }

    setOverwrite();

    if(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF") == 0)
    {
        this->StatusBarShow();
    }
    else
    {
        this->StatusBarHide();
    }

    systemLocked = 0;

    if(cfgMain.gbl.lock)
    {
        systemLocked = 1;
        qDebug("\t system Lock %d\n", systemLocked);
    }

    memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);
    appmgr_get_disk_info(diskInfo);
    qDebug("%s: disk state(%x), hdd cnt = %d \n", __func__, appmgr_get_boot_disk_state(), diskInfo[0].hddCount);

    appmgr_create_rs_config();

    initializeSystemFlag = true;
    qDebug("\n\n\t initializeSystem() ----- \n");
}
