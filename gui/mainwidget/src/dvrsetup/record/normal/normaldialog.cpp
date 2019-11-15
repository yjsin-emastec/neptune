#include <QtGui>
#include "normaldialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

#if defined(HI3521)
NormalDialog::NormalDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::NormalDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        buttonFrame[0] = ui720.buttonFrame1;
        buttonFrame[1] = ui720.buttonFrame2;
        buttonFrame[2] = ui720.buttonFrame3;
        buttonFrame[3] = ui720.buttonFrame4;
        buttonFrame[4] = ui720.buttonFrameAll;

        buttonQuality[0] = ui720.buttonQuality1;
        buttonQuality[1] = ui720.buttonQuality2;
        buttonQuality[2] = ui720.buttonQuality3;
        buttonQuality[3] = ui720.buttonQuality4;
        buttonQuality[4] = ui720.buttonQualityAll;

        buttonRecording[0] = ui720.buttonRecording1;
        buttonRecording[1] = ui720.buttonRecording2;
        buttonRecording[2] = ui720.buttonRecording3;
        buttonRecording[3] = ui720.buttonRecording4;
        buttonRecording[4] = ui720.buttonRecordingAll;

        buttonAudio[0] = ui720.buttonAudio1;
        buttonAudio[1] = ui720.buttonAudio2;
        buttonAudio[2] = ui720.buttonAudio3;
        buttonAudio[3] = ui720.buttonAudio4;
        buttonAudio[4] = ui720.buttonAudioAll;

        buttonDefault = ui720.buttonDefault;
        buttonReload  = ui720.buttonReload;
        buttonSave    = ui720.buttonSave;
        buttonClose   = ui720.buttonClose;

        labelFrame[0] = ui720.labelFrame1;
        labelFrame[1] = ui720.labelFrame2;
        labelFrame[2] = ui720.labelFrame3;
        labelFrame[3] = ui720.labelFrame4;
        labelFrame[4] = ui720.labelFrame;

        labelQuality[0] = ui720.labelQuality1;
        labelQuality[1] = ui720.labelQuality2;
        labelQuality[2] = ui720.labelQuality3;
        labelQuality[3] = ui720.labelQuality4;
        labelQuality[4] = ui720.labelQuality;

        labelRecording[0] = ui720.labelRecording1;
        labelRecording[1] = ui720.labelRecording2;
        labelRecording[2] = ui720.labelRecording3;
        labelRecording[3] = ui720.labelRecording4;
        labelRecording[4] = ui720.labelRecording;

        labelAudio[0] = ui720.labelAudio1;
        labelAudio[1] = ui720.labelAudio2;
        labelAudio[2] = ui720.labelAudio3;
        labelAudio[3] = ui720.labelAudio4;
        labelAudio[4] = ui720.labelAudio;

        labelCh[0] = ui720.labelCh1;
        labelCh[1] = ui720.labelCh2;
        labelCh[2] = ui720.labelCh3;
        labelCh[3] = ui720.labelCh4;
        labelCh[4] = ui720.labelAll;

        for(int ch=0; ch<NUMOFCH; ch++)
        {
            labelFrame[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelQuality[ch]   ->setStyleSheet("background-color:rgb(50,57,83);");
            labelRecording[ch] ->setStyleSheet("background-color:rgb(50,57,83);");
            labelAudio[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelCh[ch]        ->setStyleSheet("font:45px;");
        }

        buttonFrame[NUMOFCH]    ->setStyleSheet("QPushButton{background-color:rgb(06,86,159); font:45px; } QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonQuality[NUMOFCH]  ->setStyleSheet("QPushButton{background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRecording[NUMOFCH]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudio[NUMOFCH]    ->setStyleSheet("QPushButton{background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");

        labelCh[NUMOFCH]        ->setStyleSheet("background-color:rgb(06,86,159); font:45px;");
        labelFrame[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelQuality[NUMOFCH]   ->setStyleSheet("background-color:rgb(06,86,159);");
        labelRecording[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudio[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");

        //yjsin [19/01/02] if text is long, change font size and label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(280, 91);
            buttonReload->setGeometry(15+280+10, 550, 251, 91);
            buttonFrame[NUMOFCH]    ->setStyleSheet("QPushButton{background-color:rgb(06,86,159); font:40px; } QPushButton:focus{background-color:rgb(152,14,69);}");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonDefault->resize(300, 91);
            buttonReload->setGeometry(15+300+10, 550, 241, 91);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonReload->resize(250, 91);
        }
    }
    else
    {
        Ui::NormalDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        buttonFrame[0] = ui1080.buttonFrame1;
        buttonFrame[1] = ui1080.buttonFrame2;
        buttonFrame[2] = ui1080.buttonFrame3;
        buttonFrame[3] = ui1080.buttonFrame4;
        buttonFrame[4] = ui1080.buttonFrameAll;

        buttonQuality[0] = ui1080.buttonQuality1;
        buttonQuality[1] = ui1080.buttonQuality2;
        buttonQuality[2] = ui1080.buttonQuality3;
        buttonQuality[3] = ui1080.buttonQuality4;
        buttonQuality[4] = ui1080.buttonQualityAll;

        buttonRecording[0] = ui1080.buttonRecording1;
        buttonRecording[1] = ui1080.buttonRecording2;
        buttonRecording[2] = ui1080.buttonRecording3;
        buttonRecording[3] = ui1080.buttonRecording4;
        buttonRecording[4] = ui1080.buttonRecordingAll;

        buttonAudio[0] = ui1080.buttonAudio1;
        buttonAudio[1] = ui1080.buttonAudio2;
        buttonAudio[2] = ui1080.buttonAudio3;
        buttonAudio[3] = ui1080.buttonAudio4;
        buttonAudio[4] = ui1080.buttonAudioAll;

        buttonDefault = ui1080.buttonDefault;
        buttonReload  = ui1080.buttonReload;
        buttonSave    = ui1080.buttonSave;
        buttonClose   = ui1080.buttonClose;

        labelFrame[0] = ui1080.labelFrame1;
        labelFrame[1] = ui1080.labelFrame2;
        labelFrame[2] = ui1080.labelFrame3;
        labelFrame[3] = ui1080.labelFrame4;
        labelFrame[4] = ui1080.labelFrame;

        labelQuality[0] = ui1080.labelQuality1;
        labelQuality[1] = ui1080.labelQuality2;
        labelQuality[2] = ui1080.labelQuality3;
        labelQuality[3] = ui1080.labelQuality4;
        labelQuality[4] = ui1080.labelQuality;

        labelRecording[0] = ui1080.labelRecording1;
        labelRecording[1] = ui1080.labelRecording2;
        labelRecording[2] = ui1080.labelRecording3;
        labelRecording[3] = ui1080.labelRecording4;
        labelRecording[4] = ui1080.labelRecording;

        labelAudio[0] = ui1080.labelAudio1;
        labelAudio[1] = ui1080.labelAudio2;
        labelAudio[2] = ui1080.labelAudio3;
        labelAudio[3] = ui1080.labelAudio4;
        labelAudio[4] = ui1080.labelAudio;

        labelCh[0] = ui1080.labelCh1;
        labelCh[1] = ui1080.labelCh2;
        labelCh[2] = ui1080.labelCh3;
        labelCh[3] = ui1080.labelCh4;
        labelCh[4] = ui1080.labelAll;

        for(int ch=0; ch<NUMOFCH; ch++)
        {
            labelFrame[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelQuality[ch]   ->setStyleSheet("background-color:rgb(50,57,83);");
            labelRecording[ch] ->setStyleSheet("background-color:rgb(50,57,83);");
            labelAudio[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelCh[ch]        ->setStyleSheet("font:60px");

            buttonFrame[ch]    ->setStyleSheet("font:60px;");
            buttonQuality[ch]  ->setStyleSheet("font:60px;");
            buttonRecording[ch]->setStyleSheet("font:60px;");
            buttonAudio[ch]    ->setStyleSheet("font:60px;");
        }

        buttonFrame[NUMOFCH]    ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonQuality[NUMOFCH]  ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRecording[NUMOFCH]->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudio[NUMOFCH]    ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");

        labelCh[NUMOFCH]        ->setStyleSheet("font:60px; background-color:rgb(06,86,159);");
        labelFrame[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelQuality[NUMOFCH]   ->setStyleSheet("background-color:rgb(06,86,159);");
        labelRecording[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudio[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");

        //yjsin [19/02/21] if text is long, change label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(400, 131);
            buttonReload->setGeometry(35+400+20, 830, 400, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonDefault->resize(400, 131);
            buttonReload->setGeometry(35+400+20, 830, 400, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonDefault->resize(320, 131);
            buttonReload->setGeometry(35+320+20, 830, 370, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonFrame[NUMOFCH]->setFocus();

    connect(buttonFrame[0],     SIGNAL(released(void)), this, SLOT(onButtonFrame1       (void)));
    connect(buttonFrame[1],     SIGNAL(released(void)), this, SLOT(onButtonFrame2       (void)));
    connect(buttonFrame[2],     SIGNAL(released(void)), this, SLOT(onButtonFrame3       (void)));
    connect(buttonFrame[3],     SIGNAL(released(void)), this, SLOT(onButtonFrame4       (void)));
    connect(buttonFrame[4],     SIGNAL(released(void)), this, SLOT(onButtonFrameAll     (void)));

    connect(buttonQuality[0],   SIGNAL(released(void)), this, SLOT(onButtonQuality1     (void)));
    connect(buttonQuality[1],   SIGNAL(released(void)), this, SLOT(onButtonQuality2     (void)));
    connect(buttonQuality[2],   SIGNAL(released(void)), this, SLOT(onButtonQuality3     (void)));
    connect(buttonQuality[3],   SIGNAL(released(void)), this, SLOT(onButtonQuality4     (void)));
    connect(buttonQuality[4],   SIGNAL(released(void)), this, SLOT(onButtonQualityAll   (void)));

    connect(buttonRecording[0], SIGNAL(released(void)), this, SLOT(onButtonRecording1   (void)));
    connect(buttonRecording[1], SIGNAL(released(void)), this, SLOT(onButtonRecording2   (void)));
    connect(buttonRecording[2], SIGNAL(released(void)), this, SLOT(onButtonRecording3   (void)));
    connect(buttonRecording[3], SIGNAL(released(void)), this, SLOT(onButtonRecording4   (void)));
    connect(buttonRecording[4], SIGNAL(released(void)), this, SLOT(onButtonRecordingAll (void)));

    connect(buttonAudio[0],     SIGNAL(released(void)), this, SLOT(onButtonAudio1       (void)));
    connect(buttonAudio[1],     SIGNAL(released(void)), this, SLOT(onButtonAudio2       (void)));
    connect(buttonAudio[2],     SIGNAL(released(void)), this, SLOT(onButtonAudio3       (void)));
    connect(buttonAudio[3],     SIGNAL(released(void)), this, SLOT(onButtonAudio4       (void)));
    connect(buttonAudio[4],     SIGNAL(released(void)), this, SLOT(onButtonAudioAll     (void)));

    connect(buttonDefault,      SIGNAL(released(void)), this, SLOT(onButtonDefault      (void)));
    connect(buttonReload,       SIGNAL(released(void)), this, SLOT(onButtonReload       (void)));
    connect(buttonSave,         SIGNAL(released(void)), this, SLOT(onButtonSave         (void)));
    connect(buttonClose,        SIGNAL(released(void)), this, SLOT(reject()));

    isFirstClickButtonFrame  =true;
    isFirstClickButtonQuality=true;
}
#elif defined(HI3531D)
NormalDialog::NormalDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::NormalDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        buttonFrame[0] = ui720.buttonFrame1;
        buttonFrame[1] = ui720.buttonFrame2;
        buttonFrame[2] = ui720.buttonFrame3;
        buttonFrame[3] = ui720.buttonFrame4;
        buttonFrame[4] = ui720.buttonFrame5;
        buttonFrame[5] = ui720.buttonFrame6;
        buttonFrame[6] = ui720.buttonFrame7;
        buttonFrame[7] = ui720.buttonFrame8;
        buttonFrame[8] = ui720.buttonFrameAll;

        buttonQuality[0] = ui720.buttonQuality1;
        buttonQuality[1] = ui720.buttonQuality2;
        buttonQuality[2] = ui720.buttonQuality3;
        buttonQuality[3] = ui720.buttonQuality4;
        buttonQuality[4] = ui720.buttonQuality5;
        buttonQuality[5] = ui720.buttonQuality6;
        buttonQuality[6] = ui720.buttonQuality7;
        buttonQuality[7] = ui720.buttonQuality8;
        buttonQuality[8] = ui720.buttonQualityAll;

        buttonRecording[0] = ui720.buttonRecording1;
        buttonRecording[1] = ui720.buttonRecording2;
        buttonRecording[2] = ui720.buttonRecording3;
        buttonRecording[3] = ui720.buttonRecording4;
        buttonRecording[4] = ui720.buttonRecording5;
        buttonRecording[5] = ui720.buttonRecording6;
        buttonRecording[6] = ui720.buttonRecording7;
        buttonRecording[7] = ui720.buttonRecording8;
        buttonRecording[8] = ui720.buttonRecordingAll;

        buttonAudio[0] = ui720.buttonAudio1;
        buttonAudio[1] = ui720.buttonAudio2;
        buttonAudio[2] = ui720.buttonAudio3;
        buttonAudio[3] = ui720.buttonAudio4;
        buttonAudio[4] = ui720.buttonAudio5;
        buttonAudio[5] = ui720.buttonAudio6;
        buttonAudio[6] = ui720.buttonAudio7;
        buttonAudio[7] = ui720.buttonAudio8;
        buttonAudio[8] = ui720.buttonAudioAll;

        buttonDefault = ui720.buttonDefault;
        buttonReload  = ui720.buttonReload;
        buttonSave    = ui720.buttonSave;
        buttonClose   = ui720.buttonClose;

        labelFrame[0] = ui720.labelFrame1;
        labelFrame[1] = ui720.labelFrame2;
        labelFrame[2] = ui720.labelFrame3;
        labelFrame[3] = ui720.labelFrame4;
        labelFrame[4] = ui720.labelFrame5;
        labelFrame[5] = ui720.labelFrame6;
        labelFrame[6] = ui720.labelFrame7;
        labelFrame[7] = ui720.labelFrame8;
        labelFrame[8] = ui720.labelFrame;

        labelQuality[0] = ui720.labelQuality1;
        labelQuality[1] = ui720.labelQuality2;
        labelQuality[2] = ui720.labelQuality3;
        labelQuality[3] = ui720.labelQuality4;
        labelQuality[4] = ui720.labelQuality5;
        labelQuality[5] = ui720.labelQuality6;
        labelQuality[6] = ui720.labelQuality7;
        labelQuality[7] = ui720.labelQuality8;
        labelQuality[8] = ui720.labelQuality;

        labelRecording[0] = ui720.labelRecording1;
        labelRecording[1] = ui720.labelRecording2;
        labelRecording[2] = ui720.labelRecording3;
        labelRecording[3] = ui720.labelRecording4;
        labelRecording[4] = ui720.labelRecording5;
        labelRecording[5] = ui720.labelRecording6;
        labelRecording[6] = ui720.labelRecording7;
        labelRecording[7] = ui720.labelRecording8;
        labelRecording[8] = ui720.labelRecording;

        labelAudio[0] = ui720.labelAudio1;
        labelAudio[1] = ui720.labelAudio2;
        labelAudio[2] = ui720.labelAudio3;
        labelAudio[3] = ui720.labelAudio4;
        labelAudio[4] = ui720.labelAudio5;
        labelAudio[5] = ui720.labelAudio6;
        labelAudio[6] = ui720.labelAudio7;
        labelAudio[7] = ui720.labelAudio8;
        labelAudio[8] = ui720.labelAudio;

        labelCh[0] = ui720.labelCh1;
        labelCh[1] = ui720.labelCh2;
        labelCh[2] = ui720.labelCh3;
        labelCh[3] = ui720.labelCh4;
        labelCh[4] = ui720.labelCh5;
        labelCh[5] = ui720.labelCh6;
        labelCh[6] = ui720.labelCh7;
        labelCh[7] = ui720.labelCh8;
        labelCh[8] = ui720.labelAll;

        for(int ch=0; ch<NUMOFCH; ch++)
        {
            labelFrame[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelQuality[ch]   ->setStyleSheet("background-color:rgb(50,57,83);");
            labelRecording[ch] ->setStyleSheet("background-color:rgb(50,57,83);");
            labelAudio[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelCh[ch]        ->setStyleSheet("font:40px");

            buttonFrame[ch]    ->setStyleSheet("font:40px;");
            buttonQuality[ch]  ->setStyleSheet("font:40px;");
            buttonRecording[ch]->setStyleSheet("font:40px;");
            buttonAudio[ch]    ->setStyleSheet("font:40px;");
        }

        buttonFrame[NUMOFCH]    ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonQuality[NUMOFCH]  ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRecording[NUMOFCH]->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudio[NUMOFCH]    ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");

        labelCh[NUMOFCH]        ->setStyleSheet("font:40px; background-color:rgb(06,86,159);");
        labelFrame[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");
        labelQuality[NUMOFCH]   ->setStyleSheet("background-color:rgb(06,86,159);");
        labelRecording[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");
        labelAudio[NUMOFCH]     ->setStyleSheet("background-color:rgb(06,86,159);");

        //yjsin [19/01/02] if text is long, change font size and label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(280, 91);
            buttonReload->setGeometry(15+280+10, 570, 251, 91);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonDefault->resize(300, 91);
            buttonReload->setGeometry(15+300+10, 570, 241, 91);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonReload->resize(250, 91);
        }
    }
    else
    {
        Ui::NormalDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        buttonFrame[0] = ui1080.buttonFrame1;
        buttonFrame[1] = ui1080.buttonFrame2;
        buttonFrame[2] = ui1080.buttonFrame3;
        buttonFrame[3] = ui1080.buttonFrame4;
        buttonFrame[4] = ui1080.buttonFrame5;
        buttonFrame[5] = ui1080.buttonFrame6;
        buttonFrame[6] = ui1080.buttonFrame7;
        buttonFrame[7] = ui1080.buttonFrame8;
        buttonFrame[8] = ui1080.buttonFrameAll;

        buttonQuality[0] = ui1080.buttonQuality1;
        buttonQuality[1] = ui1080.buttonQuality2;
        buttonQuality[2] = ui1080.buttonQuality3;
        buttonQuality[3] = ui1080.buttonQuality4;
        buttonQuality[4] = ui1080.buttonQuality5;
        buttonQuality[5] = ui1080.buttonQuality6;
        buttonQuality[6] = ui1080.buttonQuality7;
        buttonQuality[7] = ui1080.buttonQuality8;
        buttonQuality[8] = ui1080.buttonQualityAll;

        buttonRecording[0] = ui1080.buttonRecording1;
        buttonRecording[1] = ui1080.buttonRecording2;
        buttonRecording[2] = ui1080.buttonRecording3;
        buttonRecording[3] = ui1080.buttonRecording4;
        buttonRecording[4] = ui1080.buttonRecording5;
        buttonRecording[5] = ui1080.buttonRecording6;
        buttonRecording[6] = ui1080.buttonRecording7;
        buttonRecording[7] = ui1080.buttonRecording8;
        buttonRecording[8] = ui1080.buttonRecordingAll;

        buttonAudio[0] = ui1080.buttonAudio1;
        buttonAudio[1] = ui1080.buttonAudio2;
        buttonAudio[2] = ui1080.buttonAudio3;
        buttonAudio[3] = ui1080.buttonAudio4;
        buttonAudio[4] = ui1080.buttonAudio5;
        buttonAudio[5] = ui1080.buttonAudio6;
        buttonAudio[6] = ui1080.buttonAudio7;
        buttonAudio[7] = ui1080.buttonAudio8;
        buttonAudio[8] = ui1080.buttonAudioAll;

        buttonDefault = ui1080.buttonDefault;
        buttonReload  = ui1080.buttonReload;
        buttonSave    = ui1080.buttonSave;
        buttonClose   = ui1080.buttonClose;

        labelFrame[0] = ui1080.labelFrame1;
        labelFrame[1] = ui1080.labelFrame2;
        labelFrame[2] = ui1080.labelFrame3;
        labelFrame[3] = ui1080.labelFrame4;
        labelFrame[4] = ui1080.labelFrame5;
        labelFrame[5] = ui1080.labelFrame6;
        labelFrame[6] = ui1080.labelFrame7;
        labelFrame[7] = ui1080.labelFrame8;
        labelFrame[8] = ui1080.labelFrame;

        labelQuality[0] = ui1080.labelQuality1;
        labelQuality[1] = ui1080.labelQuality2;
        labelQuality[2] = ui1080.labelQuality3;
        labelQuality[3] = ui1080.labelQuality4;
        labelQuality[4] = ui1080.labelQuality5;
        labelQuality[5] = ui1080.labelQuality6;
        labelQuality[6] = ui1080.labelQuality7;
        labelQuality[7] = ui1080.labelQuality8;
        labelQuality[8] = ui1080.labelQuality;

        labelRecording[0] = ui1080.labelRecording1;
        labelRecording[1] = ui1080.labelRecording2;
        labelRecording[2] = ui1080.labelRecording3;
        labelRecording[3] = ui1080.labelRecording4;
        labelRecording[4] = ui1080.labelRecording5;
        labelRecording[5] = ui1080.labelRecording6;
        labelRecording[6] = ui1080.labelRecording7;
        labelRecording[7] = ui1080.labelRecording8;
        labelRecording[8] = ui1080.labelRecording;

        labelAudio[0] = ui1080.labelAudio1;
        labelAudio[1] = ui1080.labelAudio2;
        labelAudio[2] = ui1080.labelAudio3;
        labelAudio[3] = ui1080.labelAudio4;
        labelAudio[4] = ui1080.labelAudio5;
        labelAudio[5] = ui1080.labelAudio6;
        labelAudio[6] = ui1080.labelAudio7;
        labelAudio[7] = ui1080.labelAudio8;
        labelAudio[8] = ui1080.labelAudio;

        labelCh[0] = ui1080.labelCh1;
        labelCh[1] = ui1080.labelCh2;
        labelCh[2] = ui1080.labelCh3;
        labelCh[3] = ui1080.labelCh4;
        labelCh[4] = ui1080.labelCh5;
        labelCh[5] = ui1080.labelCh6;
        labelCh[6] = ui1080.labelCh7;
        labelCh[7] = ui1080.labelCh8;
        labelCh[8] = ui1080.labelAll;

        for(int ch=0; ch<NUMOFCH; ch++)
        {
            labelFrame[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelQuality[ch]   ->setStyleSheet("background-color:rgb(50,57,83);");
            labelRecording[ch] ->setStyleSheet("background-color:rgb(50,57,83);");
            labelAudio[ch]     ->setStyleSheet("background-color:rgb(50,57,83);");
            labelCh[ch]        ->setStyleSheet("font:60px");

            buttonFrame[ch]    ->setStyleSheet("font:60px;");
            buttonQuality[ch]  ->setStyleSheet("font:60px;");
            buttonRecording[ch]->setStyleSheet("font:60px;");
            buttonAudio[ch]    ->setStyleSheet("font:60px;");
        }

        buttonFrame[NUMOFCH]    ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonQuality[NUMOFCH]  ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRecording[NUMOFCH]->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudio[NUMOFCH]    ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

        labelCh[NUMOFCH]        ->setStyleSheet("font:60px; background-color:rgb(06,86,159);");
        labelFrame[NUMOFCH]     ->setStyleSheet("background-color:rgb(50,57,83);");
        labelQuality[NUMOFCH]   ->setStyleSheet("background-color:rgb(50,57,83);");
        labelRecording[NUMOFCH] ->setStyleSheet("background-color:rgb(50,57,83);");
        labelAudio[NUMOFCH]     ->setStyleSheet("background-color:rgb(50,57,83);");

        //yjsin [19/02/21] if text is long, change label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(400, 131);
            buttonReload->setGeometry(25+400+20, 860, 400, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonDefault->resize(400, 131);
            buttonReload->setGeometry(25+400+20, 860, 400, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonDefault->resize(320, 131);
            buttonReload->setGeometry(25+320+20, 860, 370, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonFrame[NUMOFCH]->setFocus();

    connect(buttonFrame[0],     SIGNAL(released(void)), this, SLOT(onButtonFrame1       (void)));
    connect(buttonFrame[1],     SIGNAL(released(void)), this, SLOT(onButtonFrame2       (void)));
    connect(buttonFrame[2],     SIGNAL(released(void)), this, SLOT(onButtonFrame3       (void)));
    connect(buttonFrame[3],     SIGNAL(released(void)), this, SLOT(onButtonFrame4       (void)));
    connect(buttonFrame[4],     SIGNAL(released(void)), this, SLOT(onButtonFrame5       (void)));
    connect(buttonFrame[5],     SIGNAL(released(void)), this, SLOT(onButtonFrame6       (void)));
    connect(buttonFrame[6],     SIGNAL(released(void)), this, SLOT(onButtonFrame7       (void)));
    connect(buttonFrame[7],     SIGNAL(released(void)), this, SLOT(onButtonFrame8       (void)));
    connect(buttonFrame[8],     SIGNAL(released(void)), this, SLOT(onButtonFrameAll     (void)));

    connect(buttonQuality[0],   SIGNAL(released(void)), this, SLOT(onButtonQuality1     (void)));
    connect(buttonQuality[1],   SIGNAL(released(void)), this, SLOT(onButtonQuality2     (void)));
    connect(buttonQuality[2],   SIGNAL(released(void)), this, SLOT(onButtonQuality3     (void)));
    connect(buttonQuality[3],   SIGNAL(released(void)), this, SLOT(onButtonQuality4     (void)));
    connect(buttonQuality[4],   SIGNAL(released(void)), this, SLOT(onButtonQuality5     (void)));
    connect(buttonQuality[5],   SIGNAL(released(void)), this, SLOT(onButtonQuality6     (void)));
    connect(buttonQuality[6],   SIGNAL(released(void)), this, SLOT(onButtonQuality7     (void)));
    connect(buttonQuality[7],   SIGNAL(released(void)), this, SLOT(onButtonQuality8     (void)));
    connect(buttonQuality[8],   SIGNAL(released(void)), this, SLOT(onButtonQualityAll   (void)));

    connect(buttonRecording[0], SIGNAL(released(void)), this, SLOT(onButtonRecording1   (void)));
    connect(buttonRecording[1], SIGNAL(released(void)), this, SLOT(onButtonRecording2   (void)));
    connect(buttonRecording[2], SIGNAL(released(void)), this, SLOT(onButtonRecording3   (void)));
    connect(buttonRecording[3], SIGNAL(released(void)), this, SLOT(onButtonRecording4   (void)));
    connect(buttonRecording[4], SIGNAL(released(void)), this, SLOT(onButtonRecording5   (void)));
    connect(buttonRecording[5], SIGNAL(released(void)), this, SLOT(onButtonRecording6   (void)));
    connect(buttonRecording[6], SIGNAL(released(void)), this, SLOT(onButtonRecording7   (void)));
    connect(buttonRecording[7], SIGNAL(released(void)), this, SLOT(onButtonRecording8   (void)));
    connect(buttonRecording[8], SIGNAL(released(void)), this, SLOT(onButtonRecordingAll (void)));

    connect(buttonAudio[0],     SIGNAL(released(void)), this, SLOT(onButtonAudio1       (void)));
    connect(buttonAudio[1],     SIGNAL(released(void)), this, SLOT(onButtonAudio2       (void)));
    connect(buttonAudio[2],     SIGNAL(released(void)), this, SLOT(onButtonAudio3       (void)));
    connect(buttonAudio[3],     SIGNAL(released(void)), this, SLOT(onButtonAudio4       (void)));
    connect(buttonAudio[4],     SIGNAL(released(void)), this, SLOT(onButtonAudio5       (void)));
    connect(buttonAudio[5],     SIGNAL(released(void)), this, SLOT(onButtonAudio6       (void)));
    connect(buttonAudio[6],     SIGNAL(released(void)), this, SLOT(onButtonAudio7       (void)));
    connect(buttonAudio[7],     SIGNAL(released(void)), this, SLOT(onButtonAudio8       (void)));
    connect(buttonAudio[8],     SIGNAL(released(void)), this, SLOT(onButtonAudioAll     (void)));

    connect(buttonDefault,      SIGNAL(released(void)), this, SLOT(onButtonDefault      (void)));
    connect(buttonReload,       SIGNAL(released(void)), this, SLOT(onButtonReload       (void)));
    connect(buttonSave,         SIGNAL(released(void)), this, SLOT(onButtonSave         (void)));
    connect(buttonClose,        SIGNAL(released(void)), this, SLOT(reject()));

    isFirstClickButtonFrame  =true;
    isFirstClickButtonQuality=true;
}
#endif

NormalDialog::~NormalDialog()
{
}
void NormalDialog::initNormalConfig(void)
{
    for(int ch=0; ch<NUMOFCH; ch++)
    {
        switch(cfgSetup.rec.record_main.fr_hd[ch])
        {
            case  5 : { buttonFrame[ch]->setText( " 5 Fps");    infoFrame[ch] =  5; }    break;
            case 10 : { buttonFrame[ch]->setText( "10 Fps");    infoFrame[ch] = 10; }    break;
            case 15 : { buttonFrame[ch]->setText( "15 Fps");    infoFrame[ch] = 15; }    break;
            case 20 : { buttonFrame[ch]->setText( "20 Fps");    infoFrame[ch] = 20; }    break;
            case 25 : { buttonFrame[ch]->setText( "25 Fps");    infoFrame[ch] = 25; }    break;
            case 30 : { buttonFrame[ch]->setText( "30 Fps");    infoFrame[ch] = 30; }    break;
            default : { buttonFrame[ch]->setText( "30 Fps");    infoFrame[ch] = 30; }    break;
        }
        switch(cfgSetup.rec.record_main.quality[ch])
        {
            case QUALITY_ECONOMY : { buttonQuality[ch]->setText(tr("Low"   ));  infoQuality[ch] = QUALITY_ECONOMY; }  break;
            case QUALITY_HIGH    : { buttonQuality[ch]->setText(tr("Middle"));  infoQuality[ch] = QUALITY_HIGH;    }  break;
            case QUALITY_ULTRA   : { buttonQuality[ch]->setText(tr("High"  ));  infoQuality[ch] = QUALITY_ULTRA;   }  break;
            default              : { buttonQuality[ch]->setText(tr("High"  ));  infoQuality[ch] = QUALITY_ULTRA;   }  break;
        }
        switch(cfgSetup.rec.record_type[ch])
        {
            case false  : { buttonRecording[ch]->setText(tr("Off"));    infoRecording[ch] = false; }    break;
            case true   : { buttonRecording[ch]->setText(tr("On" ));    infoRecording[ch] = true;  }    break;
            default     : { buttonRecording[ch]->setText(tr("On" ));    infoRecording[ch] = true;  }    break;
        }
        switch(cfgSetup.rec.audio[ch])
        {
            case false  : { buttonAudio[ch]->setText(tr("Off"));    infoAudio[ch] = false; }    break;
            case true   : { buttonAudio[ch]->setText(tr("On" ));    infoAudio[ch] = true;  }    break;
            default     : { buttonAudio[ch]->setText(tr("On" ));    infoAudio[ch] = true;  }    break;
        }
    }
}

void NormalDialog::onButtonFrame(int chNum)
{
    int maxFrame = getMaxFrame(chNum);

    if( infoFrame[chNum] < maxFrame )   { infoFrame[chNum] = infoFrame[chNum]+5; }
    else                                { infoFrame[chNum] = 5; }

    updateFrameText(chNum);
    isFirstClickButtonFrame=true;
}
void NormalDialog::onButtonFrame1()     { onButtonFrame(0); }
void NormalDialog::onButtonFrame2()     { onButtonFrame(1); }
void NormalDialog::onButtonFrame3()     { onButtonFrame(2); }
void NormalDialog::onButtonFrame4()     { onButtonFrame(3); }
void NormalDialog::onButtonFrame5()     { onButtonFrame(4); }
void NormalDialog::onButtonFrame6()     { onButtonFrame(5); }
void NormalDialog::onButtonFrame7()     { onButtonFrame(6); }
void NormalDialog::onButtonFrame8()     { onButtonFrame(7); }
void NormalDialog::onButtonFrameAll()
{
    /*
        when maximum frame is different for each camera, change the frame based on maximum frame.
        ex>
            1 ch : 1080p  : 15 -> 30 -> 5 -> 10 -> 15 -> 15 -> 15 -> 15 -> 5
            2 ch : 720p30 : 15 -> 15 -> 5 -> 10 -> 15 -> 20 -> 25 -> 30 -> 5
            3 ch : 720p25 : 15 -> 25 -> 5 -> 10 -> 15 -> 20 -> 25 -> 25 -> 5
            4 ch : NTSC   : 15 -> 39 -> 5 -> 10 -> 15 -> 20 -> 25 -> 30 -> 5
    */

    int maxFrame[NUMOFCH];
    int allChMaxFrame=0, maxCh=0;
    int count=0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        maxFrame[ch] = getMaxFrame(ch);
        if( maxFrame[ch] > allChMaxFrame ) { allChMaxFrame = maxFrame[ch]; maxCh=ch; }

        if( infoFrame[ch] == maxFrame[ch] ) { count++; }
    }

    if(isFirstClickButtonFrame)
    {
        for(int ch=0; ch<NUMOFCH; ch++)
        {
            if( count < NUMOFCH )   { infoFrame[ch] = maxFrame[ch]; }   // if all channels are not max frame -> set max frame
            else                    { infoFrame[ch] = 5; }
        }
        isFirstClickButtonFrame=false;
    }
    else
    {
        for(int ch=0; ch<NUMOFCH; ch++)
        {
            if( ch != maxCh)
            {
                if( infoFrame[maxCh] != allChMaxFrame )
                {
                    if( infoFrame[ch] >= maxFrame[ch] )                 // if not maxCh and reached the max frame -> keep max frame
                    {
                         infoFrame[ch] = maxFrame[ch];
                    }
                    else
                    {
                        infoFrame[ch] = infoFrame[ch] + 5;
                    }
                }
                else
                {
                    infoFrame[ch] = 5;
                }
            }
        }

        if( infoFrame[maxCh] != maxFrame[maxCh] )
        {
            infoFrame[maxCh] = infoFrame[maxCh] + 5;
        }
        else
        {
            infoFrame[maxCh] = 5;
        }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        updateFrameText(ch);
    }
}

#if defined(HI3521)
int NormalDialog::getMaxFrame(int chNum)
{
    int currentMaxFrame;
    int arVIS[NUMOFCH];

    ver_get_vis_list(arVIS);

    if((arVIS[chNum] == ver_vis_hd_1080_25p) || (arVIS[chNum] == ver_vis_hd_1080_30p) || (arVIS[chNum] == ver_vis_hd_1080_50p) ||
       (arVIS[chNum] == ver_vis_hd_1080_60p) || (arVIS[chNum] == ver_vis_hd_1080_i50) || (arVIS[chNum] == ver_vis_hd_1080_i60) )    //FHD
    {
        currentMaxFrame=15;
    }
    else if((arVIS[chNum] == ver_vis_pal)    || (arVIS[chNum] == ver_vis_hd_720_25p)  || (arVIS[chNum] == ver_vis_hd_720_50p))      //PAL
    {
        currentMaxFrame=25;
    }
    else if((arVIS[chNum] == ver_vis_ntsc)   || (arVIS[chNum] == ver_vis_hd_720_30p)  || (arVIS[chNum] == ver_vis_hd_720_60p)  || (arVIS[chNum] == ver_vis_unknown) )  //NTSC
    {
        currentMaxFrame=30;
    }
    else
    {
        qDebug("[ERROR]NormalDialog::getMaxFrame error");
        currentMaxFrame=15;
    }

    return currentMaxFrame;
}

#elif defined(HI3531D)
int NormalDialog::getMaxFrame(int chNum)
{
    int currentMaxFrame;
    int arVIS[NUMOFCH];

    ver_get_vis_list(arVIS);

    if     ((arVIS[chNum] == ver_vis_hd_720_30p)    || (arVIS[chNum] == ver_vis_hd_720_60p)     ||
            (arVIS[chNum] == ver_vis_hd_1080_30p)   || (arVIS[chNum] == ver_vis_hd_1080_60p)    ||
            (arVIS[chNum] == ver_vis_ntsc)          || (arVIS[chNum] == ver_vis_hd_1080_i60)    )   //NTSC
    {
        currentMaxFrame = 30;
    }
    else if((arVIS[chNum] == ver_vis_hd_720_25p)    || (arVIS[chNum] == ver_vis_hd_720_50p)     ||
            (arVIS[chNum] == ver_vis_hd_1080_25p)   || (arVIS[chNum] == ver_vis_hd_1080_50p)    ||
            (arVIS[chNum] == ver_vis_pal)           || (arVIS[chNum] == ver_vis_hd_1080_i50)    )   //PAL
    {
        currentMaxFrame = 25;
    }
    else
    {
        qDebug("[ERROR]NormalDialog::getMaxFrame error");
        currentMaxFrame = 30;
    }

    return currentMaxFrame;
}
#endif

void NormalDialog::updateFrameText(int chNum)
{
    switch( infoFrame[chNum] )
    {
        case  5 : { buttonFrame[chNum]->setText( " 5 Fps"); } break;
        case 10 : { buttonFrame[chNum]->setText( "10 Fps"); } break;
        case 15 : { buttonFrame[chNum]->setText( "15 Fps"); } break;
        case 20 : { buttonFrame[chNum]->setText( "20 Fps"); } break;
        case 25 : { buttonFrame[chNum]->setText( "25 Fps"); } break;
        case 30 : { buttonFrame[chNum]->setText( "30 Fps"); } break;
        default : { buttonFrame[chNum]->setText( "30 Fps"); } break;
    }
}

void NormalDialog::onButtonQuality(int chNum)
{
    switch( infoQuality[chNum] )
    {
        case QUALITY_ECONOMY : { infoQuality[chNum] = QUALITY_HIGH;     }   break;
        case QUALITY_HIGH    : { infoQuality[chNum] = QUALITY_ULTRA;    }   break;
        case QUALITY_ULTRA   : { infoQuality[chNum] = QUALITY_ECONOMY;  }   break;
        default              : { infoQuality[chNum] = QUALITY_ULTRA;    }   break;
    }
    updateQualityText(chNum);
    isFirstClickButtonQuality=true;
}
void NormalDialog::onButtonQuality1()   { onButtonQuality(0); }
void NormalDialog::onButtonQuality2()   { onButtonQuality(1); }
void NormalDialog::onButtonQuality3()   { onButtonQuality(2); }
void NormalDialog::onButtonQuality4()   { onButtonQuality(3); }
void NormalDialog::onButtonQuality5()   { onButtonQuality(4); }
void NormalDialog::onButtonQuality6()   { onButtonQuality(5); }
void NormalDialog::onButtonQuality7()   { onButtonQuality(6); }
void NormalDialog::onButtonQuality8()   { onButtonQuality(7); }
void NormalDialog::onButtonQualityAll()
{
    int allChMaxQuality=QUALITY_ECONOMY, maxCh=0;
    int count=0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoQuality[ch] > allChMaxQuality ) { allChMaxQuality = infoQuality[ch]; maxCh=ch; }

        if( infoQuality[0] == infoQuality[ch] ) { count++; }
    }

    if( isFirstClickButtonQuality )
    {
        for(int ch=0; ch<NUMOFCH; ch++)
        {
            if( (count >= NUMOFCH) && infoQuality[ch] == QUALITY_ULTRA) { infoQuality[ch] = QUALITY_ECONOMY;    }
            else                                                        { infoQuality[ch] = QUALITY_ULTRA;      }
        }
        isFirstClickButtonQuality=false;
    }
    else
    {
        if( count >= NUMOFCH )
        {
            int currentQuality=infoQuality[0];

            for(int ch=0; ch<NUMOFCH; ch++)
            {
                switch( currentQuality )
                {
                    case QUALITY_ECONOMY : { infoQuality[ch] = QUALITY_HIGH;     }   break;
                    case QUALITY_HIGH    : { infoQuality[ch] = QUALITY_ULTRA;    }   break;
                    case QUALITY_ULTRA   : { infoQuality[ch] = QUALITY_ECONOMY;  }   break;
                    default              : { infoQuality[ch] = QUALITY_ULTRA;    }   break;
                }
            }
        }
        else
        {
            for(int ch=0; ch<NUMOFCH; ch++)
            {
                switch( infoQuality[maxCh] )
                {
                    case QUALITY_ECONOMY : { infoQuality[ch] = QUALITY_ECONOMY; }   break;
                    case QUALITY_HIGH    : { infoQuality[ch] = QUALITY_HIGH;    }   break;
                    case QUALITY_ULTRA   : { infoQuality[ch] = QUALITY_ULTRA;   }   break;
                    default              : { infoQuality[ch] = QUALITY_ULTRA;   }   break;
                }
            }
        }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        updateQualityText(ch);
    }
}
void NormalDialog::updateQualityText(int chNum)
{
    switch( infoQuality[chNum] )
    {
        case QUALITY_ECONOMY : { buttonQuality[chNum]->setText(tr("Low"));      }   break;
        case QUALITY_HIGH    : { buttonQuality[chNum]->setText(tr("Middle"));   }   break;
        case QUALITY_ULTRA   : { buttonQuality[chNum]->setText(tr("High"));     }   break;
        default              : { buttonQuality[chNum]->setText(tr("High"));     }   break;
    }
}

void NormalDialog::onButtonRecording(int chNum)
{
    switch( infoRecording[chNum] )
    {
        case true   : { infoRecording[chNum] = false; } break;
        case false  : { infoRecording[chNum] = true;  } break;
        default     : { infoRecording[chNum] = true;  } break;
    }

    updateRecordingText(chNum);
}
void NormalDialog::onButtonRecording1()     { onButtonRecording(0); }
void NormalDialog::onButtonRecording2()     { onButtonRecording(1); }
void NormalDialog::onButtonRecording3()     { onButtonRecording(2); }
void NormalDialog::onButtonRecording4()     { onButtonRecording(3); }
void NormalDialog::onButtonRecording5()     { onButtonRecording(4); }
void NormalDialog::onButtonRecording6()     { onButtonRecording(5); }
void NormalDialog::onButtonRecording7()     { onButtonRecording(6); }
void NormalDialog::onButtonRecording8()     { onButtonRecording(7); }
void NormalDialog::onButtonRecordingAll()
{
    int count = 0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoRecording[ch] == true ) { count++; }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( count >= NUMOFCH )  { infoRecording[ch] = false; }
        else                    { infoRecording[ch] = true;  }
        updateRecordingText(ch);
    }
}
void NormalDialog::updateRecordingText(int chNum)
{
    switch( infoRecording[chNum] )
    {
        case false : { buttonRecording[chNum]->setText(tr("Off")); } break;
        case true  : { buttonRecording[chNum]->setText(tr("On"));  } break;
        default    : { buttonRecording[chNum]->setText(tr("On"));  } break;
    }
}

void NormalDialog::onButtonAudio(int chNum)
{
    switch( infoAudio[chNum] )
    {
        case true   : { infoAudio[chNum] = false; } break;
        case false  : { infoAudio[chNum] = true;  } break;
        default     : { infoAudio[chNum] = true;  } break;
    }

    updateAudioText(chNum);
}
void NormalDialog::onButtonAudio1()     { onButtonAudio(0); }
void NormalDialog::onButtonAudio2()     { onButtonAudio(1); }
void NormalDialog::onButtonAudio3()     { onButtonAudio(2); }
void NormalDialog::onButtonAudio4()     { onButtonAudio(3); }
void NormalDialog::onButtonAudio5()     { onButtonAudio(4); }
void NormalDialog::onButtonAudio6()     { onButtonAudio(5); }
void NormalDialog::onButtonAudio7()     { onButtonAudio(6); }
void NormalDialog::onButtonAudio8()     { onButtonAudio(7); }
void NormalDialog::onButtonAudioAll()
{
    int count = 0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoAudio[ch] == true ) { count++; }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( count >= NUMOFCH )  { infoAudio[ch] = false; }
        else                    { infoAudio[ch] = true;  }
        updateAudioText(ch);
    }
}
void NormalDialog::updateAudioText(int chNum)
{
    switch( infoAudio[chNum] )
    {
        case false : { buttonAudio[chNum]->setText(tr("Off")); } break;
        case true  : { buttonAudio[chNum]->setText(tr("On"));  } break;
        default    : { buttonAudio[chNum]->setText(tr("On"));  } break;
    }
}

void NormalDialog::onButtonDefault()
{
    for(int ch=0; ch<NUMOFCH; ch++)
    {
        infoFrame[ch]=getMaxFrame(ch);
        infoQuality[ch]=QUALITY_ULTRA;
        infoRecording[ch]=true;
        infoAudio[ch]=true;

        updateFrameText(ch);
        updateQualityText(ch);
        updateRecordingText(ch);
        updateAudioText(ch);
    }
}
void NormalDialog::onButtonReload()
{
    initNormalConfig();
}
void NormalDialog::onButtonSave()
{
    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoFrame[ch] > getMaxFrame(ch) ) { infoFrame[ch] = getMaxFrame(ch); }

        switch( infoFrame[ch] )
        {
            case  5 : { cfgSetup.rec.record_main.fr_hd[ch] =  5; break; }
            case 10 : { cfgSetup.rec.record_main.fr_hd[ch] = 10; break; }
            case 15 : { cfgSetup.rec.record_main.fr_hd[ch] = 15; break; }
            case 20 : { cfgSetup.rec.record_main.fr_hd[ch] = 20; break; }
            case 25 : { cfgSetup.rec.record_main.fr_hd[ch] = 25; break; }
            case 30 : { cfgSetup.rec.record_main.fr_hd[ch] = 30; break; }
            default : { cfgSetup.rec.record_main.fr_hd[ch] = 30; break; }
        }
        switch ( infoQuality[ch] )
        {
            case QUALITY_ECONOMY : { cfgSetup.rec.record_main.quality[ch] = QUALITY_ECONOMY; break; }
            case QUALITY_HIGH    : { cfgSetup.rec.record_main.quality[ch] = QUALITY_HIGH;    break; }
            case QUALITY_ULTRA   : { cfgSetup.rec.record_main.quality[ch] = QUALITY_ULTRA;   break; }
            default              : { cfgSetup.rec.record_main.quality[ch] = QUALITY_ULTRA;   break; }
        }
        switch ( infoRecording[ch] )
        {
            case true  : { cfgSetup.rec.record_type[ch] = true;  break; }
            case false : { cfgSetup.rec.record_type[ch] = false; break; }
            default    : { cfgSetup.rec.record_type[ch] = true;  break; }
        }
        switch ( infoAudio[ch] )
        {
            case true  : { cfgSetup.rec.audio[ch] = true;  break; }
            case false : { cfgSetup.rec.audio[ch] = false; break; }
            default    : { cfgSetup.rec.audio[ch] = true;  break; }
        }
    }

    QDialog::accept();
}

#if defined(HI3521)
void NormalDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up :
        {
            if     ( buttonFrame[4]     ->hasFocus() )  { buttonDefault     ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }

            else if( buttonQuality[4]   ->hasFocus() )  { buttonReload      ->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }

            else if( buttonRecording[4] ->hasFocus() )  { buttonSave        ->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonRecording[3]->setFocus(); }

            else if( buttonAudio[4]     ->hasFocus() )  { buttonClose       ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }

            break;
        }
        case Qt::Key_Down :
        {
            if     ( buttonFrame[4]     ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonDefault     ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }

            else if( buttonQuality[4]   ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonReload      ->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }

            else if( buttonRecording[4] ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonSave        ->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonRecording[4]->setFocus(); }

            else if( buttonAudio[4]     ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonClose       ->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }

            break;
        }
        case Qt::Key_Left :
        {
            if     ( buttonFrame[4]     ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonClose       ->setFocus(); }

            else if( buttonQuality[4]   ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonDefault     ->setFocus(); }

            else if( buttonRecording[4] ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonReload      ->setFocus(); }

            else if( buttonAudio[4]     ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonSave        ->setFocus(); }

            break;
        }
        case Qt::Key_Right :
        {
            if     ( buttonFrame[4]     ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonReload      ->setFocus(); }

            else if( buttonQuality[4]   ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonSave        ->setFocus(); }

            else if( buttonRecording[4] ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonClose       ->setFocus(); }

            else if( buttonAudio[4]     ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonDefault     ->setFocus(); }

            break;
        }
        case Qt::Key_Enter :
        {
            if     ( buttonFrame[4]     ->hasFocus() )  { onButtonFrameAll(); }
            else if( buttonFrame[0]     ->hasFocus() )  { onButtonFrame1();   }
            else if( buttonFrame[1]     ->hasFocus() )  { onButtonFrame2();   }
            else if( buttonFrame[2]     ->hasFocus() )  { onButtonFrame3();   }
            else if( buttonFrame[3]     ->hasFocus() )  { onButtonFrame4();   }
            else if( buttonDefault      ->hasFocus() )  { onButtonDefault();  }

            else if( buttonQuality[4]   ->hasFocus() )  { onButtonQualityAll(); }
            else if( buttonQuality[0]   ->hasFocus() )  { onButtonQuality1();   }
            else if( buttonQuality[1]   ->hasFocus() )  { onButtonQuality2();   }
            else if( buttonQuality[2]   ->hasFocus() )  { onButtonQuality3();   }
            else if( buttonQuality[3]   ->hasFocus() )  { onButtonQuality4();   }
            else if( buttonReload       ->hasFocus() )  { onButtonReload();     }

            else if( buttonRecording[4] ->hasFocus() )  { onButtonRecordingAll(); }
            else if( buttonRecording[0] ->hasFocus() )  { onButtonRecording1();   }
            else if( buttonRecording[1] ->hasFocus() )  { onButtonRecording2();   }
            else if( buttonRecording[2] ->hasFocus() )  { onButtonRecording3();   }
            else if( buttonRecording[3] ->hasFocus() )  { onButtonRecording4();   }
            else if( buttonSave         ->hasFocus() )  { onButtonSave();         }

            else if( buttonAudio[4]     ->hasFocus() )  { onButtonAudioAll(); }
            else if( buttonAudio[0]     ->hasFocus() )  { onButtonAudio1();   }
            else if( buttonAudio[1]     ->hasFocus() )  { onButtonAudio2();   }
            else if( buttonAudio[2]     ->hasFocus() )  { onButtonAudio3();   }
            else if( buttonAudio[3]     ->hasFocus() )  { onButtonAudio4();   }
            else if( buttonClose        ->hasFocus() )  { reject();           }

            break;
        }
        case Qt::Key_Escape :
        {
            reject();

            break;
        }
        default :
        {
            return;
        }
    }
}

#elif defined(HI3531D)
void NormalDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up :
        {
            if     ( buttonFrame[8]     ->hasFocus() )  { buttonDefault     ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonFrame[8]    ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonFrame[4]     ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonFrame[5]     ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonFrame[6]     ->hasFocus() )  { buttonFrame[5]    ->setFocus(); }
            else if( buttonFrame[7]     ->hasFocus() )  { buttonFrame[6]    ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonFrame[7]    ->setFocus(); }

            else if( buttonQuality[8]   ->hasFocus() )  { buttonReload      ->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonQuality[8]  ->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonQuality[4]   ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonQuality[5]   ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonQuality[6]   ->hasFocus() )  { buttonQuality[5]  ->setFocus(); }
            else if( buttonQuality[7]   ->hasFocus() )  { buttonQuality[6]  ->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonQuality[7]  ->setFocus(); }

            else if( buttonRecording[8] ->hasFocus() )  { buttonSave        ->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonRecording[8]->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonRecording[4] ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonRecording[5] ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonRecording[6] ->hasFocus() )  { buttonRecording[5]->setFocus(); }
            else if( buttonRecording[7] ->hasFocus() )  { buttonRecording[6]->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonRecording[7]->setFocus(); }

            else if( buttonAudio[8]     ->hasFocus() )  { buttonClose       ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonAudio[8]    ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )  { buttonAudio[5]    ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )  { buttonAudio[6]    ->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonAudio[7]    ->setFocus(); }

            break;
        }
        case Qt::Key_Down :
        {
            if     ( buttonFrame[8]     ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonFrame[4]     ->hasFocus() )  { buttonFrame[5]    ->setFocus(); }
            else if( buttonFrame[5]     ->hasFocus() )  { buttonFrame[6]    ->setFocus(); }
            else if( buttonFrame[6]     ->hasFocus() )  { buttonFrame[7]    ->setFocus(); }
            else if( buttonFrame[7]     ->hasFocus() )  { buttonDefault     ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonFrame[8]    ->setFocus(); }

            else if( buttonQuality[8]   ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonQuality[4]   ->hasFocus() )  { buttonQuality[5]  ->setFocus(); }
            else if( buttonQuality[5]   ->hasFocus() )  { buttonQuality[6]  ->setFocus(); }
            else if( buttonQuality[6]   ->hasFocus() )  { buttonQuality[7]  ->setFocus(); }
            else if( buttonQuality[7]   ->hasFocus() )  { buttonReload      ->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonQuality[8]  ->setFocus(); }

            else if( buttonRecording[8] ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonRecording[4] ->hasFocus() )  { buttonRecording[5]->setFocus(); }
            else if( buttonRecording[5] ->hasFocus() )  { buttonRecording[6]->setFocus(); }
            else if( buttonRecording[6] ->hasFocus() )  { buttonRecording[7]->setFocus(); }
            else if( buttonRecording[7] ->hasFocus() )  { buttonSave        ->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonRecording[8]->setFocus(); }

            else if( buttonAudio[8]     ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )  { buttonAudio[5]    ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )  { buttonAudio[6]    ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )  { buttonAudio[7]    ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )  { buttonClose       ->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonAudio[8]    ->setFocus(); }

            break;
        }
        case Qt::Key_Left :
        {
            if     ( buttonFrame[8]     ->hasFocus() )  { buttonAudio[8]    ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonFrame[4]     ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonFrame[5]     ->hasFocus() )  { buttonAudio[5]    ->setFocus(); }
            else if( buttonFrame[6]     ->hasFocus() )  { buttonAudio[6]    ->setFocus(); }
            else if( buttonFrame[7]     ->hasFocus() )  { buttonAudio[7]    ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonClose       ->setFocus(); }

            else if( buttonQuality[8]   ->hasFocus() )  { buttonFrame[8]    ->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonQuality[4]   ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonQuality[5]   ->hasFocus() )  { buttonFrame[5]    ->setFocus(); }
            else if( buttonQuality[6]   ->hasFocus() )  { buttonFrame[6]    ->setFocus(); }
            else if( buttonQuality[7]   ->hasFocus() )  { buttonFrame[7]    ->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonDefault     ->setFocus(); }

            else if( buttonRecording[8] ->hasFocus() )  { buttonQuality[8]  ->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonRecording[4] ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonRecording[5] ->hasFocus() )  { buttonQuality[5]  ->setFocus(); }
            else if( buttonRecording[6] ->hasFocus() )  { buttonQuality[6]  ->setFocus(); }
            else if( buttonRecording[7] ->hasFocus() )  { buttonQuality[7]  ->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonReload      ->setFocus(); }

            else if( buttonAudio[8]     ->hasFocus() )  { buttonRecording[8]->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )  { buttonRecording[5]->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )  { buttonRecording[6]->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )  { buttonRecording[7]->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonSave        ->setFocus(); }

            break;
        }
        case Qt::Key_Right :
        {
            if     ( buttonFrame[8]     ->hasFocus() )  { buttonQuality[8]  ->setFocus(); }
            else if( buttonFrame[0]     ->hasFocus() )  { buttonQuality[0]  ->setFocus(); }
            else if( buttonFrame[1]     ->hasFocus() )  { buttonQuality[1]  ->setFocus(); }
            else if( buttonFrame[2]     ->hasFocus() )  { buttonQuality[2]  ->setFocus(); }
            else if( buttonFrame[3]     ->hasFocus() )  { buttonQuality[3]  ->setFocus(); }
            else if( buttonFrame[4]     ->hasFocus() )  { buttonQuality[4]  ->setFocus(); }
            else if( buttonFrame[5]     ->hasFocus() )  { buttonQuality[5]  ->setFocus(); }
            else if( buttonFrame[6]     ->hasFocus() )  { buttonQuality[6]  ->setFocus(); }
            else if( buttonFrame[7]     ->hasFocus() )  { buttonQuality[7]  ->setFocus(); }
            else if( buttonDefault      ->hasFocus() )  { buttonReload      ->setFocus(); }

            else if( buttonQuality[8]   ->hasFocus() )  { buttonRecording[8]->setFocus(); }
            else if( buttonQuality[0]   ->hasFocus() )  { buttonRecording[0]->setFocus(); }
            else if( buttonQuality[1]   ->hasFocus() )  { buttonRecording[1]->setFocus(); }
            else if( buttonQuality[2]   ->hasFocus() )  { buttonRecording[2]->setFocus(); }
            else if( buttonQuality[3]   ->hasFocus() )  { buttonRecording[3]->setFocus(); }
            else if( buttonQuality[4]   ->hasFocus() )  { buttonRecording[4]->setFocus(); }
            else if( buttonQuality[5]   ->hasFocus() )  { buttonRecording[5]->setFocus(); }
            else if( buttonQuality[6]   ->hasFocus() )  { buttonRecording[6]->setFocus(); }
            else if( buttonQuality[7]   ->hasFocus() )  { buttonRecording[7]->setFocus(); }
            else if( buttonReload       ->hasFocus() )  { buttonSave        ->setFocus(); }

            else if( buttonRecording[8] ->hasFocus() )  { buttonAudio[8]    ->setFocus(); }
            else if( buttonRecording[0] ->hasFocus() )  { buttonAudio[0]    ->setFocus(); }
            else if( buttonRecording[1] ->hasFocus() )  { buttonAudio[1]    ->setFocus(); }
            else if( buttonRecording[2] ->hasFocus() )  { buttonAudio[2]    ->setFocus(); }
            else if( buttonRecording[3] ->hasFocus() )  { buttonAudio[3]    ->setFocus(); }
            else if( buttonRecording[4] ->hasFocus() )  { buttonAudio[4]    ->setFocus(); }
            else if( buttonRecording[5] ->hasFocus() )  { buttonAudio[5]    ->setFocus(); }
            else if( buttonRecording[6] ->hasFocus() )  { buttonAudio[6]    ->setFocus(); }
            else if( buttonRecording[7] ->hasFocus() )  { buttonAudio[7]    ->setFocus(); }
            else if( buttonSave         ->hasFocus() )  { buttonClose       ->setFocus(); }

            else if( buttonAudio[8]     ->hasFocus() )  { buttonFrame[8]    ->setFocus(); }
            else if( buttonAudio[0]     ->hasFocus() )  { buttonFrame[0]    ->setFocus(); }
            else if( buttonAudio[1]     ->hasFocus() )  { buttonFrame[1]    ->setFocus(); }
            else if( buttonAudio[2]     ->hasFocus() )  { buttonFrame[2]    ->setFocus(); }
            else if( buttonAudio[3]     ->hasFocus() )  { buttonFrame[3]    ->setFocus(); }
            else if( buttonAudio[4]     ->hasFocus() )  { buttonFrame[4]    ->setFocus(); }
            else if( buttonAudio[5]     ->hasFocus() )  { buttonFrame[5]    ->setFocus(); }
            else if( buttonAudio[6]     ->hasFocus() )  { buttonFrame[6]    ->setFocus(); }
            else if( buttonAudio[7]     ->hasFocus() )  { buttonFrame[7]    ->setFocus(); }
            else if( buttonClose        ->hasFocus() )  { buttonDefault     ->setFocus(); }

            break;
        }
        case Qt::Key_Enter :
        {
            if     ( buttonFrame[8]     ->hasFocus() )  { onButtonFrameAll(); }
            else if( buttonFrame[0]     ->hasFocus() )  { onButtonFrame1();   }
            else if( buttonFrame[1]     ->hasFocus() )  { onButtonFrame2();   }
            else if( buttonFrame[2]     ->hasFocus() )  { onButtonFrame3();   }
            else if( buttonFrame[3]     ->hasFocus() )  { onButtonFrame4();   }
            else if( buttonFrame[4]     ->hasFocus() )  { onButtonFrame5();   }
            else if( buttonFrame[5]     ->hasFocus() )  { onButtonFrame6();   }
            else if( buttonFrame[6]     ->hasFocus() )  { onButtonFrame7();   }
            else if( buttonFrame[7]     ->hasFocus() )  { onButtonFrame8();   }
            else if( buttonDefault      ->hasFocus() )  { onButtonDefault();  }

            else if( buttonQuality[8]   ->hasFocus() )  { onButtonQualityAll(); }
            else if( buttonQuality[0]   ->hasFocus() )  { onButtonQuality1();   }
            else if( buttonQuality[1]   ->hasFocus() )  { onButtonQuality2();   }
            else if( buttonQuality[2]   ->hasFocus() )  { onButtonQuality3();   }
            else if( buttonQuality[3]   ->hasFocus() )  { onButtonQuality4();   }
            else if( buttonQuality[4]   ->hasFocus() )  { onButtonQuality5();   }
            else if( buttonQuality[5]   ->hasFocus() )  { onButtonQuality6();   }
            else if( buttonQuality[6]   ->hasFocus() )  { onButtonQuality7();   }
            else if( buttonQuality[7]   ->hasFocus() )  { onButtonQuality8();   }
            else if( buttonReload       ->hasFocus() )  { onButtonReload();     }

            else if( buttonRecording[8] ->hasFocus() )  { onButtonRecordingAll(); }
            else if( buttonRecording[0] ->hasFocus() )  { onButtonRecording1();   }
            else if( buttonRecording[1] ->hasFocus() )  { onButtonRecording2();   }
            else if( buttonRecording[2] ->hasFocus() )  { onButtonRecording3();   }
            else if( buttonRecording[3] ->hasFocus() )  { onButtonRecording4();   }
            else if( buttonRecording[4] ->hasFocus() )  { onButtonRecording5();   }
            else if( buttonRecording[5] ->hasFocus() )  { onButtonRecording6();   }
            else if( buttonRecording[6] ->hasFocus() )  { onButtonRecording7();   }
            else if( buttonRecording[7] ->hasFocus() )  { onButtonRecording8();   }
            else if( buttonSave         ->hasFocus() )  { onButtonSave();         }

            else if( buttonAudio[8]     ->hasFocus() )  { onButtonAudioAll(); }
            else if( buttonAudio[0]     ->hasFocus() )  { onButtonAudio1();   }
            else if( buttonAudio[1]     ->hasFocus() )  { onButtonAudio2();   }
            else if( buttonAudio[2]     ->hasFocus() )  { onButtonAudio3();   }
            else if( buttonAudio[3]     ->hasFocus() )  { onButtonAudio4();   }
            else if( buttonAudio[4]     ->hasFocus() )  { onButtonAudio5();   }
            else if( buttonAudio[5]     ->hasFocus() )  { onButtonAudio6();   }
            else if( buttonAudio[6]     ->hasFocus() )  { onButtonAudio7();   }
            else if( buttonAudio[7]     ->hasFocus() )  { onButtonAudio8();   }
            else if( buttonClose        ->hasFocus() )  { reject();           }

            break;
        }
        case Qt::Key_Escape :
        {
            reject();

            break;
        }
        default :
        {
            return;
        }
    }
}
#endif

