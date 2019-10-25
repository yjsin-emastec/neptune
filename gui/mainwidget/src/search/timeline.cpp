#include <QtGui>
#include "timeline.h"
#include "main/mainglobal.h"

TimeLine::TimeLine(QWidget *parent)
    : QWidget(parent)
{
    CH_COUNT=devInfo.videoNum;

    isDrawRecord    = true;
    focusStatus     = 1;
    isSliderDrag    = false;
    selectHour      = 0;
    selectMinute    = 0;

    sliderSearchTime = new QSlider(Qt::Horizontal, this);

    if(mainHeight == 720)
    {
        TL_HEIGHT               = 16;
        TL_LEFT_MARGIN          = 190;
        TL_UP_MARGIN            = 25;
        TL_WIDTH                = 960;
        CH_WIDTH                = 80;
        TL_SLIDER_HEIGHT        = 20;
        TL_SLIDER_HANDLE_GAP    = 20;

        NUM_15SEC_PER_MIN       = 12;
        NUM_MIN_PER_HOUR        = 20;
        NUM_PIXEL_PER_MIN       = 2;
        NUM_TICK_SIZE           = 4;

        fontSize                = 24;
        textWidth               = 38;
        textHeight              = 23;
        lineSize                = 1;

        sliderSearchTime->setStyleSheet("QSlider { background-color:rgb(0,0,0,0);}"
                "::groove { margin:0 20px; height: 20px; background-color: rgb(255,255,255,0);}"
                "::handle { image: url(:/images/slider_handle.png); width: 40px;  margin: 0 -20px;}");
    }
    else
    {
        TL_HEIGHT               = 27;
        TL_LEFT_MARGIN          = 280;
        TL_UP_MARGIN            = 44;
        TL_WIDTH                = 1440;
        CH_WIDTH                = 120;
        TL_SLIDER_HEIGHT        = 30;
        TL_SLIDER_HANDLE_GAP    = 30;

        NUM_15SEC_PER_MIN       = 4;
        NUM_MIN_PER_HOUR        = 60;
        NUM_PIXEL_PER_MIN       = 1;
        NUM_TICK_SIZE           = 6;

        fontSize                = 38;
        textWidth               = 58;
        textHeight              = 38;
        lineSize                = 2;

        sliderSearchTime->setStyleSheet("QSlider { background-color:rgb(0,0,0,0);}"
                "::groove { margin: 30px; height: 30px; background-color: rgb(255,255,255,0);}"
                "::handle { image: url(:/images/slider_handle.png); width: 60px; margin: -30px}");
    }

    sliderSearchTime->move(TL_LEFT_MARGIN-TL_SLIDER_HANDLE_GAP, TL_UP_MARGIN-TL_SLIDER_HEIGHT);
    sliderSearchTime->setRange(0, TL_WIDTH-1);
    sliderSearchTime->resize(TL_WIDTH+TL_SLIDER_HANDLE_GAP*2 , TL_SLIDER_HEIGHT);
    sliderSearchTime->setPageStep(0);
    sliderSearchTime->setFocusPolicy(Qt::NoFocus);
    sliderSearchTime->setLayoutDirection(Qt::LeftToRight);
    sliderSearchTime->show();

    connect(sliderSearchTime, SIGNAL(sliderPressed()),   this, SLOT(timeSliderPressed()));
    connect(sliderSearchTime, SIGNAL(valueChanged(int)), this, SLOT(timeSliderMoved(int)));
    connect(sliderSearchTime, SIGNAL(sliderReleased()),  this, SLOT(timeSliderReleased()));

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


    //draw select time
    QString hour, min, ap, time;

    if( utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0 )      //12Hour
    {
        int h;
        if( selectHour == 0 )
        {
            h = selectHour+12;
            ap = "AM";
        }
        else if( selectHour > 12 )
        {
            h = selectHour-12;
            ap = "PM";
        }
        else if( selectHour == 12 )
        {
            h= selectHour;
            ap = "PM";
        }
        else
        {
            h = selectHour;
            ap = "AM";
        }

        if( h < 10 )
        {
            hour = QString("%1%2").arg("0", QString::number(h));
        }
        else
        {
            hour = QString("%1").arg(QString::number(h));
        }
    }
    else                                                                //24Hour
    {
        ap=tr("TIME");

        if( selectHour < 10 )
        {
            hour = QString("%1%2").arg("0", QString::number(selectHour));
        }
        else
        {
            hour = QString("%1").arg(QString::number(selectHour));
        }
    }

    if( selectMinute < 10 )
    {
        min = QString("%1%2").arg("0", QString::number(selectMinute));
    }
    else
    {
        min = QString("%1").arg(QString::number(selectMinute));
    }
    time = QString("%1:%2").arg(hour, min);

    QFont font;
    font.setPixelSize(fontSize*1.5);
    painter.setFont(font);
    painter.setPen(QColor(255, 255, 255));
    painter.drawText( (TL_LEFT_MARGIN-textWidth*4)/2, (this->height()/3)-((textHeight*1.5)/2), textWidth*4, textHeight*1.5, Qt::AlignCenter, ap);
    painter.drawText( (TL_LEFT_MARGIN-textWidth*4)/2, (this->height()/3)*2-((textHeight*1.5)/2), textWidth*4, textHeight*1.5, Qt::AlignCenter, time );

    //draw time tick
    painter.setPen(QColor(255, 0, 0));
    painter.setBrush(QColor(255, 0, 0));

    if( focusStatus == 2 )
    {
        QRect bar( TL_LEFT_MARGIN + (selectHour*NUM_MIN_PER_HOUR*NUM_PIXEL_PER_MIN) + (selectMinute/(15*NUM_15SEC_PER_MIN/60)*NUM_PIXEL_PER_MIN) - NUM_TICK_SIZE/2, TL_UP_MARGIN, NUM_TICK_SIZE, TL_UP_MARGIN+TL_HEIGHT*8 );
        painter.drawRect(bar);
    }
    else if( focusStatus == 3 )
    {
        QRect bar( TL_LEFT_MARGIN + selectMinute*(TL_WIDTH/60) - NUM_TICK_SIZE/2, TL_UP_MARGIN, NUM_TICK_SIZE,TL_UP_MARGIN+ TL_HEIGHT*8);
        painter.drawRect(bar);
    }
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
        NUM_PIXEL_PER_MIN = 2;
    }
    else
    {
        NUM_PIXEL_PER_MIN = 1;
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
        painter->setPen(QColor(255, 255, 255));
        str = tr("%1").arg(i);
        painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-textWidth/2, (TL_UP_MARGIN-textHeight)-(TL_UP_MARGIN-textHeight)/2, textWidth, textHeight, textFlag, str);
    }

    sliderSearchTime->setValue( (selectHour*NUM_MIN_PER_HOUR*NUM_PIXEL_PER_MIN) + (selectMinute/(15*NUM_15SEC_PER_MIN/60) * NUM_PIXEL_PER_MIN) );

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
        painter->setPen(QColor(255, 255, 255));
        str = tr("%1").arg(i);
        painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/60)*i)-textWidth/2, (TL_UP_MARGIN-textHeight)-(TL_UP_MARGIN-textHeight)/2 , textWidth, textHeight, textFlag, str);
    }

    sliderSearchTime->setValue( selectMinute*(TL_WIDTH/60));

    if(isDrawRecord)
    {
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

    qDebug(" ............. paintMinuteBorder - ");
}
void TimeLine::mousePressEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();

    if( (x>TL_LEFT_MARGIN) && (x<TL_LEFT_MARGIN+TL_WIDTH) && (y>TL_UP_MARGIN ) && (y<TL_UP_MARGIN+TL_HEIGHT*CH_COUNT) )
    {
        if( e->button() == Qt::LeftButton)          //move select time
        {
            if( focusStatus == 1 )
            {
                focusStatus = 2;
                selectHour = (x-TL_LEFT_MARGIN)/(TL_WIDTH/24);
                selectMinute = ((x-TL_LEFT_MARGIN)-(selectHour*NUM_MIN_PER_HOUR*NUM_PIXEL_PER_MIN)) / NUM_PIXEL_PER_MIN * (15*NUM_15SEC_PER_MIN/60);
                emit changeFocus(focusStatus);
            }
            else if( focusStatus == 2 )
            {
                selectHour = (x-TL_LEFT_MARGIN)/(TL_WIDTH/24);
                selectMinute = ((x-TL_LEFT_MARGIN)-(selectHour*NUM_MIN_PER_HOUR*NUM_PIXEL_PER_MIN)) / NUM_PIXEL_PER_MIN * (15*NUM_15SEC_PER_MIN/60);
            }
            else
            {
                selectMinute = ((x-TL_LEFT_MARGIN)/(TL_WIDTH/60));
            }

            updateTimeLinePixmap();
        }
        else if( e->button() == Qt::RightButton)    //change time format
        {
            if( focusStatus != 3 )
            {
                focusStatus = 3;
            }
            else
            {
                focusStatus = 2;
            }

            updateTimeLinePixmap();
            emit changeFocus(focusStatus);
        }
    }
    else if( (x>0) && (x<TL_LEFT_MARGIN) )
    {
        if( e->button() == Qt::LeftButton )
        {
            if( focusStatus == 1 )
            {
                focusStatus = 2;
                selectHour = 0;
                selectMinute = 0;
                emit changeFocus(focusStatus);
            }
        }
        else if( e->button() == Qt::RightButton )
        {
            if( focusStatus == 1 )
            {
                focusStatus = 2;
                emit changeFocus(focusStatus);
            }
            else if( focusStatus == 2 )
            {
                focusStatus = 3;
                emit changeFocus(focusStatus);
            }
            else if( focusStatus == 3 )
            {
                focusStatus = 2;
                emit changeFocus(focusStatus);
            }
        }
    }
}
void TimeLine::mouseDoubleClickEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();

    if(e->button() == Qt::LeftButton)
    {
        if( (x>TL_LEFT_MARGIN) && (x<TL_LEFT_MARGIN+TL_WIDTH) && (y>TL_UP_MARGIN ) && (y<TL_UP_MARGIN+TL_HEIGHT*CH_COUNT) )
        {
            emit startPlayback(QTime(selectHour, selectMinute, 0));
        }
    }
}
void TimeLine::setFocusStatus(int status)
{
    focusStatus=status;

    if( focusStatus == 1 )
    {
        selectHour = selectMinute = 0;
        sliderSearchTime->hide();
    }
    else
    {
        sliderSearchTime->show();
    }

    updateTimeLinePixmap();
}
void TimeLine::timeSliderMoved(int val)
{
    if( isSliderDrag )
    {
        if( focusStatus == 2 )
        {
            selectHour  = val/(TL_WIDTH/24);
            selectMinute = (val-(selectHour*NUM_MIN_PER_HOUR*NUM_PIXEL_PER_MIN)) / NUM_PIXEL_PER_MIN * (15*NUM_15SEC_PER_MIN/60);
        }
        else
        {
            if( val%(TL_WIDTH/60) !=0 )
            {
                int temp = val - val%(TL_WIDTH/60);

                selectMinute = temp/(TL_WIDTH/60);
                sliderSearchTime->setValue(temp);
            }
            else
            {
                selectMinute = val/(TL_WIDTH/60);
            }
        }
    }

    update();
}
void TimeLine::timeSliderPressed()
{
    isSliderDrag =true;
}
void TimeLine::timeSliderReleased()
{
    isSliderDrag = false;
}

