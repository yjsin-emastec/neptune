#ifndef SYSTEMLOGPAGE_H
#define SYSTEMLOGPAGE_H

#include <QtGui/QWidget>
#include "ui_systemlogpage.h"
#include "main/mainglobal.h"
#include "main/mainwidget.h"

class EventSortFilterProxyModel;
class QTreeView;
class FunctionDialog;
class SystemLogPage : public QWidget, public Ui::LogPage
{
    Q_OBJECT

public:
    SystemLogPage(QWidget *parent = 0);
    ~SystemLogPage();

    void resetLog();
    void onQueryLogCount();
    void onQueryLogData();
    void KeyPressEvent(int key);

signals:
    void previousSearch (int type);
    void closeSearch    (int type);

private slots:
    void onButtonPrevious();
    void onButtonClose();
    void onButtonSearch();
    void onButtonFunction();
    void onButtonPageUp();
    void onButtonPageDn();

private:
    EventSortFilterProxyModel *proxyModel;
    QAbstractItemModel *systemLogModel;
    FunctionDialog *functionDialog;
    SYSTEM_LOG_QUERY_S *pQuery;

    int logCount, logPageNow, logPageNum;
    QString startTime,endTime;
    QString logFilter, logSort;
    QString ampmStatus;
    bool isKeyLock, isSearch;


    void updateLogCount();
    void addEventLog(const QString &logDateTime, const QString &log);
    QString changeTimeformat(char event_time[20]);
};



#endif // SYSTEMLOGPAGE_H
