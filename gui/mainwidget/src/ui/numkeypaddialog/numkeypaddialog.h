#ifndef NUMKEYPADDIALOG_H
#define NUMKEYPADDIALOG_H

#include <QDialog>
#include "textmessagebox/textmessagedialog.h"

namespace Ui {
class NumKeypadDialog;
class TextMessageDialog;
}

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
	Ui::NumKeypadDialog *ui;
	bool checkMaximumNumber(QString addVal);
	void checkAutoDot();
	QString Text;
	int maxNumber;
	bool isNetworkPort;
	bool isNetworkIPv4;
	bool isPhoneNumber;
	TextMessageDialog *msgBox;

protected:
	void keyPressEvent(QKeyEvent *event);
};

#endif // NUMKEYPADDIALOG_H
