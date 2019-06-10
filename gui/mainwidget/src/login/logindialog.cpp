#include <QtGui>
#include "logindialog.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "main/mainglobal.h"
#include "aifrecord.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::LoginDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        buttonCancel = ui720.buttonCancel;
        buttonEdit = ui720.buttonEdit;
        buttonOk = ui720.buttonOk;
        lineEditPassword = ui720.lineEditPassword;
        labelPassword = ui720.labelPassword;

        labelPassword->setStyleSheet("font:48px;color:white;padding-left:10px;");

        //yjsin [18/01/05] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            labelPassword->setStyleSheet("font:45px;color:white;padding-left:5px;");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            labelPassword->setStyleSheet("font:45px;color:white;padding-left:5px;");
        }
    }
    else
    {
        Ui::LoginDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        buttonCancel = ui1080.buttonCancel;
        buttonEdit = ui1080.buttonEdit;
        buttonOk = ui1080.buttonOk;
        lineEditPassword = ui1080.lineEditPassword;
        labelPassword = ui1080.labelPassword;

        labelPassword->setStyleSheet("font:70px;color:white;padding-left:20px");

        //yjsin [18/02/21] if text is long, change font size
        if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            labelPassword->setStyleSheet("font:65px;color:white;padding-left:20px");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            labelPassword->setStyleSheet("font:65px;color:white;padding-left:20px");
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    setAutoFillBackground(true);

    keyboardDialog = NULL;

    connect(buttonEdit, SIGNAL(clicked()),  this, SLOT(showKeyboard()));
    connect(buttonOk,  SIGNAL(clicked()), this, SLOT(checkPassword()));
    connect(buttonCancel,  SIGNAL(clicked()), this, SLOT(reject()));

    buttonOk->setText(tr("Ok"));
    buttonCancel->setText(tr("Cancel"));

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
    buttonOk->setFocusPolicy(Qt::StrongFocus);
    buttonOk->setFocus();
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
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Incorrect Password");
        labelPassword->setText(tr("Incorrect Password.\nPlease try again."));
        this->lineEditPassword->setText("");
        buttonEdit->setFocus();
    }
    else
    {
        QDialog::accept();
    }
}
