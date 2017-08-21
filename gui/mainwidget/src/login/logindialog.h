#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtGui/QDialog>
#include "DVR.h"
#include "ui_logindialog.h"

class UiKeyboardDialog;

enum { CHECK_SETUP = 0, CHECK_SEARCH, CHECK_RECORD_OFF, CHECK_POWER_ON, CHECK_POWER_OFF, CHECK_LOCK, CHECK_BACKUP, CHECK_UNLOCK };

class LoginDialog : public QDialog, public Ui::LoginDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void updateConfig(int checkMode);
    int  selUserId;
    QString PasswordString;

public slots:
    void showKeyboard();
    void checkPassword();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    UiKeyboardDialog *keyboardDialog;
};

#endif // LOGINDIALOG_H
