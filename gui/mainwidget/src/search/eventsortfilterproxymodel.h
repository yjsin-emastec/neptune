#ifndef EVENTSORTFILTERPROXYMODEL_H
#define EVENTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class EventSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    EventSortFilterProxyModel(QObject *parent = 0);
    void setEventFilterRegExp ( const QRegExp & regExp );
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    QRegExp filterEventRegExp;
};

#endif // EVENTSORTFILTERPROXYMODEL_H
