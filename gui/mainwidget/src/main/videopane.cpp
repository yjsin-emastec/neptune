#include <QtGui>
#include "videopane.h"
#include "mainglobal.h"
#include "appmgr.h"
#include "DVR.h"
#include "dev/Ver.h"
#include <core/Core.h>

#define TOP_BOTTOM_OFFSET                      18
#define LEFT_RIGHT_OFFSET                      10
#define SPLIT_LINE_WIDTH                       0

#define CHNAME_POS_X_OFFSET                    0
#define CHNAME_POS_Y_OFFSET                    10

#define VIDEOLOSS_POS_X_OFFSET                 0
#define VIDEOLOSS_POS_Y_OFFSET                 0

#define FONT_PIXELSIZE_CHANNELNAME             32

#define CHANNEL_LABEL_NORMAL_STYLE             "color:white;font-weight:bold;font-size:16px;"
#define CHANNEL_LABEL_FOCUS_STYLE              "color:rgb(255, 168, 80);font-weight:bold;font-size:16px;"
#define NOVIDEO_LABEL_NORMAL_STYLE             "color:white;font-weight:bold;font-size:24px;"
#define NOVIDEO_LABEL_FOCUS_STYLE              "color:rgb(255, 168, 80);font-weight:bold;font-size:24px;"
#define CIFMODEL_CHANNEL_LABEL_NORMAL_STYLE    "color:white;font-weight:bold;font-size:24px;"
#define CIFMODEL_CHANNEL_LABEL_FOCUS_STYLE     "color:rgb(255, 168, 80);font-weight:bold;font-size:24px;"

