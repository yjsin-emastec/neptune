#ifndef VIDEOINPUTBAR_H
#define VIDEOINPUTBAR_H

#include <QtGui/QDialog>
#include "ui_videoinputbar.h"
#include "ui_videoinputbar1080p.h"

#define NUMOFCH 8

class VideoInputBar : public QDialog
{
    Q_OBJECT

public :
    VideoInputBar(QWidget *parent = 0);
    ~VideoInputBar();

    void setInfo(int[], int[]);
    void getInfo(int[], int[]);

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
    void onButtonClose();

protected :
    void keyPressEvent(QKeyEvent *event);

private :
    QFrame *frame;
    QPushButton *buttonCh[NUMOFCH+1];
    QPushButton *buttonMirror;
    QPushButton *buttonFlip;
    QPushButton *buttonClose;

    int selectedCh;
    int infoMirror[NUMOFCH+1];
    int infoFlip[NUMOFCH+1];

    void updateButton();
};

#endif // VIDEOINPUTBAR_H
