#include <QtGui>
#include "normaldialog.h"
#include "main/mainglobal.h"
#include "dev/Ver.h"

NormalDialog::NormalDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonChannel->setFocus();

    connect(buttonChannel,     SIGNAL(released(void)), this, SLOT(onButtonChannel   (void)));
    connect(buttonFrameRate,   SIGNAL(released(void)), this, SLOT(onButtonFrameRate (void)));
    connect(buttonQuality,     SIGNAL(released(void)), this, SLOT(onButtonQuality   (void)));
    connect(buttonRecording,   SIGNAL(released(void)), this, SLOT(onButtonRecording (void)));
    connect(buttonAudio,       SIGNAL(released(void)), this, SLOT(onButtonAudio     (void)));
    connect(buttonDefault,     SIGNAL(released(void)), this, SLOT(onButtonDefault   (void)));
    connect(buttonSave,        SIGNAL(released(void)), this, SLOT(onButtonSave      (void)));
    connect(buttonClose,       SIGNAL(released(void)), this, SLOT(reject            (void)));
}
NormalDialog::~NormalDialog()
{
}
void NormalDialog::initNormalConfig(void)
{
    buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("All")));  indexChannel = 4;

    switch(getMaxFrame())
    {
        case  5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  indexFrameRate = 1; } break;
        case 10: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  indexFrameRate = 2; } break;
        case 15: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  indexFrameRate = 3; } break;
        case 20: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  indexFrameRate = 4; } break;
        case 25: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  indexFrameRate = 5; } break;
        case 30: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  indexFrameRate = 0; } break;
    }
    ChAllFrameRate=indexFrameRate;

    buttonQuality  ->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));     indexQuality = 0;       ChAllQuality=indexQuality;
    buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));      indexRecording = 0;     ChAllRecording=indexRecording;
    buttonAudio    ->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));          indexAudio = 0;         ChAllAudio=indexAudio;

}
void NormalDialog::onButtonChannel(void)
{
    /*
       Channel  indexChannel  ch
          1          1         0
          2          2         1
          3          3         2
          4          0         3
       All(1-4)      4      All(0-3)
    */

    switch(indexChannel)
    {
        case 0: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("All")));    indexChannel = 4; } break;
        case 1: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("2")));      indexChannel = 2; } break;
        case 2: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("3")));      indexChannel = 3; } break;
        case 3: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("4")));      indexChannel = 0; } break;
        case 4: { buttonChannel->setText(tr("%1\n%2").arg(tr("Channel"),tr("1")));      indexChannel = 1; } break;
    }

    if(indexChannel == 4)     //selected channel : All
    {
        //check current max frame
        int maxFrame = getMaxFrame();
        if((maxFrame == 15 && ChAllFrameRate > 3) || (maxFrame == 15 && ChAllFrameRate == 0))
        {
            ChAllFrameRate = 3;
        }
        else if((maxFrame == 25 && ChAllFrameRate > 5) || (maxFrame == 25 && ChAllFrameRate == 0))
        {
            ChAllFrameRate = 5;
        }

        //apply previous config
        switch(ChAllFrameRate)
        {
            case 1: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));   indexFrameRate = 1; }   break;
            case 2: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));   indexFrameRate = 2; }   break;
            case 3: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));   indexFrameRate = 3; }   break;
            case 4: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));   indexFrameRate = 4; }   break;
            case 5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));   indexFrameRate = 5; }   break;
            case 0: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));   indexFrameRate = 0; }   break;
        }
        switch(ChAllQuality)
        {
            case 1: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"  )));                  indexQuality = 1; }     break;
            case 2: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle")));                 indexQuality = 2; }     break;
            case 0: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));                 indexQuality = 0; }     break;
        }
        switch(ChAllRecording)
        {
            case 1: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));                indexRecording = 1; }   break;
            case 0: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));                indexRecording = 0; }   break;
        }
        switch(ChAllAudio)
        {
            case 1: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));                        indexAudio = 1; }       break;
            case 0: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));                        indexAudio = 0; }       break;
        }
    }

    else    //selected channel : 1,2,3,4
    {
        int ch=0;
        if(indexChannel <= 0)   { ch = 3;}
        else                    { ch = indexChannel-1; }

        //qDebug("Notice: %s %d, idxCh=%d, fr=%d q=%d r_t=%d a=%d\n", __func__, __LINE__, indexChannel, cfgSetup.rec.record_main.fr_hd[ch], cfgSetup.rec.record_main.quality[ch], cfgSetup.rec.record_type[ch], cfgSetup.rec.audio[ch]);

        if( getMaxFrame() < cfgSetup.rec.record_main.fr_hd[ch])
        {
            cfgSetup.rec.record_main.fr_hd[ch]=getMaxFrame();
        }

        switch(cfgSetup.rec.record_main.fr_hd[ch])
        {
            case  5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  indexFrameRate = 1; }   break;
            case 10: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  indexFrameRate = 2; }   break;
            case 15: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  indexFrameRate = 3; }   break;
            case 20: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  indexFrameRate = 4; }   break;
            case 25: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  indexFrameRate = 5; }   break;
            case 30: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  indexFrameRate = 0; }   break;
        }
        switch(cfgSetup.rec.record_main.quality[ch])
        {
            case QUALITY_ECONOMY: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"   )));   indexQuality = 1; }     break;
            case QUALITY_HIGH:    { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle")));   indexQuality = 2; }     break;
            case QUALITY_ULTRA:   { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));   indexQuality = 0; }     break;
        }
        switch(cfgSetup.rec.record_type[ch])
        {
            case false: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));            indexRecording = 1; }   break;
            case true:  { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));            indexRecording = 0; }   break;
        }
        switch(cfgSetup.rec.audio[ch])
        {
            case false: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));                    indexAudio = 1; }       break;
            case true:  { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));                    indexAudio = 0; }       break;
        }
    }
}
void NormalDialog::onButtonFrameRate(void)
{
    /*
       Frame Rate   indexFrame
            5           1
           10           2
           15           3
           20           4
           25           5
           30           0
    */

    if(indexChannel == 4)     //selected channel : All
    {
        //check max frame rate
        int maxFrame;
        switch(getMaxFrame())
        {
            case  5: { maxFrame = 1; }  break;
            case 10: { maxFrame = 2; }  break;
            case 15: { maxFrame = 3; }  break;
            case 20: { maxFrame = 4; }  break;
            case 25: { maxFrame = 5; }  break;
            case 30: { maxFrame = 6; }  break;
        }
        if(indexFrameRate >= maxFrame) { indexFrameRate = 0; }

        //display frame rate
        switch(indexFrameRate)
        {
            case 0: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));   indexFrameRate = 1; } break;
            case 1: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));   indexFrameRate = 2; } break;
            case 2: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));   indexFrameRate = 3; } break;
            case 3: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));   indexFrameRate = 4; } break;
            case 4: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));   indexFrameRate = 5; } break;
            case 5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));   indexFrameRate = 0; } break;
        }
        ChAllFrameRate = indexFrameRate;
    }
    else    //selected channel : 1,2,3,4
    {
        int ch = 0, arVIS[devInfo.videoNum];
        ver_get_vis_list(arVIS);

        if(indexChannel <= 0) { ch = 3; }
        else                  { ch = indexChannel-1; }

        if((arVIS[ch] == ver_vis_hd_1080_25p) || (arVIS[ch] == ver_vis_hd_1080_30p) || (arVIS[ch] == ver_vis_hd_1080_50p) ||
           (arVIS[ch] == ver_vis_hd_1080_60p) || (arVIS[ch] == ver_vis_hd_1080_i50) || (arVIS[ch] == ver_vis_hd_1080_i60) )     //FHD
        {
            if(indexFrameRate >= 3) { indexFrameRate = 0; }
        }
        else if((arVIS[ch] == ver_vis_pal)    || (arVIS[ch] == ver_vis_hd_720_25p)  || (arVIS[ch] == ver_vis_hd_720_50p))       //PAL
        {
            if(indexFrameRate >= 5) { indexFrameRate = 0; }
        }

        switch(indexFrameRate)
        {
            case 0: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] =  5;  indexFrameRate = 1; } break;
            case 1: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 10;  indexFrameRate = 2; } break;
            case 2: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 15;  indexFrameRate = 3; } break;
            case 3: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 20;  indexFrameRate = 4; } break;
            case 4: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 25;  indexFrameRate = 5; } break;
            case 5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  cfgSetup.rec.record_main.fr_hd[ch] = 30;  indexFrameRate = 0; } break;
        }
    }
}
void NormalDialog::onButtonQuality(void)
{
    /*
       Quality     indexQuality
         Low            1
         Middle         2
         High           0
    */

    if(indexChannel == 4)   //selected channel : All
    {
        switch(indexQuality)
        {
            case 0: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"  )));  indexQuality = 1; } break;
            case 1: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle"))); indexQuality = 2; } break;
            case 2: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  ))); indexQuality = 0; } break;
        }
        ChAllQuality = indexQuality;
    }
    else   //selected channel : 1,2,3,4
    {
        int ch = 0;
        if(indexChannel <= 0) { ch = 3; }
        else                  { ch = indexChannel-1; }

        switch(indexQuality)
        {
            case 0: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Low"  )));   cfgSetup.rec.record_main.quality[ch] = QUALITY_ECONOMY;  indexQuality = 1; } break;
            case 1: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("Middle")));  cfgSetup.rec.record_main.quality[ch] = QUALITY_HIGH;     indexQuality = 2; } break;
            case 2: { buttonQuality->setText(tr("%1\n%2").arg(tr("Quality"),tr("High"  )));  cfgSetup.rec.record_main.quality[ch] = QUALITY_ULTRA;    indexQuality = 0; } break;
        }
    }
}
void NormalDialog::onButtonRecording(void)
{
    /*
       Recording    indexRecording
          Off             1
          On              0
    */

    if(indexChannel == 4)   //selected channel : All
    {
        switch(indexRecording)
        {
            case 0: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));    indexRecording = 1; } break;
            case 1: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));    indexRecording = 0; } break;
        }
        ChAllRecording = indexRecording;
    }
    else   //selected channel : 1,2,3,4
    {
        int ch =0;
        if(indexChannel <= 0) { ch = 3; }
        else                  { ch = indexChannel-1; }

        switch(indexRecording)
        {
            case 0: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("Off")));  cfgSetup.rec.record_type[ch] = false;  indexRecording = 1; } break;
            case 1: { buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On" )));  cfgSetup.rec.record_type[ch] = true;   indexRecording = 0; } break;
        }
    }
}
void NormalDialog::onButtonAudio(void)
{
    /*
       Audio    indexAudio
        Off         1
        On          0
    */

    if(indexChannel == 4)   //selected channel : All
    {
        switch(indexAudio)
        {
            case 0: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));    indexAudio = 1; } break;
            case 1: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));    indexAudio = 0; } break;
        }
        ChAllAudio = indexAudio;
    }
    else   //selected channel : 1,2,3,4
    {
        int ch = 0;
        if(indexChannel <= 0) { ch = 3; }
        else                  { ch = indexChannel-1; }

        switch(indexAudio)
        {
            case 0: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("Off")));  cfgSetup.rec.audio[ch] = false;  indexAudio = 1; } break;
            case 1: { buttonAudio->setText(tr("%1\n%2").arg(tr("Audio"),tr("On" )));  cfgSetup.rec.audio[ch] = true;   indexAudio = 0; } break;
        }
    }
}
void NormalDialog::onButtonDefault(void)
{
    if(indexChannel == 4)   //selected channel : All
    {
        switch(getMaxFrame())
        {
            case  5: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr(" 5"),tr("Fps")));  indexFrameRate = 1; } break;
            case 10: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("10"),tr("Fps")));  indexFrameRate = 2; } break;
            case 15: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));  indexFrameRate = 3; } break;
            case 20: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("20"),tr("Fps")));  indexFrameRate = 4; } break;
            case 25: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));  indexFrameRate = 5; } break;
            case 30: { buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));  indexFrameRate = 0; } break;
        }
        ChAllFrameRate=indexFrameRate;

        buttonQuality  ->setText(tr("%1\n%2").arg(tr("Quality"),tr("High")));       indexQuality = 0;       ChAllQuality=indexQuality;
        buttonRecording->setText(tr("%1\n%2").arg(tr("Recording"),tr("On")));       indexRecording = 0;     ChAllRecording=indexRecording;
        buttonAudio    ->setText(tr("%1\n%2").arg(tr("Audio"),tr("On")));           indexAudio = 0;         ChAllAudio=indexAudio;
    }
    else    //selected channel : 1,2,3,4
    {
        int ch = 0, arVIS[devInfo.videoNum];
        ver_get_vis_list(arVIS);

        if(indexChannel <= 0) { ch = 3; }
        else                  { ch = indexChannel-1; }

        cfgSetup.rec.record_main.quality[ch] = QUALITY_ULTRA; indexQuality   = 0; buttonQuality   ->setText(tr("%1\n%2").arg(tr("Quality"  ),tr("High")));
        cfgSetup.rec.record_type[ch]         = true;          indexRecording = 0; buttonRecording ->setText(tr("%1\n%2").arg(tr("Recording"),tr("On"  )));
        cfgSetup.rec.audio[ch]               = true;          indexAudio     = 0; buttonAudio     ->setText(tr("%1\n%2").arg(tr("Audio"    ),tr("On"  )));

        if ((arVIS[ch] == ver_vis_hd_1080_25p) || (arVIS[ch] == ver_vis_hd_1080_30p) || (arVIS[ch] == ver_vis_hd_1080_50p) ||
            (arVIS[ch] == ver_vis_hd_1080_60p) || (arVIS[ch] == ver_vis_hd_1080_i50) || (arVIS[ch] == ver_vis_hd_1080_i60) )    //FHD
        {
            cfgSetup.rec.record_main.fr_hd[ch] = 15; indexFrameRate = 3; buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));
        }
        else if((arVIS[ch] == ver_vis_pal)     || (arVIS[ch] == ver_vis_hd_720_25p)  || (arVIS[ch] == ver_vis_hd_720_50p) )     //PAL
        {
            cfgSetup.rec.record_main.fr_hd[ch] = 25; indexFrameRate = 5; buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("25"),tr("Fps")));
        }
        else if ((arVIS[ch] == ver_vis_ntsc)   || (arVIS[ch] == ver_vis_hd_720_30p)  || (arVIS[ch] == ver_vis_hd_720_60p)  || (arVIS[ch] == ver_vis_unknown) )  //NTSC
        {
            cfgSetup.rec.record_main.fr_hd[ch] = 30; indexFrameRate = 0; buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("30"),tr("Fps")));
        }
        else    //etc or ERROR
        {
            qDebug("[ERROR]NormalDialog::onButtonDefault error");
            cfgSetup.rec.record_main.fr_hd[ch] = 15; indexFrameRate = 3; buttonFrameRate->setText(tr("%1\n%2 %3").arg(tr("Frame Rate"),tr("15"),tr("Fps")));
        }
    }
}
void NormalDialog::onButtonSave(void)
{
    if(indexChannel == 4)   //selected channel : All
    {
        int arVIS[devInfo.videoNum];
        ver_get_vis_list(arVIS);

        for( int i=0;i<devInfo.videoNum;i++)
        {
            switch(indexFrameRate)
            {
                case 0 :
                {
                    if((arVIS[i] == ver_vis_hd_1080_25p) || (arVIS[i] == ver_vis_hd_1080_30p) || (arVIS[i] == ver_vis_hd_1080_50p) ||
                       (arVIS[i] == ver_vis_hd_1080_60p) || (arVIS[i] == ver_vis_hd_1080_i50) || (arVIS[i] == ver_vis_hd_1080_i60) )    //FHD
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 15;
                    }
                    else if((arVIS[i] == ver_vis_pal)    || (arVIS[i] == ver_vis_hd_720_25p)  || (arVIS[i] == ver_vis_hd_720_50p))      //PAL
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 25;
                    }
                    else if((arVIS[i] == ver_vis_ntsc)   || (arVIS[i] == ver_vis_hd_720_30p)  || (arVIS[i] == ver_vis_hd_720_60p)  || (arVIS[i] == ver_vis_unknown) )  //NTSC
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 30;
                    }
                    break;
                }
                case 1 : { cfgSetup.rec.record_main.fr_hd[i] =  5;  break; }
                case 2 : { cfgSetup.rec.record_main.fr_hd[i] = 10;  break; }
                case 3 : { cfgSetup.rec.record_main.fr_hd[i] = 15;  break; }
                case 4 :
                {
                    if((arVIS[i] == ver_vis_hd_1080_25p) || (arVIS[i] == ver_vis_hd_1080_30p) || (arVIS[i] == ver_vis_hd_1080_50p) ||
                       (arVIS[i] == ver_vis_hd_1080_60p) || (arVIS[i] == ver_vis_hd_1080_i50) || (arVIS[i] == ver_vis_hd_1080_i60) )    //FHD
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 15;
                    }
                    else
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 20;
                    }
                    break;
                }
                case 5 :
                {
                    if((arVIS[i] == ver_vis_hd_1080_25p) || (arVIS[i] == ver_vis_hd_1080_30p) || (arVIS[i] == ver_vis_hd_1080_50p) ||
                       (arVIS[i] == ver_vis_hd_1080_60p) || (arVIS[i] == ver_vis_hd_1080_i50) || (arVIS[i] == ver_vis_hd_1080_i60) )    //FHD
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 15;
                    }
                    else
                    {
                        cfgSetup.rec.record_main.fr_hd[i] = 25;
                    }
                    break;
                }
                default :
                {
                    qDebug("[ERROR]NormalDialog::onButtonSave FrameRate save error");
                    cfgSetup.rec.record_main.fr_hd[i] = 15;
                    break;
                }
            }
            switch(indexQuality)
            {
                case 0  : { cfgSetup.rec.record_main.quality[i] = QUALITY_ULTRA;       break; }
                case 1  : { cfgSetup.rec.record_main.quality[i] = QUALITY_ECONOMY;     break; }
                case 2  : { cfgSetup.rec.record_main.quality[i] = QUALITY_HIGH;        break; }
                default : { qDebug("[ERROR]NormalDialog::onButtonSave Quality save error");
                            cfgSetup.rec.record_main.quality[i] = QUALITY_ULTRA;       break; }
            }
            switch(indexRecording)
            {
                case 0  : { cfgSetup.rec.record_type[i] = true;    break; }
                case 1  : { cfgSetup.rec.record_type[i] = false;   break; }
                default : { qDebug("[ERROR]NormalDialog::onButtonSave Recording save error");
                            cfgSetup.rec.record_type[i] = true;    break; }
            }
            switch(indexAudio)
            {
                case 0  : { cfgSetup.rec.audio[i] = true;      break; }
                case 1  : { cfgSetup.rec.audio[i] = false;     break; }
                default : { qDebug("[ERROR]NormalDialog::onButtonSave Audio save error");
                            cfgSetup.rec.audio[i] = true;      break; }
            }
        }
    }

    QDialog::accept();
}
int NormalDialog::getMaxFrame(void)
{
    int arVIS[devInfo.videoNum];
    ver_get_vis_list(arVIS);

    //check current maxFrame
    int currentMaxFrame, maxFrame=0;
    for(int i=0;i<devInfo.videoNum;i++)
    {
        if((arVIS[i] == ver_vis_hd_1080_25p) || (arVIS[i] == ver_vis_hd_1080_30p) || (arVIS[i] == ver_vis_hd_1080_50p) ||
           (arVIS[i] == ver_vis_hd_1080_60p) || (arVIS[i] == ver_vis_hd_1080_i50) || (arVIS[i] == ver_vis_hd_1080_i60) )    //FHD
        {
            currentMaxFrame=15;
        }
        else if((arVIS[i] == ver_vis_pal)    || (arVIS[i] == ver_vis_hd_720_25p)  || (arVIS[i] == ver_vis_hd_720_50p))      //PAL
        {
            currentMaxFrame=25;
        }
        else if((arVIS[i] == ver_vis_ntsc)   || (arVIS[i] == ver_vis_hd_720_30p)  || (arVIS[i] == ver_vis_hd_720_60p)  || (arVIS[i] == ver_vis_unknown) )  //NTSC
        {
            currentMaxFrame=30;
        }
        else
        {
            qDebug("[ERROR]NormalDialog::getMaxFrame error");
            currentMaxFrame=15;
        }

        if(currentMaxFrame>maxFrame)
        {
            maxFrame=currentMaxFrame;
        }
    }
    return maxFrame;
}
void NormalDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonChannel->hasFocus())            { buttonDefault->setFocus();      }
            else if(buttonDefault->hasFocus())            { buttonChannel->setFocus();      }
            else if(buttonFrameRate->hasFocus())          { buttonSave->setFocus();         }
            else if(buttonRecording->hasFocus())          { buttonFrameRate->setFocus();    }
            else if(buttonSave->hasFocus())               { buttonRecording->setFocus();    }
            else if(buttonQuality->hasFocus())            { buttonClose->setFocus();        }
            else if(buttonAudio->hasFocus())              { buttonQuality->setFocus();      }
            else if(buttonClose->hasFocus())              { buttonAudio->setFocus();        }

            return;

        case Qt::Key_Down:

                 if(buttonChannel->hasFocus())            { buttonDefault->setFocus();      }
            else if(buttonDefault->hasFocus())            { buttonChannel->setFocus();      }
            else if(buttonFrameRate->hasFocus())          { buttonRecording->setFocus();    }
            else if(buttonRecording->hasFocus())          { buttonSave->setFocus();         }
            else if(buttonSave->hasFocus())               { buttonFrameRate->setFocus();    }
            else if(buttonQuality->hasFocus())            { buttonAudio->setFocus();        }
            else if(buttonAudio->hasFocus())              { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())              { buttonQuality->setFocus();      }

            return;

        case Qt::Key_Left:

                 if(buttonChannel->hasFocus())            { buttonQuality->setFocus();      }
            else if(buttonFrameRate->hasFocus())          { buttonChannel->setFocus();      }
            else if(buttonQuality->hasFocus())            { buttonFrameRate->setFocus();    }
            else if(buttonDefault->hasFocus())            { buttonAudio->setFocus();        }
            else if(buttonRecording->hasFocus())          { buttonDefault->setFocus();      }
            else if(buttonAudio->hasFocus())              { buttonRecording->setFocus();    }
            else if(buttonSave->hasFocus())               { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())              { buttonSave->setFocus();         }

            return;

        case Qt::Key_Right:

                 if(buttonChannel->hasFocus())            { buttonFrameRate->setFocus();    }
            else if(buttonFrameRate->hasFocus())          { buttonQuality->setFocus();      }
            else if(buttonQuality->hasFocus())            { buttonChannel->setFocus();      }
            else if(buttonDefault->hasFocus())            { buttonRecording->setFocus();    }
            else if(buttonRecording->hasFocus())          { buttonAudio->setFocus();        }
            else if(buttonAudio->hasFocus())              { buttonDefault->setFocus();      }
            else if(buttonSave->hasFocus())               { buttonClose->setFocus();        }
            else if(buttonClose->hasFocus())              { buttonSave->setFocus();         }

            return;

        case Qt::Key_Enter:

            break;

        case Qt::Key_Escape:

            reject();

            return;

        default:

            reject();

            return;
    }

    QDialog::keyPressEvent(event);
}
void NormalDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
