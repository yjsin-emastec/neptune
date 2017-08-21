#ifndef GSENSORDIALOG_H
#define GSENSORDIALOG_H

#include <QtGui/QDialog>
#include "ui_gsensordialog.h"
#include "DVR.h"

class GsensorDialog : public QDialog, public Ui::GsensorDialog
{
    Q_OBJECT

public:
    GsensorDialog(QWidget *parent = 0);
    ~GsensorDialog();
	void initGsensorConfig(void);
	
signals:

public slots:
	void onButtonGsensor(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	int indexGsensor;    
};

#endif // GSENSORDIALOG_H
