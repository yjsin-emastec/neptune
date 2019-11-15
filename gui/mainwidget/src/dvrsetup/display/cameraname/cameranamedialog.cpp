#include <QtGui>
#include "cameranamedialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"

#if defined(HI3521)
CameraNameDialog::CameraNameDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::CameraNameDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        labelCameraName[0] = ui720.labelCameraName1;
        labelCameraName[1] = ui720.labelCameraName2;
        labelCameraName[2] = ui720.labelCameraName3;
        labelCameraName[3] = ui720.labelCameraName4;

        lineEditName[0] = ui720.lineEditName1;
        lineEditName[1] = ui720.lineEditName2;
        lineEditName[2] = ui720.lineEditName3;
        lineEditName[3] = ui720.lineEditName4;

        buttonVirtualKeyboard[0] = ui720.buttonVirtualKeyboard1;
        buttonVirtualKeyboard[1] = ui720.buttonVirtualKeyboard2;
        buttonVirtualKeyboard[2] = ui720.buttonVirtualKeyboard3;
        buttonVirtualKeyboard[3] = ui720.buttonVirtualKeyboard4;

        buttonSave  = ui720.buttonSave;
        buttonClose = ui720.buttonClose;

        for(int i=0; i<NUMOFCH; i++)
        {
            labelCameraName[i]->setStyleSheet("font:48px;");
            lineEditName[i]->setStyleSheet("font:48px;");
        }
    }
    else
    {
        Ui::CameraNameDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        labelCameraName[0] = ui1080.labelCameraName1;
        labelCameraName[1] = ui1080.labelCameraName2;
        labelCameraName[2] = ui1080.labelCameraName3;
        labelCameraName[3] = ui1080.labelCameraName4;

        lineEditName[0] = ui1080.lineEditName1;
        lineEditName[1] = ui1080.lineEditName2;
        lineEditName[2] = ui1080.lineEditName3;
        lineEditName[3] = ui1080.lineEditName4;

        buttonVirtualKeyboard[0] = ui1080.buttonVirtualKeyboard1;
        buttonVirtualKeyboard[1] = ui1080.buttonVirtualKeyboard2;
        buttonVirtualKeyboard[2] = ui1080.buttonVirtualKeyboard3;
        buttonVirtualKeyboard[3] = ui1080.buttonVirtualKeyboard4;

        buttonSave  = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;

        for(int i=0; i<NUMOFCH; i++)
        {
            labelCameraName[i]->setStyleSheet("font:60px;");
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonVirtualKeyboard[0]->setFocus();
    keyboard = NULL;

    connect(buttonVirtualKeyboard[0], SIGNAL(released()), this, SLOT(onCameraName1()));
    connect(buttonVirtualKeyboard[1], SIGNAL(released()), this, SLOT(onCameraName2()));
    connect(buttonVirtualKeyboard[2], SIGNAL(released()), this, SLOT(onCameraName3()));
    connect(buttonVirtualKeyboard[3], SIGNAL(released()), this, SLOT(onCameraName4()));

    connect(buttonSave,               SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,              SIGNAL(released()), this, SLOT(reject()));
}

#elif defined(HI3531D)
CameraNameDialog::CameraNameDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::CameraNameDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        labelCameraName[0] = ui720.labelCameraName1;
        labelCameraName[1] = ui720.labelCameraName2;
        labelCameraName[2] = ui720.labelCameraName3;
        labelCameraName[3] = ui720.labelCameraName4;
        labelCameraName[4] = ui720.labelCameraName5;
        labelCameraName[5] = ui720.labelCameraName6;
        labelCameraName[6] = ui720.labelCameraName7;
        labelCameraName[7] = ui720.labelCameraName8;

        lineEditName[0] = ui720.lineEditName1;
        lineEditName[1] = ui720.lineEditName2;
        lineEditName[2] = ui720.lineEditName3;
        lineEditName[3] = ui720.lineEditName4;
        lineEditName[4] = ui720.lineEditName5;
        lineEditName[5] = ui720.lineEditName6;
        lineEditName[6] = ui720.lineEditName7;
        lineEditName[7] = ui720.lineEditName8;

        buttonVirtualKeyboard[0] = ui720.buttonVirtualKeyboard1;
        buttonVirtualKeyboard[1] = ui720.buttonVirtualKeyboard2;
        buttonVirtualKeyboard[2] = ui720.buttonVirtualKeyboard3;
        buttonVirtualKeyboard[3] = ui720.buttonVirtualKeyboard4;
        buttonVirtualKeyboard[4] = ui720.buttonVirtualKeyboard5;
        buttonVirtualKeyboard[5] = ui720.buttonVirtualKeyboard6;
        buttonVirtualKeyboard[6] = ui720.buttonVirtualKeyboard7;
        buttonVirtualKeyboard[7] = ui720.buttonVirtualKeyboard8;

        buttonSave  = ui720.buttonSave;
        buttonClose = ui720.buttonClose;

        for(int i=0; i<NUMOFCH; i++)
        {
            labelCameraName[i]->setStyleSheet("font:40px;");
            lineEditName[i]->setStyleSheet("font:45px;");
        }
    }
    else
    {
        Ui::CameraNameDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        labelCameraName[0] = ui1080.labelCameraName1;
        labelCameraName[1] = ui1080.labelCameraName2;
        labelCameraName[2] = ui1080.labelCameraName3;
        labelCameraName[3] = ui1080.labelCameraName4;
        labelCameraName[4] = ui1080.labelCameraName5;
        labelCameraName[5] = ui1080.labelCameraName6;
        labelCameraName[6] = ui1080.labelCameraName7;
        labelCameraName[7] = ui1080.labelCameraName8;

        lineEditName[0] = ui1080.lineEditName1;
        lineEditName[1] = ui1080.lineEditName2;
        lineEditName[2] = ui1080.lineEditName3;
        lineEditName[3] = ui1080.lineEditName4;
        lineEditName[4] = ui1080.lineEditName5;
        lineEditName[5] = ui1080.lineEditName6;
        lineEditName[6] = ui1080.lineEditName7;
        lineEditName[7] = ui1080.lineEditName8;

        buttonVirtualKeyboard[0] = ui1080.buttonVirtualKeyboard1;
        buttonVirtualKeyboard[1] = ui1080.buttonVirtualKeyboard2;
        buttonVirtualKeyboard[2] = ui1080.buttonVirtualKeyboard3;
        buttonVirtualKeyboard[3] = ui1080.buttonVirtualKeyboard4;
        buttonVirtualKeyboard[4] = ui1080.buttonVirtualKeyboard5;
        buttonVirtualKeyboard[5] = ui1080.buttonVirtualKeyboard6;
        buttonVirtualKeyboard[6] = ui1080.buttonVirtualKeyboard7;
        buttonVirtualKeyboard[7] = ui1080.buttonVirtualKeyboard8;

        buttonSave  = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;

        for(int i=0; i<NUMOFCH; i++)
        {
            labelCameraName[i]->setStyleSheet("font:60px;");
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonVirtualKeyboard[0]->setFocus();
    keyboard = NULL;

    connect(buttonVirtualKeyboard[0], SIGNAL(released()), this, SLOT(onCameraName1()));
    connect(buttonVirtualKeyboard[1], SIGNAL(released()), this, SLOT(onCameraName2()));
    connect(buttonVirtualKeyboard[2], SIGNAL(released()), this, SLOT(onCameraName3()));
    connect(buttonVirtualKeyboard[3], SIGNAL(released()), this, SLOT(onCameraName4()));
    connect(buttonVirtualKeyboard[4], SIGNAL(released()), this, SLOT(onCameraName5()));
    connect(buttonVirtualKeyboard[5], SIGNAL(released()), this, SLOT(onCameraName6()));
    connect(buttonVirtualKeyboard[6], SIGNAL(released()), this, SLOT(onCameraName7()));
    connect(buttonVirtualKeyboard[7], SIGNAL(released()), this, SLOT(onCameraName8()));
    connect(buttonSave,               SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,              SIGNAL(released()), this, SLOT(reject()));
}
#endif

CameraNameDialog::~CameraNameDialog()
{
}
void CameraNameDialog::initCameraNameConfig(void)
{
	int ch = 0;
	QString str;
	QByteArray text;

    for(int i=0; i<NUMOFCH; i++)
    {
        text = QByteArray::fromHex((char *)DisplayCfg.channel_name[ch++]);
        str = QString::fromUtf8(text.data());
        lineEditName[i]->setText(str);
    }
}
void CameraNameDialog::onCameraName(int ch)
{
    int maxLen = 10;
    QString str;

    if(!keyboard)
    {
        keyboard = new UiKeyboardDialog(this);
    }

    keyboard->setKeyboadProperty(str, lineEditName[ch]->text(), false, maxLen);
    keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

    if(keyboard->exec())
    {
        QString str = keyboard->text;
        lineEditName[ch]->setText(str.trimmed());

        printf("%s \n", qPrintable(str));
        QByteArray text = str.trimmed().toUtf8().toHex();
        memset(DisplayCfg.channel_name[ch], 0, sizeof(DisplayCfg.channel_name[ch]));
        memcpy(DisplayCfg.channel_name[ch], str.trimmed().toUtf8().toHex(), text.size());
    }

    delete keyboard;
    keyboard = NULL;
}
void CameraNameDialog::onCameraName1() { onCameraName(0); }
void CameraNameDialog::onCameraName2() { onCameraName(1); }
void CameraNameDialog::onCameraName3() { onCameraName(2); }
void CameraNameDialog::onCameraName4() { onCameraName(3); }
void CameraNameDialog::onCameraName5() { onCameraName(4); }
void CameraNameDialog::onCameraName6() { onCameraName(5); }
void CameraNameDialog::onCameraName7() { onCameraName(6); }
void CameraNameDialog::onCameraName8() { onCameraName(7); }

#if defined(HI3521)
void CameraNameDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonVirtualKeyboard[0]->hasFocus())   { buttonClose->setFocus();              }
            else if(buttonVirtualKeyboard[1]->hasFocus())   { buttonVirtualKeyboard[0]->setFocus(); }
            else if(buttonVirtualKeyboard[2]->hasFocus())   { buttonVirtualKeyboard[1]->setFocus(); }
            else if(buttonVirtualKeyboard[3]->hasFocus())   { buttonVirtualKeyboard[2]->setFocus(); }
            else if(buttonSave ->hasFocus())                { buttonVirtualKeyboard[3]->setFocus(); }
            else if(buttonClose->hasFocus())                { buttonVirtualKeyboard[3]->setFocus(); }

            return;

        case Qt::Key_Down:

                if(buttonVirtualKeyboard[0]->hasFocus())    { buttonVirtualKeyboard[1]->setFocus(); }
           else if(buttonVirtualKeyboard[1]->hasFocus())    { buttonVirtualKeyboard[2]->setFocus(); }
           else if(buttonVirtualKeyboard[2]->hasFocus())    { buttonVirtualKeyboard[3]->setFocus(); }
           else if(buttonVirtualKeyboard[3]->hasFocus())    { buttonClose->setFocus(); }
           else if(buttonSave ->hasFocus())                 { buttonVirtualKeyboard[0]->setFocus(); }
           else if(buttonClose->hasFocus())                 { buttonVirtualKeyboard[0]->setFocus(); }

            return;

        case Qt::Key_Left:

                 if(buttonSave ->hasFocus())                { buttonClose->setFocus();              }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();               }

            return;

        case Qt::Key_Right:

                 if(buttonSave ->hasFocus())                { buttonClose->setFocus();              }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();               }

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

