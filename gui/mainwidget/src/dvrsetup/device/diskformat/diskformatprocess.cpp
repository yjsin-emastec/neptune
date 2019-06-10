#include <QtGui>
#include "diskformatprocess.h"
#include "main/mainglobal.h"
#include "hal/diskservice.h"

DiskFormatProcessDialog::DiskFormatProcessDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::DiskFormatProcessDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelStatus=ui720.labelStatus;
        diskformatProgressBar=ui720.diskformatProgressBar;

        labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white;padding-left:10px;");
        diskformatProgressBar->setStyleSheet("QProgressBar {font:48px;color:white;} QProgressBar::chunk{font:48px;Background-color:rgb(152,14,69);}");

        //yjsin [18/01/05] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            labelStatus->setStyleSheet("font:41px;background-color:rgb(50,57,83);color:white;padding-left:10px;");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            labelStatus->setStyleSheet("font:41px;background-color:rgb(50,57,83);color:white;padding-left:10px;");
        }
    }
    else
    {
        Ui::DiskFormatProcessDialog1080p ui1080p;
        ui1080p.setupUi(this);

        frame = ui1080p.frame;
        labelStatus=ui1080p.labelStatus;
        diskformatProgressBar=ui1080p.diskformatProgressBar;

        labelStatus->setStyleSheet("font:70px;background-color:rgb(50,57,83);color:white;padding-left:30px");
        diskformatProgressBar->setStyleSheet("QProgressBar {font:70px;color:white;} QProgressBar::chunk{font:48px;Background-color:rgb(152,14,69);}");

        //yjsin [19/02/21] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            labelStatus->setStyleSheet("font:62px;background-color:rgb(50,57,83);color:white;padding-left:20px;");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            labelStatus->setStyleSheet("font:62px;background-color:rgb(50,57,83);color:white;padding-left:20px;");
        }
    }

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	setPalette(QPalette(QColor(255, 128, 64)));
	frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
	setAutoFillBackground(true);
}
DiskFormatProcessDialog::~DiskFormatProcessDialog()
{
}
void DiskFormatProcessDialog::DiskFormatInit()
{
	diskformatProgressBar->setFormat(tr("Formatting..."));
	diskformatProgressBar->setValue(0);
	labelStatus->setText(tr("%1\n%2").arg(tr("Please don't turn off system."), tr("System will restart after formatting.")));
}
void DiskFormatProcessDialog::TestDiskFormatInit()
{
	diskformatProgressBar->setFormat(tr("Formatting..."));
	diskformatProgressBar->setValue(0);
	labelStatus->setText(tr("%1\n%2").arg(tr("You must not turn off system."), tr("Please wait during formatting.")));
}
void DiskFormatProcessDialog::StartFormat()
{
	StartTimer();
	DiskService::impl()->format(DiskFormatNum);
}
void DiskFormatProcessDialog::onSystemReboot()
{
	emit diskformatReboot();
}
void DiskFormatProcessDialog::onDiskFormatupdateprocess(int disk, unsigned long total, unsigned long percent, unsigned long remain_time)
{
	int i = 0, diskNum = 0;

    qDebug("\t===========================> FORMAT => %d%%", percent);

	if(total != 2)
	{
		diskformatProgressBar->setValue(percent);
	}

	if(total == 1) // Format Start
	{
		for(i = 0; i < MAX_HDD_COUNT; i++)
		{
			if(DiskFormatNum & (0x01 << i))
			{
				diskNum = i;
				break;
			}
		}
		qDebug("\n\t START format disk %d, diskNum = %d, DiskFormatNum = %x \n", disk, diskNum, DiskFormatNum);

		for(i = 0; i < MAX_HDD_COUNT; i++)
		{
			if(DiskFormatNum & (0x01 << i))
			{
				diskNum = i;
				DiskFormatNum &= ~(0x1 << i);
				break;
			}
		}
	}
	else if(total == 2) // Format Stop
	{
		qDebug("\n\t STOP format disk %d, diskNum = %d, DiskFormatNum = %x \n", disk, diskNum, DiskFormatNum);

		if(DiskFormatNum == 0)
        {
			formatTimer->stop();
		}
	}
}
void DiskFormatProcessDialog::StartTimer()
{
	formatTimer = new QTimer(this);

	connect(formatTimer, SIGNAL(timeout()), this, SLOT(onDiskformatupdate()));

	formatTimer->start(1000);
}
void DiskFormatProcessDialog::onDiskFormatupdateEnd()
{
	qDebug("\n\t onDiskFormatupdateEnd !!! \n");

	formatTimer->stop();
	delete formatTimer;

	QString str;

	if(DiskService::impl()->formatResult() == 0) { str = QString(tr("Format Failure")); appmgr_write_system_log(SYSTEM_LOG_TYPE_FLASH, "Format Failure"); }
	else                                         { str = QString(tr("Format Success")); appmgr_write_system_log(SYSTEM_LOG_TYPE_FLASH, "Format Success"); }

	qDebug() << __func__ << str;

	diskformatProgressBar->setValue(0);
	diskformatProgressBar->setFormat("");

    if(mainHeight == 720)
    {
        labelStatus->setStyleSheet("font:72px;background-color:rgb(152,14,69);color:white");
    }
    else
    {
        labelStatus->setStyleSheet("font:100px;background-color:rgb(152,14,69);color:white");
    }
	labelStatus->setAlignment(Qt::AlignCenter);
	labelStatus->setText(str);

	QTimer::singleShot(3000, this, SLOT(onSystemReboot()));
}
void DiskFormatProcessDialog::onDiskformatupdate()
{
	;
}
