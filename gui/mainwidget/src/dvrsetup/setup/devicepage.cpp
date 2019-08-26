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

        buttonVideo = ui720.buttonVideo;
        buttonTrigger = ui720.buttonTrigger;
        buttonGsensor = ui720.buttonGsensor;
        buttonBuzzer = ui720.buttonBuzzer;
        buttonDiskFormat = ui720.buttonDiskFormat;
        buttonClose = ui720.buttonClose;
    }
    else
    {
        Ui::DevicePage1080p ui1080;
        ui1080.setupUi(this);

        buttonVideo = ui1080.buttonVideo;
        buttonTrigger = ui1080.buttonTrigger;
        buttonGsensor = ui1080.buttonGsensor;
        buttonBuzzer = ui1080.buttonBuzzer;
        buttonDiskFormat = ui1080.buttonDiskFormat;
        buttonClose = ui1080.buttonClose;
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    msgBox              = NULL;
    videoInputDialog    = NULL;
    triggerInputDialog  = NULL;
    gsensorDialog       = NULL;
    buzzerDialog        = NULL;

    appmgr_get_disk_info(&diskInfo[0]);
    if(diskInfo[0].smartInfo_ata_id)    { buttonDiskFormat->setText(tr("HDD Format")); }
    else                                { buttonDiskFormat->setText(tr("SSD Format")); }

    connect(buttonVideo,       SIGNAL(released()), this, SLOT(onButtonVideo()));
    connect(buttonTrigger,     SIGNAL(released()), this, SLOT(onButtonTrigger()));
    connect(buttonGsensor,     SIGNAL(released()), this, SLOT(onButtonGsensor()));
    connect(buttonBuzzer,      SIGNAL(released()), this, SLOT(onButtonBuzzer()));
    connect(buttonDiskFormat,  SIGNAL(released()), this, SLOT(onDiskFormat()));
    connect(buttonClose,       SIGNAL(released()), this, SLOT(onButtonClose()));
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
void DevicePage::onDiskFormat(void)
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
