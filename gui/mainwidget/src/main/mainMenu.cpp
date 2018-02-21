#include "mainwidget.h"
#include "mainglobal.h"

MainMenu::MainMenu(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

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
    if(indexAudio >= 5) { indexAudio = 0; }

    if(currentSplit==1)
    {
        if(indexAudio+1==AUDIO_LIVE_MUTE)
        {
            switch(currentChannelNum)
            {
                case 0: { buttonAudio->setText(tr("Audio\n1"));     indexAudio=2;       emit setAudio1();    break; }
                case 1: { buttonAudio->setText(tr("Audio\n2"));     indexAudio=3;       emit setAudio2();    break; }
                case 2: { buttonAudio->setText(tr("Audio\n3"));     indexAudio=4;       emit setAudio3();    break; }
                case 3: { buttonAudio->setText(tr("Audio\n4"));     indexAudio=5;       emit setAudio4();    break; }
            }
        }
        else
        {
            buttonAudio->setText(tr("Audio\nMute"));
            indexAudio=1;

            emit setAudioMute();
        }
    }
    else
    {
        switch(++indexAudio)
        {
            case 1: { buttonAudio->setText(tr("Audio\nMute")); emit setAudioMute(); break; }
            case 2: { buttonAudio->setText(tr("Audio\n1"));    emit setAudio1();    break; }
            case 3: { buttonAudio->setText(tr("Audio\n2"));    emit setAudio2();    break; }
            case 4: { buttonAudio->setText(tr("Audio\n3"));    emit setAudio3();    break; }
            case 5: { buttonAudio->setText(tr("Audio\n4"));    emit setAudio4();    break; }
        }
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

    switch(audioStatus)
    {
        case LIVE_AUDIO_MUTE:

            buttonAudio->setText(tr("Audio\nMute"));
            indexAudio = 1;
            appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, indexAudio-1);

            break;

        case LIVE_AUDIO_SINGLE_1:

            buttonAudio->setText(tr("Audio\n1"));
            indexAudio = 2;

            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);

            break;

        case LIVE_AUDIO_SINGLE_2:

            buttonAudio->setText(tr("Audio\n2"));
            indexAudio = 3;

            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);

            break;

        case LIVE_AUDIO_SINGLE_3:

            buttonAudio->setText(tr("Audio\n3"));
            indexAudio = 4;

            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);

            break;

        case LIVE_AUDIO_SINGLE_4:

            buttonAudio->setText(tr("Audio\n4"));
            indexAudio = 5;

            appmgr_set_audio_output_mix(AUDIO_LIVE, audioStatus-2);

            break;

        default:

            buttonAudio->setText(tr("Audio\nMute"));
            indexAudio = 1;
            appmgr_set_audio_output_mix(AUDIO_LIVE_MUTE, indexAudio-1);

            break;
    }
}
void MainMenu::onUpdateAudioButton()
{
    switch(cfgMain.gbl.audioOut)
    {
        case 0: { buttonAudio->setText(tr("Audio\nMute"));  indexAudio=1;   break; }
        case 2: { buttonAudio->setText(tr("Audio\n1"));     indexAudio=2;   break; }
        case 3: { buttonAudio->setText(tr("Audio\n2"));     indexAudio=3;   break; }
        case 4: { buttonAudio->setText(tr("Audio\n3"));     indexAudio=4;   break; }
        case 5: { buttonAudio->setText(tr("Audio\n4"));     indexAudio=5;   break; }
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
