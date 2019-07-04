#include "mainwidget.h"
#include "mainglobal.h"

MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::MainMenu ui720;
        ui720.setupUi(this);

        frame           = ui720.frame;
        buttonSetup     = ui720.buttonSetup;
        buttonSearch    = ui720.buttonSearch;
        buttonAudio     = ui720.buttonAudio;
        buttonShutdown  = ui720.buttonShutdown;
        buttonClose     = ui720.buttonClose;

    }
    else
    {
        Ui::MainMenu1080p ui1080;
        ui1080.setupUi(this);

        frame           = ui1080.frame;
        buttonSetup     = ui1080.buttonSetup;
        buttonSearch    = ui1080.buttonSearch;
        buttonAudio     = ui1080.buttonAudio;
        buttonShutdown  = ui1080.buttonShutdown;
        buttonClose     = ui1080.buttonClose;

        buttonSetup->setStyleSheet("font:70px;");
        buttonSearch->setStyleSheet("font:70px;");
        buttonAudio->setStyleSheet("font:70px;");
        buttonShutdown->setStyleSheet("font:70px;");
        buttonClose->setStyleSheet("font:70px;");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    connect(buttonSetup,     SIGNAL(released()), this, SLOT(onButtonSetup()));
    connect(buttonSearch,    SIGNAL(released()), this, SLOT(onButtonSearch()));
    connect(buttonAudio,     SIGNAL(released()), this, SLOT(onButtonAudio()));
    connect(buttonShutdown,  SIGNAL(released()), this, SLOT(onButtonShutdown()));
    connect(buttonClose,     SIGNAL(released()), this, SLOT(onButtonClose()));

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
    //if(indexAudio > devInfo.videoNum || indexAudio < 0)   { indexAudio = 0; }
    if(indexAudio > 8 || indexAudio < 0)    { indexAudio = 0; }

    if(currentSplit==1)
    {
        if(indexAudio+1 == AUDIO_LIVE_MUTE)
        {
            indexAudio=currentChannelNum+2;
            buttonAudio->setText(QString("%1\n%2").arg(tr("Audio"), QString::number(currentChannelNum+1)));
            QString str = QString("%1 %2").arg("Audio Output", QString::number(currentChannelNum+1));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
            emit setAudio(currentChannelNum+1);
        }
        else
        {
            indexAudio=1;
            buttonAudio->setText(tr("Audio\nMute"));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Audio Mute");
            emit setAudioMute();
        }
    }
    else
    {
        if(indexAudio == 0)
        {
            buttonAudio->setText(tr("Audio\nMute"));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Audio Mute");
            emit setAudioMute();
        }
        else
        {
            buttonAudio->setText(QString("%1\n%2").arg(tr("Audio"), QString::number(indexAudio)));
            QString str = QString("%1 %2").arg("Audio Output", QString::number(indexAudio));
            appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());
            emit setAudio(indexAudio);
        }

        indexAudio++;
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
        buttonAudio->setText(tr("Audio\nMute"));
        indexAudio = 1;
        appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, LIVE_AUDIO_MUTE);
    }
    //else if (audioStatus >= LIVE_AUDIO_SINGLE_1 && audioStatus <= devInfo.videoNum+1)
    else if(audioStatus >= LIVE_AUDIO_SINGLE_1 && audioStatus <= 8+1)
    {
        buttonAudio->setText(QString("%1\n%2").arg(tr("Audio"), QString::number(audioStatus-1)));
        indexAudio = audioStatus;
        appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);
    }
    else
    {
        buttonAudio->setText(tr("Audio\nMute"));
        indexAudio = 1;
        appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, LIVE_AUDIO_MUTE);
    }
}
void MainMenu::onUpdateAudioButton()
{
    int audioOutCH = cfgMain.gbl.audioOut;

    if(audioOutCH == LIVE_AUDIO_MUTE)
    {
        buttonAudio->setText(tr("Audio\nMute"));
        indexAudio=1;
    }
    //else if(audioCH >= LIVE_AUDIO_SINGLE_1 && audioCH <= devInfo.videoNum+1)
    else if(audioOutCH >= LIVE_AUDIO_SINGLE_1 && audioOutCH <= 8+1)
    {
        buttonAudio->setText(QString("%1\n%2").arg(tr("Audio"), QString::number(audioOutCH-1)));
        indexAudio=audioOutCH;
    }
    else
    {
        buttonAudio->setText(tr("Audio\nMute"));
        indexAudio=1;
    }
}
void MainMenu::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonSetup->hasFocus())     { buttonAudio->setFocus();      }
            else if(buttonAudio->hasFocus())     { buttonSetup->setFocus();      }
            else if(buttonSearch->hasFocus())    { buttonShutdown->setFocus();   }
            else if(buttonShutdown->hasFocus())  { buttonSearch->setFocus();     }

            return;

        case Qt::Key_Down:

                 if(buttonSetup->hasFocus())     { buttonAudio->setFocus();      }
            else if(buttonAudio->hasFocus())     { buttonSetup->setFocus();      }
            else if(buttonSearch->hasFocus())    { buttonShutdown->setFocus();   }
            else if(buttonShutdown->hasFocus())  { buttonSearch->setFocus();     }

            return;

        case Qt::Key_Left:

                 if(buttonSetup->hasFocus())     { buttonSearch->setFocus();     }
            else if(buttonSearch->hasFocus())    { buttonSetup->setFocus();      }
            else if(buttonAudio->hasFocus())     { buttonClose->setFocus();      }
            else if(buttonShutdown->hasFocus())  { buttonAudio->setFocus();      }
            else if(buttonClose->hasFocus())     { buttonShutdown->setFocus();   }

            return;

        case Qt::Key_Right:

                 if(buttonSetup->hasFocus())     { buttonSearch->setFocus();     }
            else if(buttonSearch->hasFocus())    { buttonSetup->setFocus();      }
            else if(buttonAudio->hasFocus())     { buttonShutdown->setFocus();   }
            else if(buttonShutdown->hasFocus())  { buttonClose->setFocus();      }
            else if(buttonClose->hasFocus())     { buttonAudio->setFocus();      }

            return;

        case Qt::Key_Enter:

            break;

        case Qt::Key_Escape:

            onButtonClose();

            return;

        default:

            onButtonClose();

            return;
    }

    QDialog::keyPressEvent(event);
}
