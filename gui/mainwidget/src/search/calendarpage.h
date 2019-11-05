#ifndef CALENDARPAGE_H
#define CALENDARPAGE_H

#include <QtGui/QWidget>
#include "ui_calendarpage.h"

class CalendarWidget;
class QPushButton;
class QLabel;
class TimeLine;

class CalendarPage : public QWidget, public Ui::CalendarPage
{
    Q_OBJECT

public:
    CalendarPage(QWidget *parent = 0);
    ~CalendarPage();
    void QuerySearchData(int type);
    bool UpdateDates(int type);
    void ResetSearch();
    void UpdateSelectTime();
    void KeyPressEvent(int key);

public slots:
    void onChangeFocus(int status);
    void onUpdateCalendar();

signals:
    void previousSearch (int type);
    void closeSearch    (int type);
    void startPlayback  ();

private slots:
    void onStartPlayback();
    void onUpdateTimeLine();
    void onButtonPrevMonth();
    void onButtonNextMonth();
    void onButtonPrevious();
    void onButtonClose();
    void onTimerUpdate();

private:
    void CreateNavigationWidget();
    void CreateCalendar();
    void ChangeCalendarSelectDay(int dir);
    void UpdateMonthLabel();
    int  curMonthIndex;
    int  focusStatus;
    int  iconSize;
    int  prevYear, prevMonth;

    QLabel          *lableDate;
    CalendarWidget  *calendar;
    TimeLine        *timeLine;
    QPushButton     *buttonPrevMonth,
                    *buttonNextMonth,
                    *buttonPrevious,
                    *buttonClose;
    QTimer *updateTimer;
    bool isUpdate;
};

#endif // CALENDARPAGE_H
