#include <QtGui>
#include "buzzerdialog.h"
#include "main/mainglobal.h"

BuzzerDialog::BuzzerDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonBuzzer->setFocus();

    connect(buttonBuzzer,    SIGNAL(released()), this, SLOT(onButtonBuzzer()));
    connect(pushButtonSave,  SIGNAL(released()), this, SLOT(accept()));
    connect(pushButtonClose, SIGNAL(released()), this, SLOT(reject()));
}
BuzzerDialog::~BuzzerDialog()
{
}
void BuzzerDialog::initBuzzerConfig(void)
{
    switch(utils_cfg_cmp_item(DeviceCfg.buzzer_output, "OFF"))
    {
        case 0:  { buttonBuzzer->setText(tr("%1%2").arg(tr("Buzzer"),tr("\nOutput: Off"))); indexBuzzer = 1; break; }
        default: { buttonBuzzer->setText(tr("%1%2").arg(tr("Buzzer"),tr("\nOutput: On")));  indexBuzzer = 0; break; }
    }
}
void BuzzerDialog::onButtonBuzzer()
{
    switch(indexBuzzer)
    {
        case 0:

            buttonBuzzer->setText(tr("%1%2").arg(tr("Buzzer"),tr("\nOutput: Off")));
            utils_cfg_cpy_item(DeviceCfg.buzzer_output, "OFF");
            indexBuzzer = 1;

            break;

        case 1:

            buttonBuzzer->setText(tr("%1%2").arg(tr("Buzzer"),tr("\nOutput: On")));
            utils_cfg_cpy_item(DeviceCfg.buzzer_output, "ON");
            indexBuzzer = 0;

            break;
    }
}
void BuzzerDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonBuzzer->hasFocus())               { pushButtonSave->setFocus();        }
            else if(pushButtonSave->hasFocus())             { buttonBuzzer->setFocus();          }
            else if(pushButtonClose->hasFocus())            { buttonBuzzer->setFocus();          }

            return;

        case Qt::Key_Down:

                 if(buttonBuzzer->hasFocus())               { pushButtonSave->setFocus();        }
            else if(pushButtonSave->hasFocus())             { buttonBuzzer->setFocus();          }
            else if(pushButtonClose->hasFocus())            { buttonBuzzer->setFocus();          }

            return;

        case Qt::Key_Left:

                 if(pushButtonSave->hasFocus())             { pushButtonClose->setFocus();        }
            else if(pushButtonClose->hasFocus())            { pushButtonSave->setFocus();         }

            return;

        case Qt::Key_Right:

                 if(pushButtonSave->hasFocus())             { pushButtonClose->setFocus();        }
            else if(pushButtonClose->hasFocus())            { pushButtonSave->setFocus();         }

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
void BuzzerDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
