#ifndef MARKERDIALOG_H
#define MARKERDIALOG_H

#include <QtGui/QWidget>
#include <QtCore/qmath.h>

class MarkerDialog : public QWidget
{
    Q_OBJECT

public :
    MarkerDialog(QWidget *parent = 0);
    ~MarkerDialog();

    void initMarker();
    void updateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4);
    bool isChangedConfig();

protected :
    void paintEvent(QPaintEvent *event);

private :
    int ch;
    int len;
    int bold;
    int penType;

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

    QPoint leftStartBackup;
    QPoint leftEndBackup;
    QPoint rightStartBackup;
    QPoint rightEndBackup;

    void loadMarkerConfig();
};

#endif // MARKERDIALOG_H
