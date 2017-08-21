#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QtGui/QDialog>
#include "ui_configdialog.h"
#include "DVR.h"

class TextMessageDialog;

class ConfigDialog : public QDialog, public Ui::ConfigDialog
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
};

#endif // CONFIGDIALOG_H
