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

void MainWidget::createVideoPane(int isReset)
{
    QString str;

    int paneWidth  = (int)(mainWidth  / getMaxSplit());
    int paneHeight = (int)(mainHeight / getMaxSplit());

    qDebug("%s + \n", __func__);

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        QByteArray text = QByteArray::fromHex((char *)DisplayCfg.channel_name[i]);

        str = QString::fromUtf8(text.data());

        videoPane[i] = new VideoPane(i, str, this);
        videoPane[i]->resize( paneWidth, paneHeight);
        videoPane[i]->move((i%getMaxSplit()) * paneWidth, (i/getMaxSplit()) * paneHeight);

        connect(videoPane[i], SIGNAL(videoPaneMouseRightClicked(int)),  this, SLOT(videoPaneRightClicked(int)));
        connect(videoPane[i], SIGNAL(videoPaneMouseClicked(int)),       this, SLOT(videoPaneClicked(int)));
        connect(videoPane[i], SIGNAL(videoPaneMouseDoubleClicked(int)), this, SLOT(videoPaneDoubleClicked(int)));
    }

    QByteArray text = QByteArray::fromHex((char *)DisplayCfg.channel_name[0]);

    str = QString::fromUtf8(text.data());

    videoPane[devInfo.videoNum] = new VideoPane(devInfo.videoNum, str, this);

    paneWidth  = (int)(mainWidth  / Split_9);
    paneHeight = (int)(mainHeight / Split_9);

    videoPane[devInfo.videoNum]->resize(paneWidth, paneHeight);
    videoPane[devInfo.videoNum]->move((8%Split_9) * paneWidth, (8/Split_9) * paneHeight);

    if(isReset)
    {
        int i = 0, record = 0, prerecord = 0;

        for(i = 0; i < devInfo.videoNum; i++)
        {
            if(liveEvent.cameraLoss & (1<<i))
            {
                videoPane[i]->setVideoLossDetect(1);
            }
        }

        if(liveEvent.diskFull == 1)
        {
            for(i = 0; i < devInfo.videoNum; i++)
            {
                if(isShowOsd) { videoPane[i]->setOsdEnable(1); }
                else          { videoPane[i]->setOsdEnable(0); }

                record_icon_draw = 1;

                videoPane[i]->setRecordingDetect(0x0, 0x0, 0x0, 0x0);
            }
        }
        else
        {
            for(i = 0; i < devInfo.videoNum; i++)
            {
                if(isShowOsd) { videoPane[i]->setOsdEnable(1); }
                else          { videoPane[i]->setOsdEnable(0); }

                record    = (liveEvent.recordOn     & (1<<i));
                prerecord = (liveEvent.prerecordOn  & (1<<i));

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
        }

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            videoPane[i]->show();
        }

        splitFlag = 0;

        setSplitScreen(latestSplitStartChNum, latestChannelNum, latestSplit);
    }
    else
    {
        currentSplit      = getMaxSplit();
        currentChannelNum = 0;
        splitStartChNum   = 0;

        for(int i = 0; i < devInfo.videoNum+1; i++)
        {
            videoPane[i]->hide();
        }
    }

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

        msgBox = new TextMessageDialog(tr("NOTICE"), tr("NOTICE\n\nCurrent status is trigger."), 2, this);
        msgBox->setMsgAlignment(Qt::AlignCenter);
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

            msgBox = new TextMessageDialog(tr("NOTICE"), tr("NOTICE\n\nCurrent status is trigger."), 2, this);
            msgBox->setMsgAlignment(Qt::AlignCenter);
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
    else if(devInfo.videoNum == 10)
    {
        return Split_10;
    }
    else
    {
        return Split_16;
    }
}
int MainWidget::isMaxSplit()
{
    int isMax = 0;

    switch(currentSplit)
    {
        case Split_1:  { if(devInfo.videoNum <= 1)  isMax = 1; break; }
        case Split_4:  { if(devInfo.videoNum <= 4)  isMax = 1; break; }
        case Split_9:  { if(devInfo.videoNum <= 9)  isMax = 1; break; }
        case Split_16: { if(devInfo.videoNum <= 16) isMax = 1; break; }
    }

    return isMax;
}
void MainWidget::oneChannelSplit(int ch)
{
    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
    }

    if(operationMode == OPMODE_PLAYBACK && SelectPbSplit == Split_1)
    {
        return;
    }

    if(devInfo.videoNum > ch)
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
void MainWidget::onSetGpsStatus(int gps)
{
    if(currentSplit == Split_1)
    {
        videoPane[currentChannelNum]->setGpsStatus(gps);
    }
    else
    {
        videoPane[1]->setGpsStatus(gps);
    }
}
void MainWidget::eventPopupOneChannel(int type, int ch)
{
    int i = 0, split = 0;
    int paneWidth, paneHeight;

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
        videoPane[i]->setAudioOutput(0);
    }

    for(i = 0; i < devInfo.videoNum+1; i++)
    {
        videoPane[i]->hide();
    }

    if(devInfo.videoNum > ch)
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

            isTrigger = 1;

            videoPane[ch]->setGpsStatus(appmgr_get_gps_connected());

