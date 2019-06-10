#include <QtGui>
#include "recordpage.h"
#include "dvrsetup/record/normal/normaldialog.h"
#include "dvrsetup/record/event/eventdialog.h"
#include "main/mainglobal.h"
#include "appmgr.h"

RecordPage::RecordPage(QWidget *parent)
    : QWidget(parent)
{
    if(mainHeight == 720)
    {
        Ui::RecordPage ui720;
        ui720.setupUi(this);

        buttonNormal    = ui720.buttonNormal;
        buttonEvent     = ui720.buttonEvent;
        buttonClose     = ui720.buttonClose;
    }
    else
    {
        Ui::RecordPage1080p ui1080;
        ui1080.setupUi(this);

        buttonNormal    = ui1080.buttonNormal;
        buttonEvent     = ui1080.buttonEvent;
        buttonClose     = ui1080.buttonClose;
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    normalDialog = NULL;
    eventDialog  = NULL;

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
    }
    else    //reject
    {
        emit saveRecordPage(0);
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
        emit saveRecordPage(2);
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
