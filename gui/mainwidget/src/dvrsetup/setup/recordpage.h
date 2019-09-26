#ifndef RECORDPAGE_H
#define RECORDPAGE_H

#include <QtGui/QWidget>
#include "ui_recordpage.h"
#include "ui_recordpage1080p.h"
#include "ui/customwidget/customimagelabel.h"

class NormalDialog;
class EventDialog;

class RecordPage : public QWidget
{
    Q_OBJECT

public:
    RecordPage(QWidget *parent = 0);
    ~RecordPage();

    CustomImageLabel *buttonNormal;
    CustomImageLabel *buttonEvent;
    CustomImageLabel *buttonClose;

    QLabel           *labelNormalText;
    QLabel           *labelEventText;
    QLabel           *labelCloseText;

signals:
	void saveRecordPage(int type);
	void escapeTabFocus(void);
	void closeSetupMenu(void);

public slots:
    void onButtonNormal(void);
    void onButtonEvent(void);
	void onButtonClose(void);
    void setFocusNormal(void);
    void setFocusEvent(void);
    void setFocusClose(void);
    void setFocusTabLayout(void);

    void onRecordSave(void);
	
private:
	NormalDialog *normalDialog;
	EventDialog  *eventDialog;

    QPixmap iconImageNormal[3];
    QPixmap iconImageFocus[3];

    void changeFocus(int n);
};

#endif // RECORDPAGE_H
