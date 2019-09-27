#include "mainwidget.h"
#include "mainglobal.h"

MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::MainMenu ui720;
        ui720.setupUi(this);

        frame                   = ui720.frame;

        buttonSetup             = ui720.buttonSetup;
        buttonSearch            = ui720.buttonSearch;
        buttonNotAvailable      = ui720.buttonNotAvailable;
        buttonAudio             = ui720.buttonAudio;
        buttonShutdown          = ui720.buttonShutdown;
        buttonClose             = ui720.buttonClose;

        labelSetupText          = ui720.labelSetupText;
        labelSearchText         = ui720.labelSearchText;
        labelNotAvailableText   = ui720.labelNotAvailableText;
        labelAudioText          = ui720.labelAudioText;
        labelShutdownText       = ui720.labelShutdownText;
        labelCloseText          = ui720.labelCloseText;

        labelSetupText          ->setStyleSheet("font: 40px;");
        labelSearchText         ->setStyleSheet("font: 40px;");
        labelNotAvailableText   ->setStyleSheet("font: 40px;");
        labelAudioText          ->setStyleSheet("font: 40px;");
        labelShutdownText       ->setStyleSheet("font: 40px;");
        labelCloseText          ->setStyleSheet("font: 40px;");
    }
    else
    {
        Ui::MainMenu1080p ui1080;
        ui1080.setupUi(this);

        frame                   = ui1080.frame;

        buttonSetup             = ui1080.buttonSetup;
        buttonSearch            = ui1080.buttonSearch;
        buttonNotAvailable      = ui1080.buttonNotAvailable;
        buttonAudio             = ui1080.buttonAudio;
        buttonShutdown          = ui1080.buttonShutdown;
        buttonClose             = ui1080.buttonClose;

        labelSetupText          = ui1080.labelSetupText;
        labelSearchText         = ui1080.labelSearchText;
        labelNotAvailableText   = ui1080.labelNotAvailableText;
        labelAudioText          = ui1080.labelAudioText;
        labelShutdownText       = ui1080.labelShutdownText;
        labelCloseText          = ui1080.labelCloseText;

        labelSetupText          ->setStyleSheet("font: 65px;");
        labelSearchText         ->setStyleSheet("font: 65px;");
        labelNotAvailableText   ->setStyleSheet("font: 65px;");
        labelAudioText          ->setStyleSheet("font: 65px;");
        labelShutdownText       ->setStyleSheet("font: 65px;");
        labelCloseText          ->setStyleSheet("font: 65px;");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    iconImageNormal[0].load(":images/main/setup.png");
    iconImageNormal[1].load(":images/main/search.png");
    iconImageNormal[2].load(":images/dvrsetup/display/blank.png");
    iconImageNormal[3].load(":images/main/audiomute.png");
    iconImageNormal[4].load(":images/main/shutdown.png");
    iconImageNormal[5].load(":images/dvrsetup/system/close.png");

    iconImageFocus[0].load(":images/main/setup2.png");
    iconImageFocus[1].load(":images/main/search2.png");
    //iconImageFocus[2].load(":images/dvrsetup/display/blank2.png");
    iconImageFocus[3].load(":images/main/audiomute2.png");
    iconImageFocus[4].load(":images/main/shutdown2.png");
    iconImageFocus[5].load(":images/dvrsetup/system/close2.png");

    buttonSetup         ->setPixmap(iconImageNormal[0]);
    buttonSearch        ->setPixmap(iconImageNormal[1]);
    buttonNotAvailable  ->setPixmap(iconImageNormal[2]);
    buttonAudio         ->setPixmap(iconImageNormal[3]);
    buttonShutdown      ->setPixmap(iconImageNormal[4]);
    buttonClose         ->setPixmap(iconImageNormal[5]);

    buttonSetup         ->setScaledContents(true);
    buttonSearch        ->setScaledContents(true);
    buttonNotAvailable  ->setScaledContents(true);
    buttonAudio         ->setScaledContents(true);
    buttonShutdown      ->setScaledContents(true);
    buttonClose         ->setScaledContents(true);

    connect(buttonSetup,    SIGNAL(pressed()), this, SLOT(onButtonSetup()));
    connect(buttonSearch,   SIGNAL(pressed()), this, SLOT(onButtonSearch()));
    connect(buttonAudio,    SIGNAL(pressed()), this, SLOT(onButtonAudio()));
    connect(buttonShutdown, SIGNAL(pressed()), this, SLOT(onButtonShutdown()));
    connect(buttonClose,    SIGNAL(pressed()), this, SLOT(onButtonClose()));

    connect(buttonSetup,    SIGNAL(focusIn()), this, SLOT(setFocusSetup()));
    connect(buttonSearch,   SIGNAL(focusIn()), this, SLOT(setFocusSearch()));
    connect(buttonAudio,    SIGNAL(focusIn()), this, SLOT(setFocusAudio()));
    connect(buttonShutdown, SIGNAL(focusIn()), this, SLOT(setFocusShutdown()));
    connect(buttonClose,    SIGNAL(focusIn()), this, SLOT(setFocusClose()));

    initMainMenu();
}
MainMenu::~MainMenu()
{
}
void MainMenu::onButtonSetup()
{
    hide();
    emit setupClicked();
}
void MainMenu::onButtonSearch()
{
    hide();
    emit searchClicked();
}
void MainMenu::onButtonAudio()
{
    if(indexAudio > devInfo.videoNum || indexAudio < 0)   { indexAudio = 0; }

    if(currentSplit==Split_1)
    {
        if(indexAudio == AUDIO_LIVE_MUTE-1)
        {
            indexAudio=currentChannelNum+2;
            setAudioOut(indexAudio);
        }
        else
        {
            indexAudio=AUDIO_LIVE_MUTE-1;
            setAudioOut(indexAudio);
        }
    }
    else if(currentSplit==Split_4)
    {
        if(splitStartChNum == 0)                        //ch1234
        {
            if(indexAudio <= LIVE_AUDIO_SINGLE_4)       //audio1234
            {
                if( indexAudio == LIVE_AUDIO_SINGLE_4 ) { indexAudio = LIVE_AUDIO_MUTE; }

                indexAudio++;
                setAudioOut(indexAudio);
            }
            else                                        //audio5678
            {
                indexAudio = LIVE_AUDIO_MUTE+1;
                setAudioOut(indexAudio);
            }
        }
        else                                            //ch5678
        {
            if(indexAudio == LIVE_AUDIO_MUTE+1)         //audio mute
            {
                indexAudio = LIVE_AUDIO_SINGLE_5;
                setAudioOut(indexAudio);
            }
            else if(indexAudio <= LIVE_AUDIO_SINGLE_4)  //audio1234
            {
                indexAudio = LIVE_AUDIO_MUTE+1;
                setAudioOut(indexAudio);
            }
            else                                        //audio5678
            {
                if( indexAudio >= LIVE_AUDIO_SINGLE_8 ) { indexAudio = LIVE_AUDIO_MUTE; }

                indexAudio++;
                setAudioOut(indexAudio);
            }
        }

        emit changePrevAudio(indexAudio);
    }
    else
    {
        if( indexAudio >= LIVE_AUDIO_SINGLE_8 ) { indexAudio = LIVE_AUDIO_MUTE; }

        indexAudio++;
        setAudioOut(indexAudio);
    }
}
void MainMenu::setAudioOut(int audioNum)
{
    if(audioNum == AUDIO_LIVE_MUTE-1)
    {
        labelAudioText->setText(tr("Mute"));
        updateAudioIcon(audioNum);

        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Audio Mute");
        emit setAudioMute();
    }
    else if( (audioNum >= LIVE_AUDIO_SINGLE_1) && (audioNum <= LIVE_AUDIO_SINGLE_8) )
    {
        labelAudioText->setText(QString("%1 %2").arg(tr("Audio"), QString::number(audioNum-1)));
        updateAudioIcon(audioNum);

        QString str = QString("%1 %2").arg("Audio Output", QString::number(audioNum-1));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
        emit setAudio(audioNum-1);
    }
    else
    {
        labelAudioText->setText(tr("Mute"));
        updateAudioIcon(audioNum);

        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Audio Mute");
        emit setAudioMute();
    }
}
void MainMenu::onButtonShutdown()
{
    hide();
    emit shutdownClicked();
}
void MainMenu::onButtonClose()
{
    hide();
    emit exitMainMenu();
}
void MainMenu::initMainMenu(void)
{
    audioStatus = cfgMain.gbl.audioOut;

    emit enterMainMenu();

    if(audioStatus == LIVE_AUDIO_MUTE)
    {
        labelAudioText->setText(tr("Mute"));
        updateAudioIcon(LIVE_AUDIO_MUTE+1);

        indexAudio = 1;
        appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, LIVE_AUDIO_MUTE);
    }
    else if (audioStatus >= LIVE_AUDIO_SINGLE_1 && audioStatus <= devInfo.videoNum+1)
    {
        labelAudioText->setText(QString("%1 %2").arg(tr("Audio"), QString::number(audioStatus-1)));
        updateAudioIcon(audioStatus);

        indexAudio = audioStatus;
        appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
    }
    else
    {
        labelAudioText->setText(tr("Mute"));
        updateAudioIcon(LIVE_AUDIO_MUTE+1);

        indexAudio = 1;
        appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, LIVE_AUDIO_MUTE);
    }

    setFocusSetup();
}
void MainMenu::onUpdateAudioButton()
{
    int audioOutCH = cfgMain.gbl.audioOut;

    if(audioOutCH == LIVE_AUDIO_MUTE)
    {
        labelAudioText->setText(tr("Mute"));
        updateAudioIcon(LIVE_AUDIO_MUTE+1);

        indexAudio=1;
    }
    else if(audioOutCH >= LIVE_AUDIO_SINGLE_1 && audioOutCH <= devInfo.videoNum+1)
    {
        labelAudioText->setText(QString("%1 %2").arg(tr("Audio"), QString::number(audioOutCH-1)));
        updateAudioIcon(audioOutCH);

        indexAudio=audioOutCH;
    }
    else
    {
        labelAudioText->setText(tr("Mute"));
        updateAudioIcon(LIVE_AUDIO_MUTE+1);

        indexAudio=1;
    }
}

