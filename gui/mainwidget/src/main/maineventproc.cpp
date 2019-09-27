#include <QtGui>
#include <QWSServer>
#include "textmessagebox/textmessagedialog.h"
#include <glib.h>
#include "mainwidget.h"
#include "dvrsetup/setup/setupdialog.h"
#include "search/searchdialog.h"
#include "statusbardialog.h"
#include "playbardialog.h"
#include "search/backupdialog/backupdialog.h"
#include "videopane.h"
#include "mainglobal.h"
#include "KeypadCode.h"
#include "DVR.h"
#include "dvrsetup/device/diskformat/diskformatprocess.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#include <dev/Ver.h>
#include "aifbackup2.h"

void MainWidget::doUpdateDvrTime()
{
    if(operationMode > OPMODE_INIT)
    {
        QTimer::singleShot(10, statusBar, SLOT(updateTime()));
    }

    updateGpsStatus();
}

extern int errno;
#define SEMPERM 0600

int local_semaphore_init(key_t semkey)
{
    int status = 0, semid ;

    if((semid = semget(semkey, 1, SEMPERM|IPC_CREAT|IPC_EXCL)) == -1)
    {
        if(errno == EEXIST)
        {
            semid = semget(semkey, 1, 0);
        }
    }
    else   /* if created... */
    {
        status = semctl(semid, 0, SETVAL, 1);
    }

    if(semid == -1 || status == -1)
    {
        perror("initsem failed");
        return (-1);
    }
    else
    {
        return semid;    /* all okay  */
    }
}
int local_semaphore_wait(int semid)
{
    struct sembuf p_buf;
    p_buf.sem_num = 0;
    p_buf.sem_op  = -1;
    p_buf.sem_flg = SEM_UNDO;

    if(semop(semid, &p_buf, 1) == -1)
    {
        perror("p(semid) failed");
        exit(1);
    }
    else
    {
        return 0;
    }
}
int local_semaphore_post(int semid)
{
    struct sembuf v_buf;
    v_buf.sem_num = 0;
    v_buf.sem_op  = 1;
    v_buf.sem_flg = SEM_UNDO;

    if(semop(semid, &v_buf, 1) == -1)
    {
        perror("v(semid) failed");
        exit(1);
    }
    else
    {
        return 0;
    }
}
void MainWidget::doDvrEvent(Event *e)
{
    int eType = e->event;

    switch(eType)
    {
        case Send_QT_KEYPAD:
        {
            int keyCode = GPOINTER_TO_INT(e->data);

            if(operationMode == OPMODE_WAIT)
            {
                // skip key operation
                qDebug("skip... key");
            }
            else
            {
                //qDebug("%s(), key = %x \n", __func__, keyCode);
                if(operationMode == OPMODE_LIVE || operationMode == OPMODE_PLAYBACK)
                {
                    keypadEvent((unsigned char)keyCode);
                }
                else if(diskformatprocessDialog && diskformatprocessDialog->isVisible())
                {
                    qDebug("RC ESC Key Skip !!!!!!!!!!!!");
                }
                else if(operationMode == OPMODE_LOGIN)
                {
                    passNumpadKeypadEvent(keyCode);
                }
                else if(operationMode == OPMODE_SETUP)
                {
                    passNumpadKeypadEvent(keyCode);
                }
                else
                {
                    passKeypadEvent(keyCode);
                }
            }

            break;
        }
        case Send_QT_LIVE:
        {
            live_event_t *live;
            live = (live_event_t *)e->data;
            updateDvrEvent(live);

            break;
        }
        case Send_QT_INIT:
        {
            InitEvent *item;
            InitEvent itemTemp;
            item = (InitEvent *)e->data;
            memcpy(&itemTemp, item, sizeof(InitEvent));

            if(itemTemp.initType == INIT_COMPLETE)
            {
                // display initialize application message
                emit initEvent(0, itemTemp.initType, -1);
                qDebug("system init success !!!!!!!!!!!!");
                createPopupDialog();
            }

            emit initEvent(0, itemTemp.initType, itemTemp.progress);

            break;
        }
        case Send_QT_SEARCH_CALENDAR:
        {
            struct _n_cal_data_t {
                int type;
                int now;
                int dataCount;
                caldata_t calData[10];
            } *ce;

            ce = (struct _n_cal_data_t*)e->data;

            //qDebug("source[%d], dest[%d], event[%d]\n", e->source, e->dest, e->event);
            qDebug("Send_QT_SEARCH_CALENDAR %d, %d, %d, %d, %d\n", ce->type, ce->now, ce->dataCount, ce->calData[0].year, ce->calData[0].month);

            if(ce->dataCount == 0 && ce->calData[0].year == 0 && ce->calData[0].month == 0)
            {
                time_t cur;
                struct tm tmNow;
                time(&cur);
                localtime_r(&cur, &tmNow);
                ce->calData[0].year = tmNow.tm_year+1900;
                ce->calData[0].month = tmNow.tm_mon+1;
            }

            calDataCount = ce->dataCount;
            memset(calendarData, 0, sizeof(struct _caldata) * MAX_CAL_MONTH_DATA);
            memcpy(calendarData, ce->calData, sizeof(struct _caldata) * calDataCount);
            qDebug(".......... Send_QT_SEARCH_CALENDAR %d, %x", ce->type, ce->dataCount);

            #if 0 // jungyver [17/02/18]
            for(int i = 0; i < calDataCount; i++)
            {
                for(int k = 0; k < 32; k++)
                {
                    qDebug(".... cal %d, day %d = %x", calendarData[i].month, k, calendarData[i].data[k]);
                }
            }
            #endif

            emit searchCalendarReady(SEARCH_REC_TIME);

            break;
        }
        case Send_QT_SEARCH_TIMELINE:
        {
            // NOTE: diskmgr/inc/diskmgr.h
            struct _n_tl_data_t {
                int type;
                int now;
                int dataCount;
                int dlsType;
                time_search_info_t timeSearchInfo[25];
                unsigned long boundary;
            } *tl;

            int h, m, s, hTmp;

            tl = (struct _n_tl_data_t *) e->data;

            if((tl->dlsType == DLS_START_DAY) || (tl->dlsType == DLS_START_END_DAY))
            {
                for(h = 0, hTmp = 0; hTmp < 25; h++, hTmp++)
                {
                    if(h == dlsPlayback.dlsBeginHour)
                    {
                        hTmp++;
                    }

                    for(m = 0; m < 60; m++)
                    {
                        for(s = 0; s < 4; s++)
                        {
                            timeLog[hTmp].channel[m*4+s] = timeLog[hTmp].channel[m*4+s] | (tl->timeSearchInfo[h].channel[m*4+s] & 0x0000ffff);
                        }
                    }
                }
            }
            else // DLS_OFF, DLS_DAY, DLS_END_DAY
            {
                for(h = 0; h < 25; h++)
                {
                    for(m = 0; m < 60; m++)
                    {
                        for(s = 0; s < 4; s++)
                        {
                            timeLog[h].channel[m*4+s] = timeLog[h].channel[m*4+s] | (tl->timeSearchInfo[h].channel[m*4+s] & 0x0000ffff);
                        }
                    }
                }
            }

            #if 0 // jungyver [17/02/18]
            for(h = 0; h < 25; h++)
            {
                for(m = 0; m < 240; m++)
                {
                    qDebug("timeLog[%d].channel[%d] = %x \n", h, m, timeLog[h].channel[m]);
                }
            }
            #endif

            emit searchDataReady(SEARCH_REC_TIME);

            break;
        }
        case Send_QT_SEARCH_AUDIO_TIMELINE:
        {
            // NOTE: diskmgr/inc/diskmgr.h
            struct _n_tl_data_t {
                int type;
                int now;
                int dataCount;
                int dlsType;
                time_search_info_t timeSearchInfo[25];
                unsigned long boundary;
            } *tl;

            int h, m, s, hTmp;

            tl = (struct _n_tl_data_t *) e->data;

            memset(timeLog, 0, sizeof(struct _time_search_info_ext) * 25);

            qDebug(" %dh, dlsType = %d, boundary = %ld \n", dlsPlayback.dlsBeginHour, tl->dlsType, tl->boundary);

            if((tl->dlsType == DLS_START_DAY) || (tl->dlsType == DLS_START_END_DAY))
            {
                for(h = 0, hTmp = 0; hTmp < 25; h++, hTmp++)
                {
                    if(h == dlsPlayback.dlsBeginHour)
                    {
                        hTmp++;
                    }

                    for(m = 0; m < 60; m++)
                    {
                        for(s = 0; s < 4; s++)
                        {
                            timeLog[hTmp].channel[m*4+s] = tl->timeSearchInfo[h].channel[m*4+s];
                            timeLog[hTmp].channel[m*4+s] = (timeLog[hTmp].channel[m*4+s] & 0x0000ffff) << 16;

                        }
                    }
                }
            }
            else // DLS_OFF, DLS_DAY, DLS_END_DAY
            {
                for(h = 0; h < 25; h++)
                {
                    for(m = 0; m < 60; m++)
                    {
                        for(s = 0; s < 4; s++)
                        {
                            timeLog[h].channel[m*4+s] = tl->timeSearchInfo[h].channel[m*4+s];
                            timeLog[h].channel[m*4+s] = (timeLog[h].channel[m*4+s] & 0x0000ffff) << 16;
                        }
                    }
                }
            }

            break;
        }
        case Send_QT_SEARCH_EVENT:
        {
            WriteLogData_t* pLogData;
            int rv;

            pLogData = (WriteLogData_t*)e->data;

            memset(eventLog, 0, sizeof(struct _eventlog_info) * MAX_EVENT_SEARCH_LOG);

            qDebug("pLogData(%d, %d, %d)\n", pLogData->size, pLogData->count, pLogData->offset);

            if(pLogData->size <= 0 || pLogData->count > MAX_EVENT_SEARCH_LOG)
            {
                eventLogCount = 0;
            }
            else
            {
                eventLogCount = pLogData->count;
            }

            rv = appmgr_conv_SearchEventLog((DataEvent*)pLogData->data, eventLog, eventLogCount);

            #if 0 // jungyver [17/02/18]
            {
                int ii;
                for(ii=0;ii<eventLogCount;ii++)
                {
                    qDebug("%d:<CH%d> - <Type %d> - <Time %s>\n", ii, (eventLog+ii)->ch, (eventLog+ii)->rtype, atime((eventLog+ii)->t));
                }
            }
            #endif

            if(rv != 0)
            {
                eventLogCount = 0;
            }

            emit searchDataReady(SEARCH_EVENT_LOG);

            break;
        }
        case Send_QT_PLAYER:
        {
            WorkTimeEvent *itemTemp;
            time_t pbTime;
            int pbChannel;

            itemTemp = (WorkTimeEvent *)e->data;
            pbTime = (time_t)(itemTemp->pbtime);
            pbChannel = itemTemp->pbchnn;

            //qDebug("\n\n\t Send_QT_PLAYER: pbTime[%s] \n", atime(pbTime));
            if(operationMode == OPMODE_PLAYBACK)
            {
                if(mainPbChannel != pbChannel)
                {
                    qDebug("\n\n\t Send_QT_PLAYER mainPbChannel[%x], pbChannel[%x]\n", mainPbChannel, pbChannel);
                    mainPbChannel = pbChannel;

                    for(int i = 0; i < devInfo.videoNum; i++)
                    {
                        if(pbChannel & (0x01 << i))
                        {
                            videoPane[i]->setNoRecordVideoDetect(0);
                        }
                        else
                        {
                            videoPane[i]->setNoRecordVideoDetect(1);
                        }
                    }
                }

                emit playbackTimeNotify(pbTime);
            }

            break;
        }
        case Send_QT_PLAYER_STOP:
        {
            WorkPlayEvent *item;
            item = (WorkPlayEvent *)e->data;

            emit playbackStopNotify();

            break;
        }
        case Send_QT_BACKUP_LOG:
        {
            InitEvent *item;
            InitEvent itemTemp;
            item = (InitEvent *)e->data;
            memcpy(&itemTemp, item, sizeof(InitEvent));

            if(operationMode == OPMODE_SEARCH)
            {
                emit saveLogProgress(itemTemp.initType, itemTemp.progress);
            }

            break;
        }
        case Send_QT_BACKUP_MEDIA:
        {
            InitEvent *item;
            InitEvent itemTemp;
            item = (InitEvent *)e->data;
            memcpy(&itemTemp, item, sizeof(InitEvent));

            if(operationMode == OPMODE_BACKUP)
            {
                emit backupProgress(itemTemp.initType, itemTemp.progress);
            }

            break;
        }
        case Send_QT_BACKUP_CALCULATION:
        {
            CalculationEvent *item;
            CalculationEvent itemTemp;
            item = (CalculationEvent *)e->data;
            memcpy(&itemTemp, item, sizeof(CalculationEvent));

            if(operationMode == OPMODE_BACKUP)
            {
                emit backupCalculation(itemTemp.deviceFreeMb, itemTemp.mediaBytes, itemTemp.indexBytes);
            }

            break;
        }
        case Send_QT_DISK:
        {
            int Message;

            Message = GPOINTER_TO_INT(e->data);

            if(Message == DISK_FORMAT_END)
            {
                qDebug("receive DISK_FORMAT_END message\n");
                emit diskformatEnd();
            }
#if 1 // GyverJeong [18/04/11]
            else if(Message == DISK_MOUNT_ERR)
            {
                qDebug("Receive DISK_MOUNT_ERR Message");

                if(msgBoxDisk)
                {
                    delete msgBoxDisk;
                }

                msgBoxDisk = new TextMessageDialog(tr("MOUNT ERROR"), tr("Format Error"), 2, this);
                msgBoxDisk->move((appmgr_get_mainwidget_width()-msgBoxDisk->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBoxDisk->sizeHint().height())/2);
                msgBoxDisk->exec();
                delete msgBoxDisk;
                msgBoxDisk = NULL;
            }
#endif

            break;
        }
        case Send_QT_DISK_FORMAT_PROCESS:
        {
            DiskFormat_t *item;

            if(!diskformatprocessDialog)
            {
                diskformatprocessDialog = new DiskFormatProcessDialog(this);
                qDebug("................... diskformatprocessDialog create.........");
            }
            item = (DiskFormat_t *)e->data;

            //qDebug("Send_QT_DISK_FORMAT_PROCESS index[%ld], %lu%% %02u:%02u \n", item->total_file_count, item->percent, item->remain_time/60, item->remain_time%60);
            emit diskformatProgress(item->disk, item->total_file_count, item->percent, item->remain_time);

            break;
        }
        case Send_QT_UPGRADE_PROGRESS:
        {
            if(setupDialog)
            {
                int *pPercent = (int *)e->data;
                emit upgradeProgress(*pPercent);
            }

            break;
        }
        case Send_QT_DISK_STATE:
        {
            DiskState_t *item;
            item = (DiskState_t *)e->data;

            if(isDisk)
            {
                if(item->code == DS_CODE_HDD_NOT_FOUND)
                {
                    if(msgBoxDisk)
                    {
                        delete msgBoxDisk;
                    }

                    appmgr_set_beep_no_disk(1);

                    msgBoxDisk = new TextMessageDialog(tr("ERROR"), tr("NO SSD"), 2, this);
                    msgBoxDisk->move((appmgr_get_mainwidget_width()-msgBoxDisk->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBoxDisk->sizeHint().height())/2);

                    if(msgBoxDisk->exec())
                    {
                        ;
                    }

                    if(msgBoxDisk)
                    {
                        delete msgBoxDisk;
                        msgBoxDisk = NULL;
                    }

                    appmgr_set_beep_no_disk(0);

                    qDebug("receive Send_QT_DISK_STATE message NO DISK Detected\n");
                }
                else if(item->code == DS_CODE_HDD_FORMAT_START)
                {
                    qDebug("receive Send_QT_DISK_STATE message formatting Start\n");
                }
            }

            break;
        }
        case Send_QT_TIME_CHANGE:
        {
            if(operationMode == OPMODE_LIVE)
            {
                time_change_event_t *item;
                item = (time_change_event_t *)e->data;

                qDebug("Send_QT_TIME_CHANGE.....\n");
                emit timeChangeNotify();
            }

            break;
        }
        case Send_QT_STATUSBAR_STATE:
        {
            StatusBarState_t *item;
            int enable;

            item = (StatusBarState_t *)e->data;
            enable = item->state;

            if(item->operationMode == OPMODE_LIVE)
            {
                statusBarState(enable);
            }
            else if(item->operationMode == OPMODE_PLAYBACK)
            {
                playBarState(enable);
            }

            break;
        }
        case Send_QT_UPDATE_CONFIG:
        {
            if(operationMode != OPMODE_LIVE)
            {
                return;
            }

            utils_cfg_get_from_res();

            break;
        }
        case Send_QT_EVENT_POPUP:
        {
            EventPopup_t *item;
            item = (EventPopup_t *)e->data;

            //qDebug("\n\n\t Send_QT_EVENT_POPUP type[%d], ch[%d] \n", item->type, item->ch);
            if(msgBox && item->type == EVENT_POPUP_SENSOR_OFF)
            {
                delete msgBox;
                msgBox = NULL;
            }

            if(msgBoxDisk)
            {
                appmgr_set_beep_no_disk(0);
            }

            eventPopupOneChannel(item->type, item->ch);

            break;
        }
        case Send_QT_EVENT_LOG_COUNT:
        {
            EVENT_LOG_DATA_S *pData = (EVENT_LOG_DATA_S *)e->data;
            extern EVENT_LOG_DATA_S gEventLog[MAX_EVENT_LOG_PAGE_DATA];
            memset(gEventLog, 0, sizeof(EVENT_LOG_DATA_S) * MAX_EVENT_LOG_PAGE_DATA);
            memcpy(gEventLog, pData, sizeof(EVENT_LOG_DATA_S) * ((pData+0)->count));
            emit queryLogCount();

            break;
        }
        case Send_QT_EVENT_LOG_DATA:
        {
            EVENT_LOG_DATA_S *pData = (EVENT_LOG_DATA_S *)e->data;
            extern EVENT_LOG_DATA_S gEventLog[MAX_EVENT_LOG_PAGE_DATA];
            memset(gEventLog, 0, sizeof(EVENT_LOG_DATA_S) * MAX_EVENT_LOG_PAGE_DATA);
            memcpy(gEventLog, pData, sizeof(EVENT_LOG_DATA_S) * ((pData+0)->count));
            emit queryLogData();

            break;
        }
        case Send_QT_EVENT_LOG_BACKUP:
        {
            EVENT_LOG_DATA_S *pData = (EVENT_LOG_DATA_S *)e->data;
            extern EVENT_LOG_DATA_S gEventLog[MAX_EVENT_LOG_PAGE_DATA];
            memset(gEventLog, 0, sizeof(EVENT_LOG_DATA_S) * MAX_EVENT_LOG_PAGE_DATA);
            memcpy(gEventLog, pData, sizeof(EVENT_LOG_DATA_S) * ((pData+0)->count));
            emit queryLogBackup();

            break;
        }
        case Send_QT_SYSTEM_LOG_COUNT:
        {
            SYSTEM_LOG_DATA_S *pData = (SYSTEM_LOG_DATA_S *)e->data;
            extern SYSTEM_LOG_DATA_S gSystemLog[SYSTEM_LOG_COUNT_PER_PAGE];
            memset(gSystemLog, 0, sizeof(SYSTEM_LOG_DATA_S) * SYSTEM_LOG_COUNT_PER_PAGE);
            memcpy(gSystemLog, pData, sizeof(SYSTEM_LOG_DATA_S) * ((pData+0)->count));
            emit systemLogCount();

            break;
        }
        case Send_QT_SYSTEM_LOG_DATA:
        {

            SYSTEM_LOG_DATA_S *pData = (SYSTEM_LOG_DATA_S *)e->data;
            extern SYSTEM_LOG_DATA_S gSystemLog[SYSTEM_LOG_COUNT_PER_PAGE];
            memset(gSystemLog, 0, sizeof(SYSTEM_LOG_DATA_S) * SYSTEM_LOG_COUNT_PER_PAGE);
            memcpy(gSystemLog, pData, sizeof(SYSTEM_LOG_DATA_S) * ((pData+0)->count));
            emit systemLogData();

            break;
        }
        case Send_QT_SYSTEM_LOG_BACKUP:
        {
            SYSTEM_LOG_DATA_S *pData = (SYSTEM_LOG_DATA_S *)e->data;
            extern SYSTEM_LOG_DATA_S gSystemLog[SYSTEM_LOG_COUNT_PER_PAGE];
            memset(gSystemLog, 0, sizeof(SYSTEM_LOG_DATA_S) * SYSTEM_LOG_COUNT_PER_PAGE);
            memcpy(gSystemLog, pData, sizeof(SYSTEM_LOG_DATA_S) * ((pData+0)->count));
            emit systemLogBackup();

            break;
        }
        case Send_QT_EVENT_SATA_LINK_UP:
        {
            if(isDisk)
            {
                system_state = SYSTEM_SHUTDOWN;

                if(msgBox)
                {
                    delete msgBox;
                }

                msgBox = new TextMessageDialog(tr("ERROR"), QString("%1\n%2").arg(tr("Storage was attached."),tr("System will restart.")), 3, this);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                msgBox->exec();

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }
            }

            break;
        }
        case Send_QT_EVENT_SATA_LINK_DOWN:
        {
            if(isDisk)
            {
                system_state = SYSTEM_SHUTDOWN;

                if(msgBox)
                {
                    delete msgBox;
                }

                for(int ii = 0; ii < devInfo.videoNum; ii++)
                {
                    videoPane[ii]->systemShutdownIconClean();
                }

                if(diskInfo[0].smartInfo_ata_id)    { msgBox = new TextMessageDialog(tr("ERROR"), QString("%1\n%2").arg(tr("HDD was detached."), tr("System will restart.")), 3, this); }
                else                                { msgBox = new TextMessageDialog(tr("ERROR"), QString("%1\n%2").arg(tr("SSD was detached."), tr("System will restart.")), 3, this); }

                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                msgBox->exec();

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }
            }

            break;
        }
        case Send_QT_EVENT_IO_ERROR:
        {
            system_state = SYSTEM_SHUTDOWN;

            if(msgBox)
            {
                delete msgBox;
            }

            for(int ii = 0; ii < devInfo.videoNum; ii++)
            {
                videoPane[ii]->systemShutdownIconClean();
            }

            msgBox = new TextMessageDialog(tr("ERROR"), QString("%1\n%2").arg(tr("IO Error occurred."), tr("System will restart.")), 3, this);

            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

            msgBox->exec();

            if(msgBox)
            {
                delete msgBox;
                msgBox = NULL;
            }

            break;
        }
        case Send_QT_REMOVE_USB_MEMORY:
        {
            isDisk = 0;

            appmgr_set_usb_flag(1);

            if(msgBox)
            {
                delete msgBox;
                msgBox = NULL;
            }

            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("WARNING"), QString("%1\n%2\n%3").arg(
                            tr("Please unplug USB memory.   "),
                            tr("If you click button of 'Ok',"),
                            tr("System will restart.")), 2, this);
            }
            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

            msgBox->exec();

            appmgr_reboot_system(0);

            break;
        }
        case Send_QT_ACC_POWER_OFF:
        {
            int *pElapsedTime = (int *)e->data;
            char tmp[16] = {0,};
            sprintf(tmp, "%02d.%03d", *pElapsedTime/1000, *pElapsedTime%1000);

            system_state = SYSTEM_SHUTDOWN;

            if(msgBox)
            {
                delete msgBox;
                msgBox = NULL;
            }

            for(int ii = 0; ii < devInfo.videoNum; ii++)
            {
                videoPane[ii]->systemShutdownIconClean();
            }

            msgBox = new TextMessageDialog(tr("POWER OFF"), QString("%1: %2\n%3").arg(tr("Elapsed Time"), tr(tmp), tr("System will shutdown.")), 3, this);

            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

            msgBox->exec();

            break;
        }
        case Send_QT_SET_RECORD_ICON:
        {
            int *pSetRecordIcon = (int *)e->data;
#if 1 // GyverJeong [18/03/15]
            if(isDrawRecordIcon)
            {
                videoPane[*pSetRecordIcon]->setRecordingDetect(1, 0, 0, 0);
            }
#else
            videoPane[*pSetRecordIcon]->setRecordingDetect(1, 0, 0, 0);
#endif

            break;
        }
        case Send_QT_RESET_RECORD_ICON:
        {
            //for(int ii = 0; ii < devInfo.videoNum; ii++)
            for(int ii = 0; ii < 8; ii++)
            {
                isDrawRecordIcon = 0;
                videoPane[ii]->setRecordingDetect(0x0, 0x0, 0x0, 0x0);
            }

            break;
        }
