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
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    labelModelName->setStyleSheet("font:40px;color:white");
    labelModelName->setAlignment(Qt::AlignCenter);
    labelVersion->setStyleSheet("font:40px;color:white");
    labelVersion->setAlignment(Qt::AlignCenter);
    labelFileName->setStyleSheet("font:40px;color:white");
    labelFileName->setAlignment(Qt::AlignCenter);
    labelProgress->setStyleSheet("font:40px;color:white");
    labelProgress->setAlignment(Qt::AlignCenter);
    labelModelNameValue->setStyleSheet("font:40px;color:white");
    labelVersionValue->setStyleSheet("font:40px;color:white");
    labelFileNameValue->setStyleSheet("font:38px;color:white");
    labelProgressValue->setStyleSheet("font:40px;color:white");

#if 1 //yjsin [17/09/13] if text is long, change font size and label location and size
    if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
    {
        labelModelName->setStyleSheet("font:36px;color:white");
        labelFileName->setStyleSheet("font:36px;color:white");
        labelFileNameValue->setStyleSheet("font:35px;color:white");

        labelModelName->setGeometry(10, 197, 341, 71);
        labelModelNameValue->setGeometry(350, 197, 741, 71);
        labelVersion->setGeometry(10, 267, 341, 71);
        labelVersionValue->setGeometry(350, 267, 741, 71);
        labelFileName->setGeometry(10, 337, 341, 71);
        labelFileNameValue->setGeometry(350, 337, 741, 71);
        labelProgress->setGeometry(10, 407, 341, 71);
        labelProgressValue->setGeometry(350, 407, 741, 71);
        progressBar->setGeometry(354, 410, 731, 66);
    }
    //yjsin [17/10/12] if text is long, change label size
    else if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
    {
        labelModelName->setGeometry(10, 197, 320, 71);
        labelModelNameValue->setGeometry(329, 197, 761, 71);
        labelVersion->setGeometry(10, 267, 320, 71);
        labelVersionValue->setGeometry(329, 267, 761, 71);
        labelFileName->setGeometry(10, 337, 320, 71);
        labelFileNameValue->setGeometry(329, 337, 761, 71);
        labelFileNameValue->setStyleSheet("font:36px;color:white");
        labelProgress->setGeometry(10, 407, 320, 71);
        labelProgressValue->setGeometry(329, 407, 761, 71);
        progressBar->setGeometry(334, 410, 751, 66);

        buttonFind->setGeometry(287, 495, 250, 90);
        buttonUpgrade->setGeometry(540, 495, 300, 90);
        buttonUpgrade->setStyleSheet("font:42px;");
    }
#endif

    upgradeTimer = NULL;
    msgBox       = NULL;

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
    labelStatus->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");
    buttonFind->setFocus();

    buttonFind->setEnabled(false);
    buttonUpgrade->setEnabled(false);
    buttonClose->setEnabled(false);

    UpdateLabelStatus(1);

    labelModelNameValue->clear();
    labelVersionValue->clear();
    labelFileNameValue->clear();
    progressBar->setValue(0);

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
    labelStatus->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelFileNameValue->clear();
    buttonFind->setEnabled(false);
    buttonUpgrade->setEnabled(false);
    buttonClose->setEnabled(false);
    progressBar->setValue(0);
    labelStatus->setStyleSheet("font:48px;background-color:rgb(50,57,83);color:white");

    (void)ButtonFind(1);
}
int AppUpgradeDialog::ButtonFind(int isUnMount)
{
    int rv;
    char tmp[256];

    memset(fileName, 0, sizeof(fileName));

    rv = utils_appup_device_check();

    if(rv != 0)
    {
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
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - FOLDER\n");
        UpdateLabelStatus(6);
    }
    else if(rv == -2)
    {
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - FILE\n");
        UpdateLabelStatus(7);
    }
    else if(rv == -3)
    {
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - INVALID FILE\n");
        UpdateLabelStatus(8);
    }
    else if(rv == -4)
    {
        qDebug("[Check] FW_UPGRADE_FILE_CHECK_FAIL !! - FILE LIST OVERFLOW\n");
        UpdateLabelStatus(9);
    }
    else
    {
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
    buttonFind->setEnabled(false);
    buttonUpgrade->setEnabled(false);
    buttonClose->setEnabled(false);

    int rv = ButtonFind(0);

    if(rv == 0)
    {
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
    qDebug("\t===========================> Upgrading => %d%%", percent);
    progressBar->setValue(percent);
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
        labelStatus->setAlignment(Qt::AlignCenter);

        labelStatus->setStyleSheet("font:72px;background-color:rgb(152,14,69);color:white");

        qDebug(" FW_UPGRADE_SUCCESS !! \n");

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
                    msgBox = new TextMessageDialog(tr("NOTICE"), tr("%1\n\n%2").arg(tr("NOTICE"),tr("Please unplug USB memory.")), 2, this);
                }

                msgBox->setMsgAlignment(Qt::AlignCenter);
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
        labelStatus->setAlignment(Qt::AlignCenter);

        labelStatus->setStyleSheet("font:72px;background-color:rgb(152,14,69);color:white");

        qDebug(" FW_UPGRADE_FAIL !! \n");

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

            reject();

            return;

        default:

            reject();

            return;
    }

    QDialog::keyPressEvent(event);
}
void AppUpgradeDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
