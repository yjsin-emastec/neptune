#include <QtGui>
#include "triggerinputdialog.h"
#include "main/mainglobal.h"

TriggerInputDialog::TriggerInputDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::TriggerInputDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        labelTrigger[0] = ui720.labelTrigger1;
        labelTrigger[1] = ui720.labelTrigger2;
        labelTrigger[2] = ui720.labelTrigger3;
        labelTrigger[3] = ui720.labelTrigger4;
        labelTrigger[4] = ui720.labelTrigger5;
        labelTrigger[5] = ui720.labelTrigger6;
        labelTrigger[6] = ui720.labelTrigger7;
        labelTrigger[7] = ui720.labelTrigger8;

        buttonSourceUp[0] = ui720.buttonSourceUp1;
        buttonSourceUp[1] = ui720.buttonSourceUp2;
        buttonSourceUp[2] = ui720.buttonSourceUp3;
        buttonSourceUp[3] = ui720.buttonSourceUp4;
        buttonSourceUp[4] = ui720.buttonSourceUp5;
        buttonSourceUp[5] = ui720.buttonSourceUp6;
        buttonSourceUp[6] = ui720.buttonSourceUp7;
        buttonSourceUp[7] = ui720.buttonSourceUp8;

        buttonSourceDn[0] = ui720.buttonSourceDn1;
        buttonSourceDn[1] = ui720.buttonSourceDn2;
        buttonSourceDn[2] = ui720.buttonSourceDn3;
        buttonSourceDn[3] = ui720.buttonSourceDn4;
        buttonSourceDn[4] = ui720.buttonSourceDn5;
        buttonSourceDn[5] = ui720.buttonSourceDn6;
        buttonSourceDn[6] = ui720.buttonSourceDn7;
        buttonSourceDn[7] = ui720.buttonSourceDn8;

        labelSource[0] = ui720.labelSource1;
        labelSource[1] = ui720.labelSource2;
        labelSource[2] = ui720.labelSource3;
        labelSource[3] = ui720.labelSource4;
        labelSource[4] = ui720.labelSource5;
        labelSource[5] = ui720.labelSource6;
        labelSource[6] = ui720.labelSource7;
        labelSource[7] = ui720.labelSource8;

        buttonDelayUp[0] = ui720.buttonDelayUp1;
        buttonDelayUp[1] = ui720.buttonDelayUp2;
        buttonDelayUp[2] = ui720.buttonDelayUp3;
        buttonDelayUp[3] = ui720.buttonDelayUp4;
        buttonDelayUp[4] = ui720.buttonDelayUp5;
        buttonDelayUp[5] = ui720.buttonDelayUp6;
        buttonDelayUp[6] = ui720.buttonDelayUp7;
        buttonDelayUp[7] = ui720.buttonDelayUp8;

        buttonDelayDn[0] = ui720.buttonDelayDn1;
        buttonDelayDn[1] = ui720.buttonDelayDn2;
        buttonDelayDn[2] = ui720.buttonDelayDn3;
        buttonDelayDn[3] = ui720.buttonDelayDn4;
        buttonDelayDn[4] = ui720.buttonDelayDn5;
        buttonDelayDn[5] = ui720.buttonDelayDn6;
        buttonDelayDn[6] = ui720.buttonDelayDn7;
        buttonDelayDn[7] = ui720.buttonDelayDn8;

        labelDelay[0] = ui720.labelDelay1;
        labelDelay[1] = ui720.labelDelay2;
        labelDelay[2] = ui720.labelDelay3;
        labelDelay[3] = ui720.labelDelay4;
        labelDelay[4] = ui720.labelDelay5;
        labelDelay[5] = ui720.labelDelay6;
        labelDelay[6] = ui720.labelDelay7;
        labelDelay[7] = ui720.labelDelay8;

        buttonPriorityUp[0] = ui720.buttonPriorityUp1;
        buttonPriorityUp[1] = ui720.buttonPriorityUp2;
        buttonPriorityUp[2] = ui720.buttonPriorityUp3;
        buttonPriorityUp[3] = ui720.buttonPriorityUp4;
        buttonPriorityUp[4] = ui720.buttonPriorityUp5;
        buttonPriorityUp[5] = ui720.buttonPriorityUp6;
        buttonPriorityUp[6] = ui720.buttonPriorityUp7;
        buttonPriorityUp[7] = ui720.buttonPriorityUp8;

        buttonPriorityDn[0] = ui720.buttonPriorityDn1;
        buttonPriorityDn[1] = ui720.buttonPriorityDn2;
        buttonPriorityDn[2] = ui720.buttonPriorityDn3;
        buttonPriorityDn[3] = ui720.buttonPriorityDn4;
        buttonPriorityDn[4] = ui720.buttonPriorityDn5;
        buttonPriorityDn[5] = ui720.buttonPriorityDn6;
        buttonPriorityDn[6] = ui720.buttonPriorityDn7;
        buttonPriorityDn[7] = ui720.buttonPriorityDn8;

        labelPriority[0] = ui720.labelPriority1;
        labelPriority[1] = ui720.labelPriority2;
        labelPriority[2] = ui720.labelPriority3;
        labelPriority[3] = ui720.labelPriority4;
        labelPriority[4] = ui720.labelPriority5;
        labelPriority[5] = ui720.labelPriority6;
        labelPriority[6] = ui720.labelPriority7;
        labelPriority[7] = ui720.labelPriority8;

        buttonAudioUp[0] = ui720.buttonAudioUp1;
        buttonAudioUp[1] = ui720.buttonAudioUp2;
        buttonAudioUp[2] = ui720.buttonAudioUp3;
        buttonAudioUp[3] = ui720.buttonAudioUp4;
        buttonAudioUp[4] = ui720.buttonAudioUp5;
        buttonAudioUp[5] = ui720.buttonAudioUp6;
        buttonAudioUp[6] = ui720.buttonAudioUp7;
        buttonAudioUp[7] = ui720.buttonAudioUp8;

        buttonAudioDn[0] = ui720.buttonAudioDn1;
        buttonAudioDn[1] = ui720.buttonAudioDn2;
        buttonAudioDn[2] = ui720.buttonAudioDn3;
        buttonAudioDn[3] = ui720.buttonAudioDn4;
        buttonAudioDn[4] = ui720.buttonAudioDn5;
        buttonAudioDn[5] = ui720.buttonAudioDn6;
        buttonAudioDn[6] = ui720.buttonAudioDn7;
        buttonAudioDn[7] = ui720.buttonAudioDn8;

        labelAudio[0] = ui720.labelAudio1;
        labelAudio[1] = ui720.labelAudio2;
        labelAudio[2] = ui720.labelAudio3;
        labelAudio[3] = ui720.labelAudio4;
        labelAudio[4] = ui720.labelAudio5;
        labelAudio[5] = ui720.labelAudio6;
        labelAudio[6] = ui720.labelAudio7;
        labelAudio[7] = ui720.labelAudio8;

        labelSourceTitle = ui720.labelSource;
        labelDelayTitle = ui720.labelDelay;
        labelPriorityTitle = ui720.labelPriority;
        labelAudioTitle = ui720.labelAudio;

        buttonDefault = ui720.buttonDefault;
        buttonSave = ui720.buttonSave;
        buttonClose = ui720.buttonClose;

        for( int i=0; i<NUMOFCH; i++)
        {
            buttonSourceUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonSourceUp[i]->setIconSize(QSize(40,40));
            buttonSourceDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonSourceDn[i]->setIconSize(QSize(40,40));

            buttonDelayUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonDelayUp[i]->setIconSize(QSize(40,40));
            buttonDelayDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonDelayDn[i]->setIconSize(QSize(40,40));

            buttonPriorityUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonPriorityUp[i]->setIconSize(QSize(40,40));
            buttonPriorityDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonPriorityDn[i]->setIconSize(QSize(40,40));

            buttonAudioUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonAudioUp[i]->setIconSize(QSize(40,40));
            buttonAudioDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonAudioDn[i]->setIconSize(QSize(40,40));
        }

        labelSourceTitle->setStyleSheet("font:45px;");
        labelDelayTitle->setStyleSheet("font:45px;");
        labelPriorityTitle->setStyleSheet("font:45px;");
        labelAudioTitle->setStyleSheet("font:45px;");

        if( utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 )
        {
            buttonDefault->resize(361, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(281, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonDefault->resize(281, 91);

            labelSourceTitle->setStyleSheet("font:40px;");
            labelDelayTitle->setStyleSheet("font:40px;");
            labelPriorityTitle->setStyleSheet("font:40px;");
            labelAudioTitle->setStyleSheet("font:40px;");
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0 )
        {
            buttonDefault->resize(241, 91);
        }
    }
    else
    {
        Ui::TriggerInputDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        labelTrigger[0] = ui1080.labelTrigger1;
        labelTrigger[1] = ui1080.labelTrigger2;
        labelTrigger[2] = ui1080.labelTrigger3;
        labelTrigger[3] = ui1080.labelTrigger4;
        labelTrigger[4] = ui1080.labelTrigger5;
        labelTrigger[5] = ui1080.labelTrigger6;
        labelTrigger[6] = ui1080.labelTrigger7;
        labelTrigger[7] = ui1080.labelTrigger8;

        buttonSourceUp[0] = ui1080.buttonSourceUp1;
        buttonSourceUp[1] = ui1080.buttonSourceUp2;
        buttonSourceUp[2] = ui1080.buttonSourceUp3;
        buttonSourceUp[3] = ui1080.buttonSourceUp4;
        buttonSourceUp[4] = ui1080.buttonSourceUp5;
        buttonSourceUp[5] = ui1080.buttonSourceUp6;
        buttonSourceUp[6] = ui1080.buttonSourceUp7;
        buttonSourceUp[7] = ui1080.buttonSourceUp8;

        buttonSourceDn[0] = ui1080.buttonSourceDn1;
        buttonSourceDn[1] = ui1080.buttonSourceDn2;
        buttonSourceDn[2] = ui1080.buttonSourceDn3;
        buttonSourceDn[3] = ui1080.buttonSourceDn4;
        buttonSourceDn[4] = ui1080.buttonSourceDn5;
        buttonSourceDn[5] = ui1080.buttonSourceDn6;
        buttonSourceDn[6] = ui1080.buttonSourceDn7;
        buttonSourceDn[7] = ui1080.buttonSourceDn8;

        labelSource[0] = ui1080.labelSource1;
        labelSource[1] = ui1080.labelSource2;
        labelSource[2] = ui1080.labelSource3;
        labelSource[3] = ui1080.labelSource4;
        labelSource[4] = ui1080.labelSource5;
        labelSource[5] = ui1080.labelSource6;
        labelSource[6] = ui1080.labelSource7;
        labelSource[7] = ui1080.labelSource8;

        buttonDelayUp[0] = ui1080.buttonDelayUp1;
        buttonDelayUp[1] = ui1080.buttonDelayUp2;
        buttonDelayUp[2] = ui1080.buttonDelayUp3;
        buttonDelayUp[3] = ui1080.buttonDelayUp4;
        buttonDelayUp[4] = ui1080.buttonDelayUp5;
        buttonDelayUp[5] = ui1080.buttonDelayUp6;
        buttonDelayUp[6] = ui1080.buttonDelayUp7;
        buttonDelayUp[7] = ui1080.buttonDelayUp8;

        buttonDelayDn[0] = ui1080.buttonDelayDn1;
        buttonDelayDn[1] = ui1080.buttonDelayDn2;
        buttonDelayDn[2] = ui1080.buttonDelayDn3;
        buttonDelayDn[3] = ui1080.buttonDelayDn4;
        buttonDelayDn[4] = ui1080.buttonDelayDn5;
        buttonDelayDn[5] = ui1080.buttonDelayDn6;
        buttonDelayDn[6] = ui1080.buttonDelayDn7;
        buttonDelayDn[7] = ui1080.buttonDelayDn8;

        labelDelay[0] = ui1080.labelDelay1;
        labelDelay[1] = ui1080.labelDelay2;
        labelDelay[2] = ui1080.labelDelay3;
        labelDelay[3] = ui1080.labelDelay4;
        labelDelay[4] = ui1080.labelDelay5;
        labelDelay[5] = ui1080.labelDelay6;
        labelDelay[6] = ui1080.labelDelay7;
        labelDelay[7] = ui1080.labelDelay8;

        buttonPriorityUp[0] = ui1080.buttonPriorityUp1;
        buttonPriorityUp[1] = ui1080.buttonPriorityUp2;
        buttonPriorityUp[2] = ui1080.buttonPriorityUp3;
        buttonPriorityUp[3] = ui1080.buttonPriorityUp4;
        buttonPriorityUp[4] = ui1080.buttonPriorityUp5;
        buttonPriorityUp[5] = ui1080.buttonPriorityUp6;
        buttonPriorityUp[6] = ui1080.buttonPriorityUp7;
        buttonPriorityUp[7] = ui1080.buttonPriorityUp8;

        buttonPriorityDn[0] = ui1080.buttonPriorityDn1;
        buttonPriorityDn[1] = ui1080.buttonPriorityDn2;
        buttonPriorityDn[2] = ui1080.buttonPriorityDn3;
        buttonPriorityDn[3] = ui1080.buttonPriorityDn4;
        buttonPriorityDn[4] = ui1080.buttonPriorityDn5;
        buttonPriorityDn[5] = ui1080.buttonPriorityDn6;
        buttonPriorityDn[6] = ui1080.buttonPriorityDn7;
        buttonPriorityDn[7] = ui1080.buttonPriorityDn8;

        labelPriority[0] = ui1080.labelPriority1;
        labelPriority[1] = ui1080.labelPriority2;
        labelPriority[2] = ui1080.labelPriority3;
        labelPriority[3] = ui1080.labelPriority4;
        labelPriority[4] = ui1080.labelPriority5;
        labelPriority[5] = ui1080.labelPriority6;
        labelPriority[6] = ui1080.labelPriority7;
        labelPriority[7] = ui1080.labelPriority8;

        buttonAudioUp[0] = ui1080.buttonAudioUp1;
        buttonAudioUp[1] = ui1080.buttonAudioUp2;
        buttonAudioUp[2] = ui1080.buttonAudioUp3;
        buttonAudioUp[3] = ui1080.buttonAudioUp4;
        buttonAudioUp[4] = ui1080.buttonAudioUp5;
        buttonAudioUp[5] = ui1080.buttonAudioUp6;
        buttonAudioUp[6] = ui1080.buttonAudioUp7;
        buttonAudioUp[7] = ui1080.buttonAudioUp8;

        buttonAudioDn[0] = ui1080.buttonAudioDn1;
        buttonAudioDn[1] = ui1080.buttonAudioDn2;
        buttonAudioDn[2] = ui1080.buttonAudioDn3;
        buttonAudioDn[3] = ui1080.buttonAudioDn4;
        buttonAudioDn[4] = ui1080.buttonAudioDn5;
        buttonAudioDn[5] = ui1080.buttonAudioDn6;
        buttonAudioDn[6] = ui1080.buttonAudioDn7;
        buttonAudioDn[7] = ui1080.buttonAudioDn8;

        labelAudio[0] = ui1080.labelAudio1;
        labelAudio[1] = ui1080.labelAudio2;
        labelAudio[2] = ui1080.labelAudio3;
        labelAudio[3] = ui1080.labelAudio4;
        labelAudio[4] = ui1080.labelAudio5;
        labelAudio[5] = ui1080.labelAudio6;
        labelAudio[6] = ui1080.labelAudio7;
        labelAudio[7] = ui1080.labelAudio8;

        labelSourceTitle = ui1080.labelSource;
        labelDelayTitle = ui1080.labelDelay;
        labelPriorityTitle = ui1080.labelPriority;
        labelAudioTitle = ui1080.labelAudio;

        buttonDefault = ui1080.buttonDefault;
        buttonSave = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;

        for( int i=0; i<NUMOFCH; i++)
        {
            buttonSourceUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonSourceUp[i]->setIconSize(QSize(70,70));
            buttonSourceDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonSourceDn[i]->setIconSize(QSize(70,70));

            buttonDelayUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonDelayUp[i]->setIconSize(QSize(70,70));
            buttonDelayDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonDelayDn[i]->setIconSize(QSize(70,70));

            buttonPriorityUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonPriorityUp[i]->setIconSize(QSize(70,70));
            buttonPriorityDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonPriorityDn[i]->setIconSize(QSize(70,70));

            buttonAudioUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonAudioUp[i]->setIconSize(QSize(70,70));
            buttonAudioDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonAudioDn[i]->setIconSize(QSize(70,70));
        }

        labelSourceTitle->setStyleSheet("font:70px;");
        labelDelayTitle->setStyleSheet("font:70px;");
        labelPriorityTitle->setStyleSheet("font:70px;");
        labelAudioTitle->setStyleSheet("font:70px;");

        if( utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:50px;");
            }
            buttonDefault->resize(481, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(401, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:48px;");
            }
            buttonDefault->resize(401, 131);

            labelSourceTitle->setStyleSheet("font:60px;");
            labelDelayTitle->setStyleSheet("font:60px;");
            labelPriorityTitle->setStyleSheet("font:60px;");
            labelAudioTitle->setStyleSheet("font:60px;");
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0 )
        {
            buttonDefault->resize(350, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    connect(buttonSourceUp[0],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp1()));
    connect(buttonSourceUp[1],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp2()));
    connect(buttonSourceUp[2],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp3()));
    connect(buttonSourceUp[3],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp4()));
    connect(buttonSourceUp[4],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp5()));
    connect(buttonSourceUp[5],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp6()));
    connect(buttonSourceUp[6],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp7()));
    connect(buttonSourceUp[7],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp8()));

    connect(buttonSourceDn[0],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn1()));
    connect(buttonSourceDn[1],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn2()));
    connect(buttonSourceDn[2],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn3()));
    connect(buttonSourceDn[3],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn4()));
    connect(buttonSourceDn[4],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn5()));
    connect(buttonSourceDn[5],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn6()));
    connect(buttonSourceDn[6],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn7()));
    connect(buttonSourceDn[7],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn8()));

    connect(buttonDelayUp[0],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp1()));
    connect(buttonDelayUp[1],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp2()));
    connect(buttonDelayUp[2],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp3()));
    connect(buttonDelayUp[3],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp4()));
    connect(buttonDelayUp[4],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp5()));
    connect(buttonDelayUp[5],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp6()));
    connect(buttonDelayUp[6],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp7()));
    connect(buttonDelayUp[7],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp8()));

    connect(buttonDelayDn[0],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn1()));
    connect(buttonDelayDn[1],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn2()));
    connect(buttonDelayDn[2],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn3()));
    connect(buttonDelayDn[3],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn4()));
    connect(buttonDelayDn[4],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn5()));
    connect(buttonDelayDn[5],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn6()));
    connect(buttonDelayDn[6],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn7()));
    connect(buttonDelayDn[7],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn8()));

    connect(buttonPriorityUp[0], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp1()));
    connect(buttonPriorityUp[1], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp2()));
    connect(buttonPriorityUp[2], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp3()));
    connect(buttonPriorityUp[3], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp4()));
    connect(buttonPriorityUp[4], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp5()));
    connect(buttonPriorityUp[5], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp6()));
    connect(buttonPriorityUp[6], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp7()));
    connect(buttonPriorityUp[7], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp8()));

    connect(buttonPriorityDn[0], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn1()));
    connect(buttonPriorityDn[1], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn2()));
    connect(buttonPriorityDn[2], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn3()));
    connect(buttonPriorityDn[3], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn4()));
    connect(buttonPriorityDn[4], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn5()));
    connect(buttonPriorityDn[5], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn6()));
    connect(buttonPriorityDn[6], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn7()));
    connect(buttonPriorityDn[7], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn8()));

    connect(buttonAudioUp[0],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp1()));
    connect(buttonAudioUp[1],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp2()));
    connect(buttonAudioUp[2],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp3()));
    connect(buttonAudioUp[3],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp4()));
    connect(buttonAudioUp[4],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp5()));
    connect(buttonAudioUp[5],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp6()));
    connect(buttonAudioUp[6],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp7()));
    connect(buttonAudioUp[7],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp8()));

    connect(buttonAudioDn[0],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn1()));
    connect(buttonAudioDn[1],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn2()));
    connect(buttonAudioDn[2],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn3()));
    connect(buttonAudioDn[3],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn4()));
    connect(buttonAudioDn[4],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn5()));
    connect(buttonAudioDn[5],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn6()));
    connect(buttonAudioDn[6],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn7()));
    connect(buttonAudioDn[7],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn8()));

    connect(buttonSave,          SIGNAL(clicked()), this, SLOT(onButtonSave()));
    connect(buttonClose,         SIGNAL(clicked()), this, SLOT(reject()));
    connect(buttonDefault,       SIGNAL(clicked()), this, SLOT(onButtonDefault()));

    onButtonDefault();
    msgBox=NULL;

    for(int i=0; i<NUMOFCH; i++)
    {
        labelTrigger[i]->setText(QString("%1%2").arg(tr("Trigger"), QString::number(i+1)));
    }
}
TriggerInputDialog::~TriggerInputDialog()
{
}

