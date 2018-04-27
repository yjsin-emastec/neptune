#include <QtGui>
#include "triggerinputdialog.h"
#include "main/mainglobal.h"

TriggerInputDialog::TriggerInputDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    buttonSource1Up->setFocus();

    labelTrigger1->setStyleSheet("font:40px;color:white");
    labelTrigger1->setText(tr("Trigger1"));
    labelTrigger1->setAlignment(Qt::AlignCenter);

    labelTrigger2->setStyleSheet("font:40px;color:white");
    labelTrigger2->setText(tr("Trigger2"));
    labelTrigger2->setAlignment(Qt::AlignCenter);

    labelTrigger3->setStyleSheet("font:40px;color:white");
    labelTrigger3->setText(tr("Trigger3"));
    labelTrigger3->setAlignment(Qt::AlignCenter);

    labelTrigger4->setStyleSheet("font:40px;color:white");
    labelTrigger4->setText(tr("Trigger4"));
    labelTrigger4->setAlignment(Qt::AlignCenter);

    labelSource1->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelSource1->setAlignment(Qt::AlignCenter);
    buttonSource1Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonSource1Up->setIconSize(QSize(70, 45));
    buttonSource1Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonSource1Down->setIconSize(QSize(70, 45));

    labelSource2->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelSource2->setAlignment(Qt::AlignCenter);
    buttonSource2Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonSource2Up->setIconSize(QSize(70, 45));
    buttonSource2Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonSource2Down->setIconSize(QSize(70, 45));

    labelSource3->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelSource3->setAlignment(Qt::AlignCenter);
    buttonSource3Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonSource3Up->setIconSize(QSize(70, 45));
    buttonSource3Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonSource3Down->setIconSize(QSize(70, 45));

    labelSource4->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelSource4->setAlignment(Qt::AlignCenter);
    buttonSource4Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonSource4Up->setIconSize(QSize(70, 45));
    buttonSource4Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonSource4Down->setIconSize(QSize(70, 45));

    labelDelay1->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelDelay1->setAlignment(Qt::AlignCenter);
    buttonDelay1Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonDelay1Up->setIconSize(QSize(70, 45));
    buttonDelay1Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDelay1Down->setIconSize(QSize(70, 45));

    labelDelay2->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelDelay2->setAlignment(Qt::AlignCenter);
    buttonDelay2Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonDelay2Up->setIconSize(QSize(70, 45));
    buttonDelay2Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDelay2Down->setIconSize(QSize(70, 45));

    labelDelay3->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelDelay3->setAlignment(Qt::AlignCenter);
    buttonDelay3Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonDelay3Up->setIconSize(QSize(70, 45));
    buttonDelay3Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDelay3Down->setIconSize(QSize(70, 45));

    labelDelay4->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelDelay4->setAlignment(Qt::AlignCenter);
    buttonDelay4Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonDelay4Up->setIconSize(QSize(70, 45));
    buttonDelay4Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDelay4Down->setIconSize(QSize(70, 45));

    labelPriority1->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelPriority1->setAlignment(Qt::AlignCenter);
    buttonPriority1Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonPriority1Up->setIconSize(QSize(70, 45));
    buttonPriority1Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonPriority1Down->setIconSize(QSize(70, 45));

    labelPriority2->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelPriority2->setAlignment(Qt::AlignCenter);
    buttonPriority2Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonPriority2Up->setIconSize(QSize(70, 45));
    buttonPriority2Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonPriority2Down->setIconSize(QSize(70, 45));

    labelPriority3->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelPriority3->setAlignment(Qt::AlignCenter);
    buttonPriority3Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonPriority3Up->setIconSize(QSize(70, 45));
    buttonPriority3Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonPriority3Down->setIconSize(QSize(70, 45));

    labelPriority4->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelPriority4->setAlignment(Qt::AlignCenter);
    buttonPriority4Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonPriority4Up->setIconSize(QSize(70, 45));
    buttonPriority4Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonPriority4Down->setIconSize(QSize(70, 45));

    labelAudio1->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelAudio1->setAlignment(Qt::AlignCenter);
    buttonAudio1Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonAudio1Up->setIconSize(QSize(70, 45));
    buttonAudio1Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonAudio1Down->setIconSize(QSize(70, 45));

    labelAudio2->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelAudio2->setAlignment(Qt::AlignCenter);
    buttonAudio2Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonAudio2Up->setIconSize(QSize(70, 45));
    buttonAudio2Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonAudio2Down->setIconSize(QSize(70, 45));

    labelAudio3->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelAudio3->setAlignment(Qt::AlignCenter);
    buttonAudio3Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonAudio3Up->setIconSize(QSize(70, 45));
    buttonAudio3Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonAudio3Down->setIconSize(QSize(70, 45));

    labelAudio4->setStyleSheet("font:40px;background-color:rgb(50,57,83);color:white");
    labelAudio4->setAlignment(Qt::AlignCenter);
    buttonAudio4Up->setIcon(QIcon(":/images/arrow_up.png"));
    buttonAudio4Up->setIconSize(QSize(70, 45));
    buttonAudio4Down->setIcon(QIcon(":/images/arrow_down.png"));
    buttonAudio4Down->setIconSize(QSize(70, 45));

