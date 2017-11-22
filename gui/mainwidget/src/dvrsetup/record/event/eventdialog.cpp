#include <QtGui>
#include "eventdialog.h"
#include "main/mainglobal.h"

EventDialog::EventDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonEventTime->setFocus();

    connect(buttonEventTime, SIGNAL(released()), this, SLOT(onEventTime()));
    connect(buttonGsensor,   SIGNAL(released()), this, SLOT(onGsensor()));
    connect(buttonTrigger,   SIGNAL(released()), this, SLOT(onTrigger()));
    connect(buttonSave,      SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,     SIGNAL(released()), this, SLOT(reject()));
}
EventDialog::~EventDialog()
{
}
void EventDialog::initEventConfig(void)
{
    switch(cfgSetup.rec.pre_record[0])
    {
        case 1: { buttonEventTime->setText(tr("%1%2%3").arg(tr("Event"),tr(" Duration\n"),tr("30 sec"))); indexEventTime = 1; } break;
        case 2: { buttonEventTime->setText(tr("%1%2%3").arg(tr("Event"),tr(" Duration\n"),tr("60 sec"))); indexEventTime = 0; } break;
    }

    switch(utils_cfg_cmp_item(RecordCfg.event_impact, "OFF"))
    {
        case 0:  { buttonGsensor->setText(tr("%1%2%3").arg(tr("Impact"),tr(" Record\n"),tr("Off"))); indexGsensor = 1; break; }
        default: { buttonGsensor->setText(tr("%1%2%3").arg(tr("Impact"),tr(" Record\n"),tr("On" ))); indexGsensor = 0; break; }
    }

    switch(utils_cfg_cmp_item(RecordCfg.event_trigger, "OFF"))
    {
        case 0:  { buttonTrigger->setText(tr("%1%2%3").arg(tr("Trigger"),tr(" Record\n"),tr("Off"))); indexTrigger = 1; break; }
        default: { buttonTrigger->setText(tr("%1%2%3").arg(tr("Trigger"),tr(" Record\n"),tr("On" ))); indexTrigger = 0; break; }
    }
}
void EventDialog::onEventTime()
{
    int ch = 0;

    if(indexEventTime == 0)
    {
        buttonEventTime->setText(tr("%1%2%3").arg(tr("Event"),tr(" Duration\n"),tr("30 sec")));
        cfgSetup.rec.pre_record[ch]  = 1;
        cfgSetup.rec.post_record[ch] = 15;
        indexEventTime               = 1;
    }
    else if(indexEventTime == 1)
    {
        buttonEventTime->setText(tr("%1%2%3").arg(tr("Event"),tr(" Duration\n"),tr("60 sec")));
        cfgSetup.rec.pre_record[ch]  = 2;
        cfgSetup.rec.post_record[ch] = 30;
        indexEventTime               = 0;
    }

}
void EventDialog::onGsensor()
{
    switch(indexGsensor)
    {
        case 0:

            buttonGsensor->setText(tr("%1%2%3").arg(tr("Impact"),tr(" Record\n"),tr("Off")));
            utils_cfg_cpy_item(RecordCfg.event_impact, "OFF");
            indexGsensor = 1;

            break;

        case 1:

            buttonGsensor->setText(tr("%1%2%3").arg(tr("Impact"),tr(" Record\n"),tr("On")));
            utils_cfg_cpy_item(RecordCfg.event_impact, "ON");
            indexGsensor = 0;

            break;
    }
}
void EventDialog::onTrigger()
{
    switch(indexTrigger)
    {
        case 0:

            buttonTrigger->setText(tr("%1%2%3").arg(tr("Trigger"),tr(" Record\n"),tr("Off")));
            utils_cfg_cpy_item(RecordCfg.event_trigger, "OFF");
            indexTrigger = 1;

            break;

        case 1:

            buttonTrigger->setText(tr("%1%2%3").arg(tr("Trigger"),tr(" Record\n"),tr("On")));
            utils_cfg_cpy_item(RecordCfg.event_trigger, "ON");
            indexGsensor = 0;
            indexTrigger = 0;

            break;
    }
}
void EventDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonEventTime->hasFocus())        { buttonSave->setFocus();        }
            else if(buttonGsensor->hasFocus())          { buttonEventTime->setFocus();   }
            else if(buttonSave->hasFocus())             { buttonGsensor->setFocus();     }
            else if(buttonTrigger->hasFocus())          { buttonClose->setFocus();       }
            else if(buttonClose->hasFocus())            { buttonTrigger->setFocus();     }

            return;

        case Qt::Key_Down:

                 if(buttonEventTime->hasFocus())        { buttonGsensor->setFocus();     }
            else if(buttonGsensor->hasFocus())          { buttonSave->setFocus();        }
            else if(buttonSave->hasFocus())             { buttonEventTime->setFocus();   }
            else if(buttonTrigger->hasFocus())          { buttonClose->setFocus();       }
            else if(buttonClose->hasFocus())            { buttonTrigger->setFocus();     }

            return;

        case Qt::Key_Left:

                 if(buttonGsensor->hasFocus())          { buttonTrigger->setFocus();     }
            else if(buttonTrigger->hasFocus())          { buttonGsensor->setFocus();     }
            else if(buttonSave->hasFocus())             { buttonClose->setFocus();       }
            else if(buttonClose->hasFocus())            { buttonSave->setFocus();        }

            return;

        case Qt::Key_Right:

                 if(buttonGsensor->hasFocus())          { buttonTrigger->setFocus();     }
            else if(buttonTrigger->hasFocus())          { buttonGsensor->setFocus();     }
            else if(buttonSave->hasFocus())             { buttonClose->setFocus();       }
            else if(buttonClose->hasFocus())            { buttonSave->setFocus();        }

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
void EventDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
