#ifndef VIDEOINPUTBAR_H
#define VIDEOINPUTBAR_H

#include <QtGui/QDialog>

#if defined(HI3521)
#include "ui_videoinputbar_ch4.h"
#include "ui_videoinputbar1080p_ch4.h"
#define NUMOFCH 4

#elif defined(HI3531D)
#include "ui_videoinputbar.h"
#include "ui_videoinputbar1080p.h"
#define NUMOFCH 8

#endif

class VideoInputBar : public QDialog
{
    Q_OBJECT

public :
    VideoInputBar(QWidget *parent = 0);
    ~VideoInputBar();

    void setInfo(int mirror[], int flip[], int rotate[]);
    void getInfo(int mirror[], int flip[], int rotate[]);

signals :
    void videoInputPreview();

private slots :
    void onButtonCh(int n);
    void onButtonCh1();
    void onButtonCh2();
    void onButtonCh3();
    void onButtonCh4();
    void onButtonCh5();
    void onButtonCh6();
    void onButtonCh7();
    void onButtonCh8();
    void onButtonChAll();
    void onButtonMirror();
    void onButtonFlip();
    void onButtonRotate();
    void onButtonClose();

protected :
    void keyPressEvent(QKeyEvent *event);

private :
    QFrame *frame;
    QPushButton *buttonCh[NUMOFCH+1];
    QPushButton *buttonMirror;
    QPushButton *buttonFlip;
    QPushButton *buttonRotate;
    QPushButton *buttonClose;

    int selectedCh;
    int infoMirror[NUMOFCH+1];
    int infoFlip[NUMOFCH+1];
    int infoRotate[NUMOFCH+1];

    void saveConfig();
    void updateButton();
};

#endif // VIDEOINPUTBAR_H
