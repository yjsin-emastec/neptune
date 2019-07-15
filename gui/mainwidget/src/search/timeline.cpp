#include <QtGui>
#include "timeline.h"
#include "main/mainglobal.h"

TimeLine::TimeLine(QWidget *parent)
    : QWidget(parent)
{
#if( DEVINFO_VIDEONUM == 8 )
    CH_COUNT=8;
#else
    CH_COUNT=devInfo.videoNum;
#endif
    isDrawRecord=true;
    focusStatus=1;
    updateTimeLinePixmap();
}
TimeLine::~TimeLine()
{
}
void TimeLine::updateTimeLine()
{
    updateTimeLinePixmap();
    update();
}
void TimeLine::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, timeLinepixmap);
}
void TimeLine::updateTimeLinePixmap()
{
    timeLinepixmap = QPixmap(size());
    timeLinepixmap.fill(this, 0, 0);
    QPainter painter(&timeLinepixmap);
    painter.initFrom(this);

    if( focusStatus != 3)
    {
        paintHourBorder(&painter);
    }
    else
    {
        paintMinuteBorder(&painter);
    }
    update();
}
void TimeLine::onDrawTimeLine(bool state)
{
    isDrawRecord=state;
    updateTimeLine();
}
void TimeLine::paintHourBorder(QPainter *painter)
{
    if(mainHeight == 720)
    {
        TL_HEIGHT = 16;
        TL_LEFT_MARGIN = 60;
        TL_UP_MARGIN = 25;
        TL_WIDTH = 960;
        CH_WIDTH = 80;
        NUM_15SEC_PER_MIN = 12;
        NUM_MIN_PER_HOUR = 20;
        NUM_PIXEL_PER_MIN = 2;

        fontSize=24;
        textWidth=38;
        textHeight=23;
        lineSize=1;
    }
    else
    {
        TL_HEIGHT=27;
        TL_LEFT_MARGIN = 90;
        TL_UP_MARGIN = 44;
        TL_WIDTH = 1440;
        CH_WIDTH = 120;
        NUM_15SEC_PER_MIN = 4;
        NUM_MIN_PER_HOUR = 60;
        NUM_PIXEL_PER_MIN = 1;

        fontSize=38;
        textWidth=58;
        textHeight=38;
        lineSize=2;
    }

    qDebug(" ............. paintHourBorder + ");

    int        textFlag      =  0,
               videoStartPos = -1,
               videoEndPos   = -1,
               audioStartPos = -1,
               audioEndPos   = -1;
    bool       bVideoExist   = false,
               bAudioExist   = false;
    QRect      rect;
    QString    str;

    textFlag=Qt::AlignCenter;

    //draw timeline background
    painter->setBrush(QColor(39, 0, 79));
    painter->setPen(QPen(QColor(39,0,79), 3, Qt::SolidLine));

    QRect border(0, 0, size().width(), size().height());
    painter->drawRect(border);

    //draw timeline rect
    painter->setPen(QPen(QColor(39,0,79), 2, Qt::SolidLine));
    painter->setBrush(QColor(255,255,255));

    QRect bar(TL_LEFT_MARGIN, TL_UP_MARGIN, TL_WIDTH, TL_HEIGHT*CH_COUNT);
    painter->drawRect(bar);

    //draw hour num text
    QFont font;
    font.setPixelSize(fontSize);
    painter->setFont(font);

    for(int i = 0; i < 25; i++)
    {
        //draw focus rect
        if( focusStatus == 2 && i == selectHour )
        {
            painter->setPen(QPen(QColor(39,0,79)));
            painter->setBrush(QColor(255,0,0));

            QRect focusRect(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-textWidth/2, 0, textWidth, textHeight);
            painter->drawRect(focusRect);
        }

        painter->setPen(QColor(255, 255, 255));
        str = tr("%1").arg(i);
        painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-textWidth/2, (TL_UP_MARGIN-textHeight)-(TL_UP_MARGIN-textHeight)/2, textWidth, textHeight, textFlag, str);
    }

    if(isDrawRecord)
    {
        videoStartPos = audioStartPos = -1;
        videoEndPos   = audioEndPos   = -1;

        int hourMax = 24;
        for(int j = 0; j < CH_COUNT; j++)
        {
            for(int k = 0; k < hourMax; k++)
            {
                for(int i = 0; i < NUM_MIN_PER_HOUR; i++)
                {
                    bVideoExist = bAudioExist = false;

                    for(int m = 0; m < NUM_15SEC_PER_MIN; m++) // 2 pixel = 3 min. ( 15sec * 12 = 3 min)
                    {
                        int secPos = i * NUM_15SEC_PER_MIN + m;

                        if(timeLog[k].channel[secPos] & (1 << j))
                        {
                            bVideoExist = true;
                        }

                        if(timeLog[k].channel[secPos] & (1 << (j+16)))
                        {
                            bAudioExist = true;
                        }
                    }

                    if(bVideoExist)
                    {
                        if((audioEndPos >= 0) && (bAudioExist == false))
                        {
                            rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT), audioEndPos, TL_HEIGHT);
                            painter->fillRect(rect, QColor(65, 232, 23));
                            rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2);
                            painter->fillRect(rect, QColor(235, 173, 71));

                            videoStartPos = audioStartPos = -1;
                            videoEndPos   = audioEndPos   = -1;
                        }

                        if(videoStartPos < 0)
                        {
                            videoStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * NUM_PIXEL_PER_MIN) + (i * NUM_PIXEL_PER_MIN);
                            videoEndPos   = 0;
                        }

                        videoEndPos += NUM_PIXEL_PER_MIN;

                        if(bAudioExist)
                        {
                            if(audioStartPos < 0)
                            {
                                audioStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * NUM_PIXEL_PER_MIN) + (i * NUM_PIXEL_PER_MIN);
                                audioEndPos   = 0;

                                rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT), videoEndPos, TL_HEIGHT);
                                painter->fillRect(rect, QColor(65, 232, 23));
                                videoStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * NUM_PIXEL_PER_MIN) + (i * NUM_PIXEL_PER_MIN);
                                videoEndPos   = NUM_PIXEL_PER_MIN;
                            }

                            audioEndPos += NUM_PIXEL_PER_MIN;
                        }
                    }
                    else
                    {
                        if(videoStartPos >= 0)
                        {
                            if(audioStartPos >= 0)
                            {
                                rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT), audioEndPos, TL_HEIGHT);
                                painter->fillRect(rect, QColor(65, 232, 23));
                                rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2);
                                painter->fillRect(rect, QColor(235, 173, 71));
                            }
                            else
                            {
                                rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT), videoEndPos, TL_HEIGHT);
                                painter->fillRect(rect, QColor(65, 232, 23));
                            }
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
                    rect.setRect(audioStartPos, TL_UP_MARGIN + (j * TL_HEIGHT), audioEndPos, TL_HEIGHT);
                    painter->fillRect(rect, QColor(65, 232, 23));
                    rect.setRect(audioStartPos, TL_UP_MARGIN + (j * TL_HEIGHT)+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2);
                    painter->fillRect(rect, QColor(235, 173, 71));
                }
                else
                {
                    rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT), videoEndPos, TL_HEIGHT);
                    painter->fillRect(rect, QColor(65, 232, 23));
                }

                videoStartPos = audioStartPos = -1;
                videoEndPos   = audioEndPos   = -1;
            }
        }
    }

    //draw horizontal line
    painter->setPen(QPen(QColor(39,0,79), 2, Qt::SolidLine));

    for(int i=0; i<CH_COUNT; i++)
    {
        painter->drawLine(TL_LEFT_MARGIN, TL_UP_MARGIN+(i*TL_HEIGHT), TL_LEFT_MARGIN+TL_WIDTH, TL_UP_MARGIN+(i*TL_HEIGHT));
    }

    //draw vertical line
    for(int i = 0; i < 25; i++)
    {
        if( i%3 == 0)
        {
            painter->setPen(QPen(QColor(39,0,79), lineSize*2, Qt::SolidLine));
        }
        else
        {
            painter->setPen(QPen(QColor(39,0,79), lineSize, Qt::SolidLine));
        }

        painter->drawLine(TL_LEFT_MARGIN+((TL_WIDTH/24)*i), TL_UP_MARGIN, TL_LEFT_MARGIN+((TL_WIDTH/24)*i), TL_UP_MARGIN+(TL_HEIGHT*CH_COUNT));
    }

    if( focusStatus != 1 )
    {
        //draw select time
        QString time;
        if( selectHour < 10 )
        {
            time = QString("%1%2").arg("0").arg(selectHour);
        }
        else
        {
            time = QString::number(selectHour);
        }

        font.setPixelSize(fontSize+5);
        painter->setFont(font);
        painter->setPen(QColor(255, 255, 255));

        painter->drawText(( TL_LEFT_MARGIN-textWidth)/2, TL_UP_MARGIN+((TL_HEIGHT*CH_COUNT)-textHeight)/2, textWidth, textHeight, textFlag, time );
    }

    qDebug(" ............. paintHourBorder - ");
}
void TimeLine::paintMinuteBorder(QPainter *painter)
{
    if(mainHeight == 720)
    {
        NUM_PIXEL_PER_MIN = 4;
    }
    else
    {
        NUM_PIXEL_PER_MIN = 6;
    }

    qDebug(" ............. paintminuteBorder + ");

    int        textFlag      =  0,
               videoStartPos = -1,
               videoEndPos   = -1,
               audioStartPos = -1,
               audioEndPos   = -1;
    bool       bVideoExist   = false,
               bAudioExist   = false;
    QRect      rect;
    QString    str;

    textFlag = Qt::AlignCenter;

    //draw timeline background
    painter->setBrush(QColor(39, 0, 79));
    painter->setPen(QPen(QColor(39,0,79), 3, Qt::SolidLine));

    QRect border(0, 0, size().width(), size().height());
    painter->drawRect(border);

    //draw timeline rect
    painter->setPen(QPen(QColor(39,0,79), 2, Qt::SolidLine));
    painter->setBrush(QColor(255,255,255));

    QRect bar(TL_LEFT_MARGIN, TL_UP_MARGIN , TL_WIDTH,  TL_HEIGHT*CH_COUNT);
    painter->drawRect(bar);

    //draw minute num text
    QFont font;
    font.setPixelSize(fontSize);
    painter->setFont(font);

    for(int i = 0; i <= 60; i=i+5)
    {
        //draw focus rect
        if( i == selectMinute )
        {
            painter->setPen(QPen(QColor(39,0,79)));
            painter->setBrush(QColor(255,0,0));

            QRect focusRect(TL_LEFT_MARGIN+ ((TL_WIDTH/60)*i)- textWidth/2, 0, textWidth, textHeight);
            painter->drawRect(focusRect);
        }

        painter->setPen(QColor(255, 255, 255));
        str = tr("%1").arg(i);
        painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/60)*i)-textWidth/2, (TL_UP_MARGIN-textHeight)-(TL_UP_MARGIN-textHeight)/2 , textWidth, textHeight, textFlag, str);
    }

    for(int i=0; i<CH_COUNT; i++)
    {
        for(int j=0; j<60*60/15; j++)
        {
            bVideoExist = bAudioExist =false;

            if(timeLog[selectHour].channel[j] & (1<<i))
            {
                bVideoExist=true;
            }
            if(timeLog[selectHour].channel[j] & (1<<(i+16)))
            {
                bAudioExist=true;
            }

            if(bVideoExist)
            {
                if(( audioEndPos>=0) && (bAudioExist==false))
                {
                    rect.setRect(audioStartPos, TL_UP_MARGIN+(i*TL_HEIGHT), audioEndPos, TL_HEIGHT);
                    painter->fillRect(rect, QColor(65, 232, 23));
                    rect.setRect(audioStartPos, TL_UP_MARGIN+(i*TL_HEIGHT)+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2);
                    painter->fillRect(rect, QColor(235, 173, 71));

                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos   = -1;
                }

                if( videoStartPos < 0)
                {
                    videoStartPos = TL_LEFT_MARGIN + j*NUM_PIXEL_PER_MIN;
                    videoEndPos = 0;
                }

                videoEndPos += NUM_PIXEL_PER_MIN;

                if( bAudioExist)
                {
                    if( audioStartPos < 0 )
                    {
                        audioStartPos = TL_LEFT_MARGIN + j*NUM_PIXEL_PER_MIN;
                        audioEndPos =0;

                        rect.setRect(videoStartPos, TL_UP_MARGIN+(i*TL_HEIGHT), videoEndPos, TL_HEIGHT);
                        painter->fillRect(rect, QColor(65, 232, 23));

                        videoStartPos = TL_LEFT_MARGIN + j*NUM_PIXEL_PER_MIN;
                        videoEndPos = NUM_PIXEL_PER_MIN;
                    }

                    audioEndPos += NUM_PIXEL_PER_MIN;
                }
            }
            else
            {
                if( videoStartPos>=0 )
                {
                    if(audioStartPos >= 0)
                    {
                        rect.setRect(audioStartPos, TL_UP_MARGIN+(i*TL_HEIGHT), audioEndPos, TL_HEIGHT);
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, TL_UP_MARGIN+(i*TL_HEIGHT)+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2);
                        painter->fillRect(rect, QColor(235, 173, 71));
                    }
                    else
                    {
                        rect.setRect(videoStartPos, TL_UP_MARGIN+(i*TL_HEIGHT), videoEndPos, TL_HEIGHT);
                        painter->fillRect(rect, QColor(65, 232, 23));
                    }
                }

                videoStartPos = audioStartPos = -1;
                videoEndPos   = audioEndPos   = -1;
            }
        }

        if(videoStartPos>=0)
        {
            if(audioStartPos >= 0)
            {
                rect.setRect(audioStartPos, TL_UP_MARGIN+(i*TL_HEIGHT), audioEndPos, TL_HEIGHT);
                painter->fillRect(rect, QColor(65, 232, 23));
                rect.setRect(audioStartPos, TL_UP_MARGIN+(i*TL_HEIGHT)+TL_HEIGHT/2, audioEndPos, TL_HEIGHT/2);
                painter->fillRect(rect, QColor(235, 173, 71));
            }
            else
            {
                rect.setRect(videoStartPos, TL_UP_MARGIN+(i*TL_HEIGHT), videoEndPos, TL_HEIGHT);
                painter->fillRect(rect, QColor(65, 232, 23));
            }
        }
        videoStartPos = audioStartPos = -1;
        videoEndPos   = audioEndPos   = -1;
    }

    //draw horizontal line
    painter->setPen(QPen(QColor(39,0,79), 2, Qt::SolidLine));

    for(int i=0; i<CH_COUNT; i++)
    {
        painter->drawLine(TL_LEFT_MARGIN, TL_UP_MARGIN+(i*TL_HEIGHT), TL_LEFT_MARGIN+TL_WIDTH, TL_UP_MARGIN+(i*TL_HEIGHT));
    }

    //draw vertical line
    for(int i = 0; i <= 60; i++)
    {
        if(i%5 == 0)
        {
            painter->setPen(QPen(QColor(39,0,79), lineSize*2, Qt::SolidLine));
        }
        else
        {
            painter->setPen(QPen(QColor(39,0,79), lineSize, Qt::SolidLine));
        }

        painter->drawLine(TL_LEFT_MARGIN+((TL_WIDTH/60)*i), TL_UP_MARGIN, TL_LEFT_MARGIN+((TL_WIDTH/60)*i), TL_UP_MARGIN+(TL_HEIGHT*CH_COUNT));
    }

    //draw select time
    QString time;
    if( selectHour < 10 )
    {
        time = QString("%1%2").arg("0").arg(selectHour);
    }
    else
    {
        time = QString::number(selectHour);
    }

    font.setPixelSize(fontSize+5);
    painter->setFont(font);
    painter->setPen(QColor(255, 255, 255));

    painter->drawText(( TL_LEFT_MARGIN-textWidth)/2 , TL_UP_MARGIN + ((TL_HEIGHT*CH_COUNT)-textHeight)/2, textWidth, textHeight, textFlag, time );

    qDebug(" ............. paintMinuteBorder - ");
}
void TimeLine::mousePressEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();

    if( (x>TL_LEFT_MARGIN) && (x<TL_LEFT_MARGIN+TL_WIDTH) && (y>0) && (y<TL_UP_MARGIN) )
    {
        if(focusStatus != 3)
        {
            selectHour = (x-TL_LEFT_MARGIN)/(TL_WIDTH/24);
            focusStatus = 3;
        }
        else
        {
            focusStatus = 2;
        }

        updateTimeLinePixmap();
        emit changeFocus(focusStatus);
    }
    else if( (x>TL_LEFT_MARGIN) && (x<TL_LEFT_MARGIN+TL_WIDTH) && (y>TL_UP_MARGIN ) && (y<TL_UP_MARGIN+TL_HEIGHT*CH_COUNT) )
    {
        if(focusStatus == 1)
        {
            selectHour = (x-TL_LEFT_MARGIN)/(TL_WIDTH/24);
            focusStatus=2;
            emit changeFocus(focusStatus);
        }
        if(focusStatus == 2)
        {
            selectHour = (x-TL_LEFT_MARGIN)/(TL_WIDTH/24);
        }
        else
        {
            selectMinute = ((x-TL_LEFT_MARGIN)/(TL_WIDTH/60))/5*5;
        }

        updateTimeLinePixmap();
    }
    else if( (x>0) && (x<TL_LEFT_MARGIN) )
    {
        if(focusStatus == 2)
        {
            focusStatus=3;
            emit changeFocus(focusStatus);
        }
        else if(focusStatus ==3 )
        {
            focusStatus=2;
            emit changeFocus(focusStatus);
        }
    }
}
void TimeLine::mouseDoubleClickEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();

    if( (x>TL_LEFT_MARGIN) && (x<TL_LEFT_MARGIN+TL_WIDTH) && (y>TL_UP_MARGIN ) && (y<TL_UP_MARGIN+TL_HEIGHT*CH_COUNT) )
    {
        emit startPlayback(QTime(selectHour, selectMinute, 0));
    }
}

