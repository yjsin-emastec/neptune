#include <QtGui>
#include "licenseplatedialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"

LicensePlateDialog::LicensePlateDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonLicensePlate->setFocus();

    labelLicensePlate->setStyleSheet("font:54px;color:white");
    lineEditLicensePlate->setAlignment(Qt::AlignCenter);

    keyboard = NULL;

    connect(buttonLicensePlate, SIGNAL(released()), this, SLOT(onButtonLicensePlate()));

    connect(pushButtonSave,  SIGNAL(released()), this, SLOT(accept()));
    connect(pushButtonClose, SIGNAL(released()), this, SLOT(reject()));
}
LicensePlateDialog::~LicensePlateDialog()
{
}
void LicensePlateDialog::initLicensePlateConfig(void)
{
    QByteArray text = QByteArray::fromHex(SystemCfg.license_plate);
    QString    str  = QString::fromUtf8(text.data());
    lineEditLicensePlate->setText(str);
}
void LicensePlateDialog::onButtonLicensePlate()
{
    int maxLen = 10;
    QString str;

    if(!keyboard)
    {
        keyboard = new UiKeyboardDialog(this);
    }

    keyboard->setKeyboadProperty(str, lineEditLicensePlate->text(), false, maxLen);
    keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

    qDebug("keyboard size : %d, %d", keyboard->width(), keyboard->height());

    if(keyboard->exec())
    {
        QString str = keyboard->text;
        lineEditLicensePlate->setText(str);

        printf("%s \n", qPrintable(str));
        QByteArray text = str.toUtf8().toHex();
        memset(SystemCfg.license_plate, 0, sizeof(SystemCfg.license_plate));
        memcpy(SystemCfg.license_plate, str.toUtf8().toHex(), text.size());
    }

    delete keyboard;
    keyboard = NULL;
}
void LicensePlateDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonLicensePlate->hasFocus())   { pushButtonClose->setFocus();      }
            else if(pushButtonClose->hasFocus())      { buttonLicensePlate->setFocus();   }

            return;

        case Qt::Key_Down:

                 if(buttonLicensePlate->hasFocus())   { pushButtonClose->setFocus();      }
            else if(pushButtonClose->hasFocus())      { buttonLicensePlate->setFocus();   }

            return;

        case Qt::Key_Left:

                 if(pushButtonSave->hasFocus())       { pushButtonClose->setFocus();      }
            else if(pushButtonClose->hasFocus())      { pushButtonSave->setFocus();       }

            return;

        case Qt::Key_Right:

                 if(pushButtonSave->hasFocus())       { pushButtonClose->setFocus();      }
            else if(pushButtonClose->hasFocus())      { pushButtonSave->setFocus();       }

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
void LicensePlateDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
