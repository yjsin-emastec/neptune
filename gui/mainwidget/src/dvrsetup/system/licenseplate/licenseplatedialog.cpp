#include <QtGui>
#include "licenseplatedialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"

LicensePlateDialog::LicensePlateDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::LicensePlateDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelLicensePlate = ui720.labelLicensePlate;
        lineEditLicensePlate = ui720.lineEditLicensePlate;
        buttonLicensePlate = ui720.buttonLicensePlate;
        pushButtonSave = ui720.pushButtonSave;
        pushButtonClose = ui720.pushButtonClose;

        labelLicensePlate->setStyleSheet("font:54px;color:white");

        //yjsin [17/10/12] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
        {
            labelLicensePlate->setStyleSheet("font:43px;color:white");
        }
    }
    else
    {
        Ui::LicensePlateDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelLicensePlate = ui1080.labelLicensePlate;
        lineEditLicensePlate = ui1080.lineEditLicensePlate;
        buttonLicensePlate = ui1080.buttonLicensePlate;
        pushButtonSave = ui1080.pushButtonSave;
        pushButtonClose = ui1080.pushButtonClose;

        labelLicensePlate->setStyleSheet("font:80px;color:white");

        //yjsin [19/02/21] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
        {
            labelLicensePlate->setStyleSheet("font:63px;color:white");
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonLicensePlate->setFocus();

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
        lineEditLicensePlate->setText(str.trimmed());

        printf("%s \n", qPrintable(str));
        QByteArray text = str.trimmed().toUtf8().toHex();
        memset(SystemCfg.license_plate, 0, sizeof(SystemCfg.license_plate));
        memcpy(SystemCfg.license_plate, str.trimmed().toUtf8().toHex(), text.size());
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

            return;
    }

    QDialog::keyPressEvent(event);
}
void LicensePlateDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
