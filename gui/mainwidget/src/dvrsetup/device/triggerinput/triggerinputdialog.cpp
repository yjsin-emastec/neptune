#include <QtGui>
#include "triggerinputdialog.h"
#include "main/mainglobal.h"

#if defined(HI3521)
TriggerInputDialog::TriggerInputDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::TriggerInputDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        buttonSourceAll   = ui720.buttonSourceAll;
        buttonDelayAll    = ui720.buttonDelayAll;
        buttonPriorityAll = ui720.buttonPriorityAll;
        buttonAudioAll    = ui720.buttonAudioAll;

        labelTrigger[0] = ui720.labelTrigger1;
        labelTrigger[1] = ui720.labelTrigger2;
        labelTrigger[2] = ui720.labelTrigger3;
        labelTrigger[3] = ui720.labelTrigger4;
        labelTrigger[4] = ui720.labelAll;

        buttonSourceUp[0] = ui720.buttonSourceUp1;
        buttonSourceUp[1] = ui720.buttonSourceUp2;
        buttonSourceUp[2] = ui720.buttonSourceUp3;
        buttonSourceUp[3] = ui720.buttonSourceUp4;

        buttonSourceDn[0] = ui720.buttonSourceDn1;
        buttonSourceDn[1] = ui720.buttonSourceDn2;
        buttonSourceDn[2] = ui720.buttonSourceDn3;
        buttonSourceDn[3] = ui720.buttonSourceDn4;

        labelSource[0] = ui720.labelSource1;
        labelSource[1] = ui720.labelSource2;
        labelSource[2] = ui720.labelSource3;
        labelSource[3] = ui720.labelSource4;
        labelSource[4] = ui720.labelSourceAll;

        buttonDelayUp[0] = ui720.buttonDelayUp1;
        buttonDelayUp[1] = ui720.buttonDelayUp2;
        buttonDelayUp[2] = ui720.buttonDelayUp3;
        buttonDelayUp[3] = ui720.buttonDelayUp4;

        buttonDelayDn[0] = ui720.buttonDelayDn1;
        buttonDelayDn[1] = ui720.buttonDelayDn2;
        buttonDelayDn[2] = ui720.buttonDelayDn3;
        buttonDelayDn[3] = ui720.buttonDelayDn4;

        labelDelay[0] = ui720.labelDelay1;
        labelDelay[1] = ui720.labelDelay2;
        labelDelay[2] = ui720.labelDelay3;
        labelDelay[3] = ui720.labelDelay4;
        labelDelay[4] = ui720.labelDelayAll;

        buttonPriorityUp[0] = ui720.buttonPriorityUp1;
        buttonPriorityUp[1] = ui720.buttonPriorityUp2;
        buttonPriorityUp[2] = ui720.buttonPriorityUp3;
        buttonPriorityUp[3] = ui720.buttonPriorityUp4;

        buttonPriorityDn[0] = ui720.buttonPriorityDn1;
        buttonPriorityDn[1] = ui720.buttonPriorityDn2;
        buttonPriorityDn[2] = ui720.buttonPriorityDn3;
        buttonPriorityDn[3] = ui720.buttonPriorityDn4;

        labelPriority[0] = ui720.labelPriority1;
        labelPriority[1] = ui720.labelPriority2;
        labelPriority[2] = ui720.labelPriority3;
        labelPriority[3] = ui720.labelPriority4;
        labelPriority[4] = ui720.labelPriorityAll;

        buttonAudioUp[0] = ui720.buttonAudioUp1;
        buttonAudioUp[1] = ui720.buttonAudioUp2;
        buttonAudioUp[2] = ui720.buttonAudioUp3;
        buttonAudioUp[3] = ui720.buttonAudioUp4;

        buttonAudioDn[0] = ui720.buttonAudioDn1;
        buttonAudioDn[1] = ui720.buttonAudioDn2;
        buttonAudioDn[2] = ui720.buttonAudioDn3;
        buttonAudioDn[3] = ui720.buttonAudioDn4;

        labelAudio[0] = ui720.labelAudio1;
        labelAudio[1] = ui720.labelAudio2;
        labelAudio[2] = ui720.labelAudio3;
        labelAudio[3] = ui720.labelAudio4;
        labelAudio[4] = ui720.labelAudioAll;

        buttonDefault = ui720.buttonDefault;
        buttonSave    = ui720.buttonSave;
        buttonClose   = ui720.buttonClose;

        buttonSourceAll         ->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonDelayAll          ->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonPriorityAll       ->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudioAll          ->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

        labelTrigger[NUMOFCH]   ->setStyleSheet("font:40px; background-color:rgb(06,86,159);");
        labelSource[NUMOFCH]    ->setStyleSheet("background-color:rgb(06,86,159);");
        labelDelay[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelPriority[NUMOFCH]  ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudio[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");

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

            labelTrigger[i]->setStyleSheet("font:38px;");

            labelSource[i]->setStyleSheet("font:40px;");
            labelDelay[i]->setStyleSheet("font:40px;");
            labelPriority[i]->setStyleSheet("font:43px;");
            labelAudio[i]->setStyleSheet("font:43px;");
        }

        if( utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:32px;");
            }
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(281, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonDefault->resize(281, 91);

            for( int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:30px;");
            }
            labelAudio[NUMOFCH]->setStyleSheet("font:30px;");
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

        buttonSourceAll   = ui1080.buttonSourceAll;
        buttonDelayAll    = ui1080.buttonDelayAll;
        buttonPriorityAll = ui1080.buttonPriorityAll;
        buttonAudioAll    = ui1080.buttonAudioAll;

        labelTrigger[0] = ui1080.labelTrigger1;
        labelTrigger[1] = ui1080.labelTrigger2;
        labelTrigger[2] = ui1080.labelTrigger3;
        labelTrigger[3] = ui1080.labelTrigger4;
        labelTrigger[4] = ui1080.labelAll;

        buttonSourceUp[0] = ui1080.buttonSourceUp1;
        buttonSourceUp[1] = ui1080.buttonSourceUp2;
        buttonSourceUp[2] = ui1080.buttonSourceUp3;
        buttonSourceUp[3] = ui1080.buttonSourceUp4;

        buttonSourceDn[0] = ui1080.buttonSourceDn1;
        buttonSourceDn[1] = ui1080.buttonSourceDn2;
        buttonSourceDn[2] = ui1080.buttonSourceDn3;
        buttonSourceDn[3] = ui1080.buttonSourceDn4;

        labelSource[0] = ui1080.labelSource1;
        labelSource[1] = ui1080.labelSource2;
        labelSource[2] = ui1080.labelSource3;
        labelSource[3] = ui1080.labelSource4;
        labelSource[4] = ui1080.labelSourceAll;

        buttonDelayUp[0] = ui1080.buttonDelayUp1;
        buttonDelayUp[1] = ui1080.buttonDelayUp2;
        buttonDelayUp[2] = ui1080.buttonDelayUp3;
        buttonDelayUp[3] = ui1080.buttonDelayUp4;

        buttonDelayDn[0] = ui1080.buttonDelayDn1;
        buttonDelayDn[1] = ui1080.buttonDelayDn2;
        buttonDelayDn[2] = ui1080.buttonDelayDn3;
        buttonDelayDn[3] = ui1080.buttonDelayDn4;

        labelDelay[0] = ui1080.labelDelay1;
        labelDelay[1] = ui1080.labelDelay2;
        labelDelay[2] = ui1080.labelDelay3;
        labelDelay[3] = ui1080.labelDelay4;
        labelDelay[4] = ui1080.labelDelayAll;

        buttonPriorityUp[0] = ui1080.buttonPriorityUp1;
        buttonPriorityUp[1] = ui1080.buttonPriorityUp2;
        buttonPriorityUp[2] = ui1080.buttonPriorityUp3;
        buttonPriorityUp[3] = ui1080.buttonPriorityUp4;

        buttonPriorityDn[0] = ui1080.buttonPriorityDn1;
        buttonPriorityDn[1] = ui1080.buttonPriorityDn2;
        buttonPriorityDn[2] = ui1080.buttonPriorityDn3;
        buttonPriorityDn[3] = ui1080.buttonPriorityDn4;

        labelPriority[0] = ui1080.labelPriority1;
        labelPriority[1] = ui1080.labelPriority2;
        labelPriority[2] = ui1080.labelPriority3;
        labelPriority[3] = ui1080.labelPriority4;
        labelPriority[4] = ui1080.labelPriorityAll;

        buttonAudioUp[0] = ui1080.buttonAudioUp1;
        buttonAudioUp[1] = ui1080.buttonAudioUp2;
        buttonAudioUp[2] = ui1080.buttonAudioUp3;
        buttonAudioUp[3] = ui1080.buttonAudioUp4;

        buttonAudioDn[0] = ui1080.buttonAudioDn1;
        buttonAudioDn[1] = ui1080.buttonAudioDn2;
        buttonAudioDn[2] = ui1080.buttonAudioDn3;
        buttonAudioDn[3] = ui1080.buttonAudioDn4;

        labelAudio[0] = ui1080.labelAudio1;
        labelAudio[1] = ui1080.labelAudio2;
        labelAudio[2] = ui1080.labelAudio3;
        labelAudio[3] = ui1080.labelAudio4;
        labelAudio[4] = ui1080.labelAudioAll;

        buttonDefault = ui1080.buttonDefault;
        buttonSave    = ui1080.buttonSave;
        buttonClose   = ui1080.buttonClose;

        buttonSourceAll         ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonDelayAll          ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonPriorityAll       ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudioAll          ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

        labelTrigger[NUMOFCH]   ->setStyleSheet("font:60px; background-color:rgb(06,86,159);");
        labelSource[NUMOFCH]    ->setStyleSheet("background-color:rgb(06,86,159);");
        labelDelay[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelPriority[NUMOFCH]  ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudio[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");

        for( int i=0; i<NUMOFCH; i++)
        {
            buttonSourceUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonSourceUp[i]->setIconSize(QSize(60,60));
            buttonSourceDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonSourceDn[i]->setIconSize(QSize(60,60));

            buttonDelayUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonDelayUp[i]->setIconSize(QSize(60,60));
            buttonDelayDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonDelayDn[i]->setIconSize(QSize(60,60));

            buttonPriorityUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonPriorityUp[i]->setIconSize(QSize(60,60));
            buttonPriorityDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonPriorityDn[i]->setIconSize(QSize(60,60));

            buttonAudioUp[i]->setIcon(QIcon(":/images/arrow_up.png"));
            buttonAudioUp[i]->setIconSize(QSize(60,60));
            buttonAudioDn[i]->setIcon(QIcon(":/images/arrow_down.png"));
            buttonAudioDn[i]->setIconSize(QSize(60,60));

            labelTrigger[i]->setStyleSheet("font:58px;");
        }

        if( utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:50px;");
            }
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
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0 )
        {
            buttonDefault->resize(350, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    connect(buttonSourceAll,     SIGNAL(clicked()), this, SLOT(onButtonSourceAll()));
    connect(buttonDelayAll,      SIGNAL(clicked()), this, SLOT(onButtonDelayAll()));
    connect(buttonPriorityAll,   SIGNAL(clicked()), this, SLOT(onButtonPriorityAll()));
    connect(buttonAudioAll,      SIGNAL(clicked()), this, SLOT(onButtonAudioAll()));

    connect(buttonSourceUp[0],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp1()));
    connect(buttonSourceUp[1],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp2()));
    connect(buttonSourceUp[2],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp3()));
    connect(buttonSourceUp[3],   SIGNAL(clicked()), this, SLOT(onButtonSourceUp4()));

    connect(buttonSourceDn[0],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn1()));
    connect(buttonSourceDn[1],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn2()));
    connect(buttonSourceDn[2],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn3()));
    connect(buttonSourceDn[3],   SIGNAL(clicked()), this, SLOT(onButtonSourceDn4()));

    connect(buttonDelayUp[0],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp1()));
    connect(buttonDelayUp[1],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp2()));
    connect(buttonDelayUp[2],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp3()));
    connect(buttonDelayUp[3],    SIGNAL(clicked()), this, SLOT(onButtonDelayUp4()));

    connect(buttonDelayDn[0],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn1()));
    connect(buttonDelayDn[1],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn2()));
    connect(buttonDelayDn[2],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn3()));
    connect(buttonDelayDn[3],    SIGNAL(clicked()), this, SLOT(onButtonDelayDn4()));

    connect(buttonPriorityUp[0], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp1()));
    connect(buttonPriorityUp[1], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp2()));
    connect(buttonPriorityUp[2], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp3()));
    connect(buttonPriorityUp[3], SIGNAL(clicked()), this, SLOT(onButtonPriorityUp4()));

    connect(buttonPriorityDn[0], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn1()));
    connect(buttonPriorityDn[1], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn2()));
    connect(buttonPriorityDn[2], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn3()));
    connect(buttonPriorityDn[3], SIGNAL(clicked()), this, SLOT(onButtonPriorityDn4()));

    connect(buttonAudioUp[0],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp1()));
    connect(buttonAudioUp[1],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp2()));
    connect(buttonAudioUp[2],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp3()));
    connect(buttonAudioUp[3],    SIGNAL(clicked()), this, SLOT(onButtonAudioUp4()));

    connect(buttonAudioDn[0],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn1()));
    connect(buttonAudioDn[1],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn2()));
    connect(buttonAudioDn[2],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn3()));
    connect(buttonAudioDn[3],    SIGNAL(clicked()), this, SLOT(onButtonAudioDn4()));

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