#elif defined(HI3531D)
void CameraNameDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonVirtualKeyboard[0]->hasFocus())   { buttonClose->setFocus();              }
            else if(buttonVirtualKeyboard[1]->hasFocus())   { buttonVirtualKeyboard[0]->setFocus(); }
            else if(buttonVirtualKeyboard[2]->hasFocus())   { buttonVirtualKeyboard[1]->setFocus(); }
            else if(buttonVirtualKeyboard[3]->hasFocus())   { buttonVirtualKeyboard[2]->setFocus(); }
            else if(buttonVirtualKeyboard[4]->hasFocus())   { buttonVirtualKeyboard[3]->setFocus(); }
            else if(buttonVirtualKeyboard[5]->hasFocus())   { buttonVirtualKeyboard[4]->setFocus(); }
            else if(buttonVirtualKeyboard[6]->hasFocus())   { buttonVirtualKeyboard[5]->setFocus(); }
            else if(buttonVirtualKeyboard[7]->hasFocus())   { buttonVirtualKeyboard[6]->setFocus(); }
            else if(buttonSave ->hasFocus())                { buttonVirtualKeyboard[7]->setFocus(); }
            else if(buttonClose->hasFocus())                { buttonVirtualKeyboard[7]->setFocus(); }

            return;

        case Qt::Key_Down:

                if(buttonVirtualKeyboard[0]->hasFocus())    { buttonVirtualKeyboard[1]->setFocus(); }
           else if(buttonVirtualKeyboard[1]->hasFocus())    { buttonVirtualKeyboard[2]->setFocus(); }
           else if(buttonVirtualKeyboard[2]->hasFocus())    { buttonVirtualKeyboard[3]->setFocus(); }
           else if(buttonVirtualKeyboard[3]->hasFocus())    { buttonVirtualKeyboard[4]->setFocus(); }
           else if(buttonVirtualKeyboard[4]->hasFocus())    { buttonVirtualKeyboard[5]->setFocus(); }
           else if(buttonVirtualKeyboard[5]->hasFocus())    { buttonVirtualKeyboard[6]->setFocus(); }
           else if(buttonVirtualKeyboard[6]->hasFocus())    { buttonVirtualKeyboard[7]->setFocus(); }
           else if(buttonVirtualKeyboard[7]->hasFocus())    { buttonClose->setFocus();              }
           else if(buttonSave ->hasFocus())                 { buttonVirtualKeyboard[0]->setFocus(); }
           else if(buttonClose->hasFocus())                 { buttonVirtualKeyboard[0]->setFocus(); }

            return;

        case Qt::Key_Left:

                 if(buttonSave ->hasFocus())                { buttonClose->setFocus();              }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();               }

            return;

        case Qt::Key_Right:

                 if(buttonSave ->hasFocus())                { buttonClose->setFocus();              }
            else if(buttonClose->hasFocus())                { buttonSave->setFocus();               }

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

#endif
