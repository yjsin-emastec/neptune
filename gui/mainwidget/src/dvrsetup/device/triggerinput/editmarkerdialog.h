#ifndef EDITMARKERDIALOG_H
#define EDITMARKERDIALOG_H

#include <QtGui/QDialog>

#include "ui_editmarkerdialog.h"
#include "ui_editmarkerdialog1080p.h"
#include <QtCore/qmath.h>

class EditMarkerDialog : public QDialog
{
    Q_OBJECT

public :
    EditMarkerDialog(QWidget *parent = 0);
    ~EditMarkerDialog();

    void initMarker(int ch);
    void setMarkerCh(int ch);

public slots:
    void onButtonChUp();
    void onButtonChDn();
    void onButtonXUp();
    void onButtonXDn();
    void onButtonYUp();
    void onButtonYDn();
    void onButtonWUp();
    void onButtonWDn();
    void onButtonHUp();
    void onButtonHDn();
    void onButtonSUp();
    void onButtonSDn();
    void loadMarkerConfig();
    void onButtonClose();

protected :
    void keyPressEvent(QKeyEvent *event);

signals :
    void changeMarkerChannel(int ch);
    void updateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4);

private :
    void updateLabel();
    void updateMarker();

    int markerCh;
    int len;
    int moveSize;

    QPoint leftStart;
    QPoint leftEnd;
    QPoint rightStart;
    QPoint rightEnd;

    QPoint midLine1Start;
    QPoint midLine1End;
    QPoint midLine2Start;
    QPoint midLine2End;
    QPoint midLine3Start;
    QPoint midLine3End;

    QFrame *frame;

    QLabel *labelCh;
    QLabel *labelTextX;
    QLabel *labelTextY;
    QLabel *labelTextW;
    QLabel *labelTextH;
    QLabel *labelTextS;

    QPushButton *buttonChUp;
    QPushButton *buttonChDn;
    QPushButton *buttonXUp;
    QPushButton *buttonXDn;
    QPushButton *buttonYUp;
    QPushButton *buttonYDn;
    QPushButton *buttonWUp;
    QPushButton *buttonWDn;
    QPushButton *buttonHUp;
    QPushButton *buttonHDn;
    QPushButton *buttonSUp;
    QPushButton *buttonSDn;
    QPushButton *buttonReload;
    QPushButton *buttonClose;
};

#endif // EDITMARKERDIALOG_H
