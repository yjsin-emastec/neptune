#include <QtGui>
#include "logindialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"
#include "aifrecord.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    setAutoFillBackground(true);

    keyboardDialog = NULL;

    labelPassword->setStyleSheet("font:48px;color:white");
    lineEditPassword->setAlignment(Qt::AlignCenter);

    connect(buttonEdit, SIGNAL(clicked()),  this, SLOT(showKeyboard()));
    connect(buttonBox,  SIGNAL(accepted()), this, SLOT(checkPassword()));
    connect(buttonBox,  SIGNAL(rejected()), this, SLOT(reject()));

    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    buttonBox->button(QDialogButtonBox::Ok)->setMinimumSize(200,100);
    buttonBox->button(QDialogButtonBox::Cancel)->setMinimumSize(200,100);

    if(parent->isLeftToRight() && isRightToLeft())
    {
        setLayoutDirection(Qt::LeftToRight);
    }
    else if(parent->isRightToLeft() && isLeftToRight())
    {
        setLayoutDirection(Qt::RightToLeft);
    }

    selUserId = 0;

    this->lineEditPassword->setMaxLength(8);
}
LoginDialog::~LoginDialog()
{
    if(keyboardDialog)
    {
        delete keyboardDialog;
    }
}
void LoginDialog::updateConfig(int checkMode)
{
    aif_system_get_property(&SystemCfg);

    buttonEdit->setFocus();
    PasswordString = "";
    lineEditPassword->setText("");
    labelPassword->clear();
    labelPassword->setText(tr("Please input a password."));
}
void LoginDialog::showKeyboard()
{
    int maxLen = 8;
    labelPassword->setText(tr("Please input a password."));
    lineEditPassword->setText("");

    if(!keyboardDialog)
    {
        keyboardDialog = new UiKeyboardDialog(this);
    }

    keyboardDialog->setKeyboadProperty(NULL, NULL, true, maxLen);
    keyboardDialog->move((mainWidth - keyboardDialog->size().width()) / 2, (mainHeight - keyboardDialog->size().height()) / 2);

    if(keyboardDialog->exec())
    {
        QString str = keyboardDialog->text;
        lineEditPassword->setText(str);
    }

    delete keyboardDialog;
    keyboardDialog = NULL;
    buttonBox->button(QDialogButtonBox::Ok)->setFocus();
}
void LoginDialog::checkPassword()
{
    int ret = 1, ret1 = 0;
    char tmp1[32], tmp2[32];

    PasswordString = lineEditPassword->text();

    memset(tmp1, 0, 32);
    memcpy(tmp1, PasswordString.toStdString().c_str(), PasswordString.size());
    QByteArray text = QByteArray::fromHex(SystemCfg.admin_passwd);
    QString str = QString::fromUtf8(text.data());
    memset(tmp2, 0, 32);
    memcpy(tmp2, str.toStdString().c_str(), str.size());

    if(strcmp(tmp2, tmp1) == 0)
    {
        ret = 0;
    }
    else
    {
        ret1 = appmgr_password_check(tmp1, 1);
        qDebug("Check master password -- %d", ret1);

        if(ret1 == 1) // Goto Test Mode
        {
            utils_system("fw_setenv bootmode test");
            utils_system("miscflash 1 2 0 NULL");

            for(int ch = 0; ch < devInfo.videoNum; ch++)
            {
                stop_all_record(ch);
            }

            sync(); sync(); sync();
            sleep(1);

            appmgr_reboot_system(SYSTEM_TEST_MODE);

            sleep(3);
        }
        else if(ret1 == 2) // Master Password
        {
            utils_cfg_cpy_item(SystemCfg.admin_passwd, "");
            aif_system_set_property(&SystemCfg);
            ret = 0;
        }
        else if(ret1 == 3) // Display OSD VIS
        {
            utils_cfg_cpy_item(DisplayCfg.osd_camera, "ON");
            aif_display_set_property(&DisplayCfg);
            QDialog::reject();
        }
        else if(ret1 == 4) // Not Display OSD VIS
        {
            utils_cfg_cpy_item(DisplayCfg.osd_camera, "OFF");
            aif_display_set_property(&DisplayCfg);
            QDialog::reject();
        }
    }

    if(ret)
    {
        labelPassword->setText(tr("Incorrect Password.\nPlease try again."));
        this->lineEditPassword->setText("");
        buttonEdit->setFocus();
    }
    else
    {
        QDialog::accept();
    }
}
