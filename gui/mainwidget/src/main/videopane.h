#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>
#include <QtGui>
#include <QRubberBand>
#include "DVR.h"

class QLabel;

#define PAN_TEXT_PAINT           (1)
#define VIDEOPANE_DEBUG_PRINT    (0)

//////////////////////
class CustomRubberBand : public QRubberBand
{
public:
    CustomRubberBand(Shape s, QWidget *p = 0): QRubberBand(s, p) {}

protected:
    void paintEvent(QPaintEvent *pe)
    {
        Q_UNUSED(pe);
        QPainter painter;
        QPen pen(Qt::red, 6);
        pen.setStyle(Qt::SolidLine);

        painter.begin(this);
        painter.setPen(pen);
        painter.drawRect(pe->rect());
        painter.end();
    }
};
class VideoPane : public QWidget
{
    Q_OBJECT

public:
    VideoPane                               (int chNum = -1, const QString & text = NULL, QWidget *parent = 0);
    void setVideoLossDetect                 (int isLoss);
    void setNoRecordVideoDetect             (int isNoVideo);
    void setAlarmDetect                     (int on);
    void setRecordingDetect                 (int record, int sensor, int motion, int prerecord);
    void setChannelName                     (const QString &strName);
    void setOsdEnable                       (int on);
    void setPlaybackMode                    (int on);
    void drawRecordIcon                     (void);
    void drawGpsIcon                        (void);
    void drawAudioIcon                      (void);
    void systemShutdownIconClean            (void);
    void labelNameEnable                    (int enable);
    void setCovertDetect                    (int on);
    void setZoomOut                         (void);
    void updateStringVis                    (int vis);
    void setGpsStatus                       (int gps);
    void setAudioOutput                     (int audio);

    bool                                    inputExistHistory,
                                            zoomAction,
                                            m_flg_update,
                                            m_flg_showVis;

    QString                                 strVis,
                                            m_viewVis;

signals:
    void videoPaneMouseClicked              (int ch);
    void videoPaneMouseDoubleClicked        (int ch);
    void videoPaneMouseRightClicked         (int ch);

public slots:
    void setVideoLoss                       (int val);

protected:
    void paintEvent                         (QPaintEvent  *event);
    void resizeEvent                        (QResizeEvent *event);
    void mousePressEvent                    (QMouseEvent  *event);
    void mouseMoveEvent                     (QMouseEvent  *event);
    void mouseReleaseEvent                  (QMouseEvent  *event);
    void mouseDoubleClickEvent              (QMouseEvent  *event);
    void wheelEvent                         (QWheelEvent  *event);

private:
    void  setPaintingChnamePosition         (int *x, int *y, int *width, int *height);
    QRect makeInvalidateRegion_ChannelName  (QString parmStr_1, QString parmStr_2 = "");
    bool  checkInvalidateRegion_ChannelName (QRect invalidatedRect);
    QRect makeInvalidateRegion_Vis          (QString parmStr_1, QString parmStr_2 = "");
    void  setPaintingVisPosition            (int *x, int *y, int *width, int *height);
    bool  checkInvalidateRegion_Vis         (QRect invalidatedRect);
    void  setPaintingVideoLossPosition      (int *x, int *y, int *width, int *height);
    QRect makeInvalidateRegion_VideoLoss    (QString parmStr_1, QString parmStr_2 = "");
    bool  checkInvalidateRegion_VideoLoss   (QRect invalidatedRect);
    void  alignLabels                       (void);
    void  resizeChannelName                 (void);

    int                                     m_chname_x_align,
                                            m_chname_y_align,
                                            m_videoloss_x_align,
                                            m_videoloss_y_align,
                                            m_posChName_x,
                                            m_posChName_y,
                                            m_posVis_x,
                                            m_posVis_y,
                                            m_posVideoLoss_x,
                                            m_posVideoLoss_y,
                                            m_quickSearchMode,
                                            m_wheelX,
                                            m_wheelY,
                                            right_offset,
                                            videoPaneNo,
                                            videoLoss;

    QLabel                                 *labelName,
                                           *labelNoVideo,
                                           *labelGps,
                                           *labelAudio,
                                           *labelRecord;

    QString                                 strChannelName,
                                            m_viewChName,
                                            m_viewVideoLoss;

    QPoint                                  origin;

    bool                                    audioEnabled,
                                            gpsEnabled,
                                            recordEnabled,
                                            novideoEnabled,
                                            noDataEnabled,
                                            osdEnabled,
                                            isPlayback,
                                            isManualRecord,
                                            zoomStart,
                                            shutdownState,
                                            m_doubleClicked,
                                            m_flg_showChName,
                                            m_flg_showVideoLoss;

    CustomRubberBand                       *rubberBand;

    enum { CHNAME_ALIGN_CENTER, CHNAME_ALIGN_LEFT, CHNAME_ALIGN_RIGHT, CHNAME_ALIGN_TOP, CHNAME_ALIGN_BOTTOM, VIDEOLOSS_ALIGN_CENTER,
           VIDEOLOSS_ALIGN_LEFT, VIDEOLOSS_ALIGN_RIGHT, VIDEOLOSS_ALIGN_TOP, VIDEOLOSS_ALIGN_BOTTOM, VIDEOLOSS_ALIGN_MIDDLE };
};

#endif // VIDEOPANE_H
