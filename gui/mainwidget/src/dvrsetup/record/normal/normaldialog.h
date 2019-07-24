#ifndef NORMALDIALOG_H
#define NORMALDIALOG_H

#include <QtGui/QDialog>
#include "ui_normaldialog.h"
#include "ui_normaldialog1080p.h"
#include "DVR.h"

#define NUMOFCH 8

class NormalDialog : public QDialog
{
    Q_OBJECT

public:
    NormalDialog(QWidget *parent = 0);
    ~NormalDialog();
    void initNormalConfig(void);

signals:

public slots:
    void onButtonFrame(int chNum);
    void onButtonFrame1(void);
    void onButtonFrame2(void);
    void onButtonFrame3(void);
    void onButtonFrame4(void);
    void onButtonFrame5(void);
    void onButtonFrame6(void);
    void onButtonFrame7(void);
    void onButtonFrame8(void);
    void onButtonFrameAll(void);

    void onButtonQuality(int chNum);
    void onButtonQuality1(void);
    void onButtonQuality2(void);
    void onButtonQuality3(void);
    void onButtonQuality4(void);
    void onButtonQuality5(void);
    void onButtonQuality6(void);
    void onButtonQuality7(void);
    void onButtonQuality8(void);
    void onButtonQualityAll(void);

    void onButtonRecording(int chNum);
    void onButtonRecording1(void);
    void onButtonRecording2(void);
    void onButtonRecording3(void);
    void onButtonRecording4(void);
    void onButtonRecording5(void);
    void onButtonRecording6(void);
    void onButtonRecording7(void);
    void onButtonRecording8(void);
    void onButtonRecordingAll(void);

    void onButtonAudio(int chNum);
    void onButtonAudio1(void);
    void onButtonAudio2(void);
    void onButtonAudio3(void);
    void onButtonAudio4(void);
    void onButtonAudio5(void);
    void onButtonAudio6(void);
    void onButtonAudio7(void);
    void onButtonAudio8(void);
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
    QLabel *labelCh[NUMOFCH+1];

    int getMaxFrame(int chNum);
    void updateFrameText(int chNum);
    void updateQualityText(int chNum);
    void updateRecordingText(int chNum);
    void updateAudioText(int chNum);

    bool isFirstClickButtonFrame;
    bool isFirstClickButtonQuality;

};

#endif // NORMALDIALOG_H
