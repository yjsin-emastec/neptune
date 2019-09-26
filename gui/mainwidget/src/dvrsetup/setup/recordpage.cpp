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

        labelNormalText = ui720.labelNormalText;
        labelEventText  = ui720.labelEventText;
        labelCloseText  = ui720.labelCloseText;

        labelNormalText->setStyleSheet("font: 40px;");
        labelEventText ->setStyleSheet("font: 40px;");
        labelCloseText ->setStyleSheet("font: 40px");
    }
    else
    {
        Ui::RecordPage1080p ui1080;
        ui1080.setupUi(this);

        buttonNormal    = ui1080.buttonNormal;
        buttonEvent     = ui1080.buttonEvent;
        buttonClose     = ui1080.buttonClose;

        labelNormalText = ui1080.labelNormalText;
        labelEventText  = ui1080.labelEventText;
        labelCloseText  = ui1080.labelCloseText;

        labelNormalText->setStyleSheet("font: 65px;");
        labelEventText ->setStyleSheet("font: 65px;");
        labelCloseText ->setStyleSheet("font: 65px;");
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    normalDialog = NULL;
    eventDialog  = NULL;

    iconImageNormal[0].load(":images/dvrsetup/record/normal.png");
    iconImageNormal[1].load(":images/dvrsetup/record/event.png");
    iconImageNormal[2].load(":images/dvrsetup/system/close.png");
    iconImageFocus[0].load(":images/dvrsetup/record/normal2.png");
    iconImageFocus[1].load(":images/dvrsetup/record/event2.png");
    iconImageFocus[2].load(":images/dvrsetup/system/close2.png");

    buttonNormal->setPixmap(iconImageNormal[0]);
    buttonEvent->setPixmap(iconImageNormal[1]);
    buttonClose->setPixmap(iconImageNormal[2]);

    buttonNormal->setScaledContents(true);
    buttonEvent->setScaledContents(true);
    buttonClose->setScaledContents(true);

    connect(buttonNormal, SIGNAL(pressed()), this, SLOT(onButtonNormal()));
    connect(buttonEvent,  SIGNAL(pressed()), this, SLOT(onButtonEvent()));
    connect(buttonClose,  SIGNAL(pressed()), this, SLOT(onButtonClose()));
    connect(buttonNormal, SIGNAL(focusIn()), this, SLOT(setFocusNormal()));
    connect(buttonEvent,  SIGNAL(focusIn()), this, SLOT(setFocusEvent()));
    connect(buttonClose,  SIGNAL(focusIn()), this, SLOT(setFocusClose()));
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
void RecordPage::setFocusTabLayout()    { changeFocus(0); }
void RecordPage::setFocusNormal()       { changeFocus(1); }
void RecordPage::setFocusEvent()        { changeFocus(2); }
void RecordPage::setFocusClose()        { changeFocus(3); }
void RecordPage::changeFocus(int n)
{
    buttonNormal->setPixmap(iconImageNormal[0]);
    buttonEvent->setPixmap(iconImageNormal[1]);
    buttonClose->setPixmap(iconImageNormal[2]);

    buttonNormal->setFocusState(false);
    buttonEvent->setFocusState(false);
    buttonClose->setFocusState(false);

    switch(n)
    {
        case 0 :
            break;

        case 1 :
            buttonNormal->setPixmap(iconImageFocus[0]);
            buttonNormal->setFocusState(true);
            break;

        case 2 :
            buttonEvent->setPixmap(iconImageFocus[1]);
            buttonEvent->setFocusState(true);
            break;

        case 3 :
            buttonClose->setPixmap(iconImageFocus[2]);
            buttonClose->setFocusState(true);
            break;

        default :
            buttonNormal->setPixmap(iconImageFocus[0]);
            buttonNormal->setFocusState(true);
            break;
    }
}