#if 1 // GyverJeong [18/05/15]
        case Send_QT_SATA_ERROR_COUNT:
        {
            int *pData = (int *)e->data;
            char tmp[16] = {0,};
            sprintf(tmp, "%d", *pData);

            if(msgBox)
            {
                delete msgBox;
                msgBox = NULL;
            }

            msgBox = new TextMessageDialog( tr("NOTICE"), QString("%1 : %2").arg(tr("SATA Error Count")).arg(tmp), 3, this );
            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

            msgBox->exec();

            if(msgBox)
            {
                delete msgBox;
                msgBox = NULL;
            }

            break;
        }
#endif
        default:
        {
            qDebug("main : event receive %x", eType);

            break;
        }
    }

    #if 0
    if(e->free_func)
    {
        (*e->free_func)(e->data);
    }
    #endif

    eventThread->resetQueueRun(e);
}
void MainWidget::updateDvrEvent(live_event_t *live)
{
    int i = 0, prev = 0, cur = 0;
    int record = 0, prerecord = 0;
    QString str;
    int checkVIS[16];

    if(operationMode == OPMODE_LIVE)
    {
        // Camera Loss Draw
        if(live->cameraLoss != liveEvent.cameraLoss)
        {
            for(i = 0; i < devInfo.videoNum; i++)
            {
                prev = (liveEvent.cameraLoss & (1<<i));
                cur = (live->cameraLoss & (1<<i));

                if(prev != cur)
                {
                    videoPane[i]->setVideoLossDetect(cur);
                }

                if(prev)
                {
                    if(cfgMain.gbl.audioOut != LIVE_AUDIO_MUTE)
                    {
                        if(i == (cfgMain.gbl.audioOut-2))
                        {
                            videoPane[i]->setAudioOutput(1);
                        }
                    }
                }
            }

            liveEvent.cameraLoss = live->cameraLoss;
        }
    }

    if((live->cameraVis >> 16) & 0x1)
    {
        int save_flag = 0;

        liveEvent.cameraVis = live->cameraVis;
        ver_get_vis_list(checkVIS);

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            if(liveEvent.cameraVis & (0x1 << i))
            {
                if(checkVIS[i] == ver_vis_pal || checkVIS[i] == ver_vis_ntsc)
                {
                    if(checkVIS[i] == ver_vis_pal)
                    {
                        if(cfgMain.rec.record_main.fr_hd[i] > 25)
                        {
                            cfgMain.rec.record_main.fr_hd[i]  = 25;
                            cfgSetup.rec.record_main.fr_hd[i] = 25;
                        }
                    }

                    cfgMain.rec.record_main.resolution[i]  = RESOLUTION_FULL;
                    cfgSetup.rec.record_main.resolution[i] = RESOLUTION_FULL;
                    save_flag++;
                }
                else if(checkVIS[i] == ver_vis_hd_720_25p || checkVIS[i] == ver_vis_hd_720_30p || checkVIS[i] == ver_vis_hd_720_50p || checkVIS[i] == ver_vis_hd_720_60p)
                {

                    if(checkVIS[i] == ver_vis_hd_720_25p || checkVIS[i] == ver_vis_hd_720_50p)
                    {
                        if(cfgMain.rec.record_main.fr_hd[i] > 25)
                        {
                            cfgMain.rec.record_main.fr_hd[i]  = 25;
                            cfgSetup.rec.record_main.fr_hd[i] = 25;
                        }
                    }

                    cfgMain.rec.record_main.resolution[i]  = RESOLUTION_HD_1280x720;
                    cfgSetup.rec.record_main.resolution[i] = RESOLUTION_HD_1280x720;
                    save_flag++;
                }
                else
                {
                    if(checkVIS[i] != ver_vis_unknown)
                    {
                        if(cfgMain.rec.record_main.fr_hd[i] > 15)
                        {
                            cfgMain.rec.record_main.fr_hd[i]  = 15;
                            cfgSetup.rec.record_main.fr_hd[i] = 15;
                        }
                    }

                    cfgMain.rec.record_main.resolution[i]  = RESOLUTION_HD_1920x1080;
                    cfgSetup.rec.record_main.resolution[i] = RESOLUTION_HD_1920x1080;
                    save_flag++;
                }
            }

            videoPane[i]->updateStringVis(checkVIS[i]);
            qDebug() << videoPane[i]->strVis;
            videoPane[i]->m_flg_update  = true;
            videoPane[i]->m_flg_showVis = true;
            videoPane[i]->update(videoPane[i]->rect());
        }

        if(save_flag)
        {
            appmgr_set_camera_vis(liveEvent.cameraVis);
            setConfigString();
            appmgr_cfg_change();
            appmgr_save_setup(0, &cfgMain);
            appmgr_cfg_sync();
        }
    }
    else
    {
        liveEvent.cameraVis = live->cameraVis;
    }

    if(operationMode == OPMODE_LIVE)
    {
        if(live->diskFull != liveEvent.diskFull)
        {
            if(live->diskFull == 1)
            {
                for(i = 0; i < devInfo.videoNum; i++)
                {
                    record_icon_draw = 1;
                    videoPane[i]->setRecordingDetect(0x0, 0x0, 0x0, 0x0);
                }
            }
            else
            {
                for(i = 0; i < devInfo.videoNum; i++)
                {
                    record    = (live->recordOn & (1<<i));
                    prerecord = (live->prerecordOn & (1<<i));

                    qDebug(" Ch[%2d]: videoLoss[%d], record[%d], prerecord[%d] \n", i, (live->cameraLoss & (1<<i)), record, prerecord);

                    if(diskInfo[0].hddCount == 0)
                    {
                        record_icon_draw = 1;
                        videoPane[i]->setRecordingDetect(0x0, 0x0, 0x0, 0x0);
                    }
                    else
                    {
                        record_icon_draw = 0;
                        videoPane[i]->setRecordingDetect(record, 0, 0, prerecord);
                    }
                }

                liveEvent.recordOn     = live->recordOn;
                liveEvent.prerecordOn  = live->prerecordOn;
            }

            liveEvent.diskFull = live->diskFull;
        }

        if((live->changeRecordType != liveEvent.changeRecordType) || (live->recordOn != liveEvent.recordOn) || (live->prerecordOn != liveEvent.prerecordOn))
        {
            for(i = 0; i < devInfo.videoNum; i++)
            {
                record    = (live->recordOn & (1<<i));
                prerecord = (live->prerecordOn & (1<<i));
                //qDebug(" Ch[%2d]: videoLoss[%d], record[%d], prerecord[%d] \n", i, (live->cameraLoss & (1<<i)), record, prerecord);

                if(liveEvent.diskFull == 0)
                {
                    if(diskInfo[0].hddCount == 0)
                    {
#if 1 // GyverJeong [17/11/14]
                        int *pResetRecordIcon = g_new0(int, 1);
                        *pResetRecordIcon     = i;
                        event_send(QUEUE_QT_CORE, QUEUE_WORK, WORK_EVENT_RESET_RECORD_ICON, pResetRecordIcon, g_free, NULL);
#endif
                        record_icon_draw = 1;
                        videoPane[i]->setRecordingDetect(0x0, 0x0, 0x0, 0x0);
                    }
                    else
                    {
#if 1 // GyverJeong [17/11/14]
                        if(!record)
                        {
                            int *pResetRecordIcon = g_new0(int, 1);
                            *pResetRecordIcon     = i;
                            event_send(QUEUE_QT_CORE, QUEUE_WORK, WORK_EVENT_RESET_RECORD_ICON, pResetRecordIcon, g_free, NULL);
                            videoPane[i]->setRecordingDetect(record, 0, 0, prerecord);
                        }
#else
                        record_icon_draw = 0;
                        videoPane[i]->setRecordingDetect(record, 0, 0, prerecord);
#endif
                    }
                }
            }

            liveEvent.recordOn         = live->recordOn;
            liveEvent.prerecordOn      = live->prerecordOn;
            liveEvent.changeRecordType = live->changeRecordType;
        }

#if 1 // GyverJeong [18/04/27]
        if(operationMode == OPMODE_LIVE)
        {
#if 1 // GyverJeong [18/05/15]
            if(diskInfo[0].hddCount == 0)
            {
                live->recordOn = 0;
            }
#endif

            for(i = 0; i < devInfo.videoNum; i++)
            {
                if(videoPane[i]->isVisibleRecordIcon() != (record = ((live->recordOn&(1<<i))?1:0)))
                {
                    int *pResetRecordIcon = g_new0(int, 1);
                    *pResetRecordIcon     = i;
                    event_send(QUEUE_QT_CORE, QUEUE_WORK, WORK_EVENT_RESET_RECORD_ICON, pResetRecordIcon, g_free, NULL);
                    videoPane[i]->setRecordingDetect(record, 0, 0, 0);
                }
            }
        }
#endif

        // HDD Remain Size Draw
        if(live->diskSize != liveEvent.diskSize || live->diskFree != liveEvent.diskFree)
        {
            //int used = (int)(((live->diskSize - live->diskFree) * 100)/(live->diskSize));
            //qDebug(".......... disk progress %d", used);
            //statusBar->updateDiskProgress(used);
            statusBar->updateDiskProgress(live->diskSize, live->diskFree);
        }

        liveEvent.diskSize   = live->diskSize;
        liveEvent.diskFree   = live->diskFree;
        liveEvent.detectTime = live->detectTime;
    }
}
void MainWidget::keypadEvent(unsigned char code)
{
    //qDebug("keypadEvent() key = %x", code);

    switch(code)
    {
        case KPD_EVENT_ERR:

            break;

        case KPD_EVENT_POWER:

            systemShutdown();

            break;

        case KPD_EVENT_ESC:

            if(operationMode == OPMODE_LIVE && setupDialog  != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier, QString(QChar(Qt::Key_Escape)));
                QApplication::postEvent(QApplication::activeWindow() , key);
            }

            if(operationMode == OPMODE_PLAYBACK)
            {
                if(search_playback_start)
                {
                    break;
                }

                if(playBar != NULL)
                {
                    QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier, QString(QChar(Qt::Key_Escape)));
                    QApplication::postEvent(playBar, key);
                }
            }

            break;

        case KPD_EVENT_UP:

            if(operationMode == OPMODE_LIVE && setupDialog  != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, QString(QChar(Qt::Key_Up)));
                QApplication::postEvent(QApplication::activeWindow() , key);
            }
            else if(operationMode == OPMODE_PLAYBACK && playBar != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, QString(QChar(Qt::Key_Up)));
                QApplication::postEvent(playBar, key);
            }

            break;

        case KPD_EVENT_LEFT:

            if(operationMode == OPMODE_LIVE && setupDialog  != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier, QString(QChar(Qt::Key_Left)));
                QApplication::postEvent(QApplication::activeWindow() , key);
            }
            else if(operationMode == OPMODE_PLAYBACK && playBar != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier, QString(QChar(Qt::Key_Left)));
                QApplication::postEvent(playBar, key);
            }

            break;

        case KPD_EVENT_SELECT:

            if(operationMode == OPMODE_LIVE && setupDialog  != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier, QString(QChar(Qt::Key_Enter)));
                QApplication::postEvent(QApplication::activeWindow() , key);
            }
            else if(operationMode == OPMODE_PLAYBACK && playBar != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier, QString(QChar(Qt::Key_Enter)));
                QApplication::postEvent(playBar , key);
            }

            break;

        case KPD_EVENT_RIGHT:

            if(operationMode == OPMODE_LIVE && setupDialog  != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier, QString(QChar(Qt::Key_Right)));
                QApplication::postEvent(QApplication::activeWindow() , key);
            }
            else if(operationMode == OPMODE_PLAYBACK && playBar != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier, QString(QChar(Qt::Key_Right)));
                QApplication::postEvent(playBar, key);
            }

            break;

        case KPD_EVENT_DOWN:


            if(operationMode == OPMODE_LIVE && setupDialog  != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier, QString(QChar(Qt::Key_Down)));
                QApplication::postEvent(QApplication::activeWindow() , key);
            }
            else if(operationMode == OPMODE_PLAYBACK && playBar != NULL)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier, QString(QChar(Qt::Key_Down)));
                QApplication::postEvent(playBar, key);
            }

            break;

        case KPD_EVENT_SETUP:

            if(system_state == SYSTEM_SHUTDOWN)
            {
                break;
            }

            if(operationMode == OPMODE_LIVE && isTrigger)
            {
                if(msgBox)
                {
                    delete msgBox;
                }

                msgBox = new TextMessageDialog(tr("NOTICE"), tr("Current status is trigger."), 2, this);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                if(msgBox->exec())
                {
                    ;
                }

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }

                break;
            }

            if(operationMode == OPMODE_LIVE && setupDialog != NULL && msgBoxDisk == NULL)
            {
                runSetup();
                break;
            }

            if(operationMode == OPMODE_PLAYBACK && !EventSearchPB)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier, QString(QChar(Qt::Key_PageUp)));
                QApplication::postEvent(playBar, key);
                break;
            }

            break;

        case KPD_EVENT_SEARCH:

            if(system_state == SYSTEM_SHUTDOWN)
            {
                break;
            }

            if(operationMode == OPMODE_LIVE && isTrigger)
            {
                if(msgBox)
                {
                    delete msgBox;
                }

                msgBox = new TextMessageDialog(tr("NOTICE"), tr("Current status is trigger."), 2, this);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                if(msgBox->exec())
                {
                    ;
                }

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }

                break;
            }

            if(operationMode == OPMODE_LIVE && searchDialog != NULL && msgBoxDisk == NULL)
            {
                runSearch();
                break;
            }

            if(operationMode == OPMODE_PLAYBACK && !EventSearchPB)
            {
                QKeyEvent *key = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier, QString(QChar(Qt::Key_PageDown)));
                QApplication::postEvent(playBar, key);
                break;
            }

            break;

        case KPD_EVENT_REW:

            if(operationMode == OPMODE_PLAYBACK)
            {
                playBar->rewClicked();
            }

            break;

        case KPD_EVENT_PLAY_PAUSE:

            if(operationMode == OPMODE_PLAYBACK)
            {
                playBar->playpauseClicked();
            }

            break;

        case KPD_EVENT_FF:

            if(operationMode == OPMODE_PLAYBACK)
            {
                playBar->fastClicked();
            }

            break;

        case KPD_EVENT_AUDIO:

            if(operationMode == OPMODE_LIVE && isTrigger)
            {
                if(msgBox)
                {
                    delete msgBox;
                }

                msgBox = new TextMessageDialog(tr("NOTICE"), tr("Current status is trigger."), 2, this);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                if(msgBox->exec())
                {
                    ;
                }

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }

                break;
            }

            if(operationMode == OPMODE_LIVE)
            {
                mainMenu->onButtonAudio();
            }
            else if(operationMode == OPMODE_PLAYBACK)
            {
                playBar->onButtonAudio();
            }

            break;

        case KPD_EVENT_FREW:

            if(!EventSearchPB && operationMode == OPMODE_PLAYBACK)
            {
                playBar->rewFrameClicked();
            }

            break;

        case KPD_EVENT_FADJ:

            if(!EventSearchPB && operationMode == OPMODE_PLAYBACK)
            {
                playBar->fowardFrameClicked();
            }

            break;

        case KPD_EVENT_ARCHIVE:

            if(operationMode == OPMODE_PLAYBACK)
            {
                playBar->clickBackup();
            }

            break;

        case KPD_EVENT_STATUS:

            if(operationMode == OPMODE_LIVE)
            {
                controlBarChange();
            }
            else if(operationMode == OPMODE_PLAYBACK)
            {
                if( playBar->isHidden())
                {
                    playBarState(1);
                    appmgr_set_playber_bar_status(1);
                }
                else if( playBar->isVisible())
                {
                    playBarState(0);
                    appmgr_set_playber_bar_status(0);
                }
            }

            break;

        case KPD_EVENT_SPLIT:

            if(operationMode == OPMODE_LIVE && isTrigger)
            {
                if(msgBox)
                {
                    delete msgBox;
                }

                msgBox = new TextMessageDialog(tr("NOTICE"), tr("Current status is trigger."), 2, this);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                if(msgBox->exec())
                {
                    ;
                }

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }
            }
            else if(operationMode == OPMODE_LIVE)
            {
                statusBar->buttonSplitClicked();
            }
            else if(operationMode == OPMODE_PLAYBACK)
            {
                playBar->buttonSplitClicked();
            }

            break;

        case KPD_EVENT_1:
        case KPD_EVENT_2:
        case KPD_EVENT_3:
        case KPD_EVENT_4:
        case KPD_EVENT_5:
        case KPD_EVENT_6:
        case KPD_EVENT_7:
        case KPD_EVENT_8:
        case KPD_EVENT_9:
        case KPD_EVENT_10:

            if(operationMode == OPMODE_LIVE && isTrigger)
            {
                if(msgBox)
                {
                    delete msgBox;
                }

                msgBox = new TextMessageDialog(tr("NOTICE"), tr("Current status is trigger."), 2, this);
                msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                if(msgBox->exec())
                {
                    ;
                }

                if(msgBox)
                {
                    delete msgBox;
                    msgBox = NULL;
                }

                break;
            }

            if(splitFlag)
            {
                break;
            }

            if(operationMode == OPMODE_PLAYBACK)
            {
                if(!(mainPbChannel & 0x01<<(code-KPD_EVENT_1)))
                {
                    qDebug("%s(%d)", "No Data", code-KPD_EVENT_1);
                    break;
                }
            }

            oneChannelSplit(code - KPD_EVENT_1);

            break;

        default:

            break;
    }
}
void MainWidget::passNumpadKeypadEvent(unsigned char code)
{
    QKeyEvent	*key = NULL;

    //qDebug("passNumpadKeypadEvent() key = %x", code);

    switch (code)
    {
        case KPD_EVENT_ESC:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Escape,   Qt::NoModifier, QString(QChar(Qt::Key_Escape)));

            break;

        case KPD_EVENT_UP:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up,       Qt::NoModifier, QString(QChar(Qt::Key_Up)));

            break;

        case KPD_EVENT_LEFT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left,     Qt::NoModifier, QString(QChar(Qt::Key_Left)));

            break;

        case KPD_EVENT_SELECT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter,    Qt::NoModifier, QString(QChar(Qt::Key_Enter)));

            break;

        case KPD_EVENT_DOWN:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down,     Qt::NoModifier, QString(QChar(Qt::Key_Down)));

            break;

        case KPD_EVENT_RIGHT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right,    Qt::NoModifier, QString(QChar(Qt::Key_Right)));

            break;

        case KPD_EVENT_1:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_1,        Qt::NoModifier, QString(QChar(Qt::Key_1)));

            break;

        case KPD_EVENT_2:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_2,        Qt::NoModifier, QString(QChar(Qt::Key_2)));

            break;

        case KPD_EVENT_3:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_3,        Qt::NoModifier, QString(QChar(Qt::Key_3)));

            break;

        case KPD_EVENT_4:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_4,        Qt::NoModifier, QString(QChar(Qt::Key_4)));

            break;

        case KPD_EVENT_5:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_5,        Qt::NoModifier, QString(QChar(Qt::Key_5)));

            break;

        case KPD_EVENT_6:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_6,        Qt::NoModifier, QString(QChar(Qt::Key_6)));

            break;

        case KPD_EVENT_7:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_7,        Qt::NoModifier, QString(QChar(Qt::Key_7)));

            break;

        case KPD_EVENT_8:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_8,        Qt::NoModifier, QString(QChar(Qt::Key_8)));

            break;

        case KPD_EVENT_9:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_9,        Qt::NoModifier, QString(QChar(Qt::Key_9)));

            break;

        case KPD_EVENT_10:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_0,        Qt::NoModifier, QString(QChar(Qt::Key_0)));

            break;

        default:

            return;
    }

    QApplication::postEvent(QApplication::activeWindow() , key);
}
void MainWidget::passKeypadEvent(unsigned char code)
{
    QKeyEvent	*key = NULL;

    //qDebug("%s(): key = %x, operationMode = %d \n", __func__, code, operationMode);

    switch (code) 
    {
        case KPD_EVENT_ESC:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Escape,   Qt::NoModifier, QString(QChar(Qt::Key_Escape)));

            break;

        case KPD_EVENT_UP:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up,       Qt::NoModifier, QString(QChar(Qt::Key_Up)));

            break;

        case KPD_EVENT_LEFT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left,     Qt::NoModifier, QString(QChar(Qt::Key_Left)));

            break;

        case KPD_EVENT_SELECT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter,    Qt::NoModifier, QString(QChar(Qt::Key_Enter)));

            break;

        case KPD_EVENT_DOWN:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down,     Qt::NoModifier, QString(QChar(Qt::Key_Down)));

            break;

        case KPD_EVENT_RIGHT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right,    Qt::NoModifier, QString(QChar(Qt::Key_Right)));

            break;

        case KPD_EVENT_SETUP:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageUp,   Qt::NoModifier, QString(QChar(Qt::Key_PageUp)));

            break;

        case KPD_EVENT_SEARCH:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier, QString(QChar(Qt::Key_PageDown)));

            break;

        case KPD_EVENT_STATUS:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Bar, Qt::NoModifier, QString(QChar(Qt::Key_Bar)));

            break;

        case KPD_EVENT_PLAY_PAUSE:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Play, Qt::NoModifier, QString(QChar(Qt::Key_Play)));

            break;

        default:

            return;
    }

    QApplication::postEvent(QApplication::activeWindow() , key);
}
