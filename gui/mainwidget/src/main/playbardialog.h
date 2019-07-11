#ifndef PLAYBARDIALOG_H
#define PLAYBARDIALOG_H

#include <QtGui/QDialog>
#include "ui_playbardialog.h"
#include "ui_playbardialog1080p.h"
#include <QHBoxLayout>

class QPushButton;
class QLabel;
class PlayTimeBar;

class PlayBarDialog : public QDialog
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
    void            initPlayBar           (void);
    int             GetStatePausePlay     (void);
    int             getPlaybackChannel    (void);
    bool            getSplitMode          (void);
    void            setSplitMode          (bool state);

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
    void            setAudioMute          (void);
    void            setAudio              (int);
    void            changeSplit           (int);
    void            changeChannel         (int);

public slots:
    void            clickBackup           (void);
    void            rewClicked            (void);
    void            rewFrameClicked       (void);
    void            playClicked           (void);
    void            pauseClicked          (void);
    void            playpauseClicked      (void);
    void            fowardFrameClicked    (void);
    void            fastClicked           (void);
    void            onButtonSplit         (void);
    void            onButtonAudio         (void);
    void            onButtonZoom          (void);
    void            playbackTimeUpdate    (time_t pbTime);
    void            searchDataUpdate      (int type);
    void            closeSearchBar        (void);
    void            onUpdateTimeLabel     (QString time);
    void            onUpdateDateLabel     (QString date);

    void            buttonPrevClicked     (void);
    void            buttonSplit1Clicked   (void);
    void            buttonSplit4Clicked   (void);
    void            buttonSplit9Clicked   (void);
    void            buttonNextClicked     (void);
    void            buttonPrevPressed     (void);
    void            buttonSplit1Pressed   (void);
    void            buttonSplit4Pressed   (void);
    void            buttonSplit9Pressed   (void);
    void            buttonNextPressed     (void);
    void            buttonPrevReleased    (void);
    void            buttonSplit1Released  (void);
    void            buttonSplit4Released  (void);
    void            buttonSplit9Released  (void);
    void            buttonNextReleased    (void);

    void            updateSplitButton     (void);

private slots:
    void            changePlaybackTime    (int pos);

private:
    void            createPlaySpeedControlButtons    (void);
    void            checkDayChanged                  (time_t pbTime, time_t prevTime, int expired);
    void            SetAudioIcon                     (int ch);
    void            keyPressEvent                    (QKeyEvent *event);

    int             playbackDirection;
    int             changeDay;
    int             pbPreviousAudio;
    int             pbPreviousSplit;
    int             ispbMute;
    int             PLAYBAR_BTN_SIZE;
    int             labelFontSize;
    int             timeBarWidth;
    int             timeBarHeightSmall;
    int             timeBarHeightBig;
    bool            isSplit;
    int             focusSplitButton;

    PlayTimeBar    *timeBar;

    QLabel         *labelDate,
                   *labelTime,
                   *labelSpeed;

    QPushButton    *buttonAudio;
    QPushButton    *buttonRew;
    QPushButton    *buttonRewFrame;
    QPushButton    *buttonPlay;
    QPushButton    *buttonFfFrame;
    QPushButton    *buttonFf;
    QPushButton    *buttonSlow;
    QPushButton    *buttonStill;
    QPushButton    *buttonClose;
    QPushButton    *buttonZoom;

    QPushButton    *buttonSplit;
    QPushButton    *buttonPrev;
    QPushButton    *buttonSplit1;
    QPushButton    *buttonSplit4;
    QPushButton    *buttonSplit9;
    QPushButton    *buttonNext;

    QFrame         *frame;

    void           hideButton             ();
    void           showButton             ();
    void           showSplitButton        ();
    void           hideSplitButton        ();
    bool           eventFilter            (QObject *o, QEvent *e);
    void           setFocusSplitButton    (int btnNum);
};

#endif // PLAYBARDIALOG_H
