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

        buttonVideoOutput       = ui720.buttonVideoOutput;
        buttonCameraName        = ui720.buttonCameraName;
        buttonNotAvailable      = ui720.buttonNotAvailable;
        buttonOsd               = ui720.buttonOsd;
        buttonNotAvailable2     = ui720.buttonNotAvailable2;
        buttonClose             = ui720.buttonClose;

        labelVideoOutputText    = ui720.labelVideoOutputText;
        labelCameraNameText     = ui720.labelCameraNameText;
        labelNotAvailableText   = ui720.labelNotAvailableText;
        labelOsdText            = ui720.labelOsdText;
        labelNotAvailableText2  = ui720.labelNotAvailableText2;
        labelCloseText          = ui720.labelCloseText;

        labelVideoOutputText    ->setStyleSheet("font: 40px;");
        labelCameraNameText     ->setStyleSheet("font: 40px;");
        labelNotAvailableText   ->setStyleSheet("font: 40px;");
        labelOsdText            ->setStyleSheet("font: 40px;");
        labelNotAvailableText2  ->setStyleSheet("font: 40px;");
        labelCloseText          ->setStyleSheet("font: 40px;");
    }
    else
    {
        Ui::DisplayPage1080p ui1080;
        ui1080.setupUi(this);

        buttonVideoOutput       = ui1080.buttonVideoOutput;
        buttonCameraName        = ui1080.buttonCameraName;
        buttonNotAvailable      = ui1080.buttonNotAvailable;
        buttonOsd               = ui1080.buttonOsd;
        buttonNotAvailable2     = ui1080.buttonNotAvailable2;
        buttonClose             = ui1080.buttonClose;

        labelVideoOutputText    = ui1080.labelVideoOutputText;
        labelCameraNameText     = ui1080.labelCameraNameText;
        labelNotAvailableText   = ui1080.labelNotAvailableText;
        labelOsdText            = ui1080.labelOsdText;
        labelNotAvailableText2  = ui1080.labelNotAvailableText2;
        labelCloseText          = ui1080.labelCloseText;

        labelVideoOutputText    ->setStyleSheet("font: 65px;");
        labelCameraNameText     ->setStyleSheet("font: 65px;");
        labelNotAvailableText   ->setStyleSheet("font: 65px;");
        labelOsdText            ->setStyleSheet("font: 65px;");
        labelNotAvailableText2  ->setStyleSheet("font: 65px;");
        labelCloseText          ->setStyleSheet("font: 65px;");
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    msgBox             = NULL;
    videoOutputDialog  = NULL;
    cameraNameDialog   = NULL;
    osdDialog          = NULL;

    iconImageNormal[0].load(":images/dvrsetup/display/videoout.png");
    iconImageNormal[1].load(":images/dvrsetup/display/cameraname.png");
    iconImageNormal[2].load(":images/dvrsetup/display/blank.png");
    iconImageNormal[3].load(":images/dvrsetup/display/osd.png");
    iconImageNormal[4].load(":images/dvrsetup/display/blank.png");
    iconImageNormal[5].load(":images/dvrsetup/system/close.png");

    iconImageFocus[0].load(":images/dvrsetup/display/videoout2.png");
    iconImageFocus[1].load(":images/dvrsetup/display/cameraname2.png");
    //iconImageFocus[2].load(":images/dvrsetup/display/blank2.png");
    iconImageFocus[3].load(":images/dvrsetup/display/osd2.png");
    //iconImageFocus[4].load(":images/dvrsetup/display/blank2.png");
    iconImageFocus[5].load(":images/dvrsetup/system/close2.png");

    buttonVideoOutput   ->setPixmap(iconImageNormal[0]);
    buttonCameraName    ->setPixmap(iconImageNormal[1]);
    buttonNotAvailable  ->setPixmap(iconImageNormal[2]);
    buttonOsd           ->setPixmap(iconImageNormal[3]);
    buttonNotAvailable2 ->setPixmap(iconImageNormal[4]);
    buttonClose         ->setPixmap(iconImageNormal[5]);

    buttonVideoOutput   ->setScaledContents(true);
    buttonCameraName    ->setScaledContents(true);
    buttonNotAvailable  ->setScaledContents(true);
    buttonOsd           ->setScaledContents(true);
    buttonNotAvailable2 ->setScaledContents(true);
    buttonClose         ->setScaledContents(true);

    connect(buttonVideoOutput, SIGNAL(pressed()), this, SLOT(onButtonVideoOutput()));
    connect(buttonCameraName,  SIGNAL(pressed()), this, SLOT(onButtonCameraName()));
    connect(buttonOsd,         SIGNAL(pressed()), this, SLOT(onButtonOsd()));
    connect(buttonClose,       SIGNAL(pressed()), this, SLOT(onButtonClose()));
    connect(buttonVideoOutput, SIGNAL(focusIn()), this, SLOT(setFocusVideoOutput()));
    connect(buttonCameraName,  SIGNAL(focusIn()), this, SLOT(setFocusCameraName()));
    connect(buttonOsd,         SIGNAL(focusIn()), this, SLOT(setFocusOsd()));
    connect(buttonClose,       SIGNAL(focusIn()), this, SLOT(setFocusClose()));
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
void DisplayPage::setFocusTabLayout()   { changeFocus(0); }
void DisplayPage::setFocusVideoOutput() { changeFocus(1); }
void DisplayPage::setFocusCameraName()  { changeFocus(2); }
void DisplayPage::setFocusOsd()         { changeFocus(4); }
void DisplayPage::setFocusClose()       { changeFocus(6); }
void DisplayPage::changeFocus(int n)
{
    buttonVideoOutput   ->setPixmap(iconImageNormal[0]);
    buttonCameraName    ->setPixmap(iconImageNormal[1]);
    //buttonNotAvailable  ->setPixmap(iconImageNormal[2]);
    buttonOsd           ->setPixmap(iconImageNormal[3]);
    //buttonNotAvailable2 ->setPixmap(iconImageNormal[4]);
    buttonClose         ->setPixmap(iconImageNormal[5]);

    buttonVideoOutput   ->setFocusState(false);
    buttonCameraName    ->setFocusState(false);
    buttonOsd           ->setFocusState(false);
    buttonClose         ->setFocusState(false);

    switch(n)
    {
        case 0 :
            break;

        case 1 :
            buttonVideoOutput->setPixmap(iconImageFocus[0]);
            buttonVideoOutput->setFocusState(true);
            break;

        case 2 :
            buttonCameraName->setPixmap(iconImageFocus[1]);
            buttonCameraName->setFocusState(true);
            break;

        case 3 :
            break;

        case 4 :
            buttonOsd->setPixmap(iconImageFocus[3]);
            buttonOsd->setFocusState(true);
            break;

        case 5 :
            break;

        case 6 :
            buttonClose->setPixmap(iconImageFocus[5]);
            buttonClose->setFocusState(true);
            break;

        default :
            buttonVideoOutput->setPixmap(iconImageFocus[0]);
            buttonVideoOutput->setFocusState(true);
            break;
    }
}
