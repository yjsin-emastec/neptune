#ifndef TIMESETDIALOG_H
#define TIMESETDIALOG_H

#include <QtGui/QDialog>
#include "ui_timesetdialog.h"
#include "ui_timesetdialog1080p.h"

class TimeSetDialog;

class TimeSetDialog : public QDialog
{
    Q_OBJECT

public:
    TimeSetDialog(QWidget *parent = 0);
    ~TimeSetDialog();
    void GetTime(time_t *time);
    void DisplayRecordTime(void);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onButtonDeleteData(void);
    void onButtonSetTime(void);
    void onUpdateStatus(void);

private:
    bool isKeyLock;
    void Delay(int millisecondsToWait);
    time_t tOld;
    QTimer *updateTimer;
    bool eventFilter(QObject *obj, QEvent *event);

    QFrame *frame;
    QLabel *labelTimeTitle;
    QLabel *labelTimeStatus;
    QLabel *labelFirstTime1;
    QLabel *labelFirstTime2;
    QLabel *labelLastTime1;
    QLabel *labelLastTime2;
    QLabel *labelSystemTime1;
    QLabel *labelSystemTime2;
    QDateTimeEdit *dateTimeSystem;
    QPushButton *buttonDeleteData;
    QPushButton *buttonSetTime;
};

#endif // TIMESETDIALOG_H
