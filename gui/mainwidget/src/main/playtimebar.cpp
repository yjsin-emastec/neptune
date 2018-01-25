#include <QtGui>
#include "playtimebar.h"
#include "main/mainglobal.h"

#define TL_LEFT_MARGIN  250
#define TL_WIDTH        960

static int gFlagTimeReceived = 0;

PlayTimeBar::PlayTimeBar(QWidget *parent)
    : QWidget(parent)
{
    xPos                    = -1;
    yPos                    = -1;
    isTimeBarDrag           = false;
    isPbTimeChanged         = false;
    isRepaintByTimeOver     = false;
    isSliderChanged         = false;
    timeDisplayFormat       = 0;
    lastTickPos             = 0;
    dlsEndHour              = -1;
    lastPbTime              = 0;
    resizeTimeLine_LeftGap  = 0;

    setPalette(QPalette(QColor(39, 0, 79)));
    setAutoFillBackground(true);

    labelDate = new QLabel(tr(""), this);
    labelTime = new QLabel(tr(""), this);

    labelDate->setStyleSheet("font-weight:bold; font-size:32px;");
    labelTime->setStyleSheet("font-weight:bold; font-size:32px;");

    labelDate->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelTime->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    sliderPlayTime = new QSlider(Qt::Horizontal, this);
    sliderPlayTime->setFocusPolicy(Qt::NoFocus);

    sliderPlayTime->setStyleSheet("QSlider { height: 50px; margin: 1px 5px}"
            "::groove { border: 50px; height: 50px; background-color: rgb(0,0,255,127);}"
            "::handle { image: url(:/images/slider_handle.png); width: 100px; margin: -30px -30px}");

    sliderPlayTime->move(TL_LEFT_MARGIN - 6, 25);
    sliderPlayTime->setRange(0, TL_WIDTH - 1);
    sliderPlayTime->resize(TL_WIDTH - 1 + 12, 18);
    sliderPlayTime->show();


    labelDate->setMinimumWidth(250);
    labelDate->move(30, 0);
    labelTime->setMinimumWidth(250);
    labelTime->move(30, 35);

    labelDate->show();
    labelTime->show();

    connect(sliderPlayTime, SIGNAL(valueChanged(int)), this, SLOT(timeSliderChanged(int)));
    connect(sliderPlayTime, SIGNAL(sliderReleased()),  this, SLOT(timeSliderReleased()));
    connect(sliderPlayTime, SIGNAL(sliderMoved(int)),  this, SLOT(timeSliderMoved(int)));

    sliderPlayTime->setLayoutDirection(Qt::LeftToRight);
}
void PlayTimeBar::setDlsEndDay(int endHour)
{
    dlsEndHour = endHour;
    lastPbTime = timeLogSelTime;

    if(dlsEndHour >= 0)
    {
        int width = TL_WIDTH + (TL_WIDTH / 24);
        sliderPlayTime->setRange(0, width - 1);
        sliderPlayTime->resize(width - 1 + 10, 18);
    }
    else
    {
        sliderPlayTime->setRange(0, TL_WIDTH - 1);
        sliderPlayTime->resize(TL_WIDTH + 1 + 12, 18);
    }

    // reset label
    labelDate->setText(tr(""));
    labelTime->setText(tr(""));
    updateTimeLinePixmap();
    update();
}
void PlayTimeBar::paintEvent(QPaintEvent *event)
{
    if(EventSearchPB)
    {
        return;
    }

    QStylePainter painter(this);

    painter.drawPixmap(0, 0, timeLinepixmap);

    if(xPos > 0 && yPos > 0)
    {
        painter.setPen(QColor(255, 0, 0));
        painter.setBrush(QColor(255, 0, 0)); // video data
        QRect bar(xPos, 1, 2, 66);
        painter.drawRect(bar);
    } 
    else
    {
        painter.setPen(QColor(255, 0, 0));
        painter.setBrush(QColor(255, 0, 0)); // video data
        QRect bar(TL_LEFT_MARGIN, 1, 2, 66);
        painter.drawRect(bar);
    }
}
void PlayTimeBar::updateTimeLinePixmap()
{
    if(EventSearchPB)
    {
        return;
    }

    timeLinepixmap = QPixmap(size());
    timeLinepixmap.fill(this, 0, 0);
    QPainter painter(&timeLinepixmap);
    painter.initFrom(this);
    drawTimeLine(&painter);
}
void PlayTimeBar::drawTimeLine(QPainter *painter)
{
    QString  str;

    int      hourMax       = 24,
             videoStartPos = -1,
             videoEndPos   = -1,
             audioStartPos = -1,
             audioEndPos   = -1,
             tmpLast       = 0;

    bool     bVideoExist   = false,
             bAudioExist   = false;

    QRect    rect;

    if(EventSearchPB)
    {
        return;
    }

    if(lastTickPos && isRepaintByTimeOver)
    {
        tmpLast = lastTickPos + (resizeTimeLine_LeftGap + TL_LEFT_MARGIN);
        lastTickPos = 0;
    }

    painter->setBrush(QColor(255, 255, 255));

    qDebug("[CHECKPOINT] timelinepixmap draw position");

    if(dlsEndHour >= 0)
    {
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), 1, TL_WIDTH+(TL_WIDTH/24),  70);
        painter->drawRect(bar);
    }
    else
    {
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), 1, TL_WIDTH,  70);
        painter->drawRect(bar);
    }

    if(dlsEndHour >= 0)
    {
        hourMax = 25;
    }

    for(int k = 0; k < hourMax; k++)
    {
        //qDebug("%s() .... timeLog[%d].channel[0] = %x", __func__, k, timeLog[k].channel[0]);
        for(int i = 0; i < 20; i++) // 1hour = 20 pixel
        {
            bVideoExist = bAudioExist = false;

            for(int m = 0; m < 12; m++) // 1 pixel = 3 min. ( 15sec * 12 = 3 min)
            {
                int secPos = i * 12 + m;

                if(timeLog[k].channel[secPos] & 0xffff)
                {
                    bVideoExist = true;
                }

                if(timeLog[k].channel[secPos] & 0xffff0000)
                {
                    bAudioExist = true;
                }
            }

            if(bVideoExist)
            {
                if((audioEndPos >= 0) && (bAudioExist == false))
                {
                    rect.setRect(audioStartPos, 3, audioEndPos, 32);
                    painter->fillRect(rect, QColor(65, 232, 23));
                    rect.setRect(audioStartPos, 35, audioEndPos, 31);
                    painter->fillRect(rect, QColor(235, 173, 71));
                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos = -1;
                }

                if(videoStartPos < 0)
                {
                    videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * 20 * 2) + (i * 2);
                    videoEndPos   = 0;
                }

                videoEndPos += 2;

                if(bAudioExist)
                {
                    if(audioStartPos < 0)
                    {
                        audioStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * 20 * 2) + (i * 2);
                        audioEndPos   = 0;

                        rect.setRect(videoStartPos, 3, videoEndPos - 2, 63);
                        painter->fillRect(rect, QColor(65, 232, 23));
                        videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * 20 * 2) + (i * 2);
                        videoEndPos   = 2;
                    }

                    audioEndPos += 2;
                }

                lastTickPos = (k*20*2) + (i*2); // slider pos. not geometric pos.
            }
            else
            {
                if(videoStartPos >= 0)
                {
                    if(audioStartPos >= 0)
                    {
                        rect.setRect(audioStartPos, 3, audioEndPos, 32);
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, 35, audioEndPos, 31);
                        painter->fillRect(rect, QColor(235, 173, 71));
                    }
                    else
                    {
                        rect.setRect(videoStartPos, 3, videoEndPos, 63);
                        painter->fillRect(rect, QColor(65, 232, 23));
                    }

                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos   = -1;
                }
            }
        }
    }

    if(videoStartPos >= 0)
    {
        if(audioStartPos >= 0)
        {
            rect.setRect(audioStartPos, 3, audioEndPos, 32);
            painter->fillRect(rect, QColor(65, 232, 23));
            rect.setRect(audioStartPos, 35, audioEndPos, 31);
            painter->fillRect(rect, QColor(235, 173, 71));
        }
        else
        {
            rect.setRect(videoStartPos, 3, videoEndPos, 63);
            painter->fillRect(rect, QColor(65, 232, 23));
        }

        videoStartPos = audioStartPos = -1;
        videoEndPos   = audioEndPos = -1;
    }

    if(isRepaintByTimeOver)
    {
        if((tmpLast - (resizeTimeLine_LeftGap + TL_LEFT_MARGIN)) == lastTickPos)
        {
            qDebug(" playback time over but index not updated..%d", lastTickPos);
        }

        isSliderChanged = true;
        lastTickPos     = sliderPlayTime->value();
        isSliderChanged = false;

    }

    isRepaintByTimeOver = false;

    for(int ii = 0; ii <= TL_WIDTH; ii++)
    {
        if((ii % 40) == 0)
        {
            rect.setRect((ii + resizeTimeLine_LeftGap + TL_LEFT_MARGIN), 1, 2, 15);
            painter->fillRect(rect, QColor(0, 0, 0));
        }

        if((ii % 120) == 0)
        {
            rect.setRect((ii + resizeTimeLine_LeftGap + TL_LEFT_MARGIN), 1, 2, 42);
            painter->fillRect(rect, QColor(255, 0, 0));
        }
    }
}
void PlayTimeBar::timeSliderChanged(int val)
{
    QString strTime;
    int tmp  = (int)val / 2;
    int Hour = (int)(tmp / 20);
    int Min  = (tmp - (Hour * 20)) * 3;

    if(isSliderChanged == true || isTimeBarDrag == true)
    {
        if(dlsEndHour >= 0)
        {
            qDebug("%s: =========  val %d, hour %d, end %d", __func__, val, Hour, dlsEndHour);

            if(Hour > dlsEndHour)
            {
                Hour -= 1;

                if(Hour < 10)
                {
                    strTime = tr("0%1:").arg(Hour);
                }
                else
                {
                    strTime = tr("%1:").arg(Hour);
                }
            }
            else
            {
                if(Hour == dlsEndHour)
                {
                    if(dlsEndHour == 0)
                    {
                        Hour    = 23;
                        strTime = tr("%1':").arg(Hour);
                    }
                    else
                    {
                        Hour -= 1;

                        if(Hour < 10)
                        {
                            strTime = tr("0%1':").arg(Hour);
                        }
                        else
                        {
                            strTime = tr("%1':").arg(Hour);
                        }
                    }
                }
                else
                {
                    if(Hour < 10)
                    {
                        strTime = tr("0%1:").arg(Hour);
                    }
                    else
                    {
                        strTime = tr("%1:").arg(Hour);
                    }
                }
            }

            if(Min < 10)
            {
                strTime += tr("0%1:00").arg(Min);
            }
            else
            {
                strTime += tr("%1:00").arg(Min);
            }

            if(gFlagTimeReceived == 0)
            {
                labelTime->setText(strTime);
            }

            xPos = val + (resizeTimeLine_LeftGap + TL_LEFT_MARGIN);
            yPos = 20;
        }
        else
        {
            if(Hour < 10)
            {
                strTime = tr("0%1:").arg(Hour);
            }
            else
            {
                strTime = tr("%1:").arg(Hour);
            }

            if(Min  < 10)
            {
                strTime += tr("0%1:00").arg(Min);
            }
            else
            {
                strTime += tr("%1:00").arg(Min);
            }

            if(gFlagTimeReceived == 0)
            {
                labelTime->setText(strTime);
            }

            xPos = val + (resizeTimeLine_LeftGap + TL_LEFT_MARGIN);
            yPos = 20;
        }

        update();
    }
}
void PlayTimeBar::timeSliderMoved(int val)
{
    isTimeBarDrag = true;
    //qDebug("......... slider move");
}
void PlayTimeBar::timeSliderReleased()
{
    int pos;

    isTimeBarDrag    = false;
    isSliderChanged  = true;
    pos              = sliderPlayTime->value();
    isSliderChanged  = false;
    xPos             = pos + TL_LEFT_MARGIN;
    yPos             = 20;

    //qDebug("......... slider release pos = %d ", pos);
    emit playTimeChanged(pos);
}
time_t PlayTimeBar::getRecordExistTime(int pos, int dir)
{
    struct tm  tmChange;

    time_t     now         = 0;

    int        Hour        = 0,
               Min         = 0,
               hourMax     = 24,
               secpos      = 0,
               i           = 0,
               j           = 0;

    bool       bVideoExist = false;

    pos /= 2;

    Hour = (int)(pos / 20);
    Min  = (pos - (Hour * 20)) * 3;

    //lastPbTime
    localtime_r(&lastPbTime, &tmChange);

    if(dlsEndHour >= 0)
    {
        hourMax = 25;
    }

    secpos = (Min * 4);

    if(!(timeLog[Hour].channel[secpos] & (0xffff)))
    {
        if(dir >= 0)
        {
            for(i = Hour; i < hourMax; i++)
            {
                for(j = 0; j < 240; j++)
                {
                    if(i == Hour)
                    {
                        if(j > secpos)
                        {
                            if(timeLog[i].channel[j] & (0xffff))
                            {
                                bVideoExist = true;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(timeLog[i].channel[j] & (0xffff))
                        {
                            bVideoExist = true;
                            break;
                        }
                    }
                }

                if(bVideoExist)
                {
                    break;
                }
            }
        }
        else
        {
            for(i = Hour; i >= 0; i--)
            {
                for(j = 239; j >= 0; j--)
                {
                    if(i == Hour)
                    {
                        if(j < secpos)
                        {
                            if(timeLog[i].channel[j] & (0xffff))
                            {
                                bVideoExist = true;
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(timeLog[i].channel[j] & (0xffff))
                        {
                            bVideoExist = true;
                            break;
                        }
                    }
                }

                if(bVideoExist)
                {
                    break;
                }
            }
        }
    }
    else
    {
        i           = Hour;
        j           = secpos;
        bVideoExist = true;
    }

    if(!bVideoExist)
    {
        return 0;
    }

    qDebug("=========== hour %d -> %d, end %d", Hour, i, dlsEndHour);

    Hour = i;
    Min  = j / 4;

    // DLS
    if(dlsEndHour >= 0 && ((Hour >= (dlsEndHour-1)) || (Hour == dlsEndHour)))
    {
        tmChange.tm_hour = Hour - 1;
        tmChange.tm_min  = Min;
        tmChange.tm_sec  = 0;
        now              = mktime(&tmChange);
    }
    else
    {
        tmChange.tm_hour = Hour;
        tmChange.tm_min  = Min;
        tmChange.tm_sec  = 0;
        now              = mktime(&tmChange);

        // dls check...
        if(dlsPlayback.isChecked && dlsPlayback.isDlsEnabled)
        {
            if(dlsPlayback.tDlsEnd > dlsPlayback.tDlsBegin)
            {
                if((now >= dlsPlayback.tDlsBegin) && (now < dlsPlayback.tDlsEnd))
                {
                    now -= 3600;
                }
            }
            else
            {
                if(!((now >= dlsPlayback.tDlsEnd) && (now < dlsPlayback.tDlsBegin)))
                {
                    now -= 3600;
                }
            }
        }
    }

    return now;
}
int PlayTimeBar::updatePlaybackTime(time_t pbTime, int endOverlap)
{
    struct tm  tmPlay;

    QString    strDate,
               sTime,
               sAmPm;

    char       szDate[32],
               szTime[32];

    int        val         = 0;

    bool       isAmPmFirst = false;


    if(isTimeBarDrag)
    {
        return 0;
    }

    lastPbTime = pbTime;
    localtime_r(&pbTime, &tmPlay);

    memset(szDate, 0, 32);

    if(endOverlap == 2)
    {
        switch(timeDisplayFormat)
        {
            case 0:
            default : { sprintf(szDate, "%d/%02d/%02d", tmPlay.tm_year+1900, tmPlay.tm_mon+1,  tmPlay.tm_mday-1);    break; } //YYYY/MM/DD
            case 1:   { sprintf(szDate, "%02d/%02d/%d", tmPlay.tm_mon+1,     tmPlay.tm_mday-1, tmPlay.tm_year+1900); break; } //MM/DD/YYYY
            case 2:   { sprintf(szDate, "%02d/%02d/%d", tmPlay.tm_mday-1,    tmPlay.tm_mon+1,  tmPlay.tm_year+1900); break; } //DD/MM/YYYY
            case 3:   { sprintf(szDate, "%d-%02d-%02d", tmPlay.tm_year+1900, tmPlay.tm_mon+1,  tmPlay.tm_mday-1);    break; } //YYYY-MM-DD
            case 4:   { sprintf(szDate, "%02d-%02d-%d", tmPlay.tm_mon+1,     tmPlay.tm_mday-1, tmPlay.tm_year+1900); break; } //MM-DD-YYYY
            case 5:   { sprintf(szDate, "%02d-%02d-%d", tmPlay.tm_mday-1,    tmPlay.tm_mon+1,  tmPlay.tm_year+1900); break; } //DD-MM-YYYY
        }

        strDate = QString::fromAscii(szDate);
        memset(szTime, 0, 32);

        if(is24HourMode)
        {
            sprintf(szTime, "%02d':%02d:%02d", 23, tmPlay.tm_min, tmPlay.tm_sec);
            sTime = QString::fromAscii(szTime);
        }
        else
        {
            sAmPm = tr("PM");
            sprintf(szTime, "%02d':%02d:%02d", 11, tmPlay.tm_min, tmPlay.tm_sec);

            if(isAmPmFirst)
            {
                sTime = sAmPm + " " + QString::fromAscii(szTime);
            }
            else
            {
                sTime = QString::fromAscii(szTime) + " " + sAmPm;
            }
        }
    }
    else
    {
        switch(timeDisplayFormat)
        {
            case 0:
            default : { sprintf(szDate, "%d/%02d/%02d", tmPlay.tm_year+1900, tmPlay.tm_mon+1, tmPlay.tm_mday);      break; } //YYYY/MM/DD
            case 1:   { sprintf(szDate, "%02d/%02d/%d", tmPlay.tm_mon+1,     tmPlay.tm_mday,  tmPlay.tm_year+1900); break; } //MM/DD/YYYY
            case 2:   { sprintf(szDate, "%02d/%02d/%d", tmPlay.tm_mday,      tmPlay.tm_mon+1, tmPlay.tm_year+1900); break; } //DD/MM/YYYY
            case 3:   { sprintf(szDate, "%d-%02d-%02d", tmPlay.tm_year+1900, tmPlay.tm_mon+1, tmPlay.tm_mday);      break; } //YYYY-MM-DD
            case 4:   { sprintf(szDate, "%02d-%02d-%d", tmPlay.tm_mon+1,     tmPlay.tm_mday,  tmPlay.tm_year+1900); break; } //MM-DD-YYYY
            case 5:   { sprintf(szDate, "%02d-%02d-%d", tmPlay.tm_mday,      tmPlay.tm_mon+1, tmPlay.tm_year+1900); break; } //DD-MM-YYYY
        }

        strDate = QString::fromAscii(szDate);

        memset(szTime, 0, 32);

        if(is24HourMode)
        {
            if(endOverlap)
            {
                sprintf(szTime, "%02d':%02d:%02d", tmPlay.tm_hour, tmPlay.tm_min, tmPlay.tm_sec);
            }
            else
            {
                sprintf(szTime, "%02d:%02d:%02d", tmPlay.tm_hour, tmPlay.tm_min, tmPlay.tm_sec);
            }

            sTime = QString::fromAscii(szTime);
        }
        else
        {
            if(tmPlay.tm_hour < 12)
            {
                sAmPm = tr("AM");
            }
            else
            {
                sAmPm = tr("PM");
            }

            if((tmPlay.tm_hour == 0)||(tmPlay.tm_hour == 12))
            {
                if(endOverlap)
                {
                    sprintf(szTime, "12':%02d:%02d", tmPlay.tm_min, tmPlay.tm_sec);
                }
                else
                {
                    sprintf(szTime, "12:%02d:%02d", tmPlay.tm_min, tmPlay.tm_sec);
                }
            }
            else
            {
                if(endOverlap)
                {
                    sprintf(szTime, "%d':%02d:%02d", tmPlay.tm_hour % 12, tmPlay.tm_min, tmPlay.tm_sec);
                }
                else
                {
                    sprintf(szTime, "%d:%02d:%02d", tmPlay.tm_hour % 12, tmPlay.tm_min, tmPlay.tm_sec);
                }
            }

            if(isAmPmFirst)
            {
                sTime = sAmPm + " " + QString::fromAscii(szTime);
            }
            else
            {
                sTime = QString::fromAscii(szTime) + " " + sAmPm;
            }
        }
    }

    gFlagTimeReceived = 1;
    labelDate->setText(strDate);
    labelTime->setText(sTime);

    if(dlsEndHour >= 0)
    {
        //qDebug("............ pbtime change hour %d, overlap %d, end %d", tmPlay.tm_hour, dlsEndHour, endOverlap);

        if(tmPlay.tm_hour == dlsEndHour - 1)
        {
            if(endOverlap)
            {
                val = ((tmPlay.tm_hour + 1) * 20) + (tmPlay.tm_min / 3);
            }
            else
            {
                val = (tmPlay.tm_hour * 20) + (tmPlay.tm_min / 3);
            }
        }
        else if(tmPlay.tm_hour == dlsEndHour)
        {
            if(endOverlap)
            {
                val = (tmPlay.tm_hour * 20) + (tmPlay.tm_min / 3);
            }
            else
            {
                val = ((tmPlay.tm_hour + 1) * 20) + (tmPlay.tm_min / 3);
            }
        }
        else if(tmPlay.tm_hour > dlsEndHour)
        {
            val = ((tmPlay.tm_hour + 1) * 20) + (tmPlay.tm_min / 3);
        }
        else
        {
            val = (tmPlay.tm_hour * 20) + (tmPlay.tm_min / 3);
        }
    }
    else
    {
        val = (tmPlay.tm_hour * 20 * 2) + (tmPlay.tm_min / 3 * 2);
    }

    isSliderChanged = true;
    sliderPlayTime->setValue(val);
    isSliderChanged = false;

    //qDebug("%s: val = %d \n", __func__, val);
    gFlagTimeReceived = 0;

    if(sliderPlayTime->isHidden() == 0)
    {
        if(val > lastTickPos)
        {
            isRepaintByTimeOver = true;

            //qDebug("record index update ....");
            return 1;
        }
    }

    return 0;
}
time_t PlayTimeBar::getLatestPlaybackTime()
{
    return lastPbTime;
}
void PlayTimeBar::setTimeFormat(int tFormat)
{
    timeDisplayFormat = tFormat;

    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)
    {
        this->is24HourMode = false;
    }
    else
    {
        this->is24HourMode = true;
    }
}
void PlayTimeBar::sliderPlayTimeChange()
{
    //qDebug("%s(), %s:%d \n", __func__, __FILE__, __LINE__);

    if(EventSearchPB)
    {
        sliderPlayTime->setStyleSheet("QSlider { height: 12px; margin: 5px 5px}");
        sliderPlayTime->hide();
    }
    else
    {
        sliderPlayTime->setStyleSheet("QSlider { height: 50px; margin: 1px 5px}"
                "::groove { border: 50px; height: 50px; background-color: rgb(0,0,255,127);}"
                "::handle { image: url(:/images/slider_handle.png); width: 100px; margin: -30px -30px}");
        sliderPlayTime->show();
    }
}
void PlayTimeBar::mousePressEvent(QMouseEvent *event)
{
    time_t now      = 0;
    int sliderValue = 0;

    if(EventSearchPB)
    {
        return;
    }
    else if(event->x()-TL_LEFT_MARGIN < 0 || event->x()-TL_LEFT_MARGIN > TL_WIDTH )
    {
        //When click outside of TimeLine, return event.
        return;
    }

    if(event->button() == Qt::LeftButton)
    {
        sliderValue = sliderPlayTime->value();

        if((event->x()-TL_LEFT_MARGIN) > sliderValue)      // +15min
        {
            sliderValue += 10;
        }
        else if((event->x()-TL_LEFT_MARGIN) < sliderValue) // -15min
        {
            sliderValue -= 10;
        }
        else
        {
            return;
        }

        if(playbackDirection == PB_FF)
        {
            now = getRecordExistTime(sliderValue,  1);
        }
        else
        {
            now = getRecordExistTime(sliderValue, -1);
        }

        if(now > 0)
        {
            appmgr_search_set_time(now);
            sliderPlayTime->setValue(sliderValue);
            timeSliderReleased();
            xPos = sliderValue + TL_LEFT_MARGIN;
            update();
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        sliderValue = event->x() - TL_LEFT_MARGIN;

        if(playbackDirection == PB_FF)
        {
            now = getRecordExistTime(sliderValue,  1);
        }
        else
        {
            now = getRecordExistTime(sliderValue, -1);
        }

        if(now > 0)
        {
            sliderPlayTime->setPageStep(sliderValue);
            appmgr_search_set_time(now);
            sliderPlayTime->setValue(sliderValue);
            timeSliderReleased();
            xPos = sliderValue + TL_LEFT_MARGIN;
            update();
            sliderPlayTime->setPageStep(10);
        }
    }
}
