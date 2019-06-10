#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QtGui/QDialog>
#include "ui_eventdialog.h"
#include "ui_eventdialog1080p.h"
#include "DVR.h"

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    EventDialog(QWidget *parent = 0);
    ~EventDialog();
	void initEventConfig(void);

signals:

public slots:
	void onEventTime(void);
	void onGsensor(void);
	void onTrigger(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	int indexEventTime;
	int indexGsensor;
	int indexTrigger;

    QFrame *frame;
    QPushButton *buttonEventTime;
    QPushButton *buttonGsensor;
    QPushButton *buttonTrigger;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
};

#endif // EVENTDIALOG_H
