#include <QtGui>
#include "configdialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "main/mainglobal.h"
#include "appmgr.h"

ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::ConfigDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelConfig = ui720.labelConfig;
        buttonSaveConfig = ui720.buttonSaveConfig;
        buttonLoadConfig = ui720.buttonLoadConfig;
        buttonClose = ui720.buttonClose;

        labelConfig->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
    }
    else
    {
        Ui::ConfigDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelConfig = ui1080.labelConfig;
        buttonSaveConfig = ui1080.buttonSaveConfig;
        buttonLoadConfig = ui1080.buttonLoadConfig;
        buttonClose = ui1080.buttonClose;

        labelConfig->setStyleSheet("font:70px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    msgBox = NULL;

    buttonSaveConfig->setFocus();

    connect(buttonSaveConfig, SIGNAL(released()), this, SLOT(onButtonSaveConfig()));
    connect(buttonLoadConfig, SIGNAL(released()), this, SLOT(onButtonLoadConfig()));
    connect(buttonClose,      SIGNAL(released()), this, SLOT(reject()));
}
ConfigDialog::~ConfigDialog()
{
}
void ConfigDialog::initConfigConfig(void)
{
    buttonSaveConfig->setFocus();
    UpdateLabelConfig(2);
}
void ConfigDialog::UpdateLabelConfig(int type)
{
    switch(type)
    {
        case 1: { labelConfig->setText(tr("%1"    ).arg(tr("Please wait for a while.")));                                   break; }
        case 2: { labelConfig->setText(tr("%1"    ).arg(tr("Please insert a USB memory.")));                                break; }
        case 3: { labelConfig->setText(tr("%1"    ).arg(tr("Config file does not exist.")));                                break; }
        case 4: { labelConfig->setText(tr("%1"    ).arg(tr("Config file was saved.")));                                     break; }
        case 5: { labelConfig->setText(tr("%1\n%2").arg(tr("Config was loaded successfully."),tr("System will restart."))); break; }
    }
}
void ConfigDialog::Delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void ConfigDialog::onButtonLoadConfig()
{
    if(!msgBox)
    {
        msgBox = new TextMessageDialog(tr("Config Load"), tr("After loading a configuration,\n" "System will restart."), 1, this);
    }
    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
    msgBoxEsckey = 1;

    if(msgBox->exec())
    {
        UpdateLabelConfig(1);
        buttonSaveConfig->setEnabled(false);
        buttonLoadConfig->setEnabled(false);
        buttonClose->setEnabled(false);

        Delay(10);

        int rv = aif_config_load_from_usb();

        if(rv < 0)
        {
            if(rv == -1) { UpdateLabelConfig(2); }
            else         { UpdateLabelConfig(3); }
        }
        else
        {
            UpdateLabelConfig(5);
            buttonClose->setEnabled(false);

            while(1)
            {
                int usbCheck = utils_appup_device_check();

                if(usbCheck == 0)
                {
                    if(msgBox)
                    {
                        delete msgBox;
                        msgBox = NULL;
                    }

                    if(!msgBox)
                    {
                        msgBox = new TextMessageDialog(tr("NOTICE"), tr("Please unplug USB memory."), 2, this);
                    }
                    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

                    if(msgBox->exec())
                    {
                        ;
                    }
                }
                else if(usbCheck == -1)
                {
                    break;
                }

                Delay(100);
            }

            QDialog::accept();
        }

        buttonSaveConfig->setEnabled(true);
        buttonLoadConfig->setEnabled(true);
        buttonClose->setEnabled(true);
        buttonLoadConfig->setFocus();
    }

    delete msgBox;
    msgBox = NULL;
    msgBoxEsckey = 0;
}
void ConfigDialog::onButtonSaveConfig()
{
    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Config Saving Start");
    UpdateLabelConfig(1);

    buttonSaveConfig->setEnabled(false);
    buttonLoadConfig->setEnabled(false);
    buttonClose->setEnabled(false);

    Delay(10);

    int rv = aif_config_save_to_usb();

    if(rv < 0)
    {
        UpdateLabelConfig(2);
    }
    else
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Config Saving End");
        UpdateLabelConfig(4);
    }

    buttonSaveConfig->setEnabled(true);
    buttonLoadConfig->setEnabled(true);
    buttonClose->setEnabled(true);
    buttonSaveConfig->setFocus();
}
void ConfigDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonLoadConfig->hasFocus())     { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())          { buttonLoadConfig->setFocus();   }

            return;

        case Qt::Key_Down:

                 if(buttonLoadConfig->hasFocus())     { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())          { buttonLoadConfig->setFocus();   }

            return;

        case Qt::Key_Left:

                 if(buttonSaveConfig->hasFocus())     { buttonLoadConfig->setFocus();   }
            else if(buttonLoadConfig->hasFocus())     { buttonSaveConfig->setFocus();   }

            return;

        case Qt::Key_Right:

                 if(buttonSaveConfig->hasFocus())     { buttonLoadConfig->setFocus();   }
            else if(buttonLoadConfig->hasFocus())     { buttonSaveConfig->setFocus();   }

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
void ConfigDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
