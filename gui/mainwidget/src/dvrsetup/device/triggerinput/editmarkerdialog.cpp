#include <QtGui>
#include "editmarkerdialog.h"
#include "main/mainglobal.h"

EditMarkerDialog::EditMarkerDialog(QWidget *parent)
    : QDialog(parent)
{
    if( mainHeight == 720 )
    {
        Ui::EditMarkerDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        labelCh     = ui720.labelCh;
        labelTextX  = ui720.labelTextX;
        labelTextY  = ui720.labelTextY;
        labelTextW  = ui720.labelTextW;
        labelTextH  = ui720.labelTextH;
        labelTextS  = ui720.labelTextS;

        buttonChUp  = ui720.buttonChUp;
        buttonChDn  = ui720.buttonChDn;
        buttonXUp   = ui720.buttonXUp;
        buttonXDn   = ui720.buttonXDn;
        buttonYUp   = ui720.buttonYUp;
        buttonYDn   = ui720.buttonYDn;
        buttonWUp   = ui720.buttonWUp;
        buttonWDn   = ui720.buttonWDn;
        buttonHUp   = ui720.buttonHUp;
        buttonHDn   = ui720.buttonHDn;
        buttonSUp   = ui720.buttonSUp;
        buttonSDn   = ui720.buttonSDn;
        buttonReload= ui720.buttonReload;
        buttonClose = ui720.buttonClose;

        len         = 25;
        moveSize    = 4;
    }
    else
    {
        Ui::EditMarkerDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        labelCh     = ui1080.labelCh;
        labelTextX  = ui1080.labelTextX;
        labelTextY  = ui1080.labelTextY;
        labelTextW  = ui1080.labelTextW;
        labelTextH  = ui1080.labelTextH;
        labelTextS  = ui1080.labelTextS;

        buttonChUp  = ui1080.buttonChUp;
        buttonChDn  = ui1080.buttonChDn;
        buttonXUp   = ui1080.buttonXUp;
        buttonXDn   = ui1080.buttonXDn;
        buttonYUp   = ui1080.buttonYUp;
        buttonYDn   = ui1080.buttonYDn;
        buttonWUp   = ui1080.buttonWUp;
        buttonWDn   = ui1080.buttonWDn;
        buttonHUp   = ui1080.buttonHUp;
        buttonHDn   = ui1080.buttonHDn;
        buttonSUp   = ui1080.buttonSUp;
        buttonSDn   = ui1080.buttonSDn;
        buttonReload= ui1080.buttonReload;
        buttonClose = ui1080.buttonClose;

        labelCh   ->setStyleSheet("font:50px;");
        labelTextX->setStyleSheet("font:50px;");
        labelTextY->setStyleSheet("font:50px;");
        labelTextW->setStyleSheet("font:50px;");
        labelTextH->setStyleSheet("font:50px;");
        labelTextS->setStyleSheet("font:50px;");

        len        = 25*1.5;
        moveSize   = 4*1.5;
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setPalette(QPalette(QColor(255, 128, 64)));

    frame->setStyleSheet("background-color: rgb(39, 0, 79)");

    connect(buttonXUp,   SIGNAL(clicked()), this, SLOT(onButtonXUp()));
    connect(buttonXDn,   SIGNAL(clicked()), this, SLOT(onButtonXDn()));
    connect(buttonYUp,   SIGNAL(clicked()), this, SLOT(onButtonYUp()));
    connect(buttonYDn,   SIGNAL(clicked()), this, SLOT(onButtonYDn()));
    connect(buttonWUp,   SIGNAL(clicked()), this, SLOT(onButtonWUp()));
    connect(buttonWDn,   SIGNAL(clicked()), this, SLOT(onButtonWDn()));
    connect(buttonHUp,   SIGNAL(clicked()), this, SLOT(onButtonHUp()));
    connect(buttonHDn,   SIGNAL(clicked()), this, SLOT(onButtonHDn()));
    connect(buttonSUp,   SIGNAL(clicked()), this, SLOT(onButtonSUp()));
    connect(buttonSDn,   SIGNAL(clicked()), this, SLOT(onButtonSDn()));
    connect(buttonChUp,  SIGNAL(clicked()), this, SLOT(onButtonChUp()));
    connect(buttonChDn,  SIGNAL(clicked()), this, SLOT(onButtonChDn()));
    connect(buttonReload,SIGNAL(clicked()), this, SLOT(loadMarkerConfig()));
    connect(buttonClose, SIGNAL(clicked()), this, SLOT(onButtonClose()));

    setMarkerCh(0);
}
EditMarkerDialog::~EditMarkerDialog()
{
}
void EditMarkerDialog::initMarker(int ch)
{
    loadMarkerConfig();

    setMarkerCh(ch);
    buttonChUp->setFocus();
    updateLabel();
}
void EditMarkerDialog::loadMarkerConfig()
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

    if( mainHeight == 1080 )
    {
        leftStart *= 1.5;
        leftEnd   *= 1.5;
        rightStart*= 1.5;
        rightEnd  *= 1.5;
    }

    updateMarker();
}
void EditMarkerDialog::onButtonClose()
{
#if 1   //marker config don't exist
    qDebug() << "save left s:"  << QString::number(leftStart.x()) << ", " << QString::number(leftStart.y());
    qDebug() << "save left e:"  << QString::number(leftEnd.x())   << ", " << QString::number(leftEnd.y());
    qDebug() << "save right s:" << QString::number(rightStart.x())<< ", " << QString::number(rightStart.y());
    qDebug() << "save right e:" << QString::number(rightEnd.x())  << ", " << QString::number(rightEnd.y());
#else
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_left_start_x,  QString::number(leftStart.x()) .toStdString().c_str() );
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_left_start_y,  QString::number(leftStart.y()) .toStdString().c_str() );
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_left_end_x,    QString::number(leftEnd.x())   .toStdString().c_str() );
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_left_end_y,    QString::number(leftEnd.y())   .toStdString().c_str() );

    utils_cfg_cpy_item( DeviceCfg.trigger_marker_right_start_x, QString::number(rightStart.x()).toStdString().c_str() );
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_right_start_y, QString::number(rightStart.y()).toStdString().c_str() );
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_right_end_x,   QString::number(rightEnd.x())  .toStdString().c_str() );
    utils_cfg_cpy_item( DeviceCfg.trigger_marker_right_end_y,   QString::number(rightEnd.y())  .toStdString().c_str() );
