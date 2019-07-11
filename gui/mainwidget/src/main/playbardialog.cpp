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

PlayBarDialog::PlayBarDialog(QWidget *parent)
    : QDialog(parent)
{    
    if(mainHeight == 720)
    {
        Ui::PlayBarDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        labelDate = ui720.labelDate;
        labelTime = ui720.labelTime;
        labelSpeed = ui720.labelSpeed;

        buttonAudio = ui720.buttonAudio;
        buttonRewFrame = ui720.buttonRewFrame;
        buttonRew = ui720.buttonRew;
        buttonPlay = ui720.buttonPlay;
        buttonFf = ui720.buttonFf;
        buttonFfFrame = ui720.buttonFfFrame;
        buttonStill = ui720.buttonStill;
        buttonClose = ui720.buttonClose;
        buttonZoom = ui720.buttonZoom;

        buttonSplit = ui720.buttonSplit;
        buttonPrev = ui720.buttonPrev;
        buttonSplit1 = ui720.buttonSplit1;
        buttonSplit4 = ui720.buttonSplit4;
        buttonSplit9 = ui720.buttonSplit9;
        buttonNext = ui720.buttonNext;

        PLAYBAR_BTN_SIZE=70;
        labelFontSize=32;

        timeBarWidth=1000;      // timebar TL_WIDTH + TL_LEFT_GAP + TL_SLIDER_GAP*2
        timeBarHeightSmall=70;  // timebar TL_UP_MARGIN+TL_HEIGHT+margin(5px)
        timeBarHeightBig=150;   // timebar TL_UP_MARGIN+TL_HEIGHT+margin(5px)
    }
    else
    {
        Ui::PlayBarDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        labelDate = ui1080.labelDate;
        labelTime = ui1080.labelTime;
        labelSpeed = ui1080.labelSpeed;

        buttonAudio = ui1080.buttonAudio;
        buttonRewFrame = ui1080.buttonRewFrame;
        buttonRew = ui1080.buttonRew;
        buttonPlay = ui1080.buttonPlay;
        buttonFf = ui1080.buttonFf;
        buttonFfFrame = ui1080.buttonFfFrame;
        buttonStill = ui1080.buttonStill;
        buttonClose = ui1080.buttonClose;
        buttonZoom = ui1080.buttonZoom;

        buttonSplit = ui1080.buttonSplit;
        buttonSplit = ui1080.buttonSplit;
        buttonPrev = ui1080.buttonPrev;
        buttonSplit1 = ui1080.buttonSplit1;
        buttonSplit4 = ui1080.buttonSplit4;
        buttonSplit9 = ui1080.buttonSplit9;
        buttonNext = ui1080.buttonNext;

        PLAYBAR_BTN_SIZE=100;
        labelFontSize=48;

        timeBarWidth=1500;
        timeBarHeightSmall=110;
        timeBarHeightBig=220;

        labelDate->setStyleSheet("font:48px;");
        labelTime->setStyleSheet("font:48px;");
        labelSpeed->setStyleSheet("font:48px;");
    }

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

    if(mainHeight == 720)
    {
        //x=label margin(20)+label width(200)+space(2)
        timeBar->setGeometry(QRect(222, 6, timeBarWidth, timeBarHeightSmall));
    }
    else
    {
        timeBar->setGeometry(QRect(330, 10, timeBarWidth, timeBarHeightSmall));
    }

    connect(buttonSplit,    SIGNAL(clicked()),                this, SLOT(onButtonSplit      (void)));
    connect(buttonAudio,    SIGNAL(clicked()),                this, SLOT(onButtonAudio      (void)));
    connect(buttonZoom,     SIGNAL(clicked()),                this, SLOT(onButtonZoom       (void)));
    connect(buttonRew,      SIGNAL(clicked()),                this, SLOT(rewClicked         (void)));
    connect(buttonRewFrame, SIGNAL(clicked()),                this, SLOT(rewFrameClicked    (void)));
    connect(buttonPlay,     SIGNAL(clicked()),                this, SLOT(playpauseClicked   (void)));
    connect(buttonFf,       SIGNAL(clicked()),                this, SLOT(fastClicked        (void)));
    connect(buttonFfFrame,  SIGNAL(clicked()),                this, SLOT(fowardFrameClicked (void)));
    connect(buttonStill,    SIGNAL(clicked()),                this, SLOT(clickBackup        (void)));
    connect(buttonClose,    SIGNAL(clicked()),                this, SLOT(closeSearchBar     (void)));
    connect(timeBar,        SIGNAL(playTimeChanged(int)),     this, SLOT(changePlaybackTime (int )));
    connect(timeBar,        SIGNAL(updateDateLabel(QString)), this, SLOT(onUpdateDateLabel  (QString)));
    connect(timeBar,        SIGNAL(updateTimeLabel(QString)), this, SLOT(onUpdateTimeLabel  (QString)));

    connect(buttonPrev,     SIGNAL(clicked()),                this, SLOT(buttonPrevClicked   (void)));
    connect(buttonSplit1,   SIGNAL(clicked()),                this, SLOT(buttonSplit1Clicked (void)));
    connect(buttonSplit4,   SIGNAL(clicked()),                this, SLOT(buttonSplit4Clicked (void)));
    connect(buttonSplit9,   SIGNAL(clicked()),                this, SLOT(buttonSplit9Clicked (void)));
    connect(buttonNext,     SIGNAL(clicked()),                this, SLOT(buttonNextClicked   (void)));

    connect(buttonPrev,     SIGNAL(pressed()),                this, SLOT(buttonPrevPressed   (void)));
    connect(buttonSplit1,   SIGNAL(pressed()),                this, SLOT(buttonSplit1Pressed (void)));
    connect(buttonSplit4,   SIGNAL(pressed()),                this, SLOT(buttonSplit4Pressed (void)));
    connect(buttonSplit9,   SIGNAL(pressed()),                this, SLOT(buttonSplit9Pressed (void)));
    connect(buttonNext,     SIGNAL(pressed()),                this, SLOT(buttonNextPressed   (void)));

    connect(buttonPrev,     SIGNAL(released()),               this, SLOT(buttonPrevReleased  (void)));
    connect(buttonSplit1,   SIGNAL(released()),               this, SLOT(buttonSplit1Released(void)));
    connect(buttonSplit4,   SIGNAL(released()),               this, SLOT(buttonSplit4Released(void)));
    connect(buttonSplit9,   SIGNAL(released()),               this, SLOT(buttonSplit9Released(void)));
    connect(buttonNext,     SIGNAL(released()),               this, SLOT(buttonNextReleased  (void)));

    buttonPrev  ->installEventFilter(this);
    buttonSplit1->installEventFilter(this);
    buttonSplit4->installEventFilter(this);
    buttonSplit9->installEventFilter(this);
    buttonNext  ->installEventFilter(this);

    indexAudio = 0;
    ispbMute=0;
    isSplit=false;
}
PlayBarDialog::~PlayBarDialog(void)
{
}
void PlayBarDialog::createPlaySpeedControlButtons(void)
{
    labelSpeed->setFont( QFont("unifont", labelFontSize, QFont::Bold) );
    labelSpeed->setSizePolicy  (QSizePolicy::Fixed, QSizePolicy::Fixed);

    buttonZoom     ->setIconSize     (QSize(PLAYBAR_BTN_SIZE/2, PLAYBAR_BTN_SIZE/2));
    buttonZoom     ->setIcon         (QIcon(":images/timeline_zoom_in.png"));

    buttonAudio    ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonAudio    ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonAudio    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonAudio    ->setIcon         (QIcon(":/images/aomute.png"));

    buttonRew      ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonRew      ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRew      ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRew      ->setIcon         (QIcon(":/images/rew.png"));

    buttonRewFrame ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonRewFrame ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRewFrame ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonRewFrame ->setIcon         (QIcon(":/images/rew_frame.png"));

    buttonPlay     ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonPlay     ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonPlay     ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonPlay     ->setIcon         (QIcon(":/images/play.png"));

    buttonFfFrame  ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonFfFrame  ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFfFrame  ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFfFrame  ->setIcon         (QIcon(":/images/ff_frame.png"));

    buttonFf       ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonFf       ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFf       ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonFf       ->setIcon         (QIcon(":/images/ff.png"));

    buttonStill    ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonStill    ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonStill    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonStill    ->setIcon         (QIcon(":/images/still_image.png"));

    buttonClose    ->setSizePolicy   (QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonClose    ->setFixedSize    (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonClose    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonClose    ->setIcon         (QIcon(":/images/close.png"));

    buttonSplit    ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonSplit    ->setIcon         (QIcon(":/images/pb_split9.png"));

    buttonPrev     ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonPrev     ->setIcon         (QIcon(":images/channel_prev.png"));
    buttonPrev     ->hide();

    buttonSplit1   ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonSplit1   ->setIcon         (QIcon(":images/split1.png"));
    buttonSplit1   ->hide();

    buttonSplit4   ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonSplit4   ->setIcon         (QIcon(":images/split4.png"));
    buttonSplit4   ->hide();

    buttonSplit9   ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonSplit9   ->setIcon         (QIcon(":images/split9.png"));
    buttonSplit9   ->hide();

    buttonNext     ->setIconSize     (QSize(PLAYBAR_BTN_SIZE, PLAYBAR_BTN_SIZE));
    buttonNext     ->setIcon         (QIcon(":images/channel_next.png"));
    buttonNext     ->hide();
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
        buttonZoom->show();
    }
    else
    {
        buttonRewFrame->hide();
        buttonFfFrame->hide();
        buttonZoom->hide();
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
            //for(int i = 0; i < devInfo.videoNum; i++)
            for(int i = 0; i < 8; i++)
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
        case  0: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); emit setAudio(1);     break; }
        case  1: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); emit setAudio(2);     break; }
        case  2: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); emit setAudio(3);     break; }
        case  3: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); emit setAudio(4);     break; }
        case  4: { buttonAudio->setIcon(QIcon(":/images/audio5.png")); emit setAudio(5);     break; }
        case  5: { buttonAudio->setIcon(QIcon(":/images/audio6.png")); emit setAudio(6);     break; }
        case  6: { buttonAudio->setIcon(QIcon(":/images/audio7.png")); emit setAudio(7);     break; }
        case  7: { buttonAudio->setIcon(QIcon(":/images/audio8.png")); emit setAudio(8);     break; }
        case 19: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); emit setAudioMute();  break; }
        default: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); emit setAudioMute();  break; }
    }
}
void PlayBarDialog::OutputAudio(int ch)
{
    switch(ch)
    {
        case  0: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); indexAudio = 2; emit setAudio(1);    break; }
        case  1: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); indexAudio = 3; emit setAudio(2);    break; }
        case  2: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); indexAudio = 4; emit setAudio(3);    break; }
        case  3: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); indexAudio = 5; emit setAudio(4);    break; }
        case  4: { buttonAudio->setIcon(QIcon(":/images/audio5.png")); indexAudio = 6; emit setAudio(5);    break; }
        case  5: { buttonAudio->setIcon(QIcon(":/images/audio6.png")); indexAudio = 7; emit setAudio(6);    break; }
        case  6: { buttonAudio->setIcon(QIcon(":/images/audio7.png")); indexAudio = 8; emit setAudio(7);    break; }
        case  7: { buttonAudio->setIcon(QIcon(":/images/audio8.png")); indexAudio = 9; emit setAudio(8);    break; }
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
            case  1: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19); emit setAudioMute(); break; }
            case  2: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         0); emit setAudio(1);    break; }
            case  3: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         1); emit setAudio(2);    break; }
            case  4: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         2); emit setAudio(3);    break; }
            case  5: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         3); emit setAudio(4);    break; }
            case  6: { buttonAudio->setIcon(QIcon(":/images/audio5.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         4); emit setAudio(5);    break; }
            case  7: { buttonAudio->setIcon(QIcon(":/images/audio6.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         5); emit setAudio(6);    break; }
            case  8: { buttonAudio->setIcon(QIcon(":/images/audio7.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         6); emit setAudio(7);    break; }
            case  9: { buttonAudio->setIcon(QIcon(":/images/audio8.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         7); emit setAudio(8);    break; }
        }

        if(indexAudio != 1)
        {
            indexAudio = 0;
        }
    }
    else
    {
        //if( indexAudio > devInfo.videoNum)
        if(indexAudio > 8 )
        {
            indexAudio = 0;
        }

        switch(++indexAudio)
        {
            case  1: { buttonAudio->setIcon(QIcon(":/images/aomute.png")); appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19); emit setAudioMute(); break; }
            case  2: { buttonAudio->setIcon(QIcon(":/images/audio1.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         0); emit setAudio(1);    break; }
            case  3: { buttonAudio->setIcon(QIcon(":/images/audio2.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         1); emit setAudio(2);    break; }
            case  4: { buttonAudio->setIcon(QIcon(":/images/audio3.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         2); emit setAudio(3);    break; }
            case  5: { buttonAudio->setIcon(QIcon(":/images/audio4.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         3); emit setAudio(4);    break; }
            case  6: { buttonAudio->setIcon(QIcon(":/images/audio5.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         4); emit setAudio(5);    break; }
            case  7: { buttonAudio->setIcon(QIcon(":/images/audio6.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         5); emit setAudio(6);    break; }
            case  8: { buttonAudio->setIcon(QIcon(":/images/audio7.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         6); emit setAudio(7);    break; }
            case  9: { buttonAudio->setIcon(QIcon(":/images/audio8.png")); appmgr_search_set_audio_mute_on_off(AUDIO_PB,         7); emit setAudio(8);    break; }
        }
    }
}
void PlayBarDialog::onButtonZoom(void)
{
    if( isSplit ) { setSplitMode(false); }

    switch(timeBar->getTimeLineStatus())
    {
        case 1 : { hideButton(); timeBar->setTimeLineStatus(3); break; }
        case 2 : { hideButton(); timeBar->setTimeLineStatus(4); break; }
        case 3 : { showButton(); timeBar->setTimeLineStatus(1); break; }
        case 4 : { showButton(); timeBar->setTimeLineStatus(2); break; }
    }
}
void PlayBarDialog::hideButton(void)
{
    buttonAudio->hide();
    buttonFfFrame->hide();
    buttonFf->hide();
    buttonPlay->hide();
    buttonRewFrame->hide();
    buttonRew->hide();
    buttonStill->hide();
    buttonClose->hide();
    timeBar->resize(timeBarWidth, timeBarHeightBig);

    buttonZoom->setIcon    (QIcon(":images/timeline_zoom_out.png"));
}
void PlayBarDialog::showButton(void)
{
    buttonAudio->show();
    buttonFfFrame->show();
    buttonFf->show();
    buttonPlay->show();
    buttonRewFrame->show();
    buttonRew->show();
    buttonStill->show();
    buttonClose->show();
    timeBar->resize(timeBarWidth, timeBarHeightSmall);

    buttonZoom->setIcon    (QIcon(":images/timeline_zoom_in.png"));
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
                case PB_SPEED_1: 	str = tr("Play");                                           break;
                case PB_SPEED_2: 	str = QString("%1 %2").arg(tr("FF"), QString("x2"));        break;
                case PB_SPEED_4: 	str = QString("%1 %2").arg(tr("FF"), QString("x4"));        break;
                case PB_SPEED_8: 	str = QString("%1 %2").arg(tr("FF"), QString("x8"));        break;
                case PB_SPEED_16:	str = QString("%1 %2").arg(tr("FF"), QString("x16"));       break;
                case PB_SPEED_32: 	str = QString("%1 %2").arg(tr("FF"), QString("x32"));       break;
                case PB_SPEED_64: 	str = QString("%1 %2").arg(tr("FF"), QString("x64"));       break;
                case PB_SPEED_128: 	str = QString("%1 %2").arg(tr("FF"), QString("x128"));      break;
                case PB_SPEED_256: 	str = QString("%1 %2").arg(tr("FF"), QString("x256"));      break;
                case PB_SPEED_1024:	str = QString("%1 %2").arg(tr("FF"), QString("x1024"));     break;
                default: return;
            }
        }
        else
        {
            switch(playbackSpeed)
            {
                case PB_SPEED_1: 	str = QString("%1 %2").arg(tr("REW"), QString("x1"));       break;
                case PB_SPEED_2: 	str = QString("%1 %2").arg(tr("REW"), QString("x2"));       break;
                case PB_SPEED_4: 	str = QString("%1 %2").arg(tr("REW"), QString("x4"));       break;
                case PB_SPEED_8: 	str = QString("%1 %2").arg(tr("REW"), QString("x8"));       break;
                case PB_SPEED_16:	str = QString("%1 %2").arg(tr("REW"), QString("x16"));      break;
                case PB_SPEED_32: 	str = QString("%1 %2").arg(tr("REW"), QString("x32"));      break;
                case PB_SPEED_64: 	str = QString("%1 %2").arg(tr("REW"), QString("x64"));      break;
                case PB_SPEED_128: 	str = QString("%1 %2").arg(tr("REW"), QString("x128")); 	break;
                case PB_SPEED_256: 	str = QString("%1 %2").arg(tr("REW"), QString("x256")); 	break;
                case PB_SPEED_1024:	str = QString("%1 %2").arg(tr("REW"), QString("x1024"));    break;
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
#if 0 //not use dls
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
#else
void PlayBarDialog::updateTimeLine(void)
{
    if(changeDay)
    {
        changeDay = 0;
        calSelTime = timeLogSelTime;
        timeBar->updateTimeLinePixmap();
    }
}
#endif
void PlayBarDialog::initPlayBar()
{
    curPbTime = 0;
    playbackSpeed_old          = playbackSpeed;
    playbackState              = pbState = PB_PLAY;
    playbackSpeed              = PB_SPEED_1;
    playbackDirection          = PB_FF;
    timeBar->playbackDirection = PB_FF;

    timeBar->initPlayTimeBar();
    displaySpeed();
    showButton();
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
        if(currentSplit==Split_1)
        {
            if(ispbMute)
            {
                OutputAudio(19);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, 19);
            }
            else if(playbackDirection != PB_FF || playbackSpeed != PB_SPEED_1)
            {
                OutputAudio(19);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, 19);
                indexAudio=currentChannelNum+2;
            }
            else
            {
                OutputAudio(currentChannelNum);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, currentChannelNum);
            }
        }
        else
        {
            if(pbPreviousAudio==AUDIO_LIVE_MUTE-1)
            {
                OutputAudio(19);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, 19);
            }
            else if(playbackDirection != PB_FF || playbackSpeed != PB_SPEED_1)
            {
                OutputAudio(19);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, 19);
                indexAudio=pbPreviousAudio;
            }
            else
            {
                OutputAudio(pbPreviousAudio-2);
                appmgr_search_set_audio_mute_on_off(AUDIO_PB, pbPreviousAudio-2);
            }
        }
    }
    else if(state == PB_PAUSE)
    {
        if(currentSplit!=Split_1 && currentSplit!=pbPreviousSplit) //when split_4 -> split_1
        {
            pbPreviousAudio=indexAudio;
        }

        if(indexAudio==AUDIO_LIVE_MUTE-1) //when current playback Audio is mute
        {
            ispbMute=1;
        }
        else
        {
            ispbMute=0;
        }

        pbPreviousSplit=currentSplit;

        OutputAudio(19);
        appmgr_search_set_audio_mute_on_off(AUDIO_LIVE_MUTE, 19);
        indexAudio=pbPreviousAudio;
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
void PlayBarDialog::onUpdateDateLabel     (QString date)
{
    labelDate->setText(date);
}
void PlayBarDialog::onUpdateTimeLabel     (QString time)
{
    labelTime->setText(time);
}
void PlayBarDialog::onButtonSplit(void)
{
    isSplit = !isSplit;

    if(isSplit) { showSplitButton(); }
    else        { hideSplitButton(); }

    updateSplitButton();
}
void PlayBarDialog::buttonSplit1Clicked()
{    
    setFocusSplitButton(1);

    if(currentSplit != Split_1)
    {
        emit changeSplit( Split_1);
    }
}
void PlayBarDialog::buttonSplit4Clicked()
{
    setFocusSplitButton(2);

    if(currentSplit != Split_4)
    {
        emit changeSplit(Split_4);
    }
}
void PlayBarDialog::buttonSplit9Clicked()
{
    setFocusSplitButton(3);

    if (currentSplit != Split_9)
    {
        emit changeSplit(Split_9);
    }
}
void PlayBarDialog::buttonPrevClicked()
{
    setFocusSplitButton(0);

    emit changeChannel(0);
}
void PlayBarDialog::buttonNextClicked()
{
    setFocusSplitButton(4);

    emit changeChannel(1);
}
void PlayBarDialog::buttonPrevPressed()
{
    buttonPrev->setIcon(QIcon(":/images/channel_prev_pressed.png"));
}
void PlayBarDialog::buttonSplit1Pressed()
{
    buttonSplit1->setIcon(QIcon(":/images/split1_pressed.png"));
}
void PlayBarDialog::buttonSplit4Pressed()
{
    buttonSplit4->setIcon(QIcon(":/images/split4_pressed.png"));
}
void PlayBarDialog::buttonSplit9Pressed()
{
    buttonSplit9->setIcon(QIcon(":/images/split9_pressed.png"));
}
void PlayBarDialog::buttonNextPressed()
{
    buttonNext->setIcon(QIcon(":/images/channel_next_pressed.png"));
}
void PlayBarDialog::buttonPrevReleased()
{
    buttonPrev->setIcon(QIcon(":/images/channel_prev_focus.png"));
}
void PlayBarDialog::buttonSplit1Released()
{
    buttonSplit1->setIcon(QIcon(":/images/split1_focus.png"));
}
void PlayBarDialog::buttonSplit4Released()
{
    buttonSplit4->setIcon(QIcon(":/images/split4_focus.png"));
}
void PlayBarDialog::buttonSplit9Released()
{
    buttonSplit9->setIcon(QIcon(":/images/split9_focus.png"));
}
void PlayBarDialog::buttonNextReleased()
{
    buttonNext->setIcon(QIcon(":/images/channel_next_focus.png"));
}
bool PlayBarDialog::eventFilter(QObject *o, QEvent *e)
{
    if(e->type() == Qt::RightButton)
    {
        if     ( o == buttonPrev   )  { setFocusSplitButton(0); }
        else if( o == buttonSplit1 )  { setFocusSplitButton(1); }
        else if( o == buttonSplit4 )  { setFocusSplitButton(2); }
        else if( o == buttonSplit9 )  { setFocusSplitButton(3); }
        else if( o == buttonNext   )  { setFocusSplitButton(4); }
    }
    return QWidget::eventFilter(o, e);
}
void PlayBarDialog::updateSplitButton()
{
    switch ( currentSplit )
    {
        case Split_1 :
        {
            if( isSplit ) { buttonSplit->setIcon(QIcon(":images/pb_split1_pressed.png")); }
            else          { buttonSplit->setIcon(QIcon(":images/pb_split1.png")); }
            break;
        }
        case Split_4 :
        {
            if( isSplit ) { buttonSplit->setIcon(QIcon(":images/pb_split4_pressed.png")); }
            else          { buttonSplit->setIcon(QIcon(":images/pb_split4.png")); }
            break;
        }
        case Split_9 :
        {
            if( isSplit ) { buttonSplit->setIcon(QIcon(":images/pb_split9_pressed.png")); }
            else          { buttonSplit->setIcon(QIcon(":images/pb_split9.png")); }
            break;
        }
    }
}
void PlayBarDialog::setFocusSplitButton(int btnNum)
{
    /*
        case 0  : previous button
        case 1  : split 1  button
        case 2  : split 4  button
        case 3  : split 9  button
        case 4  : next     button
    */

    switch( btnNum )
    {
        case 0 :
        {
            focusSplitButton=0;
            buttonPrev  ->setIcon(QIcon(":/images/channel_prev_focus.png"));
            buttonSplit1->setIcon(QIcon(":/images/split1.png"));
            buttonSplit4->setIcon(QIcon(":/images/split4.png"));
            buttonSplit9->setIcon(QIcon(":/images/split9.png"));
            buttonNext  ->setIcon(QIcon(":/images/channel_next.png"));
            break;
        }
        case 1 :
        {
            focusSplitButton=1;
            buttonPrev  ->setIcon(QIcon(":/images/channel_prev.png"));
            buttonSplit1->setIcon(QIcon(":/images/split1_focus.png"));
            buttonSplit4->setIcon(QIcon(":/images/split4.png"));
            buttonSplit9->setIcon(QIcon(":/images/split9.png"));
            buttonNext  ->setIcon(QIcon(":/images/channel_next.png"));
            break;
        }
        case 2 :
        {
            focusSplitButton=2;
            buttonPrev  ->setIcon(QIcon(":/images/channel_prev.png"));
            buttonSplit1->setIcon(QIcon(":/images/split1.png"));
            buttonSplit4->setIcon(QIcon(":/images/split4_focus.png"));
            buttonSplit9->setIcon(QIcon(":/images/split9.png"));
            buttonNext  ->setIcon(QIcon(":/images/channel_next.png"));
            break;
        }
        case 3 :
        {
            focusSplitButton=3;
            buttonPrev  ->setIcon(QIcon(":/images/channel_prev.png"));
            buttonSplit1->setIcon(QIcon(":/images/split1.png"));
            buttonSplit4->setIcon(QIcon(":/images/split4.png"));
            buttonSplit9->setIcon(QIcon(":/images/split9_focus.png"));
            buttonNext  ->setIcon(QIcon(":/images/channel_next.png"));
            break;
        }

        default :
        {
            focusSplitButton=btnNum;
            buttonPrev  ->setIcon(QIcon(":/images/channel_prev.png"));
            buttonSplit1->setIcon(QIcon(":/images/split1.png"));
            buttonSplit4->setIcon(QIcon(":/images/split4.png"));
            buttonSplit9->setIcon(QIcon(":/images/split9.png"));
            buttonNext  ->setIcon(QIcon(":/images/channel_next_focus.png"));
            break;
        }
    }
}
bool PlayBarDialog::getSplitMode()
{
    return isSplit;
}
void PlayBarDialog::setSplitMode(bool state)
{
    isSplit = state;

    if ( isSplit ) { showSplitButton(); }
    else           { hideSplitButton(); }
}

void PlayBarDialog::showSplitButton()
{
    int timeLineState = timeBar->getTimeLineStatus();
    if( timeLineState > 2 )
    {
        timeBar->setTimeLineStatus(timeLineState-2);
        showButton();
    }

    //show split button
    buttonRewFrame->hide();
    buttonRew->hide();
    buttonPlay->hide();
    buttonFf->hide();
    buttonFfFrame->hide();

    buttonPrev->show();
    buttonSplit1->show();
    buttonSplit4->show();
    buttonSplit9->show();
    buttonNext->show();

    focusSplitButton=currentSplit;
    setFocusSplitButton(focusSplitButton);
    updateSplitButton();
}
void PlayBarDialog::hideSplitButton()
{
    //show play button
    buttonRew->show();
    buttonPlay->show();
    buttonFf->show();

    buttonPrev->hide();
    buttonSplit1->hide();
    buttonSplit4->hide();
    buttonSplit9->hide();
    buttonNext->hide();

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

    updateSplitButton();
}
void PlayBarDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up :
        {
            if( isSplit )
            {
                if( focusSplitButton >= 4 ) { focusSplitButton=0; }
                else                        { focusSplitButton++; }
                setFocusSplitButton(focusSplitButton);

                break;
            }


            if( !EventSearchPB && (( timeBar->getTimeLineStatus() == 2 ) || ( timeBar->getTimeLineStatus() ==4 )) )
            {
                if( playbackSpeed == PB_SPEED_1 )
                {
                    appmgr_search_set_jump_level(1,1);
                }
                else
                {
                    appmgr_search_set_jump_level(1,5);
                }
            }

            break;
        }
        case Qt::Key_Down :
        {
            if( isSplit )
            {
                if( focusSplitButton == 0 ) { focusSplitButton=4; }
                else                        { focusSplitButton--; }
                setFocusSplitButton(focusSplitButton);

                break;
            }

            if( !EventSearchPB && (( timeBar->getTimeLineStatus() == 2 ) || ( timeBar->getTimeLineStatus() ==4 )) )
            {
                if( playbackSpeed == PB_SPEED_1 )
                {
                    appmgr_search_set_jump_level(0,1);
                }
                else
                {
                    appmgr_search_set_jump_level(0,5);
                }
            }

            break;
        }
        case Qt::Key_Left :
        {
            if( isSplit )
            {
                if( focusSplitButton == 0 ) { focusSplitButton=4; }
                else                        { focusSplitButton--; }
                setFocusSplitButton(focusSplitButton);

                break;
            }

            if( !EventSearchPB )
            {
                if( timeBar->getTimeLineStatus() == 1 || timeBar->getTimeLineStatus() == 3 )
                {
                    appmgr_search_set_jump_level(0,60);
                }
                else
                {
                    appmgr_search_set_jump_level(0,5);
                }
            }

            break;
        }
        case Qt::Key_Right :
        {
            if( isSplit )
            {
                if( focusSplitButton >= 4 ) { focusSplitButton=0; }
                else                        { focusSplitButton++; }
                setFocusSplitButton(focusSplitButton);

                break;
            }

            if( !EventSearchPB )
            {
                if( timeBar->getTimeLineStatus() == 1 || timeBar->getTimeLineStatus() == 3 )
                {
                    appmgr_search_set_jump_level(1,60);
                }
                else
                {
                    appmgr_search_set_jump_level(1,5);
                }
            }

            break;
        }
        case Qt::Key_Enter:
        {
            if( isSplit )
            {
                switch( focusSplitButton )
                {
                    case 0 : { buttonPrevClicked();   break; }
                    case 1 : { buttonSplit1Clicked(); break; }
                    case 2 : { buttonSplit4Clicked(); break; }
                    case 3 : { buttonSplit9Clicked(); break; }
                    case 4 : { buttonNextClicked();   break; }
                }
                break;
            }

            if( !EventSearchPB )
            {
                switch(timeBar->getTimeLineStatus())
                {
                    case 1 : { timeBar->setTimeLineStatus(2); break; }
                    case 2 : { timeBar->setTimeLineStatus(1); break; }
                    case 3 : { timeBar->setTimeLineStatus(4); break; }
                    case 4 : { timeBar->setTimeLineStatus(3); break; }
                }
            }

            break;
        }
        case Qt::Key_Escape:
        {
            if( !EventSearchPB )
            {
                if( timeBar->getTimeLineStatus() == 1 || timeBar->getTimeLineStatus() == 3 )
                {
                    closeSearchBar();
                }
                else
                {
                    switch(timeBar->getTimeLineStatus())
                    {
                        case 1 : { timeBar->setTimeLineStatus(2); break; }
                        case 2 : { timeBar->setTimeLineStatus(1); break; }
                        case 3 : { timeBar->setTimeLineStatus(4); break; }
                        case 4 : { timeBar->setTimeLineStatus(3); break; }
                    }
                }
            }
            else
            {
                closeSearchBar();
            }

            break;
        }
        case Qt::Key_PageUp :
        {
            if( !EventSearchPB )
            {
                onButtonZoom();
            }
            break;
        }
        case Qt::Key_PageDown :
        {
            if( !EventSearchPB )
            {
                onButtonZoom();
            }
            break;
        }
    }
}
