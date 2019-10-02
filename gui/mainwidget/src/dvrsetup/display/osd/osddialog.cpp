#include <QtGui>
#include "osddialog.h"
#include "main/mainglobal.h"

OsdDialog::OsdDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::OsdDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        buttonCameraName = ui720.buttonCameraName;
        buttonNoVideo = ui720.buttonNoVideo;
        buttonStatusBar = ui720.buttonStatusBar;
        buttonRecordStatus = ui720.buttonRecordStatus;
        buttonGpsStatus = ui720.buttonGpsStatus;
        buttonCameraInfo = ui720.buttonCameraInfo;
        buttonSave = ui720.buttonSave;
        buttonClose = ui720.buttonClose;
    }
    else
    {
        Ui::OsdDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        buttonCameraName = ui1080.buttonCameraName;
        buttonNoVideo = ui1080.buttonNoVideo;
        buttonStatusBar = ui1080.buttonStatusBar;
        buttonRecordStatus = ui1080.buttonRecordStatus;
        buttonGpsStatus = ui1080.buttonGpsStatus;
        buttonCameraInfo = ui1080.buttonCameraInfo;
        buttonSave = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonCameraName->setFocus();

    connect(buttonCameraName,   SIGNAL(released()), this, SLOT(onChannelName()));
    connect(buttonNoVideo,      SIGNAL(released()), this, SLOT(onNoVideo()));
    connect(buttonStatusBar,    SIGNAL(released()), this, SLOT(onStatusBar()));
    connect(buttonRecordStatus, SIGNAL(released()), this, SLOT(onRecordStatus()));
    connect(buttonGpsStatus,    SIGNAL(released()), this, SLOT(onGpsStatus()));
    connect(buttonCameraInfo,   SIGNAL(released()), this, SLOT(onCameraInfo()));
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
        case 0 : { buttonCameraName->setText(QString("%1\n%2").arg(tr("Camera Name"),tr("Off")));               indexCameraName   = 0; break; }
        default: { buttonCameraName->setText(QString("%1\n%2").arg(tr("Camera Name"),tr("On")));                indexCameraName   = 1; break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_viloss, "OFF"))
    {
        case 0 : { buttonNoVideo->setText(QString("%1\n%2").arg(tr("No Video"),tr("Off")));                     indexNoVideo      = 0; break; }
        default: { buttonNoVideo->setText(QString("%1\n%2").arg(tr("No Video"),tr("On")));                      indexNoVideo      = 1; break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_status, "OFF"))
    {
        case 0 : { buttonStatusBar->setText(QString("%1\n%2").arg(tr("Status Bar"),tr("AutoHide: Off")));       indexStatusBar    = 0; break; }
        default: { buttonStatusBar->setText(QString("%1\n%2").arg(tr("Status Bar"),tr("AutoHide: On")));        indexStatusBar    = 1; break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_record, "OFF"))
    {
        case 0 : { buttonRecordStatus->setText(QString("%1\n%2").arg(tr("Record Status"),tr("Off")));           indexRecordStatus = 0; break; }
        default: { buttonRecordStatus->setText(QString("%1\n%2").arg(tr("Record Status"),tr("On")));            indexRecordStatus = 1; break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_gps, "OFF"))
    {
        case 0 : { buttonGpsStatus->setText(QString("%1\n%2").arg(tr("Gps Status"), tr("Off")));                indexGpsStatus    = 0; break; }
        default: { buttonGpsStatus->setText(QString("%1\n%2").arg(tr("Gps Status"), tr("On")));                 indexGpsStatus    = 1; break; }
    }

    switch(utils_cfg_cmp_item(DisplayCfg.osd_camera, "OFF"))
    {
        case 0 : { buttonCameraInfo->setText(QString("%1\n%2").arg(tr("Camera Info"), tr("Off")));              indexCameraInfo   = 0; break; }
        default: { buttonCameraInfo->setText(QString("%1\n%2").arg(tr("Camera Info"), tr("On")));               indexCameraInfo   = 1; break; }
    }
}

