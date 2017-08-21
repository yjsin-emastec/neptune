#ifndef EVENTRECVTHREAD_H
#define EVENTRECVTHREAD_H

#include <QThread>
#include <QPoint>
#include <Event.h>
#include <EasternEvent.h>

class EventRecvThread : public QThread
{
    Q_OBJECT

public:
    EventRecvThread();
    void stop();
    void clearEventQueue();
	void resetQueueRun(Event *e);

signals:
    void eventReady(Event *e);
	void timerReady();

protected:
    void run();
    void checkClockTimeOut();

private:
    volatile bool stopped;
   	time_t timeDvr;
	bool queueRun;

	int mCount;
	QPoint mCurPt;
	QPoint mPrePt;
};

#endif // EVENTRECVTHREAD_H
