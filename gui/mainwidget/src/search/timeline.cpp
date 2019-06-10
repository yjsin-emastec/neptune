#include <QtGui>
#include "timeline.h"
#include "main/mainglobal.h"

TimeLine::TimeLine(QWidget *parent)
    : QWidget(parent)
{
    isDrawRecord=true;
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
    paintBorder(&painter);
}
void TimeLine::onDrawTimeLine(bool state)
{
    isDrawRecord=state;
    updateTimeLine();
}
void TimeLine::paintBorder(QPainter *painter)
{
    if(mainHeight == 720)
    {
        TL_HEIGHT = 32;
        TL_LEFT_MARGIN = 80;
        TL_UP_MARGIN = 25;
        TL_WIDTH = 960;
        CH_WIDTH = 80;
        NUM_15SEC_PER_MIN = 12;
        NUM_MIN_PER_HOUR = 20;

        qDebug(" ............. paintBorder + ");

        int        textFlag      =  0,
                   videoStartPos = -1,
                   videoEndPos   = -1,
                   audioStartPos = -1,
                   audioEndPos   = -1;

        bool       bVideoExist   = false,
                   bAudioExist   = false;

        QRect      rect;

        QString    str;

        textFlag = Qt::AlignLeft | Qt::AlignVCenter;

        painter->setBrush(QColor(255, 255, 255));

        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine));

        QRect border(0, 0, size().width(), size().height());

        painter->drawRect(border);

        painter->setPen(QPen(QColor(0, 0, 0), 2, Qt::SolidLine));

        painter->setBrush(QColor(255, 255, 255));

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            QRect bar(TL_LEFT_MARGIN-2, TL_UP_MARGIN + (i * TL_HEIGHT), TL_WIDTH+4,  TL_HEIGHT);
            painter->drawRect(bar);
        }

        QFont font;
        font.setPixelSize(24);
        painter->setFont(font);
        painter->setPen(QColor(0, 0, 0));

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            str = tr("CAM%1").arg(i+1);
            painter->drawText(8, TL_UP_MARGIN + (i * TL_HEIGHT) - 1, CH_WIDTH, TL_HEIGHT, textFlag, str);
        }

        font.setPixelSize(24);
        painter->setFont(font);

        for(int i = 0; i < 25; i++)
        {
            str = tr("%1").arg(i);

            if(i < 10)
            {
                painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-8, TL_UP_MARGIN - 22, 35, 20, textFlag, str);
            }
            else
            {
                painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-16, TL_UP_MARGIN - 22, 35, 20, textFlag, str);
            }
        }

        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));

        for(int i = 0; i < 25; i++)
        {
            painter->drawLine(TL_LEFT_MARGIN+((TL_WIDTH/24)*i), TL_UP_MARGIN, TL_LEFT_MARGIN+((TL_WIDTH/24)*i), TL_UP_MARGIN+(TL_HEIGHT*4));
        }


        if(isDrawRecord)
        {
            bool bOnce = true;

            videoStartPos = audioStartPos = -1;
            videoEndPos   = audioEndPos   = -1;

            int hourMax = 24;

            for(int j = 0; j < devInfo.videoNum; j++)
            {
                for(int k = 0; k < hourMax; k++)
                {
                    for(int i = 0; i < NUM_MIN_PER_HOUR; i++)
                    {
                        bVideoExist = bAudioExist = false;

                        for(int m = 0; m < NUM_15SEC_PER_MIN; m++) // 1 pixel = 3 min. ( 15sec * 12 = 3 min)
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

                            if(bAudioExist && bOnce)
                            {
                                //qDebug("%s()     channel %d, hour %d, secpos %d mask %x", __func__, j, k, secPos, timeLog[k].channel[secPos]);
                                bOnce = false;
                            }
                        }

                        if(bVideoExist)
                        {
                            if((audioEndPos >= 0) && (bAudioExist == false))
                            {
                                rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+ 6, audioEndPos, 20);
                                painter->fillRect(rect, QColor(65, 232, 23));
                                rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+16, audioEndPos, 10);
                                painter->fillRect(rect, QColor(235, 173, 71));

                                videoStartPos = audioStartPos = -1;
                                videoEndPos   = audioEndPos   = -1;
                            }

                            if(videoStartPos < 0)
                            {
                                videoStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * 2) + (i * 2);
                                videoEndPos   = 0;
                            }

                            videoEndPos += 2;

                            if(bAudioExist)
                            {
                                if(audioStartPos < 0)
                                {
                                    audioStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * 2) + (i * 2);
                                    audioEndPos   = 0;

                                    rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 6, videoEndPos - 2, 20);
                                    painter->fillRect(rect, QColor(65, 232, 23));
                                    videoStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * 2) + (i * 2);
                                    videoEndPos   = 2;
                                }

                                audioEndPos += 2;
                            }
                        }
                        else
                        {
                            if(videoStartPos >= 0)
                            {
                                if(audioStartPos >= 0)
                                {
                                    rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+ 6, audioEndPos, 20);
                                    painter->fillRect(rect, QColor(65, 232, 23));
                                    rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+16, audioEndPos, 10);
                                    painter->fillRect(rect, QColor(235, 173, 71));
                                }
                                else
                                {
                                    rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 6, videoEndPos, 20);
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
                        rect.setRect(audioStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) +  6, audioEndPos, 20);
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 16, audioEndPos, 10);
                        painter->fillRect(rect, QColor(235, 173, 71));
                    }
                    else
                    {
                        rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 6, videoEndPos, 20);
                        painter->fillRect(rect, QColor(65, 232, 23));
                    }

                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos   = -1;
                }
            }
        }

        qDebug(" ............. paintBorder - ");
    }
    else
    {
        TL_HEIGHT = 50;
        TL_LEFT_MARGIN = 130;
        TL_UP_MARGIN = 50;
        TL_WIDTH = 1440;
        CH_WIDTH = 120;
        NUM_15SEC_PER_MIN = 4;
        NUM_MIN_PER_HOUR = 60;

        qDebug(" ............. paintBorder + ");

        int        textFlag      =  0,
                   videoStartPos = -1,
                   videoEndPos   = -1,
                   audioStartPos = -1,
                   audioEndPos   = -1;

        bool       bVideoExist   = false,
                   bAudioExist   = false;

        QRect      rect;

        QString    str;

        textFlag = Qt::AlignLeft | Qt::AlignVCenter;

        painter->setBrush(QColor(255, 255, 255));

        painter->setPen(QPen(Qt::red, 3, Qt::SolidLine));

        QRect border(0, 0, size().width(), size().height());

        painter->drawRect(border);

        painter->setPen(QPen(QColor(0, 0, 0), 2, Qt::SolidLine));

        painter->setBrush(QColor(255, 255, 255));

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            QRect bar(TL_LEFT_MARGIN-2, TL_UP_MARGIN + (i * TL_HEIGHT), TL_WIDTH+4,  TL_HEIGHT);
            painter->drawRect(bar);
        }

        QFont font;
        font.setPixelSize(40);
        painter->setFont(font);
        painter->setPen(QColor(0, 0, 0));

        for(int i = 0; i < devInfo.videoNum; i++)
        {
            str = tr("CAM%1").arg(i+1);
            painter->drawText(10, TL_UP_MARGIN + (i * TL_HEIGHT) - 1, CH_WIDTH, TL_HEIGHT, textFlag, str);
        }

        font.setPixelSize(40);
        painter->setFont(font);

        for(int i = 0; i < 25; i++)
        {
            str = tr("%1").arg(i);

            if(i < 10)
            {
                painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-10, TL_UP_MARGIN - 40, 50, 30, textFlag, str);
            }
            else
            {
                painter->drawText(TL_LEFT_MARGIN+((TL_WIDTH/24)*i)-25, TL_UP_MARGIN - 40, 50, 30, textFlag, str);
            }
        }

        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));

        for(int i = 0; i < 25; i++)
        {
            painter->drawLine(TL_LEFT_MARGIN+((TL_WIDTH/24)*i), TL_UP_MARGIN, TL_LEFT_MARGIN+((TL_WIDTH/24)*i), TL_UP_MARGIN+(TL_HEIGHT*4));
        }


        if(isDrawRecord)
        {

            bool bOnce = true;

            videoStartPos = audioStartPos = -1;
            videoEndPos   = audioEndPos   = -1;

            int hourMax = 24;

            for(int j = 0; j < devInfo.videoNum; j++)
            {
                for(int k = 0; k < hourMax; k++)
                {
                    for(int i = 0; i < NUM_MIN_PER_HOUR; i++)
                    {
                        bVideoExist = bAudioExist = false;

                        for(int m = 0; m < NUM_15SEC_PER_MIN; m++) // 1 pixel = 1 min. ( 15sec * 4 = 1 min)
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

                            if(bAudioExist && bOnce)
                            {
                                //qDebug("%s()     channel %d, hour %d, secpos %d mask %x", __func__, j, k, secPos, timeLog[k].channel[secPos]);
                                bOnce = false;
                            }
                        }

                        if(bVideoExist)
                        {
                            if((audioEndPos >= 0) && (bAudioExist == false))
                            {
                                rect.setRect(audioStartPos , TL_UP_MARGIN+(j*TL_HEIGHT)+10, audioEndPos, 30);
                                painter->fillRect(rect, QColor(65, 232, 23));
                                rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+25, audioEndPos, 15);
                                painter->fillRect(rect, QColor(235, 173, 71));

                                videoStartPos = audioStartPos = -1;
                                videoEndPos   = audioEndPos   = -1;
                            }

                            if(videoStartPos < 0)
                            {
                                videoStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * 1) + (i * 1);
                                videoEndPos   = 0;
                            }

                            videoEndPos += 1;

                            if(bAudioExist)
                            {
                                if(audioStartPos < 0)
                                {
                                    audioStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * 1) + (i * 1);
                                    audioEndPos   = 0;

                                    rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) +10, videoEndPos - 1, 30);
                                    painter->fillRect(rect, QColor(65, 232, 23));
                                    videoStartPos = TL_LEFT_MARGIN + (k * NUM_MIN_PER_HOUR * 1) + (i * 1);
                                    videoEndPos   = 1;
                                }

                                audioEndPos += 1;
                            }
                        }
                        else
                        {
                            if(videoStartPos >= 0)
                            {
                                if(audioStartPos >= 0)
                                {
                                    rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+10, audioEndPos, 30);
                                    painter->fillRect(rect, QColor(65, 232, 23));
                                    rect.setRect(audioStartPos, TL_UP_MARGIN+(j*TL_HEIGHT)+25, audioEndPos, 15);
                                    painter->fillRect(rect, QColor(235, 173, 71));
                                }
                                else
                                {
                                    rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) +10, videoEndPos, 30);
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
                        rect.setRect(audioStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 10, audioEndPos, 30);
                        painter->fillRect(rect, QColor(65, 232, 23));
                        rect.setRect(audioStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 25, audioEndPos, 15);
                        painter->fillRect(rect, QColor(235, 173, 71));
                    }
                    else
                    {
                        rect.setRect(videoStartPos, TL_UP_MARGIN + (j * TL_HEIGHT) + 10, videoEndPos, 30);
                        painter->fillRect(rect, QColor(65, 232, 23));
                    }

                    videoStartPos = audioStartPos = -1;
                    videoEndPos   = audioEndPos   = -1;
                }
            }
        }

        qDebug(" ............. paintBorder - ");
    }
}