void TimeLine::setFocusStatus(int status)
{
    focusStatus=status;

    if( focusStatus == 1)       { selectHour = 0; }
    else if( focusStatus == 2 ) { selectMinute =0; }

    updateTimeLinePixmap();
}
void TimeLine::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if(focusStatus == 2)
            {
                if( selectHour < 23) { selectHour++; }
                else                 { selectHour=0; }
            }
            else if(focusStatus == 3)
            {
                if( selectMinute < 55) { selectMinute+=5; }
                else                   { selectMinute=0;  }
            }
            break;
        }
        case Qt::Key_Down:
        {
            if(focusStatus == 2)
            {
                if( selectHour >= 1 ) { selectHour--; }
                else                  { selectHour=23; }
            }
            else if( focusStatus ==3)
            {
                if( selectMinute >= 5) { selectMinute-=5; }
                else                   { selectMinute=55; }
            }
            break;
        }
        case Qt::Key_Left:
        {
            if(focusStatus == 2)
            {
                if( selectHour >= 1 ) { selectHour--; }
                else                  { selectHour=23; }
            }
            else if( focusStatus ==3)
            {
                if( selectMinute >= 5) { selectMinute-=5; }
                else                   { selectMinute=55; }
            }
            break;
        }
        case Qt::Key_Right:
        {
            if(focusStatus == 2)
            {
                if( selectHour < 23) { selectHour++; }
                else                 { selectHour=0; }
            }
            else if(focusStatus == 3)
            {
                if( selectMinute < 55) { selectMinute+=5; }
                else                   { selectMinute=0;  }
            }
            break;
        }
        case Qt::Key_Enter:
        {
            if(focusStatus == 2)
            {
                emit changeFocus(3);
            }
            else if( focusStatus ==3 )
            {
                emit startPlayback(QTime(selectHour, selectMinute, 0));
            }

            break;
        }
        case Qt::Key_Escape:
        {
            if( focusStatus ==2)
            {
                emit changeFocus(1);
            }
            else if( focusStatus ==3 )
            {
                emit changeFocus(2);
            }

            break;
        }
        case Qt::Key_Bar:
        {
            if(focusStatus == 1)
            {
                 emit changeFocus(2);
            }
            else
            {
                emit changeFocus(1);
            }

            break;
        }
        case Qt::Key_Play:
        {
            emit startPlayback(QTime(selectHour, selectMinute, 0));

            break;
        }
        default :
            return;
    }

    updateTimeLinePixmap();
}
