#ifndef SECURITYDIALOG_H
#define SECURITYDIALOG_H

#include <QtGui/QDialog>
#include "ui_securitydialog.h"
#include "DVR.h"

class SecurityDialog;
class UiKeyboardDialog;

class SecurityDialog : public QDialog, public Ui::SecurityDialog
{
    Q_OBJECT

public:
    SecurityDialog(QWidget *parent = 0);
    ~SecurityDialog();
	void initSecurityConfig(void);

signals:
	;

public slots:
	void onButtonNewPassword(void);
	void onButtonConfirmPassword(void);
	void onButtonSystemLock(void);
	void onButtonSave(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	UiKeyboardDialog *keyboard;
	char newPassword[16], confirmPassword[16];
	int isInputNewPassword, isInputConfirmPassword, indexSystemLock;
};

#endif // SECURITYDIALOG_H
