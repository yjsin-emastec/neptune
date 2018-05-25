#include <QtGui>
#include "setdatetimedialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

SetDateTimeDialog::SetDateTimeDialog(QWidget *parent, int dateFormat, cfg_dls_t *cfg)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    layoutFrame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    setAutoFillBackground(true);

    msgBox = NULL;
    bOnce = true;
    timeFormat = dateFormat;
    dlsZone = DLS_OFF;

    memset(&cfgDls, 0, sizeof(cfg_dls_t));

    if(cfg)
    {
        memcpy(&cfgDls, cfg, sizeof(cfg_dls_t));
    }

    initComboBox();

    enableSetTime();
    changeDlsType(cfgDls.dls_flag);

    connect(comboBoxTime_1,   SIGNAL(currentIndexChanged(int)), this, SLOT(time1Changed(int)));
    connect(comboBoxTime_2,   SIGNAL(currentIndexChanged(int)), this, SLOT(time2Changed(int)));
    connect(comboBoxTime_3,   SIGNAL(currentIndexChanged(int)), this, SLOT(time3Changed(int)));
    connect(buttonTimeFormat, SIGNAL(released()),               this, SLOT(onButtonTimeFormat()));
    connect(buttonGpsSync,    SIGNAL(released()),               this, SLOT(onButtonGpsSync()));

    buttonTimeFormat->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonGpsSync->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    comboBoxTime_1->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");
    comboBoxTime_2->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");
    comboBoxTime_3->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");
    comboBoxTime_4->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");
    comboBoxTime_5->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");
    comboBoxTime_6->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");

    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Save"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    buttonBox->button(QDialogButtonBox::Ok)->setMinimumSize(200,91);
    buttonBox->button(QDialogButtonBox::Cancel)->setMinimumSize(200,91);

    comboBoxTimeZone->setStyleSheet("QComboBox{font:38px;background:rgb(50,57,83);color:white;}QComboBox:focus{border-color:rgb(67,74,86);background-color:rgb(152,14,69);color:white;}");
    comboBoxTimeZone->setView(new QListView);   //item width resize
    isKeyLock = 0;

    comboBoxTimeZone->installEventFilter(this);
    comboBoxTime_1->installEventFilter(this);
    comboBoxTime_2->installEventFilter(this);
    comboBoxTime_3->installEventFilter(this);
    comboBoxTime_4->installEventFilter(this);
    comboBoxTime_5->installEventFilter(this);
    comboBoxTime_6->installEventFilter(this);
}
void SetDateTimeDialog::initComboBox()
{
    QString str;
    time_t now;
    struct tm tmNow;
    int dlsType = DLS_OFF, isEndOverlap = 0;
    dls_convert_info_t dlsSetDate;

    time(&now);
    localtime_r(&now, &tmNow);

    buttonTimeFormat->setFocus();

    switch(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR"))
    {
        case 0:  { buttonTimeFormat->setText(tr("Time Format\n12 Hour")); indexTimeFormat = 1; break; }
        default: { buttonTimeFormat->setText(tr("Time Format\n24 Hour")); indexTimeFormat = 0; break; }
    }

    if(utils_cfg_cmp_item(SystemCfg.gps_sync, "ON") == 0)
    {
        buttonGpsSync->setText(tr("GPS Synchronization\nOn"));
        indexGpsSync = 0;
    }
    else if(utils_cfg_cmp_item(SystemCfg.gps_sync, "OFF") == 0)
    {
        buttonGpsSync->setText(tr("GPS Synchronization\nOff"));
        indexGpsSync = 1;
    }

    comboBoxTimeZone->addItem(tr("TimeZone [UTC -12:00 Eniwetok/Kwajalein]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -11:00 Niue]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -10:00 Hawaii]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -09:00 Alaska]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -08:00 Los Angeles/Vancouver]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -07:00 Arizona]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -06:00 Chicago/Houston/Mexico City]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -05:00 Boston/Montreal/New York]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -04:30 Caracas]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -04:00 Santiago]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -03:30 Newfoundland]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -03:00 Buenos Aires/Rio de Janero]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -02:00 Fernando de Noronha]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC -01:00 Azores]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +00:00 Lisbon/London/Monaco]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +01:00 Berlin/Paris/Rome]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +02:00 Athens/Cape Town/Istanbul]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +03:00 Moscow/Baghdad/Kuwait]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +03:30 Teheran]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +04:00 Abu Dhabi/Muscat]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +04:30 Kabul]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +05:00 Islamabad/Karachi]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +05:30 Chennai]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +05:45 Kathmandu]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +06:00 Astana/Dhaka/Almaty]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +06:30 Rangoon]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +07:00 Bangkok/Hanoi/Jakarta]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +08:00 Beijing/Singapore/Taipei]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +09:00 Seoul/Tokyo]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +09:30 Darwin]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +10:00 Guam/Canberra/Sydney]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +11:00 Magadan/Solomon]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +12:00 Fiji/Marshall]"));
    comboBoxTimeZone->addItem(tr("TimeZone [UTC +13:00 Nuku'alofa]"));

    checkTimezone();

    dlsZone = DLS_OFF;
    appmgr_make_dls_time_info(tmNow.tm_year, 0, &dlsSetDate);

    if(dlsSetDate.isChecked && dlsSetDate.isDlsEnabled)
    {
        if(dlsSetDate.tDlsEnd > dlsSetDate.tDlsBegin)
        {
            if((now >= dlsSetDate.tDlsBegin) && (now < dlsSetDate.tDlsEnd))
            {
                dlsType = DLS_DAY;
            }
        }
        else
        {
            if(!((now >= dlsSetDate.tDlsEnd) && (now < dlsSetDate.tDlsBegin)))
            {
                dlsType = DLS_DAY;
            }
        }

        qDebug("Set Date : DLS End Month %d, Day %d, Hour %d", dlsSetDate.dlsEndMonth, dlsSetDate.dlsEndDay, dlsSetDate.dlsEndHour);

        if(tmNow.tm_mon == dlsSetDate.dlsEndMonth && tmNow.tm_mday == dlsSetDate.dlsEndDay)
        {
            dlsZone = DLS_END_DAY;
        }
        else if(tmNow.tm_mon == dlsSetDate.dlsBeginMonth && tmNow.tm_mday == dlsSetDate.dlsBeginDay)
        {
            dlsZone = DLS_START_DAY;
        }
        else
        {
            dlsZone = DLS_DAY;
        }

        if(dlsType)
        {
            if(tmNow.tm_mon == dlsSetDate.dlsEndMonth && tmNow.tm_mday == dlsSetDate.dlsEndDay && (tmNow.tm_hour == dlsSetDate.dlsEndHour-1))
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

    switch (timeFormat)
    {
        case DF_A_YYYY_MM_DD:
        case DF_B_YYYY_MM_DD:

            for(int i = ver_get_ref_year(); i < MAX_YEAR; i++)
            {
                str= QString("%1: %2").arg(tr("Year")).arg(i);
                comboBoxTime_1->addItem(str);
            }

            for(int i = 0; i < 12; i++)
            {
                if(i<9)
                {
                    str=QString("%1: 0%2").arg(tr("Month")).arg(i+1);
                }
                else
                {
                    str=QString("%1: %2").arg(tr("Month")).arg(i+1);
                }
                comboBoxTime_2->addItem(str);
            }

            for(int i = 0; i < 31; i++)
            {
                if(i<9)
                {
                    str=QString("%1: 0%2").arg(tr("Day")).arg(i+1);
                }
                else
                {
                    str=QString("%1: %2").arg(tr("Day")).arg(i+1);
                }
                comboBoxTime_3->addItem(str);
            }

            if(tmNow.tm_year < (ver_get_ref_year()-1900))
            {
                comboBoxTime_1->setCurrentIndex(0);
            }
            else
            {
                comboBoxTime_1->setCurrentIndex((tmNow.tm_year+1900)-ver_get_ref_year());
            }

            comboBoxTime_2->setCurrentIndex(tmNow.tm_mon);
            comboBoxTime_3->setCurrentIndex(tmNow.tm_mday-1);

            break;

        case DF_A_MM_DD_YYYY:
        case DF_B_MM_DD_YYYY:

            for(int i = 0; i < 12; i++)
            {
                if(i<9)
                {
                    str=QString("%1: 0%2").arg(tr("Month")).arg(i+1);
                }
                else
                {
                    str=QString("%1: %2").arg(tr("Month")).arg(i+1);
                }
                comboBoxTime_1->addItem(str);
            }

            for(int i = 0; i < 31; i++)
            {
                if(i<9)
                {
                    str=QString("%1: 0%2").arg(tr("Day")).arg(i+1);
                }
                else
                {
                    str=QString("%1: %2").arg(tr("Day")).arg(i+1);
                }
                comboBoxTime_2->addItem(str);
            }

            for(int i = ver_get_ref_year(); i < MAX_YEAR; i++)
            {
                str= QString("%1: %2").arg(tr("Year")).arg(i);
                comboBoxTime_3->addItem(str);
            }

            if(tmNow.tm_year < (ver_get_ref_year()-1900))
            {
                comboBoxTime_3->setCurrentIndex(0);
            }
            else
            {
                comboBoxTime_3->setCurrentIndex((tmNow.tm_year+1900)-ver_get_ref_year());
            }

            comboBoxTime_1->setCurrentIndex(tmNow.tm_mon);
            comboBoxTime_2->setCurrentIndex(tmNow.tm_mday-1);

            break;

        case DF_A_DD_MM_YYYY:
        case DF_B_DD_MM_YYYY:

            for(int i = 0; i < 31; i++)
            {
                if(i<9)
                {
                    str=QString("%1: 0%2").arg(tr("Day")).arg(i+1);
                }
                else
                {
                    str=QString("%1: %2").arg(tr("Day")).arg(i+1);
                }
                comboBoxTime_1->addItem(str);
            }

            for(int i = 0; i < 12; i++)
            {
                if(i<9)
                {
                    str=QString("%1: 0%2").arg(tr("Month")).arg(i+1);
                }
                else
                {
                    str=QString("%1: %2").arg(tr("Month")).arg(i+1);
                }
                comboBoxTime_2->addItem(str);
            }

            for(int i = ver_get_ref_year(); i < MAX_YEAR; i++)
            {
                str=QString("%1: %2").arg(tr("Year")).arg(i);
                comboBoxTime_3->addItem(str);
            }

            if(tmNow.tm_year < (ver_get_ref_year()-1900) ) // Rtc base 2000/1/1
            {
                comboBoxTime_3->setCurrentIndex(0);
            }
            else
            {
                comboBoxTime_3->setCurrentIndex((tmNow.tm_year+1900)-ver_get_ref_year());
            }

            comboBoxTime_2->setCurrentIndex(tmNow.tm_mon);
            comboBoxTime_1->setCurrentIndex(tmNow.tm_mday-1);

            break;
    }

    monthDayCheck(4);

    switch (timeFormat)
    {
        case DF_A_YYYY_MM_DD:
        case DF_B_YYYY_MM_DD:

            comboBoxTime_3->setCurrentIndex(tmNow.tm_mday-1);

            break;

        case DF_A_MM_DD_YYYY:
        case DF_B_MM_DD_YYYY:

            comboBoxTime_2->setCurrentIndex(tmNow.tm_mday-1);

            break;

        case DF_A_DD_MM_YYYY:
        case DF_B_DD_MM_YYYY:

            comboBoxTime_1->setCurrentIndex(tmNow.tm_mday-1);

            break;
    }

    switch (timeFormat)
    {
        case DF_A_YYYY_MM_DD:
        case DF_A_MM_DD_YYYY:
        case DF_A_DD_MM_YYYY:

            labelTime_1->setText(tr("/"));
            labelTime_2->setText(tr("/"));

            break;

        case DF_B_DD_MM_YYYY:
        case DF_B_MM_DD_YYYY:
        case DF_B_YYYY_MM_DD:

            labelTime_1->setText(tr("-"));
            labelTime_2->setText(tr("-"));

            break;
    }

    // yjsin [17/10/24] Change ComboBox text when time format changed.
    // but DayightSavingTime(DTS) part are not changeed.
    for(int i = 0; i < 24; i++)
    {
        if(indexTimeFormat==1 && i==0)                  //12H, 12 AM
        {
            str=QString("%1: AM %2").arg(tr("Hour")).arg(i+12);
        }
        else if(indexTimeFormat==1 && i>0 && i<10)      //12H, 1~9 AM
        {
            str=QString("%1: AM 0%2").arg(tr("Hour")).arg(i);
        }
        else if(indexTimeFormat==1 && i>=10 && i<12)    //12H, 10~11 AM
        {
            str=QString("%1: AM %2").arg(tr("Hour")).arg(i);
        }
        else if(indexTimeFormat==1 && i==12)            //12H, 12 PM
        {
            str=QString("%1: PM %2").arg(tr("Hour")).arg(i);
        }
        else if(indexTimeFormat==1 && i>12 && i<22)     //12H, 1~9 PM
        {
            str=QString("%1: PM 0%2").arg(tr("Hour")).arg(i-12);
        }
        else if(indexTimeFormat==1 && i>=22 && i<24)    //12H, 10~11 PM
        {
            str=QString("%1: PM %2").arg(tr("Hour")).arg(i-12);
        }
        else if(indexTimeFormat==0 && i>=0 && i<10)     //24H, 0~9
        {
            str=QString("%1: 0%2").arg(tr("Hour")).arg(i);
        }
        else if(indexTimeFormat==0 && i>=10 && i<24)    //24H, 10~23
        {
            str=QString("%1: %2").arg(tr("Hour")).arg(i);
        }
        else                                            //Error
        {
            str=QString("%1: %2").arg(tr("Hour")).arg(i);
            qDebug("[ERROR]SetDateTimeDialog::initComboBox()");
        }
        comboBoxTime_4->addItem(str);

        if(dlsZone == DLS_END_DAY && (i == (dlsSetDate.dlsEndHour - 1)))
        {
            str = tr("Hour: %1").arg(i);
            comboBoxTime_4->addItem(str);
        }
    }

    for(int i = 0; i < 60; i++)
    {
        if(i<10)
        {
            str=QString("%1: 0%2").arg(tr("Minute")).arg(i);
        }
        else
        {
            str=QString("%1: %2").arg(tr("Minute")).arg(i);
        }
        comboBoxTime_5->addItem(str);

        if(i<10)
        {
            str=QString("%1: 0%2").arg(tr("Second")).arg(i);
        }
        else
        {
            str=QString("%1: %2").arg(tr("Second")).arg(i);
        }
        comboBoxTime_6->addItem(str);
    }

    if(dlsZone == DLS_END_DAY)
    {
        if(tmNow.tm_hour == (dlsSetDate.dlsEndHour-1))
        {
            if(isEndOverlap)
            {
                comboBoxTime_4->setCurrentIndex(tmNow.tm_hour+1);
            }
            else
            {
                comboBoxTime_4->setCurrentIndex(tmNow.tm_hour);
            }
        }
        else if(tmNow.tm_hour >= (dlsSetDate.dlsEndHour))
        {
            comboBoxTime_4->setCurrentIndex(tmNow.tm_hour+1);
        }
        else
        {
            comboBoxTime_4->setCurrentIndex(tmNow.tm_hour);
        }
    }
    else
    {
        comboBoxTime_4->setCurrentIndex(tmNow.tm_hour);
    }

    comboBoxTime_5->setCurrentIndex(tmNow.tm_min);
    comboBoxTime_6->setCurrentIndex(tmNow.tm_sec);

    getChangedTime(&oldTime);
}//
SetDateTimeDialog::~SetDateTimeDialog()
{
}
void SetDateTimeDialog::changeDlsType(int dls)
{
}
void SetDateTimeDialog::enableSetTime()
{
    emit signalResetTimer();
    QString str;
    time_t tFirstRec = 0, tLastRect= 0;
    struct tm tmLast;
    int diskNum = 0;
    int dlsType = DLS_OFF, isEndOverlap = 0;
    dls_convert_info_t dlsSetDate;
    char szDate[30];
    bool bSet = 1;

    comboBoxTime_1->setEnabled(bSet);
    comboBoxTime_2->setEnabled(bSet);
    comboBoxTime_3->setEnabled(bSet);
    comboBoxTime_4->setEnabled(bSet);
    comboBoxTime_5->setEnabled(bSet);
    comboBoxTime_6->setEnabled(bSet);

    if(bSet)
    {
        disk_used_info_t diskInfo[MAX_HDD_COUNT];
        memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);
        diskNum = appmgr_get_disk_info(diskInfo);

        if(diskNum <= 0)
        {
            return;
        }

        for(int i = 0; i < MAX_HDD_COUNT; i++)
        {
            if(tFirstRec == 0)
            {
                tFirstRec = diskInfo[i].startTime;
            }
            else
            {
                if((tFirstRec > diskInfo[i].startTime) && (diskInfo[i].startTime > 0))
                {
                    tFirstRec = diskInfo[i].startTime;
                }
            }

            if(tLastRect == 0)
            {
                tLastRect = diskInfo[i].lastTime;
            }
            else
            {
                if(diskInfo[i].lastTime > tLastRect)
                {
                    tLastRect = diskInfo[i].lastTime;
                }
            }
        }

        localtime_r(&tLastRect, &tmLast);

        appmgr_make_dls_time_info(tmLast.tm_year, 0, &dlsSetDate);

        if(dlsSetDate.isChecked && dlsSetDate.isDlsEnabled)
        {
            if(dlsSetDate.tDlsEnd > dlsSetDate.tDlsBegin)
            {
                if((tLastRect >= dlsSetDate.tDlsBegin) && (tLastRect < dlsSetDate.tDlsEnd))
                {
                    dlsType = DLS_DAY;
                }
            }
            else
            {
                if(!((tLastRect >= dlsSetDate.tDlsEnd) && (tLastRect < dlsSetDate.tDlsBegin)))
                {
                    dlsType = DLS_DAY;
                }
            }

            if(dlsType)
            {
                if(tmLast.tm_mon == dlsSetDate.dlsEndMonth && tmLast.tm_mday == dlsSetDate.dlsEndDay && (tmLast.tm_hour == dlsSetDate.dlsEndHour-1))
                {
                    isEndOverlap = 1;
                }
                else
                {
                    tLastRect += 3600;
                    localtime_r(&tLastRect, &tmLast);
                }
            }
        }

        str = tr("If you set the time faster than recording data,\n"
                "some data will be erased from storage.\n");

        memset(szDate, 0, 30);

        switch (DateFormat)
        {
            case 0:
            default : 	//YYYY/MM/DD

                if(isEndOverlap)
                {
                    sprintf(szDate, "%d/%02d/%02d %02d':%02d:%02d", tmLast.tm_year+1900, tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_hour-1, tmLast.tm_min, tmLast.tm_sec);
                }
                else
                {
                    sprintf(szDate, "%d/%02d/%02d %02d:%02d:%02d", tmLast.tm_year+1900, tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
                }

                break;

            case 1:		//MM/DD/YYYY

                if(isEndOverlap)
                {
                    sprintf(szDate, "%02d/%02d/%d %02d':%02d:%02d", tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_year+1900, tmLast.tm_hour-1, tmLast.tm_min, tmLast.tm_sec);
                }
                else
                {
                    sprintf(szDate, "%02d/%02d/%d %02d:%02d:%02d", tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
                }

                break;

            case 2:		//DD/MM/YYYY

                if(isEndOverlap)
                {
                    sprintf(szDate, "%02d/%02d/%d %02d':%02d:%02d", tmLast.tm_mday, tmLast.tm_mon+1, tmLast.tm_year+1900, tmLast.tm_hour-1, tmLast.tm_min, tmLast.tm_sec);
                }
                else
                {
                    sprintf(szDate, "%02d/%02d/%d %02d:%02d:%02d", tmLast.tm_mday, tmLast.tm_mon+1, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
                }

                break;
            case 3:		//YYYY-MM-DD

                if(isEndOverlap)
                {
                    sprintf(szDate, "%d-%02d-%02d %02d':%02d:%02d", tmLast.tm_year+1900, tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_hour-1, tmLast.tm_min, tmLast.tm_sec);
                }
                else
                {
                    sprintf(szDate, "%d-%02d-%02d %02d:%02d:%02d", tmLast.tm_year+1900, tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
                }

                break;
            case 4:		//MM-DD-YYYY

                if(isEndOverlap)
                {
                    sprintf(szDate, "%02d-%02d-%d %02d':%02d:%02d", tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_year+1900, tmLast.tm_hour-1, tmLast.tm_min, tmLast.tm_sec);
                }
                else
                {
                    sprintf(szDate, "%02d-%02d-%d %02d:%02d:%02d", tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
                }

                break;
            case 5:		//DD-MM-YYYY

                if(isEndOverlap)
                {
                    sprintf(szDate, "%02d-%02d-%d %02d':%02d:%02d", tmLast.tm_mday, tmLast.tm_mon+1, tmLast.tm_year+1900, tmLast.tm_hour-1, tmLast.tm_min, tmLast.tm_sec);
                }
                else
                {
                    sprintf(szDate, "%02d-%02d-%d %02d:%02d:%02d", tmLast.tm_mday, tmLast.tm_mon+1, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
                }

                break;
        }

        str += QString::fromAscii(szDate);

        if(!msgBox)
        {
            msgBox = new TextMessageDialog(tr("SET DATE & TIME"), str, 2, this);
        }

        msgBox->exec();

        delete msgBox;
        msgBox = NULL;

        bOnce = false;
    }
}
void SetDateTimeDialog::checkChangeTime()
{
}
void SetDateTimeDialog::getChangedTime(time_t *newTime)
{
    struct tm when;
    dls_convert_info_t dlsSetDate;

    switch (timeFormat)
    {
        case DF_A_YYYY_MM_DD:
        case DF_B_YYYY_MM_DD:

            when.tm_year = comboBoxTime_1->currentIndex() + ver_get_ref_year() - 1900;
            when.tm_mon = comboBoxTime_2->currentIndex();
            when.tm_mday = comboBoxTime_3->currentIndex() + 1;

            break;

        case DF_A_MM_DD_YYYY:
        case DF_B_MM_DD_YYYY:

            when.tm_year = comboBoxTime_3->currentIndex() + ver_get_ref_year() - 1900;
            when.tm_mon = comboBoxTime_1->currentIndex();
            when.tm_mday = comboBoxTime_2->currentIndex() + 1;

            break;

        case DF_A_DD_MM_YYYY:
        case DF_B_DD_MM_YYYY:

            when.tm_year = comboBoxTime_3->currentIndex() + ver_get_ref_year() - 1900;
            when.tm_mon = comboBoxTime_2->currentIndex();
            when.tm_mday = comboBoxTime_1->currentIndex() + 1;

            break;
    }

    appmgr_make_dls_time_info(when.tm_year, 0, &dlsSetDate);

    if(dlsSetDate.isChecked && dlsSetDate.isDlsEnabled)
    {
        if(when.tm_mon == dlsSetDate.dlsEndMonth && when.tm_mday == dlsSetDate.dlsEndDay)
        {
            if(when.tm_hour < dlsSetDate.dlsEndHour)
            {
                when.tm_hour = comboBoxTime_4->currentIndex();
                when.tm_min  = comboBoxTime_5->currentIndex();
                when.tm_sec  = comboBoxTime_6->currentIndex();

                *newTime     = mktime(&when);

                // dls zone
                *newTime -= 3600;
            }
            else
            {
                // no dls zone
                when.tm_hour = comboBoxTime_4->currentIndex() - 1;
                when.tm_min  = comboBoxTime_5->currentIndex();
                when.tm_sec  = comboBoxTime_6->currentIndex();

                *newTime     = mktime(&when);
            }
        }
        else if(when.tm_mon == dlsSetDate.dlsBeginMonth && when.tm_mday == dlsSetDate.dlsBeginDay)
        {
            when.tm_hour = comboBoxTime_4->currentIndex();
            when.tm_min  = comboBoxTime_5->currentIndex();
            when.tm_sec  = comboBoxTime_6->currentIndex();

            *newTime     = mktime(&when);

            if(when.tm_hour > dlsSetDate.dlsBeginHour)
            {
                *newTime -= 3600;
            }
        }
        else
        {
            when.tm_hour = comboBoxTime_4->currentIndex();
            when.tm_min  = comboBoxTime_5->currentIndex();
            when.tm_sec  = comboBoxTime_6->currentIndex();
            *newTime     = mktime(&when);

            if(dlsSetDate.tDlsEnd > dlsSetDate.tDlsBegin)
            {
                if((*newTime >= dlsSetDate.tDlsBegin) && (*newTime < dlsSetDate.tDlsEnd))
                {
                    *newTime -= 3600;
                }
            }
            else
            {
                if(!((*newTime >= dlsSetDate.tDlsEnd) && (*newTime < dlsSetDate.tDlsBegin)))
                {
                    *newTime -= 3600;
                }
            }
        }
    }
    else
    {
        when.tm_hour = comboBoxTime_4->currentIndex();
        when.tm_min  = comboBoxTime_5->currentIndex();
        when.tm_sec  = comboBoxTime_6->currentIndex();

        *newTime     = mktime(&when);
    }
}
void SetDateTimeDialog::getChangedConfig(time_t *newTime, cfg_dls_t *cfg)
{
    if(!cfg)
    {
        return;
    }

    setTimezone();

    time_t tmpTime;
    getChangedTime(&tmpTime);

    if(tmpTime == oldTime)
    {
        *newTime = 0;
    }
    else
    {
        *newTime = tmpTime;
    }

    cfg->dls_flag = cfgDls.dls_flag;

    if(cfgDls.dls_flag == 2)
    {
        ;
    }
    else if(cfgDls.dls_flag == 3)
    {
        ;
    }
}
void SetDateTimeDialog::resetHour()
{
    QString str;
    struct tm when;
    dls_convert_info_t dlsSetDate;
    int prevHourLen = 0, prevHour = 0;

    when.tm_year = when.tm_mon = when.tm_mday = 0;

    prevHourLen = comboBoxTime_4->count();
    prevHour    = comboBoxTime_4->currentIndex();

    switch (timeFormat)
    {
        case DF_A_YYYY_MM_DD:
        case DF_B_YYYY_MM_DD:

            when.tm_year = comboBoxTime_1->currentIndex() + ver_get_ref_year() - 1900;
            when.tm_mon = comboBoxTime_2->currentIndex();
            when.tm_mday = comboBoxTime_3->currentIndex() + 1;

            break;

        case DF_A_MM_DD_YYYY:
        case DF_B_MM_DD_YYYY:

            when.tm_year = comboBoxTime_3->currentIndex() + ver_get_ref_year() - 1900;
            when.tm_mon = comboBoxTime_1->currentIndex();
            when.tm_mday = comboBoxTime_2->currentIndex() + 1;

            break;

        case DF_A_DD_MM_YYYY:
        case DF_B_DD_MM_YYYY:

            when.tm_year = comboBoxTime_3->currentIndex() + ver_get_ref_year() - 1900;
            when.tm_mon = comboBoxTime_2->currentIndex();
            when.tm_mday = comboBoxTime_1->currentIndex() + 1;

            break;
    }

    appmgr_make_dls_time_info(when.tm_year, 0, &dlsSetDate);

    if(dlsSetDate.isChecked && dlsSetDate.isDlsEnabled)
    {
        if(when.tm_mon == dlsSetDate.dlsEndMonth && when.tm_mday == dlsSetDate.dlsEndDay)
        {
            comboBoxTime_4->clear();

            for(int i = 0; i < 24; i++)
            {
                str = tr("Hour: %1").arg(i);
                comboBoxTime_4->addItem(str);

                if(i == (dlsSetDate.dlsEndHour - 1))
                {
                    str = tr("Hour: %1").arg(i);
                    comboBoxTime_4->addItem(str);
                }
            }
        }
        else
        {
            if(prevHourLen != 24)
            {
                comboBoxTime_4->clear();

                for(int i = 0; i < 24; i++)
                {
                    str = tr("Hour: %1").arg(i);
                    comboBoxTime_4->addItem(str);
                }
            }
        }
    }
    else
    {
        if(prevHourLen != 24)
        {
            comboBoxTime_4->clear();

            for(int i = 0; i < 24; i++)
            {
                str = tr("Hour: %1").arg(i);
                comboBoxTime_4->addItem(str);
            }
        }
    }

    if(prevHour >= comboBoxTime_4->count())
    {
        comboBoxTime_4->setCurrentIndex(comboBoxTime_4->count() - 1);
    }
    else
    {
        comboBoxTime_4->setCurrentIndex(prevHour);
    }
}
void SetDateTimeDialog::time1Changed(int val)
{
    emit signalResetTimer();

    monthDayCheck(1);

    resetHour();
}
void SetDateTimeDialog::time2Changed(int val)
{
    emit signalResetTimer();

    monthDayCheck(2);

    resetHour();
}
void SetDateTimeDialog::time3Changed(int val)
{
    emit signalResetTimer();

    monthDayCheck(3);

    resetHour();
}
void SetDateTimeDialog::monthDayCheck(int type)
{
    int year = 0, month = 0, day = 0, maxDay = 0;
    int yearChanged = 0, monthChange = 0;
    QString str;
    QComboBox *comboDay = NULL;

    switch (timeFormat)
    {
        case DF_A_YYYY_MM_DD:
        case DF_B_YYYY_MM_DD:

            if(type == 3)
            {
                return;
            }

            year     = comboBoxTime_1->currentIndex() + ver_get_ref_year();
            month    = comboBoxTime_2->currentIndex();
            day      = comboBoxTime_3->currentIndex();
            comboDay = comboBoxTime_3;

            if(type == 1)
            {
                yearChanged = 1;
            }
            else
            {
                monthChange = 1;
            }

            break;

        case DF_A_MM_DD_YYYY:
        case DF_B_MM_DD_YYYY:

            if(type == 2)
            {
                return;
            }

            year     = comboBoxTime_3->currentIndex() + ver_get_ref_year();
            month    = comboBoxTime_1->currentIndex();
            day      = comboBoxTime_2->currentIndex();
            comboDay = comboBoxTime_2;

            if(type == 3)
            {
                yearChanged = 1;
            }
            else
            {
                monthChange = 1;
            }

            break;

        case DF_A_DD_MM_YYYY:
        case DF_B_DD_MM_YYYY:

            if(type == 1)
            {
                return;
            }

            year     = comboBoxTime_3->currentIndex() + ver_get_ref_year();
            month    = comboBoxTime_2->currentIndex();
            day      = comboBoxTime_1->currentIndex();
            comboDay = comboBoxTime_1;

            if(type == 3)
            {
                yearChanged = 1;
            }
            else
            {
                monthChange = 1;
            }

            break;
    }

    if(month == 1)
    {
        if((year %4) == 0)
        {
            if((year % 100) == 0)
            {
                if((year % 400) == 0)
                {
                    maxDay = 29;
                }
                else
                {
                    maxDay = 28;
                }
            }
            else
            {
                maxDay = 29;
            }
        }
        else
        {
            maxDay = 28;
        }
    }
    else if(month == 3 || month == 5 || month == 8 || month == 10) // 0 base 4, 6, 9, 11
    {
        maxDay = 30;
    }
    else
    {
        maxDay = 31;
    }

    if(comboDay->count() < maxDay)
    {
        int lastDay = comboDay->count();

        for(int i = lastDay; i < maxDay; i++)
        {
            str = tr("Day: %1").arg(i+1);
            comboDay->addItem(str);
        }

    }
    else if(comboDay->count() > maxDay)
    {
        int lastDay = comboDay->count();

        for(int i = maxDay; i < lastDay; i++)
        {
            //str = tr("%1").arg(i);
            comboDay->removeItem(maxDay);
        }
    }
}
void SetDateTimeDialog::changeFocusedItemValue(int isPlus)
{
    int curVal = 0;
    QComboBox *combo = NULL;

    if(comboBoxTimeZone->hasFocus())
    {
        combo = comboBoxTimeZone;
    }
    else if(comboBoxTime_1->hasFocus())
    {
        combo = comboBoxTime_1;
    }
    else if(comboBoxTime_2->hasFocus())
    {
        combo = comboBoxTime_2;
    }
    else if(comboBoxTime_3->hasFocus())
    {
        combo = comboBoxTime_3;
    }
    else if(comboBoxTime_4->hasFocus())
    {
        combo = comboBoxTime_4;
    }
    else if(comboBoxTime_5->hasFocus())
    {
        combo = comboBoxTime_5;
    }
    else if(comboBoxTime_6->hasFocus())
    {
        combo = comboBoxTime_6;
    }

    if(combo)
    {
        curVal = combo->currentIndex();

        if(isPlus)
        {
            if(++curVal >= combo->count())
            {
                curVal = 0;
            }
        }
        else
        {
            if(--curVal < 0)
            {
                curVal = combo->count() - 1;
            }
        }

        combo->setCurrentIndex(curVal);
    }
}
void SetDateTimeDialog::on_comboBoxBeginMonth_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxBeginWeek_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxBeginDay_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxBeginHour_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxEndMonth_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxEndWeek_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxEndDay_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxEndHour_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxTime_4_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxTime_5_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_comboBoxTime_6_currentIndexChanged(int index)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::on_buttonBox_accepted()
{
    emit signalResetTimer();
    this->accept();
}
void SetDateTimeDialog::on_buttonBox_rejected()
{
    emit signalResetTimer();
    this->reject();
}
void SetDateTimeDialog::checkTimezone()
{
    int timezone = 0;

    if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -12:00") == 0)
    {
        timezone =  0;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -11:00") == 0)
    {
        timezone =  1;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -10:00") == 0)
    {
        timezone =  2;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -9:00" ) == 0)
    {
        timezone =  3;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -8:00" ) == 0)
    {
        timezone =  4;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -7:00" ) == 0)
    {
        timezone =  5;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -6:00" ) == 0)
    {
        timezone =  6;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -5:00" ) == 0)
    {
        timezone =  7;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -4:30" ) == 0)
    {
        timezone =  8;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -4:00" ) == 0)
    {
        timezone =  9;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -3:30" ) == 0)
    {
        timezone = 10;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -3:00" ) == 0)
    {
        timezone = 11;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -2:00" ) == 0)
    {
        timezone = 12;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT -1:00" ) == 0)
    {
        timezone = 13;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +0:00" ) == 0)
    {
        timezone = 14;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +1:00" ) == 0)
    {
        timezone = 15;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +2:00" ) == 0)
    {
        timezone = 16;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +3:00" ) == 0)
    {
        timezone = 17;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +3:30" ) == 0)
    {
        timezone = 18;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +4:00" ) == 0)
    {
        timezone = 19;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +4:30" ) == 0)
    {
        timezone = 20;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +5:00" ) == 0)
    {
        timezone = 21;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +5:30" ) == 0)
    {
        timezone = 22;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +5:45" ) == 0)
    {
        timezone = 23;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +6:00" ) == 0)
    {
        timezone = 24;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +6:30" ) == 0)
    {
        timezone = 25;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +7:00" ) == 0)
    {
        timezone = 26;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +8:00" ) == 0)
    {
        timezone = 27;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +9:00" ) == 0)
    {
        timezone = 28;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +9:30" ) == 0)
    {
        timezone = 29;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +10:00") == 0)
    {
        timezone = 30;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +11:00") == 0)
    {
        timezone = 31;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +12:00") == 0)
    {
        timezone = 32;
    }
    else if(utils_cfg_cmp_item(SystemCfg.time_zone, "GMT +13:00") == 0)
    {
        timezone = 33;
    }

    comboBoxTimeZone->setCurrentIndex(timezone);
}
void SetDateTimeDialog::setTimezone()
{
    int val;

    val = comboBoxTimeZone->currentIndex();

    switch (val)
    {
        case  0: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -12:00"); break;
        case  1: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -11:00"); break;
        case  2: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -10:00"); break;
        case  3: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -9:00" ); break;
        case  4: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -8:00" ); break;
        case  5: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -7:00" ); break;
        case  6: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -6:00" ); break;
        case  7: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -5:00" ); break;
        case  8: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -4:30" ); break;
        case  9: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -4:00" ); break;
        case 10: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -3:30" ); break;
        case 11: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -3:00" ); break;
        case 12: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -2:00" ); break;
        case 13: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT -1:00" ); break;
        case 14: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +0:00" ); break;
        case 15: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +1:00" ); break;
        case 16: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +2:00" ); break;
        case 17: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +3:00" ); break;
        case 18: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +3:30" ); break;
        case 19: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +4:00" ); break;
        case 20: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +4:30" ); break;
        case 21: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +5:00" ); break;
        case 22: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +5:30" ); break;
        case 23: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +5:45" ); break;
        case 24: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +6:00" ); break;
        case 25: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +6:30" ); break;
        case 26: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +7:00" ); break;
        case 27: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +8:00" ); break;
        case 28: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +9:00" ); break;
        case 29: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +9:30" ); break;
        case 30: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +10:00"); break;
        case 31: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +11:00"); break;
        case 32: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +12:00"); break;
        case 33: utils_cfg_cpy_item(SystemCfg.time_zone, "GMT +13:00"); break;
        default:                                                        break;
    }
}
void SetDateTimeDialog::onButtonTimeFormat()
{
    switch(indexTimeFormat)
    {
        case 0:

            buttonTimeFormat->setText(tr("Time Format\n12 Hour"));
            utils_cfg_cpy_item(SystemCfg.time_format, "12HOUR");
            indexTimeFormat = 1;

            break;

        case 1:

            buttonTimeFormat->setText(tr("Time Format\n24 Hour"));
            utils_cfg_cpy_item(SystemCfg.time_format, "24HOUR");
            indexTimeFormat = 0;

            break;
    }

}
void SetDateTimeDialog::onButtonGpsSync()
{
    switch(indexGpsSync)
    {
        case 0:

            buttonGpsSync->setText(tr("GPS Synchronization\nOff"));
            utils_cfg_cpy_item(SystemCfg.gps_sync, "OFF");
            indexGpsSync = 1;

            break;

        case 1:

            buttonGpsSync->setText(tr("GPS Synchronization\nOn"));
            utils_cfg_cpy_item(SystemCfg.gps_sync, "ON");
            indexGpsSync = 0;

            break;
    }
}
bool SetDateTimeDialog::eventFilter(QObject *obj, QEvent *event)
{
    if((obj==comboBoxTimeZone || obj==comboBoxTime_1 || obj==comboBoxTime_2 || obj==comboBoxTime_3 ||
        obj==comboBoxTime_4   || obj==comboBoxTime_5 || obj==comboBoxTime_6) && (event->type()==QEvent::FocusOut))
    {
        isKeyLock=false;
    }
    return QWidget::eventFilter(obj, event);
}
