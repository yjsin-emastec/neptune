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
    connect(calendar, SIGNAL(drawTimeLine(bool)), timeLine, SLOT(onDrawTimeLine(bool)));

    buttonPrevious = new QPushButton();
    buttonPrevious->setText(tr("Previous"));
    //buttonPrevious->setMaximumWidth(200);
    buttonPrevious->setFixedSize(200,76);

    buttonClose = new QPushButton();
    buttonClose->setText(tr("Close"));
    //buttonClose->setMaximumWidth(200);
    buttonClose->setFixedSize(200,76);

#if 1 //yjsin [18/01/05] if text is long, change font size
    if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        buttonPrevious->setStyleSheet("font:40px;color:white");
        buttonClose->setStyleSheet("font:38px;color:white");
    }
#endif

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
    emit closeSearch(0);
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

    calendar->SetCurrentPageIndex(curMonthIndex, 2);
    calendar->initFocus();

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
    calendar->setFocus();

    if(calDataCount == 0)
    {
        return;
    }

    int pos = calendar->getSelectedPos();

    if(dir == 1)        //up
    {
        if(pos >= 7)    { pos = pos-7;  }
        else            { pos = pos+35; }
    }
    else if(dir == 2)   //down
    {
        if(pos > 34)    { pos = pos-35; }
        else            { pos = pos+7;  }
    }
    else if(dir == 3)   //left
    {
        if(pos%7 == 0)  { pos = pos+6;  }
        else            { pos = pos-1;  }
    }
    else if(dir == 4 )  //right
    {
        if(pos%7 == 6)  { pos = pos-6;  }
        else            { pos = pos+1;  }
    }

    calendar->moveFocus(pos);
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
