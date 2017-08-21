#include <QtGui>
#include "normaldialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

NormalDialog::NormalDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonChannel->setFocus();

    connect(buttonChannel,     SIGNAL(released(void)), this, SLOT(onButtonChannel   (void)));
    connect(buttonFrameRate,   SIGNAL(released(void)), this, SLOT(onButtonFrameRate (void)));
    connect(buttonQuality,     SIGNAL(released(void)), this, SLOT(onButtonQuality   (void)));
    connect(buttonRecording,   SIGNAL(released(void)), this, SLOT(onButtonRecording (void)));
    connect(buttonAudio,       SIGNAL(released(void)), this, SLOT(onButtonAudio     (void)));
    connect(buttonDefault,     SIGNAL(released(void)), this, SLOT(onButtonDefault   (void)));
    connect(buttonSave,        SIGNAL(released(void)), this, SLOT(accept            (void)));
    connect(buttonClose,       SIGNAL(released(void)), this, SLOT(reject            (void)));
}
NormalDialog::~NormalDialog()
{
}
void NormalDialog::initNormalConfig(void)
{
    buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("1"))); indexChannel = 1;

    switch(cfgSetup.rec.record_main.fr_hd[0])
    {
        case  5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  indexFrameRate = 1; } break;
        case 10: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  indexFrameRate = 2; } break;
        case 15: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  indexFrameRate = 3; } break;
        case 20: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  indexFrameRate = 4; } break;
        case 25: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  indexFrameRate = 5; } break;
        case 30: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  indexFrameRate = 0; } break;
    }

    switch(cfgSetup.rec.record_main.quality[0])
    {
        case QUALITY_ECONOMY: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"   )));  indexQuality = 1; } break;
        case QUALITY_HIGH:    { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle")));  indexQuality = 2; } break;
        case QUALITY_ULTRA:   { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));  indexQuality = 0; } break;
    }

    switch(cfgSetup.rec.record_type[0])
    {
        case false: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));  indexRecording = 1; } break;
        case true:  { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));  indexRecording = 0; } break;
    }

    switch(cfgSetup.rec.audio[0])
    {
        case false: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));  indexAudio = 1; } break;
        case true:  { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));  indexAudio = 0; } break;
    }
}
void NormalDialog::onButtonChannel(void)
{
    int arVIS[devInfo.videoNum], ch = 0;

    switch(indexChannel)
    {
        case 0: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("1")));  indexChannel = 1; } break;
        case 1: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("2")));  indexChannel = 2; } break;
        case 2: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("3")));  indexChannel = 3; } break;
        case 3: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("4")));  indexChannel = 0; } break;
    }

    if(indexChannel <= 0) { ch = 3; }
    else                  { ch = indexChannel-1; }

    ver_get_vis_list(arVIS);

    //qDebug("Notice: %s %d, idxCh=%d, fr=%d q=%d r_t=%d a=%d\n", __func__, __LINE__, indexChannel, cfgSetup.rec.record_main.fr_hd[ch], cfgSetup.rec.record_main.quality[ch], cfgSetup.rec.record_type[ch], cfgSetup.rec.audio[ch]);

    switch(cfgSetup.rec.record_main.fr_hd[ch])
    {
        case  5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  indexFrameRate = 1; } break;
        case 10: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  indexFrameRate = 2; } break;
        case 15: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  indexFrameRate = 3; } break;
        case 20: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  indexFrameRate = 4; } break;
        case 25: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  indexFrameRate = 5; } break;
        case 30: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  indexFrameRate = 0; } break;
    }

    switch(cfgSetup.rec.record_main.quality[ch])
    {
        case QUALITY_ECONOMY: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"   )));  indexQuality = 1; } break;
        case QUALITY_HIGH:    { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle")));  indexQuality = 2; } break;
        case QUALITY_ULTRA:   { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));  indexQuality = 0; } break;
    }

    switch(cfgSetup.rec.record_type[ch])
    {
        case false: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));  indexRecording = 1; } break;
        case true:  { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));  indexRecording = 0; } break;
    }

    switch(cfgSetup.rec.audio[ch])
    {
        case false: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));  indexAudio = 1; } break;
        case true:  { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));  indexAudio = 0; } break;
    }
}
void NormalDialog::onButtonFrameRate(void)
{
    int ch = 0, arVIS[devInfo.videoNum];

    ver_get_vis_list(arVIS);

    if(indexChannel <= 0) { ch = 3; }
    else                  { ch = indexChannel-1; }

    if((arVIS[ch] == ver_vis_pal) || (arVIS[ch] == ver_vis_hd_720_25p) || (arVIS[ch] == ver_vis_hd_720_50p))
    {
        if(indexFrameRate >= 5) { indexFrameRate = 0; }
    }

    if((arVIS[ch] == ver_vis_hd_1080_25p) || (arVIS[ch] == ver_vis_hd_1080_30p) || (arVIS[ch] == ver_vis_hd_1080_50p) || (arVIS[ch] == ver_vis_hd_1080_60p))
    {
        if(indexFrameRate >= 3) { indexFrameRate = 0; }
    }

    switch(indexFrameRate)
    {
        case 0: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] =  5;  indexFrameRate = 1; } break;
        case 1: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 10;  indexFrameRate = 2; } break;
        case 2: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 15;  indexFrameRate = 3; } break;
        case 3: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 20;  indexFrameRate = 4; } break;
        case 4: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 25;  indexFrameRate = 5; } break;
        case 5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 30;  indexFrameRate = 0; } break;
    }
}
void NormalDialog::onButtonQuality(void)
{
    int ch = 0;
    if(indexChannel <= 0) { ch = 3; }
    else                  { ch = indexChannel-1; }

    switch(indexQuality)
    {
        case 0: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"  )));   cfgSetup.rec.record_main.quality[ch] = QUALITY_ECONOMY;  indexQuality = 1; } break;
        case 1: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle")));  cfgSetup.rec.record_main.quality[ch] = QUALITY_HIGH;     indexQuality = 2; } break;
        case 2: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));  cfgSetup.rec.record_main.quality[ch] = QUALITY_ULTRA;    indexQuality = 0; } break;
    }
}
void NormalDialog::onButtonRecording(void)
{
    int ch = 0;
    if(indexChannel <= 0) { ch = 3; }
    else                  { ch = indexChannel-1; }

    switch(indexRecording)
    {
        case 0: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));  cfgSetup.rec.record_type[ch] = false;  indexRecording = 1; } break;
        case 1: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));  cfgSetup.rec.record_type[ch] = true;   indexRecording = 0; } break;
    }
}
void NormalDialog::onButtonAudio(void)
{
    int ch = 0;
    if(indexChannel <= 0) { ch = 3; }
    else                  { ch = indexChannel-1; }

    switch(indexAudio)
    {
        case 0: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));  cfgSetup.rec.audio[ch] = false;  indexAudio = 1; } break;
        case 1: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));  cfgSetup.rec.audio[ch] = true;   indexAudio = 0; } break;
    }
}
void NormalDialog::onButtonDefault(void)
{
    int ch = 0, arVIS[devInfo.videoNum];

    ver_get_vis_list(arVIS);

    if(indexChannel <= 0) { ch = 3; }
    else                  { ch = indexChannel-1; }

    cfgSetup.rec.record_main.quality[ch] = QUALITY_ULTRA; indexQuality   = 0; buttonQuality   ->setText(tr("%1\n%2"   ).arg(tr("Quality"   ),tr("High")          ));
    cfgSetup.rec.record_type[ch]         = true;          indexRecording = 0; buttonRecording ->setText(tr("%1\n%2"   ).arg(tr("Recording" ),tr("On"  )          ));
    cfgSetup.rec.audio[ch]               = false;         indexAudio     = 1; buttonAudio     ->setText(tr("%1\n%2"   ).arg(tr("Audio"     ),tr("Off" )          ));
    cfgSetup.rec.record_main.fr_hd[ch]   = 30;            indexFrameRate = 0; buttonFrameRate ->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"  ),tr("Fps")));

    if((arVIS[ch] == ver_vis_hd_1080_25p) || (arVIS[ch] == ver_vis_hd_1080_30p) || (arVIS[ch] == ver_vis_hd_1080_50p) || (arVIS[ch] == ver_vis_hd_1080_60p))
    {
        cfgSetup.rec.record_main.fr_hd[ch] = 15; buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));
    }
}
void NormalDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonChannel->hasFocus())            { buttonDefault->setFocus();      }
            else if(buttonDefault->hasFocus())            { buttonChannel->setFocus();      }
            else if(buttonFrameRate->hasFocus())          { buttonSave->setFocus();         }
            else if(buttonRecording->hasFocus())          { buttonFrameRate->setFocus();    }
            else if(buttonSave->hasFocus())               { buttonRecording->setFocus();    }
            else if(buttonQuality->hasFocus())            { buttonClose->setFocus();        }
            else if(buttonAudio->hasFocus())              { buttonQuality->setFocus();      }
            else if(buttonClose->hasFocus())              { buttonAudio->setFocus();        }

            return;

        case Qt::Key_Down:

                 if(buttonChannel->hasFocus())            { buttonDefault->setFocus();      }
            else if(buttonDefault->hasFocus())            { buttonChannel->setFocus();      }
            else if(buttonFrameRate->hasFocus())          { buttonRecording->setFocus();    }
            else if(buttonRecording->hasFocus())          { buttonSave->setFocus();         }
            else if(buttonSave->hasFocus())               { buttonFrameRate->setFocus();    }
            else if(buttonQuality->hasFocus())            { buttonAudio->setFocus();        }
            else if(buttonAudio->hasFocus())              { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())              { buttonQuality->setFocus();      }

            return;

        case Qt::Key_Left:

                 if(buttonChannel->hasFocus())            { buttonQuality->setFocus();      }
            else if(buttonFrameRate->hasFocus())          { buttonChannel->setFocus();      }
            else if(buttonQuality->hasFocus())            { buttonFrameRate->setFocus();    }
            else if(buttonDefault->hasFocus())            { buttonAudio->setFocus();        }
            else if(buttonRecording->hasFocus())          { buttonDefault->setFocus();      }
            else if(buttonAudio->hasFocus())              { buttonRecording->setFocus();    }
            else if(buttonSave->hasFocus())               { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())              { buttonSave->setFocus();         }

            return;

        case Qt::Key_Right:

                 if(buttonChannel->hasFocus())            { buttonFrameRate->setFocus();    }
            else if(buttonFrameRate->hasFocus())          { buttonQuality->setFocus();      }
            else if(buttonQuality->hasFocus())            { buttonChannel->setFocus();      }
            else if(buttonDefault->hasFocus())            { buttonRecording->setFocus();    }
            else if(buttonRecording->hasFocus())          { buttonAudio->setFocus();        }
            else if(buttonAudio->hasFocus())              { buttonDefault->setFocus();      }
            else if(buttonSave->hasFocus())               { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())              { buttonSave->setFocus();         }

            return;

        case Qt::Key_Enter:

            break;

        case Qt::Key_Escape:

            reject();

            return;

        default:

            reject();

            return;
    }

    QDialog::keyPressEvent(event);
}
void NormalDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
