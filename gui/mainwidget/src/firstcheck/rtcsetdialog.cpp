#include <QtGui>
#include "rtcsetdialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

RtcSetDialog::RtcSetDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    labelRtcTitle->setStyleSheet("font:50px;background-color:rgb(50,57,83);color:white");
    labelRtcTitle->setAlignment(Qt::AlignCenter);

    labelRtcStatus->setStyleSheet("font:40px;color:white");
    labelRtcStatus->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    label->setStyleSheet("font:40px;color:white");

#if 1 //yjsin [18/01/05] if text is long, change font size
    if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
    {
        labelRtcStatus->setStyleSheet("font:35px;color:white");
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        labelRtcStatus->setStyleSheet("font:48px;color:white");
        buttonSetRestart->setGeometry(25,490,790,91);
    }
#endif

    dateTimeRtc->setDisplayFormat("yyyy/MM/dd hh:mm:ss");
    dateTimeRtc->setDateTime(QDateTime::currentDateTime());
    dateTimeRtc->setAlignment(Qt::AlignCenter);
    dateTimeRtc->setDateRange(QDate(ver_get_ref_year(),1,1),QDate(MAX_YEAR-1,12,31));
    dateTimeRtc->setStyleSheet("QDateTimeEdit {font:56px; selection-color:white; selection-background-color:rgb(152,14,69);}");
    dateTimeRtc->setWrapping(true);
    dateTimeRtc->installEventFilter(this);

    buttonSetRestart->setStyleSheet("QPushButton{font-size:48px;background-color:rgb(67,74,86);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}QPushButton:disabled{color:gray;}");

    dateTimeRtc->setFocus();

    isKeyLock = false;
    tOld      = dateTimeRtc->dateTime().toTime_t();

    connect(buttonSetRestart, SIGNAL(released()), this, SLOT(accept()));

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateStatus()));
    updateTimer->start(1000);
}
RtcSetDialog::~RtcSetDialog()
{
}
void RtcSetDialog::GetTime(time_t *time)
{
    *time = dateTimeRtc->dateTime().toTime_t();
}
void RtcSetDialog::onUpdateStatus(void)
{
    time_t tNow = dateTimeRtc->dateTime().toTime_t();

    if(tOld != tNow)
    {
        qDebug("RTC Beep Off");

        appmgr_set_beep_duration(0);

        updateTimer->stop();

        if(updateTimer)
        {
            delete updateTimer;
            updateTimer = NULL;
        }

    }
}
bool RtcSetDialog::eventFilter(QObject *obj, QEvent *event)
{
    if((obj==dateTimeRtc) && (event->type()==QEvent::FocusOut))
    {
        isKeyLock=false;
    }

    return QDialog::eventFilter(obj, event);
}
void RtcSetDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

            if(dateTimeRtc->hasFocus() && isKeyLock)
            {
                dateTimeRtc->stepUp();
            }
            else if(dateTimeRtc->hasFocus())
            {
                buttonSetRestart->setFocus();
            }
            else if(buttonSetRestart->hasFocus())
            {
                dateTimeRtc->setFocus();
            }

            return;

        case Qt::Key_Down:

            if(dateTimeRtc->hasFocus() && isKeyLock)
            {
                dateTimeRtc->stepDown();
            }
            else if(dateTimeRtc->hasFocus())
            {
                buttonSetRestart->setFocus();
            }
            else if(buttonSetRestart->hasFocus())
            {
                dateTimeRtc->setFocus();
            }

            return;

        case Qt::Key_Left:

            if(dateTimeRtc->hasFocus() && isKeyLock)
            {
                switch(dateTimeRtc->currentSectionIndex())
                {
                    case 0: { dateTimeRtc->setSelectedSection(QDateTimeEdit::SecondSection);         break; }
                    case 1: { dateTimeRtc->setSelectedSection(QDateTimeEdit::YearSection);           break; }
                    case 2: { dateTimeRtc->setSelectedSection(QDateTimeEdit::MonthSection);          break; }
                    case 3: { dateTimeRtc->setSelectedSection(QDateTimeEdit::DaySection);            break; }
                    case 4: { dateTimeRtc->setSelectedSection(QDateTimeEdit::HourSection);           break; }
                    case 5: { dateTimeRtc->setSelectedSection(QDateTimeEdit::MinuteSection);         break; }
                }
            }

            return;

        case Qt::Key_Right:

            if(dateTimeRtc->hasFocus() && isKeyLock)
            {
                switch(dateTimeRtc->currentSectionIndex())
                {
                    case 0: { dateTimeRtc->setSelectedSection(QDateTimeEdit::MonthSection);          break; }
                    case 1: { dateTimeRtc->setSelectedSection(QDateTimeEdit::DaySection);            break; }
                    case 2: { dateTimeRtc->setSelectedSection(QDateTimeEdit::HourSection);           break; }
                    case 3: { dateTimeRtc->setSelectedSection(QDateTimeEdit::MinuteSection);         break; }
                    case 4: { dateTimeRtc->setSelectedSection(QDateTimeEdit::SecondSection);         break; }
                    case 5: { dateTimeRtc->setSelectedSection(QDateTimeEdit::YearSection);           break; }
                }
            }

            return;

        case Qt::Key_Enter:

            if(dateTimeRtc->hasFocus())
            {
                isKeyLock = true;
            }
            else if(buttonSetRestart->hasFocus())
            {
                QDialog::accept();
            }

            return;

        case Qt::Key_Escape:

            if(dateTimeRtc->hasFocus())
            {
                isKeyLock = false;
            }
            else
            {
                QDialog::accept();
            }

            return;

        default:

            QDialog::accept();

            return;
    }

    QDialog::keyPressEvent(event);
}
