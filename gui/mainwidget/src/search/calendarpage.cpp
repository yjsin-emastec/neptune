#include <QtGui>
#include "calendarpage.h"
#include "calendarwidget.h"
#include "timeline.h"
#include "../main/mainglobal.h"
#include <Event.h>
#include <EasternEvent.h>

CalendarPage::CalendarPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    ResetSearch();

    CreateNavigationWidget();
    CreateCalendar();

    timeLine = new TimeLine(this);

    buttonPrevious = new QPushButton();
    buttonPrevious->setText(tr("Previous"));
    buttonPrevious->setMaximumWidth(200);

    buttonClose = new QPushButton();
    buttonClose->setText(tr("Close"));
    buttonClose->setMaximumWidth(200);

    connect(buttonPrevious, SIGNAL(released()), this, SLOT(onButtonPrevious()));
    connect(buttonClose, SIGNAL(released()), this, SLOT(onButtonClose()));

    QHBoxLayout	*buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonPrevMonth);
    buttonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLayout->addWidget(lableDate);
    buttonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLayout->addWidget(buttonNextMonth);

    QVBoxLayout *buttonLayout2 = new QVBoxLayout;
    buttonLayout2->addWidget(buttonPrevious);
    buttonLayout2->addWidget(buttonClose);

    QHBoxLayout *timeLineLayout = new QHBoxLayout;
    timeLineLayout->addWidget(timeLine);
    timeLineLayout->addLayout(buttonLayout2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(calendar);
    mainLayout->addLayout(timeLineLayout);

    setLayout(mainLayout);

    curMonthIndex = 0;

    UpdateDates(-1);

    QTimer::singleShot(100, this, SLOT(onUpdateTimeLine()));
}
CalendarPage::~CalendarPage()
{
}
void CalendarPage::onUpdateTimeLine()
{
    timeLine->updateTimeLine();
}
void CalendarPage::onButtonPrevious()
{
    emit previousSearch(0);
}
void CalendarPage::onButtonClose()
{
    emit closeSearch();
}
void CalendarPage::onStartPlayback()
{
    emit startPlayback();
}
void CalendarPage::ResetSearch()
{
    memset(calendarData, 0, sizeof(struct _caldata) * MAX_CAL_MONTH_DATA);
    calDataCount = 0;
}
void CalendarPage::CreateNavigationWidget()
{
    buttonPrevMonth = new QPushButton;
    buttonPrevMonth->setText("<<");
    buttonPrevMonth->setMinimumWidth(100);
    buttonPrevMonth->setMinimumHeight(60);

    buttonNextMonth = new QPushButton;
    buttonNextMonth->setText(">>");
    buttonNextMonth->setMinimumWidth(100);
    buttonNextMonth->setMinimumHeight(60);

    lableDate = new QLabel(tr("Aug, 2016"));
    lableDate->setStyleSheet("color:white; font-weight:bold; font-size:48px;");

    connect(buttonPrevMonth, SIGNAL(clicked()), this, SLOT(onButtonPrevMonth()));
    connect(buttonNextMonth, SIGNAL(clicked()), this, SLOT(onButtonNextMonth()));
}
void CalendarPage::CreateCalendar()
{
    calendar = new CalendarWidget(this);
    connect(calendar, SIGNAL(startPlayback()), this, SLOT(onStartPlayback()));
}
void CalendarPage::QuerySearchData(int type)
{
    int searchDateType = -1;

    searchDateType = SEARCH_REC_TIME;

    if(searchDateType < 0)
    {
        qDebug("Invalid search date type");
        return;
    }

    qDebug("QuerySearchData searchDateType[%d]\n", searchDateType);

    appmgr_search_get_date(searchDateType, QUEUE_QT_CORE);
}
bool CalendarPage::UpdateDates(int type)
{
    bool isExistDate = true;

    if(type < 0)
    {
        return false;
    }

    appmgr_apply_dls_to_calendar_log(calendarData, calDataCount);

    curMonthIndex = calDataCount -1;

    if(curMonthIndex < 0 || ( calendarData[0].year == 0 && calendarData[0].month == 0))
    {
        QDate date = QDate::currentDate();

        calendarData[0].year = date.year();
        calendarData[0].month = date.month();
        curMonthIndex = 0;

        // No Data!!!!!!!!
        isExistDate = false;
    }

    calendar->SetCurrentPageIndex(curMonthIndex, 0);

    if(calDataCount < 2)
    {
        buttonPrevMonth->setEnabled(false);
    }
    else
    {
        buttonPrevMonth->setEnabled(true);
    }

    buttonNextMonth->setEnabled(false);
    UpdateMonthLabel();

    return isExistDate;
}
void CalendarPage::onButtonPrevMonth()
{
    curMonthIndex--;

    if(curMonthIndex < 0)
    {
        curMonthIndex = 0;
    }

    if(curMonthIndex < (calDataCount - 1))
    {
        buttonNextMonth->setEnabled(true);
    }

    if(curMonthIndex <= 0)
    {
        buttonPrevMonth->setEnabled(false);
        //return;
    }

    calendar->SetCurrentPageIndex(curMonthIndex, 0);
    UpdateMonthLabel();
}
void CalendarPage::onButtonNextMonth()
{
    curMonthIndex++;

    if(curMonthIndex > (calDataCount - 1))
    {
        curMonthIndex = calDataCount - 1;
    }

    if(curMonthIndex > 0)
    {
        buttonPrevMonth->setEnabled(true);
    }

    if(curMonthIndex >= (calDataCount - 1))
    {
        buttonNextMonth->setEnabled(false);
    }

    calendar->SetCurrentPageIndex(curMonthIndex, 1);
    UpdateMonthLabel();
}
void CalendarPage::UpdateMonthLabel()
{
    QString str;

    switch (calendarData[curMonthIndex].month) 
    {
        case 1:     str = tr("Jan");    break;
        case 2:     str = tr("Feb");    break;
        case 3:     str = tr("Mar");    break;
        case 4:     str = tr("Apr");    break;
        case 5:     str = tr("May");    break;
        case 6:     str = tr("Jun");    break;
        case 7:     str = tr("Jul");    break;
        case 8:     str = tr("Aug");    break;
        case 9:     str = tr("Sep");    break;
        case 10:    str = tr("Oct");    break;
        case 11:    str = tr("Nov");    break;
        case 12:    str = tr("Dec");    break;
    }

    str = tr("%1, %2").arg(str).arg(calendarData[curMonthIndex].year);
    lableDate->setText(str);
}
void CalendarPage::UpdateSelectTime()
{
    struct tm tmNow;

    QDate date = calendar->selectedDate();

    if(!date.isValid())
    {
        qDebug(" ERROR!!!! invalid date.......!!!!!!!!!!");
        QDate date2 = QDate::currentDate();

        tmNow.tm_year = date2.year()  - 1900;
        tmNow.tm_mon  = date2.month() - 1;
        tmNow.tm_mday = date2.day();
    }
    else
    {
        tmNow.tm_year = date.year()  - 1900;
        tmNow.tm_mon  = date.month() - 1;
        tmNow.tm_mday = date.day();
    }

    tmNow.tm_hour = 0;
    tmNow.tm_min  = 0;
    tmNow.tm_sec  = 0;

    qDebug(" calendar select %d-%d-%d", tmNow.tm_year+1900, tmNow.tm_mon+1, tmNow.tm_mday);
    calSelTime = mktime(&tmNow);
}
void CalendarPage::ChangeCalendarSelectDay(int dir)
{
    bool isFindDay = false;
    int weekday, weekStartDay = 0, weekEndDay = 0, curSelDay;

    if(calDataCount == 0)
    {
        return;
    }

    QDate curDate = calendar->selectedDate();

    if(!curDate.isValid()) // maybe not exist record date.
    {
        ;
    }

    weekday    = curDate.dayOfWeek();
    curSelDay  = curDate.day();

    switch(weekday)
    {
        case Qt::Sunday:    weekStartDay = curSelDay + 0; weekEndDay = curSelDay + 6; break;
        case Qt::Monday:    weekStartDay = curSelDay - 1; weekEndDay = curSelDay + 5; break;
        case Qt::Tuesday:   weekStartDay = curSelDay - 2; weekEndDay = curSelDay + 4; break;
        case Qt::Wednesday: weekStartDay = curSelDay - 3; weekEndDay = curSelDay + 3; break;
        case Qt::Thursday:  weekStartDay = curSelDay - 4; weekEndDay = curSelDay + 2; break;
        case Qt::Friday:    weekStartDay = curSelDay - 5; weekEndDay = curSelDay + 1; break;
        case Qt::Saturday:  weekStartDay = curSelDay - 6; weekEndDay = curSelDay + 0; break;
    }

    if(weekStartDay < 1)
    {
        weekStartDay = 1;
    }

    if(weekEndDay > curDate.daysInMonth())
    {
        weekEndDay = curDate.daysInMonth();
    }

    //qDebug("%s(): weekStartDay[%d], weekEndDay[%d] \n", __func__, weekStartDay, weekEndDay);

    if(dir == 1)
    {
        int wsd = weekStartDay;
        int wed = weekEndDay;
_UpCal:
        wsd = (wsd-7 > 0) ? wsd-7 : 1;
        wed = (wed-7 > 0) ? wed-7 : 1;

        if(((weekEndDay-weekStartDay) < 6) && (weekEndDay == curDate.daysInMonth()))
        {
            wed = wsd + 6;
        }

        for(int checkDay = wsd; checkDay <= wed; checkDay++)
        {
            if(wsd == wed)
            {
                break;
            }

            if(calendarData[curMonthIndex].data[checkDay])
            {
                calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                return;
            }
        }

        if(isFindDay == false && wsd != 1)
        {
            goto _UpCal;
        }

        int lastDay = appmgr_get_days_of_month(calendarData[curMonthIndex].year, calendarData[curMonthIndex].month);

        for(int checkDay = lastDay; checkDay > curSelDay; checkDay--)
        {
            if(calendarData[curMonthIndex].data[checkDay])
            {
                calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                return;
            }
        }
    }
    else if(dir == 2)
    {
        int wsd      = weekStartDay;
        int wed      = weekEndDay;
        int lastDay  = appmgr_get_days_of_month(calendarData[curMonthIndex].year, calendarData[curMonthIndex].month);
_DownCal:
        wsd = (wsd+7 > lastDay) ? lastDay : wsd+7;
        wed = (wed+7 > lastDay) ? lastDay : wed+7;

        if((wed-wsd < 6) && (wed != lastDay))
        {
            wsd = wed - 6;
        }

        for(int checkDay = wed; checkDay >= wsd; checkDay--)
        {
            if(wsd == wed)
            {
                break;
            }

            if(calendarData[curMonthIndex].data[checkDay])
            {
                calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                return;
            }
        }

        if(isFindDay == false && wsd != lastDay)
        {
            goto _DownCal;
        }

        for(int checkDay = 1; checkDay < curSelDay; checkDay++)
        {
            if(calendarData[curMonthIndex].data[checkDay])
            {
                calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                return;
            }
        }
    }
    else if(dir == 3)
    {
        for(int checkDay = curSelDay-1; checkDay >= weekStartDay; checkDay--)
        {
            if(calendarData[curMonthIndex].data[checkDay])
            {
                calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                return;
            }

        }

        if(isFindDay == false)
        {
            for(int checkDay = weekEndDay; checkDay > curSelDay; checkDay--)
            {
                if(calendarData[curMonthIndex].data[checkDay])
                {
                    calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                    calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                    return;
                }
            }
        }
    }
    else if(dir == 4)
    {
        for(int checkDay = curSelDay+1; checkDay <= weekEndDay; checkDay++)
        {
            if(calendarData[curMonthIndex].data[checkDay])
            {
                calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                return;
            }
        }

        if(isFindDay == false)
        {
            for(int checkDay = weekStartDay; checkDay < curSelDay; checkDay++)
            {
                if(calendarData[curMonthIndex].data[checkDay])
                {
                    calendar->SetSelectedDate(QDate(curDate.year(), curDate.month(), checkDay));
                    calendar->FindData(QDate(curDate.year(), curDate.month(), checkDay));
                    return;
                }
            }
        }
    }
}
void CalendarPage::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if(buttonPrevious->hasFocus()  || buttonClose->hasFocus() ||
               buttonPrevMonth->hasFocus() || buttonNextMonth->hasFocus())
            {
                buttonPrevious->clearFocus();
                buttonClose->clearFocus();
                buttonPrevMonth->clearFocus();
                buttonNextMonth->clearFocus();
                calendar->setFocus();
                ChangeCalendarSelectDay(1);
            }
            else
            {
                ChangeCalendarSelectDay(1);
            }

            break;
        }
        case Qt::Key_Down:
        {
            if(buttonPrevious->hasFocus()  || buttonClose->hasFocus() ||
               buttonPrevMonth->hasFocus() || buttonNextMonth->hasFocus())
            {
                buttonPrevious->clearFocus();
                buttonClose->clearFocus();
                buttonPrevMonth->clearFocus();
                buttonNextMonth->clearFocus();
                calendar->setFocus();
                ChangeCalendarSelectDay(2);
            }
            else
            {
                ChangeCalendarSelectDay(2);
            }

            break;
        }
        case Qt::Key_Left:
        {
            if(buttonPrevious->hasFocus()  || buttonClose->hasFocus() ||
               buttonPrevMonth->hasFocus() || buttonNextMonth->hasFocus())
            {
                buttonPrevious->clearFocus();
                buttonClose->clearFocus();
                buttonPrevMonth->clearFocus();
                buttonNextMonth->clearFocus();
                calendar->setFocus();
                ChangeCalendarSelectDay(3);
            }
            else
            {
                ChangeCalendarSelectDay(3);
            }

            break;
        }
        case Qt::Key_Right:
        {
            if(buttonPrevious->hasFocus()  || buttonClose->hasFocus() ||
               buttonPrevMonth->hasFocus() || buttonNextMonth->hasFocus())
            {
                buttonPrevious->clearFocus();
                buttonClose->clearFocus();
                buttonPrevMonth->clearFocus();
                buttonNextMonth->clearFocus();
                calendar->setFocus();
                ChangeCalendarSelectDay(4);
            }
            else
            {
                ChangeCalendarSelectDay(4);
            }

            break;
        }
        case Qt::Key_Enter:
        {
            if(buttonPrevMonth->hasFocus())
            {
                onButtonPrevMonth();

                if(buttonPrevMonth->isEnabled())
                {
                    buttonPrevMonth->setFocus();
                }
                else if(buttonNextMonth->isEnabled())
                {
                    buttonNextMonth->setFocus();
                }
            }
            else if(buttonNextMonth->hasFocus())
            {
                onButtonNextMonth();

                if(buttonNextMonth->isEnabled())
                {
                    buttonNextMonth->setFocus();
                }
                else if(buttonPrevMonth->isEnabled())
                {
                    buttonPrevMonth->setFocus();
                }
            }
            else if(buttonPrevious->hasFocus())
            {
                onButtonPrevious();
            }
            else if(buttonClose->hasFocus())
            {
                onButtonClose();
            }
            else if(!buttonPrevious->hasFocus()  && !buttonClose->hasFocus() &&
                    !buttonPrevMonth->hasFocus() && !buttonNextMonth->hasFocus())
            {
                calendar->StartPlayback();
            }

            break;
        }
        case Qt::Key_Escape:
        {
            onButtonPrevious();

            break;
        }
        case Qt::Key_PageUp:
        {
            if(buttonNextMonth->isEnabled())
            {
                onButtonNextMonth();
                buttonPrevious->clearFocus();
                buttonClose->clearFocus();
                buttonPrevMonth->clearFocus();
                buttonNextMonth->clearFocus();
                calendar->setFocus();
            }

            break;
        }
        case Qt::Key_PageDown:
        {
            if(buttonPrevMonth->isEnabled())
            {
                onButtonPrevMonth();
                buttonPrevious->clearFocus();
                buttonClose->clearFocus();
                buttonPrevMonth->clearFocus();
                buttonNextMonth->clearFocus();
                calendar->setFocus();
            }

            break;
        }
        default:
        {
            return;
        }
    }
    return;
}
