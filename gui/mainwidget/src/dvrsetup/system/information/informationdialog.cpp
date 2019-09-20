#include <QtGui>
#include "informationdialog.h"
#include "main/mainglobal.h"

InformationDialog::InformationDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::InformationDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelLicensePlate = ui720.labelLicensePlate;
        labelLicensePlate2 = ui720.labelLicensePlate2;
        labelModelName = ui720.labelModelName;
        labelModelName2 = ui720.labelModelName2;
        labelVersion = ui720.labelVersion;
        labelVersion2 = ui720.labelVersion2;
        labelHddSize = ui720.labelHddSize;
        labelNormalSize2 = ui720.labelNormalSize2;
        labelEventSize2 = ui720.labelEventSize2;
        labelDVRTemperature = ui720.labelDVRTemperature;
        labelDVRTemperature2 = ui720.labelDVRTemperature2;
        labelDiskTemperature = ui720.labelDiskTemperature;
        labelGps = ui720.labelGps;
        labelGps2 = ui720.labelGps2;
        buttonClose = ui720.buttonClose;

        labelLicensePlate   ->setStyleSheet("font:46px;color:white");
        labelModelName      ->setStyleSheet("font:46px;color:white");
        labelVersion        ->setStyleSheet("font:46px;color:white");
        labelHddSize        ->setStyleSheet("font:46px;color:white");
        labelGps            ->setStyleSheet("font:46px;color:white");
        labelLicensePlate2  ->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelModelName2     ->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelVersion2       ->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelNormalSize2    ->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelEventSize2     ->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelGps2           ->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelDiskTemperature->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelDVRTemperature ->setStyleSheet("font:46px;color:white");
        labelDVRTemperature2->setStyleSheet("font:46px;background-color:rgb(50,57,83);color:white;padding-left:15px;");

        //yjsin [17/10/12] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
        {
            labelLicensePlate->setStyleSheet("font:35px;color:white");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "ENGLISH") == 0)
        {
            labelLicensePlate->setStyleSheet("font:43px;color:white");
        }
    }
    else
    {
        Ui::InformationDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelLicensePlate = ui1080.labelLicensePlate;
        labelLicensePlate2 = ui1080.labelLicensePlate2;
        labelModelName = ui1080.labelModelName;
        labelModelName2 = ui1080.labelModelName2;
        labelVersion = ui1080.labelVersion;
        labelVersion2 = ui1080.labelVersion2;
        labelHddSize = ui1080.labelHddSize;
        labelNormalSize2 = ui1080.labelNormalSize2;
        labelEventSize2 = ui1080.labelEventSize2;
        labelDVRTemperature = ui1080.labelDVRTemperature;
        labelDVRTemperature2 = ui1080.labelDVRTemperature2;
        labelDiskTemperature = ui1080.labelDiskTemperature;
        labelGps = ui1080.labelGps;
        labelGps2 = ui1080.labelGps2;
        buttonClose = ui1080.buttonClose;

        labelLicensePlate   ->setStyleSheet("font:65px;color:white");
        labelModelName      ->setStyleSheet("font:65px;color:white");
        labelVersion        ->setStyleSheet("font:65px;color:white");
        labelHddSize        ->setStyleSheet("font:65px;color:white");
        labelGps            ->setStyleSheet("font:65px;color:white");
        labelLicensePlate2  ->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelModelName2     ->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelVersion2       ->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelNormalSize2    ->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelEventSize2     ->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelGps2           ->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelDiskTemperature->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelDVRTemperature ->setStyleSheet("font:65px;color:white");
        labelDVRTemperature2->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white;padding-left:30px;");

        //yjsin [19/02/21] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
        {
            labelLicensePlate->setStyleSheet("font:45px;color:white");
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonClose->setFocus();

    connect(buttonClose, SIGNAL(released()), this, SLOT(onClose()));
}
InformationDialog::~InformationDialog()
{
}
void InformationDialog::initInformationConfig(void)
{
    char tmp[32], *modelName = NULL;

    QByteArray text = QByteArray::fromHex(SystemCfg.license_plate);
    QString    str  = QString::fromUtf8(text.data());
    labelLicensePlate2->setText(tr("%1").arg(str));

    modelName = utils_get_model_name();
    labelModelName2->setText(tr("%1").arg(modelName));

    memset(tmp, 0, sizeof(tmp));
    (void)utils_get_sw_version(tmp);
    labelVersion2->setText(tr("%1").arg(tmp));

    memset(tmp, 0, sizeof(tmp));
    (void)utils_get_normal_total_size(tmp);
    QString nomalCapacity=QString(tmp);

    if( nomalCapacity.compare("No Disk")==0 || nomalCapacity.compare("0 GigaByte")==0 )
    {
        labelNormalSize2->setText(tr("%1").arg(tr("No SSD")));

        if(mainHeight == 720)
        {
            labelNormalSize2->resize(740,85);
        }
        else
        {
            labelNormalSize2->resize(1061,121);
        }
    }
    else
    {
        labelNormalSize2->setText(tr("%1").arg(tmp));
    }

    memset(tmp, 0, sizeof(tmp));
    (void)utils_get_event_total_size(tmp);
    QString eventCapacity=QString(tmp);

    if( eventCapacity.compare("No Disk")==0 || eventCapacity.compare("0 GigaByte")==0 )
    {
        labelEventSize2->setText(tr("%1").arg(tr("No SSD")));
        labelEventSize2->setVisible(false);
    }
    else
    {
        labelEventSize2->setText(tr("%1").arg(tmp));
    }

    onUpdateStatus();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateStatus()));
    updateTimer->start(1000);
}
void InformationDialog::onUpdateStatus(void)
{
    int isConnected = appmgr_get_gps_connected();

    if(isConnected)
    {
        labelGps2->setText(tr("%1").arg(tr("Connected")));
    }
    else
    {
        labelGps2->setText(tr("%1").arg(tr("Not connected")));
    }

    appmgr_get_disk_info(&diskInfo);

    if(diskInfo.smartInfo_ata_id)
    {
        labelHddSize->setText(tr("HDD Size"));
        labelDiskTemperature->setText(tr("%1%2%3").arg("HDD: ").arg(diskInfo.smartInfo_temperature).arg(tr(" ℃")));
    }
    else
    {
        labelHddSize->setText(tr("SSD Size"));
        labelDiskTemperature->setText(tr("%1%2%3").arg("SSD: ").arg(diskInfo.smartInfo_temperature).arg(tr(" ℃")));
    }

    labelDVRTemperature2->setText(tr("%1%2%3").arg("DVR: ").arg(appmgr_get_board_temperature()).arg(tr(" ℃")));
}
void InformationDialog::onClose(void)
{
    updateTimer->stop();
    delete updateTimer;
    reject();
}
void InformationDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Enter:
        {
            if(buttonClose->hasFocus())
            {
                onClose();
            }

            return;
        }
        case Qt::Key_Escape:
        {
            onClose();

            return;
        }
        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
