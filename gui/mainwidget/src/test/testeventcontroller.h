#ifndef TESTEVENTCONTROLLER_H
#define TESTEVENTCONTROLLER_H

#include <QObject>
#include "Event.h"

class TestEventController : public QObject
{
    Q_OBJECT

public:
    TestEventController           (void);
    ~TestEventController          (void);

signals:
    void diskFormatProgress       (int disk, unsigned long total, unsigned long percent, unsigned long remain_time);
    void diskFormatEnd            (void);
    void sendKey                  (int value);

protected slots:
    void handleEvent              (Event *e);

private:
    void sendKeycode              (Event *e);
    void eventDiskFormatEnd       (Event *e);
    void eventDiskFormatProcess   (Event *e);
    void call                     (Event *e);
};

#endif // TESTEVENTCONTROLLER_H
