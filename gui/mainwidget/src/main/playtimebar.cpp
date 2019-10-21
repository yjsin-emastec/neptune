#include <QtGui>
#include "playtimebar.h"
#include "main/mainglobal.h"

static int gFlagTimeReceived = 0;

PlayTimeBar::PlayTimeBar(QWidget *parent)
    : QWidget(parent)
{
    xPos                    = -1;
    isTimeBarDrag           = false;
    isPbTimeChanged         = false;
    isRepaintByTimeOver     = false;
    isSliderChanged         = false;
    timeDisplayFormat       = 0;
    lastTickPos             = 0;
    dlsEndHour              = -1;
    lastPbTime              = 0;
    resizeTimeLine_LeftGap  = 0;
    timeLineStatus          = 1;
    currentPbHour           = 0;

    setPalette(QPalette(QColor(39, 0, 79)));
    setAutoFillBackground(true);

    sliderPlayTime = new QSlider(Qt::Horizontal, this);
    sliderPlayTime->setFocusPolicy(Qt::NoFocus);

    if(mainHeight == 720)
    {
        heightSmall       = 40;     //totalHeight - upMargin
        heightBig         = 120;

        TL_LEFT_MARGIN    = 20;     //leftMargin + handleGap
        TL_UP_MARGIN      = 25;
        TL_WIDTH          = 960;
        TL_HEIGHT         = heightSmall;
        TL_SLIDER_HEIGHT  = 20;
        TL_SLIDER_HANDLE_GAP = 20;

        NUM_15SEC_PER_MIN = 12;     // 2 pixel = 3 min ( 15sec * 12 = 3 min)
        NUM_MIN_PER_HOUR  = 20;     // 1 hour = 20 pixel
        NUM_MINIMUM_PIXEL = 2;
        NUM_TICK_SIZE     = 4;

        textWidth         = 38;
        textHeight        = 25;
        textFontSize      = 24;
        lineSize          = 1;

        //setting tip : TL_SLIDER_HANDLE_GAP = groove margin >= -1 x handle margin = handle width/2
        sliderPlayTime->setStyleSheet("QSlider { background-color:rgb(0,0,0,0);}"
                "::groove { margin:0 20px; height: 20px; background-color: rgb(255,255,255,0);}"
                "::handle { image: url(:/images/slider_handle.png); width: 40px;  margin: 0 -20px;}");
    }
    else
    {
        heightSmall       = 60;
        heightBig         = 176;

        TL_LEFT_MARGIN    = 30;
        TL_UP_MARGIN      = 38;
        TL_WIDTH          = 1440;
        TL_HEIGHT         = heightSmall;
        TL_SLIDER_HEIGHT  = 30;
        TL_SLIDER_HANDLE_GAP = 30;

        NUM_15SEC_PER_MIN = 4;      // 1 pixel = 1 min. ( 15sec * 4 = 1 min)
        NUM_MIN_PER_HOUR  = 60;     // 1 hour = 60 pixel
        NUM_MINIMUM_PIXEL = 1;
        NUM_TICK_SIZE     = 6;

        textWidth         = 87;
        textHeight        = 57;
        textFontSize      = 38;
        lineSize          = 2;

        sliderPlayTime->setStyleSheet("QSlider { background-color:rgb(0,0,0,0);}"
                "::groove { margin: 30px; height: 30px; background-color: rgb(255,255,255,0);}"
                "::handle { image: url(:/images/slider_handle.png); width: 60px; margin: -30px}");
    }

    CH_COUNT=devInfo.videoNum;

    sliderPlayTime->move(TL_LEFT_MARGIN-TL_SLIDER_HANDLE_GAP, TL_UP_MARGIN-TL_SLIDER_HEIGHT);
    sliderPlayTime->setRange(0, TL_WIDTH-1);
    sliderPlayTime->resize(TL_WIDTH+TL_SLIDER_HANDLE_GAP*2 , TL_SLIDER_HEIGHT);
    sliderPlayTime->setPageStep(0);
    sliderPlayTime->show();

    connect(sliderPlayTime, SIGNAL(valueChanged(int)), this, SLOT(timeSliderChanged(int)));
    connect(sliderPlayTime, SIGNAL(sliderReleased()),  this, SLOT(timeSliderReleased()));
    connect(sliderPlayTime, SIGNAL(sliderMoved(int)),  this, SLOT(timeSliderMoved(int)));

    sliderPlayTime->setLayoutDirection(Qt::LeftToRight);
}
void PlayTimeBar::initPlayTimeBar()
{
    timeLineStatus=1;

    dlsEndHour = -1;
    lastPbTime = timeLogSelTime;

    if(dlsEndHour >= 0)
    {
        int width = TL_WIDTH + (TL_WIDTH/24);
        sliderPlayTime->setRange(0, width-1);
        sliderPlayTime->resize(width+TL_SLIDER_HANDLE_GAP*2 , TL_SLIDER_HEIGHT);
    }
    else
    {
        sliderPlayTime->setRange(0, TL_WIDTH - 1);
        sliderPlayTime->resize(TL_WIDTH+TL_SLIDER_HANDLE_GAP*2 , TL_SLIDER_HEIGHT);
    }

    updateTimeLinePixmap();
}
void PlayTimeBar::paintEvent(QPaintEvent *event)
{
    if(EventSearchPB)
    {
        return;
    }

    QStylePainter painter(this);

    painter.drawPixmap(0, 0, timeLinepixmap);

    if( xPos > 0 )
    {
        painter.setPen(QColor(255, 0, 0));
        painter.setBrush(QColor(255, 0, 0)); // video data
        QRect bar(xPos-NUM_TICK_SIZE/2, TL_UP_MARGIN, NUM_TICK_SIZE, TL_HEIGHT);
        painter.drawRect(bar);
    }
    else
    {
        painter.setPen(QColor(255, 0, 0));
        painter.setBrush(QColor(255, 0, 0)); // video data
        QRect bar(TL_LEFT_MARGIN, TL_UP_MARGIN, NUM_TICK_SIZE, TL_HEIGHT);
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

    QFont textFont;
    textFont.setPixelSize(textFontSize);
    painter.setFont(textFont);

    switch (timeLineStatus)
    {
        case 1 : { drawTimeLine1(&painter); break; }    //unified channel, hour   status
        case 2 : { drawTimeLine2(&painter); break; }    //unified channel, minute status
        case 3 : { drawTimeLine3(&painter); break; }    //each    channel, hour   status
        case 4 : { drawTimeLine4(&painter); break; }    //each    channel, minute status
    }

    update();
}

void PlayTimeBar::drawTimeLine1(QPainter *painter)
{
    TL_HEIGHT = heightSmall;

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
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH+(TL_WIDTH/24), TL_HEIGHT);
        painter->drawRect(bar);
    }
    else
    {
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH, TL_HEIGHT);
        painter->drawRect(bar);
    }

    if(dlsEndHour >= 0)
    {
        hourMax = 25;
    }

    for(int k = 0; k < hourMax; k++)
    {
        //qDebug("%s() .... timeLog[%d].channel[0] = %x", __func__, k, timeLog[k].channel[0]);
        for(int i = 0; i < NUM_MIN_PER_HOUR; i++) // 720p: 1hour = 20 pixel , 1080p: 1hour = 60 pixel
        {
            bVideoExist = bAudioExist = false;

            for(int m = 0; m < NUM_15SEC_PER_MIN; m++) // 720p: 2 pixel = 3 min ( 15sec * 12 = 3 min), 1080p: 1px = 1 min ( 15sec * 4 = 1 min )
            {
                int secPos = i * NUM_15SEC_PER_MIN + m;

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
                    rect.setRect(audioStartPos, TL_UP_MARGIN, audioEndPos, (TL_HEIGHT/2) );
                    painter->fillRect(rect, QColor(65, 232, 23));
                    rect.setRect(audioStartPos, TL_UP_MARGIN+TL_HEIGHT/2, audioEndPos, (TL_HEIGHT/2) );
                    painter->fillRect(rect, QColor(235, 173, 71));
                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos = -1;
                }

                if(videoStartPos < 0)
                {
                    videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + (i * NUM_MINIMUM_PIXEL);
                    videoEndPos   = 0;
                }

                if(bAudioExist)
                {
                    if(audioStartPos < 0)
                    {
                        audioStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + (i * NUM_MINIMUM_PIXEL);
                        audioEndPos   = 0;

                        rect.setRect(videoStartPos, TL_UP_MARGIN, videoEndPos, (TL_HEIGHT/2) );
                        painter->fillRect(rect, QColor(65, 232, 23));
                        videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + (i * NUM_MINIMUM_PIXEL);
                        videoEndPos   = NUM_MINIMUM_PIXEL;
                    }

                    audioEndPos += NUM_MINIMUM_PIXEL;
                }

                videoEndPos += NUM_MINIMUM_PIXEL;

                lastTickPos = (k*NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL) + (i*NUM_MINIMUM_PIXEL); // slider pos. not geometric pos.
            }
            else
            {
                if(videoStartPos >= 0)
                {
                    if(audioStartPos >= 0)
                    {
                        rect.setRect(audioStartPos, TL_UP_MARGIN, audioEndPos, (TL_HEIGHT/2) );
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, TL_UP_MARGIN+TL_HEIGHT/2, audioEndPos, (TL_HEIGHT/2) );
                        painter->fillRect(rect, QColor(235, 173, 71));
                    }
                    else
                    {
                        rect.setRect(videoStartPos, TL_UP_MARGIN, videoEndPos, TL_HEIGHT);
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
            rect.setRect(audioStartPos, TL_UP_MARGIN, audioEndPos, (TL_HEIGHT/2) );
            painter->fillRect(rect, QColor(65, 232, 23));
            rect.setRect(audioStartPos, TL_UP_MARGIN+TL_HEIGHT/2, audioEndPos, (TL_HEIGHT/2) );
            painter->fillRect(rect, QColor(235, 173, 71));
        }
        else
        {
            rect.setRect(videoStartPos, TL_UP_MARGIN, videoEndPos, TL_HEIGHT );
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
        if((ii % (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
            painter->drawLine(ii+(resizeTimeLine_LeftGap+TL_LEFT_MARGIN), TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);
        }

        if((ii % (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL*3) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize*2, Qt::SolidLine));
            painter->drawLine(ii+(resizeTimeLine_LeftGap+TL_LEFT_MARGIN), TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);

            int hour = ii/(NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL);
            painter->setPen(QColor(255,255,255));
            painter->drawText(ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN-textWidth/2, (TL_UP_MARGIN-textHeight)/2, textWidth, textHeight, Qt::AlignCenter, QString("%1").arg(hour));
        }
    }

    for(int i=0; i<1+1; i++)
    {
        painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
        painter->drawLine(resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT*i, resizeTimeLine_LeftGap+TL_LEFT_MARGIN+TL_WIDTH, TL_UP_MARGIN+TL_HEIGHT*i);
    }
}

void PlayTimeBar::drawTimeLine3(QPainter *painter)
{
    TL_HEIGHT = heightBig;

    int      hourMax       = 24,
             videoStartPos = -1,
             videoEndPos   = -1,
             audioStartPos = -1,
             audioEndPos   = -1,
             tmpLast       = 0,
             recordRectHeight = TL_HEIGHT/CH_COUNT-lineSize;

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
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH+(TL_WIDTH/24),  TL_HEIGHT);
        painter->drawRect(bar);
    }
    else
    {
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH,  TL_HEIGHT);
        painter->drawRect(bar);
    }

    if(dlsEndHour >= 0)
    {
        hourMax = 25;
    }

    for(int j=0; j<CH_COUNT; j++)
    {
        for(int k = 0; k < hourMax; k++)
        {
            //qDebug("%s() .... timeLog[%d].channel[0] = %x", __func__, k, timeLog[k].channel[0]);
            for(int i = 0; i < NUM_MIN_PER_HOUR; i++) // 720p: 1hour = 20 pixel , 1080p: 1hour = 60 pixel
            {
                bVideoExist = bAudioExist = false;

                for(int m = 0; m < NUM_15SEC_PER_MIN; m++) // 720p: 2 pixel = 3 min ( 15sec * 12 = 3 min), 1080p: 1px = 1 min ( 15sec * 4 = 1 min )
                {
                    int secPos = i * NUM_15SEC_PER_MIN + m;

                    if(timeLog[k].channel[secPos] & (1<<j))
                    {
                        bVideoExist = true;
                    }
                    if(timeLog[k].channel[secPos] & (1<<(j+16)))
                    {
                        bAudioExist = true;
                    }
                }

                if(bVideoExist)
                {
                    if((audioEndPos >= 0) && (bAudioExist == false))
                    {
                        rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, audioEndPos, recordRectHeight/2 );
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j+recordRectHeight/2, audioEndPos, recordRectHeight/2 );
                        painter->fillRect(rect, QColor(235, 173, 71));
                        videoStartPos = audioStartPos = -1;
                        videoEndPos   = audioEndPos = -1;
                    }

                    if(videoStartPos < 0)
                    {
                        videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + (i * NUM_MINIMUM_PIXEL);
                        videoEndPos   = 0;
                    }

                    if(bAudioExist)
                    {
                        if(audioStartPos < 0)
                        {
                            audioStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + (i * NUM_MINIMUM_PIXEL);
                            audioEndPos   = 0;

                            rect.setRect(videoStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, videoEndPos, recordRectHeight);
                            painter->fillRect(rect, QColor(65, 232, 23));

                            videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + (i * NUM_MINIMUM_PIXEL);
                            videoEndPos   = NUM_MINIMUM_PIXEL;
                        }

                        audioEndPos += NUM_MINIMUM_PIXEL;
                    }

                    videoEndPos += NUM_MINIMUM_PIXEL;

                    lastTickPos = (k*NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL) + (i*NUM_MINIMUM_PIXEL); // slider pos. not geometric pos.
                }
                else
                {
                    if(videoStartPos >= 0)
                    {
                        if(audioStartPos >= 0)
                        {
                            rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, audioEndPos, recordRectHeight/2 );
                            painter->fillRect(rect, QColor(65, 232, 23));
                            rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j+recordRectHeight/2, audioEndPos, recordRectHeight/2 );
                            painter->fillRect(rect, QColor(235, 173, 71));
                        }
                        else
                        {
                            rect.setRect(videoStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, videoEndPos, recordRectHeight );
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
                rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, audioEndPos, recordRectHeight/2 );
                painter->fillRect(rect, QColor(65, 232, 23));
                rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j+recordRectHeight/2, audioEndPos, recordRectHeight/2 );
                painter->fillRect(rect, QColor(235, 173, 71));
            }
            else
            {
                rect.setRect(videoStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, videoEndPos, recordRectHeight );
                painter->fillRect(rect, QColor(65, 232, 23));
            }

            videoStartPos = audioStartPos = -1;
            videoEndPos   = audioEndPos = -1;
        }
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
        if((ii % (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
            painter->drawLine(ii+(resizeTimeLine_LeftGap+TL_LEFT_MARGIN), TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);
        }

        if((ii % (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL*3) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize*2, Qt::SolidLine));
            painter->drawLine(ii+(resizeTimeLine_LeftGap+TL_LEFT_MARGIN), TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);

            int hour = ii/(NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL);
            painter->setPen(QColor(255,255,255));
            painter->drawText( ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN-textWidth/2, (TL_UP_MARGIN-textHeight)/2, textWidth, textHeight, Qt::AlignCenter, QString("%1").arg(hour));
        }
    }

    for(int i=0; i<CH_COUNT+1; i++)
    {
        painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
        painter->drawLine( resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+(recordRectHeight+lineSize)*i, resizeTimeLine_LeftGap+TL_LEFT_MARGIN+TL_WIDTH, TL_UP_MARGIN+(recordRectHeight+lineSize)*i);
    }
}

