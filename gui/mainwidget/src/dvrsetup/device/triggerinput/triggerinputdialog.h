#ifndef TRIGGERINPUTDIALOG_H
#define TRIGGERINPUTDIALOG_H

#include <QtGui/QDialog>
#include "textmessagebox/textmessagedialog.h"
#include "DVR.h"

#if defined(HI3521)
#include "ui_triggerinputdialog_ch4.h"
#include "ui_triggerinputdialog1080p_ch4.h"
#define NUMOFCH 4

#elif defined(HI3531D)
#include "ui_triggerinputdialog.h"
#include "ui_triggerinputdialog1080p.h"
#define NUMOFCH 8
#endif

class TriggerInputDialog : public QDialog, public Ui::TriggerInputDialog
{
    Q_OBJECT

public:
    TriggerInputDialog(QWidget *parent = 0);
    ~TriggerInputDialog();

    void initTriggerInputConfig(void);

signals:

private slots:

    void onButtonSourceAll();
    void onButtonDelayAll();
    void onButtonPriorityAll();
    void onButtonAudioAll();

    void onButtonSourceUp1();
    void onButtonSourceUp2();
    void onButtonSourceUp3();
    void onButtonSourceUp4();
    void onButtonSourceUp5();
    void onButtonSourceUp6();
    void onButtonSourceUp7();
    void onButtonSourceUp8();

    void onButtonSourceDn1();
    void onButtonSourceDn2();
    void onButtonSourceDn3();
    void onButtonSourceDn4();
    void onButtonSourceDn5();
    void onButtonSourceDn6();
    void onButtonSourceDn7();
    void onButtonSourceDn8();

    void onButtonDelayUp1();
    void onButtonDelayUp2();
    void onButtonDelayUp3();
    void onButtonDelayUp4();
    void onButtonDelayUp5();
    void onButtonDelayUp6();
    void onButtonDelayUp7();
    void onButtonDelayUp8();

    void onButtonDelayDn1();
    void onButtonDelayDn2();
    void onButtonDelayDn3();
    void onButtonDelayDn4();
    void onButtonDelayDn5();
    void onButtonDelayDn6();
    void onButtonDelayDn7();
    void onButtonDelayDn8();

    void onButtonPriorityUp1();
    void onButtonPriorityUp2();
    void onButtonPriorityUp3();
    void onButtonPriorityUp4();
    void onButtonPriorityUp5();
    void onButtonPriorityUp6();
    void onButtonPriorityUp7();
    void onButtonPriorityUp8();

    void onButtonPriorityDn1();
    void onButtonPriorityDn2();
    void onButtonPriorityDn3();
    void onButtonPriorityDn4();
    void onButtonPriorityDn5();
    void onButtonPriorityDn6();
    void onButtonPriorityDn7();
    void onButtonPriorityDn8();

    void onButtonAudioUp1();
    void onButtonAudioUp2();
    void onButtonAudioUp3();
    void onButtonAudioUp4();
    void onButtonAudioUp5();
    void onButtonAudioUp6();
    void onButtonAudioUp7();
    void onButtonAudioUp8();

    void onButtonAudioDn1();
    void onButtonAudioDn2();
    void onButtonAudioDn3();
    void onButtonAudioDn4();
    void onButtonAudioDn5();
    void onButtonAudioDn6();
    void onButtonAudioDn7();
    void onButtonAudioDn8();

    void onButtonSave();
    void onButtonDefault();


protected:
    void keyPressEvent(QKeyEvent *event);


private:

    QFrame *frame;

    QPushButton *buttonSourceUp[NUMOFCH];
    QPushButton *buttonSourceDn[NUMOFCH];
    QPushButton *buttonDelayUp[NUMOFCH];
    QPushButton *buttonDelayDn[NUMOFCH];
    QPushButton *buttonPriorityUp[NUMOFCH];
    QPushButton *buttonPriorityDn[NUMOFCH];
    QPushButton *buttonAudioUp[NUMOFCH];
    QPushButton *buttonAudioDn[NUMOFCH];
    QPushButton *buttonSourceAll, *buttonDelayAll, *buttonPriorityAll, *buttonAudioAll;

    QLabel *labelTrigger[NUMOFCH+1];
    QLabel *labelSource[NUMOFCH+1];
    QLabel *labelDelay[NUMOFCH+1];
    QLabel *labelPriority[NUMOFCH+1];
    QLabel *labelAudio[NUMOFCH+1];

    QPushButton *buttonDefault;
    QPushButton *buttonSave;
    QPushButton *buttonClose;

    int infoSource[NUMOFCH+1];
    int infoDelay[NUMOFCH+1];
    int infoPriority[NUMOFCH+1];
    bool infoAudio[NUMOFCH+1];

    void updateSourceLabel(int ch);
    void updateDelayLabel(int ch);
    void updatePriorityLabel(int ch);
    void updateAudioLabel(int ch);

    void onButtonSourceUp(int ch);
    void onButtonSourceDn(int ch);
    void onButtonDelayUp(int ch);
    void onButtonDelayDn(int ch);
    void onButtonPriorityUp(int ch);
    void onButtonPriorityDn(int ch);
    void onButtonAudioUp(int ch);
    void onButtonAudioDn(int ch);

    int checkPriorityRedundant();

    TextMessageDialog *msgBox;

};

#endif // TRIGGERINPUTDIALOG_H
