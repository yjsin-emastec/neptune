#include <QtGui>
#include "cameranamedialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"

CameraNameDialog::CameraNameDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::CameraNameDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelCameraName1 = ui720.labelCameraName1;
        labelCameraName2 = ui720.labelCameraName2;
        labelCameraName3 = ui720.labelCameraName3;
        labelCameraName4 = ui720.labelCameraName4;
        lineEditName1 = ui720.lineEditName1;
        lineEditName2 = ui720.lineEditName2;
        lineEditName3 = ui720.lineEditName3;
        lineEditName4 = ui720.lineEditName4;
        buttonVirtualKeyboard1 = ui720.buttonVirtualKeyboard1;
        buttonVirtualKeyboard2 = ui720.buttonVirtualKeyboard2;
        buttonVirtualKeyboard3 = ui720.buttonVirtualKeyboard3;
        buttonVirtualKeyboard4 = ui720.buttonVirtualKeyboard4;
        buttonSave = ui720.buttonSave;
        buttonClose = ui720.buttonClose;

        labelCameraName1->setStyleSheet("font:48px;color:white");
        labelCameraName2->setStyleSheet("font:48px;color:white");
        labelCameraName3->setStyleSheet("font:48px;color:white");
        labelCameraName4->setStyleSheet("font:48px;color:white");
    }
    else
    {
        Ui::CameraNameDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelCameraName1 = ui1080.labelCameraName1;
        labelCameraName2 = ui1080.labelCameraName2;
        labelCameraName3 = ui1080.labelCameraName3;
        labelCameraName4 = ui1080.labelCameraName4;
        lineEditName1 = ui1080.lineEditName1;
        lineEditName2 = ui1080.lineEditName2;
        lineEditName3 = ui1080.lineEditName3;
        lineEditName4 = ui1080.lineEditName4;
        buttonVirtualKeyboard1 = ui1080.buttonVirtualKeyboard1;
        buttonVirtualKeyboard2 = ui1080.buttonVirtualKeyboard2;
        buttonVirtualKeyboard3 = ui1080.buttonVirtualKeyboard3;
        buttonVirtualKeyboard4 = ui1080.buttonVirtualKeyboard4;
        buttonSave = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;

        labelCameraName1->setStyleSheet("font:65px;color:white");
        labelCameraName2->setStyleSheet("font:65px;color:white");
        labelCameraName3->setStyleSheet("font:65px;color:white");
        labelCameraName4->setStyleSheet("font:65px;color:white");
    }

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	setPalette(QPalette(QColor(255, 128, 64)));
	frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
	buttonVirtualKeyboard1->setFocus();

	keyboard = NULL;

    connect(buttonVirtualKeyboard1, SIGNAL(released()), this, SLOT(onCameraName1()));
    connect(buttonVirtualKeyboard2, SIGNAL(released()), this, SLOT(onCameraName2()));
    connect(buttonVirtualKeyboard3, SIGNAL(released()), this, SLOT(onCameraName3()));
    connect(buttonVirtualKeyboard4, SIGNAL(released()), this, SLOT(onCameraName4()));
    connect(buttonSave,             SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,            SIGNAL(released()), this, SLOT(reject()));
}
CameraNameDialog::~CameraNameDialog()
{
}
void CameraNameDialog::initCameraNameConfig(void)
{
	int ch = 0;
	QString str;
	QByteArray text;

	text = QByteArray::fromHex((char *)DisplayCfg.channel_name[ch++]);
	str = QString::fromUtf8(text.data());
	lineEditName1->setText(str);

	text = QByteArray::fromHex((char *)DisplayCfg.channel_name[ch++]);
	str = QString::fromUtf8(text.data());
	lineEditName2->setText(str);

	text = QByteArray::fromHex((char *)DisplayCfg.channel_name[ch++]);
	str = QString::fromUtf8(text.data());
	lineEditName3->setText(str);

	text = QByteArray::fromHex((char *)DisplayCfg.channel_name[ch++]);
	str = QString::fromUtf8(text.data());
	lineEditName4->setText(str);
}
void CameraNameDialog::onCameraName1()
{
	int maxLen = 10;
	QString str;

	if(!keyboard)
	{
		keyboard = new UiKeyboardDialog(this);
	}

	keyboard->setKeyboadProperty(str, lineEditName1->text(), false, maxLen);
	keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

	qDebug("keyboard size : %d, %d", keyboard->width(), keyboard->height());

	if(keyboard->exec())
	{
		QString str = keyboard->text;
		lineEditName1->setText(str.trimmed());

		printf("%s \n", qPrintable(str));
        QByteArray text = str.trimmed().toUtf8().toHex();
		memset(DisplayCfg.channel_name[0], 0, sizeof(DisplayCfg.channel_name[0]));
		memcpy(DisplayCfg.channel_name[0], str.trimmed().toUtf8().toHex(), text.size());
	}

	delete keyboard;
	keyboard = NULL;
}
void CameraNameDialog::onCameraName2()
{
	int maxLen = 10;
	QString str;

	if(!keyboard)
	{
		keyboard = new UiKeyboardDialog(this);
	}

	keyboard->setKeyboadProperty(str, lineEditName2->text(), false, maxLen);
	keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

	if(keyboard->exec())
	{
		QString str = keyboard->text;
		lineEditName2->setText(str.trimmed());

		printf("%s \n", qPrintable(str));
        QByteArray text = str.trimmed().toUtf8().toHex();
		memset(DisplayCfg.channel_name[1], 0, sizeof(DisplayCfg.channel_name[1]));
		memcpy(DisplayCfg.channel_name[1], str.trimmed().toUtf8().toHex(), text.size());
	}

	delete keyboard;
	keyboard = NULL;
}
void CameraNameDialog::onCameraName3()
{
	int maxLen = 10;
	QString str;

	if(!keyboard)
	{
		keyboard = new UiKeyboardDialog(this);
	}

	keyboard->setKeyboadProperty(str, lineEditName3->text(), false, maxLen);
	keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

	if(keyboard->exec())
	{
		QString str = keyboard->text;
		lineEditName3->setText(str.trimmed());

		printf("%s \n", qPrintable(str));
        QByteArray text = str.trimmed().toUtf8().toHex();
		memset(DisplayCfg.channel_name[2], 0, sizeof(DisplayCfg.channel_name[2]));
		memcpy(DisplayCfg.channel_name[2], str.trimmed().toUtf8().toHex(), text.size());
	}

	delete keyboard;
	keyboard = NULL;
}
void CameraNameDialog::onCameraName4()
{
	int maxLen = 10;
	QString str;

	if(!keyboard)
	{
		keyboard = new UiKeyboardDialog(this);
	}

	keyboard->setKeyboadProperty(str, lineEditName4->text(), false, maxLen);
	keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

	if(keyboard->exec())
	{
		QString str = keyboard->text;
		lineEditName4->setText(str.trimmed());

		printf("%s \n", qPrintable(str));
        QByteArray text = str.trimmed().toUtf8().toHex();
		memset(DisplayCfg.channel_name[3], 0, sizeof(DisplayCfg.channel_name[3]));
		memcpy(DisplayCfg.channel_name[3], str.trimmed().toUtf8().toHex(), text.size());
	}

	delete keyboard;
	keyboard = NULL;
}
void CameraNameDialog::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
		case Qt::Key_Up:

			     if(buttonVirtualKeyboard1->hasFocus())     { buttonClose->setFocus();                }
			else if(buttonVirtualKeyboard2->hasFocus())     { buttonVirtualKeyboard1->setFocus();     }
			else if(buttonVirtualKeyboard3->hasFocus())     { buttonVirtualKeyboard2->setFocus();     }
			else if(buttonVirtualKeyboard4->hasFocus())     { buttonVirtualKeyboard3->setFocus();     }
			else if(buttonClose->hasFocus())                { buttonVirtualKeyboard4->setFocus();     }

			return;

		case Qt::Key_Down:

			     if(buttonVirtualKeyboard1->hasFocus())     { buttonVirtualKeyboard2->setFocus();     }
			else if(buttonVirtualKeyboard2->hasFocus())     { buttonVirtualKeyboard3->setFocus();     }
			else if(buttonVirtualKeyboard3->hasFocus())     { buttonVirtualKeyboard4->setFocus();     }
			else if(buttonVirtualKeyboard4->hasFocus())     { buttonClose->setFocus();                }
			else if(buttonClose->hasFocus())                { buttonVirtualKeyboard1->setFocus();     }

			return;

		case Qt::Key_Left:

			     if(buttonSave->hasFocus())                 { buttonClose->setFocus();                }
			else if(buttonClose->hasFocus())                { buttonSave->setFocus();                 }

			return;

		case Qt::Key_Right:

			     if(buttonSave->hasFocus())                 { buttonClose->setFocus();                }
			else if(buttonClose->hasFocus())                { buttonSave->setFocus();                 }

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
void CameraNameDialog::keyReleaseEvent(QKeyEvent *event)
{
	return;
}