void PlayTimeBar::drawTimeLine2(QPainter *painter)
{
    TL_HEIGHT=heightSmall;

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
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH+(TL_WIDTH/24),  TL_HEIGHT);
        painter->drawRect(bar);
    }
    else
    {
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH,  TL_HEIGHT);
        painter->drawRect(bar);
    }

    if(dlsEndHour >= 0)
    {
        hourMax = 25;
    }

    int NUM_15SEC_PER_PIXEL = TL_WIDTH/60/4;
    int currentTime = currentPbHour;

    for(int k=0; k<60*60/15; k++)
    {
        bVideoExist = bAudioExist = false;

        if(timeLog[currentTime].channel[k] & 0xffff)
        {
            bVideoExist = true;
        }
        if(timeLog[currentTime].channel[k] & 0xffff0000)
        {
            bAudioExist = true;
        }

        if( bVideoExist )
        {
            if( (audioEndPos >= 0) && (bAudioExist == false) )
            {
                rect.setRect(audioStartPos, TL_UP_MARGIN, audioEndPos, TL_HEIGHT/2 );
                painter->fillRect(rect, QColor(65, 232, 23));
                rect.setRect(audioStartPos, TL_UP_MARGIN+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2 );
                painter->fillRect(rect, QColor(235, 173, 71));

                videoStartPos = audioStartPos = -1;
                videoEndPos   = audioEndPos = -1;
            }

            if(videoStartPos < 0)
            {
                videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_15SEC_PER_PIXEL);
                videoEndPos   = 0;
            }

            if(bAudioExist)
            {
                if(audioStartPos < 0)
                {
                    audioStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_15SEC_PER_PIXEL);
                    audioEndPos   = 0;

                    rect.setRect(videoStartPos, TL_UP_MARGIN, videoEndPos , TL_HEIGHT );
                    painter->fillRect(rect, QColor(65, 232, 23));

                    videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_15SEC_PER_PIXEL);
                    videoEndPos   = NUM_15SEC_PER_PIXEL;
                }

                audioEndPos += NUM_15SEC_PER_PIXEL;
            }

            videoEndPos += NUM_15SEC_PER_PIXEL;

            lastTickPos = k * NUM_15SEC_PER_PIXEL; // slider pos. not geometric pos.
        }
        else
        {
            if(videoStartPos >= 0)
            {
                if(audioStartPos >= 0)
                {
                    rect.setRect(audioStartPos, TL_UP_MARGIN, audioEndPos, TL_HEIGHT/2 );
                    painter->fillRect(rect, QColor(65, 232, 23));
                    rect.setRect(audioStartPos, TL_UP_MARGIN+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2 );
                    painter->fillRect(rect, QColor(235, 173, 71));
                }
                else
                {
                    rect.setRect(videoStartPos, TL_UP_MARGIN, videoEndPos, TL_HEIGHT);
                    painter->fillRect(rect, QColor(65, 232, 23));
                }

                videoStartPos = audioStartPos = -1;
                videoEndPos   = audioEndPos   = -1;
            }
        }
    }

    if(videoStartPos >= 0)
    {
        if(audioStartPos >= 0)
        {
            rect.setRect(audioStartPos, TL_UP_MARGIN, audioEndPos, TL_HEIGHT/2 );
            painter->fillRect(rect, QColor(65, 232, 23));
            rect.setRect(audioStartPos, TL_UP_MARGIN+TL_HEIGHT/2 , audioEndPos, TL_HEIGHT/2 );
            painter->fillRect(rect, QColor(235, 173, 71));
        }
        else
        {
            rect.setRect(videoStartPos, TL_UP_MARGIN, videoEndPos, TL_HEIGHT );
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
        if((ii % (NUM_15SEC_PER_PIXEL*4) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
            painter->drawLine(ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);
        }

        if((ii % (NUM_15SEC_PER_PIXEL*4*5) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize*2, Qt::SolidLine));
            painter->drawLine(ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);

            int min=ii/(NUM_15SEC_PER_PIXEL*4*5)*5;

            painter->setPen(QColor(255,255,255));
            painter->drawText((ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN)-textWidth/2, (TL_UP_MARGIN-textHeight)/2, textWidth, textHeight, Qt::AlignCenter, QString("%1").arg(min));
        }
    }

    for(int i=0; i<1+1; i++)
    {
        painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
        painter->drawLine( resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT*i, resizeTimeLine_LeftGap+TL_LEFT_MARGIN+TL_WIDTH, TL_UP_MARGIN+TL_HEIGHT*i);
    }
}
void PlayTimeBar::drawTimeLine4(QPainter *painter)
{
    TL_HEIGHT=heightBig;

    int      hourMax       = 24,
             videoStartPos = -1,
             videoEndPos   = -1,
             audioStartPos = -1,
             audioEndPos   = -1,
             tmpLast       = 0,
             recordRectHeight = TL_HEIGHT/CH_COUNT-lineSize;

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
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH+(TL_WIDTH/24), TL_HEIGHT);
        painter->drawRect(bar);
    }
    else
    {
        QRect bar((resizeTimeLine_LeftGap + TL_LEFT_MARGIN), TL_UP_MARGIN, TL_WIDTH, TL_HEIGHT);
        painter->drawRect(bar);
    }

    if(dlsEndHour >= 0)
    {
        hourMax = 25;
    }

    int NUM_15SEC_PER_PIXEL = TL_WIDTH/60/4;
    int currentTime = currentPbHour;

    for(int j=0; j<CH_COUNT; j++)
    {
        for(int k=0; k<60*60/15; k++)
        {
            bVideoExist = bAudioExist = false;

            if(timeLog[currentTime].channel[k] & (1<<j))
            {
                bVideoExist = true;
            }
            if(timeLog[currentTime].channel[k] & (1<<(j+16)))
            {
                bAudioExist = true;
            }

            if( bVideoExist )
            {
                if( (audioEndPos >= 0) && (bAudioExist == false) )
                {
                    rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, audioEndPos, recordRectHeight/2 );
                    painter->fillRect(rect, QColor(65, 232, 23));
                    rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j+recordRectHeight/2, audioEndPos, recordRectHeight/2 );
                    painter->fillRect(rect, QColor(235, 173, 71));

                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos = -1;
                }

                if(videoStartPos < 0)
                {
                    videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_15SEC_PER_PIXEL);
                    videoEndPos   = 0;
                }

                if(bAudioExist)
                {
                    if(audioStartPos < 0)
                    {
                        audioStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_15SEC_PER_PIXEL);
                        audioEndPos   = 0;

                        rect.setRect(videoStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, videoEndPos , recordRectHeight );
                        painter->fillRect(rect, QColor(65, 232, 23));

                        videoStartPos = (resizeTimeLine_LeftGap + TL_LEFT_MARGIN) + (k * NUM_15SEC_PER_PIXEL);
                        videoEndPos   = NUM_15SEC_PER_PIXEL;
                    }

                    audioEndPos += NUM_15SEC_PER_PIXEL;
                }

                videoEndPos += NUM_15SEC_PER_PIXEL;

                lastTickPos = k * NUM_15SEC_PER_PIXEL; // slider pos. not geometric pos.
            }
            else
            {
                if(videoStartPos >= 0)
                {
                    if(audioStartPos >= 0)
                    {
                        rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, audioEndPos, recordRectHeight/2 );
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j+recordRectHeight/2, audioEndPos, recordRectHeight/2 );
                        painter->fillRect(rect, QColor(235, 173, 71));
                    }
                    else
                    {
                        rect.setRect(videoStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, videoEndPos, recordRectHeight );
                        painter->fillRect(rect, QColor(65, 232, 23));
                    }

                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos   = -1;
                }
            }
        }

        if(videoStartPos >= 0)
        {
            if(audioStartPos >= 0)
            {
                rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, audioEndPos, recordRectHeight/2 );
                painter->fillRect(rect, QColor(65, 232, 23));
                rect.setRect(audioStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j+recordRectHeight/2 , audioEndPos, recordRectHeight/2 );
                painter->fillRect(rect, QColor(235, 173, 71));
            }
            else
            {
                rect.setRect(videoStartPos, TL_UP_MARGIN+lineSize+(recordRectHeight+lineSize)*j, videoEndPos, recordRectHeight );
                painter->fillRect(rect, QColor(65, 232, 23));
            }

            videoStartPos = audioStartPos = -1;
            videoEndPos   = audioEndPos = -1;
        }
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
        if((ii % (NUM_15SEC_PER_PIXEL*4) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
            painter->drawLine(ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);
        }

        if((ii % (NUM_15SEC_PER_PIXEL*4*5) ) == 0)
        {
            painter->setPen(QPen(QColor(39, 0, 79), lineSize*2, Qt::SolidLine));
            painter->drawLine(ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN, ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+TL_HEIGHT);

            int min=ii/(NUM_15SEC_PER_PIXEL*4*5)*5;

            painter->setPen(QColor(255,255,255));
            painter->drawText((ii+resizeTimeLine_LeftGap+TL_LEFT_MARGIN)-textWidth/2, (TL_UP_MARGIN-textHeight)/2, textWidth, textHeight, Qt::AlignCenter, QString("%1").arg(min));
        }
    }

    for(int i=0; i<CH_COUNT+1; i++)
    {
        painter->setPen(QPen(QColor(39, 0, 79), lineSize, Qt::SolidLine));
        painter->drawLine( resizeTimeLine_LeftGap+TL_LEFT_MARGIN, TL_UP_MARGIN+(recordRectHeight+lineSize)*i, resizeTimeLine_LeftGap+TL_LEFT_MARGIN+TL_WIDTH, TL_UP_MARGIN+(recordRectHeight+lineSize)*i);
    }
}
void PlayTimeBar::timeSliderChanged(int val)
{
    QString strTime;
    QString strAmPm;
    int Hour;
    int Min;
    int Sec;

    if(isSliderChanged == true || isTimeBarDrag == true)
    {
        if( timeLineStatus == 1 || timeLineStatus == 3 )
        {
            Hour = (int)(val / (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL));
            Min  = (val - (Hour * (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL))) * (15 * NUM_15SEC_PER_MIN / 60) / NUM_MINIMUM_PIXEL;
            Sec  = 0;
        }
        else
        {
            int minPx=TL_WIDTH/60/4;
            Hour = currentPbHour;
            Min  = (int)(val/minPx/4);
            Sec = ((val/minPx)-(Min*4)) * 15;
        }

        if( !is24HourMode && Hour>=12 )
        {
            Hour -=12;
            strAmPm=tr("PM");
        }
        else
        {
            strAmPm=tr("AM");
        }
        if( Hour == 0 )
        {
            Hour +=12;
        }

        if(dlsEndHour >= 0)
        {
            qDebug("%s: =========  val %d, hour %d, end %d", __func__, val, Hour, dlsEndHour);

            if(Hour > dlsEndHour)
            {
                Hour -= 1;

                if(Hour < 10)
                {
                    strTime = QString("0%1:").arg(Hour);
                }
                else
                {
                    strTime = QString("%1:").arg(Hour);
                }
            }
            else
            {
                if(Hour == dlsEndHour)
                {
                    if(dlsEndHour == 0)
                    {
                        Hour    = 23;
                        strTime = QString("%1':").arg(Hour);
                    }
                    else
                    {
                        Hour -= 1;

                        if(Hour < 10)
                        {
                            strTime = QString("0%1':").arg(Hour);
                        }
                        else
                        {
                            strTime = QString("%1':").arg(Hour);
                        }
                    }
                }
                else
                {
                    if(Hour < 10)
                    {
                        strTime = QString("0%1:").arg(Hour);
                    }
                    else
                    {
                        strTime = QString("%1:").arg(Hour);
                    }
                }
            }

            if(Min < 10)
            {
                strTime += QString("0%1:").arg(Min);
            }
            else
            {
                strTime += QString("%1:").arg(Min);
            }

            if(Sec < 10)
            {
                strTime += QString("0%1").arg(Sec);
            }
            else
            {
                strTime += QString("%1").arg(Sec);
            }

            if( !is24HourMode )
            {
                strTime += QString(" %1").arg(strAmPm);
            }

            if(gFlagTimeReceived == 0)
            {
                emit updateTimeLabel(strTime);
            }

            xPos = val + (resizeTimeLine_LeftGap + TL_LEFT_MARGIN);
        }
        else
        {
            if(Hour < 10)
            {
                strTime = QString("0%1:").arg(Hour);
            }
            else
            {
                strTime = QString("%1:").arg(Hour);
            }

            if(Min  < 10)
            {
                strTime += QString("0%1:").arg(Min);
            }
            else
            {
                strTime += QString("%1:").arg(Min);
            }

            if(Sec < 10)
            {
                strTime += QString("0%1").arg(Sec);
            }
            else
            {
                strTime += QString("%1").arg(Sec);
            }

            if( !is24HourMode )
            {
                strTime += QString(" %1").arg(strAmPm);
            }

            if(gFlagTimeReceived == 0)
            {
                emit updateTimeLabel(strTime);
            }

            xPos = val + (resizeTimeLine_LeftGap + TL_LEFT_MARGIN);
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

    //lastPbTime
    localtime_r(&lastPbTime, &tmChange);

    if( timeLineStatus == 1 || timeLineStatus == 3 )
    {
        Hour = (int)(pos / (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL));
        Min  = (pos - (Hour * (NUM_MIN_PER_HOUR*NUM_MINIMUM_PIXEL))) * (15 * NUM_15SEC_PER_MIN / 60) / NUM_MINIMUM_PIXEL;
        secpos = (Min * 4);

        if(dlsEndHour >= 0)
        {
            hourMax = 25;
        }

        if(!(timeLog[Hour].channel[secpos] & (0xffff)))     // when record video not exist
        {
            if(dir >= 0)                                    //dir = FF
            {
                for(i = Hour; i < hourMax; i++)             //check all hour
                {
                    for(j = 0; j < 240; j++)                //check all min
                    {
                        if(i == Hour)                       //when same Hour, check future
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
            else                                            //dir = Rewind
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
        else                                               // when record video exist
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
    }
    else
    {
        int minPx = TL_WIDTH/60/4;

        Hour    = tmChange.tm_hour;
        Min     = (int)(pos/minPx/4);
        int Sec = (pos/minPx)-(Min*4);
        secpos  = pos/minPx;

        if(dlsEndHour >= 0)
        {
            hourMax = 25;
        }

        if( !(timeLog[Hour].channel[secpos] & (0xffff)) )
        {
            if(dir >= 0)
            {
                for(i=0; i<240; i++)
                {
                    if(i > secpos)
                    {
                        if(timeLog[Hour].channel[i] & (0xffff))
                        {
                            bVideoExist=true;
                            break;
                        }
                    }
                }
            }
            else
            {
                for(i=239; i>=0; i++)
                {
                    if( i<secpos )
                    {
                        if(timeLog[Hour].channel[i] & (0xffff))
                        {
                            bVideoExist=true;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            i = secpos;
            bVideoExist=true;
        }

        if(!bVideoExist)
        {
            return 0;
        }

        Min = i/4;
        Sec = (i-Min*4)*15;

        // DLS
        if(dlsEndHour >= 0 && ((Hour >= (dlsEndHour-1)) || (Hour == dlsEndHour)))
        {
            tmChange.tm_hour = Hour - 1;
            tmChange.tm_min  = Min;
            tmChange.tm_sec  = Sec;
            now              = mktime(&tmChange);
        }
        else
        {
            tmChange.tm_hour = Hour;
            tmChange.tm_min  = Min;
            tmChange.tm_sec  = Sec;
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
                    sprintf(szTime, "%02d':%02d:%02d", tmPlay.tm_hour % 12, tmPlay.tm_min, tmPlay.tm_sec);
                }
                else
                {
                    sprintf(szTime, "%02d:%02d:%02d", tmPlay.tm_hour % 12, tmPlay.tm_min, tmPlay.tm_sec);
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
    emit updateTimeLabel(sTime);
    emit updateDateLabel(strDate);

    updateSlider();
    currentPbHour=tmPlay.tm_hour;

    //qDebug("%s: val = %d \n", __func__, val);
    gFlagTimeReceived = 0;

    if(sliderPlayTime->isHidden() == 0)
    {
        if(sliderPlayTime->value() != lastTickPos)
        {
            isRepaintByTimeOver = true;
            lastTickPos = val;
            //qDebug("record index update ....");
            updateTimeLinePixmap();
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

    if(EventSearchPB) { sliderPlayTime->hide(); }
    else              { sliderPlayTime->show(); }
}
void PlayTimeBar::updateSlider()
{
    struct tm tmLastPlay;
    localtime_r(&lastPbTime, &tmLastPlay);

    int val;
    if( timeLineStatus == 1 || timeLineStatus == 3 )
    {
        val = (tmLastPlay.tm_hour * NUM_MIN_PER_HOUR * NUM_MINIMUM_PIXEL) + ( tmLastPlay.tm_min / (15*NUM_15SEC_PER_MIN/60) * NUM_MINIMUM_PIXEL );
    }
    else
    {
        int minPx=TL_WIDTH/60/4;
        val = tmLastPlay.tm_min*minPx*4 + tmLastPlay.tm_sec/15*minPx;
    }

    isSliderChanged=false;
    sliderPlayTime->setValue(val);

    xPos=val+TL_LEFT_MARGIN;
    update();
}
void PlayTimeBar::mousePressEvent(QMouseEvent *event)
{
    time_t now      = 0;
    int sliderValue = 0;

    if(EventSearchPB)
    {
        return;
    }
    else if(event->x()-TL_LEFT_MARGIN < 0 || event->x()-TL_LEFT_MARGIN > TL_WIDTH
            || event->y() < TL_UP_MARGIN || event->y() > TL_UP_MARGIN+TL_HEIGHT)
    {
        //When click outside of TimeLine, return event.
        return;
    }

    if(event->button() == Qt::LeftButton)
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
            appmgr_search_set_time(now);
            sliderPlayTime->setValue(sliderValue);
            timeSliderReleased();
            xPos = sliderValue + TL_LEFT_MARGIN;
            update();
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        switch(timeLineStatus)
        {
            case 1 : { timeLineStatus = 2; break; }
            case 2 : { timeLineStatus = 1; break; }
            case 3 : { timeLineStatus = 4; break; }
            case 4 : { timeLineStatus = 3; break; }
        }

        updateSlider();
        updateTimeLinePixmap();
    }
}
int PlayTimeBar::getTimeLineStatus()
{
    return timeLineStatus;
}
void PlayTimeBar::setTimeLineStatus(int status)
{
    timeLineStatus=status;

    updateSlider();
    updateTimeLinePixmap();
}
