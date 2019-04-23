#ifndef APPUPGRADEDIALOG_H
#define APPUPGRADEDIALOG_H

#include <QtGui/QDialog>
#include "ui_appupgradedialog.h"

class TextMessageDialog;

class AppUpgradeDialog : public QDialog, public Ui::AppUpgradeDialog
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
};

#endif // APPUPGRADEDIALOG_H
