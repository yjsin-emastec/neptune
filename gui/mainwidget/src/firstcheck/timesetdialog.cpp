#include <QtGui>
#include "timesetdialog.h"
#include "main/mainglobal.h"
#include "main/languagedefine.h"
#include "dev/Ver.h"

TimeSetDialog::TimeSetDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::TimeSetDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelTimeTitle = ui720.labelTimeTitle;
        labelTimeStatus = ui720.labelTimeStatus;
        labelFirstTime1 = ui720.labelFirstTime1;
        labelFirstTime2 = ui720.labelFirstTime2;
        labelLastTime1 = ui720.labelLastTime1;
        labelLastTime2 = ui720.labelLastTime2;
        labelSystemTime1 = ui720.labelSystemTime1;
        labelSystemTime2 = ui720.labelSystemTime2;
        dateTimeSystem = ui720.dateTimeSystem;
        buttonDeleteData = ui720.buttonDeleteData;
        buttonSetTime = ui720.buttonSetTime;

        labelTimeTitle->setStyleSheet("font:50px;background-color:rgb(50,57,83);color:white");
        labelTimeStatus->setStyleSheet("font:44px;color:white;padding-left:5px;");
        labelFirstTime1->setStyleSheet("font:44px;background-color:rgb(50,57,83);color:white");
        labelFirstTime2->setStyleSheet("font:44px;color:white");
        labelLastTime1->setStyleSheet("font:44px;background-color:rgb(50,57,83);color:white");
        labelLastTime2->setStyleSheet("font:44px;color:white");
        labelSystemTime1->setStyleSheet("font:44px;background-color:rgb(50,57,83);color:white");
        labelSystemTime2->setStyleSheet("font:44px;color:white");

        dateTimeSystem->setStyleSheet("QDateTimeEdit {font:44px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        buttonDeleteData->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(67,74,86);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}QPushButton:disabled{color:gray;}");
        buttonSetTime->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(67,74,86);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}QPushButton:disabled{color:gray;}");
    }
    else
    {
        Ui::TimeSetDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelTimeTitle = ui1080.labelTimeTitle;
        labelTimeStatus = ui1080.labelTimeStatus;
        labelFirstTime1 = ui1080.labelFirstTime1;
        labelFirstTime2 = ui1080.labelFirstTime2;
        labelLastTime1 = ui1080.labelLastTime1;
        labelLastTime2 = ui1080.labelLastTime2;
        labelSystemTime1 = ui1080.labelSystemTime1;
        labelSystemTime2 = ui1080.labelSystemTime2;
        dateTimeSystem = ui1080.dateTimeSystem;
        buttonDeleteData = ui1080.buttonDeleteData;
        buttonSetTime = ui1080.buttonSetTime;

        labelTimeTitle->setStyleSheet("font:80px;background-color:rgb(50,57,83);color:white");
        labelTimeStatus->setStyleSheet("font:65px;color:white;padding-left:30px;");
        labelFirstTime1->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white");
        labelFirstTime2->setStyleSheet("font:65px;color:white");
        labelLastTime1->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white");
        labelLastTime2->setStyleSheet("font:65px;color:white");
        labelSystemTime1->setStyleSheet("font:65px;background-color:rgb(50,57,83);color:white");
        labelSystemTime2->setStyleSheet("font:65px;color:white");

        dateTimeSystem->setStyleSheet("QDateTimeEdit {font:65px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        buttonDeleteData->setStyleSheet("QPushButton{font-size:65px;background-color:rgb(67,74,86);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}QPushButton:disabled{color:gray;}");
        buttonSetTime->setStyleSheet("QPushButton{font-size:65px;background-color:rgb(67,74,86);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}QPushButton:disabled{color:gray;}");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)     { dateTimeSystem->setDisplayFormat("yyyy/MM/dd hh:mm:ss AP"); }    //12H
    else                                                             { dateTimeSystem->setDisplayFormat("yyyy/MM/dd hh:mm:ss");    }    //24H

    dateTimeSystem->setDateTime(QDateTime::currentDateTime());
    dateTimeSystem->setDateRange(QDate(ver_get_ref_year(),1,1),QDate(MAX_YEAR-1,12,31));
    dateTimeSystem->setWrapping(true);
    dateTimeSystem->installEventFilter(this);
    dateTimeSystem->setContextMenuPolicy(Qt::NoContextMenu);

    connect(buttonDeleteData, SIGNAL(released()), this, SLOT(onButtonDeleteData()));
    connect(buttonSetTime,    SIGNAL(released()), this, SLOT(onButtonSetTime()));

    tOld = dateTimeSystem->dateTime().toTime_t();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateStatus()));
    updateTimer->start(1000);

    dateTimeSystem->setFocus();
    isKeyLock = false;
}
TimeSetDialog::~TimeSetDialog()
{
}
void TimeSetDialog::onUpdateStatus(void)
{
    time_t tNow = dateTimeSystem->dateTime().toTime_t();

    if(tOld != tNow)
    {
        qDebug("TimeSetDialog Beep Off");

        appmgr_set_beep_duration(0);

        updateTimer->stop();

        if(updateTimer)
        {
            delete updateTimer;
            updateTimer = NULL;
        }
    }
}
void TimeSetDialog::DisplayRecordTime(void)
{
    QString strFirst, strLast;
    time_t tFirstRec = 0, tLastRec= 0;
    struct tm tmFirst, tmLast;
    char   FirstDate[30], LastDate[30];

    appmgr_search_get_first_rec_time(&tFirstRec);
    appmgr_search_get_last_rec_time(&tLastRec);

    qDebug("%s %d, First Time: %s, Last Time: %s \n", __func__, __LINE__, atime(tFirstRec), atime(tLastRec));
    appmgr_search_get_rec_start_end_time(&tFirstRec, &tLastRec);

    qDebug("%s %d, First Time: %s, Last Time: %s \n", __func__, __LINE__, atime(tFirstRec), atime(tLastRec));

    localtime_r(&tFirstRec, &tmFirst);
    localtime_r(&tLastRec, &tmLast);

    memset(FirstDate, 0, 30);
    memset(LastDate, 0, 30);

    char *AMPM = " ";
    int firstHour = tmFirst.tm_hour;
    int lastHour= tmLast.tm_hour;

    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)
    {
        if( tmFirst.tm_hour == 0 )          { firstHour=tmFirst.tm_hour+12;     AMPM=" AM"; }
        else if( tmFirst.tm_hour == 12 )    { firstHour=tmFirst.tm_hour;        AMPM=" PM"; }
        else if( tmFirst.tm_hour > 12 )     { firstHour=tmFirst.tm_hour-12;     AMPM=" PM"; }
        else                                { firstHour=tmFirst.tm_hour;        AMPM=" AM"; }

        if( tmLast.tm_hour == 0 )           { lastHour=tmLast.tm_hour+12;       AMPM=" AM"; }
        else if( tmLast.tm_hour == 12 )     { lastHour=tmLast.tm_hour;          AMPM=" PM"; }
        else if( tmLast.tm_hour > 12 )      { lastHour=tmLast.tm_hour-12;       AMPM=" PM"; }
        else                                { lastHour=tmLast.tm_hour;          AMPM=" AM"; }
    }

    sprintf(FirstDate, "%d/%02d/%02d %02d:%02d:%02d%s", tmFirst.tm_year+1900, tmFirst.tm_mon+1, tmFirst.tm_mday, firstHour, tmFirst.tm_min, tmFirst.tm_sec, AMPM);
    sprintf(LastDate,  "%d/%02d/%02d %02d:%02d:%02d%s", tmLast.tm_year+1900,  tmLast.tm_mon+1,  tmLast.tm_mday,  lastHour,  tmLast.tm_min,  tmLast.tm_sec,  AMPM);

    strFirst += QString::fromAscii(FirstDate);
    strLast  += QString::fromAscii(LastDate);

    QString first = QString("First Rec: %1").arg(QString::fromUtf8(FirstDate));
    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, first.toStdString().c_str());
    QString last  = QString("Last  Rec: %1").arg(QString::fromUtf8(LastDate));
    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, last.toStdString().c_str());

    labelFirstTime2->setText(strFirst);
    labelLastTime2->setText(strLast);
}
void TimeSetDialog::GetTime(time_t *time)
{
    *time = dateTimeSystem->dateTime().toTime_t();
}
void TimeSetDialog::Delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void TimeSetDialog::onButtonDeleteData(void)
{
    labelTimeStatus->setText(tr("%1\n%2").arg(tr("System is deleting data."),tr("Do not turn off system.")));
    dateTimeSystem->clearFocus();
    buttonDeleteData->clearFocus();
    buttonSetTime->clearFocus();
    dateTimeSystem->setEnabled(false);
    buttonDeleteData->setEnabled(false);
    buttonSetTime->setEnabled(false);

    tOld = 0;

    this->Delay(10000);

    appmgr_disk_file_deletion(0, 0, 1);

    for(;;)
    {
        if(appmgr_get_boot_fs_state() == FS_TIME_MISMATCH_DONE)
        {
            qDebug("\n\t Time Mismatch ... Done");
            break;
        }

        this->Delay(1000);
    }

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Deletion Completion");

    labelTimeStatus->setText(tr("%1").arg(tr("Completion")));

    this->Delay(3000);

    QDialog::accept();
}
void TimeSetDialog::onButtonSetTime(void)
{
    time_t tNow = 0, tFirstRec = 0, tLastRect= 0;
    int val = LANGUAGE_ENGLISH;

    dateTimeSystem->setEnabled(false);
    buttonDeleteData->setEnabled(false);
    buttonSetTime->setEnabled(false);

    tNow = dateTimeSystem->dateTime().toTime_t();

    appmgr_search_get_rec_start_end_time(&tFirstRec, &tLastRect);

    qDebug("Current Time: %s, First Time: %s, Last Time: %s \n", atime(tNow), atime(tFirstRec), atime(tLastRect));

    tOld = 0;

    if(tNow > tLastRect)
    {
        system_property_t SystemCfg;
        aif_system_get_property(&SystemCfg);

        if(utils_cfg_cmp_item(SystemCfg.language, "ENGLISH") == 0)
        {
            val = LANGUAGE_ENGLISH;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "KOREAN")  == 0)
        {
            val = LANGUAGE_KOREAN;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH")  == 0)
        {
            val = LANGUAGE_SPANISH;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH")  == 0)
        {
            val = LANGUAGE_FRENCH;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN")  == 0)
        {
            val = LANGUAGE_ITALIAN;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE")  == 0)
        {
            val = LANGUAGE_PORTUGUESE;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE")  == 0)
        {
            val = LANGUAGE_JAPANESE;
        }
        else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN")  == 0)
        {
            val = LANGUAGE_GERMAN;
        }
        else
        {
            val = LANGUAGE_ENGLISH;
        }

        appmgr_firstrun_setting(tNow, val);
        appmgr_disk_file_deletion(0, 0, 2);

        QString str = QString("Set %1 andThen Reboot").arg(QString::fromUtf8(atime(tNow)));
        appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, str.toStdString().c_str());

        for(;;)
        {
            if(appmgr_get_boot_fs_state() == FS_TIME_MISMATCH_DONE)
            {
                qDebug("\n\t Time Mismatch ... Done");
                break;
            }

            this->Delay(1000);
        }

        QDialog::accept();
    }
    else
    {
        labelTimeStatus->setText(tr("System Time must be later than record last time."));
        dateTimeSystem->setEnabled(true);
        buttonDeleteData->setEnabled(true);
        buttonSetTime->setEnabled(true);
        dateTimeSystem->setFocus();
    }
}
bool TimeSetDialog::eventFilter(QObject *obj, QEvent *event)
{
    if((obj==dateTimeSystem) && (event->type()==QEvent::FocusOut))
    {
        isKeyLock=false;
    }

    return QDialog::eventFilter(obj, event);
}
void TimeSetDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

            if(dateTimeSystem->hasFocus() && isKeyLock)
            {
                dateTimeSystem->stepUp();
            }
            else if(dateTimeSystem->hasFocus())
            {
                buttonSetTime->setFocus();
            }
            else if(buttonSetTime->hasFocus())
            {
                dateTimeSystem->setFocus();
            }
            else if(buttonDeleteData->hasFocus())
            {
                dateTimeSystem->setFocus();
            }

            return;

        case Qt::Key_Down:

            if(dateTimeSystem->hasFocus() && isKeyLock)
            {
                dateTimeSystem->stepDown();
            }
            else if(dateTimeSystem->hasFocus())
            {
                buttonSetTime->setFocus();
            }
            else if(buttonSetTime->hasFocus())
            {
                dateTimeSystem->setFocus();
            }
            else if(buttonDeleteData->hasFocus())
            {
                dateTimeSystem->setFocus();
            }

            return;

        case Qt::Key_Left:

            if(dateTimeSystem->hasFocus() && isKeyLock)
            {
                switch(dateTimeSystem->currentSectionIndex())
                {
                    case 0: { dateTimeSystem->setSelectedSection(QDateTimeEdit::SecondSection);         break; }
                    case 1: { dateTimeSystem->setSelectedSection(QDateTimeEdit::YearSection);           break; }
                    case 2: { dateTimeSystem->setSelectedSection(QDateTimeEdit::MonthSection);          break; }
                    case 3: { dateTimeSystem->setSelectedSection(QDateTimeEdit::DaySection);            break; }
                    case 4: { dateTimeSystem->setSelectedSection(QDateTimeEdit::HourSection);           break; }
                    case 5: { dateTimeSystem->setSelectedSection(QDateTimeEdit::MinuteSection);         break; }
                }
            }
            else if(buttonDeleteData->hasFocus())
            {
                buttonSetTime->setFocus();
            }
            else if(buttonSetTime->hasFocus())
            {
                buttonDeleteData->setFocus();
            }

            return;

        case Qt::Key_Right:

            if(dateTimeSystem->hasFocus() && isKeyLock)
            {
                switch(dateTimeSystem->currentSectionIndex())
                {
                    case 0: { dateTimeSystem->setSelectedSection(QDateTimeEdit::MonthSection);          break; }
                    case 1: { dateTimeSystem->setSelectedSection(QDateTimeEdit::DaySection);            break; }
                    case 2: { dateTimeSystem->setSelectedSection(QDateTimeEdit::HourSection);           break; }
                    case 3: { dateTimeSystem->setSelectedSection(QDateTimeEdit::MinuteSection);         break; }
                    case 4: { dateTimeSystem->setSelectedSection(QDateTimeEdit::SecondSection);         break; }
                    case 5: { dateTimeSystem->setSelectedSection(QDateTimeEdit::YearSection);           break; }
                }
            }
            else if(buttonDeleteData->hasFocus())
            {
                buttonSetTime->setFocus();
            }
            else if(buttonSetTime->hasFocus())
            {
                buttonDeleteData->setFocus();
            }

            return;

        case Qt::Key_Enter:

            if(dateTimeSystem->hasFocus() && isKeyLock)
            {
                isKeyLock = false;
            }
            else if(dateTimeSystem->hasFocus())
            {
                isKeyLock = true;
            }
            else if(buttonDeleteData->hasFocus())
            {
                onButtonDeleteData();
            }
            else if(buttonSetTime->hasFocus())
            {
                onButtonSetTime();
            }

            return;

        case Qt::Key_Escape:

            if(dateTimeSystem->hasFocus())
            {
                isKeyLock = false;
            }

            return;

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