void TriggerInputDialog::initTriggerInputConfig(void)
{
    buttonSourceDn[0]->setFocus();

    //source init
    QString source[NUMOFCH];
    source[0] = QString(DeviceCfg.trigger1_source);
    source[1] = QString(DeviceCfg.trigger2_source);
    source[2] = QString(DeviceCfg.trigger3_source);
    source[3] = QString(DeviceCfg.trigger4_source);
    source[4] = QString(DeviceCfg.trigger5_source);
    source[5] = QString(DeviceCfg.trigger6_source);
    source[6] = QString(DeviceCfg.trigger7_source);
    source[7] = QString(DeviceCfg.trigger8_source);

    for(int i=0; i<NUMOFCH; i++)
    {
        if( source[i].split("CAM").length() == 2 )
        {
            QStringList strList = source[i].split("CAM");
            infoSource[i] = strList[1].toInt();

            if( (infoSource[i] <= 0) || (infoSource[i] > NUMOFCH) )
            {
                qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid source value";
                infoSource[i] = i+1;
            }
        }
        else
        {
            qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid source config";
            infoSource[i] = i+1;
        }
        updateSourceLabel(i);
    }


    //delay init
    QString delay[NUMOFCH];
    delay[0] = QString(DeviceCfg.trigger1_delay);
    delay[1] = QString(DeviceCfg.trigger2_delay);
    delay[2] = QString(DeviceCfg.trigger3_delay);
    delay[3] = QString(DeviceCfg.trigger4_delay);
    delay[4] = QString(DeviceCfg.trigger5_delay);
    delay[5] = QString(DeviceCfg.trigger6_delay);
    delay[6] = QString(DeviceCfg.trigger7_delay);
    delay[7] = QString(DeviceCfg.trigger8_delay);

    for(int i=0; i<NUMOFCH; i++)
    {
        if( delay[i].split("SEC").length() == 2 )
        {
            QStringList strList = delay[i].split("SEC");
            infoDelay[i] = strList[0].toInt();

            if( infoDelay[i] < 0 || infoDelay[i] > 20 )
            {
                qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid delay value";
                infoDelay[i] = 2;
            }
        }
        else
        {
            qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid delay config";
            infoDelay[i] = 2;
        }
        updateDelayLabel(i);
    }


    //priority init
    int priority[NUMOFCH];
    priority[0] = QString(DeviceCfg.trigger1_priority).toInt();
    priority[1] = QString(DeviceCfg.trigger2_priority).toInt();
    priority[2] = QString(DeviceCfg.trigger3_priority).toInt();
    priority[3] = QString(DeviceCfg.trigger4_priority).toInt();
    priority[4] = QString(DeviceCfg.trigger5_priority).toInt();
    priority[5] = QString(DeviceCfg.trigger6_priority).toInt();
    priority[6] = QString(DeviceCfg.trigger7_priority).toInt();
    priority[7] = QString(DeviceCfg.trigger8_priority).toInt();

    for(int i=0; i<NUMOFCH; i++)
    {
        if( (priority[i]>=1) && (priority[i]<=NUMOFCH))
        {
            infoPriority[i] = priority[i];
        }
        else
        {
            qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid priority value";
            infoPriority[i] = i+1;
        }
        updatePriorityLabel(i);
    }


    //audio init
    QString audio[NUMOFCH];
    audio[0] = QString(DeviceCfg.trigger1_audio);
    audio[1] = QString(DeviceCfg.trigger2_audio);
    audio[2] = QString(DeviceCfg.trigger3_audio);
    audio[3] = QString(DeviceCfg.trigger4_audio);
    audio[4] = QString(DeviceCfg.trigger5_audio);
    audio[5] = QString(DeviceCfg.trigger6_audio);
    audio[6] = QString(DeviceCfg.trigger7_audio);
    audio[7] = QString(DeviceCfg.trigger8_audio);

    for(int i=0; i<NUMOFCH; i++)
    {
        if( audio[i].compare("OUTPUT") == 0 )
        {
            infoAudio[i] = true;
        }
        else if( audio[i].compare("MUTE") == 0 )
        {
            infoAudio[i] = false;
        }
        else
        {
            qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid audio config";
            infoAudio[i] = true;
        }
        updateAudioLabel(i);
    }
}

