#include <QtGui>
#include "appupgradedialog.h"
#include "main/mainglobal.h"
#include "textmessagebox/textmessagedialog.h"
#include "utils.h"
#include "appmgr.h"
#include "Event.h"

AppUpgradeDialog::AppUpgradeDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::AppUpgradeDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelStatus = ui720.labelStatus;
        labelModelName = ui720.labelModelName;
        labelModelNameValue = ui720.labelModelNameValue;
        labelVersion = ui720.labelVersion;
        labelVersionValue = ui720.labelVersionValue;
        labelFileName = ui720.labelFileName;
        labelFileNameValue = ui720.labelFileNameValue;
        labelProgress = ui720.labelProgress;
        labelProgressValue = ui720.labelProgressValue;
        progressBar = ui720.progressBar;
        buttonFind = ui720.buttonFind;
        buttonUpgrade = ui720.buttonUpgrade;
        buttonClose = ui720.buttonClose;

        labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
        labelModelName->setStyleSheet("font:40px;color:white");
        labelModelName->setAlignment(Qt::AlignCenter);
        labelVersion->setStyleSheet("font:40px;color:white");
        labelVersion->setAlignment(Qt::AlignCenter);
        labelFileName->setStyleSheet("font:40px;color:white");
        labelFileName->setAlignment(Qt::AlignCenter);
        labelProgress->setStyleSheet("font:40px;color:white");
        labelProgress->setAlignment(Qt::AlignCenter);
        labelModelNameValue->setStyleSheet("font:40px;color:white;padding-left:5px;");
        labelVersionValue->setStyleSheet("font:40px;color:white;padding-left:5px;");
        labelFileNameValue->setStyleSheet("font:38px;color:white;padding-left:5px;");
        labelProgressValue->setStyleSheet("font:40px;color:white");

        //yjsin [17/09/13] if text is long, change font size and label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
        {
            buttonFind->setGeometry(345, 560, 250, 90);
            buttonUpgrade->setGeometry(605, 560, 350, 90);
            buttonUpgrade->setStyleSheet("font:45px");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonFind->setGeometry(335, 560, 250, 90);
            buttonUpgrade->setGeometry(595, 560, 360, 90);
            buttonUpgrade->setStyleSheet("font:45px");
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonFind->setGeometry(335, 560, 250, 90);
            buttonUpgrade->setGeometry(595, 560, 360, 90);
        }
    }
    else
    {
        Ui::AppUpgradeDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelStatus = ui1080.labelStatus;
        labelModelName = ui1080.labelModelName;
        labelModelNameValue = ui1080.labelModelNameValue;
        labelVersion = ui1080.labelVersion;
        labelVersionValue = ui1080.labelVersionValue;
        labelFileName = ui1080.labelFileName;
        labelFileNameValue = ui1080.labelFileNameValue;
        labelProgress = ui1080.labelProgress;
        labelProgressValue = ui1080.labelProgressValue;
        progressBar = ui1080.progressBar;
        buttonFind = ui1080.buttonFind;
        buttonUpgrade = ui1080.buttonUpgrade;
        buttonClose = ui1080.buttonClose;

        labelStatus->setStyleSheet("font:70px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
        labelModelName->setStyleSheet("font:55px;color:white");
        labelVersion->setStyleSheet("font:55px;color:white");
        labelFileName->setStyleSheet("font:55px;color:white");
        labelProgress->setStyleSheet("font:55px;color:white");
        labelModelNameValue->setStyleSheet("font:55px;color:white;padding-left:7px;");
        labelVersionValue->setStyleSheet("font:55px;color:white;padding-left:7px;");
        labelFileNameValue->setStyleSheet("font:53px;color:white;padding-left:7px;");
        labelProgressValue->setStyleSheet("font:55px;color:white");

        //yjsin [19/02/21] if text is long, change font size and label location and size
        if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
        {
            buttonFind->setGeometry(490, 860, 401, 131);
            buttonUpgrade->setGeometry(910, 860, 501, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonFind->setGeometry(480, 860, 401, 131);
            buttonUpgrade->setGeometry(900, 860, 511, 131);
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
        {
            buttonFind->setGeometry(490, 860, 401, 131);
            buttonUpgrade->setGeometry(910, 860, 501, 131);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    upgradeTimer = NULL;
    msgBox       = NULL;
    upgradeState = false;

    buttonFind->setFocus();

    connect(buttonFind,    SIGNAL(released()), this, SLOT(onButtonFind()));
    connect(buttonUpgrade, SIGNAL(released()), this, SLOT(onButtonUpgrade()));
    connect(buttonClose,   SIGNAL(released()), this, SLOT(reject()));
}
AppUpgradeDialog::~AppUpgradeDialog()
{
}
void AppUpgradeDialog::initAppUpgradeConfig(void)
{
    buttonFind->setFocus();

    buttonFind->setEnabled(false);
    buttonUpgrade->setEnabled(false);
    buttonClose->setEnabled(false);

    UpdateLabelStatus(1);

    labelModelNameValue->clear();
    labelVersionValue->clear();
    labelFileNameValue->clear();
    progressBar->setValue(0);
    upgradeState=false;

    QTimer::singleShot(2000, this, SLOT(initButton()));
}
void AppUpgradeDialog::initButton(void)
{
    char *cModelName = utils_get_model_name();
    labelModelNameValue->setText(cModelName);

    aif_system_get_status(&SystemCfgInfo);
    labelVersionValue->setText(SystemCfgInfo.sw_version);

    buttonFind->setEnabled(true);
    buttonClose->setEnabled(true);

    buttonFind->setFocus();

    UpdateLabelStatus(2);
}
void AppUpgradeDialog::UpdateLabelStatus(int message)
{
    switch(message)
    {
        case  1: { labelStatus->setText(tr("%1\n%2").arg(tr("After upgrading firmware,"), tr("System will restart.")));                        break; }
        case  2: { labelStatus->setText(tr("%1\n%2").arg(tr("Please insert a USB memory and then"), tr("click 'Find' button.")));              break; }
        case  3: { labelStatus->setText(tr("%1")    .arg(tr("Please insert a USB memory.")));                                                  break; }
        case  4: { labelStatus->setText(tr("%1")    .arg(tr("Please reinsert a USB memory.")));                                                break; }
        case  5: { labelStatus->setText(tr("%1\n%2").arg(tr("A file was found."), tr("Please select 'Upgrade' button.")));                     break; }
        case  6: { labelStatus->setText(tr("%1")    .arg(tr("Directory does not exist.")));                                                    break; }
        case  7: { labelStatus->setText(tr("%1")    .arg(tr("File does not exist.")));                                                         break; }
        case  8: { labelStatus->setText(tr("%1")    .arg(tr("File is invalid.")));                                                             break; }
        case  9: { labelStatus->setText(tr("%1")    .arg(tr("List overflowed.")));                                                             break; }
        case 10: { labelStatus->setText(tr("%1")    .arg(tr("Please do not remove USB memory.")));                                             break; }
        case 11: { labelStatus->setText(tr("%1\n%2").arg(tr("Please do not turn off system."), tr("System will restart after upgrading.")));   break; }
        case 12: { labelStatus->setText(tr("%1")    .arg(tr("UPGRADE SUCCESS")));                                                              break; }
        case 13: { labelStatus->setText(tr("%1")    .arg(tr("UPGRADE FAIL")));                                                                 break; }
    }
}
void AppUpgradeDialog::Delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void AppUpgradeDialog::onButtonFind(void)
{
    labelFileNameValue->clear();
    buttonFind->setEnabled(false);
    buttonUpgrade->setEnabled(false);
    buttonClose->setEnabled(false);
    progressBar->setValue(0);

    if(mainHeight == 720)
    {
        labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white;padding-left:15px;");
    }
    else
    {
        labelStatus->setStyleSheet("font:70px;background-color:rgb(50,57,83);color:white;padding-left:30px;");
    }
    labelStatus->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    (void)ButtonFind(1);
}
int AppUpgradeDialog::ButtonFind(int isUnMount)
{
    int  rv, ii = 0, cnt = 0;
    char tmp[256], buf[128];

    memset(fileName, 0, sizeof(fileName));

    rv = utils_appup_device_check();

    if(rv != 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade device check: fail");
        qDebug(" FW_UPGRADE_DEVICE_CHECK_FAIL !! \n");
        buttonFind->setEnabled(true);
        buttonFind->setFocus();
        buttonUpgrade->setEnabled(false);
        buttonClose->setEnabled(true);
        labelFileNameValue->clear();
        UpdateLabelStatus(3);
        return rv;
    }

    rv = utils_appup_device_mount();

    if(rv != 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade device mount: fail");
        qDebug(" FW_UPGRADE_DEVICE_MOUNT_FAIL !! \n");
        buttonFind->setEnabled(true);
        buttonFind->setFocus();
        buttonUpgrade->setEnabled(false);
        buttonClose->setEnabled(true);
        labelFileNameValue->clear();
        UpdateLabelStatus(4);
        return rv;
    }

    rv = utils_appup_file_check(fileName, 512);

    if(rv == 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade file check: success");

        while(fileName[ii])
        {
            if(fileName[ii] == '_')
            {
                cnt++;
            }

            if(cnt == 3)
            {
                memset(buf, 0, sizeof(buf));
                memcpy(buf, fileName, ii);
                ii++;
                memset(tmp, 0, sizeof(tmp));
                memcpy(tmp, &fileName[ii], strlen(&fileName[ii])-4);
                break;
            }

            ii++;
        }

        QString oem = QString("Upgrade OEM: %1").arg(QString::fromUtf8(buf));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, oem.toStdString().c_str());

        QString str = QString("Upgrade Ver: %1").arg(QString::fromUtf8(tmp));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());

        qDebug("[Check] FW_UPGRADE_FILE_CHECK_SUCCESS !!\n");
        UpdateLabelStatus(5);
        labelFileNameValue->setText(tr("%1").arg(fileName));

        if(isUnMount)
        {
            buttonFind->setEnabled(true);
            buttonUpgrade->setEnabled(true);
            buttonUpgrade->setFocus();
            buttonClose->setEnabled(true);
            sprintf(tmp, "echo %s > /tmp/fuFileName", fileName);
            utils_system(tmp);
        }
    }
    else if(rv == -1)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade file check fail: Folder");
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - FOLDER\n");
        UpdateLabelStatus(6);
    }
    else if(rv == -2)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade file check fail: File");
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - FILE\n");
        UpdateLabelStatus(7);
    }
    else if(rv == -3)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade file check fail: Invalid");
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - INVALID FILE\n");
        UpdateLabelStatus(8);
    }
    else if(rv == -4)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade file check fail: Overflow");
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - FILE LIST OVERFLOW\n");
        UpdateLabelStatus(9);
    }
    else
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Upgrade file check fail: Unknown");
        qDebug("[Error] %s - %d UNKNOWN RETURN VALUE !!! - utils_appup_file_check()=%d\n", __func__, __LINE__, rv);
    }

    if(rv != 0)
    {
        buttonFind->setEnabled(true);
        buttonFind->setFocus();
        buttonUpgrade->setEnabled(false);
        buttonClose->setEnabled(true);
    }

    if(isUnMount)
    {
        rv = utils_appup_device_unmount();
        if(rv < 0)
        {
            qDebug("[Error] FW_UPGRADE_DEVICE_UNMOUNT_FAIL !!\n");
            return rv;
        }
    }

    return rv;
}
void AppUpgradeDialog::onButtonUpgrade(void)
{
    upgradeState=true;
    buttonFind->setEnabled(false);
    buttonUpgrade->setEnabled(false);
    buttonClose->setEnabled(false);

    int rv = ButtonFind(0);

    if(rv == 0)
    {
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Firmware Upgrade Start");
        UpdateLabelStatus(10);
        Delay(3000);
        qDebug("[Notice] FW_UPGRADE_START !!\n");
        UpdateLabelStatus(11);
        event_send(QUEUE_QT_CORE, QUEUE_APPMGR, APPMGR_EVENT_UPGRADE_FIRMWARE_BY_APP, NULL, NULL, NULL);
        (void) appmgr_set_upgrade_result(1);
        StartTimer();
    }
}
void AppUpgradeDialog::onUpgradeProgress(int percent)
{
    if(upgradeState)
    {
        qDebug("\t===========================> Upgrading => %d%%", percent);
        progressBar->setValue(percent);
    }
}
void AppUpgradeDialog::StartTimer(void)
{
    if(!upgradeTimer)
    {
        upgradeTimer = new QTimer(this);
    }

    connect(upgradeTimer, SIGNAL(timeout()), this, SLOT(ConfirmUpgradeResult()));
    upgradeTimer->start(1000);
}
void AppUpgradeDialog::ConfirmUpgradeResult(void)
{
    int rv = appmgr_get_upgrade_result();

    if (rv == 0)
    {
        if(mainHeight == 720)
        {
            labelStatus->setStyleSheet("font:72px;background-color:rgb(152,14,69);color:white");
        }
        else
        {
            labelStatus->setStyleSheet("font:100px;background-color:rgb(152,14,69);color:white");
        }
        labelStatus->setAlignment(Qt::AlignCenter);

        qDebug(" FW_UPGRADE_SUCCESS !! \n");

        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Firmware Upgrade End: SUCCESS");

        progressBar->setValue(100);

        UpdateLabelStatus(12);

        upgradeTimer->stop();

        if(upgradeTimer)
        {
            delete upgradeTimer;
            upgradeTimer = NULL;
        }

        rv = utils_appup_device_unmount();

        if(rv < 0)
        {
            qDebug("[Error] %s, FW_UPGRADE_DEVICE_UNMOUNT_FAIL !!\n", __func__);
        }

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

        Delay(5000);

        QDialog::accept();

        return;
    }
    else if (rv == -1)
    {
        if(mainHeight == 720)
        {
            labelStatus->setStyleSheet("font:72px;background-color:rgb(152,14,69);color:white");
        }
        else
        {
            labelStatus->setStyleSheet("font:100px;background-color:rgb(152,14,69);color:white");
        }
        labelStatus->setAlignment(Qt::AlignCenter);

        qDebug(" FW_UPGRADE_FAIL !! \n");

        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Firmware Upgrade End: FAIL");

        progressBar->setValue(100);

        UpdateLabelStatus(13);

        upgradeTimer->stop();

        if(upgradeTimer)
        {
            delete upgradeTimer;
            upgradeTimer = NULL;
        }

        rv = utils_appup_device_unmount();

        buttonFind->setEnabled(true);

        buttonFind->setFocus();

        buttonUpgrade->setEnabled(false);

        buttonClose->setEnabled(true);

        if(rv < 0)
        {
            qDebug("[Error] %s, FW_UPGRADE_DEVICE_UNMOUNT_FAIL !!\n", __func__);
        }

        return;
    }
}
void AppUpgradeDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        case Qt::Key_Down:

            return;

        case Qt::Key_Left:

                 if(buttonFind->hasFocus())        { buttonClose->setFocus();    }
            else if(buttonUpgrade->hasFocus())     { buttonFind->setFocus();     }
            else if(buttonClose->hasFocus() &&
                   !buttonUpgrade->isEnabled())    { buttonFind->setFocus();     }
            else if(buttonClose->hasFocus())       { buttonUpgrade->setFocus();  }

            return;

        case Qt::Key_Right:

                 if(buttonFind->hasFocus() &&
                   !buttonUpgrade->isEnabled())    { buttonClose->setFocus();    }
            else if(buttonFind->hasFocus())        { buttonUpgrade->setFocus();  }
            else if(buttonUpgrade->hasFocus())     { buttonClose->setFocus();    }
            else if(buttonClose->hasFocus())       { buttonFind->setFocus();     }

            return;

        case Qt::Key_Enter:

            if(buttonClose->hasFocus())
            {
                reject();
            }
            else if(buttonUpgrade->hasFocus())
            {
                onButtonUpgrade();
            }
            else if(buttonFind->hasFocus())
            {
                onButtonFind();
            }

            return;

        case Qt::Key_Escape:

            if(buttonClose->isEnabled())
            {
                reject();
            }

            return;

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
void AppUpgradeDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
