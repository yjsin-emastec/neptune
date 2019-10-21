#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QTime>
class QSlider;
class QLabel;
class TimeLine : public QWidget
{
    Q_OBJECT

public:
    TimeLine(QWidget *parent = 0);
    ~TimeLine();
    void updateTimeLine();
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void setFocusStatus(int status);
    void KeyPressEvent(int key);

signals:
    void changeFocus(int status);
    void startPlayback(QTime startTime);

public slots:
    void onDrawTimeLine(bool state);

    void timeSliderPressed();
    void timeSliderMoved(int);
    void timeSliderReleased();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void paintHourBorder(QPainter *painter);
    void paintMinuteBorder(QPainter *painter);
    void updateTimeLinePixmap();

    QPixmap timeLinepixmap;
	int TL_HEIGHT;
    int TL_LEFT_MARGIN;
    int TL_UP_MARGIN;
    int TL_WIDTH;
    int CH_WIDTH;
    int TL_SLIDER_HEIGHT;
    int TL_SLIDER_HANDLE_GAP;

    int NUM_15SEC_PER_MIN;
    int NUM_MIN_PER_HOUR;
    int NUM_PIXEL_PER_MIN;
    int NUM_TICK_SIZE;

    int CH_COUNT;
    int fontSize;

    int textWidth, textHeight;
    int lineSize;

    int selectHour;
    int selectMinute;
    int focusStatus;
    bool isDrawRecord;

    bool isSliderDrag;

    QSlider *sliderSearchTime;
    QLabel *labelSearchTime;
};

#endif // TIMELINE_H
