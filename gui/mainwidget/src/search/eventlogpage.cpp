#include <QtGui>
#include "eventlogpage.h"
#include "eventsortfilterproxymodel.h"
#include "main/mainglobal.h"
#include "Event.h"

EventLogPage::EventLogPage(QWidget *parent)
    : QWidget(parent)
{
    logCount       = 0;
    logPageNum     = 0;

    createEventLogView();
    createEventLogModel();

    log_type = EVENT_LOG_ALL;
    log_sort = EVENT_LOG_DESC;

    labelStartTime = new QLabel(tr("Start:"));
    labelStartTime->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelStartTime->setMaximumSize(QSize(80, 90));

    searchStartTime = new QDateTimeEdit(QDateTime::currentDateTime());
    searchStartTime->setDisplayFormat("yyyy.MM.dd hh:mm");
    searchStartTime->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    searchStartTime->setStyleSheet("QDateTimeEdit {font:33px; selection-color:white; selection-background-color:rgb(152,14,69);}");
    searchStartTime->setMaximumSize(QSize(400, 90));

    labelEndTime = new QLabel(tr("End:"));
    labelEndTime->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelEndTime->setMaximumSize(QSize(80, 90));
    searchEndTime = new QDateTimeEdit(QDateTime::currentDateTime());
    searchEndTime->setDisplayFormat("yyyy.MM.dd hh:mm");
    searchEndTime->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    searchEndTime->setStyleSheet("QDateTimeEdit {font:33px; selection-color:white; selection-background-color:rgb(152,14,69);}");
    searchEndTime->setMaximumSize(QSize(400, 90));

    labelFilter = new QLabel(tr("Filter:"));
    labelFilter->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelFilter->setMaximumSize(QSize(80, 90));

    buttonFilter = new QPushButton(tr("All"));
    buttonFilter->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonFilter->setMaximumSize(QSize(200, 90));

    buttonSort = new QPushButton(tr("Desc"));
    buttonSort->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonSort->setMaximumSize(QSize(200, 90));

    labelLog = new QLabel(tr("Log:"));
    labelLog->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelLog->setMaximumSize(QSize(80, 90));

    labelLogResult = new QLabel(tr("0"));
    labelLogResult->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelLogResult->setMaximumSize(QSize(160, 90));
    labelLogResult->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    buttonSearch = new QPushButton(tr("Search"));
    buttonSearch->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonSearch->setMaximumSize(QSize(240, 90));

    buttonPrevLogPage = new QPushButton(tr("<"));
    buttonPrevLogPage->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonPrevLogPage->setMaximumSize(QSize(150, 90));
    buttonPrevLogPage->setEnabled(false);
    labelPage = new QLabel("(0/0)");
    labelPage->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    labelPage->setMaximumSize(QSize(180, 90));
    labelPage->setAlignment(Qt::AlignCenter);
    buttonNextLogPage = new QPushButton(tr(">"));
    buttonNextLogPage->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonNextLogPage->setMaximumSize(QSize(150, 90));
    buttonNextLogPage->setEnabled(false);

    buttonPlay = new QPushButton(tr("Play"));
    buttonPlay->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonPlay->setMaximumSize(QSize(480, 90));
    buttonPlay->setEnabled(false);

    buttonPrevious = new QPushButton(tr("Previous"));
    buttonPrevious->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonPrevious->setMaximumSize(QSize(240, 90));

    buttonClose = new QPushButton(tr("Close"));
    buttonClose->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    buttonClose->setMaximumSize(QSize(240, 90));

#if 1 //yjsin [17/09/13] if text is long, change label size
    if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
    {
        labelStartTime->setMaximumSize(QSize(100, 90));
        labelEndTime->setMaximumSize(QSize(100, 90));
        labelFilter->setMaximumSize(QSize(100, 90));
        labelLog->setMaximumSize(QSize(130, 90));
    }
    //yjsin [17/10/12] if text is long, change label size
    else if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
    {
        labelStartTime->setMaximumSize(QSize(100, 90));
        labelEndTime->setMaximumSize(QSize(100, 90));
        labelFilter->setMaximumSize(QSize(100, 90));
        labelLog->setMaximumSize(QSize(130, 90));
    }
#endif

    QHBoxLayout *mainLayout   = new QHBoxLayout;
    QVBoxLayout *menuVLayout0 = new QVBoxLayout;
    QHBoxLayout *menuHLayout1 = new QHBoxLayout;
    QHBoxLayout *menuHLayout2 = new QHBoxLayout;
    QHBoxLayout *menuHLayout3 = new QHBoxLayout;
    QHBoxLayout *menuHLayout4 = new QHBoxLayout;
    QHBoxLayout *menuHLayout5 = new QHBoxLayout;
    QHBoxLayout *menuHLayout6 = new QHBoxLayout;
    QHBoxLayout *menuHLayout7 = new QHBoxLayout;

    menuHLayout1->addWidget(labelStartTime);
    menuHLayout1->addWidget(searchStartTime);

    menuHLayout2->addWidget(labelEndTime);
    menuHLayout2->addWidget(searchEndTime);

    menuHLayout3->addWidget(labelFilter);
    menuHLayout3->addWidget(buttonFilter);
    menuHLayout3->addWidget(buttonSort);

    menuHLayout4->addWidget(labelLog);
    menuHLayout4->addWidget(labelLogResult);
    menuHLayout4->addWidget(buttonSearch);

    menuHLayout5->addWidget(buttonPrevLogPage);
    menuHLayout5->addWidget(labelPage);
    menuHLayout5->addWidget(buttonNextLogPage);

    menuHLayout6->addWidget(buttonPlay);

    menuHLayout7->addWidget(buttonPrevious);
    menuHLayout7->addWidget(buttonClose);

    menuVLayout0->addLayout(menuHLayout1);
    menuVLayout0->addLayout(menuHLayout2);
    menuVLayout0->addLayout(menuHLayout3);
    menuVLayout0->addLayout(menuHLayout4);
    menuVLayout0->addLayout(menuHLayout5);
    menuVLayout0->addLayout(menuHLayout6);
    menuVLayout0->addLayout(menuHLayout7);

    mainLayout->addWidget(eventLogView);
    mainLayout->addLayout(menuVLayout0);

    setLayout(mainLayout);

    proxyModel->setSourceModel(eventLogModel);
    eventLogView->setColumnWidth(0, 330);
    eventLogView->setColumnWidth(1, 235);
    eventLogView->setColumnWidth(2, 235);
    eventLogView->setColumnHidden(3, true);

    connect(buttonFilter, SIGNAL(clicked()), this, SLOT(onButtonFilter()));
    connect(buttonSort, SIGNAL(clicked()), this, SLOT(onButtonSort()));
    connect(buttonSearch, SIGNAL(clicked()), this, SLOT(onButtonSearch()));
    connect(buttonPrevLogPage, SIGNAL(clicked()), this, SLOT(onButtonPreviousPage()));
    connect(buttonNextLogPage, SIGNAL(clicked()), this, SLOT(onButtonNextPage()));
    connect(buttonPlay, SIGNAL(clicked()), this, SLOT(onButtonPlayback()));
    connect(buttonPrevious, SIGNAL(clicked()), this, SLOT(onButtonPrevious()));
    connect(buttonClose, SIGNAL(clicked()), this, SLOT(onButtonClose()));
    connect(eventLogView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTreeViewClicked(const QModelIndex &)));

    oldIndexFilter = EVENT_LOG_ALL;
    indexFilter    = EVENT_LOG_ALL;
    oldIndexSort   = EVENT_LOG_DESC;
    indexSort      = EVENT_LOG_DESC;
    isKeyLock      = false;
}
EventLogPage::~EventLogPage()
{
}
extern EVENT_LOG_DATA_S gEventLog[MAX_EVENT_LOG_PAGE_DATA];
void EventLogPage::onQueryLogCount()
{
    int ii, count;
    QString strEventLog, strEventTime;

    logCount   = gEventLog[0].total;
    count      = gEventLog[0].count;
    logPageNum = logCount / MAX_EVENT_LOG_PAGE_DATA;

    if((logCount % MAX_EVENT_LOG_PAGE_DATA) == 0)
    {
        if(logPageNum > 0)
        {
            logPageNum -= 1;
        }
    }

    eventLogModel->removeRows(0, eventLogModel->rowCount());

    for(ii = 0; ii < count; ii++)
    {
        //qDebug("%s, gEventLog[%d].event_time=[%s] total=%d count=%d log_type=%d event_type=%d", __func__, ii, gEventLog[ii].event_time, gEventLog[ii].total, gEventLog[ii].count, gEventLog[ii].log_type, gEventLog[ii].event_type);

        switch(gEventLog[ii].log_type)
        {
            case EVENT_LOG_IMPACT:   strEventLog = tr("IMPACT");   break;
            case EVENT_LOG_TRIGGER1: strEventLog = tr("TRIGGER1"); break;
            case EVENT_LOG_TRIGGER2: strEventLog = tr("TRIGGER2"); break;
            case EVENT_LOG_TRIGGER3: strEventLog = tr("TRIGGER3"); break;
            case EVENT_LOG_TRIGGER4: strEventLog = tr("TRIGGER4"); break;
            case EVENT_LOG_PARKING:  strEventLog = tr("PARKING");  break;
            case EVENT_LOG_MOTION:   strEventLog = tr("MOTION");   break;
            default:                 strEventLog = tr("");         break;
        }

        switch(gEventLog[ii].event_type)
        {
            case 1:  strEventTime = tr("30 %1").arg(tr("SEC")); break;
            case 2:  strEventTime = tr("60 %1").arg(tr("SEC")); break;
            default: strEventTime = tr("");                         break;
        }

        addEventLog(gEventLog[ii].event_time, strEventLog, strEventTime, ii);
    }

    if(logPageNum > 0)
    {
        buttonNextLogPage->setEnabled(true);
    }

    if(logCount > 0)
    {
        labelPage->setText(tr("(%1/%2)").arg(logPageNow+1).arg(logPageNum+1));
    }
    else
    {
        labelPage->setText(tr("(%1/%2)").arg(logPageNow).arg(logPageNum));
    }

    buttonPlay->setEnabled(false);
    labelLogResult->setNum(logCount);
}
void EventLogPage::onQueryLogData()
{
    int ii, count;
    QString strEventLog, strEventTime;

    count = gEventLog[0].count;

    eventLogModel->removeRows(0, eventLogModel->rowCount());

    for(ii = 0; ii < count; ii++)
    {
        //qDebug("%s, gEventLog[%d].event_time=[%s] total=%d count=%d log_type=%d event_type=%d", __func__, ii, gEventLog[ii].event_time, gEventLog[ii].total, gEventLog[ii].count, gEventLog[ii].log_type, gEventLog[ii].event_type);

        switch(gEventLog[ii].log_type)
        {
            case EVENT_LOG_IMPACT:   strEventLog = tr("IMPACT");   break;
            case EVENT_LOG_TRIGGER1: strEventLog = tr("TRIGGER1"); break;
            case EVENT_LOG_TRIGGER2: strEventLog = tr("TRIGGER2"); break;
            case EVENT_LOG_TRIGGER3: strEventLog = tr("TRIGGER3"); break;
            case EVENT_LOG_TRIGGER4: strEventLog = tr("TRIGGER4"); break;
            case EVENT_LOG_PARKING:  strEventLog = tr("PARKING");  break;
            case EVENT_LOG_MOTION:   strEventLog = tr("MOTION");   break;
            default:                 strEventLog = tr("");         break;
        }

        switch(gEventLog[ii].event_type)
        {
            case 1:  strEventTime = tr("30 %1").arg(tr("SEC")); break;
            case 2:  strEventTime = tr("60 %1").arg(tr("SEC")); break;
            default: strEventTime = tr("");                         break;
        }

        addEventLog(gEventLog[ii].event_time, strEventLog, strEventTime, ii);
    }

    buttonPlay->setEnabled(false);
    labelPage->setText(tr("(%1/%2)").arg(logPageNow+1).arg(logPageNum+1));
}
void EventLogPage::onButtonSearch()
{
    startTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    endTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");

    logPageNow     = 0;
    logPageNum     = 0;
    oldIndexFilter = indexFilter;
    oldIndexSort   = indexSort;
    EVENT_LOG_QUERY_S *pQuery = g_new0(EVENT_LOG_QUERY_S, 1);

    if(pQuery)
    {
        if(startTime <= endTime)
        {
            memcpy(pQuery->start_time, startTime.toStdString().c_str(), startTime.size());
            memcpy(pQuery->end_time,     endTime.toStdString().c_str(), endTime.size());
        }
        else
        {
            memcpy(pQuery->start_time,   endTime.toStdString().c_str(), endTime.size());
            memcpy(pQuery->end_time,   startTime.toStdString().c_str(), startTime.size());
        }

        pQuery->log_type = log_type;
        pQuery->log_sort = log_sort;
        pQuery->offset     = 0;
        pQuery->nLog       = MAX_EVENT_LOG_PAGE_DATA;
        event_send(QUEUE_QT_CORE, QUEUE_EVENT_LOG, EVENT_LOG_QUERY_COUNT, pQuery, g_free, NULL);
        buttonPrevLogPage->setEnabled(false);
        buttonNextLogPage->setEnabled(false);
        buttonPlay->setEnabled(false);
    }
}
void EventLogPage::onButtonPreviousPage()
{
    QString oldStartTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    QString oldEndTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");

    if(startTime != oldStartTime || endTime != oldEndTime)
    {
        onButtonSearch();
        return;
    }

    if(--logPageNow >= 0)
    {
        EVENT_LOG_QUERY_S *pQuery = g_new0(EVENT_LOG_QUERY_S, 1);

        if(pQuery)
        {
            if(startTime <= endTime)
            {
                memcpy(pQuery->start_time, startTime.toStdString().c_str(), startTime.size());
                memcpy(pQuery->end_time,     endTime.toStdString().c_str(), endTime.size());
            }
            else
            {
                memcpy(pQuery->start_time,   endTime.toStdString().c_str(), endTime.size());
                memcpy(pQuery->end_time,   startTime.toStdString().c_str(), startTime.size());
            }

            pQuery->log_type = log_type;
            pQuery->log_sort = log_sort;
            pQuery->offset   = logPageNow * MAX_EVENT_LOG_PAGE_DATA;
            pQuery->nLog     = MAX_EVENT_LOG_PAGE_DATA;
            event_send(QUEUE_QT_CORE, QUEUE_EVENT_LOG, EVENT_LOG_QUERY_DATA, pQuery, g_free, NULL);

            if(logPageNow < logPageNum)
            {
                buttonNextLogPage->setEnabled(true);
            }
        }
    }

    if(logPageNow == 0)
    {
        buttonPrevLogPage->setEnabled(false);
        buttonNextLogPage->setFocus();
    }
}
void EventLogPage::onButtonNextPage()
{
    QString oldStartTime = QDateTime(searchStartTime->dateTime()).toString("yyyy-MM-dd hh:mm");
    QString oldEndTime   = QDateTime(searchEndTime->dateTime()).toString("yyyy-MM-dd hh:mm");

    if(startTime != oldStartTime || endTime != oldEndTime)
    {
        onButtonSearch();
        return;
    }

    if(++logPageNow <= logPageNum)
    {
        EVENT_LOG_QUERY_S *pQuery = g_new0(EVENT_LOG_QUERY_S, 1);

        if(pQuery)
        {
            if(startTime <= endTime)
            {
                memcpy(pQuery->start_time, startTime.toStdString().c_str(), startTime.size());
                memcpy(pQuery->end_time,     endTime.toStdString().c_str(), endTime.size());
            }
            else
            {
                memcpy(pQuery->start_time,   endTime.toStdString().c_str(), endTime.size());
                memcpy(pQuery->end_time,   startTime.toStdString().c_str(), startTime.size());
            }

            pQuery->log_type = log_type;
            pQuery->log_sort = log_sort;
            pQuery->offset   = logPageNow * MAX_EVENT_LOG_PAGE_DATA;

            if(logPageNow == logPageNum)
            {
                pQuery->nLog = logCount % MAX_EVENT_LOG_PAGE_DATA;

                if(pQuery->nLog == 0)
                {
                    pQuery->nLog = MAX_EVENT_LOG_PAGE_DATA;
                }
            }
            else
            {
                pQuery->nLog = MAX_EVENT_LOG_PAGE_DATA;
            }

            event_send(QUEUE_QT_CORE, QUEUE_EVENT_LOG, EVENT_LOG_QUERY_DATA, pQuery, g_free, NULL);

            if(logPageNow > 0)
            {
                buttonPrevLogPage->setEnabled(true);
            }
        }
    }

    if(logPageNow == logPageNum)
    {
        buttonNextLogPage->setEnabled(false);
        buttonPrevLogPage->setFocus();
    }
}
void EventLogPage::onTreeViewClicked(const QModelIndex &index)
{
    qDebug("%s ===> row = %d", __func__, index.row());

    if(index.row() >= 0)
    {
        buttonPlay->setEnabled(true);
    }
    else
    {
        buttonPlay->setEnabled(false);
    }
}
void EventLogPage::onButtonSort()
{
    if(indexSort >= EVENT_LOG_ASC)
    {
        indexSort = 0;
    }

    switch(++indexSort)
    {
        case EVENT_LOG_DESC: { buttonSort->setText(tr("Desc")); } break;
        case EVENT_LOG_ASC:  { buttonSort->setText(tr("Asce")); } break;
    }

    log_sort = indexSort;
    buttonPlay->setEnabled(false);
    eventLogView->clearSelection();
    buttonSearch->setFocus();

    //qDebug("%s,%d===>logPageNum=%d,oIdxFt=%d,idxFt=%d,oIdxSt=%d,idxSt=%d\n",__func__,__LINE__,logPageNum,oldIndexFilter,indexFilter,oldIndexSort,indexSort);

    if((logPageNum > 0) && (oldIndexFilter == indexFilter) && (oldIndexSort == indexSort))
    {
        if(logPageNow < logPageNum)
        {
            buttonNextLogPage->setEnabled(true);
        }
        if(logPageNow == 0)
        {
            buttonPrevLogPage->setEnabled(false);
        }
        if(logPageNow > 0)
        {
            buttonPrevLogPage->setEnabled(true);
        }
        if(logPageNow == logPageNum)
        {
            buttonNextLogPage->setEnabled(false);
        }
    }
    else
    {
        buttonPrevLogPage->setEnabled(false);
        buttonNextLogPage->setEnabled(false);
    }
}
void EventLogPage::onButtonFilter()
{
    if(indexFilter >= EVENT_LOG_TRIGGER)
    {
        indexFilter = 0;
    }

    switch(++indexFilter)
    {
        case EVENT_LOG_ALL:     { buttonFilter->setText(tr("All"));     } break;
        case EVENT_LOG_IMPACT:  { buttonFilter->setText(tr("Impact"));  } break;
        case EVENT_LOG_TRIGGER: { buttonFilter->setText(tr("Trigger")); } break;
    }

    log_type = indexFilter;
    buttonPlay->setEnabled(false);
    eventLogView->clearSelection();
    buttonSearch->setFocus();

    //qDebug("%s,%d===>logPageNum=%d,oIdxFt=%d,idxFt=%d,oIdxSt=%d,idxSt=%d\n",__func__,__LINE__,logPageNum,oldIndexFilter,indexFilter,oldIndexSort,indexSort);

    if((logPageNum > 0) && (oldIndexFilter == indexFilter) && (oldIndexSort == indexSort))
    {
        if(logPageNow < logPageNum)
        {
            buttonNextLogPage->setEnabled(true);
        }

        if(logPageNow == 0)
        {
            buttonPrevLogPage->setEnabled(false);
        }

        if(logPageNow > 0)
        {
            buttonPrevLogPage->setEnabled(true);
        }

        if(logPageNow == logPageNum)
        {
            buttonNextLogPage->setEnabled(false);
        }
    }
    else
    {
        buttonPrevLogPage->setEnabled(false);
        buttonNextLogPage->setEnabled(false);
    }
}
void EventLogPage::onButtonPrevious()
{
    int *pIsLocalEventSearch = g_new0(int, 1);
    *pIsLocalEventSearch     = false;

    event_send(QUEUE_QT_CORE, QUEUE_WORK, WORK_EVENT_SET_LOCAL_EVENT_SEARCH, pIsLocalEventSearch, g_free, NULL);

    isEventSearch        = 0;
    eventBackupStartTime = 0;
    eventBackupEndTime   = 0;
    emit previousSearch(1);
}
void EventLogPage::onButtonPlayback()
{
    qDebug("%s ===> row = %d", __func__, eventLogView->currentIndex().row());

    if(eventLogView->currentIndex().row() >= 0)
    {
        int event_type         = gEventLog[eventLogView->currentIndex().row()].event_type;
        QDateTime preEventTime = QDateTime::fromString(gEventLog[eventLogView->currentIndex().row()].event_time, "yyyy-MM-dd hh:mm:ss").addSecs((-15)*event_type);
        time_t playTime        =  preEventTime.toTime_t();

        qDebug() << "preEventTime : " << preEventTime.toString("yyyy-MM-dd hh:mm:ss") << "time_t : " << preEventTime.toTime_t();

        if(playTime > 0)
        {
            int ch = 0xf, split = Split_4;
            int *pIsLocalEventSearch = g_new0(int, 1);
            *pIsLocalEventSearch     = true;

            event_send(QUEUE_QT_CORE, QUEUE_WORK, WORK_EVENT_SET_LOCAL_EVENT_SEARCH, pIsLocalEventSearch, g_free, NULL);

            SelectPbSplit        = split;
            EventSearchPB        = 1;
            isEventSearch        = 1;
            eventBackupStartTime = (playTime);
            eventBackupEndTime   = (playTime+((15*event_type)*2)+2);

            appmgr_search_play_start(ch, split*split, playTime, (15*event_type)*2);

            emit startPlayback();
        }
    }
}
void EventLogPage::onButtonClose()
{
    int *pIsLocalEventSearch = g_new0(int, 1);
    *pIsLocalEventSearch     = false;

    event_send(QUEUE_QT_CORE, QUEUE_WORK, WORK_EVENT_SET_LOCAL_EVENT_SEARCH, pIsLocalEventSearch, g_free, NULL);

    isEventSearch        = 0;
    eventBackupStartTime = 0;
    eventBackupEndTime   = 0;

    emit closeSearch();
}
void EventLogPage::resetSearch()
{
    eventLogModel->removeRows(0, eventLogModel->rowCount());
    searchStartTime->setDateTime(QDateTime::currentDateTime());
    searchStartTime->setDisplayFormat("yyyy.MM.dd hh:mm");
    searchEndTime->setDateTime(QDateTime::currentDateTime());
    searchEndTime->setDisplayFormat("yyyy.MM.dd hh:mm");
    labelPage->setText(tr("(0/0)"));
    labelLogResult->setText(tr("0"));
    buttonPrevLogPage->setEnabled(false);
    buttonNextLogPage->setEnabled(false);
    buttonPlay->setEnabled(false);
    buttonFilter->setText(tr("All"));
    buttonSort->setText(tr("Desc"));
    oldIndexFilter = EVENT_LOG_ALL;
    indexFilter    = EVENT_LOG_ALL;
    log_type       = EVENT_LOG_ALL;
    oldIndexSort   = EVENT_LOG_DESC;
    indexSort      = EVENT_LOG_DESC;
    log_sort       = EVENT_LOG_DESC;
    isKeyLock      = false;
    searchStartTime->setFocus();
}
void EventLogPage::setFocusToLogView(void)
{
    QModelIndex index;
    index = eventLogView->model()->index(0, 0); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
    index = eventLogView->model()->index(0, 1); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
    index = eventLogView->model()->index(0, 2); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
    eventLogView->setFocus();
    buttonPlay->setEnabled(true);
}
void EventLogPage::createEventLogView()
{
    proxyModel = new EventSortFilterProxyModel;

    eventLogView = new QTreeView(this);
    eventLogView->setRootIsDecorated(false);
    eventLogView->setAlternatingRowColors(true);
    eventLogView->setModel(proxyModel);
    eventLogView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    eventLogView->setStyleSheet("QHeaderView{font:27px;} QTreeView{font:27px;} QTreeView::item:selected{background:rgb(152,14,69);}");
}
void EventLogPage::createEventLogModel()
{
    eventLogModel = new QStandardItemModel(0, 4, this);
    eventLogModel->setHeaderData(0, Qt::Horizontal, QObject::tr("EVENT TIME"));
    eventLogModel->setHeaderData(0, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    eventLogModel->setHeaderData(1, Qt::Horizontal, QObject::tr("LOG TYPE"));
    eventLogModel->setHeaderData(1, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    eventLogModel->setHeaderData(2, Qt::Horizontal, QObject::tr("DURATION"));
    eventLogModel->setHeaderData(2, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    eventLogModel->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM"));
}
void EventLogPage::addEventLog(const QString &eventDateTime, const QString &eventLog, const QString &eventTime, int idx)
{
    int rowNum = eventLogModel->rowCount();

    eventLogModel->insertRow(rowNum);
    eventLogModel->setData(eventLogModel->index(rowNum, 0), eventDateTime);
    eventLogModel->setData(eventLogModel->index(rowNum, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    eventLogModel->setData(eventLogModel->index(rowNum, 1), eventLog);
    eventLogModel->setData(eventLogModel->index(rowNum, 1), Qt::AlignCenter, Qt::TextAlignmentRole);
    eventLogModel->setData(eventLogModel->index(rowNum, 2), eventTime);
    eventLogModel->setData(eventLogModel->index(rowNum, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
    eventLogModel->setData(eventLogModel->index(rowNum, 3), QVariant(idx));
}
void EventLogPage::itemViewSelectChange(int isForward)
{
    QModelIndex index;
    int lineNum, curRow;

    lineNum = eventLogView->model()->rowCount();

    if(lineNum == 0)
    {
        return;
    }

    index  = eventLogView->currentIndex();
    curRow = index.row();

    if(curRow < 0)
    {
        curRow = 0;
        index  = eventLogView->model()->index(curRow, 0); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
        index  = eventLogView->model()->index(curRow, 1); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
        index  = eventLogView->model()->index(curRow, 2); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);

        return;
    }

    qDebug("... logview row %d, line %d",curRow, lineNum);

    if(isForward)
    {
        if(++curRow >= lineNum)
        {
            curRow = 0;
        }
    }
    else
    {
        if(--curRow < 0)
        {
            curRow = lineNum - 1;
        }
    }

    index = eventLogView->model()->index(curRow, 0); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
    index = eventLogView->model()->index(curRow, 1); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
    index = eventLogView->model()->index(curRow, 2); eventLogView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
}
void EventLogPage::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if(searchStartTime->hasFocus() && isKeyLock)
            {
                switch(searchStartTime->currentSectionIndex())
                {
                    case 0: { searchStartTime->setDateTime(searchStartTime->dateTime().addYears(1));     break; }
                    case 1: { searchStartTime->setDateTime(searchStartTime->dateTime().addMonths(1));    break; }
                    case 2: { searchStartTime->setDateTime(searchStartTime->dateTime().addDays(1));      break; }
                    case 3: { searchStartTime->setDateTime(searchStartTime->dateTime().addSecs(3600));   break; }
                    case 4: { searchStartTime->setDateTime(searchStartTime->dateTime().addSecs(60));     break; }
                }
            }
            else if(searchEndTime->hasFocus() && isKeyLock)
            {
                switch(searchEndTime->currentSectionIndex())
                {
                    case 0: { searchEndTime->setDateTime(searchEndTime->dateTime().addYears(1));         break; }
                    case 1: { searchEndTime->setDateTime(searchEndTime->dateTime().addMonths(1));        break; }
                    case 2: { searchEndTime->setDateTime(searchEndTime->dateTime().addDays(1));          break; }
                    case 3: { searchEndTime->setDateTime(searchEndTime->dateTime().addSecs(3600));       break; }
                    case 4: { searchEndTime->setDateTime(searchEndTime->dateTime().addSecs(60));         break; }
                }
            }
            else if(eventLogView->hasFocus())                                      { itemViewSelectChange(0);        }
            else if(searchStartTime->hasFocus())                                   { buttonPrevious->setFocus();     }
            else if(searchEndTime->hasFocus())                                     { searchStartTime->setFocus();    }
            else if(buttonFilter->hasFocus())                                      { searchEndTime->setFocus();      }
            else if(buttonSort->hasFocus())                                        { searchEndTime->setFocus();      }
            else if(buttonSearch->hasFocus())                                      { buttonFilter->setFocus();       }
            else if(buttonPrevLogPage->hasFocus())                                 { buttonSearch->setFocus();       }
            else if(buttonNextLogPage->hasFocus())                                 { buttonSearch->setFocus();       }
            else if(buttonPlay->hasFocus() && buttonNextLogPage->isEnabled())      { buttonNextLogPage->setFocus();  }
            else if(buttonPlay->hasFocus() && buttonPrevLogPage->isEnabled())      { buttonPrevLogPage->setFocus();  }
            else if(buttonPlay->hasFocus())                                        { buttonSearch->setFocus();       }
            else if(buttonPrevious->hasFocus() && buttonPlay->isEnabled())         { buttonPlay->setFocus();         }
            else if(buttonPrevious->hasFocus() && buttonNextLogPage->isEnabled())  { buttonNextLogPage->setFocus();  }
            else if(buttonPrevious->hasFocus() && buttonPrevLogPage->isEnabled())  { buttonPrevLogPage->setFocus();  }
            else if(buttonPrevious->hasFocus())                                    { buttonSearch->setFocus();       }
            else if(buttonClose->hasFocus() && buttonPlay->isEnabled())            { buttonPlay->setFocus();         }
            else if(buttonClose->hasFocus() && buttonNextLogPage->isEnabled())     { buttonNextLogPage->setFocus();  }
            else if(buttonClose->hasFocus() && buttonPrevLogPage->isEnabled())     { buttonPrevLogPage->setFocus();  }
            else if(buttonClose->hasFocus())                                       { buttonSearch->setFocus();       }

            break;
        }
        case Qt::Key_Down:
        {
            if(searchStartTime->hasFocus() && isKeyLock)
            {
                switch(searchStartTime->currentSectionIndex())
                {
                    case 0: { searchStartTime->setDateTime(searchStartTime->dateTime().addYears(-1));    break; }
                    case 1: { searchStartTime->setDateTime(searchStartTime->dateTime().addMonths(-1));   break; }
                    case 2: { searchStartTime->setDateTime(searchStartTime->dateTime().addDays(-1));     break; }
                    case 3: { searchStartTime->setDateTime(searchStartTime->dateTime().addSecs(-3600));  break; }
                    case 4: { searchStartTime->setDateTime(searchStartTime->dateTime().addSecs(-60));    break; }
                }
            }
            else if(searchEndTime->hasFocus() && isKeyLock)
            {
                switch(searchEndTime->currentSectionIndex())
                {
                    case 0: { searchEndTime->setDateTime(searchEndTime->dateTime().addYears(-1));        break; }
                    case 1: { searchEndTime->setDateTime(searchEndTime->dateTime().addMonths(-1));       break; }
                    case 2: { searchEndTime->setDateTime(searchEndTime->dateTime().addDays(-1));         break; }
                    case 3: { searchEndTime->setDateTime(searchEndTime->dateTime().addSecs(-3600));      break; }
                    case 4: { searchEndTime->setDateTime(searchEndTime->dateTime().addSecs(-60));        break; }
                }
            }
            else if(eventLogView->hasFocus())                                         { itemViewSelectChange(1);       }
            else if(searchStartTime->hasFocus())                                      { searchEndTime->setFocus();     }
            else if(searchEndTime->hasFocus())                                        { buttonFilter->setFocus();      }
            else if(buttonFilter->hasFocus())                                         { buttonSearch->setFocus();      }
            else if(buttonSort->hasFocus())                                           { buttonSearch->setFocus();      }
            else if(buttonSearch->hasFocus() && buttonNextLogPage->isEnabled())       { buttonNextLogPage->setFocus(); }
            else if(buttonSearch->hasFocus() && buttonPrevLogPage->isEnabled())       { buttonPrevLogPage->setFocus(); }
            else if(buttonSearch->hasFocus() && buttonPlay->isEnabled())              { buttonPlay->setFocus();        }
            else if(buttonSearch->hasFocus())                                         { buttonPrevious->setFocus();    }
            else if(buttonNextLogPage->hasFocus() && buttonPlay->isEnabled())         { buttonPlay->setFocus();        }
            else if(buttonNextLogPage->hasFocus())                                    { buttonPrevious->setFocus();    }
            else if(buttonPrevLogPage->hasFocus() && buttonPlay->isEnabled())         { buttonPlay->setFocus();        }
            else if(buttonPrevLogPage->hasFocus())                                    { buttonPrevious->setFocus();    }
            else if(buttonPlay->hasFocus())                                           { buttonPrevious->setFocus();    }
            else if(buttonPrevious->hasFocus())                                       { searchStartTime->setFocus();   }
            else if(buttonClose->hasFocus())                                          { searchStartTime->setFocus();   }

            break;
        }
        case Qt::Key_Left:
        {
            if(searchStartTime->hasFocus() && isKeyLock)
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
            else if(searchEndTime->hasFocus() && isKeyLock)
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
            else if((searchStartTime->hasFocus()   ||  searchEndTime->hasFocus() ||
                     buttonFilter->hasFocus()      ||  buttonSearch->hasFocus()  ||
                     buttonPrevLogPage->hasFocus() ||  buttonPlay->hasFocus()    ||
                     buttonPrevious->hasFocus())   && (eventLogView->model()->rowCount() > 0))
            {
                setFocusToLogView();
            }
            else if(buttonFilter->hasFocus())                                          { buttonSort->setFocus();        }
            else if(buttonSort->hasFocus())                                            { buttonFilter->setFocus();      }
            else if(buttonNextLogPage->hasFocus() && buttonPrevLogPage->isEnabled())   { buttonPrevLogPage->setFocus(); }
            else if(buttonNextLogPage->hasFocus() &&
                   !buttonPrevLogPage->isEnabled() &&
                    eventLogView->model()->rowCount() > 0)                             { setFocusToLogView();           }
            else if(buttonPrevious->hasFocus())                                        { buttonClose->setFocus();       }
            else if(buttonClose->hasFocus())                                           { buttonPrevious->setFocus();    }
            else if(eventLogView->hasFocus() && buttonPlay->isEnabled())               { buttonPlay->setFocus();        }
            else if(eventLogView->hasFocus())                                          { buttonSearch->setFocus();      }

            break;
        }
        case Qt::Key_Right:
        {
            if(searchStartTime->hasFocus() && isKeyLock)
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
            else if(searchEndTime->hasFocus() && isKeyLock)
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
            else if((searchStartTime->hasFocus()   ||  searchEndTime->hasFocus() ||
                     buttonSort->hasFocus()        ||  buttonSearch->hasFocus()  ||
                     buttonNextLogPage->hasFocus() ||  buttonPlay->hasFocus()    ||
                     buttonClose->hasFocus())      && (eventLogView->model()->rowCount() > 0))
            {
                setFocusToLogView();
            }
            else if(buttonSort->hasFocus())                                            { buttonFilter->setFocus();       }
            else if(buttonFilter->hasFocus())                                          { buttonSort->setFocus();         }
            else if(buttonPrevLogPage->hasFocus() && buttonNextLogPage->isEnabled())   { buttonNextLogPage->setFocus();  }
            else if(buttonPrevLogPage->hasFocus() &&
                   !buttonNextLogPage->isEnabled() &&
                    eventLogView->model()->rowCount() > 0)                             { setFocusToLogView();            }
            else if(buttonPrevious->hasFocus())                                        { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())                                           { buttonPrevious->setFocus();     }
            else if(eventLogView->hasFocus() && buttonPlay->isEnabled())               { buttonPlay->setFocus();         }
            else if(eventLogView->hasFocus())                                          { buttonSearch->setFocus();       }

            break;
        }
        case Qt::Key_Enter:
        {
            if(searchStartTime->hasFocus() || searchEndTime->hasFocus())          { isKeyLock = true;               }
            else if(buttonFilter->hasFocus())                                          { onButtonFilter();               }
            else if(buttonSort->hasFocus())                                            { onButtonSort();                 }
            else if(buttonSearch->hasFocus())                                          { onButtonSearch();               }
            else if(buttonPrevLogPage->hasFocus())                                     { onButtonPreviousPage();         }
            else if(buttonNextLogPage->hasFocus())                                     { onButtonNextPage();             }
            else if(buttonPlay->hasFocus())                                            { onButtonPlayback();             }
            else if(buttonPrevious->hasFocus())                                        { onButtonPrevious();             }
            else if(buttonClose->hasFocus())                                           { onButtonClose();                }

            break;
        }
        case Qt::Key_Escape:
        {
            if(isKeyLock)
            {
                isKeyLock = false;
            }
            else
            {
                onButtonPrevious();
            }

            break;
        }
        case Qt::Key_PageUp:
        {
            if(buttonNextLogPage->isEnabled())
            {
                eventLogView->clearSelection();
                buttonNextLogPage->setFocus();
                onButtonNextPage();
            }

            break;
        }
        case Qt::Key_PageDown:
        {
            if(buttonPrevLogPage->isEnabled())
            {
                eventLogView->clearSelection();
                buttonPrevLogPage->setFocus();
                onButtonPreviousPage();
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
