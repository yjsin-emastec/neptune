#ifndef PLAYTIMEBAR_H
#define PLAYTIMEBAR_H

#include <QWidget>
class QLabel;
class QSlider;
class PlayTimeBar : public QWidget
{
    Q_OBJECT

public:
    PlayTimeBar(QWidget *parent = 0);
    void setTimeFormat(int tFormat);
    void sliderPlayTimeChange();
    void setDlsEndDay(int endHour);
    time_t getLatestPlaybackTime();
    time_t getRecordExistTime(int pos, int dir);
    int updatePlaybackTime(time_t pbTime, int endOverlap);
    int playbackDirection;

signals:
    void playTimeChanged(int pos);

public slots:
    void timeSliderChanged(int val);
    void timeSliderReleased();
    void timeSliderMoved(int val);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void drawTimeLine(QPainter *painter);
    void updateTimeLinePixmap();

    QLabel  *labelDate,
            *labelTime;

    QSlider *sliderPlayTime;

    QPixmap  timeLinepixmap;

    time_t   lastPbTime;

    bool     is24HourMode,
             isTimeBarDrag,
             isPbTimeChanged,
             isRepaintByTimeOver,
             isSliderChanged;

    int      xPos,
             yPos,
             timeDisplayFormat,
             dlsEndHour,
             lastTickPos,
             resizeTimeLine_LeftGap;
};

#endif // PLAYTIMEBAR_H
