#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>
#include "ui_configdialog.h"
#include "ui_configdialog1080p.h"
#include "DVR.h"

class TextMessageDialog;

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
	void initConfigConfig(void);

signals:

public slots:
	void onButtonSaveConfig(void);
	void onButtonLoadConfig(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	void UpdateLabelConfig(int type);
	void Delay(int millisecondsToWait);
	TextMessageDialog *msgBox;

    QFrame *frame;
    QLabel *labelConfig;
    QPushButton *buttonSaveConfig;
    QPushButton *buttonLoadConfig;
    QPushButton *buttonClose;
};

#endif // CONFIGDIALOG_H