void OsdDialog::onChannelName()
{
    if(indexCameraName == 1)
    {
        buttonCameraName->setText(QString("%1\n%2").arg(tr("Camera Name"),tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_chname, "OFF");
        indexCameraName = 0;
    }
    else
    {
        buttonCameraName->setText(QString("%1\n%2").arg(tr("Camera Name"),tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_chname, "ON");
        indexCameraName = 1;
    }
}
void OsdDialog::onNoVideo()
{
    if(indexNoVideo == 1)
    {
        buttonNoVideo->setText(QString("%1\n%2").arg(tr("No Video"),tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_viloss, "OFF");
        indexNoVideo = 0;
    }
    else
    {
        buttonNoVideo->setText(QString("%1\n%2").arg(tr("No Video"),tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_viloss, "ON");
        indexNoVideo = 1;
    }
}
void OsdDialog::onStatusBar()
{
    if(indexStatusBar == 1)
    {
        buttonStatusBar->setText(QString("%1\n%2").arg(tr("Status Bar"),tr("AutoHide: Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_status, "OFF");
        indexStatusBar = 0;
    }
    else
    {
        buttonStatusBar->setText(QString("%1\n%2").arg(tr("Status Bar"),tr("AutoHide: On")));
        utils_cfg_cpy_item(DisplayCfg.osd_status, "ON");
        indexStatusBar = 1;
    }
}
void OsdDialog::onRecordStatus()
{
    if(indexRecordStatus == 1)
    {
        buttonRecordStatus->setText(QString("%1\n%2").arg(tr("Record Status"),tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_record, "OFF");
        indexRecordStatus = 0;
    }
    else
    {
        buttonRecordStatus->setText(QString("%1\n%2").arg(tr("Record Status"),tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_record, "ON");
        indexRecordStatus = 1;
    }
}
void OsdDialog::onGpsStatus()
{
    if(indexGpsStatus == 1)
    {
        buttonGpsStatus->setText(QString("%1\n%2").arg(tr("Gps Status"), tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_gps, "OFF");
        indexGpsStatus = 0;
    }
    else
    {
        buttonGpsStatus->setText(QString("%1\n%2").arg(tr("Gps Status"), tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_gps, "ON");
        indexGpsStatus = 1;
    }
}
void OsdDialog::onCameraInfo()
{
    if(indexCameraInfo == 1)
    {
        buttonCameraInfo->setText(QString("%1\n%2").arg(tr("Camera Info"), tr("Off")));
        utils_cfg_cpy_item(DisplayCfg.osd_camera, "OFF");
        indexCameraInfo = 0;
    }
    else
    {
        buttonCameraInfo->setText(QString("%1\n%2").arg(tr("Camera Info"), tr("On")));
        utils_cfg_cpy_item(DisplayCfg.osd_camera, "ON");
        indexCameraInfo = 1;
    }
}
void OsdDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonCameraName->hasFocus())           { buttonSave->setFocus();             }
            else if(buttonStatusBar->hasFocus())            { buttonCameraName->setFocus();       }
            else if(buttonGpsStatus->hasFocus())            { buttonStatusBar->setFocus();        }
            else if(buttonSave->hasFocus())                 { buttonGpsStatus->setFocus();        }
            else if(buttonNoVideo->hasFocus())              { buttonClose->setFocus();            }
            else if(buttonRecordStatus->hasFocus())         { buttonNoVideo->setFocus();          }
            else if(buttonCameraInfo->hasFocus())           { buttonRecordStatus->setFocus();     }
            else if(buttonClose->hasFocus())                { buttonCameraInfo->setFocus();       }

            return;

        case Qt::Key_Down:

                 if(buttonCameraName->hasFocus())           { buttonStatusBar->setFocus();        }
            else if(buttonStatusBar->hasFocus())            { buttonGpsStatus->setFocus();        }
            else if(buttonGpsStatus->hasFocus())            { buttonSave->setFocus();             }
            else if(buttonSave->hasFocus())                 { buttonCameraName->setFocus();       }
            else if(buttonNoVideo->hasFocus())              { buttonRecordStatus->setFocus();     }
            else if(buttonRecordStatus->hasFocus())         { buttonCameraInfo->setFocus();       }
            else if(buttonCameraInfo->hasFocus())           { buttonClose->setFocus();            }
            else if(buttonClose->hasFocus())                { buttonNoVideo->setFocus();          }

            return;

        case Qt::Key_Left:

                 if(buttonCameraName->hasFocus())           { buttonNoVideo->setFocus();          }
            else if(buttonNoVideo->hasFocus())              { buttonCameraName->setFocus();       }
            else if(buttonStatusBar->hasFocus())            { buttonRecordStatus->setFocus();     }
            else if(buttonRecordStatus->hasFocus())         { buttonStatusBar->setFocus();        }
            else if(buttonGpsStatus->hasFocus())            { buttonCameraInfo->setFocus();       }
            else if(buttonCameraInfo->hasFocus())           { buttonGpsStatus->setFocus();        }
            else if(buttonSave->hasFocus())                 { buttonClose->setFocus();            }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();             }

            return;

        case Qt::Key_Right:

                 if(buttonCameraName->hasFocus())           { buttonNoVideo->setFocus();          }
            else if(buttonNoVideo->hasFocus())              { buttonCameraName->setFocus();       }
            else if(buttonStatusBar->hasFocus())            { buttonRecordStatus->setFocus();     }
            else if(buttonRecordStatus->hasFocus())         { buttonStatusBar->setFocus();        }
            else if(buttonGpsStatus->hasFocus())            { buttonCameraInfo->setFocus();       }
            else if(buttonCameraInfo->hasFocus())           { buttonGpsStatus->setFocus();        }
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