void MainMenu::updateAudioIcon(int audioNum)
{
    switch(audioNum)
    {
        case 1 :    { iconImageNormal[3].load(":images/main/audiomute.png");   iconImageFocus[3].load(":images/main/audiomute2.png");  break; }
        case 2 :    { iconImageNormal[3].load(":images/main/audio1.png");      iconImageFocus[3].load(":images/main/audio1f.png");     break; }
        case 3 :    { iconImageNormal[3].load(":images/main/audio2.png");      iconImageFocus[3].load(":images/main/audio2f.png");     break; }
        case 4 :    { iconImageNormal[3].load(":images/main/audio3.png");      iconImageFocus[3].load(":images/main/audio3f.png");     break; }
        case 5 :    { iconImageNormal[3].load(":images/main/audio4.png");      iconImageFocus[3].load(":images/main/audio4f.png");     break; }
        case 6 :    { iconImageNormal[3].load(":images/main/audio5.png");      iconImageFocus[3].load(":images/main/audio5f.png");     break; }
        case 7 :    { iconImageNormal[3].load(":images/main/audio6.png");      iconImageFocus[3].load(":images/main/audio6f.png");     break; }
        case 8 :    { iconImageNormal[3].load(":images/main/audio7.png");      iconImageFocus[3].load(":images/main/audio7f.png");     break; }
        case 9 :    { iconImageNormal[3].load(":images/main/audio8.png");      iconImageFocus[3].load(":images/main/audio8f.png");     break; }
        default :   { iconImageNormal[3].load(":images/main/audiomute.png");   iconImageFocus[3].load(":images/main/audiomute2.png");  break; }
    }

    buttonAudio->setPixmap(iconImageFocus[3]);
}

