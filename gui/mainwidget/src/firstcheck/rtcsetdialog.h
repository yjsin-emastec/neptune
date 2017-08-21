#ifndef RTCSETDIALOG_H
#define RTCSETDIALOG_H

#include <QtGui/QDialog>
#include "ui_rtcsetdialog.h"

class RtcSetDialog;

class RtcSetDialog : public QDialog, public Ui::RtcSetDialog
{
    Q_OBJECT

public:
    RtcSetDialog(QWidget *parent = 0);
    ~RtcSetDialog();
    void GetTime(time_t *time);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    bool isKeyLock;
    time_t tOld;
    QTimer *updateTimer;

private slots:
    void onUpdateStatus(void);

};

#endif // RTCSETDIALOG_H