#if 0 //yjsin [18/01/19] Change audio scenarios during trigger operation. If audio mute, Trigger audio mute.
            if(audioStatus != LIVE_AUDIO_MUTE)
            {
                appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
                videoPane[ch]->setAudioOutput(1);
            }
#else
            appmgr_set_audio_output_mix(AUDIO_LIVE, ch);
            videoPane[ch]->setAudioOutput(1);
#endif

            qDebug("\n\t %s() + : ch[%d], EVENT_POPUP_SENSOR_ON \n", __func__, ch);

            paneWidth  = (int)(mainWidth/Split_1);
            paneHeight = (int)(mainHeight/Split_1);

            appmgr_set_video_split(ch, Split_1);

            sensorEventPopupCh = ch;

            videoPane[ch]->resize(paneWidth, paneHeight);
            videoPane[ch]->move((0%Split_1) * paneWidth, (0/Split_1) * paneHeight);
            videoPane[ch]->show();
        }
        else if(type == EVENT_POPUP_SENSOR_OFF)
        {
            isTrigger = 0;

            for(int ii = 0; ii < devInfo.videoNum; ii++)
            {
                if(ii != 1)
                {
                    videoPane[ii]->setGpsStatus(0);
                }
            }

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
        }
    }
}
void MainWidget::rotateSplit()
{
    int ret = -1;
    int tempCh;

    if(operationMode <= OPMODE_INIT)
    {
        return;
    }

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
    }

    if(SelectPbSplit == Split_1)
    {
        return;
    }

    if(splitFlag)
    {
        fprintf(stderr, "\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    qDebug("%s(): currentSplit[%d], currentChannelNum[%d], splitStartChNum[%d], currentSplit[%d] \n", __func__, currentSplit, currentChannelNum, splitStartChNum, currentSplit);

    if(mouseDoubleClickedFlag)
    {
        switch(currentSplit)
        {
            case Split_1:

                if(currentSplitOld != Split_1)
                {
                    if(currentSplitOld == Split_9)
                    {
                        tempCh            = currentChannelNum;
                        currentChannelNum = splitStartChNumOld;
                        ret               = splitScreen(currentSplitOld);
                        currentChannelNum = tempCh;

                        if(operationMode == OPMODE_PLAYBACK)
                        {
                            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, currentChannelNum);
                        }
                    }
                    else
                    {
                        ret = splitScreen(currentSplitOld);
                    }
                }

                break;

            case Split_9:

                splitStartChNumOld = splitStartChNum;

            case Split_4:
            case Split_10:
            case Split_16:
            case Split_17:

                currentSplitOld = currentSplit;

                ret = splitScreen(Split_1);

                break;
        }
    }
    else
    {
        switch(currentSplit)
        {
            case Split_1:

                if(devInfo.videoNum >= 4)
                {
                    ret = splitScreen(Split_4);
                }

                break;

            case Split_4:

                if(devInfo.videoNum <= 4)
                {
                    ret = splitScreen(Split_1);
                }
                else if(devInfo.videoNum >= 8)
                {
                    ret = splitScreen(Split_9);
                }

                break;

            case Split_9:

                if(devInfo.videoNum > 9)
                {
                    ret = splitScreen(Split_16);
                }
                else
                {
                    ret = splitScreen(Split_1);
                }

                break;

            case Split_16:

                ret = splitScreen(Split_1);

                break;

            case Split_17:

                ret = splitScreen(Split_1);

                break;
        }
    }
}
void MainWidget::rotateChannel(int forward)
{
    int i, paneWidth = 0, paneHeight = 0, splitPage, firstCh, focusPos;
    int split = currentSplit;
    int pbPreState = 0;

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
    }

    if(SelectPbSplit == Split_1)
    {
        return;
    }

    if(splitFlag)
    {
        fprintf(stderr, "\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    if( m_selectOther )
    {
        firstCh = currentChannelNum;
        goto _rotateProcess;
    }

    splitFlag = 1;

    qDebug("%s + \n", __func__);

    paneWidth  = (int)(mainWidth  / split);
    paneHeight = (int)(mainHeight / split);

    if(split == getMaxSplit())
    {
        if(forward)
        {
            if(++currentChannelNum >= devInfo.videoNum)
            {
                currentChannelNum = 0;
            }
        }
        else
        {
            if(--currentChannelNum < 0)
            {
                currentChannelNum = devInfo.videoNum-1;
            }
        }

        if(operationMode == OPMODE_PLAYBACK)
        {
            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, currentChannelNum);
        }

        splitFlag = 0;
        qDebug("%s - \n", __func__);
        return;
    }

    if(operationMode == OPMODE_PLAYBACK)
    {
        if(playBar->GetStatePausePlay() == PB_PLAY)
        {
            pbPreState = PB_PLAY;
            playBar->PausePlayChange(PB_PAUSE);
        }
    }

    for(i = 0; i < devInfo.videoNum+1; i++)
    {
        videoPane[i]->hide();
    }

    firstCh  = splitStartChNum;
    focusPos = currentChannelNum%(split*split);

    if(currentChannelNum < firstCh)
    {
        if(currentChannelNum == 0)
        {
            focusPos = 7;
        }
        else if(currentChannelNum == 1)
        {
            focusPos = 8;
        }
    }

    if(forward)
    {
        firstCh += (split*split);

        if(firstCh >= devInfo.videoNum)
        {
            firstCh -= devInfo.videoNum;
        }

        splitPage         = firstCh   / (split * split);
        firstCh           = splitPage * (split * split);
        currentChannelNum = firstCh+focusPos;

        if(currentChannelNum >= devInfo.videoNum)
        {
            currentChannelNum -= devInfo.videoNum;
        }
    }
    else
    {
        firstCh -= (split*split);

        if(firstCh < 0)
        {
            firstCh += devInfo.videoNum;

            if(firstCh < (split *split))
            {
                firstCh += ((split*split*2) - devInfo.videoNum);
            }
        }

        splitPage         = firstCh   / (split * split);
        firstCh           = splitPage * (split * split);
        currentChannelNum = firstCh   + focusPos;

        if(currentChannelNum >= devInfo.videoNum)
        {
            currentChannelNum -= devInfo.videoNum;
        }
    }

_rotateProcess:

    splitStartChNum = firstCh;

    QCoreApplication::processEvents();

    if(split == Split_1)
    {
        appmgr_set_video_split(currentChannelNum, split * split);
    }
    else if(split == Split_10)
    {
        appmgr_set_video_split(splitStartChNum, Split_10);
    }
    else if(split == Split_17)
    {
        appmgr_set_video_split(splitStartChNum, Split_17);
    }
    else
    {
        appmgr_set_video_split(splitStartChNum, split * split);
    }

    if(operationMode == OPMODE_PLAYBACK)
    {
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, currentChannelNum);
    }
    else if(operationMode == OPMODE_LIVE)
    {
        ;
    }

    if(split == Split_10)
    {
        for(i = 0; i < devInfo.videoNum; i++)
        {
            int vidCh = firstCh + i;

            if(vidCh >= devInfo.videoNum)
            {
                vidCh -= devInfo.videoNum;
            }

            if(i == 8 || i == 9)
            {
                paneWidth  = (int)(mainWidth  / Split_4);
                paneHeight = (int)(mainHeight / Split_4);

                videoPane[vidCh]->resize(paneWidth, paneHeight);
                videoPane[vidCh]->move(((i-6)%Split_4) * paneWidth, ((i-6)/Split_4) * paneHeight);
            }
            else
            {
                paneWidth  = (int)(mainWidth  / Split_16);
                paneHeight = (int)(mainHeight / Split_16);

                videoPane[vidCh]->resize(paneWidth, paneHeight);
                videoPane[vidCh]->move((i%Split_16) * paneWidth, (i/Split_16) * paneHeight);
            }

            videoPane[vidCh]->show();
        }
    }
    else if((split == Split_9) && (devInfo.videoNum == 8 || devInfo.videoNum == 16))
    {
        for(i = 0; i < (split * split - 1); i++)
        {
            int vidCh = firstCh + i;

            if(vidCh >= devInfo.videoNum)
            {
                vidCh -= devInfo.videoNum;
            }

            videoPane[vidCh]->resize(paneWidth, paneHeight);
            videoPane[vidCh]->move((i%split) * paneWidth, (i/split) * paneHeight);
            videoPane[vidCh]->show();
        }

        videoPane[devInfo.videoNum]->resize(paneWidth, paneHeight);
        videoPane[devInfo.videoNum]->move((8%split) * paneWidth, ((8)/split) * paneHeight);
        videoPane[devInfo.videoNum]->show();
    }
    else if(split == Split_17)
    {
        int x = 3, y = 0;

        paneWidth  = (int)(mainWidth  / 4);
        paneHeight = (int)(mainHeight / 4);

        videoPane[firstCh]->resize(paneWidth*3, paneHeight*3);
        videoPane[firstCh]->move(0, 0);
        videoPane[firstCh]->show();

        for(i = 0; i < devInfo.videoNum; i++)
        {
            if(i != firstCh)
            {
                videoPane[i]->resize(paneWidth, paneHeight);
                videoPane[i]->move(x*paneWidth, y*paneHeight);
                videoPane[i]->show();

                if(x == 3)
                {
                    y++;

                    if(y == 3)
                    {
                        x = 0;
                    }
                }
                else
                {
                    x++;
                }
            }
        }
    }
    else
    {
        for(i = 0; i < (split*split); i++)
        {
            int vidCh = firstCh + i;

            if(vidCh >= devInfo.videoNum)
            {
                vidCh -= devInfo.videoNum;
            }

            videoPane[vidCh]->resize(paneWidth, paneHeight);
            videoPane[vidCh]->move((i%split) * paneWidth, (i/split) * paneHeight);
            videoPane[vidCh]->show();
        }
    }

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
}
void MainWidget::rotateOneChannel(int ch)
{
    int i, paneWidth, paneHeight;
    int split = currentSplit;

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->zoomAction = false;
    }

    if(splitFlag)
    {
        fprintf(stderr, "\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    splitFlag = 1;

    qDebug("%s + ch = %d \n", __func__, ch);

    paneWidth  = (int)(mainWidth  / split);
    paneHeight = (int)(mainHeight / split);

    for(i = 0; i < devInfo.videoNum+1; i++)
    {
        videoPane[i]->hide();
    }

    splitStartChNum = currentChannelNum = ch;

    appmgr_set_video_split(currentChannelNum, Split_1);

    videoPane[currentChannelNum]->resize(paneWidth, paneHeight);
    videoPane[currentChannelNum]->move((0%Split_1) * paneWidth, (0/Split_1) * paneHeight);
    videoPane[currentChannelNum]->show();

    splitFlag = 0;

    qDebug("%s - \n", __func__);
}
int MainWidget::splitScreen(int split)
{
    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->setZoomOut();
    }

    qDebug("===============================");

    int i = 0, splitPage = 0, firstCh = 0;
    int paneWidth, paneHeight;
    int pbPreState = 0;
    int rotate4Split = 0;
    int video_in_cnt = 0, video_in_ch = 0;
    int rotation_channel = 0;

    rotation_channel = cfgMain.live.rotation_channel[0] | (cfgMain.live.rotation_channel[1] << 8);

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
        fprintf(stderr, "\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return split;
    }

    if(split == -1 && currentSplit == Split_1)
    {
        for(i = 0; i < devInfo.videoNum; i++)
        {
            if(liveEvent.cameraLoss & (1 << i))
            {
                ;
            }
            else
            {
                if(rotation_channel & (1 << i))
                {
                    video_in_ch = i;
                    video_in_cnt++;
                }
            }
        }

        if(video_in_cnt == 0)
        {
            ;
        }
        else if(video_in_cnt == 1)
        {
            if(currentChannelNum != video_in_ch)
            {
                rotateOneChannel(video_in_ch);
            }
        }
        else
        {
            if(currentChannelNum >= video_in_ch)
            {
                for(i = 0; i < devInfo.videoNum; i++)
                {
                    if(liveEvent.cameraLoss & (1 << i))
                    {
                        ;
                    }
                    else
                    {
                        if(rotation_channel & (1 << i))
                        {
                            video_in_ch = i;
                            break;
                        }
                    }
                }

                rotateOneChannel(video_in_ch);
            }
            else
            {
                for(i = currentChannelNum+1; i < devInfo.videoNum; i++)
                {
                    if(liveEvent.cameraLoss & (1 << i))
                    {
                        ;
                    }
                    else
                    {
                        if(rotation_channel & (1 << i))
                        {
                            video_in_ch = i;
                            break;
                        }
                    }
                }

                rotateOneChannel(video_in_ch);
            }
        }

        return 0;
    }

    splitFlag = 1;

    qDebug("%s + \n", __func__);
    qDebug("%s(): currentChannelNum[%d], split[%d], currentSplit[%d] \n", __func__, currentChannelNum, split, currentSplit);

    if(split == currentSplit || split == -1)
    {
        splitFlag = 0;
        qDebug("%s - \n", __func__);

        rotateChannel(1);

        goto _end;
    }

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

    for(i = 0; i < devInfo.videoNum+1; i++)
    {
        videoPane[i]->hide();
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
        appmgr_set_video_split(currentChannelNum, split * split);
    }
    else if(split == Split_10)
    {
        appmgr_set_video_split(splitStartChNum, Split_10);
    }
    else if(split == Split_17)
    {
        appmgr_set_video_split(splitStartChNum, Split_17);
    }
    else
    {
        appmgr_set_video_split(splitStartChNum, split * split);
    }

    if(split == Split_1)
    {
        videoPane[currentChannelNum]->setGpsStatus(appmgr_get_gps_connected());
    }

    for(i = 0; i < devInfo.videoNum; i++)
    {
        int vidCh = firstCh + i;

        if(vidCh >= devInfo.videoNum)
        {
            vidCh -= devInfo.videoNum;
        }

        if(split == Split_4 && i != 1)
        {
            videoPane[i]->setGpsStatus(0);
        }

        videoPane[vidCh]->resize( paneWidth, paneHeight);
        videoPane[vidCh]->move((i%split) * paneWidth, (i/split) * paneHeight);
        videoPane[vidCh]->show();
    }

    if(operationMode == OPMODE_PLAYBACK)
    {
        if(pbPreState == PB_PLAY)
        {
            playBar->PausePlayChange(PB_PLAY);
        }

        emit splitChangeNotify(split);
    }

_end:

    splitFlag = 0;

    qDebug("%s - \n", __func__);

    return split;
}
void MainWidget::setSplitScreen(int startCh, int selectCh, int split)
{
    int i = 0, paneWidth = 0, paneHeight = 0, splitPage = 0, firstCh = 0;

    if(splitFlag)
    {
        fprintf(stderr, "\n\n\t %s(), splitFlag(%d) \n", __func__, splitFlag);
        return;
    }

    splitFlag = 1;

    qDebug("%s + \n", __func__);

    if(split > getMaxSplit())
    {
        split = getMaxSplit();
    }

    for(i = 0; i < devInfo.videoNum+1; i++)
    {
        videoPane[i]->hide();
    }

    paneWidth  = (int)(mainWidth  / split);
    paneHeight = (int)(mainHeight / split);

    videoPaneClicked(selectCh);

    splitPage       = (currentChannelNum / (split * split));
    firstCh         = splitPage*(split*split);
    splitStartChNum = firstCh;
    currentSplit    = split;

    for(i = 0; i < devInfo.videoNum; i++)
    {
        int vidCh = firstCh + i;

        if(vidCh >= devInfo.videoNum)
        {
            vidCh -= devInfo.videoNum;
        }

        videoPane[vidCh]->resize(paneWidth, paneHeight);
        videoPane[vidCh]->move((i%split) * paneWidth, (i/split) * paneHeight);
        videoPane[vidCh]->show();
    }

    qDebug(" %s(), done startch %d, cursel %d, split %d", __func__, startCh, selectCh, split);
    qDebug("%s + \n", __func__);

    QCoreApplication::processEvents();

    if(split == Split_1)
    {
        appmgr_set_video_split(currentChannelNum, split * split);
    }
    else
    {
        appmgr_set_video_split(splitStartChNum, split * split);
    }

    splitFlag = 0;

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

    for(int i = 0; i < devInfo.videoNum; i++)
    {
        videoPane[i]->setOsdEnable(1);
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

    if(curChannel >= (devInfo.videoNum - devInfo.videoIPNum))
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
