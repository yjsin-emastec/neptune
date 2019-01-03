#ifndef NORMALDIALOG_H
#define NORMALDIALOG_H

#include <QtGui/QDialog>
#include "ui_normaldialog.h"
#include "DVR.h"

#define NUMOFCH 4

class NormalDialog : public QDialog
{
    Q_OBJECT

public:
    NormalDialog(QWidget *parent = 0);
    ~NormalDialog();
    void initNormalConfig(void);

signals:

public slots:
    void onButtonFrame1(void);
    void onButtonFrame2(void);
    void onButtonFrame3(void);
    void onButtonFrame4(void);
    void onButtonFrameAll(void);

    void onButtonQuality1(void);
    void onButtonQuality2(void);
    void onButtonQuality3(void);
    void onButtonQuality4(void);
    void onButtonQualityAll(void);

    void onButtonRecording1(void);
    void onButtonRecording2(void);
    void onButtonRecording3(void);
    void onButtonRecording4(void);
    void onButtonRecordingAll(void);

    void onButtonAudio1(void);
    void onButtonAudio2(void);
    void onButtonAudio3(void);
    void onButtonAudio4(void);
    void onButtonAudioAll(void);

    void onButtonDefault(void);
    void onButtonReload(void);
    void onButtonSave(void);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    int infoFrame[NUMOFCH];
    int infoQuality[NUMOFCH];
    bool infoRecording[NUMOFCH];
    bool infoAudio[NUMOFCH];

    QFrame *frame;
    QPushButton *buttonFrame[NUMOFCH+1];
    QPushButton *buttonQuality[NUMOFCH+1];
    QPushButton *buttonRecording[NUMOFCH+1];
    QPushButton *buttonAudio[NUMOFCH+1];
    QPushButton *buttonDefault;
    QPushButton *buttonReload;
    QPushButton *buttonSave;
    QPushButton *buttonClose;

    QLabel *labelFrame[NUMOFCH+1];
    QLabel *labelQuality[NUMOFCH+1];
    QLabel *labelRecording[NUMOFCH+1];
    QLabel *labelAudio[NUMOFCH+1];
    QLabel *labelAll;
    QLabel *labelCh[NUMOFCH];

    int getMaxFrame(int chNum);
    void updateFrameText(int chNum);
    void updateQualityText(int chNum);
    void updateRecordingText(int chNum);
    void updateAudioText(int chNum);

    bool isFirstClickButtnFrame;
    bool isFirstClickButtnQuality;

};

#endif // NORMALDIALOG_H
