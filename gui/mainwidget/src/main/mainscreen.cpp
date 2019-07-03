#include <QtGui>
#include <QPalette>
#include "videopane.h"
#include "mainwidget.h"
#include "playbardialog.h"
#include "search/searchdialog.h"
#include "login/logindialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "mainglobal.h"
#include "dev/Ver.h"
#include <core/Core.h>
#include "textmessagebox/textmessagedialog.h"
#include "statusbardialog.h"

void MainWidget::createVideoPane(int isReset)
{
    QString str;

    int paneWidth  = (int)(mainWidth  / getMaxSplit());
    int paneHeight = (int)(mainHeight / getMaxSplit());

    qDebug("%s + \n", __func__);

    //for(int ii = 0; ii < devInfo.videoNum; ii++)
    for(int ii = 0; ii < 8; ii++)
    {
        QByteArray text = QByteArray::fromHex((char *)DisplayCfg.channel_name[ii]);

        str = QString::fromUtf8(text.data());

        videoPane[ii] = new VideoPane(ii, str, this);
        videoPane[ii]->resize(paneWidth, paneHeight);
        videoPane[ii]->move((ii%getMaxSplit()) * paneWidth, (ii/getMaxSplit()) * paneHeight);

        connect(videoPane[ii], SIGNAL(videoPaneMouseRightClicked  (int)), this, SLOT(videoPaneRightClicked  (int)));
        connect(videoPane[ii], SIGNAL(videoPaneMouseClicked       (int)), this, SLOT(videoPaneClicked       (int)));
        connect(videoPane[ii], SIGNAL(videoPaneMouseDoubleClicked (int)), this, SLOT(videoPaneDoubleClicked (int)));
    }

    QByteArray text = QByteArray::fromHex((char *)DisplayCfg.channel_name[0]);

    str = QString::fromUtf8(text.data());

    if(isReset)
    {
        ;
    }
    else
    {
        currentSplit      = getMaxSplit();
        currentChannelNum = 0;
        splitStartChNum   = 0;

        //for(int ii = 0; ii < devInfo.videoNum+1; ii++)
        for(int ii = 0; ii < 8; ii++)
        {
            videoPane[ii]->hide();
        }
    }

    previousAudioCh = cfgMain.gbl.audioOut;

    qDebug("%s - \n", __func__);
}
void MainWidget::videoPaneClicked(int ch)
{
    if(systemLocked == 1)
    {
        return;
    }

    currentChannelNum = ch;
}
void MainWidget::videoPaneDoubleClicked(int ch)
{
    if(systemLocked)
    {
        return;
    }

    if(isTrigger && operationMode == OPMODE_LIVE)
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

        delete msgBox;
        msgBox = NULL;
        return;
    }

    if(operationMode == OPMODE_PLAYBACK)
    {
        if(!(mainPbChannel & (0x01<<ch)))
        {
            qDebug("%s(%d)", "No Data", ch);
            return;
        }
    }

    currentChannelNum = ch;

    mouseDoubleClickedFlag = 1;

    rotateSplit();

    mouseDoubleClickedFlag = 0;
}
void MainWidget::videoPaneRightClicked(int ch)
{
    if(systemLocked)
    {
        return;
    }

    QPoint curPos, menuPos;

    currentChannelNum = ch;

    if(operationMode == OPMODE_LIVE)
    {
        if(isTrigger)
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

            delete msgBox;
            msgBox = NULL;
        }
        else
        {
            if(mainMenu->isHidden())
            {
                curPos.setX((mainWidth  - mainMenu->width())  / 2);
                curPos.setY((mainHeight - mainMenu->height()) / 2);

                mainMenu->move(curPos);
                mainMenu->initMainMenu();
                mainMenu->show();
            }
        }
    }

    if(operationMode == OPMODE_PLAYBACK)
    {
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, currentChannelNum);
    }
}
int MainWidget::getMaxSplit()
{
#if 0
    if(devInfo.videoNum == 1)
    {
        return Split_1;
    }
    else if(devInfo.videoNum > 1 && devInfo.videoNum <= 4)
    {
        return Split_4;
    }
    else if(devInfo.videoNum > 4 && devInfo.videoNum <= 9)
    {
        return Split_9;
    }
    else
    {
        return Split_16;
    }
#else
    return Split_9;
#endif
}
int MainWidget::isMaxSplit()
{
    int isMax = 0;
#if 0
    switch(currentSplit)
    {
        case Split_1:  { if(devInfo.videoNum <=  1) isMax = 1; break; }
        case Split_4:  { if(devInfo.videoNum <=  4) isMax = 1; break; }
        case Split_9:  { if(devInfo.videoNum <=  9) isMax = 1; break; }
        case Split_16: { if(devInfo.videoNum <= 16) isMax = 1; break; }
    }
#else
    if( currentSplit == 8 || currentSplit == 9 ) { isMax=1; }
#endif
    return isMax;
}
void MainWidget::oneChannelSplit(int ch)
{
    //for(int ii = 0; ii < devInfo.videoNum; ii++)
    for(int ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->zoomAction = false;
    }

    if(operationMode == OPMODE_PLAYBACK && SelectPbSplit == Split_1)
    {
        return;
    }

    //if(devInfo.videoNum > ch)
    if(8 > ch)
    {
        if(currentChannelNum == ch && currentSplit == Split_1)
        {
            qDebug("\n\t 1 oneChannelSplit(), ch[%d], currentSplit[%d] \n", ch, currentSplit);
            return;
        }

        qDebug("\n\t 2 oneChannelSplit(), ch[%d], currentSplit[%d] \n", ch, currentSplit);

        videoPaneClicked(ch);

        if(currentSplit == Split_1)
        {
            currentSplit = Split_4;
        }

        splitScreen(Split_1);
    }
}
void MainWidget::updateGpsStatus()
{
    int currentStatus=appmgr_get_gps_connected();

    //for(int i=0; i<devInfo.videoNum; i++)
    for(int i=0; i<8; i++)
    {
        videoPane[i]->setGpsStatus(0);
    }

    if( isTrigger )
    {
        videoPane[sensorEventPopupCh]->setGpsStatus(currentStatus);
    }
    else
    {
        if( currentSplit == Split_1 )
        {
            videoPane[currentChannelNum]->setGpsStatus(currentStatus);
        }
        else
        {
            videoPane[ (currentChannelNum/(currentSplit*currentSplit))*(currentSplit*currentSplit)+(currentSplit-1) ]->setGpsStatus(currentStatus);
        }
    }
}
void MainWidget::eventPopupOneChannel(int type, int ch)
{
    int ii = 0, split = 0;
    int paneWidth, paneHeight;

    //for(ii = 0; ii < devInfo.videoNum; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->zoomAction = false;
        videoPane[ii]->setAudioOutput(0);
    }

    //for(ii = 0; ii < devInfo.videoNum+1; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->hide();
    }

    //if(devInfo.videoNum > ch)
    if(8 > ch)
    {
        if(type == EVENT_POPUP_SENSOR_ON)
        {
            if(mainMenu)
            {
                if(mainMenu->isVisible())
                {
                    mainMenu->onButtonClose();
                }
            }

            if(loginDialog)
            {
                if(loginDialog->isVisible())
                {
                    if(loginDialog->keyboardDialog)
                    {
                        if(loginDialog->keyboardDialog->isVisible())
                        {
                            loginDialog->keyboardDialog->reject();
                        }
                    }

                    loginDialog->reject();
                }
            }

            if(statusBar)
            {
                if(statusBar->isVisible())
                {
                    statusBar->setSplitMode(false);
                }
            }

            isTrigger = 1;

            //save previousAudioCh, when trigger occurred
            if(currentSplit!=Split_1)
            {
                previousAudioCh=audioStatus;
            }

            videoPane[ch]->setGpsStatus(appmgr_get_gps_connected());

            triggerAudioOut(ch);

            qDebug("\n\t %s() + : ch[%d], EVENT_POPUP_SENSOR_ON \n", __func__, ch);

            paneWidth  = (int)(mainWidth  / Split_1);
            paneHeight = (int)(mainHeight / Split_1);

            appmgr_set_video_split(ch, Split_1);

            sensorEventPopupCh = ch;

            videoPane[ch]->resize(paneWidth, paneHeight);
            videoPane[ch]->move((0%Split_1) * paneWidth, (0/Split_1) * paneHeight);

            if(ver_get_oem() == OEM_DAEJI)
            {
                if(ch == 2 && mainHeight == 720)
                {
                    videoPane[ch]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_1280x720);
                }
                else if(ch == 2 && mainHeight == 1080)
                {
                    videoPane[ch]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_1920x1080);
                }
            }

            videoPane[ch]->show();
            emit updateSplitButton();
            emit updateTriggerState(isTrigger);
        }
        else if(type == EVENT_POPUP_SENSOR_OFF)
        {
            isTrigger = 0;

            updateGpsStatus();

            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, sensorEventPopupCh);

            videoPane[sensorEventPopupCh]->setAudioOutput(0);

            if(audioStatus != LIVE_AUDIO_MUTE)
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
                videoPane[audioStatus-2]->setAudioOutput(1);
            }

            qDebug("\n\t %s() + : ch[%d], EVENT_POPUP_SENSOR_OFF \n", __func__, ch);

            if(currentSplit == Split_1)
            {
                splitScreen(Split_4);
            }
            else
            {
                split        = currentSplit;
                currentSplit = Split_1;

                splitScreen(split);
            }

            emit updateTriggerState(isTrigger);
        }
    }
}
void MainWidget::rotateSplit()
{
    int ret = -1;

    if(operationMode <= OPMODE_INIT)
    {
        return;
    }

    //for(int ii = 0; ii < devInfo.videoNum; ii++)
    for(int ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->zoomAction = false;
    }

    if(SelectPbSplit == Split_1)
    {
        return;
    }

    if(splitFlag)
    {
        qDebug("\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    qDebug("%s(): currentSplit[%d], currentChannelNum[%d], splitStartChNum[%d], currentSplit[%d] \n", __func__,currentSplit,currentChannelNum,splitStartChNum,currentSplit);

    if(mouseDoubleClickedFlag)
    {
        switch(currentSplit)
        {
            case Split_1:
            {
                if(currentSplitOld != Split_1)
                {
                    ret = splitScreen(currentSplitOld);
                }

                break;
            }
            default:
            {
                currentSplitOld = currentSplit;
                ret             = splitScreen(Split_1);
                break;
            }
        }
    }
    else
    {
        switch(currentSplit)
        {
            case Split_1:
            {
                if(devInfo.videoNum <= 4)       { ret = splitScreen(Split_4);  }
                else if(devInfo.videoNum <= 9)  { ret = splitScreen(Split_9);  }
                else if(devInfo.videoNum <= 16) { ret = splitScreen(Split_16); }

                break;
            }
            default :
            {
                ret = splitScreen(Split_1);
                break;
            }
        }
    }
}
void MainWidget::rotateOneChannel(int ch)
{
    int ii, paneWidth, paneHeight;
    int split = currentSplit;

    //for(ii = 0; ii < devInfo.videoNum; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->zoomAction = false;
    }

    if(splitFlag)
    {
        qDebug("\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    splitFlag = 1;

    qDebug("%s + ch = %d \n", __func__, ch);

    paneWidth  = (int)(mainWidth  / split);
    paneHeight = (int)(mainHeight / split);

    //for(ii = 0; ii < devInfo.videoNum+1; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->hide();
    }

    splitStartChNum = currentChannelNum = ch;

    appmgr_set_video_split(currentChannelNum, Split_1);

    videoPane[currentChannelNum]->resize(paneWidth, paneHeight);
    videoPane[currentChannelNum]->move((0%Split_1) * paneWidth, (0/Split_1) * paneHeight);
    videoPane[currentChannelNum]->show();

    splitFlag = 0;

    emit updateSplitButton();
    qDebug("%s - \n", __func__);
}
int MainWidget::splitScreen(int split)
{
    //for(int ii = 0; ii < devInfo.videoNum; ii++)
    for(int ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->setZoomOut();
    }

    qDebug("===============================");

    int ii = 0, splitPage = 0, firstCh = 0;
    int paneWidth, paneHeight;
    int pbPreState   = 0;
    int rotate4Split = 0;

    if(SelectPbSplit == Split_1)
    {
        return split;
    }

    if(split > SPLIT_MAX - 1)
    {
        return customSplitScreen(split);
    }

    if(splitFlag)
    {
        qDebug("\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return split;
    }

    splitFlag = 1;

    qDebug("%s + \n", __func__);
    qDebug("%s(): currentChannelNum[%d], split[%d], currentSplit[%d] \n", __func__, currentChannelNum, split, currentSplit);

    if(operationMode == OPMODE_PLAYBACK)
    {
        if(playBar->GetStatePausePlay() == PB_PLAY)
        {
            pbPreState = PB_PLAY;
            playBar->PausePlayChange(PB_PAUSE);
        }
    }

    if(split > getMaxSplit())
    {
        split = getMaxSplit();
    }

    //for(ii = 0; ii < devInfo.videoNum+1; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->hide();
    }

    paneWidth  = (int)(mainWidth  / split);
    paneHeight = (int)(mainHeight / split);

    splitPage       = (currentChannelNum / (split * split));
    firstCh         = splitPage * (split * split);
    splitStartChNum = firstCh;

    if(rotate4Split != 1)
    {
        currentSplit = split;
    }

    qDebug("%s(): splitPage[%d], currentChannelNum[%d], splitStartChNum[%d], currentSplit[%d] \n", __func__, splitPage, currentChannelNum, splitStartChNum, currentSplit);

    if(split == Split_1)
    {
        appmgr_set_video_split(currentChannelNum, (split * split));

        if(previousSplit != split)
        {
            previousAudioCh = audioStatus;
        }

        if(audioStatus != 0)
        {
            setAudioOutCh(currentChannelNum+2);
        }

        emit updateSplitButton();
    }
    else
    {
        appmgr_set_video_split(splitStartChNum, (split * split));
        setAudioOutCh(previousAudioCh);

        emit updateSplitButton();
    }

    //for(ii = 0; ii < devInfo.videoNum; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        int vidCh = firstCh + ii;

        //if(vidCh >= devInfo.videoNum)
        if(vidCh >= 8)
        {
            //vidCh -= devInfo.videoNum;
            vidCh -= 8;
        }

        videoPane[vidCh]->resize( paneWidth, paneHeight);
        videoPane[vidCh]->move((ii%split) * paneWidth, (ii/split) * paneHeight);

        if(ver_get_oem() == OEM_DAEJI)
        {
            if(mainHeight == 720)
            {
                if(split == Split_4 && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_640x360);
                }
                else if(split == Split_1 && currentChannelNum == ii && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_1280x720);
                }
            }
            else if(mainHeight == 1080)
            {
                if(split == Split_4 && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_960x540);
                }
                else if(split == Split_1 && currentChannelNum == ii && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_1920x1080);
                }
            }
        }

        videoPane[vidCh]->show();
    }

    updateGpsStatus();

    if(operationMode == OPMODE_PLAYBACK)
    {
        if(pbPreState == PB_PLAY)
        {
            playBar->PausePlayChange(PB_PLAY);
        }

        emit splitChangeNotify(split);
    }

    splitFlag = 0;

    qDebug("%s - \n", __func__);

    previousSplit = split;

    emit updateAudioButton();

    return split;
}
void MainWidget::setSplitScreen(int startCh, int selectCh, int split)
{
    currentSplitOld=currentSplit;
    currentSplit = split;
    currentChannelNum=selectCh;

    int ii = 0, paneWidth = 0, paneHeight = 0, splitPage = 0, firstCh = 0;

    if(splitFlag)
    {
        qDebug("\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    splitFlag = 1;

    qDebug("%s + \n", __func__);

    if(split > getMaxSplit())
    {
        split = getMaxSplit();
    }

    //for(ii = 0; ii < devInfo.videoNum+1; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->hide();
    }

    paneWidth  = (int)(mainWidth  / split);
    paneHeight = (int)(mainHeight / split);

    videoPaneClicked(selectCh);

    splitPage       = (currentChannelNum / (split * split));
    firstCh         = (splitPage         * (split * split));
    splitStartChNum = firstCh;
    currentSplit    = split;

    //for(ii = 0; ii < devInfo.videoNum; ii++)
    for(ii = 0; ii < 8; ii++)
    {
        int vidCh = firstCh + ii;

        //if(vidCh >= devInfo.videoNum)
        if(vidCh >= 8)
        {
            //vidCh -= devInfo.videoNum;
            vidCh -= 8;
        }

        videoPane[vidCh]->resize(paneWidth, paneHeight);
        videoPane[vidCh]->move((ii%split) * paneWidth, (ii/split) * paneHeight);

        if(ver_get_oem() == OEM_DAEJI)
        {
            if(mainHeight == 720)
            {
                if(split == Split_4 && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_640x360);
                }
                else if(split == Split_1 && currentChannelNum == ii && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_1280x720);
                }
            }
            else if(mainHeight == 1080)
            {
                if(split == Split_4 && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_960x540);
                }
                else if(split == Split_1 && currentChannelNum == ii && ii == 2)
                {
                    videoPane[ii]->DisplayLogo(OEM_DAEJI, RESOLUTION_HD_1920x1080);
                }
            }
        }

        videoPane[vidCh]->show();
    }

    qDebug(" %s(), done startch %d, cursel %d, split %d", __func__, startCh, selectCh, split);
    qDebug("%s + \n", __func__);

    QCoreApplication::processEvents();

    if(split == Split_1)
    {
        appmgr_set_video_split(currentChannelNum, split * split);
        emit updateSplitButton();
    }
    else
    {
        appmgr_set_video_split(splitStartChNum, split * split);
        emit updateSplitButton();
    }

    splitFlag = 0;
    updateGpsStatus();

    qDebug("%s - \n", __func__);
}
int MainWidget::customSplitScreen(int split)
{
    return split;
}
void MainWidget::showOsd(int show)
{
    isShowOsd = show;

    qDebug("showOsd-> %d", show);

    //for(int ii = 0; ii < devInfo.videoNum; ii++)
    for(int ii = 0; ii < 8; ii++)
    {
        videoPane[ii]->setOsdEnable(1);
    }
}
void MainWidget::audioSetting(int preChannel, int curChannel)
{
    if(preChannel == curChannel)
    {
        return;
    }

    audioStatus = curChannel + LIVE_AUDIO_SINGLE_1;

    (void) utils_set_audio_output(audioStatus);

    if(operationMode == OPMODE_LIVE)
    {
        cfgMain.gbl.audioOut = audioStatus;
        appmgr_save_setup(3, &cfgMain);
    }

    //if(curChannel >= (devInfo.videoNum - devInfo.videoIPNum))
    if(curChannel >= (8 - devInfo.videoIPNum))
    {
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, audioStatus-2);
    }
    else
    {
        if(cfgMain.live.display_ch[audioStatus-2])
        {
            appmgr_set_audio_output_mix(AUDIO_PB, audioStatus-2);
        }
        else
        {
            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
        }
    }
}
void MainWidget::triggerAudioOut(int ch)
{
    //if trigger_audio is mute, set Audio mute
    switch(ch)
    {
        case 0 :
        {
            if(utils_cfg_cmp_item(DeviceCfg.trigger1_audio, "MUTE") == 0)
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, ch);
                videoPane[ch]->setAudioOutput(0);
            }
            else
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
                videoPane[ch]->setAudioOutput(1);
            }
            break;
        }
        case 1 :
        {
            if(utils_cfg_cmp_item(DeviceCfg.trigger2_audio, "MUTE") == 0)
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, ch);
                videoPane[ch]->setAudioOutput(0);
            }
            else
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
                videoPane[ch]->setAudioOutput(1);
            }
            break;
        }
        case 2 :
        {
            if(utils_cfg_cmp_item(DeviceCfg.trigger3_audio, "MUTE") == 0)
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, ch);
                videoPane[ch]->setAudioOutput(0);
            }
            else
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
                videoPane[ch]->setAudioOutput(1);
            }
            break;
        }
        case 3 :
        {
            if(utils_cfg_cmp_item(DeviceCfg.trigger4_audio, "MUTE") == 0)
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, ch);
                videoPane[ch]->setAudioOutput(0);
            }
            else
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
                videoPane[ch]->setAudioOutput(1);
            }
            break;
        }
        default :
        {
            appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
            videoPane[ch]->setAudioOutput(1);
            break;
        }
    }
}
