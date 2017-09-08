#include <QtGui>
#include "diskformatprocess.h"
#include "main/mainglobal.h"
#include "hal/diskservice.h"

DiskFormatProcessDialog::DiskFormatProcessDialog(QWidget *parent)
    : QDialog(parent)
{
	setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	setPalette(QPalette(QColor(255, 128, 64)));
	frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
	setAutoFillBackground(true);

	labelStatus = new QLabel("");
	labelStatus->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	labelStatus->setMinimumWidth(840);
	labelStatus->setMinimumHeight(200);
	labelStatus->setFrameStyle(QFrame::Box);
	labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

	diskformatProgressBar = new QProgressBar;
	diskformatProgressBar->setRange(0, 100);
	diskformatProgressBar->setValue(0);
	diskformatProgressBar->setAlignment(Qt::AlignCenter);
	diskformatProgressBar->setStyleSheet("QProgressBar {font:48px;color:white;} QProgressBar::chunk{font:48px;Background-color:rgb(152,14,69);}");
	diskformatProgressBar->setMinimumWidth(840);
	diskformatProgressBar->setMinimumHeight(100);
    diskformatProgressBar->setTextVisible(true);

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(labelStatus);
	layout->addWidget(diskformatProgressBar);

	setLayout(layout);

	frame->setGeometry(4, 4, sizeHint().width()-8, sizeHint().height()-8);
}
DiskFormatProcessDialog::~DiskFormatProcessDialog()
{
}
void DiskFormatProcessDialog::DiskFormatInit()
{
	diskformatProgressBar->setFormat(tr("Formatting..."));
	labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
	diskformatProgressBar->setValue(0);
	labelStatus->setText(tr("%1\n%2").arg(tr("Please don't turn off system."), tr("System will restart after formatting.")));
}
void DiskFormatProcessDialog::TestDiskFormatInit()
{
	diskformatProgressBar->setFormat(tr("Formatting..."));
	labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
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

	if(DiskService::impl()->formatResult() == 0) { str = QString(tr("Format Fail")); }
	else                                         { str = QString(tr("Format Success")); }

	qDebug() << __func__ << str;

	diskformatProgressBar->setValue(0);
	diskformatProgressBar->setFormat("");

	labelStatus->setStyleSheet("font:72px;background-color:rgb(152,14,69);color:white");
	labelStatus->setAlignment(Qt::AlignCenter);
	labelStatus->setText(str);

	QTimer::singleShot(3000, this, SLOT(onSystemReboot()));
}
void DiskFormatProcessDialog::onDiskformatupdate()
{
	;
}
