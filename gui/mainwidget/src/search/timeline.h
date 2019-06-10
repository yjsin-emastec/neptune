#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>

class TimeLine : public QWidget
{
    Q_OBJECT

public:
    TimeLine(QWidget *parent = 0);
    ~TimeLine();
    void updateTimeLine();

public slots:
    void onDrawTimeLine(bool state);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void paintBorder(QPainter *painter);
    void updateTimeLinePixmap();

    QPixmap timeLinepixmap;
	int TL_HEIGHT;
    int TL_LEFT_MARGIN;
    int TL_UP_MARGIN;
    int TL_WIDTH;
    int CH_WIDTH;
    int NUM_15SEC_PER_MIN;
    int NUM_MIN_PER_HOUR;
    int fontSize;
    bool isDrawRecord;
};

#endif // TIMELINE_H
