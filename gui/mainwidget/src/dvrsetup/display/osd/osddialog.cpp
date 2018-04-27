#include <QtGui>
#include "osddialog.h"
#include "main/mainglobal.h"

OsdDialog::OsdDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonCameraName->setFocus();

#if 1 //yjsin [18/01/05] if text is long, change font size
    if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
    {
        buttonStatusBar->setStyleSheet("font:45px;color:white");
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        buttonRecordStatus->setStyleSheet("font:41px;color:white");
    }
#endif

    connect(buttonCameraName,   SIGNAL(released()), this, SLOT(onChannelName()));
    connect(buttonNoVideo,      SIGNAL(released()), this, SLOT(onNoVideo()));
    connect(buttonStatusBar,    SIGNAL(released()), this, SLOT(onStatusBar()));
    connect(buttonRecordStatus, SIGNAL(released()), this, SLOT(onRecordStatus()));
    connect(buttonSave,         SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,        SIGNAL(released()), this, SLOT(reject()));
}
OsdDialog::~OsdDialog()
{
}
void OsdDialog::initOsdConfig(void)
{
    switch(utils_cfg_cmp_item(DisplayCfg.osd_chname, "OFF"))
    {
        case 0:  { buttonCameraName->setText(tr("%1\n%2").arg(tr("Camera Name"),tr("Off")));                    indexCameraName   = 1;  break; }
        default: { buttonCameraName->setText(tr("%1\n%2").arg(tr("Camera Name"),tr("On")));                     indexCameraName   = 0;  break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_viloss, "OFF"))
    {
        case 0:  { buttonNoVideo->setText(tr("%1\n%2").arg(tr("No Video"),tr("Off")));                          indexNoVideo      = 1;  break; }
        default: { buttonNoVideo->setText(tr("%1\n%2").arg(tr("No Video"),tr("On")));                           indexNoVideo      = 0;  break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF"))
    {
        case 0:  { buttonStatusBar->setText(tr("%1%2%3").arg(tr("Status Bar"),tr("\nAutoHide: "),tr("Off ")));   indexStatusBar    = 1;  break; }
        default: { buttonStatusBar->setText(tr("%1%2%3").arg(tr("Status Bar"),tr("\nAutoHide: "),tr("On ")));    indexStatusBar    = 0;  break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_record, "OFF"))
    {
        case 0:  { buttonRecordStatus->setText(tr("%1\n%2").arg(tr("Record Status"),tr("Off")));                indexRecordStatus = 1;  break; }
        default: { buttonRecordStatus->setText(tr("%1\n%2").arg(tr("Record Status"),tr("On")));                 indexRecordStatus = 0;  break; }
    }
}
void OsdDialog::onChannelName()
{
    if(indexCameraName == 0)
    {
        buttonCameraName->setText(tr("%1\n%2").arg(tr("Camera Name"),tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_chname, "OFF");
        indexCameraName = 1;
    }
    else if(indexCameraName == 1)
    {
        buttonCameraName->setText(tr("%1\n%2").arg(tr("Camera Name"),tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_chname, "ON");
        indexCameraName = 0;
    }
}
void OsdDialog::onNoVideo()
{
    if(indexNoVideo == 0)
    {
        buttonNoVideo->setText(tr("%1\n%2").arg(tr("No Video"),tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_viloss, "OFF");
        indexNoVideo = 1;
    }
    else if(indexNoVideo == 1)
    {
        buttonNoVideo->setText(tr("%1\n%2").arg(tr("No Video"),tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_viloss, "ON");
        indexNoVideo = 0;
    }
}
void OsdDialog::onStatusBar()
{
    if(indexStatusBar == 0)
    {
        qDebug("hi3");
        buttonStatusBar->setText(tr("%1%2%3").arg(tr("Status Bar"),tr("\nAutoHide: "),tr("Off ")));
        utils_cfg_cpy_item(DisplayCfg.osd_status, "OFF");
        indexStatusBar = 1;
    }
    else if(indexStatusBar == 1)
    {
        buttonStatusBar->setText(tr("%1%2%3").arg(tr("Status Bar"),tr("\nAutoHide: "),tr("On ")));
        utils_cfg_cpy_item(DisplayCfg.osd_status, "ON");
        indexStatusBar = 0;
    }
}
void OsdDialog::onRecordStatus()
{
    if(indexRecordStatus == 0)
    {
        buttonRecordStatus->setText(tr("%1\n%2").arg(tr("Record Status"),tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_record, "OFF");
        indexRecordStatus = 1;
    }
    else if(indexRecordStatus == 1)
    {
        buttonRecordStatus->setText(tr("%1\n%2").arg(tr("Record Status"),tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_record, "ON");
        indexRecordStatus = 0;
    }
}
void OsdDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonCameraName->hasFocus())           { buttonSave->setFocus();             }
            else if(buttonStatusBar->hasFocus())            { buttonCameraName->setFocus();       }
            else if(buttonSave->hasFocus())                 { buttonStatusBar->setFocus();        }
            else if(buttonNoVideo->hasFocus())              { buttonClose->setFocus();            }
            else if(buttonRecordStatus->hasFocus())         { buttonNoVideo->setFocus();          }
            else if(buttonClose->hasFocus())                { buttonRecordStatus->setFocus();     }

            return;

        case Qt::Key_Down:

                 if(buttonCameraName->hasFocus())           { buttonStatusBar->setFocus();        }
            else if(buttonStatusBar->hasFocus())            { buttonSave->setFocus();             }
            else if(buttonSave->hasFocus())                 { buttonCameraName->setFocus();       }
            else if(buttonNoVideo->hasFocus())              { buttonRecordStatus->setFocus();     }
            else if(buttonRecordStatus->hasFocus())         { buttonClose->setFocus();            }
            else if(buttonClose->hasFocus())                { buttonNoVideo->setFocus();          }

            return;

        case Qt::Key_Left:

                 if(buttonCameraName->hasFocus())           { buttonNoVideo->setFocus();          }
            else if(buttonNoVideo->hasFocus())              { buttonCameraName->setFocus();       }
            else if(buttonStatusBar->hasFocus())            { buttonRecordStatus->setFocus();     }
            else if(buttonRecordStatus->hasFocus())         { buttonStatusBar->setFocus();        }
            else if(buttonSave->hasFocus())                 { buttonClose->setFocus();            }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();             }

            return;

        case Qt::Key_Right:

                 if(buttonCameraName->hasFocus())           { buttonNoVideo->setFocus();          }
            else if(buttonNoVideo->hasFocus())              { buttonCameraName->setFocus();       }
            else if(buttonStatusBar->hasFocus())            { buttonRecordStatus->setFocus();     }
            else if(buttonRecordStatus->hasFocus())         { buttonStatusBar->setFocus();        }
            else if(buttonSave->hasFocus())                 { buttonClose->setFocus();            }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();             }

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
void OsdDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
