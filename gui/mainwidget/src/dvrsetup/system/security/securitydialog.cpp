#include <QtGui>
#include "securitydialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"

SecurityDialog::SecurityDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonNewPassword->setFocus();

    labelSecurity->setStyleSheet("font:50px;background-color:rgb(50,57,83);color:white");
    labelNewPassword->setStyleSheet("font:40px;color:white");
    labelConfirmPassword->setStyleSheet("font:40px;color:white");
    labelSystemLock->setStyleSheet("font:40px;color:white");
    labelNewPassword->setAlignment(Qt::AlignCenter);
    labelConfirmPassword->setAlignment(Qt::AlignCenter);
    labelSystemLock->setAlignment(Qt::AlignCenter);
    lineEditNewPassword->setAlignment(Qt::AlignCenter);
    lineEditConfirmPassword->setAlignment(Qt::AlignCenter);

    lineEditNewPassword->setEchoMode(QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    keyboard = NULL;

    connect(buttonNewPassword, SIGNAL(released()), this, SLOT(onButtonNewPassword()));
    connect(buttonConfirmPassword, SIGNAL(released()), this, SLOT(onButtonConfirmPassword()));
    connect(buttonSystemLock, SIGNAL(released()), this, SLOT(onButtonSystemLock()));

    connect(buttonSave, SIGNAL(released()), this, SLOT(onButtonSave()));
    connect(buttonClose, SIGNAL(released()), this, SLOT(reject()));
}
SecurityDialog::~SecurityDialog()
{
}
void SecurityDialog::initSecurityConfig(void)
{
    lineEditNewPassword->clear();
    lineEditConfirmPassword->clear();
    isInputNewPassword = 0;
    isInputConfirmPassword = 0;
    memset(newPassword, 0, sizeof(newPassword));
    memset(confirmPassword, 0, sizeof(confirmPassword));

    if(utils_cfg_cmp_item(SystemCfg.system_lock, "YES") == 0)
    {
        buttonSystemLock->setText(tr("On"));
        indexSystemLock = 1;
    }
    else if(utils_cfg_cmp_item(SystemCfg.system_lock, "NO") == 0)
    {
        buttonSystemLock->setText(tr("Off"));
        indexSystemLock = 2;
    }
}
void SecurityDialog::onButtonNewPassword(void)
{
    int maxLen = 8;
    QString str;

    if(!keyboard)
    {
        keyboard = new UiKeyboardDialog(this);
    }

    keyboard->setKeyboadProperty(str, lineEditNewPassword->text(), false, maxLen);
    keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

    qDebug("keyboard size : %d, %d", keyboard->width(), keyboard->height());

    if(keyboard->exec())
    {
        QString str = keyboard->text;
        lineEditNewPassword->setText(str);

        printf("%s \n", qPrintable(str));
        memset(newPassword, 0, sizeof(newPassword));
        memcpy(newPassword, str.toStdString().c_str(), str.size());
        isInputNewPassword = 1;
    }

    delete keyboard;
    keyboard = NULL;
}
void SecurityDialog::onButtonConfirmPassword(void)
{
    int maxLen = 8;
    QString str;

    if(!keyboard)
    {
        keyboard = new UiKeyboardDialog(this);
    }

    keyboard->setKeyboadProperty(str, lineEditConfirmPassword->text(), false, maxLen);
    keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

    qDebug("keyboard size : %d, %d", keyboard->width(), keyboard->height());

    if(keyboard->exec())
    {
        QString str = keyboard->text;
        lineEditConfirmPassword->setText(str);

        labelSecurity->setText(tr("Please input new password."));
        printf("%s \n", qPrintable(str));
        memset(confirmPassword, 0, sizeof(confirmPassword));
        memcpy(confirmPassword, str.toStdString().c_str(), str.size());
        isInputConfirmPassword = 1;
    }

    delete keyboard;
    keyboard = NULL;
}
void SecurityDialog::onButtonSystemLock()
{
    if(indexSystemLock >= 2)
    {
        indexSystemLock = 0;
    }

    switch(++indexSystemLock)
    {
        case 1:

            buttonSystemLock->setText(tr("On"));
            utils_cfg_cpy_item(SystemCfg.system_lock, "YES");

            break;

        case 2:

            buttonSystemLock->setText(tr("Off"));
            utils_cfg_cpy_item(SystemCfg.system_lock, "NO");

            break;
    }
}
void SecurityDialog::onButtonSave(void)
{
    if(isInputNewPassword && isInputConfirmPassword)
    {
        if(strcmp(newPassword, confirmPassword) != 0)
        {
            labelSecurity->setText(tr("Password did not match.\nPlease try again."));
            buttonConfirmPassword->setFocus();
            return;
        }

        QString str = lineEditConfirmPassword->text();
        QByteArray text = str.toUtf8().toHex();
        memset(SystemCfg.admin_passwd, 0, sizeof(SystemCfg.admin_passwd));
        memcpy(SystemCfg.admin_passwd, str.toUtf8().toHex(), text.size());
    }
    else if(isInputNewPassword)
    {
        labelSecurity->setText(tr("Password did not match.\nPlease try again."));
        buttonConfirmPassword->setFocus();
        return;
    }
    else if(isInputConfirmPassword)
    {
        labelSecurity->setText(tr("Password did not match.\nPlease try again."));
        buttonNewPassword->setFocus();
        return;
    }

    QDialog::accept();
}
void SecurityDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonNewPassword->hasFocus())            { buttonClose->setFocus();             }
            else if(buttonConfirmPassword->hasFocus())        { buttonNewPassword->setFocus();       }
            else if(buttonSystemLock->hasFocus())             { buttonConfirmPassword->setFocus();   }
            else if(buttonSave->hasFocus())                   { buttonSystemLock->setFocus();        }
            else if(buttonClose->hasFocus())                  { buttonSystemLock->setFocus();        }

            return;

        case Qt::Key_Down:

                 if(buttonNewPassword->hasFocus())            { buttonConfirmPassword->setFocus();   }
            else if(buttonConfirmPassword->hasFocus())        { buttonSystemLock->setFocus();        }
            else if(buttonSystemLock->hasFocus())             { buttonClose->setFocus();             }
            else if(buttonSave->hasFocus())                   { buttonNewPassword->setFocus();       }
            else if(buttonClose->hasFocus())                  { buttonNewPassword->setFocus();       }

            return;

        case Qt::Key_Left:

                 if(buttonSave->hasFocus())                   { buttonClose->setFocus();             }
            else if(buttonClose->hasFocus())                  { buttonSave->setFocus();              }

            return;

        case Qt::Key_Right:

                 if(buttonSave->hasFocus())                   { buttonClose->setFocus();             }
            else if(buttonClose->hasFocus())                  { buttonSave->setFocus();              }

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
void SecurityDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
