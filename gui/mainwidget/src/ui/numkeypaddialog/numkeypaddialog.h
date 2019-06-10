#ifndef NUMKEYPADDIALOG_H
#define NUMKEYPADDIALOG_H

#include <QDialog>
#include "textmessagebox/textmessagedialog.h"
#include "ui_numkeypaddialog.h"
#include "ui_numkeypaddialog1080p.h"

class NumKeypadDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit NumKeypadDialog(QWidget *parent = 0);
	~NumKeypadDialog();
	void updateConfig(bool isNumberOnly);
	void setPhoneNumber(bool enable);
	void setText(QString text);
	void setMaximumNumber(int max);
	QString text();
	
private slots:
	void on_pushButton_Close_clicked();
	void on_pushButton_Enter_clicked();
	void on_pushButton_Clear_clicked();
	void on_pushButton_Backspace_clicked();
	void on_pushButton_0_clicked();
	void on_pushButton_1_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	void on_pushButton_8_clicked();
	void on_pushButton_9_clicked();
	void on_pushButton_Dot_clicked();

private:
	bool checkMaximumNumber(QString addVal);
	void checkAutoDot();
	QString Text;
	int maxNumber;
	bool isNetworkPort;
	bool isNetworkIPv4;
	bool isPhoneNumber;
	TextMessageDialog *msgBox;

    QFrame *frame_Border;
    QFrame *frame_Body;
    QLineEdit *lineEdit_Text;
    QPushButton *pushButton_0;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_Backspace;
    QPushButton *pushButton_Clear;
    QPushButton *pushButton_Close;
    QPushButton *pushButton_Dot;
    QPushButton *pushButton_Enter;
    QPushButton *pushButton_Not;

protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif // NUMKEYPADDIALOG_H