void TriggerInputDialog::updateSourceLabel(int ch)
{
    labelSource[ch]->setText(QString("%1 %2").arg(tr("CAM"), QString::number(infoSource[ch])));
}
void TriggerInputDialog::updateDelayLabel(int ch)
{
    labelDelay[ch]->setText(QString("%1 %2").arg(QString::number(infoDelay[ch]), tr("Sec")));
}
void TriggerInputDialog::updatePriorityLabel(int ch)
{
    labelPriority[ch]->setText(QString::number(infoPriority[ch]));
}
void TriggerInputDialog::updateAudioLabel(int ch)
{
    if( infoAudio[ch] )
    {
        labelAudio[ch]->setText(tr("Output"));
    }
    else
    {
        labelAudio[ch]->setText(tr("Mute"));
    }
}

void TriggerInputDialog::onButtonSourceUp1()    { onButtonSourceUp(0); }
void TriggerInputDialog::onButtonSourceUp2()    { onButtonSourceUp(1); }
void TriggerInputDialog::onButtonSourceUp3()    { onButtonSourceUp(2); }
void TriggerInputDialog::onButtonSourceUp4()    { onButtonSourceUp(3); }
void TriggerInputDialog::onButtonSourceUp5()    { onButtonSourceUp(4); }
void TriggerInputDialog::onButtonSourceUp6()    { onButtonSourceUp(5); }
void TriggerInputDialog::onButtonSourceUp7()    { onButtonSourceUp(6); }
void TriggerInputDialog::onButtonSourceUp8()    { onButtonSourceUp(7); }

