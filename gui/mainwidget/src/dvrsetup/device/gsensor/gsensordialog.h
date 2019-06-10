#ifndef GSENSORDIALOG_H
#define GSENSORDIALOG_H

#include <QtGui/QDialog>
#include "ui_gsensordialog.h"
#include "ui_gsensordialog1080p.h"
#include "DVR.h"

class GsensorDialog : public QDialog
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

    QFrame *frame;
    QPushButton *buttonClose;
    QPushButton *buttonGsensor;
    QPushButton *buttonSave;
};

#endif // GSENSORDIALOG_H
