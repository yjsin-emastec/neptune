#ifndef RTCSETDIALOG_H
#define RTCSETDIALOG_H

#include <QtGui/QDialog>
#include "ui_rtcsetdialog.h"
#include "ui_rtcsetdialog1080p.h"
class RtcSetDialog;

class RtcSetDialog : public QDialog
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
    bool eventFilter(QObject *obj, QEvent *event);

    QFrame *frame;
    QLabel *label;
    QLabel *labelRtcTitle;
    QLabel *labelRtcStatus;
    QDateTimeEdit *dateTimeRtc;
    QPushButton *buttonSetRestart;

private slots:
    void onUpdateStatus(void);

};

#endif // RTCSETDIALOG_H
