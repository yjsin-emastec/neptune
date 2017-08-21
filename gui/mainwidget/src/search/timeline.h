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

protected:
    void paintEvent(QPaintEvent *event);

private:
    void paintBorder(QPainter *painter);
    void updateTimeLinePixmap();
    QPixmap timeLinepixmap;
	int TL_HEIGHT;
};

#endif // TIMELINE_H
