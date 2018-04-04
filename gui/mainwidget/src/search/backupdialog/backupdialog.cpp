#include <QtGui>
#include "backupdialog.h"
#include "main/mainglobal.h"

BackupDialog::BackupDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    setAutoFillBackground(true);

    progressBarBackup->setValue(0);
    progressBarBackup->setFormat(tr(""));
    progressBarBackup->setAlignment(Qt::AlignCenter);
    progressBarBackup->setStyleSheet("QProgressBar {font:40px;color:white;}");

    labelStart->setStyleSheet("font:40px;color:white");
    labelStart->setAlignment(Qt::AlignCenter);

    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)    //12H
    {
        dateTimeStart->setDisplayFormat("yyyy/MM/dd hh:mm:ss AP");
        dateTimeStart->setStyleSheet("QDateTimeEdit {font:43px; selection-color:white; selection-background-color:rgb(152,14,69);}");
    }
    else                                                            // 24H
    {
        dateTimeStart->setDisplayFormat("yyyy/MM/dd hh:mm:ss");
        dateTimeStart->setStyleSheet("QDateTimeEdit {font:48px; selection-color:white; selection-background-color:rgb(152,14,69);}");

    }
    dateTimeStart->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dateTimeStart->setWrapping(true);
    dateTimeStart->installEventFilter(this);

#if 1 //yjsin [17/09/13] if text is long, change font size
    if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0 || utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0)
    {
        buttonBackup->setStyleSheet("font:39px");
    }
#endif

    labelEnd->setStyleSheet("font:40px;color:white");
    labelEnd->setAlignment(Qt::AlignCenter);

    connect(dateTimeStart, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(onInitialize(const QDateTime &)));
    connect(buttonEnd,     SIGNAL(clicked()),                          this, SLOT(onButtonEnd()));
    connect(buttonBackup,  SIGNAL(clicked()),                          this, SLOT(onButtonBackup()));
    connect(buttonClose,   SIGNAL(clicked()),                          this, SLOT(onButtonClose()));

    frame->setGeometry(4, 4, size().width()-8, size().height()-8);

    backupTimer    = NULL;
    pBackupContext = NULL;
    flagPrepare    = 0;
    indexEnd       = 1;
    isKeyLock      = false;
}

