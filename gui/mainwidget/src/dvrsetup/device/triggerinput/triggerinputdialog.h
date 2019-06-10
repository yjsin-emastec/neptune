#ifndef TRIGGERINPUTDIALOG_H
#define TRIGGERINPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_triggerinputdialog.h"
#include "ui_triggerinputdialog1080p.h"
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

    void onButtonAudio1Up(void);
    void onButtonAudio1Down(void);
    void onButtonAudio2Up(void);
    void onButtonAudio2Down(void);
    void onButtonAudio3Up(void);
    void onButtonAudio3Down(void);
    void onButtonAudio4Up(void);
    void onButtonAudio4Down(void);

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

    bool triggerAudio1,
         triggerAudio2,
         triggerAudio3,
         triggerAudio4;

    TextMessageDialog *msgBox;

    QFrame *frame;

    QPushButton *buttonAudio1Down;
    QPushButton *buttonAudio1Up;
    QPushButton *buttonAudio2Down;
    QPushButton *buttonAudio2Up;
    QPushButton *buttonAudio3Down;
    QPushButton *buttonAudio3Up;
    QPushButton *buttonAudio4Down;
    QPushButton *buttonAudio4Up;
    QPushButton *buttonDelay1Down;
    QPushButton *buttonDelay1Up;
    QPushButton *buttonDelay2Down;
    QPushButton *buttonDelay2Up;
    QPushButton *buttonDelay3Down;
    QPushButton *buttonDelay3Up;
    QPushButton *buttonDelay4Down;
    QPushButton *buttonDelay4Up;
    QPushButton *buttonPriority1Down;
    QPushButton *buttonPriority1Up;
    QPushButton *buttonPriority2Down;
    QPushButton *buttonPriority2Up;
    QPushButton *buttonPriority3Down;
    QPushButton *buttonPriority3Up;
    QPushButton *buttonPriority4Down;
    QPushButton *buttonPriority4Up;
    QPushButton *buttonSource1Down;
    QPushButton *buttonSource1Up;
    QPushButton *buttonSource2Down;
    QPushButton *buttonSource2Up;
    QPushButton *buttonSource3Down;
    QPushButton *buttonSource3Up;
    QPushButton *buttonSource4Down;
    QPushButton *buttonSource4Up;
    QPushButton *buttonClose;
    QPushButton *buttonDefault;
    QPushButton *buttonSave;

    QLabel *labelAudio1;
    QLabel *labelAudio2;
    QLabel *labelAudio3;
    QLabel *labelAudio4;
    QLabel *labelDelay1;
    QLabel *labelDelay2;
    QLabel *labelDelay3;
    QLabel *labelDelay4;
    QLabel *labelPriority1;
    QLabel *labelPriority2;
    QLabel *labelPriority3;
    QLabel *labelPriority4;
    QLabel *labelSource1;
    QLabel *labelSource2;
    QLabel *labelSource3;
    QLabel *labelSource4;
    QLabel *labelTrigger1;
    QLabel *labelTrigger2;
    QLabel *labelTrigger3;
    QLabel *labelTrigger4;
};

#endif // TRIGGERINPUTDIALOG_H
