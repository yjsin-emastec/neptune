#include <QtGui>
#include "systemlogpage.h"
#include "main/mainglobal.h"
#include "main/mainwidget.h"
#include <Event.h>
#include "eventsortfilterproxymodel.h"
#include <QString>
#include "textmessagebox/textmessagedialog.h"
#include "functiondialog.h"

extern SYSTEM_LOG_DATA_S gSystemLog[SYSTEM_LOG_COUNT_PER_PAGE];

SystemLogPage::SystemLogPage(QWidget *parent)
    : QWidget(parent)
{
    if(mainHeight == 720)
    {
        Ui::SystemLogPage ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        maskFrame = ui720.maskFrame;
        buttonClose = ui720.buttonClose;
        buttonFunction = ui720.buttonFunction;
        buttonPageDn = ui720.buttonPageDn;
        buttonPageUp = ui720.buttonPageUp;
        buttonPrevious = ui720.buttonPrevious;
        buttonSearch = ui720.buttonSearch;
        labelClose = ui720.labelClose;
        labelFilter1 = ui720.labelFilter1;
        labelFilter2 = ui720.labelFilter2;
        labelFilter3 = ui720.labelFilter3;
        labelPage = ui720.labelPage;
        labelStart = ui720.labelStart;
        labelEnd = ui720.labelEnd;
        searchEndTime = ui720.searchEndTime;
        searchStartTime = ui720.searchStartTime;
        systemLogView = ui720.systemLogView;

        iconSize = 70;
#if 0   //yjsin resize font size for emd-s10
        systemLogView->setStyleSheet("QHeaderView{font:27px;} QTreeView{font:26px;} QTreeView::item:selected{background:rgb(152,14,69);}");
#else   //yjsin resize font size for emd-s20
        systemLogView->setStyleSheet("QHeaderView{font:29px;} QTreeView{font:27px;} QTreeView::item:selected{background:rgb(152,14,69);}");
#endif

        //yjsin [18/09/10] if text is long, change label size
        if( (utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0) )
        {
            labelStart->setStyleSheet("font:28px;");
            labelFilter1->setGeometry(530, 530, 91, 91);
            labelFilter3->setGeometry(620, 530, 31, 91);
            labelFilter2->setGeometry(650, 530, 291, 91);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0) )
        {
            labelFilter1->setGeometry(530, 530, 91, 91);
            labelFilter3->setGeometry(620, 530, 31, 91);
            labelFilter2->setGeometry(650, 530, 291, 91);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0) || (utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0) )
        {
            labelFilter1->setGeometry(530, 530, 101, 91);
            labelFilter3->setGeometry(640, 530, 20, 91);
            labelFilter2->setGeometry(660, 530, 281, 91);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0) )
        {
            labelStart->setStyleSheet("font:30px;");
            labelFilter1->setGeometry(530, 530, 111, 91);
            labelFilter3->setGeometry(650, 530, 20, 91);
            labelFilter2->setGeometry(670, 530, 281, 91);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0) )
        {
            labelFilter1->setGeometry(530, 530, 126, 91);
            labelFilter3->setGeometry(665, 530, 20, 91);
            labelFilter2->setGeometry(685, 530, 281, 91);
        }
    }
    else
    {
        Ui::SystemLogPage1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        maskFrame = ui1080.maskFrame;
        buttonClose = ui1080.buttonClose;
        buttonFunction = ui1080.buttonFunction;
        buttonPageDn = ui1080.buttonPageDn;
        buttonPageUp = ui1080.buttonPageUp;
        buttonPrevious = ui1080.buttonPrevious;
        buttonSearch = ui1080.buttonSearch;
        labelClose = ui1080.labelClose;
        labelFilter1 = ui1080.labelFilter1;
        labelFilter2 = ui1080.labelFilter2;
        labelFilter3 = ui1080.labelFilter3;
        labelPage = ui1080.labelPage;
        labelStart = ui1080.labelStart;
        labelEnd = ui1080.labelEnd;
        searchEndTime = ui1080.searchEndTime;
        searchStartTime = ui1080.searchStartTime;
        systemLogView = ui1080.systemLogView;

        iconSize = 110;
#if 0   //yjsin resize font size for emd-s10
        systemLogView->setStyleSheet("QHeaderView{font:40px;} QTreeView{font:40px;} QTreeView::item:selected{background:rgb(152,14,69);}");
#else   //yjsin resize font size for emd-s20
        systemLogView->setStyleSheet("QHeaderView{font:36px;} QTreeView{font:41px;} QTreeView::item:selected{background:rgb(152,14,69);}");
#endif

        labelStart->setStyleSheet("font:45px;");
        labelEnd->setStyleSheet("font:45px;");
        labelFilter1->setStyleSheet("font:45px;");
        labelFilter2->setStyleSheet("font:45px;");
        labelFilter3->setStyleSheet("font:45px;");
        labelPage->setStyleSheet("font:45px;");

        //yjsin [19/02/21] if text is long, change label size
        if( (utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0) || (utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0) )
        {
            labelFilter1->setGeometry(790, 800, 131, 131);
            labelFilter3->setGeometry(920, 800,  51, 131);
            labelFilter2->setGeometry(970, 800, 451, 131);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0 )
        {
            labelFilter1->setGeometry(790, 800, 141, 131);
            labelFilter3->setGeometry(930, 800,  51, 131);
            labelFilter2->setGeometry(980, 800, 451, 131);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0) )
        {
            labelFilter1->setGeometry(790, 800, 161, 131);
            labelFilter3->setGeometry(950, 800,  51, 131);
            labelFilter2->setGeometry(1000, 800, 451, 131);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0) )
        {
            labelFilter1->setGeometry(790, 800, 171, 131);
            labelFilter3->setGeometry(960, 800,  41, 131);
            labelFilter2->setGeometry(1000, 800, 451, 131);
        }
        else if( (utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0) )
        {
            labelFilter1->setStyleSheet("font:40px;");
            labelFilter1->setGeometry(790, 800, 171, 131);
            labelFilter3->setGeometry(960, 800,  41, 131);
            labelFilter2->setGeometry(1000, 800, 451, 131);
        }
    }

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    searchStartTime->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchStartTime->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    searchStartTime->setWrapping(true);
    searchStartTime->setContextMenuPolicy(Qt::NoContextMenu);
    searchStartTime->installEventFilter(this);

    searchEndTime  ->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchEndTime  ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    searchEndTime  ->setWrapping(true);
    searchEndTime  ->setContextMenuPolicy(Qt::NoContextMenu);
    searchEndTime  ->installEventFilter(this);

    buttonFunction ->setIcon    (QIcon(":/images/function.png"));
    buttonFunction ->setIconSize(QSize(iconSize,iconSize));
    buttonFunction ->adjustSize ();

    buttonPrevious ->setIcon    (QIcon(":/images/previous.png"));
    buttonPrevious ->setIconSize(QSize(iconSize,iconSize));
    buttonPrevious ->adjustSize ();

    buttonClose    ->setIcon    (QIcon(":/images/close2.png"));
    buttonClose    ->setIconSize(QSize(iconSize,iconSize));
    buttonClose    ->adjustSize ();

    maskFrame->setGeometry(0,0,appmgr_get_mainwidget_width(),appmgr_get_mainwidget_height());
    maskFrame->setWindowOpacity(0);
    maskFrame->setAttribute(Qt::WA_TranslucentBackground, true);
    maskFrame->lower();

    proxyModel = new EventSortFilterProxyModel;

    systemLogView->setRootIsDecorated(false);
    systemLogView->setAlternatingRowColors(true);
    systemLogView->setModel(proxyModel);
    systemLogView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    systemLogView->header()->setMovable(false);
    systemLogView->header()->setResizeMode(QHeaderView::Fixed);
    systemLogView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    systemLogModel = new QStandardItemModel(0, 2, this);
    systemLogModel->setHeaderData(0, Qt::Horizontal, QObject::tr("TIME"));
    systemLogModel->setHeaderData(0, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    systemLogModel->setHeaderData(1, Qt::Horizontal, QObject::tr("SYSTEM LOG LIST"));
    systemLogModel->setHeaderData(1, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);

    proxyModel->setSourceModel(systemLogModel);

    if(mainHeight == 720)
    {
        systemLogView->setColumnWidth(0, 365);
        systemLogView->setColumnWidth(1, 884);
    }
    else
    {
        systemLogView->setColumnWidth(0, 550);
        systemLogView->setColumnWidth(1, 1250);
    }

    connect(buttonPrevious, SIGNAL(released()), this, SLOT(onButtonPrevious()));
    connect(buttonClose, SIGNAL(released()), this, SLOT(onButtonClose()));
    connect(buttonSearch , SIGNAL(released()), this, SLOT(onButtonSearch()));
    connect(buttonFunction , SIGNAL(released()), this, SLOT(onButtonFunction()));
    connect(buttonPageDn, SIGNAL(released()), this, SLOT(onButtonPageDn()));
    connect(buttonPageUp, SIGNAL(released()), this, SLOT(onButtonPageUp()));

    resetLog();
}
SystemLogPage::~SystemLogPage()
{
}
void SystemLogPage::resetLog()
{
    systemLogModel->removeRows(0, systemLogModel->rowCount());

    searchStartTime->setDateTime(QDateTime::currentDateTime());
    searchEndTime->setDateTime(QDateTime::currentDateTime());

    if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)    //12H
    {
        searchStartTime->setDisplayFormat("yyyy.MM.dd hh:mm AP");
        searchStartTime->setStyleSheet("QDateTimeEdit {font:32px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        searchEndTime->setDisplayFormat("yyyy.MM.dd hh:mm AP");
        searchEndTime->setStyleSheet("QDateTimeEdit {font:32px; selection-color:white; selection-background-color:rgb(152,14,69);}");

        if(mainHeight == 1080)
        {
            searchStartTime->setStyleSheet("QDateTimeEdit {font:48px; selection-color:white; selection-background-color:rgb(152,14,69);}");
            searchEndTime->setStyleSheet("QDateTimeEdit {font:48px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        }
    }
    else                                                            //24H
    {
        searchStartTime->setDisplayFormat("yyyy.MM.dd hh:mm");
        searchStartTime->setStyleSheet("QDateTimeEdit {font:39px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        searchEndTime->setDisplayFormat("yyyy.MM.dd hh:mm");
        searchEndTime->setStyleSheet("QDateTimeEdit {font:39px; selection-color:white; selection-background-color:rgb(152,14,69);}");

        if(mainHeight == 1080)
        {
            searchStartTime->setStyleSheet("QDateTimeEdit {font:55px; selection-color:white; selection-background-color:rgb(152,14,69);}");
            searchEndTime->setStyleSheet("QDateTimeEdit {font:55px; selection-color:white; selection-background-color:rgb(152,14,69);}");
        }
    }

    logPageNum=0, logPageNow=0;
    logFilter="";
    logSort=SYSTEM_LOG_DESC;
    ampmStatus="";
    isSearch=true;
    isKeyLock=false;
    functionDialog=NULL;

    labelPage->setText("0\n(0/0)");
    labelFilter2->setText(tr("\nDescending"));

    buttonPageDn->setEnabled(false);
    buttonPageUp->setEnabled(false);

    searchStartTime->setFocus();
}
void SystemLogPage::onQueryLogCount()
{
    int ii, pageCount;

    logCount=gSystemLog[0].total;
    pageCount=gSystemLog[0].count;
    logPageNum=logCount/SYSTEM_LOG_COUNT_PER_PAGE;

    //calculate pageButton Status
    if((logCount%SYSTEM_LOG_COUNT_PER_PAGE) == 0) //ex>total:15/30/45..
    {
        if(logPageNum > 0)
        {
            logPageNum-=1;
        }
    }

    if(isSearch)
    {
        //print log
        systemLogModel->removeRows(0, systemLogModel->rowCount());

        for(ii = 0; ii < pageCount; ii++)
        {
            if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)
            {
                QString logTime=changeTimeformat(gSystemLog[ii].time);
                addEventLog(QString("%1 %2").arg(logTime).arg(ampmStatus).toStdString().c_str(), gSystemLog[ii].log);
            }
            else
            {
                addEventLog(QString(gSystemLog[ii].time), QString(gSystemLog[ii].log));
            }
        }
    }

    //Page button en/disable
    if(logPageNum>0)
    {
        buttonPageUp->setEnabled(true);
    }
    if(logPageNow >= logPageNum)
    {
        buttonPageUp->setEnabled(false);
    }
    if(logPageNow==0)
    {
        buttonPageDn->setEnabled(false);
    }

    //display page count
    if(logCount > 0)
    {
        labelPage->setText(QString("%1\n(%2/%3)").arg(logCount).arg(logPageNow+1).arg(logPageNum+1));
    }
    else
    {
        labelPage->setText(QString("%1\n(%2/%3)").arg(logCount).arg(logPageNow).arg(logPageNum));
    }
}
void SystemLogPage::onQueryLogData()
{
    int ii, pageCount;
    pageCount=gSystemLog[0].count;

    systemLogModel->removeRows(0, systemLogModel->rowCount());

    for(ii = 0; ii < pageCount; ii++)
    {
        if(utils_cfg_cmp_item(SystemCfg.time_format, "12HOUR") == 0)
        {
            QString logTime=changeTimeformat(gSystemLog[ii].time);
            addEventLog(QString("%1 %2").arg(logTime).arg(ampmStatus).toStdString().c_str(), gSystemLog[ii].log);
        }
        else
        {
            addEventLog(QString(gSystemLog[ii].time), QString(gSystemLog[ii].log));
        }
    }
}

void SystemLogPage::onButtonSearch()
{
    isSearch=true;

    //init
    systemLogModel->removeRows(0, systemLogModel->rowCount());

    startTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    endTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    logPageNow=0;
    logPageNum=0;

    //search log
    pQuery = g_new0(SYSTEM_LOG_QUERY_S, 1);

    if(pQuery)
    {
        if( startTime <= endTime)
        {
            memcpy(pQuery->start, startTime.toStdString().c_str(), startTime.size());
            memcpy(pQuery->end,   endTime.toStdString().c_str(),   endTime.size());
        }
        else
        {
            memcpy(pQuery->start, endTime.toStdString().c_str(),    endTime.size());
            memcpy(pQuery->end,   startTime.toStdString().c_str(),  startTime.size());
        }
        memcpy(pQuery->filter, logFilter.toStdString().c_str(), logFilter.size());
        if(logSort.compare(SYSTEM_LOG_ASC) == 0)
        {
            memcpy(pQuery->sort, SYSTEM_LOG_ASC, strlen(SYSTEM_LOG_ASC));
        }
        else
        {
            memcpy(pQuery->sort, SYSTEM_LOG_DESC, strlen(SYSTEM_LOG_DESC));
        }

        pQuery->offset = 0;
        pQuery->nLog  = SYSTEM_LOG_COUNT_PER_PAGE;
        event_send(QUEUE_QT_CORE, QUEUE_SYSTEM_LOG, SYSTEM_LOG_COUNT, pQuery, g_free, NULL);

        buttonPageDn->setEnabled(false);
        buttonPageUp->setEnabled(false);
    }
}
void SystemLogPage::onButtonPrevious()
{
    emit previousSearch(2);
}
void SystemLogPage::onButtonClose()
{
    emit closeSearch(2);
}

void SystemLogPage::onButtonFunction()
{
    isSearch=true;

    maskFrame->raise();

    functionDialog=new FunctionDialog();
    functionDialog->setParent(this);
    functionDialog->move((this->width()-functionDialog->size().width())/2,(this->height()-functionDialog->size().height())/2);

    functionDialog->setLogFilter(logFilter);
    functionDialog->setLogSort(logSort);
    functionDialog->buttonFilter->setFocus();

    if(functionDialog->exec() == 1)
    {
        logFilter=functionDialog->getLogFilter();
        logSort=functionDialog->getLogSort();

        if(logSort.compare(SYSTEM_LOG_ASC) == 0)
        {
            labelFilter2->setText(QString("%1\n%2").arg(logFilter).arg(tr("Ascending")));
        }
        else
        {
            labelFilter2->setText(QString("%1\n%2").arg(logFilter).arg(tr("Descending")));
        }

        onButtonSearch();
    }

    delete functionDialog;
    functionDialog = NULL;

    maskFrame->lower();
    buttonFunction->setFocus();
}
void SystemLogPage::onButtonPageDn()
{
    isSearch=false;

    QString oldStartTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    QString oldEndTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");

    if(startTime != oldStartTime || endTime != oldEndTime)
    {
        onButtonSearch();
        return;
    }

    if(--logPageNow >= 0)
    {
        updateLogCount();

        pQuery = g_new0(SYSTEM_LOG_QUERY_S, 1);

        if(pQuery)
        {
            if(startTime <= endTime)
            {
                memcpy(pQuery->start, startTime.toStdString().c_str(), startTime.size());
                memcpy(pQuery->end,     endTime.toStdString().c_str(), endTime.size());
            }
            else
            {
                memcpy(pQuery->start,   endTime.toStdString().c_str(), endTime.size());
                memcpy(pQuery->end,   startTime.toStdString().c_str(), startTime.size());
            }
            memcpy(pQuery->filter, logFilter.toStdString().c_str(), logFilter.size());
            if(logSort.compare(SYSTEM_LOG_ASC) == 0)
            {
                memcpy(pQuery->sort, SYSTEM_LOG_ASC, strlen(SYSTEM_LOG_ASC));
            }
            else
            {
                memcpy(pQuery->sort, SYSTEM_LOG_DESC, strlen(SYSTEM_LOG_DESC));
            }

            pQuery->offset = logPageNow * SYSTEM_LOG_COUNT_PER_PAGE;
            pQuery->nLog   = SYSTEM_LOG_COUNT_PER_PAGE;

            event_send(QUEUE_QT_CORE, QUEUE_SYSTEM_LOG, SYSTEM_LOG_DATA, pQuery, g_free, NULL);

            if(logPageNow<logPageNum)
            {
                buttonPageUp->setEnabled(true);
            }
        }
    }

    if(logPageNow == 0)
    {
        buttonPageUp->setEnabled(false);
        buttonPageDn->setFocus();
    }
}
void SystemLogPage::onButtonPageUp()
{
    isSearch=false;

    QString oldStartTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    QString oldEndTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");

    if(startTime != oldStartTime || endTime != oldEndTime)
    {
        onButtonSearch();
        return;
    }

    if(++logPageNow <= logPageNum)
    {
        updateLogCount();

        pQuery = g_new0(SYSTEM_LOG_QUERY_S, 1);

        if(pQuery)
        {
            if(startTime <= endTime)
            {
                memcpy(pQuery->start, startTime.toStdString().c_str(), startTime.size());
                memcpy(pQuery->end,     endTime.toStdString().c_str(), endTime.size());
            }
            else
            {
                memcpy(pQuery->start,   endTime.toStdString().c_str(), endTime.size());
                memcpy(pQuery->end,   startTime.toStdString().c_str(), startTime.size());
            }
            memcpy(pQuery->filter, logFilter.toStdString().c_str(), logFilter.size());
            if(logSort.compare(SYSTEM_LOG_ASC) == 0)
            {
                memcpy(pQuery->sort, SYSTEM_LOG_ASC, strlen(SYSTEM_LOG_ASC));
            }
            else
            {
                memcpy(pQuery->sort, SYSTEM_LOG_DESC, strlen(SYSTEM_LOG_DESC));
            }

            pQuery->offset   = logPageNow * SYSTEM_LOG_COUNT_PER_PAGE;

            if(logPageNow == logPageNum)
            {
                pQuery->nLog = logCount % SYSTEM_LOG_COUNT_PER_PAGE;

                if(pQuery->nLog == 0)
                {
                    pQuery->nLog = SYSTEM_LOG_COUNT_PER_PAGE;
                }
            }
            else
            {
                pQuery->nLog = SYSTEM_LOG_COUNT_PER_PAGE;
            }

            event_send(QUEUE_QT_CORE, QUEUE_SYSTEM_LOG, SYSTEM_LOG_DATA, pQuery, g_free, NULL);

            if(logPageNow > 0)
            {
                buttonPageDn->setEnabled(true);
            }
        }
    }

    if(logPageNow >= logPageNum)
    {
        buttonPageUp->setEnabled(false);
        buttonPageDn->setFocus();
    }
}
void SystemLogPage::updateLogCount()
{
    startTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    endTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");

    pQuery = g_new0(SYSTEM_LOG_QUERY_S, 1);

    if(pQuery)
    {
        if(startTime <= endTime)
        {
            memcpy(pQuery->start, startTime.toStdString().c_str(), startTime.size());
            memcpy(pQuery->end,   endTime.toStdString().c_str(),   endTime.size());
        }
        else
        {
            memcpy(pQuery->start, endTime.toStdString().c_str(),   endTime.size());
            memcpy(pQuery->end,   startTime.toStdString().c_str(), startTime.size());
        }
        memcpy(pQuery->filter, logFilter.toStdString().c_str(), logFilter.size());
        if(logSort.compare(SYSTEM_LOG_ASC) == 0)
        {
            memcpy(pQuery->sort, SYSTEM_LOG_ASC, strlen(SYSTEM_LOG_ASC));
        }
        else
        {
            memcpy(pQuery->sort, SYSTEM_LOG_DESC, strlen(SYSTEM_LOG_DESC));
        }

        pQuery->offset=0;
        pQuery->nLog=SYSTEM_LOG_COUNT_PER_PAGE;

        event_send(QUEUE_QT_CORE, QUEUE_SYSTEM_LOG, SYSTEM_LOG_COUNT, pQuery, g_free, NULL);
    }
}
void SystemLogPage::addEventLog(const QString &logDateTime, const QString &log)
{
    int rowMax=systemLogModel->rowCount();

    systemLogModel->insertRow(rowMax);
    systemLogModel->setData(systemLogModel->index(rowMax, 0), logDateTime);
    systemLogModel->setData(systemLogModel->index(rowMax, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    systemLogModel->setData(systemLogModel->index(rowMax, 1), log);
    systemLogModel->setData(systemLogModel->index(rowMax, 1), Qt::AlignLeft, Qt::TextAlignmentRole);
}
QString SystemLogPage::changeTimeformat(char event_time[])
{
    QString qEventTime=QString(event_time);
    QRegExp rx("[- :]");
    QStringList parseList=qEventTime.split(rx, QString::SkipEmptyParts);

    QList<QString> dateTimeList;
    for(int i=0;i<parseList.size();i++)
    {
        dateTimeList.append(parseList.at(i));
    }

    if( dateTimeList.value(3).toInt()==0 ) // 0 AM
    {
        dateTimeList.replace(3, "12");
        ampmStatus="AM";
    }
    else if( dateTimeList.value(3).toInt()>0 && dateTimeList.value(3).toInt()<12 ) // 1~11 AM
    {
        ampmStatus="AM";
    }
    else if( dateTimeList.value(3).toInt()==12) // 12 PM
    {
        ampmStatus="PM";
    }
    else if( dateTimeList.value(3).toInt()>12 && dateTimeList.value(3).toInt()<22 ) // 13~21 PM
    {
        dateTimeList.replace(3, QString("%1%2").arg("0").arg(QString::number( dateTimeList.value(3).toInt()-12 )));
        ampmStatus="PM";
    }
    else if( dateTimeList.value(3).toInt()>21 && dateTimeList.value(3).toInt()<24 ) // 22~23 PM
    {
        dateTimeList.replace(3, QString::number(dateTimeList.value(3).toInt()-12));
        ampmStatus="PM";
    }
    else // Error
    {
        qDebug("[ERROR]EventLogPage::parseDateTime()");
    }

    qEventTime=QString("%1-%2-%3 %4:%5:%6")
            .arg(dateTimeList.value(0))
            .arg(dateTimeList.value(1))
            .arg(dateTimeList.value(2))
            .arg(dateTimeList.value(3))
            .arg(dateTimeList.value(4))
            .arg(dateTimeList.value(5));

    return qEventTime;
}
bool SystemLogPage::eventFilter(QObject *obj, QEvent *event)
{
    if((obj==searchStartTime || obj==searchEndTime) && (event->type()==QEvent::FocusOut))
    {
        isKeyLock=false;
    }
    return QWidget::eventFilter(obj, event);
}
void SystemLogPage::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if( functionDialog )
            {
                functionDialog->KeyPressEvent(Qt::Key_Up);
            }
            else
            {
                if( searchStartTime->hasFocus() && isKeyLock)       { searchStartTime->stepUp();   }
                else if( searchStartTime->hasFocus() )              { searchEndTime->setFocus();   }
                else if( searchEndTime->hasFocus() && isKeyLock)    { searchEndTime->stepUp();     }
                else if( searchEndTime->hasFocus() )                { searchStartTime->setFocus(); }
                else if( buttonPrevious->hasFocus())                { buttonClose->setFocus();     }
                else if( buttonClose->hasFocus())                   { buttonPrevious->setFocus();  }
            }

            break;
        }
        case Qt::Key_Down:
        {
            if( functionDialog )
            {
                functionDialog->KeyPressEvent(Qt::Key_Down);
            }
            else
            {
                if( searchStartTime->hasFocus() && isKeyLock)       { searchStartTime->stepDown(); }
                else if( searchStartTime->hasFocus() )              { searchEndTime->setFocus();   }
                else if( searchEndTime->hasFocus() && isKeyLock)    { searchEndTime->stepDown();   }
                else if( searchEndTime->hasFocus() )                { searchStartTime->setFocus(); }
                else if( buttonPrevious->hasFocus())                { buttonClose->setFocus();     }
                else if( buttonClose->hasFocus())                   { buttonPrevious->setFocus();  }
            }

            break;
        }
        case Qt::Key_Left:
        {
            if( functionDialog )
            {
                functionDialog->KeyPressEvent(Qt::Key_Left);
            }
            else
            {
                if( searchStartTime->hasFocus() && isKeyLock)
                {
                    switch(searchStartTime->currentSectionIndex())
                    {
                        case 0: { searchStartTime->setSelectedSection(QDateTimeEdit::MinuteSection);         break; }
                        case 1: { searchStartTime->setSelectedSection(QDateTimeEdit::YearSection);           break; }
                        case 2: { searchStartTime->setSelectedSection(QDateTimeEdit::MonthSection);          break; }
                        case 3: { searchStartTime->setSelectedSection(QDateTimeEdit::DaySection);            break; }
                        case 4: { searchStartTime->setSelectedSection(QDateTimeEdit::HourSection);           break; }
                    }
                }
                else if( searchEndTime->hasFocus() && isKeyLock)
                {
                    switch(searchEndTime->currentSectionIndex())
                    {
                        case 0: { searchEndTime->setSelectedSection(QDateTimeEdit::MinuteSection);           break; }
                        case 1: { searchEndTime->setSelectedSection(QDateTimeEdit::YearSection);             break; }
                        case 2: { searchEndTime->setSelectedSection(QDateTimeEdit::MonthSection);            break; }
                        case 3: { searchEndTime->setSelectedSection(QDateTimeEdit::DaySection);              break; }
                        case 4: { searchEndTime->setSelectedSection(QDateTimeEdit::HourSection);             break; }
                    }
                }
                else if( searchStartTime->hasFocus())                               { buttonPrevious->setFocus();   break; }
                else if( searchEndTime->hasFocus())                                 { buttonClose->setFocus();      break; }
                else if( buttonSearch->hasFocus())                                  { searchEndTime->setFocus();    break; }
                else if( buttonFunction->hasFocus())                                { buttonSearch->setFocus();     break; }
                else if( buttonPageDn->hasFocus())                                  { buttonFunction->setFocus();   break; }
                else if( buttonPageUp->hasFocus() && buttonPageDn->isEnabled())     { buttonPageDn->setFocus();     break; }
                else if( buttonPageUp->hasFocus())                                  { buttonFunction->setFocus();   break; }
                else if( buttonPrevious->hasFocus() && buttonPageUp->isEnabled())   { buttonPageUp->setFocus();     break; }
                else if( buttonPrevious->hasFocus() && buttonPageDn->isEnabled())   { buttonPageDn->setFocus();     break; }
                else if( buttonPrevious->hasFocus())                                { buttonFunction->setFocus();   break; }
                else if( buttonClose->hasFocus() && buttonPageUp->isEnabled())      { buttonPageUp->setFocus();     break; }
                else if( buttonClose->hasFocus() && buttonPageDn->isEnabled())      { buttonPageDn->setFocus();     break; }
                else if( buttonClose->hasFocus())                                   { buttonFunction->setFocus();   break; }
            }

            break;
        }
        case Qt::Key_Right:
        {
            if( functionDialog )
            {
                functionDialog->KeyPressEvent(Qt::Key_Right);
            }
            else
            {
                if( searchStartTime->hasFocus() && isKeyLock )
                {
                    switch(searchStartTime->currentSectionIndex())
                    {
                        case 0: { searchStartTime->setSelectedSection(QDateTimeEdit::MonthSection);          break; }
                        case 1: { searchStartTime->setSelectedSection(QDateTimeEdit::DaySection);            break; }
                        case 2: { searchStartTime->setSelectedSection(QDateTimeEdit::HourSection);           break; }
                        case 3: { searchStartTime->setSelectedSection(QDateTimeEdit::MinuteSection);         break; }
                        case 4: { searchStartTime->setSelectedSection(QDateTimeEdit::YearSection);           break; }
                    }
                }
                else if( searchEndTime->hasFocus() && isKeyLock )
                {
                    switch(searchEndTime->currentSectionIndex())
                    {
                        case 0: { searchEndTime->setSelectedSection(QDateTimeEdit::MonthSection);           break; }
                        case 1: { searchEndTime->setSelectedSection(QDateTimeEdit::DaySection);             break; }
                        case 2: { searchEndTime->setSelectedSection(QDateTimeEdit::HourSection);            break; }
                        case 3: { searchEndTime->setSelectedSection(QDateTimeEdit::MinuteSection);          break; }
                        case 4: { searchEndTime->setSelectedSection(QDateTimeEdit::YearSection);            break; }
                    }
                }
                else if( searchStartTime->hasFocus())                                   { buttonSearch->setFocus();     break; }
                else if( searchEndTime->hasFocus())                                     { buttonSearch->setFocus();     break; }
                else if( buttonSearch->hasFocus())                                      { buttonFunction->setFocus();   break; }
                else if( buttonFunction->hasFocus() && buttonPageDn->isEnabled())       { buttonPageDn->setFocus();     break; }
                else if( buttonFunction->hasFocus() && buttonPageUp->isEnabled())       { buttonPageUp->setFocus();     break; }
                else if( buttonFunction->hasFocus())                                    { buttonClose->setFocus();      break; }
                else if( buttonPageDn->hasFocus() && buttonPageUp->isEnabled())         { buttonPageUp->setFocus();     break; }
                else if( buttonPageDn->hasFocus())                                      { buttonClose->setFocus();      break; }
                else if( buttonPageUp->hasFocus())                                      { buttonClose->setFocus();      break; }
                else if( buttonPrevious->hasFocus())                                    { searchStartTime->setFocus();  break; }
                else if( buttonClose->hasFocus())                                       { searchEndTime->setFocus();    break; }
            }

            break;
        }
        case Qt::Key_Enter:
        {
            if( functionDialog )
            {
                functionDialog->KeyPressEvent(Qt::Key_Enter);
            }
            else
            {
                if( searchStartTime->hasFocus() || searchEndTime->hasFocus())   { isKeyLock=true;     }
                else if(buttonSearch->hasFocus())                               { onButtonSearch();   }
                else if(buttonFunction->hasFocus())                             { onButtonFunction(); }
                else if(buttonPageDn->hasFocus())                               { onButtonPageDn();   }
                else if(buttonPageUp->hasFocus())                               { onButtonPageUp();   }
                else if(buttonPrevious->hasFocus())                             { onButtonPrevious(); }
                else if(buttonClose->hasFocus())                                { onButtonClose();    }
            }
            break;
        }
        case Qt::Key_Escape:
        {
            if( functionDialog )
            {
                functionDialog->KeyPressEvent(Qt::Key_Escape);
            }
            else
            {
                if( searchStartTime->hasFocus() && isKeyLock==true )        { isKeyLock=false; break;    }
                else if ( searchEndTime->hasFocus() && isKeyLock==true )    { isKeyLock=false; break;    }
                else                                                        { onButtonPrevious(); break; }
            }

            break;
        }
        case Qt::Key_PageUp:
        {
            if( buttonPageUp->isEnabled() )
            {
                onButtonPageUp();
                buttonPageUp->setFocus();
            }
            break;
        }
        case Qt::Key_PageDown:
        {
            if( buttonPageDn->isEnabled() )
            {
                onButtonPageDn();
                buttonPageDn->setFocus();
            }
            break;

        }

        default:
        {
            return;
        }
    }

    return;
}

