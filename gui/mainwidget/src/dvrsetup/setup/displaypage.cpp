#include "displaypage.h"
#include "textmessagebox/textmessagedialog.h"
#include "../display/cameraname/cameranamedialog.h"
#include "../display/videooutput/videooutputdialog.h"
#include "../display/osd/osddialog.h"
#include "main/mainglobal.h"

DisplayPage::DisplayPage(QWidget *parent)
    : QWidget(parent)
{
    if(mainHeight == 720)
    {
        Ui::DisplayPage ui720;
        ui720.setupUi(this);

        buttonVideoOutput = ui720.buttonVideoOutput;
        buttonCameraName = ui720.buttonCameraName;
        buttonOsd = ui720.buttonOsd;
        buttonClose = ui720.buttonClose;
    }
    else
    {
        Ui::DisplayPage1080p ui1080;
        ui1080.setupUi(this);

        buttonVideoOutput = ui1080.buttonVideoOutput;
        buttonCameraName = ui1080.buttonCameraName;
        buttonOsd = ui1080.buttonOsd;
        buttonClose = ui1080.buttonClose;
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    msgBox             = NULL;
    videoOutputDialog  = NULL;
    cameraNameDialog   = NULL;
    osdDialog          = NULL;

    connect(buttonVideoOutput, SIGNAL(released()), this, SLOT(onButtonVideoOutput()));
    connect(buttonCameraName,  SIGNAL(released()), this, SLOT(onButtonCameraName()));
    connect(buttonOsd,         SIGNAL(released()), this, SLOT(onButtonOsd()));
    connect(buttonClose,       SIGNAL(released()), this, SLOT(onButtonClose()));
}

DisplayPage::~DisplayPage()
{
}
void DisplayPage::onButtonVideoOutput(void)
{
    emit escapeTabFocus();

    if(!videoOutputDialog)
    {
        videoOutputDialog = new VideoOutputDialog(this);
    }

    videoOutputDialog->initVideoOutputConfig();
    videoOutputDialog->move((appmgr_get_mainwidget_width()-videoOutputDialog->size().width())/2,(appmgr_get_mainwidget_height()-videoOutputDialog->size().height())/2);

    if(videoOutputDialog->exec())
    {
        if(videoOutputDialog->oldHdmi != videoOutputDialog->indexHdmi)
        {
            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("RESOLUTION CHANGE"),
                        tr("Are you sure to change the resolution?\n" "If yes, the system will restart."), 0, this);
            }

            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
            msgBoxEsckey = 1;
            if(msgBox->exec()) { emit saveDisplayPage(2); }
            else               { emit saveDisplayPage(0); }
            delete msgBox;
            msgBox = NULL;
            msgBoxEsckey = 0;
        }
        else
        {
            emit saveDisplayPage(3);
        }
    }
    else
    {
        emit saveDisplayPage(0);
    }

    delete videoOutputDialog;
    videoOutputDialog = NULL;
}
void DisplayPage::onButtonCameraName(void)
{
    emit escapeTabFocus();

    if(!cameraNameDialog)
    {
        cameraNameDialog = new CameraNameDialog(this);
    }

    cameraNameDialog->initCameraNameConfig();
    cameraNameDialog->move((appmgr_get_mainwidget_width()-cameraNameDialog->size().width())/2,(appmgr_get_mainwidget_height()-cameraNameDialog->size().height())/2);

    if(cameraNameDialog->exec())
    {
        emit saveDisplayPage(1);
    }
    else
    {
        emit saveDisplayPage(0);
    }

    delete cameraNameDialog;
    cameraNameDialog = NULL;

}
void DisplayPage::onButtonOsd(void)
{
    emit escapeTabFocus();

    if(!osdDialog)
    {
        osdDialog = new OsdDialog(this);
    }

    osdDialog->initOsdConfig();
    osdDialog->move((appmgr_get_mainwidget_width()-osdDialog->size().width())/2,(appmgr_get_mainwidget_height()-osdDialog->size().height())/2);

    if(osdDialog->exec())
    {
        emit saveDisplayPage(4);
    }
    else
    {
        emit saveDisplayPage(0);
    }

    delete osdDialog;
    osdDialog = NULL;
}
void DisplayPage::onButtonClose(void)
{
    emit escapeTabFocus();
    emit closeSetupMenu();
}
