#ifndef APPUPGRADEDIALOG_H
#define APPUPGRADEDIALOG_H

#include <QtGui/QDialog>
#include "ui_appupgradedialog.h"
#include "ui_appupgradedialog1080p.h"

class TextMessageDialog;

class AppUpgradeDialog : public QDialog
{
    Q_OBJECT

public:
    AppUpgradeDialog(QWidget *parent = 0);
    ~AppUpgradeDialog();
    void initAppUpgradeConfig(void);

signals:

public slots:
    void onButtonFind(void);
    void onButtonUpgrade(void);
    void initButton(void);
    void ConfirmUpgradeResult(void);
    void onUpgradeProgress(int percent);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void UpdateLabelStatus(int message);
    int  ButtonFind(int isUnMount);
    void Delay(int millisecondsToWait);
    void StartTimer(void);
    char fileName[512];
    QTimer *upgradeTimer;
    TextMessageDialog *msgBox;
    bool upgradeState;

    QFrame *frame;
    QLabel *labelStatus;
    QLabel *labelModelName;
    QLabel *labelModelNameValue;
    QLabel *labelVersion;
    QLabel *labelVersionValue;
    QLabel *labelFileName;
    QLabel *labelFileNameValue;
    QLabel *labelProgress;
    QLabel *labelProgressValue;
    QProgressBar *progressBar;
    QPushButton *buttonFind;
    QPushButton *buttonUpgrade;
    QPushButton *buttonClose;
};

#endif // APPUPGRADEDIALOG_H