void MainMenu::setFocusSetup()      { changeFocus(1); }
void MainMenu::setFocusSearch()     { changeFocus(2); }
void MainMenu::setFocusAudio()      { changeFocus(4); }
void MainMenu::setFocusShutdown()   { changeFocus(5); }
void MainMenu::setFocusClose()      { changeFocus(6); }

void MainMenu::changeFocus(int n)
{
    buttonSetup         ->setPixmap(iconImageNormal[0]);
    buttonSearch        ->setPixmap(iconImageNormal[1]);
    buttonNotAvailable  ->setPixmap(iconImageNormal[2]);
    buttonAudio         ->setPixmap(iconImageNormal[3]);
    buttonShutdown      ->setPixmap(iconImageNormal[4]);
    buttonClose         ->setPixmap(iconImageNormal[5]);

    buttonSetup         ->setFocusState(false);
    buttonSearch        ->setFocusState(false);
    buttonNotAvailable  ->setFocusState(false);
    buttonAudio         ->setFocusState(false);
    buttonShutdown      ->setFocusState(false);
    buttonClose         ->setFocusState(false);

    switch(n)
    {
        case 1 :
            buttonSetup->setPixmap(iconImageFocus[0]);
            buttonSetup->setFocusState(true);
            break;

        case 2 :
            buttonSearch->setPixmap(iconImageFocus[1]);
            buttonSearch->setFocusState(true);
            break;

        case 3 :
            //buttonNotAvailable->setPixmap(iconImageFocus[2]);
            //buttonNotAvailable->setFocusState(true);
            break;

        case 4 :
            buttonAudio->setPixmap(iconImageFocus[3]);
            buttonAudio->setFocusState(true);
            break;

        case 5 :
            buttonShutdown->setPixmap(iconImageFocus[4]);
            buttonShutdown->setFocusState(true);
            break;

        case 6 :
            buttonClose->setPixmap(iconImageFocus[5]);
            buttonClose->setFocusState(true);
            break;

        default :
            buttonSetup->setPixmap(iconImageFocus[0]);
            buttonSetup->setFocusState(true);
            break;
    }
}