VideoPane::VideoPane(int chNum, const QString & text, QWidget *parent)
    : QWidget(parent)
{
    QString str;
    QString style   = QString(CHANNEL_LABEL_NORMAL_STYLE);
    QColor barColor = QColor(20, 22, 24);

    setWindowFlags(Qt::FramelessWindowHint);

    setPalette(QPalette(barColor));

    setAutoFillBackground(true);

    if(ver_get_mouse_cursor() == ver_mouse_cursor_sw)
    {
        setMouseTracking(true);
    }

    videoPaneNo       = chNum;
    inputExistHistory = false;
    strChannelName    = text;

    int arVIS[MAX_VIDEO_CH];

    ver_get_vis_list(arVIS);

    updateStringVis(arVIS[videoPaneNo]);

    m_chname_x_align    = CHNAME_ALIGN_CENTER;
    m_chname_y_align    = CHNAME_ALIGN_TOP;
    m_videoloss_x_align = VIDEOLOSS_ALIGN_CENTER;
    m_videoloss_y_align = VIDEOLOSS_ALIGN_MIDDLE;

    gpsEnabled          = false;
    audioEnabled        = false;
    recordEnabled       = false;
    novideoEnabled      = false;
    isPlayback          = false;
    noDataEnabled       = false;
    osdEnabled          = false;
    zoomStart           = false;
    zoomAction          = false;
    shutdownState       = false;
    videoLoss           = 0;
    m_doubleClicked     = false;

    labelName = new QLabel(text, this);
    labelName->setStyleSheet(CIFMODEL_CHANNEL_LABEL_NORMAL_STYLE);//"background:#ff00ff;");
    labelName->setAlignment(Qt::AlignCenter);

    labelNoVideo = new QLabel(this);
    labelNoVideo->setStyleSheet(QString(NOVIDEO_LABEL_NORMAL_STYLE));
    labelNoVideo->hide();
    labelNoVideo->setAlignment(Qt::AlignCenter);

    labelAudio = new QLabel(this);
    labelAudio->setPixmap(QPixmap(":/images/audio.png"));
    labelAudio->adjustSize();
    labelAudio->hide();

    labelGps = new QLabel(this);
    labelGps->setPixmap(QPixmap(":/images/gps.png"));
    labelGps->adjustSize();
    labelGps->hide();

    labelRecord = new QLabel(this);
    labelRecord->setPixmap(QPixmap(":/images/record_on.png"));
    labelRecord->adjustSize();
    labelRecord->hide();

    if(ver_get_oem() == OEM_DAEJI)
    {
        labelDaejiLogo360 = new QLabel(this);
        labelDaejiLogo360->setPixmap(QPixmap(":/images/daeji/daeji_640x360.png"));
        labelDaejiLogo360->adjustSize();
        labelDaejiLogo360->hide();

        labelDaejiLogo720 = new QLabel(this);
        labelDaejiLogo720->setPixmap(QPixmap(":/images/daeji/daeji_1280x720.png"));
        labelDaejiLogo720->adjustSize();
        labelDaejiLogo720->hide();

        labelDaejiLogo1080 = new QLabel(this);
        labelDaejiLogo1080->setPixmap(QPixmap(":/images/daeji/daeji_1920x1080.png"));
        labelDaejiLogo1080->adjustSize();
        labelDaejiLogo1080->hide();
    }

    if((videoPaneNo == devInfo.videoNum) && (devInfo.videoNum == 8 || devInfo.videoNum == 16))
    {
        int paneWidth, paneHeight, w, h;

        appmgr_get_screen_size(&paneWidth, &paneHeight);

        w = (int)(paneWidth  / 3);
        h = (int)(paneHeight / 3);

        this->m_flg_showChName = false;
        this->m_flg_update     = true;

        update();
    }

    rubberBand = new CustomRubberBand(QRubberBand::Rectangle, this);

    this->labelName->hide();
    this->m_flg_showChName    = false;
    this->m_flg_showVideoLoss = false;
    this->m_posChName_x       = 0;
    this->m_posChName_y       = 0;
    this->m_posVideoLoss_x    = 0;
    this->m_posVideoLoss_y    = 0;
    this->m_viewChName        = "";
    this->m_viewVideoLoss     = "";
    this->m_viewVis           = "";
    this->m_flg_showVis       = false;

    setLayoutDirection(Qt::LeftToRight);
}
void VideoPane::paintEvent(QPaintEvent *event)
{
    QPainter painterBorder(this);

    int paneWidth  = size().width();
    int paneHeight = size().height();

    if(devInfo.videoNum == this->videoPaneNo)
    {
        return;
    }

#if(VIDEOPANE_DEBUG_PRINT)
    printf("VIDEOPANE [ %0d ]::PAINT_EVENT_CHANNEL", videoPaneNo);
#endif

    if(this->m_flg_showChName && checkInvalidateRegion_ChannelName(event->rect()) && utils_cfg_cmp_item(DisplayCfg.osd_chname, "ON") == 0)
    {
#if(VIDEOPANE_DEBUG_PRINT)
        printf("_NAME");
#endif
        QPainter painter(this);
        QFont font = painter.font();
        QPen  pen  = painter.pen();
        painter.save();
        font.setPixelSize(32);
        painter.setFont(font);
        pen.setColor(QColor(39,0,79));
        painter.setPen(pen);

        int align = Qt::AlignCenter;
        int _width, _height;

        this->setPaintingChnamePosition(&m_posChName_x, &m_posChName_y, &_width, &_height);
        m_posChName_x = 11;
        painter.drawText(this->m_posChName_x-1, this->m_posChName_y,   _width, _height, align, this->m_viewChName);
        painter.drawText(this->m_posChName_x+1, this->m_posChName_y,   _width, _height, align, this->m_viewChName);
        painter.drawText(this->m_posChName_x,   this->m_posChName_y-1, _width, _height, align, this->m_viewChName);
        painter.drawText(this->m_posChName_x,   this->m_posChName_y+1, _width, _height, align, this->m_viewChName);

        pen.setColor(QColor(255,128,64));
        painter.setPen(pen);
        painter.drawText(this->m_posChName_x, this->m_posChName_y, _width, _height, align, this->m_viewChName);
        painter.restore();
    }

    if(this->m_flg_showVis && checkInvalidateRegion_Vis(event->rect()) && utils_cfg_cmp_item(DisplayCfg.osd_camera, "ON") == 0)
    {
        QPainter painter(this);
        QFont font = painter.font();
        QPen  pen  = painter.pen();

        painter.save();
        font.setPixelSize(32);
        painter.setFont(font);
        pen.setColor(QColor(39,0,79));
        painter.setPen(pen);

        int align = Qt::AlignLeft;
        int _width, _height;

        this->setPaintingVisPosition(&m_posVis_x, &m_posVis_y, &_width, &_height);

        if(!isPlayback)
        {
            painter.drawText(this->m_posVis_x-1, this->m_posVis_y,   _width, _height, align, this->strVis);
            painter.drawText(this->m_posVis_x+1, this->m_posVis_y,   _width, _height, align, this->strVis);
            painter.drawText(this->m_posVis_x,   this->m_posVis_y-1, _width, _height, align, this->strVis);
            painter.drawText(this->m_posVis_x,   this->m_posVis_y+1, _width, _height, align, this->strVis);
        }

        pen.setColor(QColor(255,255,255));
        painter.setPen(pen);

        if(!isPlayback)
        {
            painter.drawText(this->m_posVis_x, this->m_posVis_y, _width, _height, align, this->strVis);
        }
        painter.restore();
    }

    if(this->m_flg_showVideoLoss && checkInvalidateRegion_VideoLoss(event->rect()) && utils_cfg_cmp_item(DisplayCfg.osd_viloss, "ON") == 0)
    {
#if(VIDEOPANE_DEBUG_PRINT)
        printf("_LOSS");
#endif
        QPainter painter(this);
        QFont font = painter.font();
        QPen  pen  = painter.pen();

        painter.save();

        font.setPixelSize(32);

        painter.setFont(font);
        pen.setColor(QColor(39,0,79));
        painter.setPen(pen);

        int align = Qt::AlignCenter;
        int _width, _height;

        this->setPaintingVideoLossPosition(&m_posVideoLoss_x, &m_posVideoLoss_y, &_width, &_height);

        painter.drawText(this->m_posVideoLoss_x-1, this->m_posVideoLoss_y,   _width, _height, align, this->m_viewVideoLoss);
        painter.drawText(this->m_posVideoLoss_x+1, this->m_posVideoLoss_y,   _width, _height, align, this->m_viewVideoLoss);
        painter.drawText(this->m_posVideoLoss_x,   this->m_posVideoLoss_y-1, _width, _height, align, this->m_viewVideoLoss);
        painter.drawText(this->m_posVideoLoss_x,   this->m_posVideoLoss_y+1, _width, _height, align, this->m_viewVideoLoss);

        pen.setColor(QColor(255, 255, 255));
        painter.setPen(pen);
        painter.drawText(this->m_posVideoLoss_x, this->m_posVideoLoss_y, _width, _height, align, this->m_viewVideoLoss);
        painter.restore();
    }

    m_flg_update = false;
#if(VIDEOPANE_DEBUG_PRINT)
    printf("\n");
#endif
}
void VideoPane::resizeEvent(QResizeEvent *event)
{
    alignLabels();
}
void VideoPane::mousePressEvent(QMouseEvent *event)
{
    if(systemLocked)
    {
        emit videoPaneMouseClicked(videoPaneNo);
        return;
    }

    if(event->button() == Qt::LeftButton)
    {
        emit videoPaneMouseClicked(videoPaneNo);

        origin = event->globalPos();

        if(appmgr_get_split() == Split_1)
        {
            if(zoomAction == false)
            {
                if(!rubberBand)
                {
                    rubberBand = new CustomRubberBand(QRubberBand::Rectangle, this);
                }

                rubberBand->setGeometry(QRect(origin, QSize()));
                rubberBand->show();
                zoomStart = true;
            }
        }
    }

    if(m_doubleClicked == true)
    {
        m_doubleClicked = false;
    }
}
void VideoPane::mouseMoveEvent(QMouseEvent *event)
{
    if(zoomStart == true)
    {
        rubberBand->setGeometry(QRect(origin, event->globalPos()).normalized());
    }

    if(ver_get_mouse_cursor() == ver_mouse_cursor_sw)
    {
        appmgr_hwcursor_position(event->globalPos().x(), event->globalPos().y());
    }
}
void VideoPane::mouseReleaseEvent(QMouseEvent *event)
{
    if(systemLocked)
    {
        return;
    }

    if(event->button() == Qt::LeftButton)
    {
        if(appmgr_get_split() == Split_1)
        {
            if(zoomAction == true)
            {
                appmgr_set_zoom(0, 0, 0, 0);

                zoomAction = false;
                zoomStart  = false;

                rubberBand->hide();

                return;
            }

            if(zoomStart == true)
            {
                zoomStart = false;
                qDebug("RubberBand end (%d, %d) (%d,%d) (%d,%d) \n", origin.x(), origin.y(), event->pos().x(), event->pos().y(), event->globalPos().x(), event->globalPos().y());
                int x1 = origin.x();
                int y1 = origin.y();
                int x2 = event->globalPos().x();
                int y2 = event->globalPos().y();
                int tmp;
                int zoomX = 0;
                int zoomY = 0;

                if(x1 > x2)
                {
                    tmp = x1;
                    x1  = x2;
                    x2  = tmp;
                }

                if(y1 > y2)
                {
                    tmp = y1;
                    y1  = y2;
                    y2  = tmp;
                }

                x1 = x1 + x1%2;
                y1 = y1 + y1%2;
                x2 = x2 + x2%2;
                y2 = y2 + y2%2;

                qDebug("(%d, %d) \n", x2-x1 ,y2-y1);

                zoomX = x2-x1;
                zoomY = y2-y1;

                if((x2-x1) > 0 && (x2-x1) < 16)
                {
                    zoomX = 16;

                    if((y2-y1) == 0)
                    {
                        zoomY = 16;
                    }
                }

                if((y2-y1) > 0 && (y2-y1) < 16)
                {
                    zoomY = 16;

                    if((x2-x1) == 0)
                    {
                        zoomX = 16;
                    }
                }

                if(zoomX >= 16 && zoomY >= 16)
                {
                    if(zoomAction == false)
                    {
                        appmgr_set_zoom(x1, y1, zoomX, zoomY);

                        zoomAction = true;

                        rubberBand->setGeometry(width() - (width()/4) + x1/4, height() - (height()/4) + y1/4, (zoomX)/4, (zoomY)/4);
                    }
                }
                else
                {
                    appmgr_set_zoom(0, 0, 0, 0);

                    zoomAction = false;
                }
            }
        }

        if(zoomAction == false)
        {
            rubberBand->hide();
        }

        if(this->x() == 0 && this->y() == 0)
        {
            return;
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(zoomAction == true)
        {
            appmgr_set_zoom(0, 0, 0, 0);

            zoomAction = false;
            zoomStart  = false;

            rubberBand->hide();
        }

        if(!isPlayback)
        {
            emit videoPaneMouseRightClicked(videoPaneNo);
        }
    }
}
void VideoPane::wheelEvent(QWheelEvent *event)
{
    if(appmgr_get_split() == Split_1)
    {
        if(zoomAction == false)
        {
            m_wheelX = event->x();
            m_wheelY = event->y();
            qDebug("= VideoPan wheel %d : %d, %d",videoPaneNo, event->x(), event->y());
        }
        else
        {
            qDebug("= %d, %d =====%d",m_wheelX, m_wheelY, event->delta());
        }
    }
}
void VideoPane::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(systemLocked)
    {
        return;
    }

    if(event->button() == Qt::LeftButton)
    {
        zoomAction      = false;
        m_doubleClicked = true;

        appmgr_set_zoom(0, 0, 0, 0);

        emit videoPaneMouseDoubleClicked(videoPaneNo);
    }
    else if(event->button() == Qt::RightButton)
    {
        ;
    }
}
void VideoPane::resizeChannelName(void)
{
    int chLen, labelLen, maxLen = 0;
    QString str;

    if(shutdownState)
    {
        return;
    }

    chLen    = strChannelName.size();
    labelLen = labelName->size().width();

    if(chLen == 0)
    {
        qDebug(" stinr is  .... ");
        qDebug() << strChannelName;

        if(this->m_flg_showChName)
        {
            update(this->makeInvalidateRegion_ChannelName(this->m_viewChName, strChannelName));
        }

        if(this->m_flg_showVideoLoss)
        {
            update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
        }

        if(this->m_flg_showVis)
        {
            update(this->makeInvalidateRegion_Vis(this->m_viewVis));
        }

        this->m_flg_showVis    = true;
        this->m_viewChName     = strChannelName;
        this->m_flg_showChName = true;
        this->m_flg_update     = true;

        return;
    }

    maxLen = 0;
    str    = strChannelName;

    if(labelLen > 1200)                         // 1split
    {
       ;
    }
    else if(labelLen < 1200 && labelLen > 600)  // 4 split
    {
        maxLen = 34;
    }
    else if(labelLen < 600 && labelLen > 400)   // 9 split
    {
        maxLen = 16;
    }
    else                                        // 16 split
    {
        maxLen = 10;
    }

    qDebug(" string .... %d, %d", chLen, maxLen);

    if(maxLen && (chLen > maxLen))
    {
        str.resize(maxLen);
        str += tr("...");
    }

    if(this->m_flg_showChName)
    {
        update(this->makeInvalidateRegion_ChannelName(this->m_viewChName, str));
    }

    if(this->m_flg_showVideoLoss)
    {
        update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
    }

    if(this->m_flg_showVis)
    {
        update(this->makeInvalidateRegion_Vis(this->m_viewVis));
    }

    this->m_flg_showVis    = true;
    this->m_viewChName     = str;
    this->m_flg_showChName = true;
    this->m_flg_update     = true;
}
void VideoPane::alignLabels(void)
{
    int paneWidth = size().width();
    int labelWidth, offset_x, labelHeight;
    int mainWidth = appmgr_get_mainwidget_width();

    if(shutdownState)
    {
        return;
    }

    if(labelName)
    {
        offset_x    = 30;
        labelHeight = labelName->sizeHint().height();
        labelName->resize(paneWidth - offset_x, labelHeight);

        offset_x = (int)(offset_x/2);
        labelName->move(offset_x, TOP_BOTTOM_OFFSET);
        resizeChannelName();
    }

    if(labelNoVideo)
    {
        offset_x    = 30;
        labelHeight = labelNoVideo->sizeHint().height();
        labelNoVideo->resize(paneWidth - offset_x, labelHeight);

        offset_x = (int)(offset_x/2);
        labelNoVideo->move(offset_x, size().height()/2);
    }

    if(mainWidth / 1 == paneWidth)
    {
        right_offset = 40;
    }
    else if(mainWidth / 2 == paneWidth)
    {
        if(videoPaneNo % 2 == 1)
        {
            right_offset = 40;
        }
        else
        {
            right_offset = 25;
        }
    }
    else if(mainWidth / 3 == paneWidth)
    {
        right_offset = 40;
    }
    else if(mainWidth / 4 == paneWidth)
    {
        if(videoPaneNo % 4 == 3)
        {
            right_offset = 40;
        }
        else
        {
            right_offset = 18;
        }
    }
    else
    {
        right_offset = 40;
    }

    right_offset = 18;
    offset_x     = 0;

    if(labelRecord)
    {
        labelWidth = labelRecord->sizeHint().width();

        if(offset_x)
        {
            offset_x = offset_x - labelWidth - 6;
        }
        else
        {
            offset_x = paneWidth - labelWidth - right_offset - 6;
        }

        labelRecord->move(offset_x, TOP_BOTTOM_OFFSET);
    }

    offset_x = 0;

    if(labelAudio)
    {
        labelWidth = labelAudio->sizeHint().width();
        offset_x   = paneWidth - labelWidth - labelRecord->sizeHint().width() - right_offset-6;

        labelAudio->move(offset_x, TOP_BOTTOM_OFFSET-6);
    }

    if(labelGps)
    {
        labelWidth = labelGps->sizeHint().width();
        offset_x   = paneWidth - labelWidth - labelRecord->sizeHint().width() - right_offset+35;
        labelGps->move(offset_x, TOP_BOTTOM_OFFSET);
    }
}
void VideoPane::setVideoLossDetect(int isLoss)
{
    QString str;
    int labelWidth, offset_x;

    if(shutdownState)
    {
        return;
    }

    if(isPlayback)
    {
        ;
    }
    else
    {
        if(isLoss)
        {
            str = tr("NO VIDEO");

            labelWidth = labelNoVideo->sizeHint().width();

            offset_x   = (int)(30/2);

            labelNoVideo->move(offset_x, size().height()/2);

            setAudioOutput(0);
        }
        else
        {
            str = tr("");
        }
    }

    novideoEnabled = isLoss ? true : false;

    if(!isPlayback)
    {
        if(isLoss)
        {
            labelNoVideo->hide();
        }
        else
        {
            labelNoVideo->hide();
        }

        this->m_flg_showChName    = true;
        this->m_flg_showVideoLoss = true;

        if(this->m_flg_showVideoLoss)
        {
            update(this->makeInvalidateRegion_VideoLoss(m_viewVideoLoss, str));
        }

        this->m_viewVideoLoss = str;
        this->m_flg_update    = true;
    }
}
void VideoPane::setNoRecordVideoDetect(int isNoVideo)
{
    QString str;

    if(shutdownState)
    {
        return;
    }

    if(isNoVideo)
    {
        str = tr("NO DATA");
    }
    else
    {
        str = tr("");
    }

    noDataEnabled = isNoVideo ? true : false;

    this->m_flg_showChName    = true;
    this->m_flg_showVideoLoss = true;
    this->m_flg_update        = true;

    if(this->m_flg_showVideoLoss)
    {
        update(this->makeInvalidateRegion_VideoLoss(m_viewVideoLoss, str));
    }

    this->m_viewVideoLoss = str;

    update();
}
void VideoPane::setGpsStatus(int gps)
{
    gpsEnabled = gps ? true : false;

    if(!isPlayback)
    {
        drawGpsIcon();
    }
}
void VideoPane::setAudioOutput(int audio)
{
    audioEnabled = audio ? true : false;

    drawAudioIcon();
}
void VideoPane::setRecordingDetect(int record, int sensor, int motion, int prerecord)
{
    if(shutdownState)
    {
        return;
    }

    recordEnabled = record ? true : false;

    if(!isPlayback)
    {
        drawRecordIcon();
    }
}
void VideoPane::setAlarmDetect(int on)
{
    if(shutdownState)
    {
        return;
    }
}
void VideoPane::setChannelName(const QString &strName)
{
    if(shutdownState)
    {
        return;
    }

    strChannelName = strName;

    qDebug(" setChannelName is  .... ");
    qDebug() << strName;
    qDebug() << strChannelName;

    resizeChannelName();
}
void VideoPane::setPlaybackMode(int on)
{
    if(shutdownState)
    {
        return;
    }

    isPlayback = on ? true : false;

    if(isPlayback)
    {
        labelNoVideo->hide();
        labelGps->hide();
        labelAudio->hide();
        labelRecord->hide();

        this->m_flg_showVideoLoss = true;
        this->m_flg_showChName    = true;
        this->m_flg_update        = true;

        if(this->m_flg_showChName)
        {
            update(this->makeInvalidateRegion_ChannelName(this->m_viewChName));
        }

        if(this->m_flg_showVideoLoss)
        {
            update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
        }
    }
    else
    {
        if(osdEnabled)
        {
            setOsdEnable(1);
        }
        else
        {
            setOsdEnable(0);
        }

        this->m_flg_showVideoLoss = true;
        this->m_flg_showChName    = true;
        this->m_flg_update        = true;

        if(this->m_flg_showChName)
        {
            update(this->makeInvalidateRegion_ChannelName(this->m_viewChName));
        }
        if(this->m_flg_showVideoLoss)
        {
            update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
        }
    }
}
void VideoPane::setOsdEnable(int on)
{
    if(shutdownState)
    {
        return;
    }

    osdEnabled = on ? true : false;

    if(utils_cfg_cmp_item(DisplayCfg.osd_chname, "ON") == 0)
    {
        this->m_flg_showChName = true;
        this->m_flg_update     = true;

        if(this->m_flg_showChName)
        {
            update(this->makeInvalidateRegion_ChannelName(this->m_viewChName));
        }

        drawRecordIcon();
    }
    else
    {
        this->m_flg_showChName = false;
        this->m_flg_update     = true;

        if(this->m_flg_showChName)
        {
            update(this->makeInvalidateRegion_ChannelName(this->m_viewChName));
        }

        drawRecordIcon();
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_viloss, "ON") == 0)
    {
        this->m_flg_showVideoLoss = true;
        this->m_flg_update        = true;

        if(this->m_flg_showVideoLoss)
        {
            update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
        }

        drawRecordIcon();

        if(novideoEnabled)
        {
            setVideoLossDetect(1);
        }
    }
    else
    {
        this->m_flg_showVideoLoss = false;
        this->m_flg_update        = true;

        if(this->m_flg_showVideoLoss)
        {
            update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
        }

        drawRecordIcon();
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_camera, "ON") == 0)
    {
        this->m_flg_showVis = true;
        this->m_flg_update  = true;

        if(this->m_flg_showVis)
        {
            update(this->makeInvalidateRegion_Vis(this->m_viewVis));
        }
    }
    else
    {
        this->m_flg_showVis = false;
        this->m_flg_update  = true;

        if(this->m_flg_showVis)
        {
            update(this->makeInvalidateRegion_Vis(this->m_viewVis));
        }
    }
}
void VideoPane::drawGpsIcon(void)
{
    if(shutdownState)
    {
        return;
    }

    if(gpsEnabled)
    {
        labelGps->setPixmap(QPixmap(":/images/gps.png"));
        labelGps->show();
    }
    else
    {
        labelGps->hide();
    }
}
void VideoPane::drawAudioIcon(void)
{
    if(shutdownState)
    {
        return;
    }

    if(audioEnabled)
    {
        labelAudio->setPixmap(QPixmap(":/images/audio.png"));
        labelAudio->show();
    }
    else
    {
        labelAudio->hide();
    }
}
void VideoPane::drawRecordIcon(void)
{
    if(shutdownState)
    {
        return;
    }

    if(utils_cfg_cmp_item(DisplayCfg.osd_record, "OFF") == 0)
    {
        labelRecord->hide();
        return;
    }

    if((recordEnabled == true) && (novideoEnabled == true))
    {
        novideoEnabled = false;
    }

    if(novideoEnabled)
    {
        labelRecord->hide();
    }
    else
    {
        if(recordEnabled)
        {
            labelRecord->setPixmap(QPixmap(":/images/record_on.png"));
            labelRecord->show();
        }
        else
        {
            labelRecord->hide();
        }
    }
}
void VideoPane::systemShutdownIconClean(void)
{
    shutdownState = true;

    labelRecord->hide();
    labelGps->hide();
    labelAudio->hide();

    this->m_flg_showVideoLoss = false;
    this->m_flg_showChName    = false;
    this->m_flg_update        = true;

    if(this->m_flg_showChName)
    {
        update(this->makeInvalidateRegion_ChannelName(this->m_viewChName));
    }

    if(this->m_flg_showVideoLoss)
    {
        update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
    }

    update();
}
void VideoPane::labelNameEnable(int enable)
{
    if(enable)
    {
        this->m_flg_showChName = true;
    }
    else
    {
        this->m_flg_showChName = false;
    }

    this->m_flg_update = true;

    if(this->m_flg_showChName)
    {
        update(this->makeInvalidateRegion_ChannelName(this->m_viewChName));
    }

    if(this->m_flg_showVideoLoss)
    {
        update(this->makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss));
    }
}
void VideoPane::setPaintingChnamePosition(int *x, int *y, int *width, int *height)
{
    QRect rt = makeInvalidateRegion_ChannelName(this->m_viewChName);
    *x       = rt.x() + 1;
    *y       = rt.y() + 1;
    *width   = rt.width()  - 2;
    *height  = rt.height() - 2;
}
QRect VideoPane::makeInvalidateRegion_ChannelName(QString parmStr_1, QString parmStr_2)
{
    QFont ft = this->font();

    ft.setPixelSize(FONT_PIXELSIZE_CHANNELNAME);

    QFontMetrics fm(ft);

    int chname_width_tmp_1 = fm.width(parmStr_1);
    int chname_width_tmp_2 = fm.width(parmStr_2);
    int chname_width;

    chname_width = (chname_width_tmp_1 > chname_width_tmp_2 ? chname_width_tmp_1 : chname_width_tmp_2);

    if(chname_width>0)
    {
        chname_width += 2;
    }

    int chname_height = fm.height() + 2;
    QRect rt;

    switch(m_chname_x_align)
    {
        case CHNAME_ALIGN_CENTER: { rt.setX((this->width() - chname_width)/2                    ); break; }
        case CHNAME_ALIGN_LEFT:   { rt.setX(CHNAME_POS_X_OFFSET                                 ); break; }
        case CHNAME_ALIGN_RIGHT:  { rt.setX(this->width() - chname_width - CHNAME_POS_X_OFFSET  ); break; }
    }

    switch(m_chname_y_align)
    {
        case CHNAME_ALIGN_TOP:    { rt.setY(CHNAME_POS_Y_OFFSET                                 ); break; }
        case CHNAME_ALIGN_BOTTOM: { rt.setY(this->height() - CHNAME_POS_Y_OFFSET - chname_height); break; }
    }

    rt.setWidth (chname_width);
    rt.setHeight(chname_height);

    return rt;
}
bool VideoPane::checkInvalidateRegion_ChannelName(QRect invalidatedRect)
{
    QRect rt = makeInvalidateRegion_ChannelName(this->m_viewChName);

    return invalidatedRect.intersects(rt);
}
void VideoPane::setPaintingVideoLossPosition(int *x, int *y, int *width, int *height)
{
    QRect rt = makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss);
    *x       = rt.x()      + 1;
    *y       = rt.y()      + 1;
    *width   = rt.width()  - 2;
    *height  = rt.height() - 2;
}
QRect VideoPane::makeInvalidateRegion_VideoLoss(QString parmStr_1, QString parmStr_2)
{
    QFont ft = this->font();

    ft.setPixelSize(FONT_PIXELSIZE_CHANNELNAME);

    QFontMetrics fm(ft);

    int videoloss_width_tmp1 = fm.width(parmStr_1);
    int videoloss_width_tmp2 = fm.width(parmStr_2);
    int videoloss_width;

    videoloss_width = (videoloss_width_tmp1 > videoloss_width_tmp2 ? videoloss_width_tmp1 : videoloss_width_tmp2);

    if(videoloss_width>0)
    {
        videoloss_width += 2;
    }

    int videoloss_height = fm.height()+2;
    QRect rt;

    switch(m_videoloss_x_align)
    {
        case VIDEOLOSS_ALIGN_CENTER: { rt.setX((this->width() - videoloss_width)/2                     ); break; }
        case VIDEOLOSS_ALIGN_LEFT:   { rt.setX(VIDEOLOSS_POS_X_OFFSET                                  ); break; }
        case VIDEOLOSS_ALIGN_RIGHT:  { rt.setX(this->width() - videoloss_width - VIDEOLOSS_POS_X_OFFSET); break; }
    }

    switch(m_videoloss_y_align)
    {
        case VIDEOLOSS_ALIGN_MIDDLE:
        default:                     { rt.setY((this->height() - videoloss_height)/2                   ); break; }
    }

    rt.setWidth(videoloss_width);
    rt.setHeight(videoloss_height);

    return rt;
}
bool VideoPane::checkInvalidateRegion_VideoLoss(QRect invalidatedRect)
{
    QRect rt = makeInvalidateRegion_VideoLoss(this->m_viewVideoLoss);

    return invalidatedRect.intersects(rt);
}
void VideoPane::setZoomOut(void)
{
    zoomAction = false;
    zoomStart  = false;
    rubberBand->hide();
    return;
}
void VideoPane::setVideoLoss(int val)
{
    videoLoss = val;
}
void VideoPane::updateStringVis(int vis)
{
    switch(vis)
    {
        case ver_vis_pal:         { this->strVis = tr("PAL"    ); break; }
        case ver_vis_ntsc:        { this->strVis = tr("NTSC"   ); break; }
        case ver_vis_hd_720_25p:  { this->strVis = tr("720p25" ); break; }
        case ver_vis_hd_720_30p:  { this->strVis = tr("720p30" ); break; }
        case ver_vis_hd_720_50p:  { this->strVis = tr("720p50" ); break; }
        case ver_vis_hd_720_60p:  { this->strVis = tr("720p60" ); break; }
        case ver_vis_hd_1080_25p: { this->strVis = tr("1080p25"); break; }
        case ver_vis_hd_1080_30p: { this->strVis = tr("1080p30"); break; }
        case ver_vis_hd_1080_50p: { this->strVis = tr("1080p50"); break; }
        case ver_vis_hd_1080_60p: { this->strVis = tr("1080p60"); break; }
        case ver_vis_hd_1080_i50: { this->strVis = tr("1080i50"); break; }
        case ver_vis_hd_1080_i60: { this->strVis = tr("1080i60"); break; }
        default:                  { this->strVis = tr(""       ); break; }
    }
}
void VideoPane::setPaintingVisPosition(int *x, int *y, int *width, int *height)
{
    QRect rt = makeInvalidateRegion_Vis(this->strVis);
    *x       = rt.x()      + 1;
    *y       = rt.y()      + 1;
    *width   = rt.width()  - 2;
    *height  = rt.height() - 2;
}
QRect VideoPane::makeInvalidateRegion_Vis(QString parmStr_1, QString parmStr_2)
{
    QFont ft = this->font();

    ft.setPixelSize(FONT_PIXELSIZE_CHANNELNAME);

    QFontMetrics fm(ft);

    int chname_width_tmp_1 = fm.width(parmStr_1);
    int chname_width_tmp_2 = fm.width(parmStr_2);
    int chname_width;

    chname_width = (chname_width_tmp_1 > chname_width_tmp_2 ? chname_width_tmp_1 : chname_width_tmp_2);

    if(chname_width>0)
    {
        chname_width += 2;
    }

    int chname_height = fm.height() + 2;
    QRect rt;

    switch(CHNAME_ALIGN_CENTER)
    {
        case CHNAME_ALIGN_CENTER: { rt.setX((this->width() - chname_width)/2                          ); break; }
        case CHNAME_ALIGN_LEFT:   { rt.setX(CHNAME_POS_X_OFFSET                                       ); break; }
        case CHNAME_ALIGN_RIGHT:  { rt.setX(this->width() - chname_width - CHNAME_POS_X_OFFSET        ); break; }
    }

    switch(CHNAME_ALIGN_BOTTOM)
    {
        case CHNAME_ALIGN_TOP:    { rt.setY(CHNAME_POS_Y_OFFSET                                       ); break; }
        case CHNAME_ALIGN_BOTTOM: { rt.setY(this->height() - CHNAME_POS_Y_OFFSET - (chname_height * 2)); break; }
    }

    rt.setWidth(chname_width);
    rt.setHeight(chname_height);

    return rt;
}
bool VideoPane::checkInvalidateRegion_Vis(QRect invalidatedRect)
{
    QRect rt = makeInvalidateRegion_Vis(this->strVis);

    return invalidatedRect.intersects(rt);
}
int VideoPane::isVisibleRecordIcon(void)
{
    return labelRecord->isVisible();
}
void VideoPane::DisplayLogo(int oem, int resolution)
{
    if(ver_get_oem() != oem)
    {
        return;
    }

    switch(oem)
    {
        case OEM_DAEJI:
        {
            if(resolution == RESOLUTION_HD_640x360)
            {
                labelDaejiLogo720 ->hide();
                labelDaejiLogo1080->hide();
                labelDaejiLogo360 ->show();
            }
            else if(resolution ==  RESOLUTION_HD_1280x720)
            {
                labelDaejiLogo360 ->hide();
                labelDaejiLogo1080->hide();
                labelDaejiLogo720 ->show();
            }
            else if(resolution ==  RESOLUTION_HD_1920x1080)
            {
                labelDaejiLogo360 ->hide();
                labelDaejiLogo720 ->hide();
                labelDaejiLogo1080->show();
            }

            break;
        }
        default:
        {
            break;
        }
    }
}
