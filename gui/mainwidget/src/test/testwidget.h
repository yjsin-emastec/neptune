#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QtGui/QMainWindow>
#include <QFile>
#include <testmgr.h>
#include "diagmaindialog.h"
#include "../dvrsetup/device/diskformat/diskformatprocess.h"

class TestEventController;
class EventRecvThread;

class TestWidget : public QMainWindow
{
    Q_OBJECT

public:
    TestWidget                       (void);
    ~TestWidget                      (void);

    int  DiskFormatStart             (void);

    DiagMainDialog                  *MainDialog;
    TestEventController             *eventController;
    EventRecvThread                 *Thread;
    DiskFormatProcessDialog         *pDiskFormatProcessDialog;

    int                              diskFormatNum;

signals:

private slots:
    void onPassKeypadEvent           (int KeyCode);
    void onRunDiagnosticsMenu        (void);
    void onDiskFormatProcessDlgClose (void);

protected:
    void mouseMoveEvent              (QMouseEvent *event);
    void mousePressEvent             (QMouseEvent *event);
    void alignWidget                 (QWidget *widget, int align);
    void LoadStyleSheet              (void);
    void DiskFormatProcessDlgOpen    (void);
};

#endif // TESTWIDGET_H
