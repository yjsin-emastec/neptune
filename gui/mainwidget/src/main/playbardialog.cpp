#include <QtGui>
#include "playbardialog.h"
#include "playtimebar.h"
#include "mainglobal.h"
#include "DVR.h"
#include "appmgr.h"
#include <EasternEvent.h>
#include <Event.h>
#include "aifbackup2.h"
#include "dev/Ver.h"

#define PLAYBAR_BTN_SIZE 70

PlayBarDialog::PlayBarDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    playbackMaxSplit = playbackStartCh = 0;

    playbackState     = pbState = PB_PAUSE;
    playbackSpeed     = PB_SPEED_1;
    playbackSpeed_old = PB_SPEED_1;
    playbackDirection = PB_FF;
    changeDay = 0;

    setAutoFillBackground(true);

    timeBar = new PlayTimeBar(this);
    timeBar->playbackDirection = PB_FF;

    createPlaySpeedControlButtons();

    QHBoxLayout  *buttonLayout = new QHBoxLayout;
    buttonLayout ->addSpacing  (30);
    buttonLayout ->addWidget   (labelSpeed);
    buttonLayout ->addWidget   (buttonAudio);
    buttonLayout ->addSpacing  (40);
    buttonLayout ->addWidget   (buttonRewFrame);
    buttonLayout ->addWidget   (buttonRew);
    buttonLayout ->addWidget   (buttonPlay);
    buttonLayout ->addWidget   (buttonFf);
    buttonLayout ->addWidget   (buttonFfFrame);
    buttonLayout ->addSpacing  (70);
    buttonLayout ->addWidget   (buttonStill);
    buttonLayout ->addWidget   (buttonClose);
    buttonLayout ->addSpacing  (15);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget (timeBar);
    layout->addLayout (buttonLayout);

    connect(buttonAudio,    SIGNAL(clicked()),            this, SLOT(onButtonAudio      (void)));
    connect(buttonRew,      SIGNAL(clicked()),            this, SLOT(rewClicked         (void)));
    connect(buttonRewFrame, SIGNAL(clicked()),            this, SLOT(rewFrameClicked    (void)));
    connect(buttonPlay,     SIGNAL(clicked()),            this, SLOT(playpauseClicked   (void)));
    connect(buttonFf,       SIGNAL(clicked()),            this, SLOT(fastClicked        (void)));
    connect(buttonFfFrame,  SIGNAL(clicked()),            this, SLOT(fowardFrameClicked (void)));
    connect(buttonStill,    SIGNAL(clicked()),            this, SLOT(clickBackup        (void)));
    connect(buttonClose,    SIGNAL(clicked()),            this, SLOT(closeSearchBar     (void)));
    connect(timeBar,        SIGNAL(playTimeChanged(int)), this, SLOT(changePlaybackTime (int )));

    setLayout(layout);

    indexAudio = 0;
}
PlayBarDialog::~PlayBarDialog(void)
{
}
void PlayBarDialog::createPlaySpeedControlButtons(void)
{
    labelSpeed = new QLabel(tr("Pause"), this);
    labelSpeed->setStyleSheet  ("font-weight:bold;font-size:32px;");
    labelSpeed->setSizePolicy  (QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelSpeed->setMinimumSize (QSize(250, PLAYBAR_BTN_SIZE));
    labelSpeed->setMaximumSize (QSize(250, PLAYBAR_BTN_SIZE));
    labelSpeed->setAlignment   (Qt::AlignLeft|Qt::AlignVCenter);

    buttonAudio     = new QPushButton(this);  buttonAudio    ->setFocusPolicy(Qt::NoFocus);
    buttonRew       = new QPushButton(this);  buttonRew      ->setFocusPolicy(Qt::NoFocus);
    buttonRewFrame  = new QPushButton(this);  buttonRewFrame ->setFocusPolicy(Qt::NoFocus);
    buttonPlay      = new QPushButton(this);  buttonPlay     ->setFocusPolicy(Qt::NoFocus);
    buttonFfFrame   = new QPushButton(this);  buttonFfFrame  ->setFocusPolicy(Qt::NoFocus);
    buttonFf        = new QPushButton(this);  buttonFf       ->setFocusPolicy(Qt::NoFocus);
    buttonStill     = new QPushButton(this);  buttonStill    ->setFocusPolicy(Qt::NoFocus);
    buttonClose     = new QPushButton(this);  buttonClose    ->setFocusPolicy(Qt::NoFocus);

    buttonAudio    ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonAudio    ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonAudio    ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonAudio    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonAudio    ->setIcon         (QIcon(":/images/aomute.png"));
    buttonAudio    ->adjustSize      ();

    buttonRew      ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonRew      ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRew      ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRew      ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRew      ->setIcon         (QIcon(":/images/rew.png"));
    buttonRew      ->adjustSize      ();

    buttonRewFrame ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonRewFrame ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRewFrame ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRewFrame ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRewFrame ->setIcon         (QIcon(":/images/rew_frame.png"));
    buttonRewFrame ->adjustSize      ();

    buttonPlay     ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonPlay     ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonPlay     ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonPlay     ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonPlay     ->setIcon         (QIcon(":/images/play.png"));
    buttonPlay     ->adjustSize      ();

    buttonFfFrame  ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonFfFrame  ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFfFrame  ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFfFrame  ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFfFrame  ->setIcon         (QIcon(":/images/ff_frame.png"));
    buttonFfFrame  ->adjustSize      ();

    buttonFf       ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonFf       ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFf       ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFf       ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFf       ->setIcon         (QIcon(":/images/ff.png"));
    buttonFf       ->adjustSize      ();

    buttonStill    ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonStill    ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonStill    ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonStill    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonStill    ->setIcon         (QIcon(":/images/still_image.png"));
    buttonStill    ->adjustSize      ();

    buttonClose    ->setSizePolicy   (QSizePolicy::Minimum, QSizePolicy::Minimum);
    buttonClose    ->setMinimumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonClose    ->setMaximumSize  (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonClose    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonClose    ->setIcon         (QIcon(":/images/close.png"));
    buttonClose    ->adjustSize      ();
}
void PlayBarDialog::setTimeFormat(int timeFormat)
{
    timeBar->setTimeFormat(timeFormat);

    buttonAudio->setIcon(QIcon(":/images/aomute.png"));
    indexAudio = 1;

    buttonPlay->setIcon(QIcon(":/images/pause.png"));

    buttonRew->setEnabled(true);
    buttonRewFrame->setEnabled(true);
    buttonFfFrame->setEnabled(true);
    buttonFf->setEnabled(true);
    buttonStill->setEnabled(true);

    if(!EventSearchPB)
    {
        buttonRewFrame->show();
        buttonFfFrame->show();
    }
    else
    {
        buttonRewFrame->hide();
        buttonFfFrame->hide();
    }

    timeBar->sliderPlayTimeChange();
}
void PlayBarDialog::closeSearchBar(void)
{
    struct tm tmNow;
    int chBit = 0;

    if(playbackState == PB_STOP)
    {
        return;
    }

    if(indexAudio != 1)
    {
        OutputAudio(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }

    playbackSpeed_old  = playbackSpeed;
    playbackSpeed      = PB_PAUSE;
    chBit              = getPlaybackChannel();

    appmgr_search_set_speed(playbackSpeed, chBit);

    playbackState      = PB_STOP;
    pbState            = PB_STOP;

    qDebug("\n\n\t %s(), timeLogSelTime[%s], calSelTime[%s] \n", __func__, atime(timeLogSelTime), atime(calSelTime));
    timeLogSelTime = calSelTime;
    localtime_r(&timeLogSelTime, &tmNow);
    appmgr_make_dls_time_info(tmNow.tm_year, 0, &dlsPlayback);

    emit exitSearchBar();

    qDebug("[CHECKPOINT] %s-%d", __func__, __LINE__);
}
void PlayBarDialog::resumePlayback(int isAviBackup, int sec)
{
    int chMask = 0, chBit = 0;

    qDebug("finish backup pbtime[%s], isAviBackup[%d], playbackSpeed[%d], playbackSpeed_old[%d]\n", atime(curPbTime), isAviBackup, playbackSpeed, playbackSpeed_old);

    if(isAviBackup > 1)
    {
        qDebug("backup ..... complete... set channel .... %d, %d", playbackMaxSplit, playbackStartCh);

        if(playbackMaxSplit == 1)
        {
            chMask = ( 1 << playbackStartCh);
        }
        else
        {
            for(int i = 0; i < devInfo.videoNum; i++)
            {
                chMask |= (1 << i);
            }
        }

        qDebug("backup ..... complete... appmgr_search_play_start .... %d", chMask);

        if(backupStartTime == 0)
        {
            backupStartTime = curPbTime;
        }

        appmgr_search_play_start(chMask, playbackMaxSplit * playbackMaxSplit, backupStartTime, sec);
        appmgr_search_play_start_real();
        backupStartTime = 0;
    }

    playbackSpeed = playbackSpeed_old;

    if(playbackSpeed == PB_SPEED_1 && playbackState == PB_PLAY)
    {
        buttonPlay->setIcon(QIcon(":/images/pause.png"));
    }
    else
    {
        buttonPlay->setIcon(QIcon(":/images/play.png"));
        buttonAudio->setIcon(QIcon(":/images/aomute.png"));
        emit setAudioMute();
    }

    //fprintf(stderr, "\n\n\t playbackSpeed[%d], playbackSpeed_old[%d], playbackState[%d]\n", playbackSpeed, playbackSpeed_old, playbackState);
    chBit = getPlaybackChannel();

    if(playbackState == PB_PAUSE)
    {
        appmgr_search_set_speed(playbackState, chBit);
    }
    else
    {
        appmgr_search_set_speed(playbackSpeed_old, chBit);
    }
}
void PlayBarDialog::SetAudioIcon(int ch)
{
    switch(ch)
    {
        case  0: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); emit setAudio1();     break; }
        case  1: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); emit setAudio2();     break; }
        case  2: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); emit setAudio3();     break; }
        case  3: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); emit setAudio4();     break; }
        case 19: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); emit setAudioMute();  break; }
        default: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); emit setAudioMute();  break; }
    }
}
void PlayBarDialog::OutputAudio(int ch)
{
    switch(ch)
    {
        case  0: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); indexAudio = 2; emit setAudio1();    break; }
        case  1: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); indexAudio = 3; emit setAudio2();    break; }
        case  2: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); indexAudio = 4; emit setAudio3();    break; }
        case  3: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); indexAudio = 5; emit setAudio4();    break; }
        case 19: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); indexAudio = 1; emit setAudioMute(); break; }
        default: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); indexAudio = 1; emit setAudioMute(); break; }
    }
}
void PlayBarDialog::onButtonAudio(void)
{
    if(playbackState !=PB_PLAY || playbackSpeed != PB_SPEED_1 || playbackDirection != PB_FF)
    {
        return;
    }

    if(currentSplit == 1)
    {
        if(indexAudio == currentChannelNum + 2)
        {
            indexAudio = 0;
        }

        if(indexAudio == 0)
        {
            ++indexAudio;;
        }
        else
        {
            indexAudio = currentChannelNum + 2;
        }

        switch(indexAudio)
        {
            case  1: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19); emit setAudioMute();  break; }
            case  2: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         0); emit setAudio1();     break; }
            case  3: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         1); emit setAudio2();     break; }
            case  4: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         2); emit setAudio3();     break; }
            case  5: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         3); emit setAudio4();     break; }
        }

        if(indexAudio != 1)
        {
            indexAudio = 0;
        }
    }
    else
    {
        if(indexAudio >= 5)
        {
            indexAudio = 0;
        }

        switch(++indexAudio)
        {
            case  1: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19); emit setAudioMute();  break; }
            case  2: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         0); emit setAudio1();     break; }
            case  3: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         1); emit setAudio2();     break; }
            case  4: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         2); emit setAudio3();     break; }
            case  5: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         3); emit setAudio4();     break; }
        }
    }
}
void PlayBarDialog::clickBackup(void)
{
    int chBit = 0;

    if(indexAudio != 1)
    {
        SetAudioIcon(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }

    chBit = getPlaybackChannel();

    appmgr_search_set_speed(PB_PAUSE, chBit);

    playbackSpeed_old = playbackSpeed;
    playbackSpeed     = PB_PAUSE;
#if 1 // GyverJeong [17/12/05]
    labelSpeed->setText(tr("Pause"));
#endif
    buttonPlay->setIcon(QIcon(":/images/play.png"));

    emit backupClicked();
}
void PlayBarDialog::displaySpeed(void)
{
    QString str;

    if(playbackState == PB_PAUSE)
    {
        str = tr("Pause");
        appmgr_search_set_pause_state(1);
    }
    else
    {
        appmgr_search_set_pause_state(0);

        if(playbackDirection == PB_FF)
        {
            switch(playbackSpeed)
            {
                case PB_SPEED_1: 	str = tr("Play");  		break;
                case PB_SPEED_2: 	str = tr("FF x2");  	break;
                case PB_SPEED_4: 	str = tr("FF x4");  	break;
                case PB_SPEED_8: 	str = tr("FF x8");  	break;
                case PB_SPEED_16:	str = tr("FF x16"); 	break;
                case PB_SPEED_32: 	str = tr("FF x32"); 	break;
                case PB_SPEED_64: 	str = tr("FF x64"); 	break;
                case PB_SPEED_128: 	str = tr("FF x128"); 	break;
                case PB_SPEED_256: 	str = tr("FF x256"); 	break;
                case PB_SPEED_1024:	str = tr("FF x1024");	break;
                default: return;
            }
        }
        else
        {
            switch(playbackSpeed)
            {
                case PB_SPEED_1: 	str = tr("REW x1");		break;
                case PB_SPEED_2: 	str = tr("REW x2"); 	break;
                case PB_SPEED_4: 	str = tr("REW x4"); 	break;
                case PB_SPEED_8: 	str = tr("REW x8"); 	break;
                case PB_SPEED_16:	str = tr("REW x16");	break;
                case PB_SPEED_32: 	str = tr("REW x32");	break;
                case PB_SPEED_64: 	str = tr("REW x64");	break;
                case PB_SPEED_128: 	str = tr("REW x128"); 	break;
                case PB_SPEED_256: 	str = tr("REW x256"); 	break;
                case PB_SPEED_1024:	str = tr("REW x1024");	break;
                default: return;
            }
        }
    }

    labelSpeed->setText(str);
}
void PlayBarDialog::rewClicked(void)
{
    int chBit = 0;

    if(indexAudio != 1)
    {
        SetAudioIcon(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }

    chBit = getPlaybackChannel();

    if(playbackDirection == PB_REW)
    {
        playbackState              = PB_PLAY;
        pbState                    = PB_PLAY;
        playbackDirection          = PB_REW;
        timeBar->playbackDirection = PB_REW;

        switch(playbackSpeed)
        {
            case PB_SPEED_1: 	playbackSpeed = PB_SPEED_2; 	break;
            case PB_SPEED_2: 	playbackSpeed = PB_SPEED_4; 	break;
            case PB_SPEED_4: 	playbackSpeed = PB_SPEED_8; 	break;
            case PB_SPEED_8: 	playbackSpeed = PB_SPEED_16; 	break;
            case PB_SPEED_16: 	playbackSpeed = PB_SPEED_32; 	break;
            case PB_SPEED_32: 	playbackSpeed = PB_SPEED_1; 	break;
            default:			playbackSpeed = PB_SPEED_1; 	break;
        }
    }
    else
    {
        playbackState              = PB_PLAY;
        pbState                    = PB_PLAY;
        playbackDirection          = PB_REW;
        timeBar->playbackDirection = PB_REW;
        playbackSpeed              = PB_SPEED_1;
    }

    appmgr_search_set_direction(playbackDirection);
    appmgr_search_set_speed(playbackSpeed, chBit);

    buttonPlay->setIcon(QIcon(":/images/play.png"));

    displaySpeed();
}
void PlayBarDialog::rewFrameClicked(void)
{
    if(playbackState == PB_PLAY)
    {
        if(indexAudio != 1)
        {
            SetAudioIcon(19);
            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
        }
    }

    if(playbackState == PB_PLAY)
    {
        if((playbackSpeed != PB_SPEED_1) || (playbackDirection == PB_REW))
        {
            appmgr_search_set_jump_level(0, 3); // Jump play(3 minute)
        }
        else
        {
            appmgr_search_set_jump(0); // Jump play(1 minute)
        }
    }

    displaySpeed();

    if(playbackState == PB_PLAY)
    {
        if(indexAudio == 1)
        {
            OutputAudio(19);
            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
        }
        else
        {
            if(currentSplit == Split_1)
            {
                OutputAudio(currentChannelNum);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
            }
            else if(currentSplit == Split_4)
            {
                OutputAudio(indexAudio-2);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, indexAudio-2);
            }
        }
    }
}
void PlayBarDialog::playClicked(void)
{
    int chBit = 0;

    if(indexAudio == 1)
    {
        OutputAudio(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }
    else
    {
        if(currentSplit == Split_1)
        {
            OutputAudio(currentChannelNum);
            appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
        }
        else if(currentSplit == Split_4)
        {
            OutputAudio(indexAudio-2);
            appmgr_search_set_audio_mute_on_off(AUDIO_PB, indexAudio-2);
        }
    }

    chBit = getPlaybackChannel();

    playbackState              = PB_PLAY;
    pbState                    = PB_PLAY;
    playbackDirection          = PB_FF;
    timeBar->playbackDirection = PB_FF;
    playbackSpeed              = PB_SPEED_1;

    buttonPlay->setIcon(QIcon(":/images/pause.png"));

    appmgr_search_set_direction(playbackDirection);
    appmgr_search_set_speed(playbackState, chBit);

    displaySpeed();
}
void PlayBarDialog::pauseClicked(void)
{
    int chBit = 0;

    if(indexAudio != 1)
    {
        SetAudioIcon(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }

    chBit = getPlaybackChannel();

    playbackState              = PB_PAUSE;
    pbState                    = PB_PAUSE;
    playbackDirection          = PB_FF;
    timeBar->playbackDirection = PB_FF;
    playbackSpeed              = PB_SPEED_1;

    buttonPlay->setIcon(QIcon(":/images/play.png"));
    appmgr_search_set_direction(playbackDirection);
    appmgr_search_set_speed(playbackState, chBit);

    displaySpeed();
}
void PlayBarDialog::playpauseClicked(void)
{
    int chBit = 0;

    if((playbackState == PB_PLAY) && (playbackDirection == PB_FF) && (playbackSpeed == PB_SPEED_1))
    {
        SetAudioIcon(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }
    else
    {
        if(indexAudio == 1)
        {
            OutputAudio(19);
            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
        }
        else
        {
            if(currentSplit == Split_1)
            {
                OutputAudio(currentChannelNum);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
            }
            else if(currentSplit == Split_4)
            {
                OutputAudio(indexAudio-2);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, indexAudio-2);
            }
        }
    }

    chBit = getPlaybackChannel();

    if((playbackState == PB_PLAY) && (playbackDirection == PB_FF) && (playbackSpeed == PB_SPEED_1))
    {
        playbackState              = PB_PAUSE;
        pbState                    = PB_PAUSE;
        playbackDirection          = PB_FF;
        timeBar->playbackDirection = PB_FF;
        playbackSpeed              = PB_SPEED_1;
        buttonPlay->setIcon(QIcon(":/images/play.png"));
        appmgr_search_set_direction(playbackDirection);
        appmgr_search_set_speed(playbackState, chBit);
    }
    else
    {
        playbackState              = PB_PLAY;
        pbState                    = PB_PLAY;
        playbackDirection          = PB_FF;
        timeBar->playbackDirection = PB_FF;
        playbackSpeed              = PB_SPEED_1;

        buttonPlay->setIcon(QIcon(":/images/pause.png"));
        appmgr_search_set_direction(playbackDirection);
        appmgr_search_set_speed(playbackState, chBit);
    }

    displaySpeed();
}
void PlayBarDialog::fowardFrameClicked(void)
{
    if(playbackState == PB_PLAY)
    {
        if(indexAudio != 1)
        {
            SetAudioIcon(19);
            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
        }
    }

    if(playbackState == PB_PLAY)
    {
        if((playbackSpeed != PB_SPEED_1) || (playbackDirection == PB_REW))
        {
            appmgr_search_set_jump_level(1, 3); // Jump play(3 minute)
        }
        else
        {
            appmgr_search_set_jump(1); // Jump play(1 minute)
        }
    }

    displaySpeed();

    if(playbackState == PB_PLAY)
    {
        if(indexAudio == 1)
        {
            OutputAudio(19);
            appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
        }
        else
        {
            if(currentSplit == Split_1)
            {
                OutputAudio(currentChannelNum);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
            }
            else if(currentSplit == Split_4)
            {
                OutputAudio(indexAudio-2);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, indexAudio-2);
            }
        }
    }
}
void PlayBarDialog::fastClicked(void)
{
    int chBit = 0;

    if(indexAudio != 1)
    {
        SetAudioIcon(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }

    chBit = getPlaybackChannel();

    if(playbackDirection == PB_FF)
    {
        playbackState              = PB_PLAY;
        pbState                    = PB_PLAY;
        playbackDirection          = PB_FF;
        timeBar->playbackDirection = PB_FF;

        switch(playbackSpeed)
        {
            case PB_SPEED_1: 	playbackSpeed = PB_SPEED_2; 	break;
            case PB_SPEED_2: 	playbackSpeed = PB_SPEED_4; 	break;
            case PB_SPEED_4: 	playbackSpeed = PB_SPEED_8; 	break;
            case PB_SPEED_8: 	playbackSpeed = PB_SPEED_16; 	break;
            case PB_SPEED_16: 	playbackSpeed = PB_SPEED_32; 	break;
            case PB_SPEED_32: 	playbackSpeed = PB_SPEED_2; 	break;
            default:			playbackSpeed = PB_SPEED_2; 	break;
        }
    }
    else
    {
        playbackState              = PB_PLAY;
        pbState                    = PB_PLAY;
        playbackDirection          = PB_FF;
        timeBar->playbackDirection = PB_FF;
        playbackSpeed              = PB_SPEED_2;
    }

    appmgr_search_set_direction(playbackDirection);
    appmgr_search_set_speed(playbackSpeed, chBit);

    buttonPlay->setIcon(QIcon(":/images/play.png"));

    displaySpeed();
}
void PlayBarDialog::setMaxSplit(int startCh, int split)
{
    playbackStartCh  = startCh;
    playbackMaxSplit = split;
}
void PlayBarDialog::updateTimeLine(void)
{
    int dlsEndHour = -1;
    struct tm tmNow;

    //qDebug("%s(), %s:%d ............. updateTimeLine\n", __func__, __FILE__, __LINE__);

    timeBar->sliderPlayTimeChange();

    localtime_r(&timeLogSelTime, &tmNow);

    if(dlsPlayback.isChecked && dlsPlayback.isDlsEnabled)
    {
        if(tmNow.tm_mon == dlsPlayback.dlsEndMonth && tmNow.tm_mday == dlsPlayback.dlsEndDay)
        {
            dlsEndHour = dlsPlayback.dlsEndHour;
        }
    }

    curPbTime = 0;

    if(changeDay)
    {
        changeDay  = 0;
        calSelTime = timeLogSelTime;
        qDebug("\n\t %s(), change Day !!  %s:%d ............. updateTimeLine\n", __func__, __FILE__, __LINE__);
    }
    else
    {
        playbackSpeed_old          = playbackSpeed;
        playbackState              = pbState = PB_PLAY;
        playbackSpeed              = PB_SPEED_1;
        playbackDirection          = PB_FF;
        timeBar->playbackDirection = PB_FF;
    }

    timeBar->setDlsEndDay(dlsEndHour);

    displaySpeed();
}
void PlayBarDialog::changePlaybackTime(int pos)
{
    int dir = 1;
    time_t now;

    if(playbackDirection == PB_REW)
    {
        dir = -1;
    }

    now = timeBar->getRecordExistTime(pos, dir);

    if(now > 0)
    {
        appmgr_search_set_time(now);
        //qDebug("%s(), pos = %d, %s \n", __func__, pos, atime(now));
    }
}
void PlayBarDialog::playbackTimeUpdate(time_t pbTime)
{
    struct tm tmNow;
    time_t uiPbtime = 0;
    int endOverlap  = 0,
        indexExpire = 0,
        dlsType     = DLS_OFF;

    //qDebug("%s(), %s:%d \n", __func__, __FILE__, __LINE__);

    curPbTime = pbTime;
    uiPbtime = pbTime;

    localtime_r(&pbTime, &tmNow);
    //qDebug("%s: pbTime: %s \n", __func__, atime(pbTime));

    if(dlsPlayback.isChecked && dlsPlayback.isDlsEnabled)
    {
        if(dlsPlayback.tDlsEnd > dlsPlayback.tDlsBegin)
        {
            if((uiPbtime >= dlsPlayback.tDlsBegin) && (uiPbtime < dlsPlayback.tDlsEnd))
            {
                dlsType = DLS_DAY;
            }
        }
        else
        {
            if(!((uiPbtime >= dlsPlayback.tDlsEnd) && (uiPbtime < dlsPlayback.tDlsBegin)))
            {
                dlsType = DLS_DAY;
            }
        }
    }

    if(dlsType)
    {
        if(tmNow.tm_mon == dlsPlayback.dlsEndMonth && tmNow.tm_mday == dlsPlayback.dlsEndDay && tmNow.tm_hour == dlsPlayback.dlsEndHour - 1)
        {
            endOverlap = 1;
        }
        else if(tmNow.tm_mon == dlsPlayback.dlsEndMonth && tmNow.tm_mday == dlsPlayback.dlsEndDay - 1 && tmNow.tm_hour == 23 && dlsPlayback.dlsEndHour == 0)
        {
            endOverlap = 2;
            uiPbtime += 3600;
        }
        else
        {
            uiPbtime += 3600;
            //qDebug("%s: uiPbtime: %s \n", __func__, atime(uiPbtime));
        }
    }

    time_t prevTime  = timeBar->getLatestPlaybackTime();
    indexExpire      = timeBar->updatePlaybackTime(uiPbtime, endOverlap);

    checkDayChanged(uiPbtime, prevTime, indexExpire);
}
void PlayBarDialog::searchDataUpdate(int type)
{
    if(type == SEARCH_REC_TIME)
    {
        //qDebug("%s(), %s:%d \n", __func__, __FILE__, __LINE__);
        updateTimeLine();
    }
}
void PlayBarDialog::checkDayChanged(time_t pbTime, time_t prevTime, int expired)
{
    struct tm tmPrev, tmCur;
    time_t now;
    int dlsType = DLS_OFF;

    localtime_r(&prevTime, &tmPrev);
    localtime_r(&pbTime, &tmCur);

    if(tmPrev.tm_year != tmCur.tm_year || tmPrev.tm_mon != tmCur.tm_mon || tmPrev.tm_mday != tmCur.tm_mday || expired)
    {
        //qDebug(" %s(), %s:%d \n", __func__, __FILE__, __LINE__);
        //qDebug(" %s: tmPrev: %s, tmCur: %s \n", __func__, atime(prevTime), atime(pbTime));

        if(tmPrev.tm_year != tmCur.tm_year || tmPrev.tm_mon != tmCur.tm_mon || tmPrev.tm_mday != tmCur.tm_mday)
        {
            changeDay = 1;
            qDebug("\n\t %s: Change Day !!! tmPrev: %s, tmCur: %s \n", __func__, atime(prevTime), atime(pbTime));
        }

        tmCur.tm_hour  = 0;
        tmCur.tm_min   = 0;
        tmCur.tm_sec   = 0;
        now            = mktime(&tmCur);
        timeLogSelTime = now;
        //qDebug(" %s: timeLogSelTime: %s \n", __func__, atime(timeLogSelTime));
        //if (expired) qDebug("############## time expired");

        // convert ui time(DLS) to local time
        if(tmPrev.tm_year != tmCur.tm_year)
        {
            appmgr_make_dls_time_info(tmCur.tm_year, 0, &dlsPlayback);
        }

        if(dlsPlayback.isChecked && dlsPlayback.isDlsEnabled)
        {
            if(dlsPlayback.tDlsEnd > dlsPlayback.tDlsBegin)
            {
                if((now >= dlsPlayback.tDlsBegin) && (now < dlsPlayback.tDlsEnd))
                {
                    now -= 3600;
                }
            }
            else
            {
                if(!((now >= dlsPlayback.tDlsEnd) && (now < dlsPlayback.tDlsBegin)))
                {
                    now -= 3600;
                }
            }
        }

        if(dlsPlayback.isChecked && dlsPlayback.isDlsEnabled)
        {
            if(dlsPlayback.tDlsEnd > dlsPlayback.tDlsBegin)
            {
                if((tmCur.tm_mon == dlsPlayback.dlsBeginMonth) && (tmCur.tm_mday == dlsPlayback.dlsBeginDay) &&
                        (tmCur.tm_mon == dlsPlayback.dlsEndMonth) && (tmCur.tm_mday == dlsPlayback.dlsEndDay))
                {
                    dlsType = DLS_START_END_DAY;
                }
                else if((tmCur.tm_mon == dlsPlayback.dlsBeginMonth) && (tmCur.tm_mday == dlsPlayback.dlsBeginDay))
                {
                    dlsType = DLS_START_DAY;
                }
                else if((tmCur.tm_mon == dlsPlayback.dlsEndMonth) && (tmCur.tm_mday == dlsPlayback.dlsEndDay))
                {
                    dlsType = DLS_END_DAY;
                }
                else if((pbTime >= dlsPlayback.tDlsBegin) && (pbTime < dlsPlayback.tDlsEnd))
                {
                    dlsType = DLS_DAY;
                }
                else
                {
                    dlsType = DLS_OFF;
                }
            }
            else
            {
                if((tmCur.tm_mon == dlsPlayback.dlsBeginMonth) && (tmCur.tm_mday == dlsPlayback.dlsBeginDay))
                {
                    dlsType = DLS_START_DAY;
                }
                else if((tmCur.tm_mon == dlsPlayback.dlsEndMonth) && (tmCur.tm_mday == dlsPlayback.dlsEndDay))
                {
                    dlsType = DLS_END_DAY;
                }
                else if(!((pbTime >= dlsLive.tDlsEnd) && (pbTime < dlsLive.tDlsBegin)))
                {
                    dlsType = DLS_DAY;
                }
                else
                {
                    dlsType = DLS_OFF;
                }
            }
        }

        qDebug("test reSearch Time =====================================");
        if(dlsType != DLS_OFF)
        {
            appmgr_search_get_log(SEARCH_REC_TIME, QUEUE_QT_CORE, timeLogSelTime, dlsType, 0);
        }
        else
        {
            appmgr_search_get_log(SEARCH_REC_TIME, QUEUE_QT_CORE, now, dlsType, 0);
        }
        qDebug("\n%s: dlsType = %d, %s, now[%s] \n", __func__, dlsType, atime(timeLogSelTime), atime(now));
    }
}
void PlayBarDialog::PausePlayChange(int state)
{
    int chBit = 0;

    if(state == PB_PLAY)
    {
        OutputAudio(currentChannelNum);
        appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
    }
    else if(state == PB_PAUSE)
    {
        OutputAudio(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
    }

    chBit = getPlaybackChannel();

    if(state == PB_PLAY)
    {
        playbackState = pbState = PB_PLAY;
        appmgr_search_set_speed(playbackSpeed, chBit);
    }
    else
    {
        playbackState = pbState = PB_PAUSE;
        appmgr_search_set_speed(playbackState, chBit);
    }
}
int PlayBarDialog::GetStatePausePlay(void)
{
    return playbackState;
}
int PlayBarDialog::getPlaybackChannel(void)
{
    int chBit = 0;
    qDebug("\n %s: splitStartChNum = %d, currentSplit = %d \n", __func__, splitStartChNum, currentSplit);

    if(currentSplit == Split_1)
    {
        chBit = 0x01 << splitStartChNum;
    }
    else if(currentSplit == Split_4)
    {
        chBit = 0x0f << splitStartChNum;
    }
    else if(currentSplit == Split_9)
    {
        chBit = 0x00ff;
    }
    else if(currentSplit == Split_10)
    {
        chBit = 0x03ff;
    }
    else if(currentSplit == Split_17)
    {
        chBit = 0x00ff;
    }
    else
    {
        chBit = 0xffff;
    }

    qDebug("\n %s: chBit %x \n", __func__, chBit);

    return chBit;
}