void BackupDialog::updateBackupDialog()
{
    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)    //12H
    {
        dateTimeStart->setDisplayFormat("yyyy/MM/dd hh:mm:ss AP");
        dateTimeStart->setStyleSheet("QDateTimeEdit {font:43px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        dateTimeStart->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else                                                            // 24H
    {
        dateTimeStart->setDisplayFormat("yyyy/MM/dd hh:mm:ss");
        dateTimeStart->setStyleSheet("QDateTimeEdit {font:48px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        dateTimeStart->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

BackupDialog::~BackupDialog()
{
}
void BackupDialog::onInitialize(const QDateTime &datetime)
{
    qDebug() << __func__ << ": " << datetime;
    progressBarBackup->setValue(0);

    if(isEventSearch)
    {
#if 1 // jungyver [17/07/15]
        progressBarBackup->setFormat(tr("Insert a USB memory."));
#else
        progressBarBackup->setFormat(tr("Please insert a USB memory."));
#endif
    }
    else
    {
#if 1 // jungyver [17/07/15]
        progressBarBackup->setFormat(tr("Insert a USB memory and Select time."));
#else
        progressBarBackup->setFormat(tr("Please insert a USB memory and Select time."));
#endif
    }
}
void BackupDialog::onButtonEnd()
{
    if(indexEnd >= 10)
    {
        indexEnd = 0;
    }

         if(indexEnd >= 0 && indexEnd <= 2) { indexEnd++;    }
    else if(indexEnd == 3)                  { indexEnd = 5;  }
    else if(indexEnd == 5)                  { indexEnd = 10; }

    switch(indexEnd)
    {
        case  1: { buttonEnd->setText(tr( "1 minute"));  } break;
        case  2: { buttonEnd->setText(tr( "2 minutes")); } break;
        case  3: { buttonEnd->setText(tr( "3 minutes")); } break;
        case  4: { buttonEnd->setText(tr( "4 minutes")); } break;
        case  5: { buttonEnd->setText(tr( "5 minutes")); } break;
        case  6: { buttonEnd->setText(tr( "6 minutes")); } break;
        case  7: { buttonEnd->setText(tr( "7 minutes")); } break;
        case  8: { buttonEnd->setText(tr( "8 minutes")); } break;
        case  9: { buttonEnd->setText(tr( "9 minutes")); } break;
        case 10: { buttonEnd->setText(tr("10 minutes")); } break;
    }

    onInitialize(dateTimeStart->dateTime());
}
void BackupDialog::onButtonBackup()
{
    dateTimeStart->setEnabled(false);
    buttonEnd->setEnabled(false);
    buttonBackup->setEnabled(false);
    buttonClose->setEnabled(false);

    pBackupContext->deviceFreeMb      = 0;
    pBackupContext->mediaBytes        = 0;
    pBackupContext->indexBytes        = 0;
    pBackupContext->eDevice           = AIF_BACKUP_DEVICE_USB;
    pBackupContext->eType             = AIF_BACKUP_TYPE_PLAYBACK_VIDEO_AVI;
    pBackupContext->split1            = 1;
    pBackupContext->channel           = 0;
    pBackupContext->dls               = 0;
    pBackupContext->channelMask       = 0xf;

    if(isEventSearch)
    {
        pBackupContext->timestampPbStart  = eventBackupStartTime;
        pBackupContext->timestampPbEnd    = eventBackupEndTime;
    }
    else
    {
        pBackupContext->timestampPbStart  = QDateTime(dateTimeStart->dateTime()).toTime_t();
        pBackupContext->timestampPbEnd    = QDateTime(dateTimeStart->dateTime().addSecs((60*indexEnd)+2)).toTime_t();
    }

    pBackupContext->progressEventQid  = QUEUE_QT_CORE;
    pBackupContext->progressEventType = Send_QT_BACKUP_MEDIA;
    pBackupContext->timestampNow      = time(NULL);
    pBackupContext->calculation       = 0;
    BackupTimer();
    (void)aif_backup_start(pBackupContext);
}
void BackupDialog::onButtonClose()
{
    if(pBackupContext)
    {
        free(pBackupContext);
        pBackupContext = NULL;
    }

    if(backupTimer)
    {
        backupTimer->stop();
        delete backupTimer; backupTimer = NULL;
    }

    if(flagPrepare)
    {
        flagPrepare = 0;
    }

    close();
}
void BackupDialog::setCaptureMode(int type, int ch, int split, time_t pbTime)
{
    isKeyLock = false;

    if(pBackupContext == NULL)
    {
        pBackupContext = (aif_backup_context_t *)malloc(sizeof(aif_backup_context_t));
        if(pBackupContext == NULL)
        {
            qDebug("%s, Error: Fail malloc", __func__);
            return;
        }
    }

    if(isEventSearch)
    {
        indexEnd = 0;
        onInitialize(QDateTime::fromTime_t(eventBackupStartTime));
        dateTimeStart->setDateTime(QDateTime::fromTime_t(eventBackupStartTime));
        QString str = QString("%1 %2").arg(QString::number((eventBackupEndTime-eventBackupStartTime)-2), tr("seconds"));
        buttonEnd->setText(str);
        dateTimeStart->setEnabled(false);
        buttonEnd->setEnabled(false);
        buttonBackup->setFocus();
    }
    else
    {
        dateTimeStart->setEnabled(true);
        buttonEnd->setEnabled(true);
        indexEnd = 1;
        buttonEnd->setText(tr("1 minute"));
        onInitialize(QDateTime::fromTime_t(pbTime));
        dateTimeStart->setDateTime(QDateTime::fromTime_t(pbTime));
        dateTimeStart->setFocus();
    }
}
void BackupDialog::BackupTimer()
{
    if(!backupTimer)
    {
        backupTimer  = new QTimer(this);
    }

    connect(backupTimer, SIGNAL(timeout()), this, SLOT(updateBackupProgress(tmp_msg, tmp_progress)));
    backupTimer->start(100);
}
void BackupDialog::updateBackupProgress(int msg, int progress)
{
    static int oldStatus = -1, currentChannel = -1;
    qDebug("\t %s(), msg[%d], progress[%d]", __func__, msg, progress);

    if(msg >= AIF_BACKUP_CHANNEL_0 && msg <= AIF_BACKUP_CHANNEL_15)
    {
        currentChannel = msg - AIF_BACKUP_CHANNEL_0 + 1;
    }

    tmp_msg      = msg;
    tmp_progress = progress;

    if(msg != AIF_BACKUP_FAILED && msg != AIF_BACKUP_END && msg != AIF_BACKUP_START)
    {
        qDebug("\t %s() %d, msg[%d], progress[%d]", __func__, __LINE__, oldStatus, progress);
        oldStatus = msg;
    }

    if(progress >= 0 && progress <= 100)
    {
        progressBarBackup->setValue(progress);
        QString str = QString("%1%2%3%4%").arg(tr("CAM"), QString::number(currentChannel), " : ", QString::number(progress));
        progressBarBackup->setFormat(str);
    }

    if(msg == AIF_BACKUP_FAILED)
    {
        qDebug("\t %s() %d, msg[%d], progress[%d]", __func__, __LINE__, oldStatus, progress);

        switch(oldStatus)
        {
            case AIF_BACKUP_DEVICE_READY:
            {
                progressBarBackup->setFormat(tr("Not found USB memory."));

                if(backupTimer)
                {
                    backupTimer->stop();
                    delete backupTimer;
                    backupTimer = NULL;
                }

                if(flagPrepare)
                {
                    flagPrepare = 0;
                }

                if(!isEventSearch)
                {
                    dateTimeStart->setEnabled(true);
                    buttonEnd->setEnabled(true);
                }

                buttonBackup->setEnabled(true);
                buttonClose->setEnabled(true);
                buttonClose->setFocus();

                break;
            }
            case AIF_BACKUP_MEDIA_INFO:
            {
                QString str = QString("%1%2%3%4").arg(tr("CAM"), QString::number(currentChannel), " : ", tr("No Data"));
                progressBarBackup->setFormat(str);

                break;
            }
            case AIF_BACKUP_SIZE_CHECK:
            {
                progressBarBackup->setFormat(tr("Lack of USB Capacity"));

                break;
            }
        }
    }
    else if(msg == AIF_BACKUP_START)
    {
        progressBarBackup->setFormat(tr("Don't remove USB memory."));
    }
    else if(msg == AIF_BACKUP_CHANNEL_CLEAR)
    {
        if(flagPrepare == 0)
        {
            progressBarBackup->setFormat(tr("Preparing..."));
            flagPrepare++;
        }
        else
        {
            flagPrepare = 0;
        }
    }
    else if(msg == AIF_BACKUP_END)
    {
        progressBarBackup->setFormat(tr("Completion"));

        if(backupTimer)
        {
            backupTimer->stop();
            delete backupTimer;
            backupTimer = NULL;
        }

        if(!isEventSearch)
        {
            dateTimeStart->setEnabled(true);
            buttonEnd->setEnabled(true);
        }

        buttonBackup->setEnabled(true);
        buttonClose->setEnabled(true);
        buttonClose->setFocus();
    }
}
bool BackupDialog::eventFilter(QObject *obj, QEvent *event)
{
    if((obj==dateTimeStart) && (event->type()==QEvent::FocusOut))
    {
        isKeyLock=false;
    }

    return QDialog::eventFilter(obj, event);
}
void BackupDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if(dateTimeStart->hasFocus() && isKeyLock)                       { dateTimeStart->stepUp();    }
            else if(dateTimeStart->hasFocus())                               { buttonBackup->setFocus();   }
            else if(buttonBackup->hasFocus() && buttonEnd->isEnabled())      { buttonEnd->setFocus();      }
            else if(buttonEnd->hasFocus()    && dateTimeStart->isEnabled())  { dateTimeStart->setFocus();  }
            else if(buttonClose->hasFocus()  && buttonEnd->isEnabled())      { buttonEnd->setFocus();      }

            break;
        }
        case Qt::Key_Down:
        {
            if(dateTimeStart->hasFocus() && isKeyLock)                       { dateTimeStart->stepDown();  }
            else if(dateTimeStart->hasFocus() && buttonEnd->isEnabled())     { buttonEnd->setFocus();      }
            else if(buttonEnd->hasFocus())                                   { buttonBackup->setFocus();   }
            else if(buttonBackup->hasFocus()  && dateTimeStart->isEnabled()) { dateTimeStart->setFocus();  }
            else if(buttonClose->hasFocus()   && dateTimeStart->isEnabled()) { dateTimeStart->setFocus();  }

            break;
        }
        case Qt::Key_Left:
        {
            if(dateTimeStart->hasFocus() && isKeyLock)
            {
                switch(dateTimeStart->currentSectionIndex())
                {
                    case 0: { dateTimeStart->setSelectedSection(QDateTimeEdit::SecondSection);      break; }
                    case 1: { dateTimeStart->setSelectedSection(QDateTimeEdit::YearSection);        break; }
                    case 2: { dateTimeStart->setSelectedSection(QDateTimeEdit::MonthSection);       break; }
                    case 3: { dateTimeStart->setSelectedSection(QDateTimeEdit::DaySection);         break; }
                    case 4: { dateTimeStart->setSelectedSection(QDateTimeEdit::HourSection);        break; }
                    case 5: { dateTimeStart->setSelectedSection(QDateTimeEdit::MinuteSection);      break; }
                }
            }
            else if(buttonBackup->hasFocus())                                { buttonClose->setFocus();    }
            else if(buttonClose->hasFocus())                                 { buttonBackup->setFocus();   }

            break;
        }
        case Qt::Key_Right:
        {
            if(dateTimeStart->hasFocus() && isKeyLock)
            {
                switch(dateTimeStart->currentSectionIndex())
                {
                    case 0: { dateTimeStart->setSelectedSection(QDateTimeEdit::MonthSection);       break; }
                    case 1: { dateTimeStart->setSelectedSection(QDateTimeEdit::DaySection);         break; }
                    case 2: { dateTimeStart->setSelectedSection(QDateTimeEdit::HourSection);        break; }
                    case 3: { dateTimeStart->setSelectedSection(QDateTimeEdit::MinuteSection);      break; }
                    case 4: { dateTimeStart->setSelectedSection(QDateTimeEdit::SecondSection);      break; }
                    case 5: { dateTimeStart->setSelectedSection(QDateTimeEdit::YearSection);        break; }
                }
            }
            else if(buttonBackup->hasFocus())                                { buttonClose->setFocus();    }
            else if(buttonClose->hasFocus())                                 { buttonBackup->setFocus();   }

            break;
        }
        case Qt::Key_Enter:
        {
                 if(dateTimeStart->hasFocus())                               { isKeyLock = true;           }
            else if(buttonEnd->hasFocus())                                   { onButtonEnd();              }
            else if(buttonBackup->hasFocus())                                { onButtonBackup();           }
            else if(buttonClose->hasFocus())                                 { onButtonClose();            }

            break;
        }
        case Qt::Key_Escape:
        {
            if(isKeyLock)                                                    { isKeyLock = false;          }
            else                                                             { onButtonClose();            }

            break;
        }
        default:
        {
            break;;
        }
    }

    return;
}
