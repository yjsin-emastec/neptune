#include <QtGui>
#include <QtCore/QTimer>
#include <QTime>
#include "statusbardialog.h"
#include "DVR.h"
#include "mainglobal.h"
#include "dev/Ver.h"

#define TIME_LABEL_STYLE			"color:white;font-weight: bold;font-size:42px;"
#define TIME_LABEL_STYLE2           "color:white;font-weight: bold;font-size:63px;"

StatusBarDialog::StatusBarDialog(int timeFormat, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    timeDisplayFormat = timeFormat;

    QString style;

    style = QString(TIME_LABEL_STYLE);

    setAutoFillBackground(true);

    labelTime->setStyleSheet(style);
    labelTime->setText(updateTime_value());
    progressBarHdd->setStyleSheet(style);
    labelNoDisk->setStyleSheet(style);

    progressBarHdd->setRange(0, 100);
    progressBarHdd->setValue(0);

    isNoDisk    = 0;

    labelNoDisk->setStyleSheet(style + "background: rgb(152, 14, 69);");
    labelNoDisk->hide();

    memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);
    appmgr_get_disk_info(diskInfo);
}
StatusBarDialog::~StatusBarDialog()
{
}
void StatusBarDialog::setTimeFormat(int timeFormat)
{
    timeDisplayFormat = timeFormat;

    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)
    {
        this->is24HourMode = false;
    }
    else
    {
        this->is24HourMode = true;
    }
}
void StatusBarDialog::updateDiskProgress(unsigned int diskSize, unsigned int diskFree)
{
    QString str;
    int used = (int)(((diskSize - diskFree) * 100) / diskSize);

    if(used == -1000) // disk not found
    {
        qDebug("%s: used = -1000 \n", __func__);
    }
    else
    {
        if(isNoDisk > 0)
        {
            progressBarHdd->show();

            if(labelNoDisk->isHidden() == 0)
            {
                labelNoDisk->hide();
            }
        }

        isNoDisk = 0;

        if(utils_cfg_cmp_item(StorageCfg.overwrite, "ON") == 0)
        {
            if(labelNoDisk->isHidden() == 0)
            {
                labelNoDisk->hide();
            }

            appmgr_set_beep_duration(0);
        }

        if(used == 100)
        {
            if(diskFree == 0)
            {
                progressBarHdd->setValue(100); // disk full

                if(utils_cfg_cmp_item(StorageCfg.overwrite, "OFF") == 0)
                {
                    str = tr("FULL");
                    labelNoDisk->setText(str);
                    labelNoDisk->show();
                }
            }
            else
            {
                progressBarHdd->setValue(99); // disk full

                if(labelNoDisk->isHidden() == 0)
                {
                    labelNoDisk->hide();
                }
            }
        }
        else if(used == 2000)
        {
            progressBarHdd->setValue(99); // disk recycle

            if(labelNoDisk->isHidden() == 0)
            {
                labelNoDisk->hide();
            }
        }
        else
        {
            if(used < 0 || used > 100)
            {
                return;
            }

            progressBarHdd->setValue(used);

            if(labelNoDisk->isHidden() == 0)
            {
                labelNoDisk->hide();
            }
        }
    }
}
QString StatusBarDialog::updateTime_value()
{
    QString str, strNoDisk;
    char szDate[32];
    char szTime[32];
    QString sTime, sAmPm;
    time_t now;
    struct tm tmNow;
    int dlsType = DLS_OFF, isEndOverlap = 0;

    time(&now);
    localtime_r(&now, &tmNow);

    if(diskInfo[0].hddCount == 0)
    {
        if(isNoDisk > 0)
        {
            strNoDisk = "   "+tr("NO SSD")+"   ";
            labelNoDisk->setText(strNoDisk);
        }
        else
        {
            isNoDisk = 1;
            progressBarHdd->hide();
            strNoDisk = "   "+tr("NO SSD")+"   ";
            labelNoDisk->setText(strNoDisk);
            labelNoDisk->show();
            qDebug("\n\t No Disk.... %d\n", isNoDisk);
        }
    }
    else
    {
        if(progressBarHdd->isHidden())
        {
            progressBarHdd->show();
        }
    }

    if(dlsLive.isChecked && dlsLive.isDlsEnabled)
    {
        if(dlsLive.dlsCheckYear != tmNow.tm_year)
        {
            appmgr_make_dls_time_info(tmNow.tm_year, 1, &dlsLive);
        }

        if(dlsLive.tDlsEnd > dlsLive.tDlsBegin)
        {
            if((now >= dlsLive.tDlsBegin) && (now < dlsLive.tDlsEnd))
            {
                dlsType = DLS_DAY;
            }
        }
        else
        {
            if(!((now >= dlsLive.tDlsEnd) && (now < dlsLive.tDlsBegin)))
            {
                dlsType = DLS_DAY;
            }
        }

        if(dlsType)
        {
            if(tmNow.tm_mon == dlsLive.dlsEndMonth && tmNow.tm_mday == dlsLive.dlsEndDay && (tmNow.tm_hour == dlsLive.dlsEndHour-1))
            {
                isEndOverlap = 1;
            }
            else
            {
                now += 3600;
                localtime_r(&now, &tmNow);
            }
        }
    }

    memset(szDate, 0, 32);
    memset(szTime, 0, 32);

    //bool is24HourMode = false;
    bool isAmPmFirst = false;
    bool isDateFirst = true;

    if(is24HourMode)
    {
        if(isEndOverlap)
        {
            sprintf(szTime, "%02d':%02d:%02d", tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
        }
        else
        {
            sprintf(szTime, "%02d:%02d:%02d", tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
        }

        sTime = QString::fromAscii(szTime);
    }
    else
    {
        if(tmNow.tm_hour < 12)
        {
            sAmPm = tr("AM");
        }
        else
        {
            sAmPm = tr("PM");
        }

        if((tmNow.tm_hour == 0)||(tmNow.tm_hour == 12))
        {
            if(isEndOverlap)
            {
                sprintf(szTime, "12':%02d:%02d", tmNow.tm_min, tmNow.tm_sec);
            }
            else
            {
                sprintf(szTime, "12:%02d:%02d", tmNow.tm_min, tmNow.tm_sec);
            }
        }
        else
        {
            if(isEndOverlap)
            {
                sprintf(szTime, "%d':%02d:%02d", tmNow.tm_hour%12, tmNow.tm_min, tmNow.tm_sec);
            }
            else
            {
                sprintf(szTime, "%d:%02d:%02d", tmNow.tm_hour%12, tmNow.tm_min, tmNow.tm_sec);
            }
        }

        if(isAmPmFirst)
        {
            sTime = sAmPm + " " + QString::fromAscii(szTime);
        }
        else
        {
            sTime = QString::fromAscii(szTime) + " " + sAmPm;
        }
    }

    switch (timeDisplayFormat)
    {
        case 0: { sprintf(szDate, "%04d/%02d/%02d", tmNow.tm_year+1900, tmNow.tm_mon+1, tmNow.tm_mday);      break; } //YYYY/MM/DD
        case 1: { sprintf(szDate, "%02d/%02d/%04d", tmNow.tm_mon+1,     tmNow.tm_mday,  tmNow.tm_year+1900); break; } //MM/DD/YYYY
        case 2: { sprintf(szDate, "%02d/%02d/%04d", tmNow.tm_mday,      tmNow.tm_mon+1, tmNow.tm_year+1900); break; } //DD/MM/YYYY
        case 3: { sprintf(szDate, "%04d-%02d-%02d", tmNow.tm_year+1900, tmNow.tm_mon+1, tmNow.tm_mday);      break; } //YYYY-MM-DD
        case 4: { sprintf(szDate, "%02d-%02d-%04d", tmNow.tm_mon+1,     tmNow.tm_mday,  tmNow.tm_year+1900); break; } //MM-DD-YYYY
        case 5: { sprintf(szDate, "%02d-%02d-%04d", tmNow.tm_mday,      tmNow.tm_mon+1, tmNow.tm_year+1900); break; } //DD-MM-YYYY

        default :
        {
            qDebug("[ERROR] UNKNOWN timeDisplayFormat:%d   %s-%d", timeDisplayFormat, __func__, __LINE__);
            break;
        }
    }

    if(isDateFirst)
    {
        str = QString::fromAscii(szDate) + " " + sTime;
    }
    else
    {
        str = sTime + " " + QString::fromAscii(szDate);
    }

    resizeStatusBar();

    return str;
}
void StatusBarDialog::updateTime()
{
    time_t now;
    struct tm tmNow;
    QString str;

    if(this->isVisible())
    {
        time(&now);
        localtime_r(&now, &tmNow);
        appmgr_set_live_system_time(now);

        // Live Time Draw
        labelTime->setText(updateTime_value());
    }
    else
    {
        if(diskInfo[0].hddCount == 0)
        {
            //qDebug("[Warning] : Not exist HDD");
        }
    }
}
void StatusBarDialog::resizeStatusBar()
{
    QSize statusbarSize;

    if(mainHeight == 720)
    {
        if(is24HourMode)
        {
            statusbarSize.setWidth(680);
            statusbarSize.setHeight(80);

            this->resize(statusbarSize);
            frame->resize(statusbarSize.width()-8,statusbarSize.height()-8);
            labelNoDisk->setGeometry(485,8,180,58);
            progressBarHdd->setGeometry(485,8,180,58);
            this->move((mainWidth-statusbarSize.width())/2, mainHeight-statusbarSize.height());
        }
        else
        {
            statusbarSize.setWidth(755);
            statusbarSize.setHeight(80);

            this->resize(statusbarSize);
            frame->resize(statusbarSize.width()-8,statusbarSize.height()-8);
            labelNoDisk->setGeometry(560,8,180,58);
            progressBarHdd->setGeometry(560,8,180,58);
            this->move((mainWidth-statusbarSize.width())/2, mainHeight-statusbarSize.height());
        }
    }
    else
    {
        if(is24HourMode)
        {
            statusbarSize.setWidth(1020);
            statusbarSize.setHeight(120);

            this->resize(statusbarSize);
            frame->resize(statusbarSize.width()-8,statusbarSize.height()-8);
            labelTime->setGeometry(15,12,725,87);
            labelNoDisk->setGeometry(frame->width()-10-270,12,270,87);
            progressBarHdd->setGeometry(frame->width()-10-270,12,270,87);
            this->move((mainWidth-statusbarSize.width())/2, mainHeight-statusbarSize.height());
            labelTime->setStyleSheet(QString(TIME_LABEL_STYLE2));
            labelNoDisk->setStyleSheet(QString(TIME_LABEL_STYLE2).append("background: rgb(152, 14, 69);"));
            progressBarHdd->setStyleSheet(QString(TIME_LABEL_STYLE2).append("background: rgb(152, 14, 69);"));
        }
        else
        {
            statusbarSize.setWidth(1130);
            statusbarSize.setHeight(120);

            this->resize(statusbarSize);
            frame->resize(statusbarSize.width()-8,statusbarSize.height()-8);
            labelTime->setGeometry(15,12,840,87);
            labelNoDisk->setGeometry(frame->width()-10-270,12,270,87);
            progressBarHdd->setGeometry(frame->width()-10-270,12,270,87);
            this->move((mainWidth-statusbarSize.width())/2, mainHeight-statusbarSize.height());
            labelTime->setStyleSheet(QString(TIME_LABEL_STYLE2));
            labelNoDisk->setStyleSheet(QString(TIME_LABEL_STYLE2).append("background: rgb(152, 14, 69);"));
            progressBarHdd->setStyleSheet(QString(TIME_LABEL_STYLE2).append("background: rgb(152, 14, 69);"));
        }
    }
}
