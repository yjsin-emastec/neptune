#include <QtCore>
#include <glib.h>
#include "Event.h"
#include "EasternEvent.h"
#include "eventrecvthread.h"
#include <QCursor>
#include "hwcursor.h"

GAsyncQueue *_q_main;

extern QScreenCursor *qt_screencursor;

EventRecvThread::EventRecvThread()
{
    qDebug("%s start !!!!!\n", __func__);

    stopped  = false;
    queueRun = true;
    timeDvr  = 0;
    mCount   = 0;
    mPrePt   = QCursor::pos();
    _q_main  = g_async_queue_new();

    event_queue_register(QUEUE_QT_CORE, _q_main);
}
void EventRecvThread::checkClockTimeOut()
{
    time_t now = time(0);

    if(timeDvr == 0)
    {
        timeDvr = now;
    }
    else
    {
        if(timeDvr != now)
        {
            timeDvr = now;
            emit timerReady();
        }
    }
}
void EventRecvThread::resetQueueRun(Event *e)
{
    if(e->free_func)
    {
        (*e->free_func)(e->data);
    }

    g_slice_free(Event, e);

    queueRun = true;
}
void EventRecvThread::run()
{
    while(!stopped)
    {
        Event *e = NULL;

        checkClockTimeOut();

        mCurPt = QCursor::pos();

        if(qt_screencursor->isVisible())
        {
            if(mCount > 500)
            {
                qt_screencursor->move(-30, -30);
                qt_screencursor->hide();
                mCount = 0;
            }
            else
            {
                mCount++;
            }
        }
        else
        {
            if(mPrePt != mCurPt)
            {
                qt_screencursor->show();
            }
            mCount = 0;
        }

        mPrePt = mCurPt;

        e = (Event *)g_async_queue_try_pop(_q_main);

        if(!e)
        {
            usleep(10000);
            continue;
        }

        if(GPOINTER_TO_INT(e->data) == -1)
        {
            g_slice_free(Event, e);
            continue;
        }

        queueRun = false;

        emit eventReady(e);
    }
}
void EventRecvThread::stop()
{
    stopped = true;
}
void EventRecvThread::clearEventQueue()
{
    Event *e;

    e = g_slice_new(Event);
    e->data = GINT_TO_POINTER(-1);
    g_async_queue_push(_q_main, e);

    while(g_async_queue_length(_q_main))
    {
        e = (Event *)g_async_queue_pop(_q_main);

        if(!e)
        {
            continue;
        }

        if(GPOINTER_TO_INT(e->data) == -1)
        {
            continue;
        }

        if(e->free_func)
        {
            (*e->free_func)(e->data);
        }

        g_slice_free(Event, e);
    }

    g_async_queue_unref(_q_main);
}
