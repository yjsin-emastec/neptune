#ifndef EVENTLOGPAGE_H
#define EVENTLOGPAGE_H

#include <QWidget>

class QTreeView;
class QAbstractItemModel;
class QLabel;
class QString;
class QPushButton;
class QDateTimeEdit;
class EventSortFilterProxyModel;
class QModelIndex;

class EventLogPage : public QWidget
{
    Q_OBJECT

public:
    EventLogPage(QWidget *parent = 0);
   ~EventLogPage();
    void resetSearch();
	void onQueryLogCount();
	void onQueryLogData();
	void KeyPressEvent(int key);

signals:
	void previousSearch(int type);
	void closeSearch();
	void startPlayback();

private slots:
	void onButtonFilter();
	void onButtonSort();
	void onButtonSearch();
	void onButtonPreviousPage();
	void onButtonNextPage();
	void onButtonPrevious();
	void onButtonPlayback();
	void onButtonClose();
	void onTreeViewClicked(const QModelIndex &index);

private:
    void createEventLogView();
    void createEventLogModel();
	void addEventLog(const QString &eventDateTime, const QString &eventLog, const QString &eventTime, int idx);
    void itemViewSelectChange(int isForward);
    void setFocusToLogView(void);

    EventSortFilterProxyModel  *proxyModel;
    QTreeView                  *eventLogView;
    QAbstractItemModel         *eventLogModel;

    QDateTimeEdit              *searchStartTime,
                               *searchEndTime;

    QLabel                     *labelStartTime,
                               *labelEndTime,
                               *labelFilter,
                               *labelLog,
                               *labelLogResult,
                               *labelPage;

    QPushButton                *buttonFilter,
                               *buttonSort,
                               *buttonSearch,
                               *buttonPrevLogPage,
                               *buttonNextLogPage,
                               *buttonPlay,
                               *buttonPrevious,
                               *buttonClose;

    int                         logCount,
                                logPageNow,
                                logPageNum,
                                log_type,
                                log_sort,
                                indexFilter,
                                indexSort,
                                oldIndexFilter,
                                oldIndexSort;

    QString                     startTime,
                                endTime;

    bool                        isKeyLock;
};

#endif // EVENTLOGPAGE_H
