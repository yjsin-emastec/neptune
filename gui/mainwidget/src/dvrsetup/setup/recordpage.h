#ifndef RECORDPAGE_H
#define RECORDPAGE_H

#include <QtGui/QWidget>
#include "ui_recordpage.h"

class NormalDialog;
class EventDialog;
class RecordStatus;

class RecordPage : public QWidget, public Ui::RecordPage
{
    Q_OBJECT

public:
    RecordPage(QWidget *parent = 0);
    ~RecordPage();

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
    RecordStatus *recordStatus;
};

#endif // RECORDPAGE_H
