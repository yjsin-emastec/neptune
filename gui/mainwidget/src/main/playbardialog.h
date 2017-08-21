#ifndef PLAYBARDIALOG_H
#define PLAYBARDIALOG_H

#include <QtGui/QDialog>
#include "ui_playbardialog.h"

class QPushButton;
class QLabel;
class PlayTimeBar;

class PlayBarDialog : public QDialog, public Ui::PlayBarDialog
{
    Q_OBJECT

public:
    PlayBarDialog(QWidget *parent = 0);
    ~PlayBarDialog();
    void setTimeFormat(int timeFormat);
    void updateTimeLine();
    void setMaxSplit(int startCh, int split);
    void resumePlayback(int isAviBackup, int sec);
    time_t curPbTime, backupStartTime;
    int playbackMaxSplit, playbackStartCh;
    void PausePlayChange(int state);
    int GetStatePausePlay(void);
    int getPlaybackChannel();
    int playbackSpeed, playbackSpeed_old, playbackState;

signals:
    void exitSearchBar();
    void backupClicked();
    void hugeBackupStatusClicked();

    public slots:
    void clickBackup();
    void rewClicked();
    void rewFrameClicked();
    void playClicked();
    void pauseClicked();
    void playpauseClicked();
    void fowardFrameClicked();
    void fastClicked();
    void onButtonAudio(void);
    void playbackTimeUpdate(time_t pbTime);
    void searchDataUpdate(int type);
    void closeSearchBar();

    private slots:
    void changePlaybackTime(int pos);

private:
    void createPlaySpeedControlButtons();
    void displaySpeed();
    void checkDayChanged(time_t pbTime, time_t prevTime, int expired);
    void OutputAudio(int ch);
    int playbackDirection, changeDay, indexAudio;
    PlayTimeBar *timeBar;
    QLabel      *labelSpeed;
    QPushButton *buttonAudio, *buttonRew, *buttonRewFrame, *buttonPlay, *buttonFfFrame, *buttonFf, *buttonSlow, *buttonStill, *buttonClose;
};

#endif // PLAYBARDIALOG_H
