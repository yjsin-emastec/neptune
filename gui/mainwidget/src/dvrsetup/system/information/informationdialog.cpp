#include <QtGui>
#include "informationdialog.h"
#include "main/mainglobal.h"

InformationDialog::InformationDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonClose->setFocus();

    labelLicensePlate   ->setStyleSheet("font:48px;color:white");
    labelLicensePlate   ->setAlignment(Qt::AlignCenter);
    labelModelName      ->setStyleSheet("font:48px;color:white");
    labelModelName      ->setAlignment(Qt::AlignCenter);
    labelVersion        ->setStyleSheet("font:48px;color:white");
    labelVersion        ->setAlignment(Qt::AlignCenter);
    labelHddSize        ->setStyleSheet("font:48px;color:white");
    labelHddSize        ->setAlignment(Qt::AlignCenter);
    labelGps            ->setStyleSheet("font:48px;color:white");
    labelGps            ->setAlignment(Qt::AlignCenter);
    labelLicensePlate2  ->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelModelName2     ->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelVersion2       ->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelNormalSize2    ->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelEventSize2     ->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelGps2           ->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelDiskTemperature->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelDVRTemperature ->setStyleSheet("font:48px;color:white");
    labelDVRTemperature ->setAlignment(Qt::AlignCenter);
    labelDVRTemperature2->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

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
        labelNormalSize2->setText(tr("%1").arg(tr("No Disk")));
        labelNormalSize2->setGeometry(370,280,700,85);
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
        labelEventSize2->setText(tr("%1").arg(tr("No Disk")));
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
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:

            return;

        default:
        case Qt::Key_Enter:
        case Qt::Key_Escape:

            if(buttonClose->hasFocus())
            {
                onClose();
            }

            return;
    }

    QDialog::keyPressEvent(event);
}
