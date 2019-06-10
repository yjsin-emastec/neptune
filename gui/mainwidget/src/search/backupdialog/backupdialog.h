#ifndef BACKUPDIALOG_H
#define BACKUPDIALOG_H

#include <QtGui/QDialog>
#include "ui_backupdialog.h"
#include "ui_backupdialog1080p.h"
#include "aifbackup2.h"

class BackupDialog : public QDialog
{
    Q_OBJECT

public:
	BackupDialog(QWidget *parent = 0);
	~BackupDialog();
	void setCaptureMode(int type, int ch, int split, time_t pbTime);
    void updateBackupDialog();

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
    bool eventFilter(QObject *obj, QEvent *event);

    QFrame *frame;
    QPushButton *buttonBackup;
    QPushButton *buttonClose;
    QPushButton *buttonEnd;
    QDateTimeEdit *dateTimeStart;
    QLabel *labelEnd;
    QLabel *labelStart;
    QProgressBar *progressBarBackup;
};

#endif // BACKUPDIALOG_H
