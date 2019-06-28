#ifndef STATUSBARDIALOG_H
#define STATUSBARDIALOG_H

#include <QtGui/QDialog>
#include <QtCore/QTimer>
#include "DVR.h"
#include "ui_statusbardialog.h"
#include<QPushButton>

class TextMessageDialog;

class StatusBarDialog : public QDialog, public Ui::StatusBarDialog
{
	Q_OBJECT

public:
	StatusBarDialog(int timeFormat, QWidget *parent = 0);
	~StatusBarDialog();
	void setTimeFormat(int timeFormat);
	void updateDiskProgress(unsigned int diskSize, unsigned int diskFree);
    void setSplitMode(bool state);
    bool getSplitMode(void);

signals:

    void changeSplit(int startCh, int selectCh, int split);

public slots:
	void updateTime();
    void onButtonSplit();
    void onButtonSplit1();
    void onButtonSplit4();
    void onButtonSplit9();
    void onButtonPrev();
    void onButtonNext();

    void onButtonSplit1Pressed();
    void onButtonSplit4Pressed();
    void onButtonSplit9Pressed();
    void onButtonPrevPressed();
    void onButtonNextPressed();

    void onButtonSplit1Released();
    void onButtonSplit4Released();
    void onButtonSplit9Released();
    void onButtonPrevReleased();
    void onButtonNextReleased();

    void updateSplitButton();
    void updateTriggerState(int state);

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

    bool isSplitMode;
    int focusSplitButton;
    int isTrigger;
    int buttonSize;

    void hideTimeLabel();
    void showTimeLabel();
    void setFocusSplitButton(int btnNum);
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    TextMessageDialog *msgBox;

private slots:
};

#endif // STATUSBARDIALOG_H
