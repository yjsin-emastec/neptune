#include <QtGui>
#include "normaldialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

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
        buttonReload = ui720.buttonReload;
        buttonSave = ui720.buttonSave;
        buttonClose = ui720.buttonClose;

        buttonFrame[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonQuality[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRecording[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudio[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

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
        labelAll = ui720.labelAll;
        labelCh[0] = ui720.labelCh1;
        labelCh[1] = ui720.labelCh2;
        labelCh[2] = ui720.labelCh3;
        labelCh[3] = ui720.labelCh4;

        for(int ch=0; ch<NUMOFCH; ch++)
        {
            labelFrame[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelQuality[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelRecording[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelAudio[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelCh[ch]->setStyleSheet("font:48px");
        }

        labelAll->setStyleSheet("font:46px;background-color:rgb(50,57,83);");
        labelFrame[4]->setStyleSheet("background-color:rgb(50,57,83);");
        labelQuality[4]->setStyleSheet("background-color:rgb(50,57,83);");
        labelRecording[4]->setStyleSheet("background-color:rgb(50,57,83);");
        labelAudio[4]->setStyleSheet("background-color:rgb(50,57,83);");

        //yjsin [19/01/02] if text is long, change font size and label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
        {
            buttonDefault->resize(304, 91);
            buttonDefault->setStyleSheet("font:38px");
            buttonReload->setGeometry(335, 550, 231, 91);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(281, 91);
            buttonReload->setGeometry(311, 550, 251, 91);
            buttonFrame[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);font-size: 40px;}QPushButton:focus{background-color:rgb(152,14,69);}");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            labelAll->setStyleSheet("font:40px");
            buttonDefault->resize(301, 91);
            buttonReload->setGeometry(331, 550, 241, 91);
            buttonAudio[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);font-size: 45px;}QPushButton:focus{background-color:rgb(152,14,69);}");
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
        buttonReload = ui1080.buttonReload;
        buttonSave = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;

        buttonFrame[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonQuality[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRecording[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonAudio[4]->setStyleSheet("QPushButton{background-color:rgb(06,86,159);}QPushButton:focus{background-color:rgb(152,14,69);}");

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
        labelAll = ui1080.labelAll;
        labelCh[0] = ui1080.labelCh1;
        labelCh[1] = ui1080.labelCh2;
        labelCh[2] = ui1080.labelCh3;
        labelCh[3] = ui1080.labelCh4;

        for(int ch=0; ch<NUMOFCH; ch++)
        {
            labelFrame[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelQuality[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelRecording[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelAudio[ch]->setStyleSheet("background-color:rgb(50,57,83);");
            labelCh[ch]->setStyleSheet("font:65px");
        }

        labelAll->setStyleSheet("font:65px;background-color:rgb(50,57,83);");
        labelFrame[4]->setStyleSheet("background-color:rgb(50,57,83);");
        labelQuality[4]->setStyleSheet("background-color:rgb(50,57,83);");
        labelRecording[4]->setStyleSheet("background-color:rgb(50,57,83);");
        labelAudio[4]->setStyleSheet("background-color:rgb(50,57,83);");

        //yjsin [19/02/21] if text is long, change label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
        {
            buttonDefault->resize(500, 131);
            buttonReload->setGeometry(560, 830, 300, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonDefault->resize(400, 131);
            buttonReload->setGeometry(460, 830, 400, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            labelAll->setStyleSheet("font:58px");
            buttonDefault->resize(400, 131);
            buttonReload->setGeometry(460, 830, 400, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonDefault->resize(320, 131);
            buttonReload->setGeometry(380, 830, 370, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonFrame[4]->setFocus();

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

    isFirstClickButtnFrame=true;
    isFirstClickButtnQuality=true;
}
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

void NormalDialog::onButtonFrame1()
{
    int maxFrame = getMaxFrame(0);

    if( infoFrame[0] < maxFrame ) { infoFrame[0] = infoFrame[0]+5; }
    else                          { infoFrame[0] = 5; }

    updateFrameText(0);
    isFirstClickButtnFrame=true;
}

void NormalDialog::onButtonFrame2()
{
    int maxFrame = getMaxFrame(1);

    if( infoFrame[1] < maxFrame ) { infoFrame[1] = infoFrame[1]+5; }
    else                          { infoFrame[1] = 5; }

    updateFrameText(1);
    isFirstClickButtnFrame=true;
}

void NormalDialog::onButtonFrame3()
{
    int maxFrame = getMaxFrame(2);

    if( infoFrame[2] < maxFrame ) { infoFrame[2] = infoFrame[2]+5; }
    else                          { infoFrame[2] = 5; }

    updateFrameText(2);
    isFirstClickButtnFrame=true;
}

void NormalDialog::onButtonFrame4()
{
    int maxFrame = getMaxFrame(3);

    if( infoFrame[3] < maxFrame ) { infoFrame[3] = infoFrame[3]+5; }
    else                          { infoFrame[3] = 5; }

    updateFrameText(3);
    isFirstClickButtnFrame=true;
}

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

    if(isFirstClickButtnFrame)
    {
        for(int ch=0; ch<NUMOFCH; ch++)
        {
            if( count < NUMOFCH )   { infoFrame[ch] = maxFrame[ch]; }   // if all channels are not max frame -> set max frame
            else                    { infoFrame[ch] = 5; }
        }
        isFirstClickButtnFrame=false;
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

int NormalDialog::getMaxFrame(int chNum)
{
    int currentMaxFrame;
#if( DEVINFO_VIDEONUM == 8 )
    int arVIS[8];
#else
    int arVIS[devInfo.videoNum];
#endif

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

void NormalDialog::onButtonQuality1()
{
    switch( infoQuality[0] )
    {
        case QUALITY_ECONOMY : { infoQuality[0] = QUALITY_HIGH;     }   break;
        case QUALITY_HIGH    : { infoQuality[0] = QUALITY_ULTRA;    }   break;
        case QUALITY_ULTRA   : { infoQuality[0] = QUALITY_ECONOMY;  }   break;
        default              : { infoQuality[0] = QUALITY_ULTRA;    }   break;
    }
    updateQualityText(0);
    isFirstClickButtnQuality=true;
}

void NormalDialog::onButtonQuality2()
{
    switch( infoQuality[1] )
    {
        case QUALITY_ECONOMY : { infoQuality[1] = QUALITY_HIGH;     }   break;
        case QUALITY_HIGH    : { infoQuality[1] = QUALITY_ULTRA;    }   break;
        case QUALITY_ULTRA   : { infoQuality[1] = QUALITY_ECONOMY;  }   break;
        default              : { infoQuality[1] = QUALITY_ULTRA;    }   break;
    }
    updateQualityText(1);
    isFirstClickButtnQuality=true;
}
void NormalDialog::onButtonQuality3()
{
    switch( infoQuality[2] )
    {
        case QUALITY_ECONOMY : { infoQuality[2] = QUALITY_HIGH;     }   break;
        case QUALITY_HIGH    : { infoQuality[2] = QUALITY_ULTRA;    }   break;
        case QUALITY_ULTRA   : { infoQuality[2] = QUALITY_ECONOMY;  }   break;
        default              : { infoQuality[2] = QUALITY_ULTRA;    }   break;
    }
    updateQualityText(2);
    isFirstClickButtnQuality=true;
}
void NormalDialog::onButtonQuality4()
{
    switch( infoQuality[3] )
    {
        case QUALITY_ECONOMY : { infoQuality[3] = QUALITY_HIGH;     }   break;
        case QUALITY_HIGH    : { infoQuality[3] = QUALITY_ULTRA;    }   break;
        case QUALITY_ULTRA   : { infoQuality[3] = QUALITY_ECONOMY;  }   break;
        default              : { infoQuality[3] = QUALITY_ULTRA;    }   break;
    }
    updateQualityText(3);
    isFirstClickButtnQuality=true;
}
void NormalDialog::onButtonQualityAll()
{
    int allChMaxQuality=QUALITY_ECONOMY, maxCh=0;
    int count=0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoQuality[ch] > allChMaxQuality ) { allChMaxQuality = infoQuality[ch]; maxCh=ch; }

        if( infoQuality[0] == infoQuality[ch] ) { count++; }
    }

    if( isFirstClickButtnQuality )
    {
        for(int ch=0; ch<NUMOFCH; ch++)
        {
            if( (count >= NUMOFCH) && infoQuality[ch] == QUALITY_ULTRA) { infoQuality[ch] = QUALITY_ECONOMY;    }
            else                                                        { infoQuality[ch] = QUALITY_ULTRA;      }
        }
        isFirstClickButtnQuality=false;
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

void NormalDialog::onButtonRecording1()
{
    switch( infoRecording[0] )
    {
        case true   : { infoRecording[0] = false; } break;
        case false  : { infoRecording[0] = true;  } break;
        default     : { infoRecording[0] = true;  } break;
    }

    updateRecordingText(0);
}

void NormalDialog::onButtonRecording2()
{
    switch( infoRecording[1] )
    {
        case true   : { infoRecording[1] = false; } break;
        case false  : { infoRecording[1] = true;  } break;
        default     : { infoRecording[1] = true;  } break;
    }

    updateRecordingText(1);
}
void NormalDialog::onButtonRecording3()
{
    switch( infoRecording[2] )
    {
        case true   : { infoRecording[2] = false; } break;
        case false  : { infoRecording[2] = true;  } break;
        default     : { infoRecording[2] = true;  } break;
    }

    updateRecordingText(2);
}
void NormalDialog::onButtonRecording4()
{
    switch( infoRecording[3] )
    {
        case true   : { infoRecording[3] = false; } break;
        case false  : { infoRecording[3] = true;  } break;
        default     : { infoRecording[3] = true;  } break;
    }

    updateRecordingText(3);
}
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

void NormalDialog::onButtonAudio1()
{
    switch( infoAudio[0] )
    {
        case true   : { infoAudio[0] = false; } break;
        case false  : { infoAudio[0] = true;  } break;
        default     : { infoAudio[0] = true;  } break;
    }

    updateAudioText(0);
}
void NormalDialog::onButtonAudio2()
{
    switch( infoAudio[1] )
    {
        case true   : { infoAudio[1] = false; } break;
        case false  : { infoAudio[1] = true;  } break;
        default     : { infoAudio[1] = true;  } break;
    }

    updateAudioText(1);
}
void NormalDialog::onButtonAudio3()
{
    switch( infoAudio[2] )
    {
        case true   : { infoAudio[2] = false; } break;
        case false  : { infoAudio[2] = true;  } break;
        default     : { infoAudio[2] = true;  } break;
    }

    updateAudioText(2);
}
void NormalDialog::onButtonAudio4()
{
    switch( infoAudio[3] )
    {
        case true   : { infoAudio[3] = false; } break;
        case false  : { infoAudio[3] = true;  } break;
        default     : { infoAudio[3] = true;  } break;
    }

    updateAudioText(3);
}
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

void NormalDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up :
        {
            if     ( buttonFrame[4]->hasFocus() )       { buttonDefault->setFocus();  }
            else if( buttonFrame[0]->hasFocus() )       { buttonFrame[4]->setFocus(); }
            else if( buttonFrame[1]->hasFocus() )       { buttonFrame[0]->setFocus(); }
            else if( buttonFrame[2]->hasFocus() )       { buttonFrame[1]->setFocus(); }
            else if( buttonFrame[3]->hasFocus() )       { buttonFrame[2]->setFocus(); }
            else if( buttonDefault->hasFocus() )        { buttonFrame[3]->setFocus(); }

            else if( buttonQuality[4]->hasFocus() )     { buttonReload->setFocus(); }
            else if( buttonQuality[0]->hasFocus() )     { buttonQuality[4]->setFocus(); }
            else if( buttonQuality[1]->hasFocus() )     { buttonQuality[0]->setFocus(); }
            else if( buttonQuality[2]->hasFocus() )     { buttonQuality[1]->setFocus(); }
            else if( buttonQuality[3]->hasFocus() )     { buttonQuality[2]->setFocus(); }
            else if( buttonReload->hasFocus() )         { buttonQuality[3]->setFocus(); }

            else if( buttonRecording[4]->hasFocus() )   { buttonSave->setFocus(); }
            else if( buttonRecording[0]->hasFocus() )   { buttonRecording[4]->setFocus(); }
            else if( buttonRecording[1]->hasFocus() )   { buttonRecording[0]->setFocus(); }
            else if( buttonRecording[2]->hasFocus() )   { buttonRecording[1]->setFocus(); }
            else if( buttonRecording[3]->hasFocus() )   { buttonRecording[2]->setFocus(); }
            else if( buttonSave->hasFocus() )           { buttonRecording[3]->setFocus(); }

            else if( buttonAudio[4]->hasFocus() )       { buttonClose->setFocus(); }
            else if( buttonAudio[0]->hasFocus() )       { buttonAudio[4]->setFocus(); }
            else if( buttonAudio[1]->hasFocus() )       { buttonAudio[0]->setFocus(); }
            else if( buttonAudio[2]->hasFocus() )       { buttonAudio[1]->setFocus(); }
            else if( buttonAudio[3]->hasFocus() )       { buttonAudio[2]->setFocus(); }
            else if( buttonClose->hasFocus() )          { buttonAudio[3]->setFocus(); }

            break;
        }
        case Qt::Key_Down :
        {
            if     ( buttonFrame[4]->hasFocus() )       { buttonFrame[0]->setFocus(); }
            else if( buttonFrame[0]->hasFocus() )       { buttonFrame[1]->setFocus(); }
            else if( buttonFrame[1]->hasFocus() )       { buttonFrame[2]->setFocus(); }
            else if( buttonFrame[2]->hasFocus() )       { buttonFrame[3]->setFocus(); }
            else if( buttonFrame[3]->hasFocus() )       { buttonDefault->setFocus();  }
            else if( buttonDefault->hasFocus() )        { buttonFrame[4]->setFocus(); }

            else if( buttonQuality[4]->hasFocus() )     { buttonQuality[0]->setFocus(); }
            else if( buttonQuality[0]->hasFocus() )     { buttonQuality[1]->setFocus(); }
            else if( buttonQuality[1]->hasFocus() )     { buttonQuality[2]->setFocus(); }
            else if( buttonQuality[2]->hasFocus() )     { buttonQuality[3]->setFocus(); }
            else if( buttonQuality[3]->hasFocus() )     { buttonReload->setFocus(); }
            else if( buttonReload->hasFocus() )         { buttonQuality[4]->setFocus(); }

            else if( buttonRecording[4]->hasFocus() )   { buttonRecording[0]->setFocus(); }
            else if( buttonRecording[0]->hasFocus() )   { buttonRecording[1]->setFocus(); }
            else if( buttonRecording[1]->hasFocus() )   { buttonRecording[2]->setFocus(); }
            else if( buttonRecording[2]->hasFocus() )   { buttonRecording[3]->setFocus(); }
            else if( buttonRecording[3]->hasFocus() )   { buttonSave->setFocus(); }
            else if( buttonSave->hasFocus() )           { buttonRecording[4]->setFocus(); }

            else if( buttonAudio[4]->hasFocus() )       { buttonAudio[0]->setFocus(); }
            else if( buttonAudio[0]->hasFocus() )       { buttonAudio[1]->setFocus(); }
            else if( buttonAudio[1]->hasFocus() )       { buttonAudio[2]->setFocus(); }
            else if( buttonAudio[2]->hasFocus() )       { buttonAudio[3]->setFocus(); }
            else if( buttonAudio[3]->hasFocus() )       { buttonClose->setFocus(); }
            else if( buttonClose->hasFocus() )          { buttonAudio[4]->setFocus(); }

            break;
        }
        case Qt::Key_Left :
        {
            if     ( buttonFrame[4]->hasFocus() )       { buttonAudio[4]->setFocus(); }
            else if( buttonFrame[0]->hasFocus() )       { buttonAudio[0]->setFocus(); }
            else if( buttonFrame[1]->hasFocus() )       { buttonAudio[1]->setFocus(); }
            else if( buttonFrame[2]->hasFocus() )       { buttonAudio[2]->setFocus(); }
            else if( buttonFrame[3]->hasFocus() )       { buttonAudio[3]->setFocus(); }
            else if( buttonDefault->hasFocus() )        { buttonClose->setFocus();    }

            else if( buttonQuality[4]->hasFocus() )     { buttonFrame[4]->setFocus(); }
            else if( buttonQuality[0]->hasFocus() )     { buttonFrame[0]->setFocus(); }
            else if( buttonQuality[1]->hasFocus() )     { buttonFrame[1]->setFocus(); }
            else if( buttonQuality[2]->hasFocus() )     { buttonFrame[2]->setFocus(); }
            else if( buttonQuality[3]->hasFocus() )     { buttonFrame[3]->setFocus(); }
            else if( buttonReload->hasFocus() )         { buttonDefault->setFocus(); }

            else if( buttonRecording[4]->hasFocus() )   { buttonQuality[4]->setFocus(); }
            else if( buttonRecording[0]->hasFocus() )   { buttonQuality[0]->setFocus(); }
            else if( buttonRecording[1]->hasFocus() )   { buttonQuality[1]->setFocus(); }
            else if( buttonRecording[2]->hasFocus() )   { buttonQuality[2]->setFocus(); }
            else if( buttonRecording[3]->hasFocus() )   { buttonQuality[3]->setFocus(); }
            else if( buttonSave->hasFocus() )           { buttonReload->setFocus(); }

            else if( buttonAudio[4]->hasFocus() )       { buttonRecording[4]->setFocus(); }
            else if( buttonAudio[0]->hasFocus() )       { buttonRecording[0]->setFocus(); }
            else if( buttonAudio[1]->hasFocus() )       { buttonRecording[1]->setFocus(); }
            else if( buttonAudio[2]->hasFocus() )       { buttonRecording[2]->setFocus(); }
            else if( buttonAudio[3]->hasFocus() )       { buttonRecording[3]->setFocus(); }
            else if( buttonClose->hasFocus() )          { buttonSave->setFocus(); }

            break;
        }
        case Qt::Key_Right :
        {
            if     ( buttonFrame[4]->hasFocus() )       { buttonQuality[4]->setFocus(); }
            else if( buttonFrame[0]->hasFocus() )       { buttonQuality[0]->setFocus(); }
            else if( buttonFrame[1]->hasFocus() )       { buttonQuality[1]->setFocus(); }
            else if( buttonFrame[2]->hasFocus() )       { buttonQuality[2]->setFocus(); }
            else if( buttonFrame[3]->hasFocus() )       { buttonQuality[3]->setFocus(); }
            else if( buttonDefault->hasFocus() )        { buttonReload->setFocus();    }

            else if( buttonQuality[4]->hasFocus() )     { buttonRecording[4]->setFocus(); }
            else if( buttonQuality[0]->hasFocus() )     { buttonRecording[0]->setFocus(); }
            else if( buttonQuality[1]->hasFocus() )     { buttonRecording[1]->setFocus(); }
            else if( buttonQuality[2]->hasFocus() )     { buttonRecording[2]->setFocus(); }
            else if( buttonQuality[3]->hasFocus() )     { buttonRecording[3]->setFocus(); }
            else if( buttonReload->hasFocus() )         { buttonSave->setFocus(); }

            else if( buttonRecording[4]->hasFocus() )   { buttonAudio[4]->setFocus(); }
            else if( buttonRecording[0]->hasFocus() )   { buttonAudio[0]->setFocus(); }
            else if( buttonRecording[1]->hasFocus() )   { buttonAudio[1]->setFocus(); }
            else if( buttonRecording[2]->hasFocus() )   { buttonAudio[2]->setFocus(); }
            else if( buttonRecording[3]->hasFocus() )   { buttonAudio[3]->setFocus(); }
            else if( buttonSave->hasFocus() )           { buttonClose->setFocus(); }

            else if( buttonAudio[4]->hasFocus() )       { buttonFrame[4]->setFocus(); }
            else if( buttonAudio[0]->hasFocus() )       { buttonFrame[0]->setFocus(); }
            else if( buttonAudio[1]->hasFocus() )       { buttonFrame[1]->setFocus(); }
            else if( buttonAudio[2]->hasFocus() )       { buttonFrame[2]->setFocus(); }
            else if( buttonAudio[3]->hasFocus() )       { buttonFrame[3]->setFocus(); }
            else if( buttonClose->hasFocus() )          { buttonDefault->setFocus(); }

            break;
        }
        case Qt::Key_Enter :
        {
            if     ( buttonFrame[4]->hasFocus() )       { onButtonFrameAll(); }
            else if( buttonFrame[0]->hasFocus() )       { onButtonFrame1(); }
            else if( buttonFrame[1]->hasFocus() )       { onButtonFrame2(); }
            else if( buttonFrame[2]->hasFocus() )       { onButtonFrame3(); }
            else if( buttonFrame[3]->hasFocus() )       { onButtonFrame4(); }
            else if( buttonDefault->hasFocus() )        { onButtonDefault(); }

            else if( buttonQuality[4]->hasFocus() )     { onButtonQualityAll(); }
            else if( buttonQuality[0]->hasFocus() )     { onButtonQuality1(); }
            else if( buttonQuality[1]->hasFocus() )     { onButtonQuality2(); }
            else if( buttonQuality[2]->hasFocus() )     { onButtonQuality3(); }
            else if( buttonQuality[3]->hasFocus() )     { onButtonQuality4(); }
            else if( buttonReload->hasFocus() )         { onButtonReload(); }

            else if( buttonRecording[4]->hasFocus() )   { onButtonRecordingAll(); }
            else if( buttonRecording[0]->hasFocus() )   { onButtonRecording1(); }
            else if( buttonRecording[1]->hasFocus() )   { onButtonRecording2(); }
            else if( buttonRecording[2]->hasFocus() )   { onButtonRecording3(); }
            else if( buttonRecording[3]->hasFocus() )   { onButtonRecording4(); }
            else if( buttonSave->hasFocus() )           { onButtonSave(); }

            else if( buttonAudio[4]->hasFocus() )       { onButtonAudioAll(); }
            else if( buttonAudio[0]->hasFocus() )       { onButtonAudio1(); }
            else if( buttonAudio[1]->hasFocus() )       { onButtonAudio2(); }
            else if( buttonAudio[2]->hasFocus() )       { onButtonAudio3(); }
            else if( buttonAudio[3]->hasFocus() )       { onButtonAudio4(); }
            else if( buttonClose->hasFocus() )          { reject(); }

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
