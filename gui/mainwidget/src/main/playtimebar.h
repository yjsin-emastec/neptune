#ifndef PLAYTIMEBAR_H
#define PLAYTIMEBAR_H

#include <QWidget>
class QPushButton;
class QSlider;
class PlayTimeBar : public QWidget
{
    Q_OBJECT

public:
    PlayTimeBar(QWidget *parent = 0);
    void setTimeFormat(int tFormat);
    void sliderPlayTimeChange();
    void initPlayTimeBar(void);
    void updateSlider(void);
    void updateTimeLinePixmap();
    time_t getLatestPlaybackTime();
    time_t getRecordExistTime(int pos, int dir);
    int updatePlaybackTime(time_t pbTime, int endOverlap);
    int playbackDirection;

    int getTimeLineStatus();
    void setTimeLineStatus(int status);


signals:
    void playTimeChanged(int pos);
    void updateTimeLabel(QString time);
    void updateDateLabel(QString time);

public slots:
    void timeSliderChanged(int val);
    void timeSliderReleased();
    void timeSliderMoved(int val);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void drawTimeLine1(QPainter *painter);
    void drawTimeLine2(QPainter *painter);
    void drawTimeLine3(QPainter *painter);
    void drawTimeLine4(QPainter *painter);

    QSlider *sliderPlayTime;

    QPixmap  timeLinepixmap;

    time_t   lastPbTime;

    bool     is24HourMode,
             isTimeBarDrag,
             isPbTimeChanged,
             isRepaintByTimeOver,
             isSliderChanged;

    int      xPos,
             timeDisplayFormat,
             dlsEndHour,
             lastTickPos,
             resizeTimeLine_LeftGap,
             currentPbHour,
             textWidth,
             textHeight,
             textFontSize,
             lineSize,
             timeLineStatus,
             heightSmall,
             heightBig;

    int      TL_LEFT_MARGIN,
             TL_UP_MARGIN,
             TL_WIDTH,
             TL_HEIGHT,
             TL_SLIDER_HEIGHT,
             TL_SLIDER_HANDLE_GAP,
             NUM_15SEC_PER_MIN,
             NUM_MIN_PER_HOUR,
             NUM_MINIMUM_PIXEL,
             NUM_TICK_SIZE,
             CH_COUNT;
};

#endif // PLAYTIMEBAR_H
