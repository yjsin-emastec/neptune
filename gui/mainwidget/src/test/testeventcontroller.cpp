#include <map>
#include <testmgr.h>
#include "testeventcontroller.h"

typedef void (TestEventController::*CtrlFunc)(Event *);

TestEventController::TestEventController()
{
}
TestEventController::~TestEventController()
{
}
void TestEventController::handleEvent(Event *e)
{
    this->call(e);

    if(e->free_func)
    {
        (*e->free_func)(e->data);
    }

    g_slice_free(Event, e);
}
void TestEventController::sendKeycode(Event *e)
{
    int keyCode = GPOINTER_TO_INT(e->data);

    qDebug("%s: keycode [%x]\n", __func__, keyCode);

    emit sendKey(keyCode);
}
void TestEventController::eventDiskFormatEnd(Event *e)
{
    int Message = GPOINTER_TO_INT(e->data);

    if(Message == DISK_FORMAT_END)
    {
        qDebug("receive DISK_FORMAT_END message\n");
        emit diskFormatEnd();
    }
}
void TestEventController::eventDiskFormatProcess(Event *e)
{
    DiskFormat_t *item = (DiskFormat_t *)e->data;

    qDebug("receive Send_QT_DISK_FORMAT_PROCESS message");
    emit diskFormatProgress(item->disk, item->total_file_count, item->percent, item->remain_time);
}
void TestEventController::call(Event *e)
{
    static std::map<int, CtrlFunc> sFuncTable;
    static bool sFuncTableInitialized = false;
    CtrlFunc func = NULL;

#ifdef __MAP
#undef __MAP
#endif

#define __MAP(id, func) sFuncTable[id] = &TestEventController::func

    if(!sFuncTableInitialized)
    {
        __MAP(Send_QT_KEYPAD,              sendKeycode);
        __MAP(Send_QT_DISK_FORMAT_PROCESS, eventDiskFormatProcess);
        __MAP(Send_QT_DISK,                eventDiskFormatEnd);
        sFuncTableInitialized = true;
    }

#undef __MAP

    func = sFuncTable[e->event];

    if(func)
    {
        (this->*func)(e);
    }
}