#elif defined(HI3531D)
TriggerInputDialog::TriggerInputDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::TriggerInputDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        buttonSourceAll   = ui720.buttonSourceAll;
        buttonDelayAll    = ui720.buttonDelayAll;
        buttonPriorityAll = ui720.buttonPriorityAll;
        buttonAudioAll    = ui720.buttonAudioAll;
        buttonMarkerAll   = ui720.buttonMarkerAll;

        labelTrigger[0]   = ui720.labelTrigger1;
        labelTrigger[1]   = ui720.labelTrigger2;
        labelTrigger[2]   = ui720.labelTrigger3;
        labelTrigger[3]   = ui720.labelTrigger4;
        labelTrigger[4]   = ui720.labelTrigger5;
        labelTrigger[5]   = ui720.labelTrigger6;
        labelTrigger[6]   = ui720.labelTrigger7;
        labelTrigger[7]   = ui720.labelTrigger8;

        labelAll          = ui720.labelAll;
        labelSourceAll    = ui720.labelSourceAll;
        labelDelayAll     = ui720.labelDelayAll;
        labelPriorityAll  = ui720.labelPriorityAll;
        labelAudioAll     = ui720.labelAudioAll;
        labelMarkerAll    = ui720.labelMarkerAll;

        buttonSource[0]   = ui720.buttonSource1;
        buttonSource[1]   = ui720.buttonSource2;
        buttonSource[2]   = ui720.buttonSource3;
        buttonSource[3]   = ui720.buttonSource4;
        buttonSource[4]   = ui720.buttonSource5;
        buttonSource[5]   = ui720.buttonSource6;
        buttonSource[6]   = ui720.buttonSource7;
        buttonSource[7]   = ui720.buttonSource8;

        buttonDelay[0]    = ui720.buttonDelay1;
        buttonDelay[1]    = ui720.buttonDelay2;
        buttonDelay[2]    = ui720.buttonDelay3;
        buttonDelay[3]    = ui720.buttonDelay4;
        buttonDelay[4]    = ui720.buttonDelay5;
        buttonDelay[5]    = ui720.buttonDelay6;
        buttonDelay[6]    = ui720.buttonDelay7;
        buttonDelay[7]    = ui720.buttonDelay8;

        buttonPriority[0] = ui720.buttonPriority1;
        buttonPriority[1] = ui720.buttonPriority2;
        buttonPriority[2] = ui720.buttonPriority3;
        buttonPriority[3] = ui720.buttonPriority4;
        buttonPriority[4] = ui720.buttonPriority5;
        buttonPriority[5] = ui720.buttonPriority6;
        buttonPriority[6] = ui720.buttonPriority7;
        buttonPriority[7] = ui720.buttonPriority8;

        buttonAudio[0]    = ui720.buttonAudio1;
        buttonAudio[1]    = ui720.buttonAudio2;
        buttonAudio[2]    = ui720.buttonAudio3;
        buttonAudio[3]    = ui720.buttonAudio4;
        buttonAudio[4]    = ui720.buttonAudio5;
        buttonAudio[5]    = ui720.buttonAudio6;
        buttonAudio[6]    = ui720.buttonAudio7;
        buttonAudio[7]    = ui720.buttonAudio8;

        buttonMarker[0]   = ui720.buttonMarker1;
        buttonMarker[1]   = ui720.buttonMarker2;
        buttonMarker[2]   = ui720.buttonMarker3;
        buttonMarker[3]   = ui720.buttonMarker4;
        buttonMarker[4]   = ui720.buttonMarker5;
        buttonMarker[5]   = ui720.buttonMarker6;
        buttonMarker[6]   = ui720.buttonMarker7;
        buttonMarker[7]   = ui720.buttonMarker8;

        buttonDefault     = ui720.buttonDefault;
        buttonEditMarker  = ui720.buttonEditMarker;
        buttonSave        = ui720.buttonSave;
        buttonClose       = ui720.buttonClose;

        buttonSourceAll   ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonDelayAll    ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonPriorityAll ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudioAll    ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonMarkerAll   ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

        for( int i=0; i<NUMOFCH; i++)
        {
            labelTrigger[i]  ->setStyleSheet("font:38px;");

            buttonSource[i]  ->setStyleSheet("font:38px;");
            buttonDelay[i]   ->setStyleSheet("font:38px");
            buttonPriority[i]->setStyleSheet("font:38px;");
            buttonAudio[i]   ->setStyleSheet("font:38px");
            buttonMarker[i]  ->setStyleSheet("font:38px");
        }
        labelAll          ->setStyleSheet("background-color:rgb(06,86,159); font:38px;");
        labelSourceAll    ->setStyleSheet("background-color:rgb(06,86,159);");
        labelDelayAll     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelPriorityAll  ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudioAll     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelMarkerAll    ->setStyleSheet("background-color:rgb(06,86,159);");

        if( utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:32px;");
            }
            buttonEditMarker->resize(241, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0 )
        {
            buttonEditMarker->resize(251, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0 )
        {
            buttonDefault->resize(281, 91);
            buttonEditMarker->setGeometry(321, 600, 261, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0 )
        {
            buttonEditMarker->resize(251, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:34px;");
            }
            buttonDefault->resize(281, 91);
            buttonEditMarker->setGeometry(321, 600, 261, 91);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0 )
        {
            buttonDefault->resize(241, 91);
            buttonEditMarker->setGeometry(281, 600, 201, 91);
        }
    }
    else
    {
        Ui::TriggerInputDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        buttonSourceAll   = ui1080.buttonSourceAll;
        buttonDelayAll    = ui1080.buttonDelayAll;
        buttonPriorityAll = ui1080.buttonPriorityAll;
        buttonAudioAll    = ui1080.buttonAudioAll;
        buttonMarkerAll   = ui1080.buttonMarkerAll;

        labelTrigger[0]   = ui1080.labelTrigger1;
        labelTrigger[1]   = ui1080.labelTrigger2;
        labelTrigger[2]   = ui1080.labelTrigger3;
        labelTrigger[3]   = ui1080.labelTrigger4;
        labelTrigger[4]   = ui1080.labelTrigger5;
        labelTrigger[5]   = ui1080.labelTrigger6;
        labelTrigger[6]   = ui1080.labelTrigger7;
        labelTrigger[7]   = ui1080.labelTrigger8;

        labelAll          = ui1080.labelAll;
        labelSourceAll    = ui1080.labelSourceAll;
        labelDelayAll     = ui1080.labelDelayAll;
        labelPriorityAll  = ui1080.labelPriorityAll;
        labelAudioAll     = ui1080.labelAudioAll;
        labelMarkerAll    = ui1080.labelMarkerAll;

        buttonSource[0]   = ui1080.buttonSource1;
        buttonSource[1]   = ui1080.buttonSource2;
        buttonSource[2]   = ui1080.buttonSource3;
        buttonSource[3]   = ui1080.buttonSource4;
        buttonSource[4]   = ui1080.buttonSource5;
        buttonSource[5]   = ui1080.buttonSource6;
        buttonSource[6]   = ui1080.buttonSource7;
        buttonSource[7]   = ui1080.buttonSource8;

        buttonDelay[0]    = ui1080.buttonDelay1;
        buttonDelay[1]    = ui1080.buttonDelay2;
        buttonDelay[2]    = ui1080.buttonDelay3;
        buttonDelay[3]    = ui1080.buttonDelay4;
        buttonDelay[4]    = ui1080.buttonDelay5;
        buttonDelay[5]    = ui1080.buttonDelay6;
        buttonDelay[6]    = ui1080.buttonDelay7;
        buttonDelay[7]    = ui1080.buttonDelay8;

        buttonPriority[0] = ui1080.buttonPriority1;
        buttonPriority[1] = ui1080.buttonPriority2;
        buttonPriority[2] = ui1080.buttonPriority3;
        buttonPriority[3] = ui1080.buttonPriority4;
        buttonPriority[4] = ui1080.buttonPriority5;
        buttonPriority[5] = ui1080.buttonPriority6;
        buttonPriority[6] = ui1080.buttonPriority7;
        buttonPriority[7] = ui1080.buttonPriority8;

        buttonAudio[0]    = ui1080.buttonAudio1;
        buttonAudio[1]    = ui1080.buttonAudio2;
        buttonAudio[2]    = ui1080.buttonAudio3;
        buttonAudio[3]    = ui1080.buttonAudio4;
        buttonAudio[4]    = ui1080.buttonAudio5;
        buttonAudio[5]    = ui1080.buttonAudio6;
        buttonAudio[6]    = ui1080.buttonAudio7;
        buttonAudio[7]    = ui1080.buttonAudio8;

        buttonMarker[0]   = ui1080.buttonMarker1;
        buttonMarker[1]   = ui1080.buttonMarker2;
        buttonMarker[2]   = ui1080.buttonMarker3;
        buttonMarker[3]   = ui1080.buttonMarker4;
        buttonMarker[4]   = ui1080.buttonMarker5;
        buttonMarker[5]   = ui1080.buttonMarker6;
        buttonMarker[6]   = ui1080.buttonMarker7;
        buttonMarker[7]   = ui1080.buttonMarker8;

        buttonDefault     = ui1080.buttonDefault;
        buttonEditMarker  = ui1080.buttonEditMarker;
        buttonSave        = ui1080.buttonSave;
        buttonClose       = ui1080.buttonClose;

        buttonSourceAll   ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonDelayAll    ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonPriorityAll ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudioAll    ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonMarkerAll   ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

        for( int i=0; i<NUMOFCH; i++)
        {
            labelTrigger[i]  ->setStyleSheet("font:60px;");

            buttonSource[i]  ->setStyleSheet("font:60px;");
            buttonDelay[i]   ->setStyleSheet("font:60px");
            buttonPriority[i]->setStyleSheet("font:60px;");
            buttonAudio[i]   ->setStyleSheet("font:60px");
            buttonMarker[i]  ->setStyleSheet("font:60px");
        }
        labelAll          ->setStyleSheet("background-color:rgb(06,86,159); font:60px;");
        labelSourceAll    ->setStyleSheet("background-color:rgb(06,86,159);");
        labelDelayAll     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelPriorityAll  ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudioAll     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelMarkerAll    ->setStyleSheet("background-color:rgb(06,86,159);");

        if( utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:50px;");
            }
            buttonEditMarker->resize(351, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0 )
        {
            buttonEditMarker->resize(351, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0 )
        {
            buttonDefault->resize(381, 131);
            buttonEditMarker->setGeometry(441, 910, 361, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0 )
        {
            buttonEditMarker->resize(351, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0 )
        {
            for(int i=0; i<NUMOFCH; i++)
            {
                labelTrigger[i]->setStyleSheet("font:50px;");
            }
            buttonDefault->resize(381, 131);
            buttonEditMarker->setGeometry(441, 910, 351, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0 )
        {
            buttonDefault->resize(331, 131);
            buttonEditMarker->setGeometry(390, 910, 301, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    connect(buttonSourceAll,    SIGNAL(clicked()), this, SLOT(onButtonSourceAll()));
    connect(buttonDelayAll,     SIGNAL(clicked()), this, SLOT(onButtonDelayAll()));
    connect(buttonPriorityAll,  SIGNAL(clicked()), this, SLOT(onButtonPriorityAll()));
    connect(buttonAudioAll,     SIGNAL(clicked()), this, SLOT(onButtonAudioAll()));
    connect(buttonMarkerAll,    SIGNAL(clicked()), this, SLOT(onButtonMarkerAll()));

    connect(buttonSource[0],    SIGNAL(clicked()), this, SLOT(onButtonSource1()));
    connect(buttonSource[1],    SIGNAL(clicked()), this, SLOT(onButtonSource2()));
    connect(buttonSource[2],    SIGNAL(clicked()), this, SLOT(onButtonSource3()));
    connect(buttonSource[3],    SIGNAL(clicked()), this, SLOT(onButtonSource4()));
    connect(buttonSource[4],    SIGNAL(clicked()), this, SLOT(onButtonSource5()));
    connect(buttonSource[5],    SIGNAL(clicked()), this, SLOT(onButtonSource6()));
    connect(buttonSource[6],    SIGNAL(clicked()), this, SLOT(onButtonSource7()));
    connect(buttonSource[7],    SIGNAL(clicked()), this, SLOT(onButtonSource8()));

    connect(buttonDelay[0],     SIGNAL(clicked()), this, SLOT(onButtonDelay1()));
    connect(buttonDelay[1],     SIGNAL(clicked()), this, SLOT(onButtonDelay2()));
    connect(buttonDelay[2],     SIGNAL(clicked()), this, SLOT(onButtonDelay3()));
    connect(buttonDelay[3],     SIGNAL(clicked()), this, SLOT(onButtonDelay4()));
    connect(buttonDelay[4],     SIGNAL(clicked()), this, SLOT(onButtonDelay5()));
    connect(buttonDelay[5],     SIGNAL(clicked()), this, SLOT(onButtonDelay6()));
    connect(buttonDelay[6],     SIGNAL(clicked()), this, SLOT(onButtonDelay7()));
    connect(buttonDelay[7],     SIGNAL(clicked()), this, SLOT(onButtonDelay8()));

    connect(buttonPriority[0],  SIGNAL(clicked()), this, SLOT(onButtonPriority1()));
    connect(buttonPriority[1],  SIGNAL(clicked()), this, SLOT(onButtonPriority2()));
    connect(buttonPriority[2],  SIGNAL(clicked()), this, SLOT(onButtonPriority3()));
    connect(buttonPriority[3],  SIGNAL(clicked()), this, SLOT(onButtonPriority4()));
    connect(buttonPriority[4],  SIGNAL(clicked()), this, SLOT(onButtonPriority5()));
    connect(buttonPriority[5],  SIGNAL(clicked()), this, SLOT(onButtonPriority6()));
    connect(buttonPriority[6],  SIGNAL(clicked()), this, SLOT(onButtonPriority7()));
    connect(buttonPriority[7],  SIGNAL(clicked()), this, SLOT(onButtonPriority8()));

    connect(buttonAudio[0],     SIGNAL(clicked()), this, SLOT(onButtonAudio1()));
    connect(buttonAudio[1],     SIGNAL(clicked()), this, SLOT(onButtonAudio2()));
    connect(buttonAudio[2],     SIGNAL(clicked()), this, SLOT(onButtonAudio3()));
    connect(buttonAudio[3],     SIGNAL(clicked()), this, SLOT(onButtonAudio4()));
    connect(buttonAudio[4],     SIGNAL(clicked()), this, SLOT(onButtonAudio5()));
    connect(buttonAudio[5],     SIGNAL(clicked()), this, SLOT(onButtonAudio6()));
    connect(buttonAudio[6],     SIGNAL(clicked()), this, SLOT(onButtonAudio7()));
    connect(buttonAudio[7],     SIGNAL(clicked()), this, SLOT(onButtonAudio8()));

    connect(buttonMarker[0],    SIGNAL(clicked()), this, SLOT(onButtonMarker1()));
    connect(buttonMarker[1],    SIGNAL(clicked()), this, SLOT(onButtonMarker2()));
    connect(buttonMarker[2],    SIGNAL(clicked()), this, SLOT(onButtonMarker3()));
    connect(buttonMarker[3],    SIGNAL(clicked()), this, SLOT(onButtonMarker4()));
    connect(buttonMarker[4],    SIGNAL(clicked()), this, SLOT(onButtonMarker5()));
    connect(buttonMarker[5],    SIGNAL(clicked()), this, SLOT(onButtonMarker6()));
    connect(buttonMarker[6],    SIGNAL(clicked()), this, SLOT(onButtonMarker7()));
    connect(buttonMarker[7],    SIGNAL(clicked()), this, SLOT(onButtonMarker8()));

    connect(buttonSave,          SIGNAL(clicked()), this, SLOT(onButtonSave()));
    connect(buttonClose,         SIGNAL(clicked()), this, SLOT(reject()));
    connect(buttonDefault,       SIGNAL(clicked()), this, SLOT(onButtonDefault()));
    connect(buttonEditMarker,    SIGNAL(clicked()), this, SLOT(onButtonEditMarker()));

    msgBox           = NULL;
    editMarkerDialog = NULL;

    for(int i=0; i<NUMOFCH; i++)
    {
        labelTrigger[i]->setText(QString("%1%2").arg(tr("Trigger"), QString::number(i+1)));
    }
}
#endif

TriggerInputDialog::~TriggerInputDialog()
{
}
void TriggerInputDialog::initTriggerInputConfig(void)
{
    buttonSourceAll->setFocus();

    //source init
    QString source[8];
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
    QString delay[8];
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
    int priority[8];
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
    QString audio[8];
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

#if 1   //marker config don't exist
    for(int i=0; i<NUMOFCH; i++)
    {
        infoMarker[i] = false;
        updateMarkerLabel(i);
    }
#else
    //Marker init
    QString marker[8];
    marker[0] = QString(DeviceCfg.trigger1_marker);
    marker[1] = QString(DeviceCfg.trigger2_marker);
    marker[2] = QString(DeviceCfg.trigger3_marker);
    marker[3] = QString(DeviceCfg.trigger4_marker);
    marker[4] = QString(DeviceCfg.trigger5_marker);
    marker[5] = QString(DeviceCfg.trigger6_marker);
    marker[6] = QString(DeviceCfg.trigger7_marker);
    marker[7] = QString(DeviceCfg.trigger8_marker);

    for(int i=0; i<NUMOFCH; i++)
    {
        if( marker[i].compare("ON") == 0 )
        {
            infoMarker[i] = true;
        }
        else if( marker[i].compare("OFF") == 0 )
        {
            infoMarker[i] = false;
        }
        else
        {
            qDebug() << "[Error]TriggerInputDialog::initTriggerInputConfig invalid marker config";
            infoMarker[i] = false;
        }
        updateMarkerLabel(i);
    }
#endif
}
void TriggerInputDialog::updateSourceLabel(int ch)
{
    buttonSource[ch]->setText(QString("%1 %2").arg(tr("CAM"), QString::number(infoSource[ch])));
}
void TriggerInputDialog::updateDelayLabel(int ch)
{
    buttonDelay[ch]->setText(QString("%1 %2").arg(QString::number(infoDelay[ch]), tr("Sec")));
}
void TriggerInputDialog::updatePriorityLabel(int ch)
{
    buttonPriority[ch]->setText(QString::number(infoPriority[ch]));
}
void TriggerInputDialog::updateAudioLabel(int ch)
{
    if( infoAudio[ch] )
    {
        buttonAudio[ch]->setText(tr("Output"));
    }
    else
    {
        buttonAudio[ch]->setText(tr("Mute"));
    }
}
void TriggerInputDialog::updateMarkerLabel(int ch)
{
    if( infoMarker[ch] )
    {
        buttonMarker[ch]->setText(tr("On"));
    }
    else
    {
        buttonMarker[ch]->setText(tr("Off"));
    }
}

void TriggerInputDialog::onButtonSourceAll()
{
    int maxVal = 0;
    int count = 0;

    for(int i=0; i<NUMOFCH; i++)
    {
        if     ( infoSource[i] > maxVal )   { maxVal = infoSource[i]; }
        else if( infoSource[i] == maxVal )  { count++; }
    }

    if( count == NUMOFCH-1 )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            if( maxVal>=NUMOFCH) { maxVal=0; }
            for(int i=0; i<NUMOFCH; i++)
            {
                infoSource[i] = maxVal+1;
                updateSourceLabel(i);
            }
        }
    }
    else
    {
        for( int i=0; i<NUMOFCH; i++)
        {
            infoSource[i] = maxVal;
            updateSourceLabel(i);
        }
    }
}
void TriggerInputDialog::onButtonDelayAll()
{
    int maxVal = -1;
    int count = 0;

    for(int i=0; i<NUMOFCH; i++)
    {
        if     ( infoDelay[i] > maxVal )    { maxVal = infoDelay[i]; }
        else if( infoDelay[i] == maxVal )   { count++; }
    }

    if( count >= NUMOFCH-1 )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            if( maxVal>=20 )   { maxVal=-1; }
            for( int i=0; i<NUMOFCH; i++)
            {
                infoDelay[i] = maxVal+1;
                updateDelayLabel(i);
            }
        }
    }
    else
    {
        for( int i=0; i<NUMOFCH; i++)
        {
            infoDelay[i] = maxVal;
            updateDelayLabel(i);
        }
    }
}
void TriggerInputDialog::onButtonPriorityAll()
{
    if( checkPriorityRedundant() != 0 )
    {
        int checkArr[NUMOFCH];
        memset(checkArr, 0, sizeof(checkArr));

        for(int i=0; i<NUMOFCH; i++)
        {
            if( checkArr[infoPriority[i]-1] == 0 )
            {
                checkArr[infoPriority[i]-1] = 1;
            }
            else
            {
                infoPriority[i] = 0;
            }
        }

        for(int i=0; i<NUMOFCH; i++)
        {
            if( infoPriority[i] == 0 )
            {
                for(int j=0; j<NUMOFCH; j++)
                {
                    if( checkArr[j] == 0 )
                    {
                        infoPriority[i] = j+1;
                        checkArr[j] = 1;
                        updatePriorityLabel(i);
                        break;
                    }
                }
            }
        }
    }
}
void TriggerInputDialog::onButtonAudioAll()
{
    int countT = 0, countF = 0;

    for( int i=0; i<NUMOFCH; i++)
    {
        if(infoAudio[i] == false )  { countF++; }
        else                        { countT++; }
    }

    if( countT == NUMOFCH )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoAudio[i] = false;
            updateAudioLabel(i);
        }
    }
    else if( countF == NUMOFCH )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoAudio[i] = true;
            updateAudioLabel(i);
        }
    }
    else if( countT >= NUMOFCH/2 )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoAudio[i] = true;
            updateAudioLabel(i);
        }
    }
    else
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoAudio[i] = false;
            updateAudioLabel(i);
        }
    }
}
void TriggerInputDialog::onButtonMarkerAll()
{
    int countT = 0, countF = 0;

    for( int i=0; i<NUMOFCH; i++)
    {
        if(infoMarker[i] == false ) { countF++; }
        else                        { countT++; }
    }

    if( countT == NUMOFCH )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoMarker[i] = false;
            updateMarkerLabel(i);
        }
    }
    else if( countF == NUMOFCH )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoMarker[i] = true;
            updateMarkerLabel(i);
        }
    }
    else if( countT >= NUMOFCH/2 )
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoMarker[i] = true;
            updateMarkerLabel(i);
        }
    }
    else
    {
        for(int i=0; i<NUMOFCH; i++)
        {
            infoMarker[i] = false;
            updateMarkerLabel(i);
        }
    }
}
void TriggerInputDialog::onButtonSource1()      { onButtonSource(0); }
void TriggerInputDialog::onButtonSource2()      { onButtonSource(1); }
void TriggerInputDialog::onButtonSource3()      { onButtonSource(2); }
void TriggerInputDialog::onButtonSource4()      { onButtonSource(3); }
void TriggerInputDialog::onButtonSource5()      { onButtonSource(4); }
void TriggerInputDialog::onButtonSource6()      { onButtonSource(5); }
void TriggerInputDialog::onButtonSource7()      { onButtonSource(6); }
void TriggerInputDialog::onButtonSource8()      { onButtonSource(7); }
void TriggerInputDialog::onButtonSource(int ch)
{
    infoSource[ch]++;
    if( infoSource[ch]>devInfo.videoNum )       { infoSource[ch] = 1; }
    updateSourceLabel(ch);
}
void TriggerInputDialog::onButtonDelay1()       { onButtonDelay(0); }
void TriggerInputDialog::onButtonDelay2()       { onButtonDelay(1); }
void TriggerInputDialog::onButtonDelay3()       { onButtonDelay(2); }
void TriggerInputDialog::onButtonDelay4()       { onButtonDelay(3); }
void TriggerInputDialog::onButtonDelay5()       { onButtonDelay(4); }
void TriggerInputDialog::onButtonDelay6()       { onButtonDelay(5); }
void TriggerInputDialog::onButtonDelay7()       { onButtonDelay(6); }
void TriggerInputDialog::onButtonDelay8()       { onButtonDelay(7); }
void TriggerInputDialog::onButtonDelay(int ch)
{
    infoDelay[ch]++;
    if( infoDelay[ch]>20)                       { infoDelay[ch] = 0; }
    updateDelayLabel(ch);
}
void TriggerInputDialog::onButtonPriority1()    { onButtonPriority(0); }
void TriggerInputDialog::onButtonPriority2()    { onButtonPriority(1); }
void TriggerInputDialog::onButtonPriority3()    { onButtonPriority(2); }
void TriggerInputDialog::onButtonPriority4()    { onButtonPriority(3); }
void TriggerInputDialog::onButtonPriority5()    { onButtonPriority(4); }
void TriggerInputDialog::onButtonPriority6()    { onButtonPriority(5); }
void TriggerInputDialog::onButtonPriority7()    { onButtonPriority(6); }
void TriggerInputDialog::onButtonPriority8()    { onButtonPriority(7); }
void TriggerInputDialog::onButtonPriority(int ch)
{
    infoPriority[ch]++;
    if( infoPriority[ch]>devInfo.videoNum )     { infoPriority[ch] = 1; }
    updatePriorityLabel(ch);
}
void TriggerInputDialog::onButtonAudio1()       { onButtonAudio(0); }
void TriggerInputDialog::onButtonAudio2()       { onButtonAudio(1); }
void TriggerInputDialog::onButtonAudio3()       { onButtonAudio(2); }
void TriggerInputDialog::onButtonAudio4()       { onButtonAudio(3); }
void TriggerInputDialog::onButtonAudio5()       { onButtonAudio(4); }
void TriggerInputDialog::onButtonAudio6()       { onButtonAudio(5); }
void TriggerInputDialog::onButtonAudio7()       { onButtonAudio(6); }
void TriggerInputDialog::onButtonAudio8()       { onButtonAudio(7); }
void TriggerInputDialog::onButtonAudio(int ch)
{
    infoAudio[ch] = !infoAudio[ch];
    updateAudioLabel(ch);
}
void TriggerInputDialog::onButtonMarker1()      { onButtonMarker(0); }
void TriggerInputDialog::onButtonMarker2()      { onButtonMarker(1); }
void TriggerInputDialog::onButtonMarker3()      { onButtonMarker(2); }
void TriggerInputDialog::onButtonMarker4()      { onButtonMarker(3); }
void TriggerInputDialog::onButtonMarker5()      { onButtonMarker(4); }
void TriggerInputDialog::onButtonMarker6()      { onButtonMarker(5); }
void TriggerInputDialog::onButtonMarker7()      { onButtonMarker(6); }
void TriggerInputDialog::onButtonMarker8()      { onButtonMarker(7); }
void TriggerInputDialog::onButtonMarker(int ch)
{
    infoMarker[ch] = !infoMarker[ch];
    updateMarkerLabel(ch);
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
#if defined(HI3521)
void TriggerInputDialog::onButtonSave()
{
    //save source
    for(int i=0; i<NUMOFCH; i++)
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
    for(int i=0; i<NUMOFCH; i++)
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
    for(int i=0; i<NUMOFCH; i++)
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
    for(int i=0; i<NUMOFCH; i++)
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

#elif defined(HI3531D)
void TriggerInputDialog::onButtonSave()
{
    //save source
    for(int i=0; i<NUMOFCH; i++)
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
    for(int i=0; i<NUMOFCH; i++)
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
    for(int i=0; i<NUMOFCH; i++)
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
    for(int i=0; i<NUMOFCH; i++)
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
/*  //marker config don't exist
    //save Marker
    for(int i=0; i<NUMOFCH; i++)
    {
        char *dst;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.trigger1_marker; break; }
            case 1 :    { dst = DeviceCfg.trigger2_marker; break; }
            case 2 :    { dst = DeviceCfg.trigger3_marker; break; }
            case 3 :    { dst = DeviceCfg.trigger4_marker; break; }
            case 4 :    { dst = DeviceCfg.trigger5_marker; break; }
            case 5 :    { dst = DeviceCfg.trigger6_marker; break; }
            case 6 :    { dst = DeviceCfg.trigger7_marker; break; }
            case 7 :    { dst = DeviceCfg.trigger8_marker; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            QString src;
            if( infoMarker[i] ) { src = "ON"; }
            else                { src = "OFF";   }

            utils_cfg_cpy_item( dst, src.toStdString().c_str());
        }
    }
*/
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
         infoMarker[i]=false;

         updateSourceLabel(i);
         updateDelayLabel(i);
         updatePriorityLabel(i);
         updateAudioLabel(i);
         updateMarkerLabel(i);
    }
}
void TriggerInputDialog::onButtonEditMarker()
{
    this->setWindowOpacity(0);
    emit makeTransparent(1);
    emit viewMarkerEdit(1);

    if( editMarkerDialog )
    {
        delete editMarkerDialog;
        editMarkerDialog = NULL;
    }

    editMarkerDialog = new EditMarkerDialog(this);
    connect(editMarkerDialog, SIGNAL(changeMarkerChannel(int)), this, SLOT(onChangeMarkerChannel(int)));
    connect(editMarkerDialog, SIGNAL(updateMarker(QPoint, QPoint, QPoint, QPoint)), this, SLOT(onUpdateMarker(QPoint, QPoint, QPoint, QPoint)));

    editMarkerDialog->move(0,0);
    editMarkerDialog->raise();

    int ch=0;
    for(int i=devInfo.videoNum-1; i>=0; i--)
    {
        if( infoMarker[i] ) { ch =i; }
    }
    editMarkerDialog->initMarker(ch);

    if( editMarkerDialog->exec() )
    {
        emit viewMarkerEdit(0);
        emit makeTransparent(0);
        this->setWindowOpacity(1);
    }

    delete editMarkerDialog;
    editMarkerDialog = NULL;
}
void TriggerInputDialog::onChangeMarkerChannel(int ch)
{
    emit changeMarkerChannel(ch);
}
void TriggerInputDialog::onUpdateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4)
{
    emit updateMarker(p1, p2, p3, p4);
}