#endif

    accept();
}
void EditMarkerDialog::onButtonXUp()
{
    if( rightEnd.x() >= mainWidth ) { return; }

    leftStart .setX( leftStart .x() + moveSize );
    leftEnd   .setX( leftEnd   .x() + moveSize );
    rightStart.setX( rightStart.x() + moveSize );
    rightEnd  .setX( rightEnd  .x() + moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonXDn()
{
    if( leftEnd.x() <= 0 ) { return; }

    leftStart .setX( leftStart .x() - moveSize );
    leftEnd   .setX( leftEnd   .x() - moveSize );
    rightStart.setX( rightStart.x() - moveSize );
    rightEnd  .setX( rightEnd  .x() - moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonYUp()
{
    if( leftEnd.y() >= mainHeight ) { return; }

    leftStart .setY( leftStart .y() + moveSize );
    leftEnd   .setY( leftEnd   .y() + moveSize );
    rightStart.setY( rightStart.y() + moveSize );
    rightEnd  .setY( rightEnd  .y() + moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonYDn()
{
    if( leftStart.y() <= 0 ) { return; }

    leftStart .setY( leftStart .y() - moveSize );
    leftEnd   .setY( leftEnd   .y() - moveSize );
    rightStart.setY( rightStart.y() - moveSize );
    rightEnd  .setY( rightEnd  .y() - moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonWUp()
{
    if( leftEnd.x() <= 0 || rightEnd.x() >= mainWidth ) { return; }

    leftStart .setX( leftStart .x() - moveSize/2 );
    leftEnd   .setX( leftEnd   .x() - moveSize/2 );
    rightStart.setX( rightStart.x() + moveSize/2 );
    rightEnd  .setX( rightEnd  .x() + moveSize/2 );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonWDn()
{
    if( rightStart.x()-leftStart.x() <= len ) { return; }

    leftStart .setX( leftStart .x() + moveSize/2 );
    leftEnd   .setX( leftEnd   .x() + moveSize/2 );
    rightStart.setX( rightStart.x() - moveSize/2 );
    rightEnd  .setX( rightEnd  .x() - moveSize/2 );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonHUp()
{
    if( leftStart.y() <= 0 ) { return; }

    leftStart .setY( leftStart .y() - moveSize );
    rightStart.setY( rightStart.y() - moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonHDn()
{
    if( (leftEnd.y()-leftStart.y()) <= mainHeight/3 ) { return; }

    leftStart .setY( leftStart .y() + moveSize );
    rightStart.setY( rightStart.y() + moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonSUp()
{
    if( leftStart.x() <= leftEnd.x() ) { return; }

    leftStart .setX( leftStart .x() - moveSize );
    rightStart.setX( rightStart.x() + moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::onButtonSDn()
{
    if( rightStart.x()-leftStart.x() <= len ) { return; }

    leftStart .setX( leftStart .x() + moveSize );
    rightStart.setX( rightStart.x() - moveSize );

    updateLabel();
    updateMarker();
}
void EditMarkerDialog::updateLabel()
{
    labelTextX->setText(QString("X:%1").arg(QString::number(leftEnd.x()+(rightEnd.x()-leftEnd.x())/2),4));
    labelTextY->setText(QString("Y:%1").arg(QString::number(leftStart.y()+(leftEnd.y()-leftStart.y())/2),4));
    labelTextW->setText(QString("W:%1").arg(QString::number(rightEnd.x()-leftEnd.x()),4));
    labelTextH->setText(QString("H:%1").arg(QString::number(leftEnd.y()-leftStart.y()),4));
    int h = leftEnd  .y() - leftStart.y();
    int w = leftStart.x() - leftEnd  .x();
    labelTextS->setText(QString("S:%1%2").arg(QString::number(qAtan2(h,w)* (180.0/3.141592653589793238463), 'f',1),3).arg(tr("°")));
}
void EditMarkerDialog::onButtonChUp()
{
    markerCh++;
    if( markerCh>=devInfo.videoNum ) { markerCh=0; }

    setMarkerCh(markerCh);
}
void EditMarkerDialog::onButtonChDn()
{
    markerCh--;
    if( markerCh<0 ) { markerCh=devInfo.videoNum-1; }

    setMarkerCh(markerCh);
}
void EditMarkerDialog::setMarkerCh(int ch)
{
    markerCh = ch;
    labelCh->setText(QString("%1%2").arg("Ch").arg(QString::number(markerCh+1)));

    emit changeMarkerChannel(markerCh);
}
void EditMarkerDialog::updateMarker()
{
    emit updateMarker( leftStart, leftEnd, rightStart, rightEnd );
}
void EditMarkerDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if     ( buttonChUp  ->hasFocus() ) { buttonChDn  ->setFocus(); }
            else if( buttonChDn  ->hasFocus() ) { buttonChUp  ->setFocus(); }
            else if( buttonXUp   ->hasFocus() ) { buttonXDn   ->setFocus(); }
            else if( buttonXDn   ->hasFocus() ) { buttonXUp   ->setFocus(); }
            else if( buttonYUp   ->hasFocus() ) { buttonYDn   ->setFocus(); }
            else if( buttonYDn   ->hasFocus() ) { buttonYUp   ->setFocus(); }
            else if( buttonWUp   ->hasFocus() ) { buttonWDn   ->setFocus(); }
            else if( buttonWDn   ->hasFocus() ) { buttonWUp   ->setFocus(); }
            else if( buttonHUp   ->hasFocus() ) { buttonHDn   ->setFocus(); }
            else if( buttonHDn   ->hasFocus() ) { buttonHUp   ->setFocus(); }
            else if( buttonSUp   ->hasFocus() ) { buttonSDn   ->setFocus(); }
            else if( buttonSDn   ->hasFocus() ) { buttonSUp   ->setFocus(); }

            break;
        }
        case Qt::Key_Down:
        {
            if     ( buttonChUp  ->hasFocus() ) { buttonChDn  ->setFocus(); }
            else if( buttonChDn  ->hasFocus() ) { buttonChUp  ->setFocus(); }
            else if( buttonXUp   ->hasFocus() ) { buttonXDn   ->setFocus(); }
            else if( buttonXDn   ->hasFocus() ) { buttonXUp   ->setFocus(); }
            else if( buttonYUp   ->hasFocus() ) { buttonYDn   ->setFocus(); }
            else if( buttonYDn   ->hasFocus() ) { buttonYUp   ->setFocus(); }
            else if( buttonWUp   ->hasFocus() ) { buttonWDn   ->setFocus(); }
            else if( buttonWDn   ->hasFocus() ) { buttonWUp   ->setFocus(); }
            else if( buttonHUp   ->hasFocus() ) { buttonHDn   ->setFocus(); }
            else if( buttonHDn   ->hasFocus() ) { buttonHUp   ->setFocus(); }
            else if( buttonSUp   ->hasFocus() ) { buttonSDn   ->setFocus(); }
            else if( buttonSDn   ->hasFocus() ) { buttonSUp   ->setFocus(); }

            break;
        }
        case Qt::Key_Left:
        {
            if     ( buttonChUp  ->hasFocus() ) { buttonClose ->setFocus(); }
            else if( buttonChDn  ->hasFocus() ) { buttonClose ->setFocus(); }
            else if( buttonXUp   ->hasFocus() ) { buttonChUp  ->setFocus(); }
            else if( buttonXDn   ->hasFocus() ) { buttonChDn  ->setFocus(); }
            else if( buttonYUp   ->hasFocus() ) { buttonXUp   ->setFocus(); }
            else if( buttonYDn   ->hasFocus() ) { buttonXDn   ->setFocus(); }
            else if( buttonWUp   ->hasFocus() ) { buttonYUp   ->setFocus(); }
            else if( buttonWDn   ->hasFocus() ) { buttonYDn   ->setFocus(); }
            else if( buttonHUp   ->hasFocus() ) { buttonWUp   ->setFocus(); }
            else if( buttonHDn   ->hasFocus() ) { buttonWDn   ->setFocus(); }
            else if( buttonSUp   ->hasFocus() ) { buttonHUp   ->setFocus(); }
            else if( buttonSDn   ->hasFocus() ) { buttonHDn   ->setFocus(); }
            else if( buttonReload->hasFocus() ) { buttonSUp   ->setFocus(); }
            else if( buttonClose ->hasFocus() ) { buttonReload->setFocus(); }

            break;
        }
        case Qt::Key_Right:
        {
            if     ( buttonChUp  ->hasFocus() ) { buttonXUp   ->setFocus(); }
            else if( buttonChDn  ->hasFocus() ) { buttonXDn   ->setFocus(); }
            else if( buttonXUp   ->hasFocus() ) { buttonYUp   ->setFocus(); }
            else if( buttonXDn   ->hasFocus() ) { buttonYDn   ->setFocus(); }
            else if( buttonYUp   ->hasFocus() ) { buttonWUp   ->setFocus(); }
            else if( buttonYDn   ->hasFocus() ) { buttonWDn   ->setFocus(); }
            else if( buttonWUp   ->hasFocus() ) { buttonHUp   ->setFocus(); }
            else if( buttonWDn   ->hasFocus() ) { buttonHDn   ->setFocus(); }
            else if( buttonHUp   ->hasFocus() ) { buttonSUp   ->setFocus(); }
            else if( buttonHDn   ->hasFocus() ) { buttonSDn   ->setFocus(); }
            else if( buttonSUp   ->hasFocus() ) { buttonReload->setFocus(); }
            else if( buttonSDn   ->hasFocus() ) { buttonReload->setFocus(); }
            else if( buttonReload->hasFocus() ) { buttonClose ->setFocus(); }
            else if( buttonClose ->hasFocus() ) { buttonChUp  ->setFocus(); }

            break;
        }
        case Qt::Key_Enter:
        {
            if     ( buttonChUp  ->hasFocus() ) { onButtonChUp(); }
            else if( buttonChDn  ->hasFocus() ) { onButtonChDn(); }
            else if( buttonXUp   ->hasFocus() ) { onButtonXUp(); }
            else if( buttonXDn   ->hasFocus() ) { onButtonXDn(); }
            else if( buttonYUp   ->hasFocus() ) { onButtonYUp(); }
            else if( buttonYDn   ->hasFocus() ) { onButtonYDn(); }
            else if( buttonWUp   ->hasFocus() ) { onButtonWUp(); }
            else if( buttonWDn   ->hasFocus() ) { onButtonWDn(); }
            else if( buttonHUp   ->hasFocus() ) { onButtonHUp(); }
            else if( buttonHDn   ->hasFocus() ) { onButtonHDn(); }
            else if( buttonSUp   ->hasFocus() ) { onButtonSUp(); }
            else if( buttonSDn   ->hasFocus() ) { onButtonSDn(); }
            else if( buttonReload->hasFocus() ) { loadMarkerConfig(); }
            else if( buttonClose ->hasFocus() ) { onButtonClose(); }

            break;
        }
        case Qt::Key_Escape:
        {
            onButtonClose();
            break;
        }
    }
}
