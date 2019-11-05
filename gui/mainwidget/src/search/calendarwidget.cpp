#include <QtGui>
#include "calendarwidget.h"
#include "../main/mainglobal.h"
#include "Event.h"

CalendarWidget::CalendarWidget(QWidget *parent)
        : QWidget(parent)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::AlternateBase);
    setFocusPolicy(Qt::WheelFocus);

    m_selectedDate   = QDate();
    m_firstDayOfWeek = Qt::Sunday;
    m_monthStartAt   = m_monthEndAt = 0;
    m_headHeight     = m_cellHeight = m_cellWidth = pageIndex = 0;

    if(mainHeight == 720)
    {
        fontSize = 48;
    }
    else
    {
        fontSize = 60;
    }
}
void CalendarWidget::SetCurrentPageIndex(int idx, int dir)
{
    if(idx < 0 || idx >= MAX_CAL_MONTH_DATA)
    {
        return;
    }

    pageIndex = idx;
    int maxDay = 0, cnt = 0;
    maxDay = appmgr_get_days_of_month(calendarData[idx].year, calendarData[idx].month);

    QDate date(calendarData[idx].year, calendarData[idx].month, 0);
    qDebug(" cal year %d, month %d", calendarData[idx].year, calendarData[idx].month);

    for(int i=1; i<maxDay+1; i++)
    {
        if(calendarData[idx].data[i])
        {
            date.setDate(calendarData[idx].year, calendarData[idx].month, i);
            qDebug("sel Day %d", i);
            cnt++;
        }
    }

    if(cnt == 0)
    {
        date.setDate(calendarData[idx].year, calendarData[idx].month, 1);
    }

    m_selectedDate = date;
    FindData(date);
    qDebug("cal select day = %d", m_selectedDate.day());
    computeMonthBoundaries();

    if(dir == 2)
    {
        selectedPos = (m_monthStartAt-1)+m_selectedDate.day()-1;
    }

    moveFocus(selectedPos);
}
bool CalendarWidget::isRecordDate(int day)
{
    return calendarData[pageIndex].data[day] ? true : false;
}
void CalendarWidget::SetSelectedDate(const QDate &date)
{
    if(date != m_selectedDate)
    {
        time_t now=0;
        struct tm tmNow;

        m_selectedDate = date;
        computeMonthBoundaries();

        memset(timeLog, 0, sizeof(struct _time_search_info_ext)*25);

        tmNow.tm_year = date.year()-1900;
        tmNow.tm_mon  = date.month()-1;
        tmNow.tm_mday = date.day();
        tmNow.tm_hour = 0;
        tmNow.tm_min  = 0;
        tmNow.tm_sec  = 0;
        now = mktime(&tmNow);

        appmgr_search_get_log(SEARCH_REC_TIME, QUEUE_QT_CORE, now, DLS_OFF, 0);
    }
}
QDate CalendarWidget::selectedDate() const
{
    return m_selectedDate;
}
int CalendarWidget::getSelectedPos()
{
    return selectedPos;
}
Qt::DayOfWeek CalendarWidget::firstDayOfWeek() const
{
    return m_firstDayOfWeek;
}
void CalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(palette().color(QPalette::Active, QPalette::Dark));

    m_headHeight = height()/8;
    m_cellHeight = (height() - m_headHeight) / 6;
    m_cellWidth = width() / 7;

    for(int y = 0; y < 7; ++y)
    {
        int weekday = y + m_firstDayOfWeek;

        if(weekday > 7)
        {
             weekday -= 7;
        }

        QRect rect((m_cellWidth * y), 0, y != 6 ? m_cellWidth : width() - (m_cellWidth * y) - 1, m_headHeight);
        drawHeaderCell(&painter, rect, weekday);

        for(int x = 0; x < 6; ++x)
        {
            QRect rect((m_cellWidth * y), m_headHeight + (m_cellHeight * x), y != 6 ? m_cellWidth : width() - (m_cellWidth * y) - 1, x != 5 ? m_cellHeight : height() - (m_headHeight + (m_cellHeight * x)) - 1);

            int offset = ((x * 7) + y) + 1;

            if((offset >= m_monthStartAt) && (offset <= m_monthEndAt))
            {
                int day = offset - m_monthStartAt + 1;
                drawItemCell(&painter, rect, weekday, day);
            }
            else
            {
                drawEmptyCell(&painter, rect);
            }
        }
    }

    drawFocus(&painter);

    qDebug("...........cal paintevent");
}
void CalendarWidget::drawFocus(QPainter *painter)
{
    QRect border;
    QRect rect((selectedPos%7)*m_cellWidth, m_headHeight+(selectedPos/7)*m_cellHeight, m_cellWidth, m_cellHeight);
    QColor focusColor;
    int borderWidth = 6;

    if( focusStatus == 1)   { focusColor.setRgb(255,0,0); }
    else                    { focusColor.setRgb(255,128,64); }

    border.setRect(rect.x(), rect.y(), rect.width(), borderWidth);
    painter->fillRect(border, focusColor);

    border.setRect(rect.x(), rect.y(), borderWidth, rect.height());
    painter->fillRect(border, focusColor);

    border.setRect(rect.x() + rect.width() - borderWidth, rect.y(), borderWidth, rect.height());
    painter->fillRect(border, focusColor);

    border.setRect(rect.x(), rect.y() + rect.height() - borderWidth, rect.width(), borderWidth);
    painter->fillRect(border, focusColor);
}
void CalendarWidget::drawHeaderCell(QPainter *painter, const QRect &rect, int weekday)
{
    QString dayName;
    painter->save();

    painter->drawRect(rect);

	QFont f = painter->font();
    f.setPointSize(fontSize);
	painter->setFont(f);

    switch (weekday)
    {
        case Qt::Sunday:     dayName = tr("Sun");  break;
        case Qt::Monday:     dayName = tr("Mon");  break;
        case Qt::Tuesday:    dayName = tr("Tue");  break;
        case Qt::Wednesday:  dayName = tr("Wed");  break;
        case Qt::Thursday:   dayName = tr("Thu");  break;
        case Qt::Friday:     dayName = tr("Fri");  break;
        case Qt::Saturday:   dayName = tr("Sat");  break;
    }

    switch(weekday)
    {
        case Qt::Saturday:    painter->setPen(QColor(Qt::blue));                                   break;
        case Qt::Sunday:      painter->setPen(QColor(Qt::red));                                    break;
        default:              painter->setPen(palette().color(QPalette::Active, QPalette::Text));  break;
    }

    painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, dayName);

    painter->restore();
}
void CalendarWidget::drawEmptyCell(QPainter *painter, const QRect &rect)
{
    painter->drawRect(rect);
}
void CalendarWidget::drawItemCell(QPainter *painter, const QRect &rect, int weekday, int day)
{
    painter->save();

	QFont f = painter->font();
    f.setPointSize(fontSize);
	painter->setFont(f);

    if(isRecordDate(day))
    {
        painter->setPen(palette().color(QPalette::Active, QPalette::Dark));
        painter->setBrush(QColor(71, 86, 222));
        painter->drawRect(rect);

        painter->setPen(palette().color(hasFocus() ? QPalette::Active : QPalette::Inactive, QPalette::HighlightedText));
        painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, QString("%1").arg(day));
    }
    else
    {
        painter->setPen(palette().color(QPalette::Active, QPalette::Dark));
        painter->setBrush(palette().brush(QPalette::Base));

        painter->drawRect(rect);
        painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, QString("%1").arg(day));
    }

    painter->restore();
}
void CalendarWidget::computeMonthBoundaries()
{
    int dayOfWeek = QDate(m_selectedDate.year(), m_selectedDate.month(), 1).dayOfWeek();

    if(dayOfWeek < m_firstDayOfWeek)
    {
        m_monthStartAt = dayOfWeek + (8 - m_firstDayOfWeek);
    }
    else if(dayOfWeek > m_firstDayOfWeek)
    {
        m_monthStartAt = dayOfWeek + (m_firstDayOfWeek - 1);
    }
    else
    {
        m_monthStartAt = 1;
    }

    m_monthEndAt = m_monthStartAt + m_selectedDate.daysInMonth() - 1;
}
QDate CalendarWidget::FindDate(int pos) const
{
    int day = (pos+1) - (m_monthStartAt-1);

    return QDate(m_selectedDate.year(), m_selectedDate.month(), day);
}
bool CalendarWidget::isDate(QPoint pos) const
{
    QRect rect(0, m_headHeight + 1, width(), height());
    return rect.contains(pos);
}
void CalendarWidget::FindData(QDate date)
{
	time_t now = 0;
	struct tm tmNow;

	memset(timeLog, 0, sizeof(struct _time_search_info_ext) * 25);

	tmNow.tm_year = date.year()-1900;
	tmNow.tm_mon  = date.month()-1;
	tmNow.tm_mday = date.day();
	tmNow.tm_hour = 0;
	tmNow.tm_min  = 0;
	tmNow.tm_sec  = 0;

	now = mktime(&tmNow);

	appmgr_search_get_log(SEARCH_REC_TIME, QUEUE_QT_CORE, now, DLS_OFF, 0);
}
void CalendarWidget::mousePressEvent(QMouseEvent *event)
{
    if(isDate(event->pos()))
    {
        int clickPos = event->pos().x()/m_cellWidth + ((event->pos().y()-m_headHeight)/m_cellHeight)*7;

        moveFocus(clickPos);
        focusStatus = 1;
        emit changeFocus(focusStatus);
    }
}
void CalendarWidget::moveFocus(int pos)
{
    selectedPos = pos;
    QDate date = FindDate(pos);

    if( date.isValid())
    {
        SetSelectedDate(date);
        emit drawTimeLine(true);
    }
    else
    {
        emit drawTimeLine(false);
    }

    update();
}
void CalendarWidget::initFocus()
{
    selectedPos = (m_monthStartAt-1) + m_selectedDate.day() - 1;
    update();
}
void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );

    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
