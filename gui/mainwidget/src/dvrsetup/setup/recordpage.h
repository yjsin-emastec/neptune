#ifndef RECORDPAGE_H
#define RECORDPAGE_H

#include <QtGui/QWidget>
#include "ui_recordpage.h"
#include "ui_recordpage1080p.h"

class NormalDialog;
class EventDialog;

class RecordPage : public QWidget
{
    Q_OBJECT

public:
    RecordPage(QWidget *parent = 0);
    ~RecordPage();

    QPushButton *buttonNormal;
    QPushButton *buttonEvent;
    QPushButton *buttonClose;

signals:
	void saveRecordPage(int type);
	void escapeTabFocus(void);
	void closeSetupMenu(void);

public slots:

private slots:
    void onButtonNormal(void);
    void onButtonEvent(void);
	void onButtonClose(void);
    void onRecordSave(void);
	
private:
	NormalDialog *normalDialog;
	EventDialog  *eventDialog;
};

#endif // RECORDPAGE_H
