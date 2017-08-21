#ifndef BACKUPDIALOG_H
#define BACKUPDIALOG_H

#include <QtGui/QDialog>
#include "ui_backupdialog.h"
#include "aifbackup2.h"

class BackupDialog : public QDialog, public Ui::BackupDialog
{
    Q_OBJECT

public:
	BackupDialog(QWidget *parent = 0);
	~BackupDialog();
	void setCaptureMode(int type, int ch, int split, time_t pbTime);
		
signals:

public slots:
	void updateBackupProgress(int msg, int progress);
	
protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void onInitialize(const QDateTime &datetime);
	void onButtonEnd();
	void onButtonBackup();
	void onButtonClose();

private:
	void BackupTimer();
	QTimer *backupTimer;
	int indexEnd, flagPrepare, tmp_msg, tmp_progress;
	bool isKeyLock;
	aif_backup_context_t *pBackupContext;
};

#endif // BACKUPDIALOG_H
