#ifndef TIMESETDIALOG_H
#define TIMESETDIALOG_H

#include <QtGui/QDialog>
#include "ui_timesetdialog.h"

class TimeSetDialog;

class TimeSetDialog : public QDialog, public Ui::TimeSetDialog
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
};

#endif // TIMESETDIALOG_H
