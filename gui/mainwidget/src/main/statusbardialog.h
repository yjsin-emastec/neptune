#ifndef STATUSBARDIALOG_H
#define STATUSBARDIALOG_H

#include <QtGui/QDialog>
#include <QtCore/QTimer>
#include "DVR.h"
#include "ui_statusbardialog.h"

class StatusBarDialog : public QDialog, public Ui::StatusBarDialog
{
	Q_OBJECT

public:
	StatusBarDialog(int timeFormat, QWidget *parent = 0);
	~StatusBarDialog();
	void setTimeFormat(int timeFormat);
	void updateDiskProgress(unsigned int diskSize, unsigned int diskFree);
	
signals:

public slots:
	void updateTime();

protected:

private:
	int timeDisplayFormat;
	bool is24HourMode;
	int isNoDisk;

	QString updateTime_value();
    void resizeStatusBar();
	int eventDetectStatus;
	disk_used_info_t diskInfo[MAX_HDD_COUNT];

	bool m_flg_update;
	bool m_flg_showTime;
	bool m_flg_showNoDisk;

	int m_posTime_x, m_posTime_y;
	int m_posNoDisk_x, m_posNoDisk_y;

	int loc_Time;
	int loc_Time_BackUp;

	QString m_viewTime;
	QString m_viewNoDisk;

private slots:
};

#endif // STATUSBARDIALOG_H
