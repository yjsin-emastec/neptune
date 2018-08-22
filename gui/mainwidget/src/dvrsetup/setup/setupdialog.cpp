#include <QtGui>
#include "setupdialog.h"
#include "systempage.h"
#include "recordpage.h"
#include "displaypage.h"
#include "devicepage.h"
#include "textmessagebox/textmessagedialog.h"
#include "main/mainglobal.h"
#include <sys/time.h>

SetupDialog::SetupDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    setAutoFillBackground(true);

    msgBox              = NULL;
    progressDialog      = NULL;

    criticalChangeType  = 0;
    progressType        = -1;
    tabChangeFlag       = false;
    tabPreIdx           = -1;

    systemPage    = new SystemPage(this);
    recordPage    = new RecordPage(this);
    displayPage   = new DisplayPage(this);
    devicePage    = new DevicePage(this);

    hBoxLayout    = new QHBoxLayout();
    button_Cancel = new QPushButton();
    button_Cancel->setText(tr("Close"));
    button_Cancel->setAutoDefault(false);

    createTabLayout();

    connect(systemPage,     SIGNAL(saveSystemPage(int, int)),  this,        SLOT(onSaveSystemPage(int, int)));
    connect(systemPage,     SIGNAL(escapeTabFocus(void)),      this,        SLOT(onEscapeTabFocus(void)));
    connect(systemPage,     SIGNAL(closeSetupMenu(void)),      this,        SLOT(reject()));
    connect(recordPage,     SIGNAL(saveRecordPage(int)),       this,        SLOT(onSaveRecordPage(int)));
    connect(recordPage,     SIGNAL(escapeTabFocus(void)),      this,        SLOT(onEscapeTabFocus(void)));
    connect(recordPage,     SIGNAL(closeSetupMenu(void)),      this,        SLOT(reject()));
    connect(displayPage,    SIGNAL(saveDisplayPage(int)),      this,        SLOT(onSaveDisplayPage(int)));
    connect(displayPage,    SIGNAL(escapeTabFocus(void)),      this,        SLOT(onEscapeTabFocus(void)));
    connect(displayPage,    SIGNAL(closeSetupMenu(void)),      this,        SLOT(reject()));
    connect(devicePage,     SIGNAL(saveDevicePage(int)),       this,        SLOT(onSaveDevicePage(int)));
    connect(devicePage,     SIGNAL(escapeTabFocus(void)),      this,        SLOT(onEscapeTabFocus(void)));
    connect(devicePage,     SIGNAL(closeSetupMenu(void)),      this,        SLOT(reject()));
    connect(this,           SIGNAL(upgradeProgress(int)),      systemPage,  SLOT(onUpgradeProgress(int)));
    connect(tabLayout,      SIGNAL(currentChanged(int)),       this,        SLOT(setupPageChanged(int)));
    connect(button_Cancel,  SIGNAL(released()),                this,        SLOT(reject()));

    indexSystem = indexRecord = indexDisplay = indexDevice = 0;
}
void SetupDialog::createTabLayout()
{
    tabLayout = new QTabWidget;

    tabLayout->addTab(systemPage,  tr("System"));
    tabLayout->addTab(recordPage,  tr("Record"));
    tabLayout->addTab(displayPage, tr("Display"));
    tabLayout->addTab(devicePage,  tr("Device"));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(tabLayout);
    mainLayout->addLayout(hBoxLayout);

    setLayout(mainLayout);
}
void SetupDialog::tabChangeIcon()
{
    return;

    //qDebug("tabPreIdx[%d], tabCurIdx[%d]", tabPreIdx, tabCurIdx);

    struct timeval	tv1, tv2;
    int diff;
    gettimeofday(&tv1, 0);

    tabChangeFlag = true;

    tabLayout->removeTab(tabPreIdx);

         if (tabPreIdx == 0) { tabLayout->insertTab(tabPreIdx, systemPage,  tr(" SYSTEM "));  }
    else if (tabPreIdx == 1) { tabLayout->insertTab(tabPreIdx, recordPage,  tr(" RECORD "));  }
    else if (tabPreIdx == 2) { tabLayout->insertTab(tabPreIdx, displayPage, tr(" DISPLAY ")); }
    else if (tabPreIdx == 3) { tabLayout->insertTab(tabPreIdx, devicePage,  tr(" DEVICE "));  }

    tabLayout->removeTab(tabCurIdx);

         if (tabCurIdx == 0) { tabLayout->insertTab(tabCurIdx, systemPage,  tr("SYSTEM"));  }
    else if (tabCurIdx == 1) { tabLayout->insertTab(tabCurIdx, recordPage,  tr("RECORD"));  }
    else if (tabCurIdx == 2) { tabLayout->insertTab(tabCurIdx, displayPage, tr("DISPLAY")); }
    else if (tabCurIdx == 3) { tabLayout->insertTab(tabCurIdx, devicePage,  tr("DEVICE"));  }

    tabLayout->setCurrentIndex(tabCurIdx);

    tabChangeFlag = false;

    gettimeofday(&tv2, 0);
    diff = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
    qDebug("%s elapsed time is %d usec \n", __func__, diff);
}
void SetupDialog::updateConfig(int userId)
{
    printf("\t%s --> %d\n",__func__,__LINE__);
    aif_system_get_property(&SystemCfg);
    aif_system_get_property(&SystemCfgTemp);
    aif_storage_get_property(&StorageCfg);
    aif_storage_get_property(&StorageCfgTemp);
    aif_display_get_property(&DisplayCfg);

    printf("\t%s --> %d\n",__func__,__LINE__);
    criticalChangeType = 0;

    printf("\t%s --> %d\n",__func__,__LINE__);

    tabCurIdx = 0;
    tabChangeIcon();
    printf("\t%s --> %d\n",__func__,__LINE__);
    tabLayout->setCurrentIndex(tabCurIdx);
    printf("\t%s --> %d\n",__func__,__LINE__);

    tabLayout->setFocus();
    printf("\t%s --> %d\n",__func__,__LINE__);

    systemPage->buttonDateTime->setFocus();
}
void SetupDialog::onSaveSystemPage(int type, int val)
{
    if(type == 1)          // time setting
    {
        QDialog::accept();
    }
    else if(type == 4)     // Factory Default
    {
        QDialog::accept();
    }
    else if(type == 6)     // Language
    {
        QDialog::accept();
    }
    else if(type == 7)     // Load Config
    {
        QDialog::accept();
    }
    else if(type == 8)     // Firmware Upgrade
    {
        QDialog::accept();
    }

    emit saveSystemPage(type, val);
}
void SetupDialog::onSaveRecordPage(int type)
{
    emit saveRecordPage(type);
}
void SetupDialog::onSaveDisplayPage(int type)
{
    if(type == 2) // video output HDMI
    {
        QDialog::accept();
    }

    emit saveDisplayPage(type);
}
void SetupDialog::onSaveDevicePage(int type)
{
    if(type == 1) // Disk Format
    {
        QDialog::reject();
    }

    emit saveDevicePage(type);
}
void SetupDialog::setupPageChanged(int pageNum)
{
    if(tabChangeFlag == true)
    {
        return;
    }

    qDebug(" setup page changed.....%d", pageNum);

    indexSystem = indexRecord = indexDisplay = indexDevice = 0;
    tabLayout->setStyleSheet("QTabBar::tab:selected{background:rgb(06,86,159)}");

    switch(pageNum)
    {
        case 0: systemPage->buttonDateTime->setFocus();      break;
        case 1: recordPage->buttonNormal->setFocus();        break;
        case 2: displayPage->buttonVideoOutput->setFocus();  break;
        case 3: devicePage->buttonVideo->setFocus();         break;
    }
}
void SetupDialog::onUpgradeProgress(int percent)
{
    if(systemPage)
    {
        emit upgradeProgress(percent);
    }
}
void SetupDialog::updateConfigProgress(int cfgType, int progress)
{
    qDebug("       updateConfigProgress %d, %d, %d", progressType, cfgType, progress);

    if(progressDialog)
    {
        emit progressEvent(progressType, cfgType, progress);
    }
}
void SetupDialog::onEscapeTabFocus(void)
{
    tabLayout->clearFocus();
    tabLayout->setStyleSheet("QTabBar::tab:selected{background:rgb(06,86,159)}");
}
void SetupDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        tabLayout->clearFocus();
        tabLayout->setStyleSheet("QTabBar::tab:selected{background:rgb(06,86,159)}");
    }
}
