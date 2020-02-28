#include <QtGui>
#include "markerdialog.h"
#include "main/mainglobal.h"

MarkerDialog::MarkerDialog(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 255, 255 ,0)));
}
MarkerDialog::~MarkerDialog()
{
}
void MarkerDialog::initMarker()
{
    loadMarkerConfig();

    bold    = 30;
    len     = 25;
    penType = 0;
    ch      = 0;

    if (mainHeight == 1080 )
    {
        this->resize(this->width()*1.5, this->height()*1.5);

        bold *= 1.5;
        len  *= 1.5;
    }

    leftStartBackup  = leftStart;
    leftEndBackup    = leftEnd;
    rightStartBackup = rightStart;
    rightEndBackup   = rightEnd;
}
void MarkerDialog::loadMarkerConfig()
{
#if 1   //marker config don't exist
    leftStart.setX(580);
    leftStart.setY(100);
    leftEnd.setX(220);
    leftEnd.setY(610);

    rightStart.setX(700);
    rightStart.setY(100);
    rightEnd.setX(1060);
    rightEnd.setY(610);
#else
    leftStart .setX(QString(DeviceCfg.trigger_marker_left_start_x));
    leftStart .setY(QString(DeviceCfg.trigger_marker_left_start_y));
    leftEnd   .setX(QString(DeviceCfg.trigger_marker_left_end_x));
    leftEnd   .setY(QString(DeviceCfg.trigger_marker_left_end_y));

    rightStart.setX(QString(DeviceCfg.trigger_marker_right_start_x));
    rightStart.setY(QString(DeviceCfg.trigger_marker_right_start_y));
    rightEnd  .setX(QString(DeviceCfg.trigger_marker_right_end_x));
    rightEnd  .setY(QString(DeviceCfg.trigger_marker_right_end_y));
#endif

    if (mainHeight == 1080 )
    {
        leftStart *=1.5;
        leftEnd   *=1.5;
        rightStart*=1.5;
        rightEnd  *=1.5;
    }
}
void MarkerDialog::paintEvent(QPaintEvent *event)
{
    int gap  = 5;
    int wing = len;

    QPainter painter(this);
    QPen mypen(Qt::red, bold);

    if     (penType==1) { mypen.setStyle(Qt::DashLine);
                          mypen.setDashPattern(QVector<qreal>() << 3 <<2 ); }
    else if(penType==2) { mypen.setStyle(Qt::DotLine);   }
    else                { mypen.setStyle(Qt::SolidLine); }

    mypen.setCapStyle(Qt::RoundCap);

    mypen.setColor(Qt::green);
    painter.setPen(mypen);

    painter.drawLine(  leftStart.x(), leftStart.y(),
                       leftStart.x()-abs( leftStart.x()- leftEnd.x())* 5/36,             leftStart.y()+abs( leftEnd.y()- leftStart.y())* 5/36);
    painter.drawLine( rightStart.x(),rightStart.y(),
                      rightStart.x()+abs(rightStart.x()-rightEnd.x())* 5/36,            rightStart.y()+abs(rightEnd.y()-rightStart.y())* 5/36);

    painter.drawLine(  leftStart.x()+gap,       leftStart.y()-gap,
                       leftStart.x()+gap+wing,   leftStart.y()-gap);
    painter.drawLine( rightStart.x()-gap,      rightStart.y()-gap,
                      rightStart.x()-gap-wing,  rightStart.y()-gap);

    mypen.setColor(Qt::yellow);
    painter.setPen(mypen);
    wing=wing*12/5;

    painter.drawLine(  leftStart.x()-abs( leftStart.x()- leftEnd.x())*12/36,             leftStart.y()+abs( leftEnd.y()- leftStart.y())*12/36,
                       leftStart.x()-abs( leftStart.x()- leftEnd.x())*20/36,             leftStart.y()+abs( leftEnd.y()- leftStart.y())*20/36);
    painter.drawLine( rightStart.x()+abs(rightStart.x()-rightEnd.x())*12/36,            rightStart.y()+abs(rightEnd.y()-rightStart.y())*12/36,
                      rightStart.x()+abs(rightStart.x()-rightEnd.x())*20/36,            rightStart.y()+abs(rightEnd.y()-rightStart.y())*20/36);

    painter.drawLine(  leftStart.x()-abs( leftStart.x()- leftEnd.x())*12/36+gap,         leftStart.y()+abs( leftEnd.y()- leftStart.y())*12/36-gap,
                       leftStart.x()-abs( leftStart.x()- leftEnd.x())*12/36+gap+wing,    leftStart.y()+abs( leftEnd.y()- leftStart.y())*12/36-gap);
    painter.drawLine( rightStart.x()+abs(rightStart.x()-rightEnd.x())*12/36-gap,        rightStart.y()+abs(rightEnd.y()-rightStart.y())*12/36-gap,
                      rightStart.x()+abs(rightStart.x()-rightEnd.x())*12/36-gap-wing,   rightStart.y()+abs(rightEnd.y()-rightStart.y())*12/36-gap);

    mypen.setColor(Qt::red);
    painter.setPen(mypen);
    wing=wing*27/12;

    painter.drawLine(  leftStart.x()-abs( leftStart.x()- leftEnd.x())*27/36,             leftStart.y()+abs( leftEnd.y()- leftStart.y())*27/36,
                       leftStart.x()-abs( leftStart.x()- leftEnd.x()),                   leftStart.y()+abs( leftEnd.y()- leftStart.y()) );
    painter.drawLine( rightStart.x()+abs(rightStart.x()-rightEnd.x())*27/36,            rightStart.y()+abs(rightEnd.y()-rightStart.y())*27/36,
                      rightStart.x()+abs(rightStart.x()-rightEnd.x()),                  rightStart.y()+abs(rightEnd.y()-rightStart.y()) );

    painter.drawLine(  leftStart.x()-abs( leftStart.x()- leftEnd.x())*27/36+gap,         leftStart.y()+abs( leftEnd.y()- leftStart.y())*27/36-gap,
                       leftStart.x()-abs( leftStart.x()- leftEnd.x())*27/36+gap+wing,    leftStart.y()+abs( leftEnd.y()- leftStart.y())*27/36-gap);
    painter.drawLine( rightStart.x()+abs(rightStart.x()-rightEnd.x())*27/36-gap,        rightStart.y()+abs(rightEnd.y()-rightStart.y())*27/36-gap,
                      rightStart.x()+abs(rightStart.x()-rightEnd.x())*27/36-gap-wing,   rightStart.y()+abs(rightEnd.y()-rightStart.y())*27/36-gap);
}
void MarkerDialog::updateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4)
{
    leftStart  = p1;
    leftEnd    = p2;
    rightStart = p3;
    rightEnd   = p4;

    update();
}
bool MarkerDialog::isChangedConfig()
{
    bool result = true;

    if(    ( leftStartBackup ==  leftStart) && ( leftEndBackup == leftEndBackup)
        && (rightStartBackup == rightStart) && (rightEndBackup == rightEnd)     )
    {
        result = false;
    }

    return result;
}
