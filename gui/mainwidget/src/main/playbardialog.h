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
    PlayBarDialog                         (QWidget *parent = 0);
    ~PlayBarDialog                        (void);

    void            setTimeFormat         (int timeFormat);
    void            updateTimeLine        (void);
    void            setMaxSplit           (int startCh, int split);
    void            resumePlayback        (int isAviBackup, int sec);
    void            PausePlayChange       (int state);
    void            OutputAudio           (int ch);
    int             GetStatePausePlay     (void);
    int             getPlaybackChannel    (void);

    time_t          curPbTime,
                    backupStartTime;

    int             playbackMaxSplit,
                    playbackStartCh,
                    playbackSpeed,
                    playbackSpeed_old,
                    playbackState,
                    indexAudio;

signals:
    void            exitSearchBar(void);
    void            backupClicked(void);

public slots:
    void            clickBackup(void);
    void            rewClicked(void);
    void            rewFrameClicked(void);
    void            playClicked(void);
    void            pauseClicked(void);
    void            playpauseClicked(void);
    void            fowardFrameClicked(void);
    void            fastClicked(void);
    void            onButtonAudio(void);
    void            playbackTimeUpdate(time_t pbTime);
    void            searchDataUpdate(int type);
    void            closeSearchBar(void);

private slots:
    void            changePlaybackTime(int pos);

private:
    void            createPlaySpeedControlButtons(void);
    void            displaySpeed(void);
    void            checkDayChanged(time_t pbTime, time_t prevTime, int expired);
    void            SetAudioIcon(int ch);

    int             playbackDirection,
                    changeDay;

    PlayTimeBar    *timeBar;

    QLabel         *labelSpeed;

    QPushButton    *buttonAudio,
                   *buttonRew,
                   *buttonRewFrame,
                   *buttonPlay,
                   *buttonFfFrame,
                   *buttonFf,
                   *buttonSlow,
                   *buttonStill,
                   *buttonClose;
};

#endif // PLAYBARDIALOG_H