#if defined(HI3521)
void TriggerInputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonDefault      ->setFocus(); }
            else if( buttonSourceUp[0]  ->hasFocus() )      { buttonSourceAll    ->setFocus(); }
            else if( buttonSourceUp[1]  ->hasFocus() )      { buttonSourceDn[0]  ->setFocus(); }
            else if( buttonSourceUp[2]  ->hasFocus() )      { buttonSourceDn[1]  ->setFocus(); }
            else if( buttonSourceUp[3]  ->hasFocus() )      { buttonSourceDn[2]  ->setFocus(); }

            else if( buttonSourceDn[0]  ->hasFocus() )      { buttonSourceUp[0]  ->setFocus(); }
            else if( buttonSourceDn[1]  ->hasFocus() )      { buttonSourceUp[1]  ->setFocus(); }
            else if( buttonSourceDn[2]  ->hasFocus() )      { buttonSourceUp[2]  ->setFocus(); }
            else if( buttonSourceDn[3]  ->hasFocus() )      { buttonSourceUp[3]  ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonDelayDn[3]   ->setFocus(); }
            else if( buttonDelayUp[0]   ->hasFocus() )      { buttonDelayAll     ->setFocus(); }
            else if( buttonDelayUp[1]   ->hasFocus() )      { buttonDelayDn[0]   ->setFocus(); }
            else if( buttonDelayUp[2]   ->hasFocus() )      { buttonDelayDn[1]   ->setFocus(); }
            else if( buttonDelayUp[3]   ->hasFocus() )      { buttonDelayDn[2]   ->setFocus(); }

            else if( buttonDelayDn[0]   ->hasFocus() )      { buttonDelayUp[0]   ->setFocus(); }
            else if( buttonDelayDn[1]   ->hasFocus() )      { buttonDelayUp[1]   ->setFocus(); }
            else if( buttonDelayDn[2]   ->hasFocus() )      { buttonDelayUp[2]   ->setFocus(); }
            else if( buttonDelayDn[3]   ->hasFocus() )      { buttonDelayUp[3]   ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonSave         ->setFocus(); }
            else if( buttonPriorityUp[0]->hasFocus() )      { buttonPriorityAll  ->setFocus(); }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonClose        ->setFocus(); }
            else if( buttonAudioUp[0]   ->hasFocus() )      { buttonAudioAll     ->setFocus(); }
            else if( buttonAudioUp[1]   ->hasFocus() )      { buttonAudioDn[0]   ->setFocus(); }
            else if( buttonAudioUp[2]   ->hasFocus() )      { buttonAudioDn[1]   ->setFocus(); }
            else if( buttonAudioUp[3]   ->hasFocus() )      { buttonAudioDn[2]   ->setFocus(); }

            else if( buttonAudioDn[0]   ->hasFocus() )      { buttonAudioUp[0]   ->setFocus(); }
            else if( buttonAudioDn[1]   ->hasFocus() )      { buttonAudioUp[1]   ->setFocus(); }
            else if( buttonAudioDn[2]   ->hasFocus() )      { buttonAudioUp[2]   ->setFocus(); }
            else if( buttonAudioDn[3]   ->hasFocus() )      { buttonAudioUp[3]   ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonSourceDn[3]  ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonAudioDn[3]   ->setFocus(); }

            break;
        }
        case Qt::Key_Down:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonSourceUp[0]  ->setFocus(); }
            else if( buttonSourceUp[0]  ->hasFocus() )      { buttonSourceDn[0]  ->setFocus(); }
            else if( buttonSourceUp[1]  ->hasFocus() )      { buttonSourceDn[1]  ->setFocus(); }
            else if( buttonSourceUp[2]  ->hasFocus() )      { buttonSourceDn[2]  ->setFocus(); }
            else if( buttonSourceUp[3]  ->hasFocus() )      { buttonSourceDn[3]  ->setFocus(); }

            else if( buttonSourceDn[0]  ->hasFocus() )      { buttonSourceUp[1]  ->setFocus(); }
            else if( buttonSourceDn[1]  ->hasFocus() )      { buttonSourceUp[2]  ->setFocus(); }
            else if( buttonSourceDn[2]  ->hasFocus() )      { buttonSourceUp[3]  ->setFocus(); }
            else if( buttonSourceDn[3]  ->hasFocus() )      { buttonDefault      ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonDelayUp[0]   ->setFocus(); }
            else if( buttonDelayUp[0]   ->hasFocus() )      { buttonDelayDn[0]   ->setFocus(); }
            else if( buttonDelayUp[1]   ->hasFocus() )      { buttonDelayDn[1]   ->setFocus(); }
            else if( buttonDelayUp[2]   ->hasFocus() )      { buttonDelayDn[2]   ->setFocus(); }
            else if( buttonDelayUp[3]   ->hasFocus() )      { buttonDelayDn[3]   ->setFocus(); }

            else if( buttonDelayDn[0]   ->hasFocus() )      { buttonDelayUp[1]   ->setFocus(); }
            else if( buttonDelayDn[1]   ->hasFocus() )      { buttonDelayUp[2]   ->setFocus(); }
            else if( buttonDelayDn[2]   ->hasFocus() )      { buttonDelayUp[3]   ->setFocus(); }
            else if( buttonDelayDn[3]   ->hasFocus() )      { buttonDelayAll     ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonPriorityUp[0]->hasFocus() )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonSave         ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonAudioUp[0]   ->setFocus(); }
            else if( buttonAudioUp[0]   ->hasFocus() )      { buttonAudioDn[0]   ->setFocus(); }
            else if( buttonAudioUp[1]   ->hasFocus() )      { buttonAudioDn[1]   ->setFocus(); }
            else if( buttonAudioUp[2]   ->hasFocus() )      { buttonAudioDn[2]   ->setFocus(); }
            else if( buttonAudioUp[3]   ->hasFocus() )      { buttonAudioDn[3]   ->setFocus(); }

            else if( buttonAudioDn[0]   ->hasFocus() )      { buttonAudioUp[1]   ->setFocus(); }
            else if( buttonAudioDn[1]   ->hasFocus() )      { buttonAudioUp[2]   ->setFocus(); }
            else if( buttonAudioDn[2]   ->hasFocus() )      { buttonAudioUp[3]   ->setFocus(); }
            else if( buttonAudioDn[3]   ->hasFocus() )      { buttonClose        ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonSourceAll    ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonPriorityAll  ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonAudioAll     ->setFocus(); }

            break;
        }
        case Qt::Key_Left:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonAudioAll     ->setFocus(); }
            else if( buttonSourceUp[0]  ->hasFocus() )      { buttonAudioUp[0]   ->setFocus(); }
            else if( buttonSourceUp[1]  ->hasFocus() )      { buttonAudioUp[1]   ->setFocus(); }
            else if( buttonSourceUp[2]  ->hasFocus() )      { buttonAudioUp[2]   ->setFocus(); }
            else if( buttonSourceUp[3]  ->hasFocus() )      { buttonAudioUp[3]   ->setFocus(); }

            else if( buttonSourceDn[0]  ->hasFocus() )      { buttonAudioDn[0]   ->setFocus(); }
            else if( buttonSourceDn[1]  ->hasFocus() )      { buttonAudioDn[1]   ->setFocus(); }
            else if( buttonSourceDn[2]  ->hasFocus() )      { buttonAudioDn[2]   ->setFocus(); }
            else if( buttonSourceDn[3]  ->hasFocus() )      { buttonAudioDn[3]   ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonSourceAll    ->setFocus(); }
            else if( buttonDelayUp[0]   ->hasFocus() )      { buttonSourceUp[0]  ->setFocus(); }
            else if( buttonDelayUp[1]   ->hasFocus() )      { buttonSourceUp[1]  ->setFocus(); }
            else if( buttonDelayUp[2]   ->hasFocus() )      { buttonSourceUp[2]  ->setFocus(); }
            else if( buttonDelayUp[3]   ->hasFocus() )      { buttonSourceUp[3]  ->setFocus(); }

            else if( buttonDelayDn[0]   ->hasFocus() )      { buttonSourceDn[0]  ->setFocus(); }
            else if( buttonDelayDn[1]   ->hasFocus() )      { buttonSourceDn[1]  ->setFocus(); }
            else if( buttonDelayDn[2]   ->hasFocus() )      { buttonSourceDn[2]  ->setFocus(); }
            else if( buttonDelayDn[3]   ->hasFocus() )      { buttonSourceDn[3]  ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonDelayAll     ->setFocus(); }
            else if( buttonPriorityUp[0]->hasFocus() )      { buttonDelayUp[0]   ->setFocus(); }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonDelayUp[1]   ->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonDelayUp[2]   ->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonDelayUp[3]   ->setFocus(); }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonDelayDn[0]   ->setFocus(); }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonDelayDn[1]   ->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonDelayDn[2]   ->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonDelayDn[3]   ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonPriorityAll  ->setFocus(); }
            else if( buttonAudioUp[0]   ->hasFocus() )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonAudioUp[1]   ->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonAudioUp[2]   ->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonAudioUp[3]   ->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }

            else if( buttonAudioDn[0]   ->hasFocus() )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonAudioDn[1]   ->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonAudioDn[2]   ->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonAudioDn[3]   ->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonClose        ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonDefault      ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonSave         ->setFocus(); }

            break;
        }
        case Qt::Key_Right:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonDelayAll     ->setFocus(); }
            else if( buttonSourceUp[0]  ->hasFocus() )      { buttonDelayUp[0]   ->setFocus(); }
            else if( buttonSourceUp[1]  ->hasFocus() )      { buttonDelayUp[1]   ->setFocus(); }
            else if( buttonSourceUp[2]  ->hasFocus() )      { buttonDelayUp[2]   ->setFocus(); }
            else if( buttonSourceUp[3]  ->hasFocus() )      { buttonDelayUp[3]   ->setFocus(); }

            else if( buttonSourceDn[0]  ->hasFocus() )      { buttonDelayDn[0]   ->setFocus(); }
            else if( buttonSourceDn[1]  ->hasFocus() )      { buttonDelayDn[1]   ->setFocus(); }
            else if( buttonSourceDn[2]  ->hasFocus() )      { buttonDelayDn[2]   ->setFocus(); }
            else if( buttonSourceDn[3]  ->hasFocus() )      { buttonDelayDn[3]   ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonPriorityAll  ->setFocus(); }
            else if( buttonDelayUp[0]   ->hasFocus() )      { buttonPriorityUp[0]->setFocus(); }
            else if( buttonDelayUp[1]   ->hasFocus() )      { buttonPriorityUp[1]->setFocus(); }
            else if( buttonDelayUp[2]   ->hasFocus() )      { buttonPriorityUp[2]->setFocus(); }
            else if( buttonDelayUp[3]   ->hasFocus() )      { buttonPriorityUp[3]->setFocus(); }

            else if( buttonDelayDn[0]   ->hasFocus() )      { buttonPriorityDn[0]->setFocus(); }
            else if( buttonDelayDn[1]   ->hasFocus() )      { buttonPriorityDn[1]->setFocus(); }
            else if( buttonDelayDn[2]   ->hasFocus() )      { buttonPriorityDn[2]->setFocus(); }
            else if( buttonDelayDn[3]   ->hasFocus() )      { buttonPriorityDn[3]->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonAudioAll     ->setFocus(); }
            else if( buttonPriorityUp[0]->hasFocus() )      { buttonAudioUp[0]   ->setFocus(); }
            else if( buttonPriorityUp[1]->hasFocus() )      { buttonAudioUp[1]   ->setFocus(); }
            else if( buttonPriorityUp[2]->hasFocus() )      { buttonAudioUp[2]   ->setFocus(); }
            else if( buttonPriorityUp[3]->hasFocus() )      { buttonAudioUp[3]   ->setFocus(); }

            else if( buttonPriorityDn[0]->hasFocus() )      { buttonAudioDn[0]   ->setFocus(); }
            else if( buttonPriorityDn[1]->hasFocus() )      { buttonAudioDn[1]   ->setFocus(); }
            else if( buttonPriorityDn[2]->hasFocus() )      { buttonAudioDn[2]   ->setFocus(); }
            else if( buttonPriorityDn[3]->hasFocus() )      { buttonAudioDn[3]   ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonSourceAll    ->setFocus(); }
            else if( buttonAudioUp[0]   ->hasFocus() )      { buttonSourceUp[0]  ->setFocus(); }
            else if( buttonAudioUp[1]   ->hasFocus() )      { buttonSourceUp[1]  ->setFocus(); }
            else if( buttonAudioUp[2]   ->hasFocus() )      { buttonSourceUp[2]  ->setFocus(); }
            else if( buttonAudioUp[3]   ->hasFocus() )      { buttonSourceUp[3]  ->setFocus(); }

            else if( buttonAudioDn[0]   ->hasFocus() )      { buttonSourceDn[0]  ->setFocus(); }
            else if( buttonAudioDn[1]   ->hasFocus() )      { buttonSourceDn[1]  ->setFocus(); }
            else if( buttonAudioDn[2]   ->hasFocus() )      { buttonSourceDn[2]  ->setFocus(); }
            else if( buttonAudioDn[3]   ->hasFocus() )      { buttonSourceDn[3]  ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonSave         ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonClose        ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonDefault      ->setFocus(); }

            break;
        }
        case Qt::Key_Enter:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { onButtonSourceAll();             }
            else if( buttonSourceUp[0]  ->hasFocus() )      { onButtonSourceUp(0);             }
            else if( buttonSourceUp[1]  ->hasFocus() )      { onButtonSourceUp(1);             }
            else if( buttonSourceUp[2]  ->hasFocus() )      { onButtonSourceUp(2);             }
            else if( buttonSourceUp[3]  ->hasFocus() )      { onButtonSourceUp(3);             }

            else if( buttonSourceDn[0]  ->hasFocus() )      { onButtonSourceDn(0);             }
            else if( buttonSourceDn[1]  ->hasFocus() )      { onButtonSourceDn(1);             }
            else if( buttonSourceDn[2]  ->hasFocus() )      { onButtonSourceDn(2);             }
            else if( buttonSourceDn[3]  ->hasFocus() )      { onButtonSourceDn(3);             }

            else if( buttonDelayAll     ->hasFocus() )      { onButtonDelayAll();              }
            else if( buttonDelayUp[0]   ->hasFocus() )      { onButtonDelayUp(0);              }
            else if( buttonDelayUp[1]   ->hasFocus() )      { onButtonDelayUp(1);              }
            else if( buttonDelayUp[2]   ->hasFocus() )      { onButtonDelayUp(2);              }
            else if( buttonDelayUp[3]   ->hasFocus() )      { onButtonDelayUp(3);              }

            else if( buttonDelayDn[0]   ->hasFocus() )      { onButtonDelayDn(0);              }
            else if( buttonDelayDn[1]   ->hasFocus() )      { onButtonDelayDn(1);              }
            else if( buttonDelayDn[2]   ->hasFocus() )      { onButtonDelayDn(2);              }
            else if( buttonDelayDn[3]   ->hasFocus() )      { onButtonDelayDn(3);              }

            else if( buttonPriorityAll  ->hasFocus() )      { onButtonPriorityAll();           }
            else if( buttonPriorityUp[0]->hasFocus() )      { onButtonPriorityUp(0);           }
            else if( buttonPriorityUp[1]->hasFocus() )      { onButtonPriorityUp(1);           }
            else if( buttonPriorityUp[2]->hasFocus() )      { onButtonPriorityUp(2);           }
            else if( buttonPriorityUp[3]->hasFocus() )      { onButtonPriorityUp(3);           }

            else if( buttonPriorityDn[0]->hasFocus() )      { onButtonPriorityDn(0);           }
            else if( buttonPriorityDn[1]->hasFocus() )      { onButtonPriorityDn(1);           }
            else if( buttonPriorityDn[2]->hasFocus() )      { onButtonPriorityDn(2);           }
            else if( buttonPriorityDn[3]->hasFocus() )      { onButtonPriorityDn(3);           }

            else if( buttonAudioAll     ->hasFocus() )      { onButtonAudioAll();              }
            else if( buttonAudioUp[0]   ->hasFocus() )      { onButtonAudioUp(0);              }
            else if( buttonAudioUp[1]   ->hasFocus() )      { onButtonAudioUp(1);              }
            else if( buttonAudioUp[2]   ->hasFocus() )      { onButtonAudioUp(2);              }
            else if( buttonAudioUp[3]   ->hasFocus() )      { onButtonAudioUp(3);              }

            else if( buttonAudioDn[0]   ->hasFocus() )      { onButtonAudioDn(0);              }
            else if( buttonAudioDn[1]   ->hasFocus() )      { onButtonAudioDn(1);              }
            else if( buttonAudioDn[2]   ->hasFocus() )      { onButtonAudioDn(2);              }
            else if( buttonAudioDn[3]   ->hasFocus() )      { onButtonAudioDn(3);              }

            else if( buttonDefault      ->hasFocus() )      { onButtonDefault();               }
            else if( buttonSave         ->hasFocus() )      { onButtonSave();                  }
            else if( buttonClose        ->hasFocus() )      { reject();                        }

            break;
        }
        case Qt::Key_Escape:
        {
            reject();
            break;
        }
    }
}

