#include <QtGui>
#include "eventsortfilterproxymodel.h"

EventSortFilterProxyModel::EventSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}
bool EventSortFilterProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);

    return (sourceModel()->data(index0).toString().contains(filterRegExp())
            && sourceModel()->data(index1).toString().contains(filterEventRegExp));
}
void EventSortFilterProxyModel::setEventFilterRegExp ( const QRegExp & regExp )
{
    filterEventRegExp = regExp;
}