void CalendarWidget::StartPlayback(void)
{
#if 1 //yjsin [19/06/14] 4->8ch test
    int hour, kk, sec = 0, ch = 0xf, split = Split_4;
#else
    int hour, kk, sec = 0, ch = 0xf, split = Split_9;
#endif
    struct tm tmNow;
    bool bVideoExist = false;
    time_t now = 0;

    int day= (selectedPos+1) - (m_monthStartAt-1);
    QDate date = QDate( m_selectedDate.year(), m_selectedDate.month(), day);

    if(isRecordDate(date.day()))
    {
        delay(500); // 500ms

        SelectPbSplit = split;
        for(hour = 0; hour < 25; hour++)
        {
            for(kk = 0; kk < 240; kk++)
            {
                if(timeLog[hour].channel[kk] & (0xffff))
                {
                    bVideoExist = true;
                    break;
                }
            }

            if(bVideoExist)
            {
                break; }
        }

        if(bVideoExist)
        {
            tmNow.tm_year = date.year()-1900;
            tmNow.tm_mon  = date.month()-1;
            tmNow.tm_mday = date.day();
            tmNow.tm_hour = hour;
            tmNow.tm_min  = kk/4;
            tmNow.tm_sec  = (kk%4) * 15;

            now = mktime(&tmNow);
        }
        else
        {
            now = 0;
        }

        qDebug("%s: now: %s \n", __func__, atime(now));

        if(now > 0)
        {
            EventSearchPB = 0;
            appmgr_search_play_start(ch, split*split, now, 0);
            emit startPlayback();
        }
    }
}
void CalendarWidget::onStartPlayback(QTime startTime)
{
#if 1 //yjsin [19/06/14] 4->8ch test
    int hour, kk, sec = 0, ch = 0xf, split = Split_4;
#else
    int hour, kk, sec = 0, ch = 0xf, split = Split_9;
#endif
    struct tm tmNow;
    bool bVideoExist = false;
    time_t now = 0;

    int day= (selectedPos+1) - (m_monthStartAt-1);
    QDate date = QDate( m_selectedDate.year(), m_selectedDate.month(), day);

    if(isRecordDate(date.day()))
    {
        delay(500); // 500ms

        SelectPbSplit = split;

        for(hour = startTime.hour(); hour < 25; hour++)
        {
            if( hour == startTime.hour() )
            {
                for( kk= startTime.minute()*4; kk <240; kk++)
                {
                    if( timeLog[hour].channel[kk] & (0xffff))
                    {
                        bVideoExist=true;
                        break;
                    }
                }
            }
            else
            {
                for(kk = 0; kk < 240; kk++)
                {
                    if(timeLog[hour].channel[kk] & (0xffff))
                    {
                        bVideoExist = true;
                        break;
                    }
                }
            }

            if(bVideoExist)
            {
                break;
            }
        }

        if(bVideoExist)
        {
            tmNow.tm_year = date.year()-1900;
            tmNow.tm_mon  = date.month()-1;
            tmNow.tm_mday = date.day();
            tmNow.tm_hour = hour;
            tmNow.tm_min  = kk/4;
            tmNow.tm_sec  = (kk%4) * 15;

            now = mktime(&tmNow);
        }
        else
        {
            now = 0;
        }

        qDebug("%s: now: %s \n", __func__, atime(now));

        if(now > 0)
        {
            EventSearchPB = 0;
            appmgr_search_play_start(ch, split*split, now, 0);
            emit startPlayback();
        }
    }
}

void CalendarWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    int hour, kk, sec = 0;

#if 1
    int ch = 0xf, split = Split_4;
#else
    int ch = 0xf, split = Split_9;
#endif
    struct tm tmNow;
    bool bVideoExist = false;
    time_t now = 0;
    if(event->button() == Qt::LeftButton)
    {
        if(isDate(event->pos()))
        {
            int clickPos = event->pos().x()/m_cellWidth + ((event->pos().y()-m_headHeight)/m_cellHeight)*7;
            QDate date = FindDate(clickPos);
            //qDebug("= %s %d ==> y=%d m=%d d=%d isRecordDate=%d\n", __func__, __LINE__, date.year(), date.month(), date.day(), isRecordDate(date.day()));

            if(isRecordDate(date.day()))
            {
                delay(500); // 500ms

                SelectPbSplit = split;

                for(hour = 0; hour < 25; hour++)
                {
                    for(kk = 0; kk < 240; kk++)
                    {
                        if(timeLog[hour].channel[kk] & (0xffff))
                        {
                            bVideoExist = true;
                            break;
                        }
                    }

                    if(bVideoExist)
                    {
                        break; }
                }

                if(bVideoExist)
                {
                    tmNow.tm_year = date.year()-1900;
                    tmNow.tm_mon  = date.month()-1;
                    tmNow.tm_mday = date.day();
                    tmNow.tm_hour = hour;
                    tmNow.tm_min  = kk/4;
                    tmNow.tm_sec  = (kk%4) * 15;

                    now = mktime(&tmNow);
                }
                else
                {
                    now = 0;
                }

                qDebug("%s: now: %s \n", __func__, atime(now));

                if(now > 0)
                {
                    EventSearchPB = 0;
                    appmgr_search_play_start(ch, split*split, now, 0);
                    emit startPlayback();
                }
            }
        }
    }
}

void CalendarWidget::setFocusStatus(int status)
{
    focusStatus = status;

    update();
}
void CalendarWidget::timerUpdate()
{
    FindData(m_selectedDate);
    update();
}
