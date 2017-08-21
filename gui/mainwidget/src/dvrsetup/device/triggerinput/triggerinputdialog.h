#ifndef TRIGGERINPUTDIALOG_H
#define TRIGGERINPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_triggerinputdialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "DVR.h"

#define  EASTERN_MAXIMUM_PRIORITY   8

class TextMessageDialog;

class TriggerInputDialog : public QDialog, public Ui::TriggerInputDialog
{
    Q_OBJECT

public:
    TriggerInputDialog(QWidget *parent = 0);
    ~TriggerInputDialog();
	void initTriggerInputConfig(void);

signals:

public slots:
	void onButtonSource1Up(void);
	void onButtonSource1Down(void);
	void onButtonSource2Up(void);
	void onButtonSource2Down(void);
	void onButtonSource3Up(void);
	void onButtonSource3Down(void);
	void onButtonSource4Up(void);
	void onButtonSource4Down(void);

	void onButtonDelay1Up(void);
	void onButtonDelay1Down(void);
	void onButtonDelay2Up(void);
	void onButtonDelay2Down(void);
	void onButtonDelay3Up(void);
	void onButtonDelay3Down(void);
	void onButtonDelay4Up(void);
	void onButtonDelay4Down(void);

	void onButtonPriority1Up(void);
	void onButtonPriority1Down(void);
	void onButtonPriority2Up(void);
	void onButtonPriority2Down(void);
	void onButtonPriority3Up(void);
	void onButtonPriority3Down(void);
	void onButtonPriority4Up(void);
	void onButtonPriority4Down(void);

	void onButtonDefault(void);
	void onButtonSave(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
    int isPriorityRedundant(void);

    int indexSource1,
        indexSource2,
        indexSource3,
        indexSource4,
        indexDelay1,
        indexDelay2,
        indexDelay3,
        indexDelay4,
        indexPriority1,
        indexPriority2,
        indexPriority3,
        indexPriority4,
        nPriority[EASTERN_MAXIMUM_PRIORITY];

    TextMessageDialog *msgBox;
};

#endif // TRIGGERINPUTDIALOG_H
