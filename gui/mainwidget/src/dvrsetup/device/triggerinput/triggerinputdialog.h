#ifndef TRIGGERINPUTDIALOG_H
#define TRIGGERINPUTDIALOG_H

#include <QtGui/QDialog>
#include "textmessagebox/textmessagedialog.h"
#include "editmarkerdialog.h"
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
    void viewMarkerEdit(int state);
    void makeTransparent(int n);
    void changeMarkerChannel(int ch);
    void updateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4);

private slots:
    void onButtonSourceAll();
    void onButtonDelayAll();
    void onButtonPriorityAll();
    void onButtonAudioAll();
    void onButtonMarkerAll();

    void onButtonSource1();
    void onButtonSource2();
    void onButtonSource3();
    void onButtonSource4();
    void onButtonSource5();
    void onButtonSource6();
    void onButtonSource7();
    void onButtonSource8();

    void onButtonDelay1();
    void onButtonDelay2();
    void onButtonDelay3();
    void onButtonDelay4();
    void onButtonDelay5();
    void onButtonDelay6();
    void onButtonDelay7();
    void onButtonDelay8();

    void onButtonPriority1();
    void onButtonPriority2();
    void onButtonPriority3();
    void onButtonPriority4();
    void onButtonPriority5();
    void onButtonPriority6();
    void onButtonPriority7();
    void onButtonPriority8();

    void onButtonAudio1();
    void onButtonAudio2();
    void onButtonAudio3();
    void onButtonAudio4();
    void onButtonAudio5();
    void onButtonAudio6();
    void onButtonAudio7();
    void onButtonAudio8();

    void onButtonMarker1();
    void onButtonMarker2();
    void onButtonMarker3();
    void onButtonMarker4();
    void onButtonMarker5();
    void onButtonMarker6();
    void onButtonMarker7();
    void onButtonMarker8();

    void onButtonSave();
    void onButtonDefault();
    void onButtonEditMarker();

    void onChangeMarkerChannel(int ch);
    void onUpdateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QFrame *frame;

    QLabel *labelTrigger[NUMOFCH];
    QLabel *labelAll;
    QLabel *labelSourceAll;
    QLabel *labelDelayAll;
    QLabel *labelPriorityAll;
    QLabel *labelAudioAll;
    QLabel *labelMarkerAll;

    QPushButton *buttonSourceAll, *buttonDelayAll, *buttonPriorityAll, *buttonAudioAll, *buttonMarkerAll;
    QPushButton *buttonSource[NUMOFCH];
    QPushButton *buttonDelay[NUMOFCH];
    QPushButton *buttonPriority[NUMOFCH];
    QPushButton *buttonAudio[NUMOFCH];
    QPushButton *buttonMarker[NUMOFCH];

    QPushButton *buttonDefault;
    QPushButton *buttonEditMarker;
    QPushButton *buttonSave;
    QPushButton *buttonClose;

    int infoSource[NUMOFCH];
    int infoDelay[NUMOFCH];
    int infoPriority[NUMOFCH];
    bool infoAudio[NUMOFCH];
    bool infoMarker[NUMOFCH];

    void updateSourceLabel(int ch);
    void updateDelayLabel(int ch);
    void updatePriorityLabel(int ch);
    void updateAudioLabel(int ch);
    void updateMarkerLabel(int ch);

    void onButtonSource(int ch);
    void onButtonDelay(int ch);
    void onButtonPriority(int ch);
    void onButtonAudio(int ch);
    void onButtonMarker(int ch);

    int checkPriorityRedundant();

    TextMessageDialog *msgBox;
    EditMarkerDialog *editMarkerDialog;
};

#endif // TRIGGERINPUTDIALOG_H
