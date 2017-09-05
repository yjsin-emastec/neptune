#include <QtGui>
#include "gsensordialog.h"
#include "main/mainglobal.h"

GsensorDialog::GsensorDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));

    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonGsensor->setFocus();

    connect(buttonGsensor,  SIGNAL(released()), this, SLOT(onButtonGsensor()));
    connect(buttonSave,     SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,    SIGNAL(released()), this, SLOT(reject()));
}
GsensorDialog::~GsensorDialog()
{
}
void GsensorDialog::initGsensorConfig(void)
{
         if(utils_cfg_cmp_item(DeviceCfg.gsensor_level, "1") == 0) { buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 1")));  indexGsensor = 0; }
    else if(utils_cfg_cmp_item(DeviceCfg.gsensor_level, "2") == 0) { buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 2")));  indexGsensor = 1; }
    else if(utils_cfg_cmp_item(DeviceCfg.gsensor_level, "3") == 0) { buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 3")));  indexGsensor = 2; }
    else if(utils_cfg_cmp_item(DeviceCfg.gsensor_level, "4") == 0) { buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 4")));  indexGsensor = 3; }
    else                                                           { buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 5")));  indexGsensor = 4; }
}
void GsensorDialog::onButtonGsensor()
{
    switch(indexGsensor)
    {
        case 0:

            buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 2")));
            utils_cfg_cpy_item(DeviceCfg.gsensor_level, "2");
            indexGsensor = 1;

            break;

        case 1:

            buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 3")));
            utils_cfg_cpy_item(DeviceCfg.gsensor_level, "3");
            indexGsensor = 2;

            break;

        case 2:

            buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 4")));
            utils_cfg_cpy_item(DeviceCfg.gsensor_level, "4");
            indexGsensor = 3;

            break;

        case 3:

            buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 5")));
            utils_cfg_cpy_item(DeviceCfg.gsensor_level, "5");
            indexGsensor = 4;

            break;

        case 4:

            buttonGsensor->setText(tr("%1%2").arg(tr("Impact"),tr("\nSensitivity: 1")));
            utils_cfg_cpy_item(DeviceCfg.gsensor_level, "1");
            indexGsensor = 0;

            break;
    }
}
void GsensorDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonGsensor->hasFocus())          { buttonSave->setFocus();         }
            else if(buttonSave->hasFocus())             { buttonGsensor->setFocus();      }
            else if(buttonClose->hasFocus())            { buttonGsensor->setFocus();      }

            return;

        case Qt::Key_Down:

                 if(buttonGsensor->hasFocus())          { buttonSave->setFocus();         }
            else if(buttonSave->hasFocus())             { buttonGsensor->setFocus();      }
            else if(buttonClose->hasFocus())            { buttonGsensor->setFocus();      }

            return;

        case Qt::Key_Left:

                 if(buttonSave->hasFocus())             { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())            { buttonSave->setFocus();         }

            return;

        case Qt::Key_Right:

                 if(buttonSave->hasFocus())             { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())            { buttonSave->setFocus();         }

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
void GsensorDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
