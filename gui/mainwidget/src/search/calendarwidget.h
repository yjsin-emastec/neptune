#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QDate>

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    CalendarWidget(QWidget *parent = 0);

    QDate selectedDate() const;
    Qt::DayOfWeek firstDayOfWeek() const;
    void SetCurrentPageIndex(int idx, int dir);
    void SetSelectedDate(const QDate &date);
    void FindData(QDate date);
    void StartPlayback(void);
    void moveFocus(int pos);
    void initFocus(void);
    int getSelectedPos(void);

signals:
    void selectedDateChanged(const QDate &newDate);
    void activated();
	void startPlayback();
    void drawTimeLine(bool state);

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void drawHeaderCell(QPainter *painter, const QRect &rect, int weekday);
    void drawEmptyCell(QPainter *painter, const QRect &rect);
    void drawItemCell(QPainter *painter, const QRect &rect, int weekday, int day);
    void drawFocus(QPainter *painter);
    void computeMonthBoundaries();
    bool isDate(QPoint pos) const;
    bool isRecordDate(int day);
    QDate FindDate(int pos) const;

    QDate m_selectedDate;
    Qt::DayOfWeek m_firstDayOfWeek;

    quint8 m_monthStartAt, m_monthEndAt;
    int m_headHeight, m_cellHeight, m_cellWidth, pageIndex;
    int selectedPos;
    int fontSize;
};

#endif // CALENDARWIDGET_H
