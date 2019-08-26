#ifndef VIDEOINPUTDIALOG_H
#define VIDEOINPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_videoinputdialog.h"
#include "ui_videoinputdialog1080p.h"

#define NUMOFCH 8

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

    void onButtonPreview();
    void onButtonSave();
    void onButtonClose();
    void onVideoInputPreview();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
    int infoMirror[NUMOFCH+1];
    int infoFlip[NUMOFCH+1];
    int backupMirror[NUMOFCH+1];
    int backupFlip[NUMOFCH+1];

    QFrame *frame;
    QPushButton *buttonMirror[NUMOFCH+1];
    QPushButton *buttonFlip[NUMOFCH+1];
    QPushButton *buttonPreview;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
    QLabel *labelCh[NUMOFCH+1];

    VideoInputBar *videoInputBar;

    void updateButton();
};

#endif // VIDEOINPUTDIALOG_H
