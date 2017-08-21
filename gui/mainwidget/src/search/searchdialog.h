#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "ui_searchdialog.h"

class QStackedLayout;
class CalendarPage;
class EventLogPage;

class SearchDialog : public QDialog, public Ui::SearchDialog
{
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
    int pbChBit, pbSplit, pbType, recType;

signals:
	void searchDataRead();

public slots:
    void onSearchDataUpdate(int type);
    void onSearchCalendarUpdate(int type);
	void onNormal();
	void onEvent();
	void onQueryLogCount();
	void onQueryLogData();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onButtonClose();
    void onHideCalendarPage(int typ);
    void onStartPlayback();

private:
    QStackedLayout  *stackedLayout;
    CalendarPage    *calendarPage;
    EventLogPage    *eventPage;
};

#endif // SEARCHDIALOG_H
