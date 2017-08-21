#include <QtGui>
#include "videoinputdialog.h"
#include "main/mainglobal.h"

VideoInputDialog::VideoInputDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonCamera->setFocus();

    connect(buttonCamera, SIGNAL(released()), this, SLOT(onButtonCamera()));
    connect(buttonMirror, SIGNAL(released()), this, SLOT(onButtonMirror()));
    connect(buttonFlip,   SIGNAL(released()), this, SLOT(onButtonFlip()));
    connect(buttonSave,   SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,  SIGNAL(released()), this, SLOT(reject()));
}
VideoInputDialog::~VideoInputDialog()
{
}
void VideoInputDialog::initVideoInputConfig(void)
{
    buttonCamera->setText(tr("Camera1")); indexCamera = 1;

    if(utils_cfg_cmp_item(DeviceCfg.camera_mirror00, "NORMAL") == 0)
    {
        buttonMirror->setText(tr("Normal"));  indexMirror = 1;
    }
    else if(utils_cfg_cmp_item(DeviceCfg.camera_mirror00, "MIRROR") == 0)
    {
        buttonMirror->setText(tr("Mirror"));  indexMirror = 0;
    }

    if(utils_cfg_cmp_item(DeviceCfg.camera_flip00, "UP") == 0)
    {
        buttonFlip->setText(tr("Up"));  indexFlip = 1;
    }
    else if(utils_cfg_cmp_item(DeviceCfg.camera_flip00, "DOWN") == 0)
    {
        buttonFlip->setText(tr("Down"));  indexFlip = 0;
    }
}
void VideoInputDialog::onButtonCamera(void)
{
    int ch = 0;

    switch(indexCamera)
    {
        case 0: { buttonCamera->setText(tr("Camera1"));  indexCamera = 1; } break;
        case 1: { buttonCamera->setText(tr("Camera2"));  indexCamera = 2; } break;
        case 2: { buttonCamera->setText(tr("Camera3"));  indexCamera = 3; } break;
        case 3: { buttonCamera->setText(tr("Camera4"));  indexCamera = 0; } break;
    }

    if(indexCamera <= 0) { ch = 3; }
    else                 { ch = indexCamera-1; }

    switch(ch)
    {
        case 0:

                 if(utils_cfg_cmp_item(DeviceCfg.camera_mirror00, "NORMAL") == 0) { buttonMirror->setText(tr("Normal")); indexMirror = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_mirror00, "MIRROR") == 0) { buttonMirror->setText(tr("Mirror")); indexMirror = 0; }

                 if(utils_cfg_cmp_item(DeviceCfg.camera_flip00, "UP")   == 0) { buttonFlip->setText(tr("Up"));   indexFlip = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_flip00, "DOWN") == 0) { buttonFlip->setText(tr("Down")); indexFlip = 0; }

            break;

        case 1:

                 if(utils_cfg_cmp_item(DeviceCfg.camera_mirror01, "NORMAL") == 0) { buttonMirror->setText(tr("Normal")); indexMirror = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_mirror01, "MIRROR") == 0) { buttonMirror->setText(tr("Mirror")); indexMirror = 0; }

                 if(utils_cfg_cmp_item(DeviceCfg.camera_flip01, "UP")   == 0) { buttonFlip->setText(tr("Up"));   indexFlip = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_flip01, "DOWN") == 0) { buttonFlip->setText(tr("Down")); indexFlip = 0; }

            break;

        case 2:

                 if(utils_cfg_cmp_item(DeviceCfg.camera_mirror02, "NORMAL") == 0) { buttonMirror->setText(tr("Normal")); indexMirror = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_mirror02, "MIRROR") == 0) { buttonMirror->setText(tr("Mirror")); indexMirror = 0; }

                 if(utils_cfg_cmp_item(DeviceCfg.camera_flip02, "UP")   == 0) { buttonFlip->setText(tr("Up"));   indexFlip = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_flip02, "DOWN") == 0) { buttonFlip->setText(tr("Down")); indexFlip = 0; }

            break;

        case 3:

                 if(utils_cfg_cmp_item(DeviceCfg.camera_mirror03, "NORMAL") == 0) { buttonMirror->setText(tr("Normal")); indexMirror = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_mirror03, "MIRROR") == 0) { buttonMirror->setText(tr("Mirror")); indexMirror = 0; }

                 if(utils_cfg_cmp_item(DeviceCfg.camera_flip03, "UP")   == 0) { buttonFlip->setText(tr("Up"));   indexFlip = 1; }
            else if(utils_cfg_cmp_item(DeviceCfg.camera_flip03, "DOWN") == 0) { buttonFlip->setText(tr("Down")); indexFlip = 0; }

            break;
    }
}
void VideoInputDialog::onButtonMirror(void)
{
    int ch = 0;

    if(indexCamera <= 0) { ch = 3; }
    else                 { ch = indexCamera-1; }

    switch(indexMirror)
    {
        case 0:

            buttonMirror->setText(tr("Normal"));

            switch(ch)
            {
                case 0: { utils_cfg_cpy_item(DeviceCfg.camera_mirror00, "NORMAL"); break; }
                case 1: { utils_cfg_cpy_item(DeviceCfg.camera_mirror01, "NORMAL"); break; }
                case 2: { utils_cfg_cpy_item(DeviceCfg.camera_mirror02, "NORMAL"); break; }
                case 3: { utils_cfg_cpy_item(DeviceCfg.camera_mirror03, "NORMAL"); break; }
            }

            indexMirror = 1;

            break;

        case 1:

            buttonMirror->setText(tr("Mirror"));

            switch(ch)
            {
                case 0: { utils_cfg_cpy_item(DeviceCfg.camera_mirror00, "MIRROR"); break; }
                case 1: { utils_cfg_cpy_item(DeviceCfg.camera_mirror01, "MIRROR"); break; }
                case 2: { utils_cfg_cpy_item(DeviceCfg.camera_mirror02, "MIRROR"); break; }
                case 3: { utils_cfg_cpy_item(DeviceCfg.camera_mirror03, "MIRROR"); break; }
            }

            indexMirror = 0;

            break;
    }
}
void VideoInputDialog::onButtonFlip(void)
{
    int ch = 0;

    if(indexCamera <= 0) { ch = 3; }
    else                 { ch = indexCamera-1; }

    switch(indexFlip)
    {
        case 0:

            buttonFlip->setText(tr("Up"));

            switch(ch)
            {
                case 0: { utils_cfg_cpy_item(DeviceCfg.camera_flip00, "UP"); break; }
                case 1: { utils_cfg_cpy_item(DeviceCfg.camera_flip01, "UP"); break; }
                case 2: { utils_cfg_cpy_item(DeviceCfg.camera_flip02, "UP"); break; }
                case 3: { utils_cfg_cpy_item(DeviceCfg.camera_flip03, "UP"); break; }
            }

            indexFlip = 1;

            break;
        case 1:

            buttonFlip->setText(tr("Down"));

            switch(ch)
            {
                case 0: { utils_cfg_cpy_item(DeviceCfg.camera_flip00, "DOWN"); break; }
                case 1: { utils_cfg_cpy_item(DeviceCfg.camera_flip01, "DOWN"); break; }
                case 2: { utils_cfg_cpy_item(DeviceCfg.camera_flip02, "DOWN"); break; }
                case 3: { utils_cfg_cpy_item(DeviceCfg.camera_flip03, "DOWN"); break; }
            }

            indexFlip = 0;

            break;
    }
}
void VideoInputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonCamera->hasFocus())        { buttonSave->setFocus();      }
            else if(buttonSave->hasFocus())          { buttonCamera->setFocus();    }
            else if(buttonMirror->hasFocus())        { buttonClose->setFocus();     }
            else if(buttonFlip->hasFocus())          { buttonMirror->setFocus();    }
            else if(buttonClose->hasFocus())         { buttonFlip->setFocus();      }

            return;

        case Qt::Key_Down:

                 if(buttonCamera->hasFocus())        { buttonSave->setFocus();      }
            else if(buttonSave->hasFocus())          { buttonCamera->setFocus();    }
            else if(buttonMirror->hasFocus())        { buttonFlip->setFocus();      }
            else if(buttonFlip->hasFocus())          { buttonClose->setFocus();     }
            else if(buttonClose->hasFocus())         { buttonMirror->setFocus();    }

            return;

        case Qt::Key_Left:

                 if(buttonCamera->hasFocus())        { buttonMirror->setFocus();    }
            else if(buttonMirror->hasFocus())        { buttonCamera->setFocus();    }
            else if(buttonSave->hasFocus())          { buttonClose->setFocus();     }
            else if(buttonClose->hasFocus())         { buttonSave->setFocus();      }

            return;

        case Qt::Key_Right:

                 if(buttonCamera->hasFocus())        { buttonMirror->setFocus();    }
            else if(buttonMirror->hasFocus())        { buttonCamera->setFocus();    }
            else if(buttonSave->hasFocus())          { buttonClose->setFocus();     }
            else if(buttonClose->hasFocus())         { buttonSave->setFocus();      }

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
void VideoInputDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