#if 1 //yjsin [17/09/13] if text is long, change font size and label location and size
    if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
    {
        buttonDefault->resize( 304, 90);
        buttonDefault->setStyleSheet("font:38px");
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
    {
        buttonDefault->resize( 304, 90);
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
    {
        buttonDefault->resize( 304, 90);
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        buttonDefault->resize( 304, 90);
    }
#endif

    connect(buttonSource1Up,       SIGNAL(released()), this, SLOT(onButtonSource1Up()));
    connect(buttonSource1Down,     SIGNAL(released()), this, SLOT(onButtonSource1Down()));
    connect(buttonDelay1Up,        SIGNAL(released()), this, SLOT(onButtonDelay1Up()));
    connect(buttonDelay1Down,      SIGNAL(released()), this, SLOT(onButtonDelay1Down()));
    connect(buttonPriority1Up,     SIGNAL(released()), this, SLOT(onButtonPriority1Up()));
    connect(buttonPriority1Down,   SIGNAL(released()), this, SLOT(onButtonPriority1Down()));
    connect(buttonAudio1Up,        SIGNAL(released()), this, SLOT(onButtonAudio1Up()));
    connect(buttonAudio1Down,      SIGNAL(released()), this, SLOT(onButtonAudio1Down()));

    connect(buttonSource2Up,       SIGNAL(released()), this, SLOT(onButtonSource2Up()));
    connect(buttonSource2Down,     SIGNAL(released()), this, SLOT(onButtonSource2Down()));
    connect(buttonDelay2Up,        SIGNAL(released()), this, SLOT(onButtonDelay2Up()));
    connect(buttonDelay2Down,      SIGNAL(released()), this, SLOT(onButtonDelay2Down()));
    connect(buttonPriority2Up,     SIGNAL(released()), this, SLOT(onButtonPriority2Up()));
    connect(buttonPriority2Down,   SIGNAL(released()), this, SLOT(onButtonPriority2Down()));
    connect(buttonAudio2Up,        SIGNAL(released()), this, SLOT(onButtonAudio2Up()));
    connect(buttonAudio2Down,      SIGNAL(released()), this, SLOT(onButtonAudio2Down()));

    connect(buttonSource3Up,       SIGNAL(released()), this, SLOT(onButtonSource3Up()));
    connect(buttonSource3Down,     SIGNAL(released()), this, SLOT(onButtonSource3Down()));
    connect(buttonDelay3Up,        SIGNAL(released()), this, SLOT(onButtonDelay3Up()));
    connect(buttonDelay3Down,      SIGNAL(released()), this, SLOT(onButtonDelay3Down()));
    connect(buttonPriority3Up,     SIGNAL(released()), this, SLOT(onButtonPriority3Up()));
    connect(buttonPriority3Down,   SIGNAL(released()), this, SLOT(onButtonPriority3Down()));
    connect(buttonAudio3Up,        SIGNAL(released()), this, SLOT(onButtonAudio3Up()));
    connect(buttonAudio3Down,      SIGNAL(released()), this, SLOT(onButtonAudio3Down()));

    connect(buttonSource4Up,       SIGNAL(released()), this, SLOT(onButtonSource4Up()));
    connect(buttonSource4Down,     SIGNAL(released()), this, SLOT(onButtonSource4Down()));
    connect(buttonDelay4Up,        SIGNAL(released()), this, SLOT(onButtonDelay4Up()));
    connect(buttonDelay4Down,      SIGNAL(released()), this, SLOT(onButtonDelay4Down()));
    connect(buttonPriority4Up,     SIGNAL(released()), this, SLOT(onButtonPriority4Up()));
    connect(buttonPriority4Down,   SIGNAL(released()), this, SLOT(onButtonPriority4Down()));
    connect(buttonAudio4Up,        SIGNAL(released()), this, SLOT(onButtonAudio4Up()));
    connect(buttonAudio4Down,      SIGNAL(released()), this, SLOT(onButtonAudio4Down()));

    connect(buttonDefault,         SIGNAL(released()), this, SLOT(onButtonDefault()));
    connect(buttonSave,            SIGNAL(released()), this, SLOT(onButtonSave()));
    connect(buttonClose,           SIGNAL(released()), this, SLOT(reject()));

    msgBox = NULL;
}
TriggerInputDialog::~TriggerInputDialog()
{
}
int TriggerInputDialog::isPriorityRedundant(void)
{
    int ii, rv = 0;
    memset(nPriority, 0, sizeof(nPriority));

         if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "01") == 0) { nPriority[0]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "02") == 0) { nPriority[1]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "03") == 0) { nPriority[2]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "04") == 0) { nPriority[3]++; }

         if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "01") == 0) { nPriority[0]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "02") == 0) { nPriority[1]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "03") == 0) { nPriority[2]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "04") == 0) { nPriority[3]++; }

         if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "01") == 0) { nPriority[0]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "02") == 0) { nPriority[1]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "03") == 0) { nPriority[2]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "04") == 0) { nPriority[3]++; }

         if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "01") == 0) { nPriority[0]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "02") == 0) { nPriority[1]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "03") == 0) { nPriority[2]++; }
    else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "04") == 0) { nPriority[3]++; }

    for(ii = 0; ii < EASTERN_MAXIMUM_PRIORITY; ii++)
    {
        if(nPriority[ii] >= 2)
        {
            qDebug("Notice : %s, nPriority[%d] = %d\n", __func__, ii, nPriority[ii]);
            rv++;
        }
    }

    return rv;
}
void TriggerInputDialog::onButtonSave(void)
{
    int ii;
    if(isPriorityRedundant())
    {
        for(ii = 0; ii < EASTERN_MAXIMUM_PRIORITY; ii++)
        {
            if(nPriority[ii] >= 2)
            {
                break;
            }
        }
        if(msgBox)
        {
            delete msgBox;
            msgBox = NULL;
        }

        msgBox = new TextMessageDialog(tr("PRIORITY REDUNDANT"),
                tr("\t\t%1\n\n%2\n%3\n").arg(tr("WARNING"),tr("Priority is redundant."),tr("Please check priority.")), 2, this);

        msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

        if(msgBox->exec()) { ; }

        delete msgBox;
        msgBox = NULL;

        switch(ii)
        {
            case 0:
            {
                     if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "01") == 0) { buttonPriority1Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "01") == 0) { buttonPriority2Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "01") == 0) { buttonPriority3Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "01") == 0) { buttonPriority4Up->setFocus(); break; }
            }
            case 1:
            {
                     if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "02") == 0) { buttonPriority1Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "02") == 0) { buttonPriority2Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "02") == 0) { buttonPriority3Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "02") == 0) { buttonPriority4Up->setFocus(); break; }
            }
            case 2:
            {
                     if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "03") == 0) { buttonPriority1Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "03") == 0) { buttonPriority2Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "03") == 0) { buttonPriority3Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "03") == 0) { buttonPriority4Up->setFocus(); break; }
            }
            case 3:
            {
                     if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "04") == 0) { buttonPriority1Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "04") == 0) { buttonPriority2Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "04") == 0) { buttonPriority3Up->setFocus(); break; }
                else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "04") == 0) { buttonPriority4Up->setFocus(); break; }
            }
        }
        return;
    }
    QDialog::accept();
}
void TriggerInputDialog::initTriggerInputConfig(void)
{
	buttonSource1Up->setFocus();

	if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "CAM1") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   indexSource1 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "CAM2") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   indexSource1 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "CAM3") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   indexSource1 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "CAM4") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   indexSource1 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "SPLIT1") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); indexSource1 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "SPLIT2") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); indexSource1 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "SPLIT3") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); indexSource1 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "SPLIT4") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); indexSource1 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "SPLIT5") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); indexSource1 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_source, "SPLIT6") == 0) {
		labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); indexSource1 = 10;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "CAM1") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   indexSource2 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "CAM2") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   indexSource2 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "CAM3") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   indexSource2 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "CAM4") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   indexSource2 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "SPLIT1") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); indexSource2 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "SPLIT2") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); indexSource2 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "SPLIT3") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); indexSource2 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "SPLIT4") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); indexSource2 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "SPLIT5") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); indexSource2 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_source, "SPLIT6") == 0) {
		labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); indexSource2 = 10;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "CAM1") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   indexSource3 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "CAM2") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   indexSource3 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "CAM3") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   indexSource3 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "CAM4") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   indexSource3 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "SPLIT1") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); indexSource3 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "SPLIT2") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); indexSource3 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "SPLIT3") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); indexSource3 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "SPLIT4") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); indexSource3 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "SPLIT5") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); indexSource3 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_source, "SPLIT6") == 0) {
		labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); indexSource3 = 10;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "CAM1") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   indexSource4 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "CAM2") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   indexSource4 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "CAM3") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   indexSource4 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "CAM4") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   indexSource4 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "SPLIT1") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); indexSource4 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "SPLIT2") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); indexSource4 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "SPLIT3") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); indexSource4 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "SPLIT4") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); indexSource4 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "SPLIT5") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); indexSource4 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_source, "SPLIT6") == 0) {
		labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); indexSource4 = 10;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "0SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  indexDelay1 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "1SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  indexDelay1 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "2SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  indexDelay1 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "3SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  indexDelay1 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "4SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  indexDelay1 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "5SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  indexDelay1 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "6SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  indexDelay1 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "7SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  indexDelay1 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "8SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  indexDelay1 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "9SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  indexDelay1 = 10;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "10SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); indexDelay1 = 11;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "11SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); indexDelay1 = 12;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "12SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); indexDelay1 = 13;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "13SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); indexDelay1 = 14;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "14SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); indexDelay1 = 15;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "15SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); indexDelay1 = 16;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "16SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); indexDelay1 = 17;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "17SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); indexDelay1 = 18;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "18SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); indexDelay1 = 19;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "19SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); indexDelay1 = 20;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger1_delay, "20SEC") == 0) {
		labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); indexDelay1 = 21;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "0SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  indexDelay2 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "1SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  indexDelay2 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "2SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  indexDelay2 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "3SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  indexDelay2 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "4SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  indexDelay2 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "5SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  indexDelay2 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "6SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  indexDelay2 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "7SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  indexDelay2 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "8SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  indexDelay2 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "9SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  indexDelay2 = 10;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "10SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); indexDelay2 = 11;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "11SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); indexDelay2 = 12;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "12SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); indexDelay2 = 13;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "13SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); indexDelay2 = 14;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "14SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); indexDelay2 = 15;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "15SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); indexDelay2 = 16;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "16SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); indexDelay2 = 17;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "17SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); indexDelay2 = 18;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "18SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); indexDelay2 = 19;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "19SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); indexDelay2 = 20;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger2_delay, "20SEC") == 0) {
		labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); indexDelay2 = 21;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "0SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  indexDelay3 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "1SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  indexDelay3 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "2SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  indexDelay3 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "3SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  indexDelay3 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "4SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  indexDelay3 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "5SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  indexDelay3 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "6SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  indexDelay3 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "7SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  indexDelay3 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "8SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  indexDelay3 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "9SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  indexDelay3 = 10;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "10SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); indexDelay3 = 11;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "11SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); indexDelay3 = 12;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "12SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); indexDelay3 = 13;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "13SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); indexDelay3 = 14;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "14SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); indexDelay3 = 15;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "15SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); indexDelay3 = 16;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "16SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); indexDelay3 = 17;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "17SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); indexDelay3 = 18;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "18SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); indexDelay3 = 19;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "19SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); indexDelay3 = 20;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger3_delay, "20SEC") == 0) {
		labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); indexDelay3 = 21;
	}

	if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "0SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  indexDelay4 = 1;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "1SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  indexDelay4 = 2;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "2SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  indexDelay4 = 3;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "3SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  indexDelay4 = 4;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "4SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  indexDelay4 = 5;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "5SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  indexDelay4 = 6;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "6SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  indexDelay4 = 7;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "7SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  indexDelay4 = 8;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "8SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  indexDelay4 = 9;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "9SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  indexDelay4 = 10;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "10SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); indexDelay4 = 11;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "11SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); indexDelay4 = 12;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "12SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); indexDelay4 = 13;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "13SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); indexDelay4 = 14;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "14SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); indexDelay4 = 15;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "15SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); indexDelay4 = 16;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "16SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); indexDelay4 = 17;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "17SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); indexDelay4 = 18;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "18SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); indexDelay4 = 19;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "19SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); indexDelay4 = 20;
	} else if(utils_cfg_cmp_item(DeviceCfg.trigger4_delay, "20SEC") == 0) {
		labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); indexDelay4 = 21;
	}

    if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "01") == 0) {
        labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); indexPriority1 = 1;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "02") == 0) {
        labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); indexPriority1 = 2;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "03") == 0) {
        labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); indexPriority1 = 3;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger1_priority, "04") == 0) {
        labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); indexPriority1 = 4;
    }

    if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "01") == 0) {
        labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); indexPriority2 = 1;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "02") == 0) {
        labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); indexPriority2 = 2;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "03") == 0) {
        labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); indexPriority2 = 3;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger2_priority, "04") == 0) {
        labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); indexPriority2 = 4;
    }

    if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "01") == 0) {
        labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); indexPriority3 = 1;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "02") == 0) {
        labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); indexPriority3 = 2;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "03") == 0) {
        labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); indexPriority3 = 3;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger3_priority, "04") == 0) {
        labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); indexPriority3 = 4;
    }

    if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "01") == 0) {
        labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); indexPriority4 = 1;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "02") == 0) {
        labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); indexPriority4 = 2;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "03") == 0) {
        labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); indexPriority4 = 3;
    } else if(utils_cfg_cmp_item(DeviceCfg.trigger4_priority, "04") == 0) {
        labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); indexPriority4 = 4;
    }

    //audio label init
    if(utils_cfg_cmp_item(DeviceCfg.trigger1_audio, "MUTE") == 0 )
    {
        labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));    triggerAudio1 = 0;
    }
    else
    {
        labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));  triggerAudio1 = 1;
    }

    if(utils_cfg_cmp_item(DeviceCfg.trigger2_audio, "MUTE") == 0 )
    {
        labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));    triggerAudio2 = 0;
    }
    else
    {
        labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));  triggerAudio2 = 1;
    }

    if(utils_cfg_cmp_item(DeviceCfg.trigger3_audio, "MUTE") == 0 )
    {
        labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));    triggerAudio3 = 0;
    }
    else
    {
        labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));  triggerAudio3 = 1;
    }

    if(utils_cfg_cmp_item(DeviceCfg.trigger4_audio, "MUTE") == 0 )
    {
        labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));    triggerAudio4 = 0;
    }
    else
    {
        labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));  triggerAudio4 = 1;
    }
}
void TriggerInputDialog::onButtonDefault()
{
    labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));     indexSource1 = 1;
	utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM1");

    labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));     indexSource2 = 2;
	utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM2");

    labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));     indexSource3 = 3;
	utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM3");

    labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));     indexSource4 = 4;
	utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM4");

    labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));       indexDelay1 = 3;
	utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "2SEC");

    labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));       indexDelay2 = 3;
	utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "2SEC");

    labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));       indexDelay3 = 3;
	utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "2SEC");

    labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));       indexDelay4 = 3;
	utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "2SEC");

    labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("1")));     indexPriority1 = 1;
	utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "01");

    labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("2")));     indexPriority2 = 2;
	utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "02");

    labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("3")));     indexPriority3 = 3;
	utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "03");

    labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("4")));     indexPriority4 = 4;
	utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "04");

    labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));      triggerAudio1=1;
    utils_cfg_cpy_item(DeviceCfg.trigger1_audio, "OUTPUT");

    labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));      triggerAudio2=1;
    utils_cfg_cpy_item(DeviceCfg.trigger2_audio, "OUTPUT");

    labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));      triggerAudio3=1;
    utils_cfg_cpy_item(DeviceCfg.trigger3_audio, "OUTPUT");

    labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));      triggerAudio4=1;
    utils_cfg_cpy_item(DeviceCfg.trigger4_audio, "OUTPUT");
}
void TriggerInputDialog::onButtonSource1Up()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource1 >= 4) { indexSource1 = 0; }
	#else
	if(indexSource1 >= 10) { indexSource1 = 0; }
	#endif

	switch(++indexSource1)
	{
		case  1: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM1");   break; }
		case  2: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM2");   break; }
		case  3: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM3");   break; }
		case  4: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT1"); break; }
		case  6: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT2"); break; }
		case  7: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT3"); break; }
		case  8: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT4"); break; }
		case  9: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT5"); break; }
		case 10: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonSource1Down()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource1 <= 1) { indexSource1 = 5; }
	#else
	if(indexSource1 <= 1) { indexSource1 = 11; }
	#endif

	switch(--indexSource1)
	{
		case  1: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM1");   break; }
		case  2: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM2");   break; }
		case  3: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM3");   break; }
		case  4: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger1_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT1"); break; }
		case  6: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT2"); break; }
		case  7: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT3"); break; }
		case  8: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT4"); break; }
		case  9: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT5"); break; }
		case 10: { labelSource1->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger1_source, "SPLIT6"); break; }
		#endif
	}

}
void TriggerInputDialog::onButtonSource2Up()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource2 >= 4) { indexSource2 = 0; }
	#else
	if(indexSource2 >= 10) { indexSource2 = 0; }
	#endif

	switch(++indexSource2)
	{
		case  1: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM1");   break; }
		case  2: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM2");   break; }
		case  3: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM3");   break; }
		case  4: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT1"); break; }
		case  6: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT2"); break; }
		case  7: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT3"); break; }
		case  8: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT4"); break; }
		case  9: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT5"); break; }
		case 10: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonSource2Down()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource2 <= 1) { indexSource2 = 5; }
	#else
	if(indexSource2 <= 1) { indexSource2 = 11; }
	#endif

	switch(--indexSource2)
	{
		case  1: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM1");   break; }
		case  2: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM2");   break; }
		case  3: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM3");   break; }
		case  4: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger2_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT1"); break; }
		case  6: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT2"); break; }
		case  7: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT3"); break; }
		case  8: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT4"); break; }
		case  9: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT5"); break; }
		case 10: { labelSource2->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger2_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonSource3Up()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource3 >= 4) { indexSource3 = 0; }
	#else
	if(indexSource3 >= 10) { indexSource3 = 0; }
	#endif

	switch(++indexSource3)
	{
		case  1: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM1");   break; }
		case  2: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM2");   break; }
		case  3: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM3");   break; }
		case  4: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT1"); break; }
		case  6: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT2"); break; }
		case  7: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT3"); break; }
		case  8: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT4"); break; }
		case  9: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT5"); break; }
		case 10: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonSource3Down()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource3 <= 1) { indexSource3 = 5; }
	#else
	if(indexSource3 <= 1) { indexSource3 = 11; }
	#endif

	switch(--indexSource3)
	{
		case  1: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM1");   break; }
		case  2: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM2");   break; }
		case  3: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM3");   break; }
		case  4: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger3_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT1"); break; }
		case  6: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT2"); break; }
		case  7: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT3"); break; }
		case  8: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT4"); break; }
		case  9: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT5"); break; }
		case 10: { labelSource3->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger3_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonSource4Up()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource4 >= 4) { indexSource4 = 0; }
	#else
	if(indexSource4 >= 10) { indexSource4 = 0; }
	#endif

	switch(++indexSource4)
	{
		case  1: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM1");   break; }
		case  2: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM2");   break; }
		case  3: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM3");   break; }
		case  4: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT1"); break; }
		case  6: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT2"); break; }
		case  7: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT3"); break; }
		case  8: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT4"); break; }
		case  9: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT5"); break; }
		case 10: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonSource4Down()
{
	#if 1 // jungyver [16/12/19]
	if(indexSource4 <= 1) { indexSource4 = 5; }
	#else
	if(indexSource4 <= 1) { indexSource4 = 11; }
	#endif

	switch(--indexSource4)
	{
		case  1: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 1")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM1");   break; }
		case  2: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 2")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM2");   break; }
		case  3: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 3")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM3");   break; }
		case  4: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("CAM 4")));   utils_cfg_cpy_item(DeviceCfg.trigger4_source, "CAM4");   break; }
		#if 0 // jungyver [16/12/19]
		case  5: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 1"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT1"); break; }
		case  6: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 2"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT2"); break; }
		case  7: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 3"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT3"); break; }
		case  8: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 4"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT4"); break; }
		case  9: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 5"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT5"); break; }
		case 10: { labelSource4->setText(tr("%1\n%2").arg(tr("Source"), tr("Split 6"))); utils_cfg_cpy_item(DeviceCfg.trigger4_source, "SPLIT6"); break; }
		#endif
	}
}
void TriggerInputDialog::onButtonDelay1Up()
{
	if(indexDelay1 >= 21) { indexDelay1 = 0; }

	switch(++indexDelay1)
	{
		case  1: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "0SEC");  break; }
		case  2: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "1SEC");  break; }
		case  3: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "2SEC");  break; }
		case  4: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "3SEC");  break; }
		case  5: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "4SEC");  break; }
		case  6: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "5SEC");  break; }
		case  7: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "6SEC");  break; }
		case  8: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "7SEC");  break; }
		case  9: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "8SEC");  break; }
		case 10: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "9SEC");  break; }
		case 11: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "10SEC"); break; }
		case 12: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "11SEC"); break; }
		case 13: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "12SEC"); break; }
		case 14: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "13SEC"); break; }
		case 15: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "14SEC"); break; }
		case 16: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "15SEC"); break; }
		case 17: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "16SEC"); break; }
		case 18: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "17SEC"); break; }
		case 19: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "18SEC"); break; }
		case 20: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "19SEC"); break; }
		case 21: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay1Down()
{
	if(indexDelay1 <= 1) { indexDelay1 = 22; }

	switch(--indexDelay1)
	{
		case  1: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "0SEC");  break; }
		case  2: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "1SEC");  break; }
		case  3: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "2SEC");  break; }
		case  4: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "3SEC");  break; }
		case  5: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "4SEC");  break; }
		case  6: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "5SEC");  break; }
		case  7: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "6SEC");  break; }
		case  8: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "7SEC");  break; }
		case  9: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "8SEC");  break; }
		case 10: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "9SEC");  break; }
		case 11: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "10SEC"); break; }
		case 12: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "11SEC"); break; }
		case 13: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "12SEC"); break; }
		case 14: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "13SEC"); break; }
		case 15: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "14SEC"); break; }
		case 16: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "15SEC"); break; }
		case 17: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "16SEC"); break; }
		case 18: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "17SEC"); break; }
		case 19: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "18SEC"); break; }
		case 20: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "19SEC"); break; }
		case 21: { labelDelay1->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger1_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay2Up()
{
	if(indexDelay2 >= 21) { indexDelay2 = 0; }

	switch(++indexDelay2)
	{
		case  1: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "0SEC");  break; }
		case  2: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "1SEC");  break; }
		case  3: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "2SEC");  break; }
		case  4: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "3SEC");  break; }
		case  5: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "4SEC");  break; }
		case  6: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "5SEC");  break; }
		case  7: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "6SEC");  break; }
		case  8: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "7SEC");  break; }
		case  9: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "8SEC");  break; }
		case 10: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "9SEC");  break; }
		case 11: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "10SEC"); break; }
		case 12: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "11SEC"); break; }
		case 13: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "12SEC"); break; }
		case 14: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "13SEC"); break; }
		case 15: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "14SEC"); break; }
		case 16: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "15SEC"); break; }
		case 17: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "16SEC"); break; }
		case 18: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "17SEC"); break; }
		case 19: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "18SEC"); break; }
		case 20: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "19SEC"); break; }
		case 21: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay2Down()
{
	if(indexDelay2 <= 1) { indexDelay2 = 22; }

	switch(--indexDelay2)
	{
		case  1: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "0SEC");  break; }
		case  2: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "1SEC");  break; }
		case  3: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "2SEC");  break; }
		case  4: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "3SEC");  break; }
		case  5: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "4SEC");  break; }
		case  6: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "5SEC");  break; }
		case  7: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "6SEC");  break; }
		case  8: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "7SEC");  break; }
		case  9: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "8SEC");  break; }
		case 10: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "9SEC");  break; }
		case 11: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "10SEC"); break; }
		case 12: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "11SEC"); break; }
		case 13: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "12SEC"); break; }
		case 14: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "13SEC"); break; }
		case 15: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "14SEC"); break; }
		case 16: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "15SEC"); break; }
		case 17: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "16SEC"); break; }
		case 18: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "17SEC"); break; }
		case 19: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "18SEC"); break; }
		case 20: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "19SEC"); break; }
		case 21: { labelDelay2->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger2_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay3Up()
{
	if(indexDelay3 >= 21) { indexDelay3 = 0; }

	switch(++indexDelay3)
	{
		case  1: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "0SEC");  break; }
		case  2: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "1SEC");  break; }
		case  3: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "2SEC");  break; }
		case  4: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "3SEC");  break; }
		case  5: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "4SEC");  break; }
		case  6: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "5SEC");  break; }
		case  7: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "6SEC");  break; }
		case  8: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "7SEC");  break; }
		case  9: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "8SEC");  break; }
		case 10: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "9SEC");  break; }
		case 11: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "10SEC"); break; }
		case 12: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "11SEC"); break; }
		case 13: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "12SEC"); break; }
		case 14: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "13SEC"); break; }
		case 15: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "14SEC"); break; }
		case 16: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "15SEC"); break; }
		case 17: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "16SEC"); break; }
		case 18: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "17SEC"); break; }
		case 19: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "18SEC"); break; }
		case 20: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "19SEC"); break; }
		case 21: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay3Down()
{
	if(indexDelay3 <= 1) { indexDelay3 = 22; }

	switch(--indexDelay3)
	{
		case  1: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "0SEC");  break; }
		case  2: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "1SEC");  break; }
		case  3: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "2SEC");  break; }
		case  4: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "3SEC");  break; }
		case  5: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "4SEC");  break; }
		case  6: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "5SEC");  break; }
		case  7: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "6SEC");  break; }
		case  8: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "7SEC");  break; }
		case  9: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "8SEC");  break; }
		case 10: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "9SEC");  break; }
		case 11: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "10SEC"); break; }
		case 12: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "11SEC"); break; }
		case 13: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "12SEC"); break; }
		case 14: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "13SEC"); break; }
		case 15: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "14SEC"); break; }
		case 16: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "15SEC"); break; }
		case 17: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "16SEC"); break; }
		case 18: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "17SEC"); break; }
		case 19: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "18SEC"); break; }
		case 20: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "19SEC"); break; }
		case 21: { labelDelay3->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger3_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay4Up()
{
	if(indexDelay4 >= 21) { indexDelay4 = 0; }

	switch(++indexDelay4)
	{
		case  1: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "0SEC");  break; }
		case  2: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "1SEC");  break; }
		case  3: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "2SEC");  break; }
		case  4: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "3SEC");  break; }
		case  5: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "4SEC");  break; }
		case  6: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "5SEC");  break; }
		case  7: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "6SEC");  break; }
		case  8: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "7SEC");  break; }
		case  9: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "8SEC");  break; }
		case 10: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "9SEC");  break; }
		case 11: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "10SEC"); break; }
		case 12: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "11SEC"); break; }
		case 13: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "12SEC"); break; }
		case 14: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "13SEC"); break; }
		case 15: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "14SEC"); break; }
		case 16: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "15SEC"); break; }
		case 17: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "16SEC"); break; }
		case 18: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "17SEC"); break; }
		case 19: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "18SEC"); break; }
		case 20: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "19SEC"); break; }
		case 21: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonDelay4Down()
{
	if(indexDelay4 <= 1) { indexDelay4 = 22; }

	switch(--indexDelay4)
	{
		case  1: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("0 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "0SEC");  break; }
		case  2: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("1 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "1SEC");  break; }
		case  3: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("2 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "2SEC");  break; }
		case  4: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("3 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "3SEC");  break; }
		case  5: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("4 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "4SEC");  break; }
		case  6: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("5 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "5SEC");  break; }
		case  7: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("6 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "6SEC");  break; }
		case  8: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("7 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "7SEC");  break; }
		case  9: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("8 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "8SEC");  break; }
		case 10: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("9 sec")));  utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "9SEC");  break; }
		case 11: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("10 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "10SEC"); break; }
		case 12: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("11 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "11SEC"); break; }
		case 13: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("12 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "12SEC"); break; }
		case 14: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("13 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "13SEC"); break; }
		case 15: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("14 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "14SEC"); break; }
		case 16: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("15 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "15SEC"); break; }
		case 17: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("16 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "16SEC"); break; }
		case 18: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("17 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "17SEC"); break; }
		case 19: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("18 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "18SEC"); break; }
		case 20: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("19 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "19SEC"); break; }
		case 21: { labelDelay4->setText(tr("%1\n%2").arg(tr("Delay"), tr("20 sec"))); utils_cfg_cpy_item(DeviceCfg.trigger4_delay, "20SEC"); break; }
	}
}
void TriggerInputDialog::onButtonPriority1Up()
{
	if(indexPriority1 >= 4) { indexPriority1 = 0; }
	switch(++indexPriority1)
	{
		case  1: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "01");   break; }
		case  2: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "02");   break; }
		case  3: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "03");   break; }
		case  4: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority1Down()
{
	if(indexPriority1 <= 1) { indexPriority1 = 5; }
	switch(--indexPriority1)
	{
		case  1: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "01");   break; }
		case  2: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "02");   break; }
		case  3: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "03");   break; }
		case  4: { labelPriority1->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger1_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority2Up()
{
	if(indexPriority2 >= 4) { indexPriority2 = 0; }
	switch(++indexPriority2)
	{
		case  1: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "01");   break; }
		case  2: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "02");   break; }
		case  3: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "03");   break; }
		case  4: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority2Down()
{
	if(indexPriority2 <= 1) { indexPriority2 = 5; }
	switch(--indexPriority2)
	{
		case  1: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "01");   break; }
		case  2: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "02");   break; }
		case  3: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "03");   break; }
		case  4: { labelPriority2->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger2_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority3Up()
{
	if(indexPriority3 >= 4) { indexPriority3 = 0; }
	switch(++indexPriority3)
	{
		case  1: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "01");   break; }
		case  2: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "02");   break; }
		case  3: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "03");   break; }
		case  4: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority3Down()
{
	if(indexPriority3 <= 1) { indexPriority3 = 5; }
	switch(--indexPriority3)
	{
		case  1: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "01");   break; }
		case  2: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "02");   break; }
		case  3: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "03");   break; }
		case  4: { labelPriority3->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger3_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority4Up()
{
	if(indexPriority4 >= 4) { indexPriority4 = 0; }
	switch(++indexPriority4)
	{
		case  1: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "01");   break; }
		case  2: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "02");   break; }
		case  3: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "03");   break; }
		case  4: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonPriority4Down()
{
	if(indexPriority4 <= 1) { indexPriority4 = 5; }
	switch(--indexPriority4)
	{
		case  1: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("1"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "01");   break; }
		case  2: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("2"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "02");   break; }
		case  3: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("3"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "03");   break; }
		case  4: { labelPriority4->setText(tr("%1\n%2").arg(tr("Priority"), tr("4"))); utils_cfg_cpy_item(DeviceCfg.trigger4_priority, "04");   break; }
    }
}
void TriggerInputDialog::onButtonAudio1Up()
{
    triggerAudio1=!triggerAudio1;
    switch(triggerAudio1)
    {
        case 0: { labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger1_audio, "MUTE");   break; }
        case 1: { labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger1_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio1Down()
{
    triggerAudio1=!triggerAudio1;
    switch(triggerAudio1)
    {
        case 0: { labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger1_audio, "MUTE");   break; }
        case 1: { labelAudio1->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger1_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio2Up()
{
    triggerAudio2=!triggerAudio2;
    switch(triggerAudio2)
    {
        case 0: { labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger2_audio, "MUTE");   break; }
        case 1: { labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger2_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio2Down()
{
    triggerAudio2=!triggerAudio2;
    switch(triggerAudio2)
    {
        case 0: { labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger2_audio, "MUTE");   break; }
        case 1: { labelAudio2->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger2_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio3Up()
{
    triggerAudio3=!triggerAudio3;
    switch(triggerAudio3)
    {
        case 0: { labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger3_audio, "MUTE");   break; }
        case 1: { labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger3_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio3Down()
{
    triggerAudio3=!triggerAudio3;
    switch(triggerAudio3)
    {
        case 0: { labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger3_audio, "MUTE");   break; }
        case 1: { labelAudio3->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger3_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio4Up()
{
    triggerAudio4=!triggerAudio4;
    switch(triggerAudio4)
    {
        case 0: { labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger4_audio, "MUTE");   break; }
        case 1: { labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger4_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::onButtonAudio4Down()
{
    triggerAudio4=!triggerAudio4;
    switch(triggerAudio4)
    {
        case 0: { labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Mute")));      utils_cfg_cpy_item(DeviceCfg.trigger4_audio, "MUTE");   break; }
        case 1: { labelAudio4->setText(tr("%1\n%2").arg(tr("Audio"), tr("Output")));    utils_cfg_cpy_item(DeviceCfg.trigger4_audio, "OUTPUT"); break; }
    }
}
void TriggerInputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
                 if(buttonSource1Up->hasFocus())               { buttonDefault->setFocus();             }
            else if(buttonSource1Down->hasFocus())             { buttonSource1Up->setFocus();           }
            else if(buttonPriority1Up->hasFocus())             { buttonSource1Down->setFocus();         }
            else if(buttonPriority1Down->hasFocus())           { buttonPriority1Up->setFocus();         }
            else if(buttonDelay1Up->hasFocus())                { buttonDefault->setFocus();             }
            else if(buttonDelay1Down->hasFocus())              { buttonDelay1Up->setFocus();            }
            else if(buttonAudio1Up->hasFocus())                { buttonDelay1Down->setFocus();          }
            else if(buttonAudio1Down->hasFocus())              { buttonAudio1Up->setFocus();            }

            else if(buttonSource2Up->hasFocus())               { buttonSave->setFocus();                }
            else if(buttonSource2Down->hasFocus())             { buttonSource2Up->setFocus();           }
            else if(buttonPriority2Up->hasFocus())             { buttonSource2Down->setFocus();         }
            else if(buttonPriority2Down->hasFocus())           { buttonPriority2Up->setFocus();         }
            else if(buttonDelay2Up->hasFocus())                { buttonClose->setFocus();               }
            else if(buttonDelay2Down->hasFocus())              { buttonDelay2Up->setFocus();            }
            else if(buttonAudio2Up->hasFocus())                { buttonDelay2Down->setFocus();          }
            else if(buttonAudio2Down->hasFocus())              { buttonAudio2Up->setFocus();            }

            else if(buttonSource3Up->hasFocus())               { buttonPriority1Down->setFocus();       }
            else if(buttonSource3Down->hasFocus())             { buttonSource3Up->setFocus();           }
            else if(buttonPriority3Up->hasFocus())             { buttonSource3Down->setFocus();         }
            else if(buttonPriority3Down->hasFocus())           { buttonPriority3Up->setFocus();         }
            else if(buttonDelay3Up->hasFocus())                { buttonAudio1Down->setFocus();          }
            else if(buttonDelay3Down->hasFocus())              { buttonDelay3Up->setFocus();            }
            else if(buttonAudio3Up->hasFocus())                { buttonDelay3Down->setFocus();          }
            else if(buttonAudio3Down->hasFocus())              { buttonAudio3Up->setFocus();            }

            else if(buttonSource4Up->hasFocus())               { buttonPriority2Down->setFocus();       }
            else if(buttonSource4Down->hasFocus())             { buttonSource4Up->setFocus();           }
            else if(buttonPriority4Up->hasFocus())             { buttonSource4Down->setFocus();         }
            else if(buttonPriority4Down->hasFocus())           { buttonPriority4Up->setFocus();         }
            else if(buttonDelay4Up->hasFocus())                { buttonAudio2Down->setFocus();          }
            else if(buttonDelay4Down->hasFocus())              { buttonDelay4Up->setFocus();            }
            else if(buttonAudio4Up->hasFocus())                { buttonDelay4Down->setFocus();          }
            else if(buttonAudio4Down->hasFocus())              { buttonAudio4Up->setFocus();            }

            else if(buttonDefault->hasFocus())                 { buttonPriority3Down->setFocus();       }
            else if(buttonSave->hasFocus())                    { buttonPriority4Down->setFocus();       }
            else if(buttonClose->hasFocus())                   { buttonAudio4Down->setFocus();          }

            return;
        }
        case Qt::Key_Down:
        {
                 if(buttonSource1Up->hasFocus())               { buttonSource1Down->setFocus();         }
            else if(buttonSource1Down->hasFocus())             { buttonPriority1Up->setFocus();         }
            else if(buttonPriority1Up->hasFocus())             { buttonPriority1Down->setFocus();       }
            else if(buttonPriority1Down->hasFocus())           { buttonSource3Up->setFocus();           }
            else if(buttonDelay1Up->hasFocus())                { buttonDelay1Down->setFocus();          }
            else if(buttonDelay1Down->hasFocus())              { buttonAudio1Up->setFocus();            }
            else if(buttonAudio1Up->hasFocus())                { buttonAudio1Down->setFocus();          }
            else if(buttonAudio1Down->hasFocus())              { buttonDelay3Up->setFocus();            }

            else if(buttonSource2Up->hasFocus())               { buttonSource2Down->setFocus();         }
            else if(buttonSource2Down->hasFocus())             { buttonPriority2Up->setFocus();         }
            else if(buttonPriority2Up->hasFocus())             { buttonPriority2Down->setFocus();       }
            else if(buttonPriority2Down->hasFocus())           { buttonSource4Up->setFocus();           }
            else if(buttonDelay2Up->hasFocus())                { buttonDelay2Down->setFocus();          }
            else if(buttonDelay2Down->hasFocus())              { buttonAudio2Up->setFocus();            }
            else if(buttonAudio2Up->hasFocus())                { buttonAudio2Down->setFocus();          }
            else if(buttonAudio2Down->hasFocus())              { buttonDelay4Up->setFocus();            }

            else if(buttonSource3Up->hasFocus())               { buttonSource3Down->setFocus();         }
            else if(buttonSource3Down->hasFocus())             { buttonPriority3Up->setFocus();         }
            else if(buttonPriority3Up->hasFocus())             { buttonPriority3Down->setFocus();       }
            else if(buttonPriority3Down->hasFocus())           { buttonDefault->setFocus();             }
            else if(buttonDelay3Up->hasFocus())                { buttonDelay3Down->setFocus();          }
            else if(buttonDelay3Down->hasFocus())              { buttonAudio3Up->setFocus();            }
            else if(buttonAudio3Up->hasFocus())                { buttonAudio3Down->setFocus();          }
            else if(buttonAudio3Down->hasFocus())              { buttonDefault->setFocus();             }

            else if(buttonSource4Up->hasFocus())               { buttonSource4Down->setFocus();         }
            else if(buttonSource4Down->hasFocus())             { buttonPriority4Up->setFocus();         }
            else if(buttonPriority4Up->hasFocus())             { buttonPriority4Down->setFocus();       }
            else if(buttonPriority4Down->hasFocus())           { buttonSave->setFocus();                }
            else if(buttonDelay4Up->hasFocus())                { buttonDelay4Down->setFocus();          }
            else if(buttonDelay4Down->hasFocus())              { buttonAudio4Up->setFocus();            }
            else if(buttonAudio4Up->hasFocus())                { buttonAudio4Down->setFocus();          }
            else if(buttonAudio4Down->hasFocus())              { buttonClose->setFocus();               }

            else if(buttonDefault->hasFocus())                 { buttonSource1Up->setFocus();           }
            else if(buttonSave->hasFocus())                    { buttonSource2Up->setFocus();           }
            else if(buttonClose->hasFocus())                   { buttonDelay2Up->setFocus();            }

            return;
        }
        case Qt::Key_Left:
        {
                 if(buttonSource1Up->hasFocus())               { buttonDelay2Up->setFocus();            }
            else if(buttonSource1Down->hasFocus())             { buttonDelay2Down->setFocus();          }
            else if(buttonPriority1Up->hasFocus())             { buttonAudio2Up->setFocus();            }
            else if(buttonPriority1Down->hasFocus())           { buttonAudio2Down->setFocus();          }
            else if(buttonDelay1Up->hasFocus())                { buttonSource1Up->setFocus();           }
            else if(buttonDelay1Down->hasFocus())              { buttonSource1Down->setFocus();         }
            else if(buttonAudio1Up->hasFocus())                { buttonPriority1Up->setFocus();         }
            else if(buttonAudio1Down->hasFocus())              { buttonPriority1Down->setFocus();       }

            else if(buttonSource2Up->hasFocus())               { buttonDelay1Up->setFocus();            }
            else if(buttonSource2Down->hasFocus())             { buttonDelay1Down->setFocus();          }
            else if(buttonPriority2Up->hasFocus())             { buttonAudio1Up->setFocus();            }
            else if(buttonPriority2Down->hasFocus())           { buttonAudio1Down->setFocus();          }
            else if(buttonDelay2Up->hasFocus())                { buttonSource2Up->setFocus();           }
            else if(buttonDelay2Down->hasFocus())              { buttonSource2Down->setFocus();         }
            else if(buttonAudio2Up->hasFocus())                { buttonPriority2Up->setFocus();         }
            else if(buttonAudio2Down->hasFocus())              { buttonPriority2Down->setFocus();       }

            else if(buttonSource3Up->hasFocus())               { buttonDelay4Up->setFocus();            }
            else if(buttonSource3Down->hasFocus())             { buttonDelay4Down->setFocus();          }
            else if(buttonPriority3Up->hasFocus())             { buttonAudio4Up->setFocus();            }
            else if(buttonPriority3Down->hasFocus())           { buttonAudio4Down->setFocus();          }
            else if(buttonDelay3Up->hasFocus())                { buttonSource3Up->setFocus();           }
            else if(buttonDelay3Down->hasFocus())              { buttonSource3Down->setFocus();         }
            else if(buttonAudio3Up->hasFocus())                { buttonPriority3Up->setFocus();         }
            else if(buttonAudio3Down->hasFocus())              { buttonPriority3Down->setFocus();       }

            else if(buttonSource4Up->hasFocus())               { buttonDelay3Up->setFocus();            }
            else if(buttonSource4Down->hasFocus())             { buttonDelay3Down->setFocus();          }
            else if(buttonPriority4Up->hasFocus())             { buttonAudio3Up->setFocus();            }
            else if(buttonPriority4Down->hasFocus())           { buttonAudio3Down->setFocus();          }
            else if(buttonDelay4Up->hasFocus())                { buttonSource4Up->setFocus();           }
            else if(buttonDelay4Down->hasFocus())              { buttonSource4Down->setFocus();         }
            else if(buttonAudio4Up->hasFocus())                { buttonPriority4Up->setFocus();         }
            else if(buttonAudio4Down->hasFocus())              { buttonPriority4Down->setFocus();       }

            else if(buttonDefault->hasFocus())                 { buttonClose->setFocus();               }
            else if(buttonSave->hasFocus())                    { buttonDefault->setFocus();             }
            else if(buttonClose->hasFocus())                   { buttonSave->setFocus();                }

            return;
        }
        case Qt::Key_Right:
        {
                 if(buttonSource1Up->hasFocus())               { buttonDelay1Up->setFocus();            }
            else if(buttonSource1Down->hasFocus())             { buttonDelay1Down->setFocus();          }
            else if(buttonPriority1Up->hasFocus())             { buttonAudio1Up->setFocus();            }
            else if(buttonPriority1Down->hasFocus())           { buttonAudio1Down->setFocus();          }
            else if(buttonDelay1Up->hasFocus())                { buttonSource2Up->setFocus();           }
            else if(buttonDelay1Down->hasFocus())              { buttonSource2Down->setFocus();         }
            else if(buttonAudio1Up->hasFocus())                { buttonPriority2Up->setFocus();         }
            else if(buttonAudio1Down->hasFocus())              { buttonPriority2Down->setFocus();       }

            else if(buttonSource2Up->hasFocus())               { buttonDelay2Up->setFocus();            }
            else if(buttonSource2Down->hasFocus())             { buttonDelay2Down->setFocus();          }
            else if(buttonPriority2Up->hasFocus())             { buttonAudio2Up->setFocus();            }
            else if(buttonPriority2Down->hasFocus())           { buttonAudio2Down->setFocus();          }
            else if(buttonDelay2Up->hasFocus())                { buttonSource1Up->setFocus();           }
            else if(buttonDelay2Down->hasFocus())              { buttonSource1Down->setFocus();         }
            else if(buttonAudio2Up->hasFocus())                { buttonPriority1Up->setFocus();         }
            else if(buttonAudio2Down->hasFocus())              { buttonPriority1Down->setFocus();       }

            else if(buttonSource3Up->hasFocus())               { buttonDelay3Up->setFocus();            }
            else if(buttonSource3Down->hasFocus())             { buttonDelay3Down->setFocus();          }
            else if(buttonPriority3Up->hasFocus())             { buttonAudio3Up->setFocus();            }
            else if(buttonPriority3Down->hasFocus())           { buttonAudio3Down->setFocus();          }
            else if(buttonDelay3Up->hasFocus())                { buttonSource4Up->setFocus();           }
            else if(buttonDelay3Down->hasFocus())              { buttonSource4Down->setFocus();         }
            else if(buttonAudio3Up->hasFocus())                { buttonPriority4Up->setFocus();         }
            else if(buttonAudio3Down->hasFocus())              { buttonPriority4Down->setFocus();       }

            else if(buttonSource4Up->hasFocus())               { buttonDelay4Up->setFocus();            }
            else if(buttonSource4Down->hasFocus())             { buttonDelay4Down->setFocus();          }
            else if(buttonPriority4Up->hasFocus())             { buttonAudio4Up->setFocus();            }
            else if(buttonPriority4Down->hasFocus())           { buttonAudio4Down->setFocus();          }
            else if(buttonDelay4Up->hasFocus())                { buttonSource3Up->setFocus();           }
            else if(buttonDelay4Down->hasFocus())              { buttonSource3Down->setFocus();         }
            else if(buttonAudio4Up->hasFocus())                { buttonPriority3Up->setFocus();         }
            else if(buttonAudio4Down->hasFocus())              { buttonPriority3Down->setFocus();       }

            else if(buttonDefault->hasFocus())                 { buttonSave->setFocus();                }
            else if(buttonSave->hasFocus())                    { buttonClose->setFocus();               }
            else if(buttonClose->hasFocus())                   { buttonDefault->setFocus();             }

            return;
        }
        case Qt::Key_Enter:
        {
            break;
        }
        case Qt::Key_Escape:
        {
            reject();
            return;
        }
        default:
        {
            return;
        }
    }

    QDialog::keyPressEvent(event);
}
void TriggerInputDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
