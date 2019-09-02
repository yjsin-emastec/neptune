#include <QtGui>
#include "setdatetimedialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

SetDateTimeDialog::SetDateTimeDialog(QWidget *parent, int dateFormat, cfg_dls_t *cfg)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::SetDateTimeDialog ui720;
        ui720.setupUi(this);

        layoutFrame = ui720.layoutFrame;

        buttonTimeFormat = ui720.buttonTimeFormat;
        buttonGpsSync = ui720.buttonGpsSync;
        buttonClose = ui720.buttonClose;
        buttonSave = ui720.buttonSave;

        comboBoxTimeZone = ui720.comboBoxTimeZone;
        dateTimeEdit = ui720.dateTimeEdit;

        buttonTimeFormat->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(50,57,83);color:white;} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonGpsSync->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(50,57,83);color:white;} QPushButton:focus{background-color:rgb(152,14,69);}");
        dateTimeEdit->setStyleSheet("QDateTimeEdit{font:50px; selection-color:white; selection-background-color:rgb(152,14,69);}");
    }
    else
    {
        Ui::SetDateTimeDialog1080p ui1080;
        ui1080.setupUi(this);

        layoutFrame = ui1080.layoutFrame;

        buttonTimeFormat = ui1080.buttonTimeFormat;
        buttonGpsSync = ui1080.buttonGpsSync;
        buttonClose = ui1080.buttonClose;
        buttonSave = ui1080.buttonSave;

        comboBoxTimeZone = ui1080.comboBoxTimeZone;
        dateTimeEdit = ui1080.dateTimeEdit;

        buttonTimeFormat->setStyleSheet("QPushButton{font-size:70px;background-color:rgb(50,57,83);color:white;} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonGpsSync->setStyleSheet("QPushButton{font-size:70px;background-color:rgb(50,57,83);color:white;} QPushButton:focus{background-color:rgb(152,14,69);}");
        dateTimeEdit->setStyleSheet("QDateTimeEdit{font:70px; selection-color:white; selection-background-color:rgb(152,14,69);}");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    layoutFrame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    setAutoFillBackground(true);

    msgBox = NULL;
    timeFormat = dateFormat;

    initComboBox();
    enableSetTime();

    connect(buttonTimeFormat, SIGNAL(clicked()), this, SLOT(onButtonTimeFormat()));
    connect(buttonGpsSync,    SIGNAL(clicked()), this, SLOT(onButtonGpsSync()));
    connect(buttonSave,       SIGNAL(clicked()), this, SLOT(onButtonSave()));
    connect(buttonClose,      SIGNAL(clicked()), this, SLOT(onButtonClose()));

    dateTimeEdit->setWrapping(true);
    dateTimeEdit->setContextMenuPolicy(Qt::NoContextMenu);
    dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss");

    dateTimeEdit->installEventFilter(this);
    comboBoxTimeZone->installEventFilter(this);

    buttonTimeFormat->setFocus();
    isKeyLock = false;
}
SetDateTimeDialog::~SetDateTimeDialog()
{
}

void SetDateTimeDialog::initComboBox()
{
    switch(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR"))
    {
        case 0:  { buttonTimeFormat->setText(tr("Time Format\n12 Hour")); infoTimeFormat = 1; break; }
        default: { buttonTimeFormat->setText(tr("Time Format\n24 Hour")); infoTimeFormat = 0; break; }
    }

    if(utils_cfg_cmp_item(SystemCfg.gps_sync, "OFF") == 0)
    {
        buttonGpsSync->setText(tr("GPS Synchronization\nOff"));
        infoGpsSync = 0;
    }
    else
    {
        buttonGpsSync->setText(tr("GPS Synchronization\nOn"));
        infoGpsSync = 1;
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

    checkTimeZone();

    dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    if( infoTimeFormat == 1 )
    {
        switch( timeFormat )
        {
            case DF_A_YYYY_MM_DD:
            case DF_B_YYYY_MM_DD:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss AP");
                break;
            case DF_A_MM_DD_YYYY:
            case DF_B_MM_DD_YYYY:
                dateTimeEdit->setDisplayFormat("MM.dd.yyyy. hh:mm:ss AP");
                break;
            case DF_A_DD_MM_YYYY:
            case DF_B_DD_MM_YYYY:
                dateTimeEdit->setDisplayFormat("dd.MM.yyyy. hh:mm:ss AP");
                break;
            default:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss AP");
                break;
        }
    }
    else
    {
        switch( timeFormat )
        {
            case DF_A_YYYY_MM_DD:
            case DF_B_YYYY_MM_DD:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss");
                break;
            case DF_A_MM_DD_YYYY:
            case DF_B_MM_DD_YYYY:
                dateTimeEdit->setDisplayFormat("MM.dd.yyyy. hh:mm:ss");
                break;
            case DF_A_DD_MM_YYYY:
            case DF_B_DD_MM_YYYY:
                dateTimeEdit->setDisplayFormat("dd.MM.yyyy. hh:mm:ss");
                break;
            default:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss");
                break;
        }
    }

    comboBoxTimeZone->setEnabled(infoGpsSync);
    dateTimeEdit->setDisabled(infoGpsSync);

    getChangedTime(&beforeChageTime);
}
void SetDateTimeDialog::checkTimeZone()
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
void SetDateTimeDialog::getChangedTime(time_t *newTime)
{
    struct tm when;

    when.tm_year = dateTimeEdit->dateTime().toString("yyyy").toInt() - 1900;
    when.tm_mon  = dateTimeEdit->dateTime().toString("MM").toInt() - 1;
    when.tm_mday = dateTimeEdit->dateTime().toString("dd").toInt();
    when.tm_hour = dateTimeEdit->dateTime().toString("hh").toInt();
    when.tm_min  = dateTimeEdit->dateTime().toString("mm").toInt();
    when.tm_sec  = dateTimeEdit->dateTime().toString("ss").toInt();

    *newTime = mktime(&when);
}
void SetDateTimeDialog::enableSetTime()
{
    QString str;
    time_t tFirstRec = 0, tLastRect = 0;
    struct tm tmLast;
    int diskNum = 0;
    char szDate[30];

    localtime_r(&tLastRect, &tmLast);
    memset(szDate, 0, 30);

    disk_used_info_t diskInfo[MAX_HDD_COUNT];
    memset(diskInfo, 0, sizeof(disk_used_info_t) * MAX_HDD_COUNT);
    diskNum = appmgr_get_disk_info(diskInfo);

    if(diskNum <= 0)
    {
        return;
    }

    qDebug() <<"\n\n\n\t hi";
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

    switch (DateFormat)
    {
        case 0:
        default : 	//YYYY/MM/DD
            sprintf(szDate, "%d/%02d/%02d %02d:%02d:%02d", tmLast.tm_year+1900, tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
            break;

        case 1:		//MM/DD/YYYY
            sprintf(szDate, "%02d/%02d/%d %02d:%02d:%02d", tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
            break;

        case 2:		//DD/MM/YYYY
            sprintf(szDate, "%02d/%02d/%d %02d:%02d:%02d", tmLast.tm_mday, tmLast.tm_mon+1, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
            break;

        case 3:		//YYYY-MM-DD
            sprintf(szDate, "%d-%02d-%02d %02d:%02d:%02d", tmLast.tm_year+1900, tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
            break;

        case 4:		//MM-DD-YYYY
            sprintf(szDate, "%02d-%02d-%d %02d:%02d:%02d", tmLast.tm_mon+1, tmLast.tm_mday, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
            break;

        case 5:		//DD-MM-YYYY
            sprintf(szDate, "%02d-%02d-%d %02d:%02d:%02d", tmLast.tm_mday, tmLast.tm_mon+1, tmLast.tm_year+1900, tmLast.tm_hour, tmLast.tm_min, tmLast.tm_sec);
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
}
void SetDateTimeDialog::onButtonTimeFormat()
{
    if( infoTimeFormat == 0 )
    {
        switch( timeFormat )
        {
            case DF_A_YYYY_MM_DD:
            case DF_B_YYYY_MM_DD:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss AP");
                break;

            case DF_A_MM_DD_YYYY:
            case DF_B_MM_DD_YYYY:
                dateTimeEdit->setDisplayFormat("MM.dd.yyyy. hh:mm:ss AP");
                break;

            case DF_A_DD_MM_YYYY:
            case DF_B_DD_MM_YYYY:
                dateTimeEdit->setDisplayFormat("dd.MM.yyyy. hh:mm:ss AP");
                break;

            default:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss AP");
                break;
        }

        buttonTimeFormat->setText(tr("Time Format\n12 Hour"));
        infoTimeFormat = 1;
    }
    else
    {
        switch( timeFormat )
        {
            case DF_A_YYYY_MM_DD:
            case DF_B_YYYY_MM_DD:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss");
                break;

            case DF_A_MM_DD_YYYY:
            case DF_B_MM_DD_YYYY:
                dateTimeEdit->setDisplayFormat("MM.dd.yyyy. hh:mm:ss");
                break;

            case DF_A_DD_MM_YYYY:
            case DF_B_DD_MM_YYYY:
                dateTimeEdit->setDisplayFormat("dd.MM.yyyy. hh:mm:ss");
                break;

            default:
                dateTimeEdit->setDisplayFormat("yyyy.MM.dd. hh:mm:ss");
                break;
        }

        buttonTimeFormat->setText(tr("Time Format\n24 Hour"));
        infoTimeFormat = 0;
    }
}
void SetDateTimeDialog::onButtonGpsSync()
{
    if( infoGpsSync == 0 )
    {
        buttonGpsSync->setText(tr("GPS Synchronization\nOn"));
        infoGpsSync = 1;
    }
    else
    {
        buttonGpsSync->setText(tr("GPS Synchronization\nOff"));
        infoGpsSync = 0;
    }

    comboBoxTimeZone->setEnabled(infoGpsSync);
    dateTimeEdit->setDisabled(infoGpsSync);

}

void SetDateTimeDialog::onButtonSave()
{
    if(infoTimeFormat == 1)
    {
        utils_cfg_cpy_item(SystemCfg.time_format, "12HOUR");
    }
    else
    {
        utils_cfg_cpy_item(SystemCfg.time_format, "24HOUR");
    }

    if(infoGpsSync == 0)
    {
        utils_cfg_cpy_item(SystemCfg.gps_sync, "OFF");
    }
    else
    {
        utils_cfg_cpy_item(SystemCfg.gps_sync, "ON");
    }

    saveTimeZone();

    accept();
}
void SetDateTimeDialog::onButtonClose()
{
    reject();
}
void SetDateTimeDialog::saveTimeZone()
{
    int val = comboBoxTimeZone->currentIndex();

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
void SetDateTimeDialog::getChangedConfig(time_t *newTime, cfg_dls_t *cfg)
{
    if( !cfg )
    {
        return;
    }

    time_t tmpTime;
    getChangedTime(&tmpTime);

    if( tmpTime == beforeChageTime)
    {
        *newTime = 0;
    }
    else
    {
        *newTime = tmpTime;
    }
}
bool SetDateTimeDialog::eventFilter(QObject *obj, QEvent *event)
{
    if( ((obj==dateTimeEdit) || (obj==comboBoxTimeZone)) && (event->type()==QEvent::FocusOut) )
    {
        isKeyLock=false;
    }

    return QWidget::eventFilter(obj, event);
}
