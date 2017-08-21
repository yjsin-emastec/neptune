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
}
void CalendarWidget::SetCurrentPageIndex(int idx, int dir)
{
    int maxDay = 0, cnt = 0;
    time_t now = 0;
    struct tm tmNow;

    if(idx < 0 || idx >= MAX_CAL_MONTH_DATA)
    {
        return;
    }

    maxDay = appmgr_get_days_of_month(calendarData[idx].year, calendarData[idx].month);

    pageIndex = idx;

    QDate date(calendarData[idx].year, calendarData[idx].month, 0);

    qDebug(" cal year %d, month %d", calendarData[idx].year, calendarData[idx].month);

    if(dir)
    {
        for(int i = 1; i < maxDay+1; i++)
        {
            if(calendarData[idx].data[i])
            {
                date.setDate(calendarData[idx].year, calendarData[idx].month, i);
                qDebug("1 sel Day %d", i);
                break;
            }
        }
    }
    else
    {
        for(int i = 1; i < maxDay+1; i++)
        {
            if(calendarData[idx].data[i])
            {
                date.setDate(calendarData[idx].year, calendarData[idx].month, i);
                qDebug("2 sel Day %d", i);
                cnt++;
            }
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

    if(isRecordDate(m_selectedDate.day()))
    {
        memset(timeLog, 0, sizeof(struct _time_search_info_ext) * 25);

        tmNow.tm_year = date.year()-1900;
        tmNow.tm_mon  = date.month()-1;
        tmNow.tm_mday = m_selectedDate.day();
        tmNow.tm_hour = 0;
        tmNow.tm_min  = 0;
        tmNow.tm_sec  = 0;

        now = mktime(&tmNow);

        appmgr_search_get_log(SEARCH_REC_TIME, QUEUE_QT_CORE, now, DLS_OFF, 0);
    }

    update();
}
bool CalendarWidget::isRecordDate(int day)
{
    return calendarData[pageIndex].data[day] ? true : false;
}
void CalendarWidget::SetSelectedDate(const QDate &date)
{
    if(date.isValid() && isRecordDate(date.day()))
    {
        if(date != m_selectedDate)
        {
            m_selectedDate = date;
            computeMonthBoundaries();
            update();

            emit selectedDateChanged(date);
        }
    }
}
QDate CalendarWidget::selectedDate() const
{
    return m_selectedDate;
}
Qt::DayOfWeek CalendarWidget::firstDayOfWeek() const
{
    return m_firstDayOfWeek;
}
void CalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(palette().color(QPalette::Active, QPalette::Dark));

    m_headHeight = 60;
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

    qDebug("...........cal paintevent");
}
void CalendarWidget::drawHeaderCell(QPainter *painter, const QRect &rect, int weekday)
{
    QString dayName;
    painter->save();

    painter->drawRect(rect);

	QFont f = painter->font();
	f.setPointSize(48);
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
	QRect border;
    painter->save();

	QFont f = painter->font();
	f.setPointSize(48);
	painter->setFont(f);

    if(day == m_selectedDate.day())
    {
        if(isRecordDate(day))
        {
            painter->setPen(palette().color(QPalette::Active, QPalette::Dark));
            painter->setBrush(palette().brush(hasFocus() ? QPalette::Active : QPalette::Inactive, QPalette::Highlight));
			painter->setBrush(QColor(71, 86, 222));
			painter->drawRect(rect);

            painter->setPen(palette().color(hasFocus() ? QPalette::Active : QPalette::Inactive, QPalette::HighlightedText));
            painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, QString("%1").arg(day));
			
			border.setRect(rect.x(), rect.y(), rect.width(), 4);
			painter->fillRect(border, QColor(255, 128, 64));

			border.setRect(rect.x(), rect.y(), 4, rect.height());
			painter->fillRect(border, QColor(255, 128, 64));

			border.setRect(rect.x() + rect.width() - 4, rect.y(), 4, rect.height());
			painter->fillRect(border, QColor(255, 128, 64));

			border.setRect(rect.x(), rect.y() + rect.height() - 4, rect.width(), 4);
			painter->fillRect(border, QColor(255, 128, 64));
        }
        else
        {
            painter->setPen(palette().color(QPalette::Active, QPalette::Dark));
            painter->setBrush(palette().brush(QPalette::Base));
            painter->drawRect(rect);
            painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, QString("%1").arg(day));
        }
    }
    else
    {
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
QDate CalendarWidget::FindDate(QPoint pos) const
{
    if(!isDate(pos))
    {
        return QDate();
    }

    int columnID  = pos.x() / m_cellWidth;
    int rowID     = (pos.y() - m_headHeight) / m_cellHeight;
    int offset    = ((rowID * 7) + columnID) + 1;
    int day       = offset - m_monthStartAt + 1;

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

	playDate = date;
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
	time_t now = 0;
	struct tm tmNow;

    if(isDate(event->pos()))
    {
        QDate date = FindDate(event->pos());
        SetSelectedDate(date);

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
    int hour, kk, sec = 0, ch = 0xf, split = Split_4;
    struct tm tmNow;
    bool bVideoExist = false;
    time_t now = 0;
    QDate date = playDate;

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
void CalendarWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    int hour, kk, sec = 0;
    int ch = 0xf, split = Split_4;
    struct tm tmNow;
    bool bVideoExist = false;
    time_t now = 0;
    if(event->button() == Qt::LeftButton)
    {
        if(isDate(event->pos()))
        {
            QDate date = FindDate(event->pos());
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