void TriggerInputDialog::onButtonSourceDn1()    { onButtonSourceDn(0); }
void TriggerInputDialog::onButtonSourceDn2()    { onButtonSourceDn(1); }
void TriggerInputDialog::onButtonSourceDn3()    { onButtonSourceDn(2); }
void TriggerInputDialog::onButtonSourceDn4()    { onButtonSourceDn(3); }
void TriggerInputDialog::onButtonSourceDn5()    { onButtonSourceDn(4); }
void TriggerInputDialog::onButtonSourceDn6()    { onButtonSourceDn(5); }
void TriggerInputDialog::onButtonSourceDn7()    { onButtonSourceDn(6); }
void TriggerInputDialog::onButtonSourceDn8()    { onButtonSourceDn(7); }

void TriggerInputDialog::onButtonSourceUp(int ch)
{
    if( infoSource[ch] >= NUMOFCH ) { infoSource[ch] = 0; }

    infoSource[ch]++;
    updateSourceLabel(ch);
}
void TriggerInputDialog::onButtonSourceDn(int ch)
{
    if( infoSource[ch] <= 1 ) { infoSource[ch] = NUMOFCH+1; }

    infoSource[ch]--;
    updateSourceLabel(ch);
}

void TriggerInputDialog::onButtonDelayUp1()     { onButtonDelayUp(0); }
void TriggerInputDialog::onButtonDelayUp2()     { onButtonDelayUp(1); }
void TriggerInputDialog::onButtonDelayUp3()     { onButtonDelayUp(2); }
void TriggerInputDialog::onButtonDelayUp4()     { onButtonDelayUp(3); }
void TriggerInputDialog::onButtonDelayUp5()     { onButtonDelayUp(4); }
void TriggerInputDialog::onButtonDelayUp6()     { onButtonDelayUp(5); }
void TriggerInputDialog::onButtonDelayUp7()     { onButtonDelayUp(6); }
void TriggerInputDialog::onButtonDelayUp8()     { onButtonDelayUp(7); }

void TriggerInputDialog::onButtonDelayDn1()     { onButtonDelayDn(0); }
void TriggerInputDialog::onButtonDelayDn2()     { onButtonDelayDn(1); }
void TriggerInputDialog::onButtonDelayDn3()     { onButtonDelayDn(2); }
void TriggerInputDialog::onButtonDelayDn4()     { onButtonDelayDn(3); }
void TriggerInputDialog::onButtonDelayDn5()     { onButtonDelayDn(4); }
void TriggerInputDialog::onButtonDelayDn6()     { onButtonDelayDn(5); }
void TriggerInputDialog::onButtonDelayDn7()     { onButtonDelayDn(6); }
void TriggerInputDialog::onButtonDelayDn8()     { onButtonDelayDn(7); }

void TriggerInputDialog::onButtonDelayUp(int ch)
{
    if( infoDelay[ch] >= 20 ) { infoDelay[ch] = 0; }

    infoDelay[ch]++;
    updateDelayLabel(ch);
}
void TriggerInputDialog::onButtonDelayDn(int ch)
{
    if( infoDelay[ch] <= 1 ) { infoDelay[ch] = 21; }

    infoDelay[ch]--;
    updateDelayLabel(ch);
}

void TriggerInputDialog::onButtonPriorityUp1()   { onButtonPriorityUp(0); }
void TriggerInputDialog::onButtonPriorityUp2()   { onButtonPriorityUp(1); }
void TriggerInputDialog::onButtonPriorityUp3()   { onButtonPriorityUp(2); }
void TriggerInputDialog::onButtonPriorityUp4()   { onButtonPriorityUp(3); }
void TriggerInputDialog::onButtonPriorityUp5()   { onButtonPriorityUp(4); }
void TriggerInputDialog::onButtonPriorityUp6()   { onButtonPriorityUp(5); }
void TriggerInputDialog::onButtonPriorityUp7()   { onButtonPriorityUp(6); }
void TriggerInputDialog::onButtonPriorityUp8()   { onButtonPriorityUp(7); }

void TriggerInputDialog::onButtonPriorityDn1()   { onButtonPriorityDn(0); }
void TriggerInputDialog::onButtonPriorityDn2()   { onButtonPriorityDn(1); }
void TriggerInputDialog::onButtonPriorityDn3()   { onButtonPriorityDn(2); }
void TriggerInputDialog::onButtonPriorityDn4()   { onButtonPriorityDn(3); }
void TriggerInputDialog::onButtonPriorityDn5()   { onButtonPriorityDn(4); }
void TriggerInputDialog::onButtonPriorityDn6()   { onButtonPriorityDn(5); }
void TriggerInputDialog::onButtonPriorityDn7()   { onButtonPriorityDn(6); }
void TriggerInputDialog::onButtonPriorityDn8()   { onButtonPriorityDn(7); }

void TriggerInputDialog::onButtonPriorityUp(int ch)
{
    if( infoPriority[ch] >= NUMOFCH ) { infoPriority[ch] = 0; }

    infoPriority[ch]++;
    updatePriorityLabel(ch);
}

void TriggerInputDialog::onButtonPriorityDn(int ch)
{
    if( infoPriority[ch] <= 1 ) { infoPriority[ch] = NUMOFCH+1; }

    infoPriority[ch]--;
    updatePriorityLabel(ch);
}

void TriggerInputDialog::onButtonAudioUp1() { onButtonAudioUp(0); }
void TriggerInputDialog::onButtonAudioUp2() { onButtonAudioUp(1); }
void TriggerInputDialog::onButtonAudioUp3() { onButtonAudioUp(2); }
void TriggerInputDialog::onButtonAudioUp4() { onButtonAudioUp(3); }
void TriggerInputDialog::onButtonAudioUp5() { onButtonAudioUp(4); }
void TriggerInputDialog::onButtonAudioUp6() { onButtonAudioUp(5); }
void TriggerInputDialog::onButtonAudioUp7() { onButtonAudioUp(6); }
void TriggerInputDialog::onButtonAudioUp8() { onButtonAudioUp(7); }

void TriggerInputDialog::onButtonAudioDn1() { onButtonAudioDn(0); }
void TriggerInputDialog::onButtonAudioDn2() { onButtonAudioDn(1); }
void TriggerInputDialog::onButtonAudioDn3() { onButtonAudioDn(2); }
void TriggerInputDialog::onButtonAudioDn4() { onButtonAudioDn(3); }
void TriggerInputDialog::onButtonAudioDn5() { onButtonAudioDn(4); }
void TriggerInputDialog::onButtonAudioDn6() { onButtonAudioDn(5); }
void TriggerInputDialog::onButtonAudioDn7() { onButtonAudioDn(6); }
void TriggerInputDialog::onButtonAudioDn8() { onButtonAudioDn(7); }

void TriggerInputDialog::onButtonAudioUp(int ch)
{
    infoAudio[ch] = !infoAudio[ch];
    updateAudioLabel(ch);
}
void TriggerInputDialog::onButtonAudioDn(int ch)
{
    infoAudio[ch] = !infoAudio[ch];
    updateAudioLabel(ch);
}