void TimeLine::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if( focusStatus == 2 )
            {
                selectHour += 3;
                if( selectHour>23 )     { selectHour = selectHour%24; }

            }
            else if( focusStatus == 3 )
            {
                selectMinute += 5;
                if( selectMinute>59 )   { selectMinute = selectMinute%60; }
            }
            break;
        }
        case Qt::Key_Down:
        {
            if( focusStatus == 2 )
            {
                selectHour -= 3;
                if( selectHour<0 )      { selectHour = 24+(selectHour%24); }
            }
            else if( focusStatus == 3 )
            {
                selectMinute -= 5;
                if( selectMinute<0 )    { selectMinute = 60+(selectMinute%60); }
            }
            break;
        }
        case Qt::Key_Left:
        {
            if( focusStatus == 2 )
            {
                selectHour -= 1;
                if( selectHour<0 )      { selectHour = 24+(selectHour%24); }
            }
            else if( focusStatus == 3 )
            {
                selectMinute -= 1;
                if( selectMinute<0 )    { selectMinute = 60+(selectMinute%60); }
            }
            break;
        }
        case Qt::Key_Right:
        {
            if( focusStatus == 2 )
            {
                selectHour += 1;
                if( selectHour>23 )     { selectHour = selectHour%24; }
            }
            else if( focusStatus == 3 )
            {
                selectMinute += 1;
                if( selectMinute>59 )   { selectMinute = selectMinute%60; }
            }
            break;
        }
        case Qt::Key_Enter:
        {
            if(focusStatus == 2)
            {
                emit changeFocus(3);
            }
            else if( focusStatus == 3 )
            {
                emit changeFocus(2);
            }

            break;
        }
        case Qt::Key_Escape:
        {
            if( focusStatus == 2)
            {
                emit changeFocus(1);
            }
            else if( focusStatus == 3 )
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
