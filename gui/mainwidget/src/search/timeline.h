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
    bool isDrawRecord;
};

#endif // TIMELINE_H
