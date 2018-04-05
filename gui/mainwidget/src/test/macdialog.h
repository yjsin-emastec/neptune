#ifndef MACDIALOG_H
#define MACDIALOG_H

#include <QtGui/QDialog>
#include "ui_macdialog.h"

class MacDialog : public QDialog, public Ui::MacDialog
{
    Q_OBJECT

public:
    MacDialog(QWidget *parent = 0);
    ~MacDialog();
    void initMac(char *mac);
    QString mac;

signals:

public slots:

private slots:
	void onButtonUp1(void);
	void onButtonDn1(void);
	void onButtonUp2(void);
	void onButtonDn2(void);
	void onButtonUp3(void);
	void onButtonDn3(void);
	void onButtonUp4(void);
	void onButtonDn4(void);
	void onButtonUp5(void);
	void onButtonDn5(void);
	void onButtonUp6(void);
	void onButtonDn6(void);
	void onButtonUp7(void);
	void onButtonDn7(void);
	void onButtonUp8(void);
	void onButtonDn8(void);
	void onButtonUp9(void);
	void onButtonDn9(void);
	void onButtonUp10(void);
	void onButtonDn10(void);
	void onButtonUp11(void);
	void onButtonDn11(void);
	void onButtonUp12(void);
	void onButtonDn12(void);

	void onButtonAllClear(void);
	void onButtonDefault(void);
	void onButtonSave(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
    char *Dec2Hex(char *val);
    char tmp[64];
    int  idxMac[12], kk, ii;
    bool isLockEsc;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MACDIALOG_H
