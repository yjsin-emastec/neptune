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
    void            displaySpeed          (void);
    int             GetStatePausePlay     (void);
    int             getPlaybackChannel    (void);

    time_t          curPbTime;
    time_t          backupStartTime;

    int             playbackMaxSplit;
    int             playbackStartCh;
    int             playbackSpeed;
    int             playbackSpeed_old;
    int             playbackState;
    int             indexAudio;

signals:
    void            exitSearchBar         (void);
    void            backupClicked         (void);
    void            setAudio1             (void);
    void            setAudio2             (void);
    void            setAudio3             (void);
    void            setAudio4             (void);
    void            setAudioMute          (void);

public slots:
    void            clickBackup           (void);
    void            rewClicked            (void);
    void            rewFrameClicked       (void);
    void            playClicked           (void);
    void            pauseClicked          (void);
    void            playpauseClicked      (void);
    void            fowardFrameClicked    (void);
    void            fastClicked           (void);
    void            onButtonAudio         (void);
    void            playbackTimeUpdate    (time_t pbTime);
    void            searchDataUpdate      (int type);
    void            closeSearchBar        (void);

private slots:
    void            changePlaybackTime    (int pos);

private:
    void            createPlaySpeedControlButtons    (void);
    void            checkDayChanged                  (time_t pbTime, time_t prevTime, int expired);
    void            SetAudioIcon                     (int ch);

    int             playbackDirection;
    int             changeDay;
    int             pbPreviousAudio;
    int             pbPreviousSplit;

    PlayTimeBar    *timeBar;

    QLabel         *labelSpeed;

    QPushButton    *buttonAudio;
    QPushButton    *buttonRew;
    QPushButton    *buttonRewFrame;
    QPushButton    *buttonPlay;
    QPushButton    *buttonFfFrame;
    QPushButton    *buttonFf;
    QPushButton    *buttonSlow;
    QPushButton    *buttonStill;
    QPushButton    *buttonClose;
};

#endif // PLAYBARDIALOG_H
