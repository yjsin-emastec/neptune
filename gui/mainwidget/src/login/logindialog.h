#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtGui/QDialog>
#include "DVR.h"
#include "ui_logindialog.h"
#include "ui_logindialog1080p.h"

class UiKeyboardDialog;

enum { CHECK_SETUP = 0, CHECK_SEARCH, CHECK_RECORD_OFF, CHECK_POWER_ON, CHECK_POWER_OFF, CHECK_LOCK, CHECK_BACKUP, CHECK_UNLOCK, CHECK_FORMAT };

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void updateConfig(int checkMode);
    int  selUserId;
    QString PasswordString;
    UiKeyboardDialog *keyboardDialog;

public slots:
    void showKeyboard();
    void checkPassword();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QFrame *frame;
    QPushButton *buttonCancel;
    QPushButton *buttonEdit;
    QPushButton *buttonOk;
    QLineEdit *lineEditPassword;
    QLabel *labelPassword;
};

#endif // LOGINDIALOG_H
