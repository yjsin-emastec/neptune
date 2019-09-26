#include "devicepage.h"
#include "textmessagebox/textmessagedialog.h"
#include "dvrsetup/device/videoinput/videoinputdialog.h"
#include "dvrsetup/device/triggerinput/triggerinputdialog.h"
#include "dvrsetup/device/gsensor/gsensordialog.h"
#include "dvrsetup/device/buzzer/buzzerdialog.h"
#include "hal/diskservice.h"
#include "main/mainglobal.h"

DevicePage::DevicePage(QWidget *parent)
    : QWidget(parent)
{
    if(mainHeight == 720)
    {
        Ui::DevicePage ui720;
        ui720.setupUi(this);

        buttonVideo         = ui720.buttonVideo;
        buttonTrigger       = ui720.buttonTrigger;
        buttonGsensor       = ui720.buttonGsensor;
        buttonBuzzer        = ui720.buttonBuzzer;
        buttonFormat        = ui720.buttonFormat;
        buttonClose         = ui720.buttonClose;

        labelVideoText      = ui720.labelVideoText;
        labelTriggerText    = ui720.labelTriggerText;
        labelGsensorText    = ui720.labelGsensorText;
        labelBuzzerText     = ui720.labelBuzzerText;
        labelFormatText     = ui720.labelFormatText;
        labelCloseText      = ui720.labelCloseText;

        labelVideoText      ->setStyleSheet("font: 40px;");
        labelTriggerText    ->setStyleSheet("font: 40px;");
        labelGsensorText    ->setStyleSheet("font: 40px;");
        labelBuzzerText     ->setStyleSheet("font: 40px;");
        labelFormatText     ->setStyleSheet("font: 40px;");
        labelCloseText      ->setStyleSheet("font: 40px;");
    }
    else
    {
        Ui::DevicePage1080p ui1080;
        ui1080.setupUi(this);

        buttonVideo         = ui1080.buttonVideo;
        buttonTrigger       = ui1080.buttonTrigger;
        buttonGsensor       = ui1080.buttonGsensor;
        buttonBuzzer        = ui1080.buttonBuzzer;
        buttonFormat        = ui1080.buttonFormat;
        buttonClose         = ui1080.buttonClose;

        labelVideoText      = ui1080.labelVideoText;
        labelTriggerText    = ui1080.labelTriggerText;
        labelGsensorText    = ui1080.labelGsensorText;
        labelBuzzerText     = ui1080.labelBuzzerText;
        labelFormatText     = ui1080.labelFormatText;
        labelCloseText      = ui1080.labelCloseText;

        labelVideoText      ->setStyleSheet("font:65px;");
        labelTriggerText    ->setStyleSheet("font:65px;");
        labelGsensorText    ->setStyleSheet("font:65px;");
        labelBuzzerText     ->setStyleSheet("font:65px;");
        labelFormatText     ->setStyleSheet("font:65px;");
        labelCloseText      ->setStyleSheet("font:65px;");
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    msgBox              = NULL;
    videoInputDialog    = NULL;
    triggerInputDialog  = NULL;
    gsensorDialog       = NULL;
    buzzerDialog        = NULL;

    appmgr_get_disk_info(&diskInfo[0]);
    if(diskInfo[0].smartInfo_ata_id)    { labelFormatText->setText(tr("HDD Format")); }
    else                                { labelFormatText->setText(tr("SSD Format")); }

    iconImageNormal[0].load(":images/dvrsetup/device/videoinput.png");
    iconImageNormal[1].load(":images/dvrsetup/device/videoinput.png");
    iconImageNormal[2].load(":images/dvrsetup/device/impactsensitivity.png");
    iconImageNormal[3].load(":images/dvrsetup/display/videoout.png");
    iconImageNormal[4].load(":images/dvrsetup/device/diskformat.png");
    iconImageNormal[5].load(":images/dvrsetup/system/close.png");

    iconImageFocus[0].load(":images/dvrsetup/device/videoinput2.png");
    iconImageFocus[1].load(":images/dvrsetup/device/videoinput2.png");
    iconImageFocus[2].load(":images/dvrsetup/device/impactsensitivity2.png");
    iconImageFocus[3].load(":images/dvrsetup/display/videoout2.png");
    iconImageFocus[4].load(":images/dvrsetup/device/diskformat2.png");
    iconImageFocus[5].load(":images/dvrsetup/system/close2.png");

    buttonVideo     ->setPixmap(iconImageNormal[0]);
    buttonTrigger   ->setPixmap(iconImageNormal[1]);
    buttonGsensor   ->setPixmap(iconImageNormal[2]);
    buttonBuzzer    ->setPixmap(iconImageNormal[3]);
    buttonFormat    ->setPixmap(iconImageNormal[4]);
    buttonClose     ->setPixmap(iconImageNormal[5]);

    buttonVideo     ->setScaledContents(true);
    buttonTrigger   ->setScaledContents(true);
    buttonGsensor   ->setScaledContents(true);
    buttonBuzzer    ->setScaledContents(true);
    buttonFormat    ->setScaledContents(true);
    buttonClose     ->setScaledContents(true);

    connect(buttonVideo,        SIGNAL(pressed()), this, SLOT(onButtonVideo()));
    connect(buttonTrigger,      SIGNAL(pressed()), this, SLOT(onButtonTrigger()));
    connect(buttonGsensor,      SIGNAL(pressed()), this, SLOT(onButtonGsensor()));
    connect(buttonBuzzer,       SIGNAL(pressed()), this, SLOT(onButtonBuzzer()));
    connect(buttonFormat,       SIGNAL(pressed()), this, SLOT(onButtonFormat()));
    connect(buttonClose,        SIGNAL(pressed()), this, SLOT(onButtonClose()));
    connect(buttonVideo,        SIGNAL(focusIn()), this, SLOT(setFocusVideo()));
    connect(buttonTrigger,      SIGNAL(focusIn()), this, SLOT(setFocusTrigger()));
    connect(buttonGsensor,      SIGNAL(focusIn()), this, SLOT(setFocusGsensor()));
    connect(buttonBuzzer,       SIGNAL(focusIn()), this, SLOT(setFocusBuzzer()));
    connect(buttonFormat,       SIGNAL(focusIn()), this, SLOT(setFocusFormat()));
    connect(buttonClose,        SIGNAL(focusIn()), this, SLOT(setFocusClose()));
}
DevicePage::~DevicePage()
{
}
void DevicePage::onButtonVideo(void)
{
    emit escapeTabFocus();

    if(!videoInputDialog)
    {
        videoInputDialog = new VideoInputDialog(this);
        connect(videoInputDialog, SIGNAL(makeTransparent(int)), this, SLOT(onMakeTransparent(int)));
        connect(videoInputDialog, SIGNAL(videoInputPreview()),  this, SLOT(onVideoInputPreview()));

        if(!videoInputDialog)
        {
            qDebug("Error : %s, Not allocated\n", __func__);
            return;
        }
    }

    videoInputDialog->initVideoInputConfig();
    videoInputDialog->move((appmgr_get_mainwidget_width()-videoInputDialog->width())/2,(appmgr_get_mainwidget_height()-videoInputDialog->height())/2);

    if(videoInputDialog->exec())
    {
        emit saveDevicePage(5);
    }
    else
    {
        emit saveDevicePage(6);
    }

    delete videoInputDialog;
    videoInputDialog = NULL;
}
void DevicePage::onMakeTransparent(int n)
{
    emit makeTransparent(n);
}
void DevicePage::onVideoInputPreview()
{
    emit videoInputPreview();
}
void DevicePage::onButtonTrigger(void)
{
    emit escapeTabFocus();

    if(!triggerInputDialog)
    {
        triggerInputDialog = new TriggerInputDialog(this);

        if(!triggerInputDialog)
        {
            qDebug("Error : %s, Not allocated\n", __func__);
            return;
        }
    }

    triggerInputDialog->initTriggerInputConfig();
    triggerInputDialog->move((appmgr_get_mainwidget_width()-triggerInputDialog->width())/2,(appmgr_get_mainwidget_height()-triggerInputDialog->height())/2);

    if(triggerInputDialog->exec())
    {
        emit saveDevicePage(4);
    }
    else
    {
        emit saveDevicePage(0);
    }

    delete triggerInputDialog;
    triggerInputDialog = NULL;
}
void DevicePage::onButtonGsensor(void)
{
    emit escapeTabFocus();

    if(!gsensorDialog)
    {
        gsensorDialog = new GsensorDialog(this);

        if(!gsensorDialog)
        {
            qDebug("Error : %s, Not allocated\n", __func__);
            return;
        }
    }

    gsensorDialog->initGsensorConfig();
    gsensorDialog->move((appmgr_get_mainwidget_width()-gsensorDialog->width())/2,(appmgr_get_mainwidget_height()-gsensorDialog->height())/2);

    if(gsensorDialog->exec())
    {
        emit saveDevicePage(3);
    }
    else
    {
        emit saveDevicePage(0);
    }

    delete gsensorDialog;
    gsensorDialog = NULL;
}
void DevicePage::onButtonBuzzer(void)
{
    emit escapeTabFocus();

    if(!buzzerDialog)
    {
        buzzerDialog = new BuzzerDialog(this);

        if(!buzzerDialog)
        {
            qDebug("Error : %s, Not allocated\n", __func__);
            return;
        }
    }

    buzzerDialog->initBuzzerConfig();
    buzzerDialog->move((appmgr_get_mainwidget_width()-buzzerDialog->width())/2,(appmgr_get_mainwidget_height()-buzzerDialog->height())/2);

    if(buzzerDialog->exec())
    {
        emit saveDevicePage(2);
    }
    else
    {
        emit saveDevicePage(0);
    }

    delete buzzerDialog;
    buzzerDialog = NULL;
}
void DevicePage::onButtonFormat(void)
{
    emit escapeTabFocus();

    if(!msgBox)
    {
        if(diskInfo[0].smartInfo_ata_id)    { msgBox = new TextMessageDialog(tr("HDD FORMAT"), tr("Are you sure to format HDD?\n" "System will restart after format."), 0, this); }
        else                                { msgBox = new TextMessageDialog(tr("SSD FORMAT"), tr("Are you sure to format SSD?\n" "System will restart after format."), 0, this); }
    }

    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
    msgBoxEsckey = 1;

    if(msgBox->exec())
    {
        memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);
        DiskService::impl()->diskInfo(diskInfo);

        if(diskInfo[0].hddInfo_size != 0)
        {
            emit saveDevicePage(1);
        }
        else
        {
            delete msgBox;
            msgBox = NULL;
            msgBoxEsckey = 0;
            msgBoxEsckey = 1;
            msgBox = new TextMessageDialog(tr("SSD FORMAT"), tr("SSD does not exist."), 2, this);
            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
            msgBox->exec();
        }
    }

    delete msgBox;
    msgBox = NULL;
    msgBoxEsckey = 0;
}
void DevicePage::onButtonClose()
{
    emit escapeTabFocus();
    emit closeSetupMenu();
}
void DevicePage::setFocusTabLayout()    { changeFocus(0); }
void DevicePage::setFocusVideo()        { changeFocus(1); }
void DevicePage::setFocusTrigger()      { changeFocus(2); }
void DevicePage::setFocusGsensor()      { changeFocus(3); }
void DevicePage::setFocusBuzzer()       { changeFocus(4); }
void DevicePage::setFocusFormat()       { changeFocus(5); }
void DevicePage::setFocusClose()        { changeFocus(6); }
void DevicePage::changeFocus(int n)
{
    buttonVideo     ->setPixmap(iconImageNormal[0]);
    buttonTrigger   ->setPixmap(iconImageNormal[1]);
    buttonGsensor   ->setPixmap(iconImageNormal[2]);
    buttonBuzzer    ->setPixmap(iconImageNormal[3]);
    buttonFormat    ->setPixmap(iconImageNormal[4]);
    buttonClose     ->setPixmap(iconImageNormal[5]);

    buttonVideo     ->setFocusState(false);
    buttonTrigger   ->setFocusState(false);
    buttonGsensor   ->setFocusState(false);
    buttonBuzzer    ->setFocusState(false);
    buttonFormat    ->setFocusState(false);
    buttonClose     ->setFocusState(false);

    switch(n)
    {
        case 0 :
            break;

        case 1 :
            buttonVideo     ->setPixmap(iconImageFocus[0]);
            buttonVideo     ->setFocusState(true);
            break;

        case 2 :
            buttonTrigger   ->setPixmap(iconImageFocus[1]);
            buttonTrigger   ->setFocusState(true);
            break;

        case 3 :
            buttonGsensor   ->setPixmap(iconImageFocus[2]);
            buttonGsensor   ->setFocusState(true);
            break;

        case 4 :
            buttonBuzzer    ->setPixmap(iconImageFocus[3]);
            buttonBuzzer    ->setFocusState(true);
            break;

        case 5 :
            buttonFormat    ->setPixmap(iconImageFocus[4]);
            buttonFormat    ->setFocusState(true);
            break;

        case 6 :
            buttonClose     ->setPixmap(iconImageFocus[5]);
            buttonClose     ->setFocusState(true);
            break;

        default :
            buttonVideo     ->setPixmap(iconImageFocus[0]);
            buttonVideo     ->setFocusState(true);
            break;
    }
}
