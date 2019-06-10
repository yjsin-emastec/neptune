#ifndef TEXTMESSAGEDIALOG_H
#define TEXTMESSAGEDIALOG_H

#include <QtGui/QDialog>
#include <QFile>
#include "ui_textmessagedialog.h"

class QLabel;
class QPushButton;

class TextMessageDialog : public QDialog, public Ui::TextMessageDialog
{
    Q_OBJECT

public:
    TextMessageDialog(const QString & title = 0, const QString & text = 0, int buttonType = 0, QWidget *parent = 0);
    ~TextMessageDialog();
	QPushButton *buttonOk, *buttonCancel;
    void setMsgAlignment(Qt::Alignment alignment);

signals:
    void waitDlgReady();
	void waitVideoOutput();
	void timeMismatchCheckClose();
	void signalResetTimer();
	
protected:
	void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *event);

private slots:
    void doWait();
	void buttonAccept();
	void buttonReject();
	void timeMismatchEndCheck();
	void doTest();
private:
	int msgType;
    QLabel *labelTitle, *labelMsg, *labelMsg1, *labelMsg2;
};

#endif // TEXTMESSAGEDIALOG_H