#elif defined(HI3531D)
void TriggerInputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonDefault         ->setFocus(); }
            else if( buttonSource[0]    ->hasFocus() )      { buttonSourceAll       ->setFocus(); }
            else if( buttonSource[1]    ->hasFocus() )      { buttonSource[0]       ->setFocus(); }
            else if( buttonSource[2]    ->hasFocus() )      { buttonSource[1]       ->setFocus(); }
            else if( buttonSource[3]    ->hasFocus() )      { buttonSource[2]       ->setFocus(); }
            else if( buttonSource[4]    ->hasFocus() )      { buttonSource[3]       ->setFocus(); }
            else if( buttonSource[5]    ->hasFocus() )      { buttonSource[4]       ->setFocus(); }
            else if( buttonSource[6]    ->hasFocus() )      { buttonSource[5]       ->setFocus(); }
            else if( buttonSource[7]    ->hasFocus() )      { buttonSource[6]       ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonEditMarker      ->setFocus(); }
            else if( buttonDelay[0]     ->hasFocus() )      { buttonDelayAll        ->setFocus(); }
            else if( buttonDelay[1]     ->hasFocus() )      { buttonDelay[0]        ->setFocus(); }
            else if( buttonDelay[2]     ->hasFocus() )      { buttonDelay[1]        ->setFocus(); }
            else if( buttonDelay[3]     ->hasFocus() )      { buttonDelay[2]        ->setFocus(); }
            else if( buttonDelay[4]     ->hasFocus() )      { buttonDelay[3]        ->setFocus(); }
            else if( buttonDelay[5]     ->hasFocus() )      { buttonDelay[4]        ->setFocus(); }
            else if( buttonDelay[6]     ->hasFocus() )      { buttonDelay[5]        ->setFocus(); }
            else if( buttonDelay[7]     ->hasFocus() )      { buttonDelay[6]        ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonPriority[7]     ->setFocus(); }
            else if( buttonPriority[0]  ->hasFocus() )      { buttonPriorityAll     ->setFocus(); }
            else if( buttonPriority[1]  ->hasFocus() )      { buttonPriority[0]     ->setFocus(); }
            else if( buttonPriority[2]  ->hasFocus() )      { buttonPriority[1]     ->setFocus(); }
            else if( buttonPriority[3]  ->hasFocus() )      { buttonPriority[2]     ->setFocus(); }
            else if( buttonPriority[4]  ->hasFocus() )      { buttonPriority[3]     ->setFocus(); }
            else if( buttonPriority[5]  ->hasFocus() )      { buttonPriority[4]     ->setFocus(); }
            else if( buttonPriority[6]  ->hasFocus() )      { buttonPriority[5]     ->setFocus(); }
            else if( buttonPriority[7]  ->hasFocus() )      { buttonPriority[6]     ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonSave            ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )      { buttonAudioAll        ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )      { buttonAudio[0]        ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )      { buttonAudio[1]        ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )      { buttonAudio[2]        ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )      { buttonAudio[3]        ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )      { buttonAudio[4]        ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )      { buttonAudio[5]        ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )      { buttonAudio[6]        ->setFocus(); }

            else if( buttonMarkerAll    ->hasFocus() )      { buttonClose           ->setFocus(); }
            else if( buttonMarker[0]    ->hasFocus() )      { buttonMarkerAll       ->setFocus(); }
            else if( buttonMarker[1]    ->hasFocus() )      { buttonMarker[0]       ->setFocus(); }
            else if( buttonMarker[2]    ->hasFocus() )      { buttonMarker[1]       ->setFocus(); }
            else if( buttonMarker[3]    ->hasFocus() )      { buttonMarker[2]       ->setFocus(); }
            else if( buttonMarker[4]    ->hasFocus() )      { buttonMarker[3]       ->setFocus(); }
            else if( buttonMarker[5]    ->hasFocus() )      { buttonMarker[4]       ->setFocus(); }
            else if( buttonMarker[6]    ->hasFocus() )      { buttonMarker[5]       ->setFocus(); }
            else if( buttonMarker[7]    ->hasFocus() )      { buttonMarker[6]       ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonSource[7]       ->setFocus(); }
            else if( buttonEditMarker   ->hasFocus() )      { buttonDelay[7]        ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonAudio[7]        ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonMarker[7]       ->setFocus(); }

            break;
        }
        case Qt::Key_Down:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonSource[0]       ->setFocus(); }
            else if( buttonSource[0]    ->hasFocus() )      { buttonSource[1]       ->setFocus(); }
            else if( buttonSource[1]    ->hasFocus() )      { buttonSource[2]       ->setFocus(); }
            else if( buttonSource[2]    ->hasFocus() )      { buttonSource[3]       ->setFocus(); }
            else if( buttonSource[3]    ->hasFocus() )      { buttonSource[4]       ->setFocus(); }
            else if( buttonSource[4]    ->hasFocus() )      { buttonSource[5]       ->setFocus(); }
            else if( buttonSource[5]    ->hasFocus() )      { buttonSource[6]       ->setFocus(); }
            else if( buttonSource[6]    ->hasFocus() )      { buttonSource[7]       ->setFocus(); }
            else if( buttonSource[7]    ->hasFocus() )      { buttonDefault         ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonDelay[0]        ->setFocus(); }
            else if( buttonDelay[0]     ->hasFocus() )      { buttonDelay[1]        ->setFocus(); }
            else if( buttonDelay[1]     ->hasFocus() )      { buttonDelay[2]        ->setFocus(); }
            else if( buttonDelay[2]     ->hasFocus() )      { buttonDelay[3]        ->setFocus(); }
            else if( buttonDelay[3]     ->hasFocus() )      { buttonDelay[4]        ->setFocus(); }
            else if( buttonDelay[4]     ->hasFocus() )      { buttonDelay[5]        ->setFocus(); }
            else if( buttonDelay[5]     ->hasFocus() )      { buttonDelay[6]        ->setFocus(); }
            else if( buttonDelay[6]     ->hasFocus() )      { buttonDelay[7]        ->setFocus(); }
            else if( buttonDelay[7]     ->hasFocus() )      { buttonEditMarker      ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonPriority[0]     ->setFocus(); }
            else if( buttonPriority[0]  ->hasFocus() )      { buttonPriority[1]     ->setFocus(); }
            else if( buttonPriority[1]  ->hasFocus() )      { buttonPriority[2]     ->setFocus(); }
            else if( buttonPriority[2]  ->hasFocus() )      { buttonPriority[3]     ->setFocus(); }
            else if( buttonPriority[3]  ->hasFocus() )      { buttonPriority[4]     ->setFocus(); }
            else if( buttonPriority[4]  ->hasFocus() )      { buttonPriority[5]     ->setFocus(); }
            else if( buttonPriority[5]  ->hasFocus() )      { buttonPriority[6]     ->setFocus(); }
            else if( buttonPriority[6]  ->hasFocus() )      { buttonPriority[7]     ->setFocus(); }
            else if( buttonPriority[7]  ->hasFocus() )      { buttonPriorityAll     ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonAudio[0]        ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )      { buttonAudio[1]        ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )      { buttonAudio[2]        ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )      { buttonAudio[3]        ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )      { buttonAudio[4]        ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )      { buttonAudio[5]        ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )      { buttonAudio[6]        ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )      { buttonAudio[7]        ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )      { buttonSave            ->setFocus(); }

            else if( buttonMarkerAll    ->hasFocus() )      { buttonMarker[0]       ->setFocus(); }
            else if( buttonMarker[0]    ->hasFocus() )      { buttonMarker[1]       ->setFocus(); }
            else if( buttonMarker[1]    ->hasFocus() )      { buttonMarker[2]       ->setFocus(); }
            else if( buttonMarker[2]    ->hasFocus() )      { buttonMarker[3]       ->setFocus(); }
            else if( buttonMarker[3]    ->hasFocus() )      { buttonMarker[4]       ->setFocus(); }
            else if( buttonMarker[4]    ->hasFocus() )      { buttonMarker[5]       ->setFocus(); }
            else if( buttonMarker[5]    ->hasFocus() )      { buttonMarker[6]       ->setFocus(); }
            else if( buttonMarker[6]    ->hasFocus() )      { buttonMarker[7]       ->setFocus(); }
            else if( buttonMarker[7]    ->hasFocus() )      { buttonClose           ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonSourceAll       ->setFocus(); }
            else if( buttonEditMarker   ->hasFocus() )      { buttonDelayAll        ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonAudioAll        ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonMarkerAll       ->setFocus(); }

            break;
        }
        case Qt::Key_Left:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonMarkerAll       ->setFocus(); }
            else if( buttonSource[0]    ->hasFocus() )      { buttonMarker[0]       ->setFocus(); }
            else if( buttonSource[1]    ->hasFocus() )      { buttonMarker[1]       ->setFocus(); }
            else if( buttonSource[2]    ->hasFocus() )      { buttonMarker[2]       ->setFocus(); }
            else if( buttonSource[3]    ->hasFocus() )      { buttonMarker[3]       ->setFocus(); }
            else if( buttonSource[4]    ->hasFocus() )      { buttonMarker[4]       ->setFocus(); }
            else if( buttonSource[5]    ->hasFocus() )      { buttonMarker[5]       ->setFocus(); }
            else if( buttonSource[6]    ->hasFocus() )      { buttonMarker[6]       ->setFocus(); }
            else if( buttonSource[7]    ->hasFocus() )      { buttonMarker[7]       ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonSourceAll       ->setFocus(); }
            else if( buttonDelay[0]     ->hasFocus() )      { buttonSource[0]       ->setFocus(); }
            else if( buttonDelay[1]     ->hasFocus() )      { buttonSource[1]       ->setFocus(); }
            else if( buttonDelay[2]     ->hasFocus() )      { buttonSource[2]       ->setFocus(); }
            else if( buttonDelay[3]     ->hasFocus() )      { buttonSource[3]       ->setFocus(); }
            else if( buttonDelay[4]     ->hasFocus() )      { buttonSource[4]       ->setFocus(); }
            else if( buttonDelay[5]     ->hasFocus() )      { buttonSource[5]       ->setFocus(); }
            else if( buttonDelay[6]     ->hasFocus() )      { buttonSource[6]       ->setFocus(); }
            else if( buttonDelay[7]     ->hasFocus() )      { buttonSource[7]       ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonDelayAll        ->setFocus(); }
            else if( buttonPriority[0]  ->hasFocus() )      { buttonDelay[0]        ->setFocus(); }
            else if( buttonPriority[1]  ->hasFocus() )      { buttonDelay[1]        ->setFocus(); }
            else if( buttonPriority[2]  ->hasFocus() )      { buttonDelay[2]        ->setFocus(); }
            else if( buttonPriority[3]  ->hasFocus() )      { buttonDelay[3]        ->setFocus(); }
            else if( buttonPriority[4]  ->hasFocus() )      { buttonDelay[4]        ->setFocus(); }
            else if( buttonPriority[5]  ->hasFocus() )      { buttonDelay[5]        ->setFocus(); }
            else if( buttonPriority[6]  ->hasFocus() )      { buttonDelay[6]        ->setFocus(); }
            else if( buttonPriority[7]  ->hasFocus() )      { buttonDelay[7]        ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonPriorityAll     ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )      { buttonPriority[0]     ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )      { buttonPriority[1]     ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )      { buttonPriority[2]     ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )      { buttonPriority[3]     ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )      { buttonPriority[4]     ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )      { buttonPriority[5]     ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )      { buttonPriority[6]     ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )      { buttonPriority[7]     ->setFocus(); }

            else if( buttonMarkerAll    ->hasFocus() )      { buttonAudioAll        ->setFocus(); }
            else if( buttonMarker[0]    ->hasFocus() )      { buttonAudio[0]        ->setFocus(); }
            else if( buttonMarker[1]    ->hasFocus() )      { buttonAudio[1]        ->setFocus(); }
            else if( buttonMarker[2]    ->hasFocus() )      { buttonAudio[2]        ->setFocus(); }
            else if( buttonMarker[3]    ->hasFocus() )      { buttonAudio[3]        ->setFocus(); }
            else if( buttonMarker[4]    ->hasFocus() )      { buttonAudio[4]        ->setFocus(); }
            else if( buttonMarker[5]    ->hasFocus() )      { buttonAudio[5]        ->setFocus(); }
            else if( buttonMarker[6]    ->hasFocus() )      { buttonAudio[6]        ->setFocus(); }
            else if( buttonMarker[7]    ->hasFocus() )      { buttonAudio[7]        ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonClose           ->setFocus(); }
            else if( buttonEditMarker   ->hasFocus() )      { buttonDefault         ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonEditMarker      ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonSave            ->setFocus(); }

            break;
        }
        case Qt::Key_Right:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { buttonDelayAll        ->setFocus(); }
            else if( buttonSource[0]    ->hasFocus() )      { buttonDelay[0]        ->setFocus(); }
            else if( buttonSource[1]    ->hasFocus() )      { buttonDelay[1]        ->setFocus(); }
            else if( buttonSource[2]    ->hasFocus() )      { buttonDelay[2]        ->setFocus(); }
            else if( buttonSource[3]    ->hasFocus() )      { buttonDelay[3]        ->setFocus(); }
            else if( buttonSource[4]    ->hasFocus() )      { buttonDelay[4]        ->setFocus(); }
            else if( buttonSource[5]    ->hasFocus() )      { buttonDelay[5]        ->setFocus(); }
            else if( buttonSource[6]    ->hasFocus() )      { buttonDelay[6]        ->setFocus(); }
            else if( buttonSource[7]    ->hasFocus() )      { buttonDelay[7]        ->setFocus(); }

            else if( buttonDelayAll     ->hasFocus() )      { buttonPriorityAll     ->setFocus(); }
            else if( buttonDelay[0]     ->hasFocus() )      { buttonPriority[0]     ->setFocus(); }
            else if( buttonDelay[1]     ->hasFocus() )      { buttonPriority[1]     ->setFocus(); }
            else if( buttonDelay[2]     ->hasFocus() )      { buttonPriority[2]     ->setFocus(); }
            else if( buttonDelay[3]     ->hasFocus() )      { buttonPriority[3]     ->setFocus(); }
            else if( buttonDelay[4]     ->hasFocus() )      { buttonPriority[4]     ->setFocus(); }
            else if( buttonDelay[5]     ->hasFocus() )      { buttonPriority[5]     ->setFocus(); }
            else if( buttonDelay[6]     ->hasFocus() )      { buttonPriority[6]     ->setFocus(); }
            else if( buttonDelay[7]     ->hasFocus() )      { buttonPriority[7]     ->setFocus(); }

            else if( buttonPriorityAll  ->hasFocus() )      { buttonAudioAll        ->setFocus(); }
            else if( buttonPriority[0]  ->hasFocus() )      { buttonAudio[0]        ->setFocus(); }
            else if( buttonPriority[1]  ->hasFocus() )      { buttonAudio[1]        ->setFocus(); }
            else if( buttonPriority[2]  ->hasFocus() )      { buttonAudio[2]        ->setFocus(); }
            else if( buttonPriority[3]  ->hasFocus() )      { buttonAudio[3]        ->setFocus(); }
            else if( buttonPriority[4]  ->hasFocus() )      { buttonAudio[4]        ->setFocus(); }
            else if( buttonPriority[5]  ->hasFocus() )      { buttonAudio[5]        ->setFocus(); }
            else if( buttonPriority[6]  ->hasFocus() )      { buttonAudio[6]        ->setFocus(); }
            else if( buttonPriority[7]  ->hasFocus() )      { buttonAudio[7]        ->setFocus(); }

            else if( buttonAudioAll     ->hasFocus() )      { buttonMarkerAll       ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )      { buttonMarker[0]       ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )      { buttonMarker[1]       ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )      { buttonMarker[2]       ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )      { buttonMarker[3]       ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )      { buttonMarker[4]       ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )      { buttonMarker[5]       ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )      { buttonMarker[6]       ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )      { buttonMarker[7]       ->setFocus(); }

            else if( buttonMarkerAll    ->hasFocus() )      { buttonSourceAll       ->setFocus(); }
            else if( buttonMarker[0]    ->hasFocus() )      { buttonSource[0]       ->setFocus(); }
            else if( buttonMarker[1]    ->hasFocus() )      { buttonSource[1]       ->setFocus(); }
            else if( buttonMarker[2]    ->hasFocus() )      { buttonSource[2]       ->setFocus(); }
            else if( buttonMarker[3]    ->hasFocus() )      { buttonSource[3]       ->setFocus(); }
            else if( buttonMarker[4]    ->hasFocus() )      { buttonSource[4]       ->setFocus(); }
            else if( buttonMarker[5]    ->hasFocus() )      { buttonSource[5]       ->setFocus(); }
            else if( buttonMarker[6]    ->hasFocus() )      { buttonSource[6]       ->setFocus(); }
            else if( buttonMarker[7]    ->hasFocus() )      { buttonSource[7]       ->setFocus(); }

            else if( buttonDefault      ->hasFocus() )      { buttonEditMarker      ->setFocus(); }
            else if( buttonEditMarker   ->hasFocus() )      { buttonSave            ->setFocus(); }
            else if( buttonSave         ->hasFocus() )      { buttonClose           ->setFocus(); }
            else if( buttonClose        ->hasFocus() )      { buttonDefault         ->setFocus(); }

            break;
        }
        case Qt::Key_Enter:
        {
            if     ( buttonSourceAll    ->hasFocus() )      { onButtonSourceAll(); }
            else if( buttonSource[0]    ->hasFocus() )      { onButtonSource1(); }
            else if( buttonSource[1]    ->hasFocus() )      { onButtonSource2(); }
            else if( buttonSource[2]    ->hasFocus() )      { onButtonSource3(); }
            else if( buttonSource[3]    ->hasFocus() )      { onButtonSource4(); }
            else if( buttonSource[4]    ->hasFocus() )      { onButtonSource5(); }
            else if( buttonSource[5]    ->hasFocus() )      { onButtonSource6(); }
            else if( buttonSource[6]    ->hasFocus() )      { onButtonSource7(); }
            else if( buttonSource[7]    ->hasFocus() )      { onButtonSource8(); }

            else if( buttonDelayAll     ->hasFocus() )      { onButtonDelayAll(); }
            else if( buttonDelay[0]     ->hasFocus() )      { onButtonDelay1(); }
            else if( buttonDelay[1]     ->hasFocus() )      { onButtonDelay2(); }
            else if( buttonDelay[2]     ->hasFocus() )      { onButtonDelay3(); }
            else if( buttonDelay[3]     ->hasFocus() )      { onButtonDelay4(); }
            else if( buttonDelay[4]     ->hasFocus() )      { onButtonDelay5(); }
            else if( buttonDelay[5]     ->hasFocus() )      { onButtonDelay6(); }
            else if( buttonDelay[6]     ->hasFocus() )      { onButtonDelay7(); }
            else if( buttonDelay[7]     ->hasFocus() )      { onButtonDelay8(); }

            else if( buttonPriorityAll  ->hasFocus() )      { onButtonPriorityAll(); }
            else if( buttonPriority[0]  ->hasFocus() )      { onButtonPriority1(); }
            else if( buttonPriority[1]  ->hasFocus() )      { onButtonPriority2(); }
            else if( buttonPriority[2]  ->hasFocus() )      { onButtonPriority3(); }
            else if( buttonPriority[3]  ->hasFocus() )      { onButtonPriority4(); }
            else if( buttonPriority[4]  ->hasFocus() )      { onButtonPriority5(); }
            else if( buttonPriority[5]  ->hasFocus() )      { onButtonPriority6(); }
            else if( buttonPriority[6]  ->hasFocus() )      { onButtonPriority7(); }
            else if( buttonPriority[7]  ->hasFocus() )      { onButtonPriority8(); }

            else if( buttonAudioAll     ->hasFocus() )      { onButtonAudioAll(); }
            else if( buttonAudio[0]     ->hasFocus() )      { onButtonAudio1(); }
            else if( buttonAudio[1]     ->hasFocus() )      { onButtonAudio2(); }
            else if( buttonAudio[2]     ->hasFocus() )      { onButtonAudio3(); }
            else if( buttonAudio[3]     ->hasFocus() )      { onButtonAudio4(); }
            else if( buttonAudio[4]     ->hasFocus() )      { onButtonAudio5(); }
            else if( buttonAudio[5]     ->hasFocus() )      { onButtonAudio6(); }
            else if( buttonAudio[6]     ->hasFocus() )      { onButtonAudio7(); }
            else if( buttonAudio[7]     ->hasFocus() )      { onButtonAudio8(); }

            else if( buttonMarkerAll    ->hasFocus() )      { onButtonMarkerAll(); }
            else if( buttonMarker[0]    ->hasFocus() )      { onButtonMarker1(); }
            else if( buttonMarker[1]    ->hasFocus() )      { onButtonMarker2(); }
            else if( buttonMarker[2]    ->hasFocus() )      { onButtonMarker3(); }
            else if( buttonMarker[3]    ->hasFocus() )      { onButtonMarker4(); }
            else if( buttonMarker[4]    ->hasFocus() )      { onButtonMarker5(); }
            else if( buttonMarker[5]    ->hasFocus() )      { onButtonMarker6(); }
            else if( buttonMarker[6]    ->hasFocus() )      { onButtonMarker7(); }
            else if( buttonMarker[7]    ->hasFocus() )      { onButtonMarker8(); }

            else if( buttonDefault      ->hasFocus() )      { onButtonDefault(); }
            else if( buttonEditMarker   ->hasFocus() )      { onButtonEditMarker(); }
            else if( buttonSave         ->hasFocus() )      { onButtonSave(); }
            else if( buttonClose        ->hasFocus() )      { reject(); }
            break;
        }
        case Qt::Key_Escape:
        {
            reject();
            break;
        }
    }
}
#endif
