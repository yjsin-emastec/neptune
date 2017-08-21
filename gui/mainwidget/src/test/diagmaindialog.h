#ifndef DIAGMAINDIALOG_H
#define DIAGMAINDIALOG_H

#include <QtGui/QDialog>
#include "ui_diagmaindialog.h"

class TestModeDialog;
class TestWidget;

class DiagMainDialog : public QDialog, public Ui::DiagMainDialog
{
    Q_OBJECT

public:
    DiagMainDialog               (QWidget *parent = 0);
    ~DiagMainDialog              ();
    void DisplayUsbMouse2        (QMouseEvent *event);
    void DisplayRemoteCtrl2      (QString str);
    void Delay                   (int millisecondsToWait);

signals:

public slots:

private slots:
    void onGsensorUpdate         (void);
    void onButtonMac2            (void);
    void onButtonNetworkPing2    (void);
    void onButtonAudio2          (void);
    void onButtonLedBuzzer2      (void);
    void onButtonFormat2         (void);
    void onButtonFactoryDefault2 (void);
    void onButtonApplication2    (void);

private:
    TestWidget   *pTestWidget;
    int           flagBuzzLed;

protected:
    void keyPressEvent           (QKeyEvent *event);

    QWidget      *Main;

    int           flagAudio;

protected slots:
    void onCheckStart            (void);
};

#endif // DIAGMAINDIALOG_H
