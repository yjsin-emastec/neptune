#include <QtGui>
#include "recordpage.h"
#include "dvrsetup/record/normal/normaldialog.h"
#include "dvrsetup/record/normal/recordstatus.h"
#include "dvrsetup/record/event/eventdialog.h"
#include "main/mainglobal.h"
#include "appmgr.h"

RecordPage::RecordPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    normalDialog = NULL;
    eventDialog  = NULL;
    recordStatus =NULL;

    connect(buttonNormal, SIGNAL(released()), this, SLOT(onButtonNormal(void)));
    connect(buttonEvent,  SIGNAL(released()), this, SLOT(onButtonEvent(void)));
    connect(buttonClose,  SIGNAL(released()), this, SLOT(onButtonClose(void)));
}
RecordPage::~RecordPage()
{
}
void RecordPage::onButtonNormal(void)
{
    emit escapeTabFocus();

    if(!normalDialog)
    {
        normalDialog = new NormalDialog(this);
    }

    normalDialog->initNormalConfig();
    normalDialog->move((appmgr_get_mainwidget_width()-normalDialog->width())/2,(appmgr_get_mainwidget_height()-normalDialog->height())/2);

    if(normalDialog->exec())    //save
    {
        QTimer::singleShot(0, this, SLOT(onRecordSave()));

        if(!recordStatus)
        {
            recordStatus = new RecordStatus(this);
        }
        recordStatus->updateRecordStatus();
        recordStatus->move((appmgr_get_mainwidget_width()-recordStatus->width())/2,(appmgr_get_mainwidget_height()-recordStatus->height())/2);
        recordStatus->exec();
    }
    else    //reject
    {
        emit saveRecordPage(0);
    }

    if(recordStatus)
    {
        delete recordStatus;
        recordStatus = NULL;
    }

    delete normalDialog;
    normalDialog = NULL;
}
void RecordPage::onButtonEvent(void)
{
    emit escapeTabFocus();

    if(!eventDialog)
    {
        eventDialog = new EventDialog(this);
    }

    eventDialog->initEventConfig();
    eventDialog->move((appmgr_get_mainwidget_width()-eventDialog->width())/2,(appmgr_get_mainwidget_height()-eventDialog->height())/2);

    if(eventDialog->exec())
    {
        emit saveRecordPage(1);
    }
    else
    {
        emit saveRecordPage(0);
    }

    delete eventDialog;
    eventDialog = NULL;
}
void RecordPage::onButtonClose(void)
{
    emit escapeTabFocus();
    emit closeSetupMenu();
}
void RecordPage::onRecordSave(void)
{
    emit saveRecordPage(1);
}