void MainMenu::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
            if     (buttonSetup->hasFocusState())       { setFocusAudio();     }
            else if(buttonSearch->hasFocusState())      { setFocusShutdown();  }
            else if(buttonAudio->hasFocusState())       { setFocusSetup();     }
            else if(buttonShutdown->hasFocusState())    { setFocusSearch();    }
            break;

        case Qt::Key_Down:
            if     (buttonSetup->hasFocusState())       { setFocusAudio();     }
            else if(buttonSearch->hasFocusState())      { setFocusShutdown();  }
            else if(buttonAudio->hasFocusState())       { setFocusSetup();     }
            else if(buttonShutdown->hasFocusState())    { setFocusSearch();    }
            break;

        case Qt::Key_Left:
            if     (buttonSetup->hasFocusState())       { setFocusSearch();    }
            else if(buttonSearch->hasFocusState())      { setFocusSetup();     }
            else if(buttonAudio->hasFocusState())       { setFocusClose();     }
            else if(buttonShutdown->hasFocusState())    { setFocusAudio();     }
            else if(buttonClose->hasFocusState())       { setFocusShutdown();  }
            break;

        case Qt::Key_Right:
            if     (buttonSetup->hasFocusState())       { setFocusSearch();    }
            else if(buttonSearch->hasFocusState())      { setFocusSetup();     }
            else if(buttonAudio->hasFocusState())       { setFocusShutdown();  }
            else if(buttonShutdown->hasFocusState())    { setFocusClose();     }
            else if(buttonClose->hasFocusState())       { setFocusAudio();     }
            break;

        case Qt::Key_Enter:
            if     (buttonSetup->hasFocusState())       { onButtonSetup();    }
            else if(buttonSearch->hasFocusState())      { onButtonSearch();   }
            else if(buttonAudio->hasFocusState())       { onButtonAudio();    }
            else if(buttonShutdown->hasFocusState())    { onButtonShutdown(); }
            else if(buttonClose->hasFocusState())       { onButtonClose();    }
            break;

        case Qt::Key_Escape:
            onButtonClose();
            break;

        default:
            break;
    }
}
