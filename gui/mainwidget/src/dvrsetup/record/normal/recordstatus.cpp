#include <QtGui>
#include "recordstatus.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

RecordStatus::RecordStatus(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    labelRecordStatus->setStyleSheet("font:50px;background-color:rgb(50,57,83);color:white");

    labelFrame->setStyleSheet("font:48px;color:white");
    labelQuality->setStyleSheet("font:48px;color:white");
    labelRecording->setStyleSheet("font:48px;color:white");
    labelAudio->setStyleSheet("font:48px;color:white");

    labelCh1->setStyleSheet("font:48px;color:white");
    labelCh2->setStyleSheet("font:48px;color:white");
    labelCh3->setStyleSheet("font:48px;color:white");
    labelCh4->setStyleSheet("font:48px;color:white");

    labelFrame1->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelFrame2->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelFrame3->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelFrame4->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

    labelQuality1->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelQuality2->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelQuality3->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelQuality4->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

    labelRecording1->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelRecording2->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelRecording3->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelRecording4->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

    labelAudio1->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelAudio2->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelAudio3->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelAudio4->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

    connect(buttonClose,       SIGNAL(released(void)), this, SLOT(reject            (void)));

    updateRecordStatus();
}
RecordStatus::~RecordStatus()
{
}
void RecordStatus::updateRecordStatus(void)
{
    QString frame, quality, recording, audio;

    for(int i=0;i<devInfo.videoNum;i++)
    {
        switch(cfgSetup.rec.record_main.fr_hd[i])
        {
            case  5: { frame = QString("%1 %2").arg(cfgSetup.rec.record_main.fr_hd[i]).arg("Fps"); }   break;
            case 10: { frame = QString("%1 %2").arg(cfgSetup.rec.record_main.fr_hd[i]).arg("Fps"); }   break;
            case 15: { frame = QString("%1 %2").arg(cfgSetup.rec.record_main.fr_hd[i]).arg("Fps"); }   break;
            case 20: { frame = QString("%1 %2").arg(cfgSetup.rec.record_main.fr_hd[i]).arg("Fps"); }   break;
            case 25: { frame = QString("%1 %2").arg(cfgSetup.rec.record_main.fr_hd[i]).arg("Fps"); }   break;
            case 30: { frame = QString("%1 %2").arg(cfgSetup.rec.record_main.fr_hd[i]).arg("Fps"); }   break;
        }
        switch(cfgSetup.rec.record_main.quality[i])
        {
            case QUALITY_ECONOMY: { quality = QString("%1").arg(tr("Low")); }     break;
            case QUALITY_HIGH:    { quality = QString("%1").arg(tr("Middle")); }  break;
            case QUALITY_ULTRA:   { quality = QString("%1").arg(tr("High")); }    break;
        }
        switch(cfgSetup.rec.record_type[i])
        {
            case false: { recording = QString("%1").arg(tr("Off")); }  break;
            case true:  { recording = QString("%1").arg(tr("On")); }   break;
        }
        switch(cfgSetup.rec.audio[i])
        {
            case false: { audio = QString("%1").arg(tr("Off")); }      break;
            case true:  { audio = QString("%1").arg(tr("On")); }       break;
        }

        switch(i)
        {
            case 0 :
            {
                labelFrame1    ->setText(frame);
                labelQuality1  ->setText(quality);
                labelRecording1->setText(recording);
                labelAudio1    ->setText(audio);
            }
            case 1 :
            {
                labelFrame2    ->setText(frame);
                labelQuality2  ->setText(quality);
                labelRecording2->setText(recording);
                labelAudio2    ->setText(audio);
            }
            case 2 :
            {
                labelFrame3    ->setText(frame);
                labelQuality3  ->setText(quality);
                labelRecording3->setText(recording);
                labelAudio3    ->setText(audio);
            }
            case 3 :
            {
                labelFrame4    ->setText(frame);
                labelQuality4  ->setText(quality);
                labelRecording4->setText(recording);
                labelAudio4    ->setText(audio);
            }
        }
    }
}

void RecordStatus::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Enter:
        {
            if(buttonClose->hasFocus())
            {
                reject();
            }

            return;
        }
        case Qt::Key_Escape:
        {
            reject();

            return;
        }
        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
void RecordStatus::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
