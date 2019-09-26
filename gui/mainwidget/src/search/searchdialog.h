#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "ui_searchdialog.h"
#include "ui_searchdialog1080p.h"
#include "ui/customwidget/customimagelabel.h"

class QStackedLayout;
class CalendarPage;
class EventLogPage;
class SystemLogPage;

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
    int pbChBit, pbSplit, pbType, recType;

    QFrame *frame;
    QFrame *frameTitle;
    QFrame *frameContents;

    CustomImageLabel *buttonTitle;
    CustomImageLabel *buttonNormal;
    CustomImageLabel *buttonEvent;
    CustomImageLabel *buttonLog;
    CustomImageLabel *buttonClose;

    QLabel *labelTitleText;
    QLabel *labelNormalText;
    QLabel *labelEventText;
    QLabel *labelLogText;
    QLabel *labelCloseText;

signals:
	void searchDataRead();

public slots:
    void onSearchDataUpdate(int type);
    void onSearchCalendarUpdate(int type);
	void onNormal();
	void onEvent();
    void onLog();
	void onQueryLogCount();
	void onQueryLogData();
	void onSystemLogCount  (void);
	void onSystemLogData   (void);
	void onSystemLogBackup (void);

    void setFocusNormal(void);
    void setFocusEvent(void);
    void setFocusLog(void);
    void setFocusClose(void);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onButtonClose      (void);
    void onButtonClose      (int type);
    void onHideCalendarPage (int type);
    void onStartPlayback    ();

private:
    QStackedLayout  *stackedLayout;
    CalendarPage    *calendarPage;
    EventLogPage    *eventPage;
    SystemLogPage   *systemLogPage;

    QPixmap iconImageNormal[5];
    QPixmap iconImageFocus[5];

    void changeFocus(int n);
};

#endif // SEARCHDIALOG_H