int TriggerInputDialog::checkPriorityRedundant()
{
    int rv=0;
    int nPriority[NUMOFCH];
    memset(nPriority, 0, sizeof(nPriority));

    for(int i=0; i<NUMOFCH; i++)
    {
        nPriority[infoPriority[i]-1]++;
    }

    for(int i=0; i<NUMOFCH; i++)
    {
        if(nPriority[i] > 1)
        {
            qDebug("Notice : %s, nPriority[%d] = %d\n", __func__, i, nPriority[i]);
            rv++;
        }
    }

    return rv;
}
#if 0   //yjsin save DeviceCfg for emd-s10
void TriggerInputDialog::onButtonSave()
{
    //save source
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_source; break; }
            case 1 :    { dst = DeviceCfg.trigger2_source; break; }
            case 2 :    { dst = DeviceCfg.trigger3_source; break; }
            case 3 :    { dst = DeviceCfg.trigger4_source; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src = QString("%1%2").arg("CAM", QString::number(infoSource[i]));
            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    //save delay
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_delay; break; }
            case 1 :    { dst = DeviceCfg.trigger2_delay; break; }
            case 2 :    { dst = DeviceCfg.trigger3_delay; break; }
            case 3 :    { dst = DeviceCfg.trigger4_delay; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src = QString("%1%2").arg(QString::number(infoDelay[i]), "SEC");
            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    //check priority redundant
    if( checkPriorityRedundant() )
    {
        if(msgBox)
        {
            delete msgBox;
            msgBox = NULL;
        }

        msgBox = new TextMessageDialog(tr("PRIORITY REDUNDANT"),
                QString("%1\n%2").arg(tr("Priority is redundant."),tr("Please check priority.")), 2, this);

        msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

        if(msgBox->exec()) { ; }

        delete msgBox;
        msgBox = NULL;

        return;
    }

    //save priority
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_priority; break; }
            case 1 :    { dst = DeviceCfg.trigger2_priority; break; }
            case 2 :    { dst = DeviceCfg.trigger3_priority; break; }
            case 3 :    { dst = DeviceCfg.trigger4_priority; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src;
            if( infoPriority[i] < 10 )
            {
                src = QString("0%1").arg(QString::number(infoPriority[i]));
            }
            else
            {
                src = QString("%1").arg(QString::number(infoPriority[i]));
            }

            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    //save audio
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_audio; break; }
            case 1 :    { dst = DeviceCfg.trigger2_audio; break; }
            case 2 :    { dst = DeviceCfg.trigger3_audio; break; }
            case 3 :    { dst = DeviceCfg.trigger4_audio; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {

            QString src;
            if( infoAudio[i] )  { src = "OUTPUT"; }
            else                { src = "MUTE";   }

            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    accept();
}
#else   //yjsin save DeviceCfg for emd-s20
void TriggerInputDialog::onButtonSave()
{
    //save source
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_source; break; }
            case 1 :    { dst = DeviceCfg.trigger2_source; break; }
            case 2 :    { dst = DeviceCfg.trigger3_source; break; }
            case 3 :    { dst = DeviceCfg.trigger4_source; break; }
            case 4 :    { dst = DeviceCfg.trigger5_source; break; }
            case 5 :    { dst = DeviceCfg.trigger6_source; break; }
            case 6 :    { dst = DeviceCfg.trigger7_source; break; }
            case 7 :    { dst = DeviceCfg.trigger8_source; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src = QString("%1%2").arg("CAM", QString::number(infoSource[i]));
            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    //save delay
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_delay; break; }
            case 1 :    { dst = DeviceCfg.trigger2_delay; break; }
            case 2 :    { dst = DeviceCfg.trigger3_delay; break; }
            case 3 :    { dst = DeviceCfg.trigger4_delay; break; }
            case 4 :    { dst = DeviceCfg.trigger5_delay; break; }
            case 5 :    { dst = DeviceCfg.trigger6_delay; break; }
            case 6 :    { dst = DeviceCfg.trigger7_delay; break; }
            case 7 :    { dst = DeviceCfg.trigger8_delay; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src = QString("%1%2").arg(QString::number(infoDelay[i]), "SEC");
            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    //check priority redundant
    if( checkPriorityRedundant() )
    {
        if(msgBox)
        {
            delete msgBox;
            msgBox = NULL;
        }

        msgBox = new TextMessageDialog(tr("PRIORITY REDUNDANT"),
                QString("%1\n%2").arg(tr("Priority is redundant."),tr("Please check priority.")), 2, this);

        msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

        if(msgBox->exec()) { ; }

        delete msgBox;
        msgBox = NULL;

        return;
    }

    //save priority
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_priority; break; }
            case 1 :    { dst = DeviceCfg.trigger2_priority; break; }
            case 2 :    { dst = DeviceCfg.trigger3_priority; break; }
            case 3 :    { dst = DeviceCfg.trigger4_priority; break; }
            case 4 :    { dst = DeviceCfg.trigger5_priority; break; }
            case 5 :    { dst = DeviceCfg.trigger6_priority; break; }
            case 6 :    { dst = DeviceCfg.trigger7_priority; break; }
            case 7 :    { dst = DeviceCfg.trigger8_priority; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src;
            if( infoPriority[i] < 10 )
            {
                src = QString("0%1").arg(QString::number(infoPriority[i]));
            }
            else
            {
                src = QString("%1").arg(QString::number(infoPriority[i]));
            }

            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    //save audio
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_audio; break; }
            case 1 :    { dst = DeviceCfg.trigger2_audio; break; }
            case 2 :    { dst = DeviceCfg.trigger3_audio; break; }
            case 3 :    { dst = DeviceCfg.trigger4_audio; break; }
            case 4 :    { dst = DeviceCfg.trigger5_audio; break; }
            case 5 :    { dst = DeviceCfg.trigger6_audio; break; }
            case 6 :    { dst = DeviceCfg.trigger7_audio; break; }
            case 7 :    { dst = DeviceCfg.trigger8_audio; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src;
            if( infoAudio[i] )  { src = "OUTPUT"; }
            else                { src = "MUTE";   }

            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }

    accept();
}
#endif
void TriggerInputDialog::onButtonDefault()
{
    for(int i=0; i<NUMOFCH; i++)
    {
         infoSource[i]=i+1;
         infoDelay[i]=2;
         infoPriority[i]=i+1;
         infoAudio[i]=true;

         updateSourceLabel(i);
         updateDelayLabel(i);
         updatePriorityLabel(i);
         updateAudioLabel(i);
    }
}

void TriggerInputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if     ( buttonSourceDn[0]->hasFocus()   )      { buttonDefault->setFocus();       }
            else if( buttonSourceDn[1]->hasFocus()   )      { buttonSourceDn[0]->setFocus();   }
            else if( buttonSourceDn[2]->hasFocus()   )      { buttonSourceDn[1]->setFocus();   }
            else if( buttonSourceDn[3]->hasFocus()   )      { buttonSourceDn[2]->setFocus();   }
            else if( buttonSourceDn[4]->hasFocus()   )      { buttonSourceDn[3]->setFocus();   }
            else if( buttonSourceDn[5]->hasFocus()   )      { buttonSourceDn[4]->setFocus();   }
            else if( buttonSourceDn[6]->hasFocus()   )      { buttonSourceDn[5]->setFocus();   }
            else if( buttonSourceDn[7]->hasFocus()   )      { buttonSourceDn[6]->setFocus();   }

            else if( buttonSourceUp[0]->hasFocus()   )      { buttonDefault->setFocus();       }
            else if( buttonSourceUp[1]->hasFocus()   )      { buttonSourceUp[0]->setFocus();   }
            else if( buttonSourceUp[2]->hasFocus()   )      { buttonSourceUp[1]->setFocus();   }
            else if( buttonSourceUp[3]->hasFocus()   )      { buttonSourceUp[2]->setFocus();   }
            else if( buttonSourceUp[4]->hasFocus()   )      { buttonSourceUp[3]->setFocus();   }
            else if( buttonSourceUp[5]->hasFocus()   )      { buttonSourceUp[4]->setFocus();   }
            else if( buttonSourceUp[6]->hasFocus()   )      { buttonSourceUp[5]->setFocus();   }
            else if( buttonSourceUp[7]->hasFocus()   )      { buttonSourceUp[6]->setFocus();   }

            else if( buttonDelayDn[0]->hasFocus()    )      { buttonDelayDn[7]->setFocus();    }
            else if( buttonDelayDn[1]->hasFocus()    )      { buttonDelayDn[0]->setFocus();    }
            else if( buttonDelayDn[2]->hasFocus()    )      { buttonDelayDn[1]->setFocus();    }
            else if( buttonDelayDn[3]->hasFocus()    )      { buttonDelayDn[2]->setFocus();    }
            else if( buttonDelayDn[4]->hasFocus()    )      { buttonDelayDn[3]->setFocus();    }
            else if( buttonDelayDn[5]->hasFocus()    )      { buttonDelayDn[4]->setFocus();    }
            else if( buttonDelayDn[6]->hasFocus()    )      { buttonDelayDn[5]->setFocus();    }
            else if( buttonDelayDn[7]->hasFocus()    )      { buttonDelayDn[6]->setFocus();    }

            else if( buttonDelayUp[0]->hasFocus()    )      { buttonDelayUp[7]->setFocus();    }
            else if( buttonDelayUp[1]->hasFocus()    )      { buttonDelayUp[0]->setFocus();    }
            else if( buttonDelayUp[2]->hasFocus()    )      { buttonDelayUp[1]->setFocus();    }
            else if( buttonDelayUp[3]->hasFocus()    )      { buttonDelayUp[2]->setFocus();    }
            else if( buttonDelayUp[4]->hasFocus()    )      { buttonDelayUp[3]->setFocus();    }
            else if( buttonDelayUp[5]->hasFocus()    )      { buttonDelayUp[4]->setFocus();    }
            else if( buttonDelayUp[6]->hasFocus()    )      { buttonDelayUp[5]->setFocus();    }
            else if( buttonDelayUp[7]->hasFocus()    )      { buttonDelayUp[6]->setFocus();    }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonSave->setFocus();          }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonPriorityDn[4]->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }
            else if( buttonPriorityDn[5]->hasFocus() )      { buttonPriorityDn[4]->setFocus(); }
            else if( buttonPriorityDn[6]->hasFocus() )      { buttonPriorityDn[5]->setFocus(); }
            else if( buttonPriorityDn[7]->hasFocus() )      { buttonPriorityDn[6]->setFocus(); }

            else if( buttonPriorityUp[0]->hasFocus() )      { buttonSave->setFocus();          }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonPriorityUp[4]->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }
            else if( buttonPriorityUp[5]->hasFocus() )      { buttonPriorityUp[4]->setFocus(); }
            else if( buttonPriorityUp[6]->hasFocus() )      { buttonPriorityUp[5]->setFocus(); }
            else if( buttonPriorityUp[7]->hasFocus() )      { buttonPriorityUp[6]->setFocus(); }

            else if( buttonAudioDn[0]->hasFocus()    )      { buttonClose->setFocus();         }
            else if( buttonAudioDn[1]->hasFocus()    )      { buttonAudioDn[0]->setFocus();    }
            else if( buttonAudioDn[2]->hasFocus()    )      { buttonAudioDn[1]->setFocus();    }
            else if( buttonAudioDn[3]->hasFocus()    )      { buttonAudioDn[2]->setFocus();    }
            else if( buttonAudioDn[4]->hasFocus()    )      { buttonAudioDn[3]->setFocus();    }
            else if( buttonAudioDn[5]->hasFocus()    )      { buttonAudioDn[4]->setFocus();    }
            else if( buttonAudioDn[6]->hasFocus()    )      { buttonAudioDn[5]->setFocus();    }
            else if( buttonAudioDn[7]->hasFocus()    )      { buttonAudioDn[6]->setFocus();    }

            else if( buttonAudioUp[0]->hasFocus()    )      { buttonClose->setFocus();         }
            else if( buttonAudioUp[1]->hasFocus()    )      { buttonAudioUp[0]->setFocus();    }
            else if( buttonAudioUp[2]->hasFocus()    )      { buttonAudioUp[1]->setFocus();    }
            else if( buttonAudioUp[3]->hasFocus()    )      { buttonAudioUp[2]->setFocus();    }
            else if( buttonAudioUp[4]->hasFocus()    )      { buttonAudioUp[3]->setFocus();    }
            else if( buttonAudioUp[5]->hasFocus()    )      { buttonAudioUp[4]->setFocus();    }
            else if( buttonAudioUp[6]->hasFocus()    )      { buttonAudioUp[5]->setFocus();    }
            else if( buttonAudioUp[7]->hasFocus()    )      { buttonAudioUp[6]->setFocus();    }

            else if( buttonDefault->hasFocus()       )      { buttonSourceDn[7]->setFocus();   }
            else if( buttonSave->hasFocus()          )      { buttonPriorityDn[7]->setFocus(); }
            else if( buttonClose->hasFocus()         )      { buttonAudioDn[7]->setFocus();    }

            break;
        }
        case Qt::Key_Down:
        {
            if     ( buttonSourceDn[0]->hasFocus()   )      { buttonSourceDn[1]->setFocus();   }
            else if( buttonSourceDn[1]->hasFocus()   )      { buttonSourceDn[2]->setFocus();   }
            else if( buttonSourceDn[2]->hasFocus()   )      { buttonSourceDn[3]->setFocus();   }
            else if( buttonSourceDn[3]->hasFocus()   )      { buttonSourceDn[4]->setFocus();   }
            else if( buttonSourceDn[4]->hasFocus()   )      { buttonSourceDn[5]->setFocus();   }
            else if( buttonSourceDn[5]->hasFocus()   )      { buttonSourceDn[6]->setFocus();   }
            else if( buttonSourceDn[6]->hasFocus()   )      { buttonSourceDn[7]->setFocus();   }
            else if( buttonSourceDn[7]->hasFocus()   )      { buttonDefault->setFocus();       }

            else if( buttonSourceUp[0]->hasFocus()   )      { buttonSourceUp[1]->setFocus();   }
            else if( buttonSourceUp[1]->hasFocus()   )      { buttonSourceUp[2]->setFocus();   }
            else if( buttonSourceUp[2]->hasFocus()   )      { buttonSourceUp[3]->setFocus();   }
            else if( buttonSourceUp[3]->hasFocus()   )      { buttonSourceUp[4]->setFocus();   }
            else if( buttonSourceUp[4]->hasFocus()   )      { buttonSourceUp[5]->setFocus();   }
            else if( buttonSourceUp[5]->hasFocus()   )      { buttonSourceUp[6]->setFocus();   }
            else if( buttonSourceUp[6]->hasFocus()   )      { buttonSourceUp[7]->setFocus();   }
            else if( buttonSourceUp[7]->hasFocus()   )      { buttonDefault->setFocus();       }

            else if( buttonDelayDn[0]->hasFocus()    )      { buttonDelayDn[1]->setFocus();    }
            else if( buttonDelayDn[1]->hasFocus()    )      { buttonDelayDn[2]->setFocus();    }
            else if( buttonDelayDn[2]->hasFocus()    )      { buttonDelayDn[3]->setFocus();    }
            else if( buttonDelayDn[3]->hasFocus()    )      { buttonDelayDn[4]->setFocus();    }
            else if( buttonDelayDn[4]->hasFocus()    )      { buttonDelayDn[5]->setFocus();    }
            else if( buttonDelayDn[5]->hasFocus()    )      { buttonDelayDn[6]->setFocus();    }
            else if( buttonDelayDn[6]->hasFocus()    )      { buttonDelayDn[7]->setFocus();    }
            else if( buttonDelayDn[7]->hasFocus()    )      { buttonDelayDn[0]->setFocus();    }

            else if( buttonDelayUp[0]->hasFocus()    )      { buttonDelayUp[1]->setFocus();    }
            else if( buttonDelayUp[1]->hasFocus()    )      { buttonDelayUp[2]->setFocus();    }
            else if( buttonDelayUp[2]->hasFocus()    )      { buttonDelayUp[3]->setFocus();    }
            else if( buttonDelayUp[3]->hasFocus()    )      { buttonDelayUp[4]->setFocus();    }
            else if( buttonDelayUp[4]->hasFocus()    )      { buttonDelayUp[5]->setFocus();    }
            else if( buttonDelayUp[5]->hasFocus()    )      { buttonDelayUp[6]->setFocus();    }
            else if( buttonDelayUp[6]->hasFocus()    )      { buttonDelayUp[7]->setFocus();    }
            else if( buttonDelayUp[7]->hasFocus()    )      { buttonDelayUp[0]->setFocus();    }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonPriorityDn[4]->setFocus(); }
            else if( buttonPriorityDn[4]->hasFocus() )      { buttonPriorityDn[5]->setFocus(); }
            else if( buttonPriorityDn[5]->hasFocus() )      { buttonPriorityDn[6]->setFocus(); }
            else if( buttonPriorityDn[6]->hasFocus() )      { buttonPriorityDn[7]->setFocus(); }
            else if( buttonPriorityDn[7]->hasFocus() )      { buttonSave->setFocus();          }

            else if( buttonPriorityUp[0]->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonPriorityUp[4]->setFocus(); }
            else if( buttonPriorityUp[4]->hasFocus() )      { buttonPriorityUp[5]->setFocus(); }
            else if( buttonPriorityUp[5]->hasFocus() )      { buttonPriorityUp[6]->setFocus(); }
            else if( buttonPriorityUp[6]->hasFocus() )      { buttonPriorityUp[7]->setFocus(); }
            else if( buttonPriorityUp[7]->hasFocus() )      { buttonSave->setFocus();          }

            else if( buttonAudioDn[0]->hasFocus()    )      { buttonAudioDn[1]->setFocus();    }
            else if( buttonAudioDn[1]->hasFocus()    )      { buttonAudioDn[2]->setFocus();    }
            else if( buttonAudioDn[2]->hasFocus()    )      { buttonAudioDn[3]->setFocus();    }
            else if( buttonAudioDn[3]->hasFocus()    )      { buttonAudioDn[4]->setFocus();    }
            else if( buttonAudioDn[4]->hasFocus()    )      { buttonAudioDn[5]->setFocus();    }
            else if( buttonAudioDn[5]->hasFocus()    )      { buttonAudioDn[6]->setFocus();    }
            else if( buttonAudioDn[6]->hasFocus()    )      { buttonAudioDn[7]->setFocus();    }
            else if( buttonAudioDn[7]->hasFocus()    )      { buttonClose->setFocus();         }

            else if( buttonAudioUp[0]->hasFocus()    )      { buttonAudioUp[1]->setFocus();    }
            else if( buttonAudioUp[1]->hasFocus()    )      { buttonAudioUp[2]->setFocus();    }
            else if( buttonAudioUp[2]->hasFocus()    )      { buttonAudioUp[3]->setFocus();    }
            else if( buttonAudioUp[3]->hasFocus()    )      { buttonAudioUp[4]->setFocus();    }
            else if( buttonAudioUp[4]->hasFocus()    )      { buttonAudioUp[5]->setFocus();    }
            else if( buttonAudioUp[5]->hasFocus()    )      { buttonAudioUp[6]->setFocus();    }
            else if( buttonAudioUp[6]->hasFocus()    )      { buttonAudioUp[7]->setFocus();    }
            else if( buttonAudioUp[7]->hasFocus()    )      { buttonClose->setFocus();         }

            else if( buttonDefault->hasFocus()       )      { buttonSourceDn[0]->setFocus();   }
            else if( buttonSave->hasFocus()          )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonClose->hasFocus()         )      { buttonAudioDn[0]->setFocus();    }

            break;
        }
        case Qt::Key_Left:
        {
            if     ( buttonSourceDn[0]->hasFocus()   )      { buttonAudioUp[0]->setFocus();    }
            else if( buttonSourceDn[1]->hasFocus()   )      { buttonAudioUp[1]->setFocus();    }
            else if( buttonSourceDn[2]->hasFocus()   )      { buttonAudioUp[2]->setFocus();    }
            else if( buttonSourceDn[3]->hasFocus()   )      { buttonAudioUp[3]->setFocus();    }
            else if( buttonSourceDn[4]->hasFocus()   )      { buttonAudioUp[4]->setFocus();    }
            else if( buttonSourceDn[5]->hasFocus()   )      { buttonAudioUp[5]->setFocus();    }
            else if( buttonSourceDn[6]->hasFocus()   )      { buttonAudioUp[6]->setFocus();    }
            else if( buttonSourceDn[7]->hasFocus()   )      { buttonAudioUp[7]->setFocus();    }

            else if( buttonSourceUp[0]->hasFocus()   )      { buttonSourceDn[0]->setFocus();   }
            else if( buttonSourceUp[1]->hasFocus()   )      { buttonSourceDn[1]->setFocus();   }
            else if( buttonSourceUp[2]->hasFocus()   )      { buttonSourceDn[2]->setFocus();   }
            else if( buttonSourceUp[3]->hasFocus()   )      { buttonSourceDn[3]->setFocus();   }
            else if( buttonSourceUp[4]->hasFocus()   )      { buttonSourceDn[4]->setFocus();   }
            else if( buttonSourceUp[5]->hasFocus()   )      { buttonSourceDn[5]->setFocus();   }
            else if( buttonSourceUp[6]->hasFocus()   )      { buttonSourceDn[6]->setFocus();   }
            else if( buttonSourceUp[7]->hasFocus()   )      { buttonSourceDn[7]->setFocus();   }

            else if( buttonDelayDn[0]->hasFocus()    )      { buttonSourceUp[0]->setFocus();   }
            else if( buttonDelayDn[1]->hasFocus()    )      { buttonSourceUp[1]->setFocus();   }
            else if( buttonDelayDn[2]->hasFocus()    )      { buttonSourceUp[2]->setFocus();   }
            else if( buttonDelayDn[3]->hasFocus()    )      { buttonSourceUp[3]->setFocus();   }
            else if( buttonDelayDn[4]->hasFocus()    )      { buttonSourceUp[4]->setFocus();   }
            else if( buttonDelayDn[5]->hasFocus()    )      { buttonSourceUp[5]->setFocus();   }
            else if( buttonDelayDn[6]->hasFocus()    )      { buttonSourceUp[6]->setFocus();   }
            else if( buttonDelayDn[7]->hasFocus()    )      { buttonSourceUp[7]->setFocus();   }

            else if( buttonDelayUp[0]->hasFocus()    )      { buttonDelayDn[0]->setFocus();    }
            else if( buttonDelayUp[1]->hasFocus()    )      { buttonDelayDn[1]->setFocus();    }
            else if( buttonDelayUp[2]->hasFocus()    )      { buttonDelayDn[2]->setFocus();    }
            else if( buttonDelayUp[3]->hasFocus()    )      { buttonDelayDn[3]->setFocus();    }
            else if( buttonDelayUp[4]->hasFocus()    )      { buttonDelayDn[4]->setFocus();    }
            else if( buttonDelayUp[5]->hasFocus()    )      { buttonDelayDn[5]->setFocus();    }
            else if( buttonDelayUp[6]->hasFocus()    )      { buttonDelayDn[6]->setFocus();    }
            else if( buttonDelayUp[7]->hasFocus()    )      { buttonDelayDn[7]->setFocus();    }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonDelayUp[0]->setFocus();    }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonDelayUp[1]->setFocus();    }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonDelayUp[2]->setFocus();    }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonDelayUp[3]->setFocus();    }
            else if( buttonPriorityDn[4]->hasFocus() )      { buttonDelayUp[4]->setFocus();    }
            else if( buttonPriorityDn[5]->hasFocus() )      { buttonDelayUp[5]->setFocus();    }
            else if( buttonPriorityDn[6]->hasFocus() )      { buttonDelayUp[6]->setFocus();    }
            else if( buttonPriorityDn[7]->hasFocus() )      { buttonDelayUp[7]->setFocus();    }

            else if( buttonPriorityUp[0]->hasFocus() )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }
            else if( buttonPriorityUp[4]->hasFocus() )      { buttonPriorityDn[4]->setFocus(); }
            else if( buttonPriorityUp[5]->hasFocus() )      { buttonPriorityDn[5]->setFocus(); }
            else if( buttonPriorityUp[6]->hasFocus() )      { buttonPriorityDn[6]->setFocus(); }
            else if( buttonPriorityUp[7]->hasFocus() )      { buttonPriorityDn[7]->setFocus(); }

            else if( buttonAudioDn[0]->hasFocus()    )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonAudioDn[1]->hasFocus()    )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonAudioDn[2]->hasFocus()    )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonAudioDn[3]->hasFocus()    )      { buttonPriorityUp[3]->setFocus(); }
            else if( buttonAudioDn[4]->hasFocus()    )      { buttonPriorityUp[4]->setFocus(); }
            else if( buttonAudioDn[5]->hasFocus()    )      { buttonPriorityUp[5]->setFocus(); }
            else if( buttonAudioDn[6]->hasFocus()    )      { buttonPriorityUp[6]->setFocus(); }
            else if( buttonAudioDn[7]->hasFocus()    )      { buttonPriorityUp[7]->setFocus(); }

            else if( buttonAudioUp[0]->hasFocus()    )      { buttonAudioDn[0]->setFocus();    }
            else if( buttonAudioUp[1]->hasFocus()    )      { buttonAudioDn[1]->setFocus();    }
            else if( buttonAudioUp[2]->hasFocus()    )      { buttonAudioDn[2]->setFocus();    }
            else if( buttonAudioUp[3]->hasFocus()    )      { buttonAudioDn[3]->setFocus();    }
            else if( buttonAudioUp[4]->hasFocus()    )      { buttonAudioDn[4]->setFocus();    }
            else if( buttonAudioUp[5]->hasFocus()    )      { buttonAudioDn[5]->setFocus();    }
            else if( buttonAudioUp[6]->hasFocus()    )      { buttonAudioDn[6]->setFocus();    }
            else if( buttonAudioUp[7]->hasFocus()    )      { buttonAudioDn[7]->setFocus();    }

            else if( buttonDefault->hasFocus()       )      { buttonClose->setFocus();         }
            else if( buttonSave->hasFocus()          )      { buttonDefault->setFocus();       }
            else if( buttonClose->hasFocus()         )      { buttonSave->setFocus();          }

            break;
        }
        case Qt::Key_Right:
        {
            if     ( buttonSourceDn[0]->hasFocus()   )      { buttonSourceUp[0]->setFocus();   }
            else if( buttonSourceDn[1]->hasFocus()   )      { buttonSourceUp[1]->setFocus();   }
            else if( buttonSourceDn[2]->hasFocus()   )      { buttonSourceUp[2]->setFocus();   }
            else if( buttonSourceDn[3]->hasFocus()   )      { buttonSourceUp[3]->setFocus();   }
            else if( buttonSourceDn[4]->hasFocus()   )      { buttonSourceUp[4]->setFocus();   }
            else if( buttonSourceDn[5]->hasFocus()   )      { buttonSourceUp[5]->setFocus();   }
            else if( buttonSourceDn[6]->hasFocus()   )      { buttonSourceUp[6]->setFocus();   }
            else if( buttonSourceDn[7]->hasFocus()   )      { buttonSourceUp[7]->setFocus();   }

            else if( buttonSourceUp[0]->hasFocus()   )      { buttonDelayDn[0]->setFocus();    }
            else if( buttonSourceUp[1]->hasFocus()   )      { buttonDelayDn[1]->setFocus();    }
            else if( buttonSourceUp[2]->hasFocus()   )      { buttonDelayDn[2]->setFocus();    }
            else if( buttonSourceUp[3]->hasFocus()   )      { buttonDelayDn[3]->setFocus();    }
            else if( buttonSourceUp[4]->hasFocus()   )      { buttonDelayDn[4]->setFocus();    }
            else if( buttonSourceUp[5]->hasFocus()   )      { buttonDelayDn[5]->setFocus();    }
            else if( buttonSourceUp[6]->hasFocus()   )      { buttonDelayDn[6]->setFocus();    }
            else if( buttonSourceUp[7]->hasFocus()   )      { buttonDelayDn[7]->setFocus();    }

            else if( buttonDelayDn[0]->hasFocus()    )      { buttonDelayUp[0]->setFocus();    }
            else if( buttonDelayDn[1]->hasFocus()    )      { buttonDelayUp[1]->setFocus();    }
            else if( buttonDelayDn[2]->hasFocus()    )      { buttonDelayUp[2]->setFocus();    }
            else if( buttonDelayDn[3]->hasFocus()    )      { buttonDelayUp[3]->setFocus();    }
            else if( buttonDelayDn[4]->hasFocus()    )      { buttonDelayUp[4]->setFocus();    }
            else if( buttonDelayDn[5]->hasFocus()    )      { buttonDelayUp[5]->setFocus();    }
            else if( buttonDelayDn[6]->hasFocus()    )      { buttonDelayUp[6]->setFocus();    }
            else if( buttonDelayDn[7]->hasFocus()    )      { buttonDelayUp[7]->setFocus();    }

            else if( buttonDelayUp[0]->hasFocus()    )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonDelayUp[1]->hasFocus()    )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonDelayUp[2]->hasFocus()    )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonDelayUp[3]->hasFocus()    )      { buttonPriorityDn[3]->setFocus(); }
            else if( buttonDelayUp[4]->hasFocus()    )      { buttonPriorityDn[4]->setFocus(); }
            else if( buttonDelayUp[5]->hasFocus()    )      { buttonPriorityDn[5]->setFocus(); }
            else if( buttonDelayUp[6]->hasFocus()    )      { buttonPriorityDn[6]->setFocus(); }
            else if( buttonDelayUp[7]->hasFocus()    )      { buttonPriorityDn[7]->setFocus(); }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }
            else if( buttonPriorityDn[4]->hasFocus() )      { buttonPriorityUp[4]->setFocus(); }
            else if( buttonPriorityDn[5]->hasFocus() )      { buttonPriorityUp[5]->setFocus(); }
            else if( buttonPriorityDn[6]->hasFocus() )      { buttonPriorityUp[6]->setFocus(); }
            else if( buttonPriorityDn[7]->hasFocus() )      { buttonPriorityUp[7]->setFocus(); }

            else if( buttonPriorityUp[0]->hasFocus() )      { buttonAudioDn[0]->setFocus();    }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonAudioDn[1]->setFocus();    }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonAudioDn[2]->setFocus();    }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonAudioDn[3]->setFocus();    }
            else if( buttonPriorityUp[4]->hasFocus() )      { buttonAudioDn[4]->setFocus();    }
            else if( buttonPriorityUp[5]->hasFocus() )      { buttonAudioDn[5]->setFocus();    }
            else if( buttonPriorityUp[6]->hasFocus() )      { buttonAudioDn[6]->setFocus();    }
            else if( buttonPriorityUp[7]->hasFocus() )      { buttonAudioDn[7]->setFocus();    }

            else if( buttonAudioDn[0]->hasFocus()    )      { buttonAudioUp[0]->setFocus();    }
            else if( buttonAudioDn[1]->hasFocus()    )      { buttonAudioUp[1]->setFocus();    }
            else if( buttonAudioDn[2]->hasFocus()    )      { buttonAudioUp[2]->setFocus();    }
            else if( buttonAudioDn[3]->hasFocus()    )      { buttonAudioUp[3]->setFocus();    }
            else if( buttonAudioDn[4]->hasFocus()    )      { buttonAudioUp[4]->setFocus();    }
            else if( buttonAudioDn[5]->hasFocus()    )      { buttonAudioUp[5]->setFocus();    }
            else if( buttonAudioDn[6]->hasFocus()    )      { buttonAudioUp[6]->setFocus();    }
            else if( buttonAudioDn[7]->hasFocus()    )      { buttonAudioUp[7]->setFocus();    }

            else if( buttonAudioUp[0]->hasFocus()    )      { buttonSourceDn[0]->setFocus();   }
            else if( buttonAudioUp[1]->hasFocus()    )      { buttonSourceDn[1]->setFocus();   }
            else if( buttonAudioUp[2]->hasFocus()    )      { buttonSourceDn[2]->setFocus();   }
            else if( buttonAudioUp[3]->hasFocus()    )      { buttonSourceDn[3]->setFocus();   }
            else if( buttonAudioUp[4]->hasFocus()    )      { buttonSourceDn[4]->setFocus();   }
            else if( buttonAudioUp[5]->hasFocus()    )      { buttonSourceDn[5]->setFocus();   }
            else if( buttonAudioUp[6]->hasFocus()    )      { buttonSourceDn[6]->setFocus();   }
            else if( buttonAudioUp[7]->hasFocus()    )      { buttonSourceDn[7]->setFocus();   }

            else if( buttonDefault->hasFocus()       )      { buttonSave->setFocus();          }
            else if( buttonSave->hasFocus()          )      { buttonClose->setFocus();         }
            else if( buttonClose->hasFocus()         )      { buttonDefault->setFocus();       }

            break;
        }
        case Qt::Key_Enter:
        {
            if     ( buttonSourceDn[0]->hasFocus()   )      { onButtonSourceDn(0);             }
            else if( buttonSourceDn[1]->hasFocus()   )      { onButtonSourceDn(1);             }
            else if( buttonSourceDn[2]->hasFocus()   )      { onButtonSourceDn(2);             }
            else if( buttonSourceDn[3]->hasFocus()   )      { onButtonSourceDn(3);             }
            else if( buttonSourceDn[4]->hasFocus()   )      { onButtonSourceDn(4);             }
            else if( buttonSourceDn[5]->hasFocus()   )      { onButtonSourceDn(5);             }
            else if( buttonSourceDn[6]->hasFocus()   )      { onButtonSourceDn(6);             }
            else if( buttonSourceDn[7]->hasFocus()   )      { onButtonSourceDn(7);             }

            else if( buttonSourceUp[0]->hasFocus()   )      { onButtonSourceUp(0);             }
            else if( buttonSourceUp[1]->hasFocus()   )      { onButtonSourceUp(1);             }
            else if( buttonSourceUp[2]->hasFocus()   )      { onButtonSourceUp(2);             }
            else if( buttonSourceUp[3]->hasFocus()   )      { onButtonSourceUp(3);             }
            else if( buttonSourceUp[4]->hasFocus()   )      { onButtonSourceUp(4);             }
            else if( buttonSourceUp[5]->hasFocus()   )      { onButtonSourceUp(5);             }
            else if( buttonSourceUp[6]->hasFocus()   )      { onButtonSourceUp(6);             }
            else if( buttonSourceUp[7]->hasFocus()   )      { onButtonSourceUp(7);             }

            else if( buttonDelayDn[0]->hasFocus()    )      { onButtonDelayDn(0);              }
            else if( buttonDelayDn[1]->hasFocus()    )      { onButtonDelayDn(1);              }
            else if( buttonDelayDn[2]->hasFocus()    )      { onButtonDelayDn(2);              }
            else if( buttonDelayDn[3]->hasFocus()    )      { onButtonDelayDn(3);              }
            else if( buttonDelayDn[4]->hasFocus()    )      { onButtonDelayDn(4);              }
            else if( buttonDelayDn[5]->hasFocus()    )      { onButtonDelayDn(5);              }
            else if( buttonDelayDn[6]->hasFocus()    )      { onButtonDelayDn(6);              }
            else if( buttonDelayDn[7]->hasFocus()    )      { onButtonDelayDn(7);              }

            else if( buttonDelayUp[0]->hasFocus()    )      { onButtonDelayUp(0);              }
            else if( buttonDelayUp[1]->hasFocus()    )      { onButtonDelayUp(1);              }
            else if( buttonDelayUp[2]->hasFocus()    )      { onButtonDelayUp(2);              }
            else if( buttonDelayUp[3]->hasFocus()    )      { onButtonDelayUp(3);              }
            else if( buttonDelayUp[4]->hasFocus()    )      { onButtonDelayUp(4);              }
            else if( buttonDelayUp[5]->hasFocus()    )      { onButtonDelayUp(5);              }
            else if( buttonDelayUp[6]->hasFocus()    )      { onButtonDelayUp(6);              }
            else if( buttonDelayUp[7]->hasFocus()    )      { onButtonDelayUp(7);              }

            else if( buttonPriorityDn[0]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[1]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[2]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[3]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[4]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[5]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[6]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[7]->hasFocus() )      { onButtonPriorityDn(0);           }

            else if( buttonPriorityUp[0]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[1]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[2]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[3]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[4]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[5]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[6]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[7]->hasFocus() )      { onButtonPriorityUp(0);           }

            else if( buttonAudioDn[0]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[1]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[2]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[3]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[4]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[5]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[6]->hasFocus()    )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[7]->hasFocus()    )      { onButtonAudioDn(0);              }

            else if( buttonAudioUp[0]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[1]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[2]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[3]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[4]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[5]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[6]->hasFocus()    )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[7]->hasFocus()    )      { onButtonAudioUp(0);              }

            else if( buttonDefault->hasFocus()       )      { onButtonDefault();               }
            else if( buttonSave->hasFocus()          )      { onButtonSave();                  }
            else if( buttonClose->hasFocus()         )      { reject();                        }

            break;
        }
        case Qt::Key_Escape:
        {
            reject();
            break;
        }
    }
}

