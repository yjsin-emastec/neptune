#ifndef VIDEOINPUTDIALOG_H
#define VIDEOINPUTDIALOG_H

#include <QtGui/QDialog>

#if defined(HI3521)
#include "ui_videoinputdialog_ch4.h"
#include "ui_videoinputdialog1080p_ch4.h"
#define NUMOFCH 4

#elif defined(HI3531D)
#include "ui_videoinputdialog.h"
#include "ui_videoinputdialog1080p.h"
#define NUMOFCH 8
#endif

class VideoInputBar;

class VideoInputDialog : public QDialog
{
    Q_OBJECT

public:
    VideoInputDialog(QWidget *parent = 0);
    ~VideoInputDialog();
	void initVideoInputConfig(void);

signals:
    void makeTransparent(int n);
    void videoInputPreview();

public slots:
    void onButtonMirror(int ch);
    void onButtonMirror1();
    void onButtonMirror2();
    void onButtonMirror3();
    void onButtonMirror4();
    void onButtonMirror5();
    void onButtonMirror6();
    void onButtonMirror7();
    void onButtonMirror8();
    void onButtonMirrorAll();

    void onButtonFlip(int ch);
    void onButtonFlip1();
    void onButtonFlip2();
    void onButtonFlip3();
    void onButtonFlip4();
    void onButtonFlip5();
    void onButtonFlip6();
    void onButtonFlip7();
    void onButtonFlip8();
    void onButtonFlipAll();

    void onButtonRotate(int ch);
    void onButtonRotate1();
    void onButtonRotate2();
    void onButtonRotate3();
    void onButtonRotate4();
    void onButtonRotate5();
    void onButtonRotate6();
    void onButtonRotate7();
    void onButtonRotate8();
    void onButtonRotateAll();

    void onButtonType(int ch);
    void onButtonType1();
    void onButtonType2();
    void onButtonType3();
    void onButtonType4();
    void onButtonType5();
    void onButtonType6();
    void onButtonType7();
    void onButtonType8();
    void onButtonTypeAll();

    void onButtonPreview();
    void onButtonDefault();
    void onButtonSave();
    void onButtonClose();
    void onVideoInputPreview();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
    int infoMirror[NUMOFCH+1];
    int infoFlip[NUMOFCH+1];
    int infoRotate[NUMOFCH+1];
    int infoType[NUMOFCH+1];
    int backupMirror[NUMOFCH+1];
    int backupFlip[NUMOFCH+1];
    int backupRotate[NUMOFCH+1];
    int backupType[NUMOFCH+1];

    QFrame *frame;
    QPushButton *buttonMirror[NUMOFCH+1];
    QPushButton *buttonFlip[NUMOFCH+1];
    QPushButton *buttonRotate[NUMOFCH+1];
    QPushButton *buttonType[NUMOFCH+1];
    QPushButton *buttonPreview;
    QPushButton *buttonDefault;
    QPushButton *buttonSave;
    QPushButton *buttonClose;

    QLabel *labelCh[NUMOFCH+1];
    QLabel *labelMirror[NUMOFCH+1];
    QLabel *labelFlip[NUMOFCH+1];
    QLabel *labelRotate[NUMOFCH+1];
    QLabel *labelType[NUMOFCH+1];

    VideoInputBar *videoInputBar;

    void updateButton();
};

#endif // VIDEOINPUTDIALOG_H
