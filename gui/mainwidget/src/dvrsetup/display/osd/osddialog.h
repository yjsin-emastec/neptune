#ifndef OSDDIALOG_H
#define OSDDIALOG_H

#include <QtGui/QDialog>
#include "ui_osddialog.h"
#include "DVR.h"

class OsdDialog : public QDialog, public Ui::OsdDialog
{
    Q_OBJECT

public:
    OsdDialog(QWidget *parent = 0);
    ~OsdDialog();
	void initOsdConfig(void);

signals:

public slots:
	void onChannelName(void);
	void onNoVideo(void);
	void onStatusBar(void);
	void onRecordStatus(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	int indexCameraName;
	int indexNoVideo;
	int indexStatusBar;
	int indexRecordStatus;
};

#endif // OSDDIALOG_H
