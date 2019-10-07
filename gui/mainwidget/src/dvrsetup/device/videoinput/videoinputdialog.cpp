#include <QtGui>
#include "videoinputdialog.h"
#include "videoinputbar.h"
#include "main/mainglobal.h"

VideoInputDialog::VideoInputDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::VideoInputDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        buttonMirror[0] = ui720.buttonMirror1;
        buttonMirror[1] = ui720.buttonMirror2;
        buttonMirror[2] = ui720.buttonMirror3;
        buttonMirror[3] = ui720.buttonMirror4;
        buttonMirror[4] = ui720.buttonMirror5;
        buttonMirror[5] = ui720.buttonMirror6;
        buttonMirror[6] = ui720.buttonMirror7;
        buttonMirror[7] = ui720.buttonMirror8;
        buttonMirror[8] = ui720.buttonMirrorAll;

        buttonFlip[0] = ui720.buttonFlip1;
        buttonFlip[1] = ui720.buttonFlip2;
        buttonFlip[2] = ui720.buttonFlip3;
        buttonFlip[3] = ui720.buttonFlip4;
        buttonFlip[4] = ui720.buttonFlip5;
        buttonFlip[5] = ui720.buttonFlip6;
        buttonFlip[6] = ui720.buttonFlip7;
        buttonFlip[7] = ui720.buttonFlip8;
        buttonFlip[8] = ui720.buttonFlipAll;

        buttonRotate[0] = ui720.buttonRotate1;
        buttonRotate[1] = ui720.buttonRotate2;
        buttonRotate[2] = ui720.buttonRotate3;
        buttonRotate[3] = ui720.buttonRotate4;
        buttonRotate[4] = ui720.buttonRotate5;
        buttonRotate[5] = ui720.buttonRotate6;
        buttonRotate[6] = ui720.buttonRotate7;
        buttonRotate[7] = ui720.buttonRotate8;
        buttonRotate[8] = ui720.buttonRotateAll;

        buttonPreview = ui720.buttonPreview;
        buttonDefault = ui720.buttonDefault;
        buttonSave    = ui720.buttonSave;
        buttonClose   = ui720.buttonClose;

        labelCh[0] = ui720.labelCh1;
        labelCh[1] = ui720.labelCh2;
        labelCh[2] = ui720.labelCh3;
        labelCh[3] = ui720.labelCh4;
        labelCh[4] = ui720.labelCh5;
        labelCh[5] = ui720.labelCh6;
        labelCh[6] = ui720.labelCh7;
        labelCh[7] = ui720.labelCh8;
        labelCh[8] = ui720.labelAll;

        labelMirror[0] = ui720.labelMirror1;
        labelMirror[1] = ui720.labelMirror2;
        labelMirror[2] = ui720.labelMirror3;
        labelMirror[3] = ui720.labelMirror4;
        labelMirror[4] = ui720.labelMirror5;
        labelMirror[5] = ui720.labelMirror6;
        labelMirror[6] = ui720.labelMirror7;
        labelMirror[7] = ui720.labelMirror8;
        labelMirror[8] = ui720.labelMirrorAll;

        labelFlip[0] = ui720.labelFlip1;
        labelFlip[1] = ui720.labelFlip2;
        labelFlip[2] = ui720.labelFlip3;
        labelFlip[3] = ui720.labelFlip4;
        labelFlip[4] = ui720.labelFlip5;
        labelFlip[5] = ui720.labelFlip6;
        labelFlip[6] = ui720.labelFlip7;
        labelFlip[7] = ui720.labelFlip8;
        labelFlip[8] = ui720.labelFlipAll;

        labelRotate[0] = ui720.labelRotate1;
        labelRotate[1] = ui720.labelRotate2;
        labelRotate[2] = ui720.labelRotate3;
        labelRotate[3] = ui720.labelRotate4;
        labelRotate[4] = ui720.labelRotate5;
        labelRotate[5] = ui720.labelRotate6;
        labelRotate[6] = ui720.labelRotate7;
        labelRotate[7] = ui720.labelRotate8;
        labelRotate[8] = ui720.labelRotateAll;

        for(int i=0; i<=NUMOFCH; i++)
        {
            labelCh[i]     ->setStyleSheet("font:40px;");
            buttonMirror[i]->setStyleSheet("font:40px;");
            buttonFlip[i]  ->setStyleSheet("font:40px;");
            buttonRotate[i]->setStyleSheet("font:40px;");

            labelMirror[i] ->setStyleSheet("background-color:rgb(50,57,83);");
            labelFlip[i]   ->setStyleSheet("background-color:rgb(50,57,83);");
            labelRotate[i] ->setStyleSheet("background-color:rgb(50,57,83);");
        }

        buttonMirror[NUMOFCH]->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonFlip[NUMOFCH]  ->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRotate[NUMOFCH]->setStyleSheet("QPushButton{font:40px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");

        labelCh[NUMOFCH]     ->setStyleSheet("font:40px; background-color:rgb(06,86,159);");
        labelMirror[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");
        labelFlip[NUMOFCH]   ->setStyleSheet("background-color:rgb(06,86,159);");
        labelRotate[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");

        if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonPreview->resize(270,91);
            buttonDefault->setGeometry(15+270+10, 570, 270, 90);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonPreview->resize(300,91);
            buttonDefault->setGeometry(15+300+10, 570, 300, 90);
        }
    }
    else
    {
        Ui::VideoInputDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        buttonMirror[0] = ui1080.buttonMirror1;
        buttonMirror[1] = ui1080.buttonMirror2;
        buttonMirror[2] = ui1080.buttonMirror3;
        buttonMirror[3] = ui1080.buttonMirror4;
        buttonMirror[4] = ui1080.buttonMirror5;
        buttonMirror[5] = ui1080.buttonMirror6;
        buttonMirror[6] = ui1080.buttonMirror7;
        buttonMirror[7] = ui1080.buttonMirror8;
        buttonMirror[8] = ui1080.buttonMirrorAll;

        buttonFlip[0] = ui1080.buttonFlip1;
        buttonFlip[1] = ui1080.buttonFlip2;
        buttonFlip[2] = ui1080.buttonFlip3;
        buttonFlip[3] = ui1080.buttonFlip4;
        buttonFlip[4] = ui1080.buttonFlip5;
        buttonFlip[5] = ui1080.buttonFlip6;
        buttonFlip[6] = ui1080.buttonFlip7;
        buttonFlip[7] = ui1080.buttonFlip8;
        buttonFlip[8] = ui1080.buttonFlipAll;

        buttonRotate[0] = ui1080.buttonRotate1;
        buttonRotate[1] = ui1080.buttonRotate2;
        buttonRotate[2] = ui1080.buttonRotate3;
        buttonRotate[3] = ui1080.buttonRotate4;
        buttonRotate[4] = ui1080.buttonRotate5;
        buttonRotate[5] = ui1080.buttonRotate6;
        buttonRotate[6] = ui1080.buttonRotate7;
        buttonRotate[7] = ui1080.buttonRotate8;
        buttonRotate[8] = ui1080.buttonRotateAll;

        buttonPreview = ui1080.buttonPreview;
        buttonDefault = ui1080.buttonDefault;
        buttonSave    = ui1080.buttonSave;
        buttonClose   = ui1080.buttonClose;

        labelCh[0] = ui1080.labelCh1;
        labelCh[1] = ui1080.labelCh2;
        labelCh[2] = ui1080.labelCh3;
        labelCh[3] = ui1080.labelCh4;
        labelCh[4] = ui1080.labelCh5;
        labelCh[5] = ui1080.labelCh6;
        labelCh[6] = ui1080.labelCh7;
        labelCh[7] = ui1080.labelCh8;
        labelCh[8] = ui1080.labelAll;

        labelMirror[0] = ui1080.labelMirror1;
        labelMirror[1] = ui1080.labelMirror2;
        labelMirror[2] = ui1080.labelMirror3;
        labelMirror[3] = ui1080.labelMirror4;
        labelMirror[4] = ui1080.labelMirror5;
        labelMirror[5] = ui1080.labelMirror6;
        labelMirror[6] = ui1080.labelMirror7;
        labelMirror[7] = ui1080.labelMirror8;
        labelMirror[8] = ui1080.labelMirrorAll;

        labelFlip[0] = ui1080.labelFlip1;
        labelFlip[1] = ui1080.labelFlip2;
        labelFlip[2] = ui1080.labelFlip3;
        labelFlip[3] = ui1080.labelFlip4;
        labelFlip[4] = ui1080.labelFlip5;
        labelFlip[5] = ui1080.labelFlip6;
        labelFlip[6] = ui1080.labelFlip7;
        labelFlip[7] = ui1080.labelFlip8;
        labelFlip[8] = ui1080.labelFlipAll;

        labelRotate[0] = ui1080.labelRotate1;
        labelRotate[1] = ui1080.labelRotate2;
        labelRotate[2] = ui1080.labelRotate3;
        labelRotate[3] = ui1080.labelRotate4;
        labelRotate[4] = ui1080.labelRotate5;
        labelRotate[5] = ui1080.labelRotate6;
        labelRotate[6] = ui1080.labelRotate7;
        labelRotate[7] = ui1080.labelRotate8;
        labelRotate[8] = ui1080.labelRotateAll;

        for(int i=0; i<=NUMOFCH; i++)
        {
            labelCh[i]     ->setStyleSheet("font:60px;");
            buttonMirror[i]->setStyleSheet("font:60px;");
            buttonFlip[i]  ->setStyleSheet("font:60px");
            buttonRotate[i]->setStyleSheet("font:60px;");

            labelMirror[i] ->setStyleSheet("background-color:rgb(50,57,83);");
            labelFlip[i]   ->setStyleSheet("background-color:rgb(50,57,83);");
            labelRotate[i] ->setStyleSheet("background-color:rgb(50,57,83);");
        }

        buttonMirror[NUMOFCH]->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonFlip[NUMOFCH]  ->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");
        buttonRotate[NUMOFCH]->setStyleSheet("QPushButton{font:60px; background-color:rgb(06,86,159);} QPushButton:focus{background-color:rgb(152,14,69);}");

        labelCh[NUMOFCH]     ->setStyleSheet("font:60px; background-color:rgb(06,86,159);");
        labelMirror[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");
        labelFlip[NUMOFCH]   ->setStyleSheet("background-color:rgb(06,86,159);");
        labelRotate[NUMOFCH] ->setStyleSheet("background-color:rgb(06,86,159);");

        if( utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
        {
            buttonPreview->resize(380,131);
            buttonDefault->setGeometry(25+380+20, 860, 390, 130);
        }
        else if( utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            buttonPreview->resize(420,131);
            buttonDefault->setGeometry(25+420+20, 860, 400, 130);
        }
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    connect(buttonMirror[0], SIGNAL(clicked()), this, SLOT(onButtonMirror1()));
    connect(buttonMirror[1], SIGNAL(clicked()), this, SLOT(onButtonMirror2()));
    connect(buttonMirror[2], SIGNAL(clicked()), this, SLOT(onButtonMirror3()));
    connect(buttonMirror[3], SIGNAL(clicked()), this, SLOT(onButtonMirror4()));
    connect(buttonMirror[4], SIGNAL(clicked()), this, SLOT(onButtonMirror5()));
    connect(buttonMirror[5], SIGNAL(clicked()), this, SLOT(onButtonMirror6()));
    connect(buttonMirror[6], SIGNAL(clicked()), this, SLOT(onButtonMirror7()));
    connect(buttonMirror[7], SIGNAL(clicked()), this, SLOT(onButtonMirror8()));
    connect(buttonMirror[8], SIGNAL(clicked()), this, SLOT(onButtonMirrorAll()));

    connect(buttonFlip[0],   SIGNAL(clicked()), this, SLOT(onButtonFlip1()));
    connect(buttonFlip[1],   SIGNAL(clicked()), this, SLOT(onButtonFlip2()));
    connect(buttonFlip[2],   SIGNAL(clicked()), this, SLOT(onButtonFlip3()));
    connect(buttonFlip[3],   SIGNAL(clicked()), this, SLOT(onButtonFlip4()));
    connect(buttonFlip[4],   SIGNAL(clicked()), this, SLOT(onButtonFlip5()));
    connect(buttonFlip[5],   SIGNAL(clicked()), this, SLOT(onButtonFlip6()));
    connect(buttonFlip[6],   SIGNAL(clicked()), this, SLOT(onButtonFlip7()));
    connect(buttonFlip[7],   SIGNAL(clicked()), this, SLOT(onButtonFlip8()));
    connect(buttonFlip[8],   SIGNAL(clicked()), this, SLOT(onButtonFlipAll()));

    connect(buttonRotate[0], SIGNAL(clicked()), this, SLOT(onButtonRotate1()));
    connect(buttonRotate[1], SIGNAL(clicked()), this, SLOT(onButtonRotate2()));
    connect(buttonRotate[2], SIGNAL(clicked()), this, SLOT(onButtonRotate3()));
    connect(buttonRotate[3], SIGNAL(clicked()), this, SLOT(onButtonRotate4()));
    connect(buttonRotate[4], SIGNAL(clicked()), this, SLOT(onButtonRotate5()));
    connect(buttonRotate[5], SIGNAL(clicked()), this, SLOT(onButtonRotate6()));
    connect(buttonRotate[6], SIGNAL(clicked()), this, SLOT(onButtonRotate7()));
    connect(buttonRotate[7], SIGNAL(clicked()), this, SLOT(onButtonRotate8()));
    connect(buttonRotate[8], SIGNAL(clicked()), this, SLOT(onButtonRotateAll()));

    connect(buttonPreview,   SIGNAL(released()),this, SLOT(onButtonPreview()));
    connect(buttonDefault,   SIGNAL(released()),this, SLOT(onButtonDefault()));
    connect(buttonSave,      SIGNAL(released()),this, SLOT(onButtonSave()));
    connect(buttonClose,     SIGNAL(released()),this, SLOT(onButtonClose()));

    videoInputBar=NULL;
}
VideoInputDialog::~VideoInputDialog()
{
}

void VideoInputDialog::initVideoInputConfig(void)
{
    QString mirror[NUMOFCH];
    mirror[0] = QString(DeviceCfg.camera_mirror00);
    mirror[1] = QString(DeviceCfg.camera_mirror01);
    mirror[2] = QString(DeviceCfg.camera_mirror02);
    mirror[3] = QString(DeviceCfg.camera_mirror03);
    mirror[4] = QString(DeviceCfg.camera_mirror04);
    mirror[5] = QString(DeviceCfg.camera_mirror05);
    mirror[6] = QString(DeviceCfg.camera_mirror06);
    mirror[7] = QString(DeviceCfg.camera_mirror07);

    for(int i=0; i<NUMOFCH; i++)
    {
        if(mirror[i].compare("MIRROR")==0)  { infoMirror[i] = 1; }
        else                                { infoMirror[i] = 0; }
    }

    QString flip[NUMOFCH];
    flip[0] = QString(DeviceCfg.camera_flip00);
    flip[1] = QString(DeviceCfg.camera_flip01);
    flip[2] = QString(DeviceCfg.camera_flip02);
    flip[3] = QString(DeviceCfg.camera_flip03);
    flip[4] = QString(DeviceCfg.camera_flip04);
    flip[5] = QString(DeviceCfg.camera_flip05);
    flip[6] = QString(DeviceCfg.camera_flip06);
    flip[7] = QString(DeviceCfg.camera_flip07);

    for(int i=0; i<NUMOFCH; i++)
    {
        if(flip[i].compare("DOWN")==0)      { infoFlip[i] = 1; }
        else                                { infoFlip[i] = 0; }
    }

    infoRotate[0] = atoi(DeviceCfg.camera_rotate00);
    infoRotate[1] = atoi(DeviceCfg.camera_rotate01);
    infoRotate[2] = atoi(DeviceCfg.camera_rotate02);
    infoRotate[3] = atoi(DeviceCfg.camera_rotate03);
    infoRotate[4] = atoi(DeviceCfg.camera_rotate04);
    infoRotate[5] = atoi(DeviceCfg.camera_rotate05);
    infoRotate[6] = atoi(DeviceCfg.camera_rotate06);
    infoRotate[7] = atoi(DeviceCfg.camera_rotate07);

    //backup config for preview
    for(int i=0; i<NUMOFCH; i++)
    {
        backupMirror[i] = infoMirror[i];
        backupFlip[i]   = infoFlip[i];
        backupRotate[i] = infoRotate[i];
    }

    buttonMirror[8]->setFocus();
    updateButton();
}
void VideoInputDialog::updateButton()
{
    for(int i=0; i<NUMOFCH; i++)
    {
        if( infoMirror[i] == 1 )            { buttonMirror[i]->setText(tr("Mirror"));  }
        else                                { buttonMirror[i]->setText(tr("Normal")); }

        if( infoFlip[i] == 1 )              { buttonFlip[i]->setText(tr("Down"));    }
        else                                { buttonFlip[i]->setText(tr("Up"));   }

        buttonRotate[i]->setText(QString("%1%2").arg(QString::number(infoRotate[i]), tr("°")));
    }
}
void VideoInputDialog::onButtonMirror(int ch)
{
    if( infoMirror[ch]==0 )                 { infoMirror[ch]=1; }
    else                                    { infoMirror[ch]=0; }

    updateButton();
}
void VideoInputDialog::onButtonMirror1()    { onButtonMirror(0); }
void VideoInputDialog::onButtonMirror2()    { onButtonMirror(1); }
void VideoInputDialog::onButtonMirror3()    { onButtonMirror(2); }
void VideoInputDialog::onButtonMirror4()    { onButtonMirror(3); }
void VideoInputDialog::onButtonMirror5()    { onButtonMirror(4); }
void VideoInputDialog::onButtonMirror6()    { onButtonMirror(5); }
void VideoInputDialog::onButtonMirror7()    { onButtonMirror(6); }
void VideoInputDialog::onButtonMirror8()    { onButtonMirror(7); }
void VideoInputDialog::onButtonMirrorAll()
{
    int count = 0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoMirror[ch] == 0 )           { count++; }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( count >= NUMOFCH )              { infoMirror[ch] = 1; }
        else                                { infoMirror[ch] = 0; }
    }

    updateButton();
}
void VideoInputDialog::onButtonFlip(int ch)
{
     if( infoFlip[ch] == 0 )                { infoFlip[ch] = 1; }
     else                                   { infoFlip[ch] = 0; }

     updateButton();
}
void VideoInputDialog::onButtonFlip1()      { onButtonFlip(0); }
void VideoInputDialog::onButtonFlip2()      { onButtonFlip(1); }
void VideoInputDialog::onButtonFlip3()      { onButtonFlip(2); }
void VideoInputDialog::onButtonFlip4()      { onButtonFlip(3); }
void VideoInputDialog::onButtonFlip5()      { onButtonFlip(4); }
void VideoInputDialog::onButtonFlip6()      { onButtonFlip(5); }
void VideoInputDialog::onButtonFlip7()      { onButtonFlip(6); }
void VideoInputDialog::onButtonFlip8()      { onButtonFlip(7); }
void VideoInputDialog::onButtonFlipAll()
{
    int count = 0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoFlip[ch] == 0 )             { count++; }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( count >= NUMOFCH )              { infoFlip[ch] = 1; }
        else                                { infoFlip[ch] = 0; }
    }

    updateButton();
}
void VideoInputDialog::onButtonRotate(int ch)
{
    if( infoRotate[ch]>=270 )   { infoRotate[ch]=0; }
    else                        { infoRotate[ch]+=90; }

    updateButton();
}

void VideoInputDialog::onButtonRotate1()    { onButtonRotate(0); }
void VideoInputDialog::onButtonRotate2()    { onButtonRotate(1); }
void VideoInputDialog::onButtonRotate3()    { onButtonRotate(2); }
void VideoInputDialog::onButtonRotate4()    { onButtonRotate(3); }
void VideoInputDialog::onButtonRotate5()    { onButtonRotate(4); }
void VideoInputDialog::onButtonRotate6()    { onButtonRotate(5); }
void VideoInputDialog::onButtonRotate7()    { onButtonRotate(6); }
void VideoInputDialog::onButtonRotate8()    { onButtonRotate(7); }
void VideoInputDialog::onButtonRotateAll()
{
    int count = 0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoRotate[ch] == infoRotate[0] )   { count++; }
    }

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( count < NUMOFCH )               { infoRotate[ch] = 0; }
        else
        {
            if( infoRotate[ch]>=270 )       { infoRotate[ch] = 0; }
            else                            { infoRotate[ch] += 90; }
        }
    }

    updateButton();
}
void VideoInputDialog::onButtonPreview()
{
    emit makeTransparent(1);
    this->setWindowOpacity(0);

    if( !videoInputBar )
    {
        videoInputBar = new VideoInputBar(this);
        connect( videoInputBar, SIGNAL(videoInputPreview()), this, SLOT(onVideoInputPreview()));
    }
    else
    {
        videoInputBar->setWindowOpacity(1);
    }

    videoInputBar->setInfo(infoMirror, infoFlip, infoRotate);
    videoInputBar->move( (mainWidth-(videoInputBar->width()))/2, mainHeight-(videoInputBar->height()) );

    if( videoInputBar->exec() )
    {
        videoInputBar->setWindowOpacity(0);
        emit makeTransparent(0);
        this->setWindowOpacity(1);

        videoInputBar->getInfo(infoMirror, infoFlip, infoRotate);
        updateButton();
    }
}
void VideoInputDialog::onVideoInputPreview()
{
    emit videoInputPreview();
}
void VideoInputDialog::onButtonDefault()
{
    for(int i=0; i<NUMOFCH; i++)
    {
        infoMirror[i] = 0;
        infoFlip[i] = 0;
        infoRotate[i] = 0;
    }

    updateButton();
}
#if 0   //yjsin save DeviceCfg for emd-s10
void VideoInputDialog::onButtonSave()
{
    if( videoInputBar )
    {
        delete videoInputBar;
        videoInputBar=NULL;
    }

    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst = NULL;

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_mirror00; break; }
            case 1 :    { dst = DeviceCfg.camera_mirror01; break; }
            case 2 :    { dst = DeviceCfg.camera_mirror02; break; }
            case 3 :    { dst = DeviceCfg.camera_mirror03; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( infoMirror[i] == 1 )    { utils_cfg_cpy_item(dst, "MIRROR"); }
            else                        { utils_cfg_cpy_item(dst, "NORMAL"); }
        }

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_flip00; break; }
            case 1 :    { dst = DeviceCfg.camera_flip01; break; }
            case 2 :    { dst = DeviceCfg.camera_flip02; break; }
            case 3 :    { dst = DeviceCfg.camera_flip03; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( infoFlip[i] == 1 )      { utils_cfg_cpy_item(dst, "DOWN"); }
            else                        { utils_cfg_cpy_item(dst, "UP");   }
        }
    }

    emit makeTransparent(0);
    emit accept();
}
void VideoInputDialog::onButtonClose()
{
    if( videoInputBar )
    {
        delete videoInputBar;
        videoInputBar = NULL;
    }

    //save backup Config
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst = NULL;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_mirror00; break; }
            case 1 :    { dst = DeviceCfg.camera_mirror01; break; }
            case 2 :    { dst = DeviceCfg.camera_mirror02; break; }
            case 3 :    { dst = DeviceCfg.camera_mirror03; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( backupMirror[i] == 1 )  { utils_cfg_cpy_item(dst, "MIRROR"); }
            else                        { utils_cfg_cpy_item(dst, "NORMAL"); }
        }

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_flip00; break; }
            case 1 :    { dst = DeviceCfg.camera_flip01; break; }
            case 2 :    { dst = DeviceCfg.camera_flip02; break; }
            case 3 :    { dst = DeviceCfg.camera_flip03; break; }
            default :   { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( backupFlip[i] == 1 )    { utils_cfg_cpy_item(dst, "DOWN"); }
            else                        { utils_cfg_cpy_item(dst, "UP");   }
        }
    }

    emit makeTransparent(0);
    emit reject();
}
#else   //yjsin save DeviceCfg for emd-s20
void VideoInputDialog::onButtonSave()
{
    if( videoInputBar )
    {
        delete videoInputBar;
        videoInputBar=NULL;
    }

    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst = NULL;

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_mirror00; break; }
            case 1 :    { dst = DeviceCfg.camera_mirror01; break; }
            case 2 :    { dst = DeviceCfg.camera_mirror02; break; }
            case 3 :    { dst = DeviceCfg.camera_mirror03; break; }
            case 4 :    { dst = DeviceCfg.camera_mirror04; break; }
            case 5 :    { dst = DeviceCfg.camera_mirror05; break; }
            case 6 :    { dst = DeviceCfg.camera_mirror06; break; }
            case 7 :    { dst = DeviceCfg.camera_mirror07; break; }
            default:    { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( infoMirror[i] == 1 )    { utils_cfg_cpy_item(dst, "MIRROR"); }
            else                        { utils_cfg_cpy_item(dst, "NORMAL"); }
        }

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_flip00; break; }
            case 1 :    { dst = DeviceCfg.camera_flip01; break; }
            case 2 :    { dst = DeviceCfg.camera_flip02; break; }
            case 3 :    { dst = DeviceCfg.camera_flip03; break; }
            case 4 :    { dst = DeviceCfg.camera_flip04; break; }
            case 5 :    { dst = DeviceCfg.camera_flip05; break; }
            case 6 :    { dst = DeviceCfg.camera_flip06; break; }
            case 7 :    { dst = DeviceCfg.camera_flip07; break; }
            default:    { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( infoFlip[i] == 1 )      { utils_cfg_cpy_item(dst, "DOWN"); }
            else                        { utils_cfg_cpy_item(dst, "UP");   }
        }

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_rotate00; break; }
            case 1 :    { dst = DeviceCfg.camera_rotate01; break; }
            case 2 :    { dst = DeviceCfg.camera_rotate02; break; }
            case 3 :    { dst = DeviceCfg.camera_rotate03; break; }
            case 4 :    { dst = DeviceCfg.camera_rotate04; break; }
            case 5 :    { dst = DeviceCfg.camera_rotate05; break; }
            case 6 :    { dst = DeviceCfg.camera_rotate06; break; }
            case 7 :    { dst = DeviceCfg.camera_rotate07; break; }
            default:    { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            sprintf(dst, "%d", infoRotate[i]);
        }
    }

    emit makeTransparent(0);
    emit accept();
}
void VideoInputDialog::onButtonClose()
{
    if( videoInputBar )
    {
        delete videoInputBar;
        videoInputBar = NULL;
    }

    //save backup Config
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst = NULL;
        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_mirror00; break; }
            case 1 :    { dst = DeviceCfg.camera_mirror01; break; }
            case 2 :    { dst = DeviceCfg.camera_mirror02; break; }
            case 3 :    { dst = DeviceCfg.camera_mirror03; break; }
            case 4 :    { dst = DeviceCfg.camera_mirror04; break; }
            case 5 :    { dst = DeviceCfg.camera_mirror05; break; }
            case 6 :    { dst = DeviceCfg.camera_mirror06; break; }
            case 7 :    { dst = DeviceCfg.camera_mirror07; break; }
            default:    { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( backupMirror[i] == 1 )  { utils_cfg_cpy_item(dst, "MIRROR"); }
            else                        { utils_cfg_cpy_item(dst, "NORMAL"); }
        }

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_flip00; break; }
            case 1 :    { dst = DeviceCfg.camera_flip01; break; }
            case 2 :    { dst = DeviceCfg.camera_flip02; break; }
            case 3 :    { dst = DeviceCfg.camera_flip03; break; }
            case 4 :    { dst = DeviceCfg.camera_flip04; break; }
            case 5 :    { dst = DeviceCfg.camera_flip05; break; }
            case 6 :    { dst = DeviceCfg.camera_flip06; break; }
            case 7 :    { dst = DeviceCfg.camera_flip07; break; }
            default:    { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            if( backupFlip[i] == 1 )    { utils_cfg_cpy_item(dst, "DOWN"); }
            else                        { utils_cfg_cpy_item(dst, "UP");   }
        }

        switch(i)
        {
            case 0 :    { dst = DeviceCfg.camera_rotate00; break; }
            case 1 :    { dst = DeviceCfg.camera_rotate01; break; }
            case 2 :    { dst = DeviceCfg.camera_rotate02; break; }
            case 3 :    { dst = DeviceCfg.camera_rotate03; break; }
            case 4 :    { dst = DeviceCfg.camera_rotate04; break; }
            case 5 :    { dst = DeviceCfg.camera_rotate05; break; }
            case 6 :    { dst = DeviceCfg.camera_rotate06; break; }
            case 7 :    { dst = DeviceCfg.camera_rotate07; break; }
            default:    { dst = NULL; }
        }

        if( dst == NULL )
        {
            qDebug("[Error] %s, DeviceCfg struct member does not exist.", __func__ );
        }
        else
        {
            sprintf(dst, "%d", backupFlip[i]);
        }
    }

    emit makeTransparent(0);
    emit reject();
}
#endif
void VideoInputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

            if     ( buttonMirror[8]->hasFocus() )  { buttonPreview  ->setFocus(); }
            else if( buttonMirror[0]->hasFocus() )  { buttonMirror[8]->setFocus(); }
            else if( buttonMirror[1]->hasFocus() )  { buttonMirror[0]->setFocus(); }
            else if( buttonMirror[2]->hasFocus() )  { buttonMirror[1]->setFocus(); }
            else if( buttonMirror[3]->hasFocus() )  { buttonMirror[2]->setFocus(); }
            else if( buttonMirror[4]->hasFocus() )  { buttonMirror[3]->setFocus(); }
            else if( buttonMirror[5]->hasFocus() )  { buttonMirror[4]->setFocus(); }
            else if( buttonMirror[6]->hasFocus() )  { buttonMirror[5]->setFocus(); }
            else if( buttonMirror[7]->hasFocus() )  { buttonMirror[6]->setFocus(); }

            else if( buttonFlip[8]  ->hasFocus() )  { buttonSave     ->setFocus(); }
            else if( buttonFlip[0]  ->hasFocus() )  { buttonFlip[8]  ->setFocus(); }
            else if( buttonFlip[1]  ->hasFocus() )  { buttonFlip[0]  ->setFocus(); }
            else if( buttonFlip[2]  ->hasFocus() )  { buttonFlip[1]  ->setFocus(); }
            else if( buttonFlip[3]  ->hasFocus() )  { buttonFlip[2]  ->setFocus(); }
            else if( buttonFlip[4]  ->hasFocus() )  { buttonFlip[3]  ->setFocus(); }
            else if( buttonFlip[5]  ->hasFocus() )  { buttonFlip[4]  ->setFocus(); }
            else if( buttonFlip[6]  ->hasFocus() )  { buttonFlip[5]  ->setFocus(); }
            else if( buttonFlip[7]  ->hasFocus() )  { buttonFlip[6]  ->setFocus(); }

            else if( buttonRotate[8]->hasFocus() )  { buttonClose    ->setFocus(); }
            else if( buttonRotate[0]->hasFocus() )  { buttonRotate[8]->setFocus(); }
            else if( buttonRotate[1]->hasFocus() )  { buttonRotate[0]->setFocus(); }
            else if( buttonRotate[2]->hasFocus() )  { buttonRotate[1]->setFocus(); }
            else if( buttonRotate[3]->hasFocus() )  { buttonRotate[2]->setFocus(); }
            else if( buttonRotate[4]->hasFocus() )  { buttonRotate[3]->setFocus(); }
            else if( buttonRotate[5]->hasFocus() )  { buttonRotate[4]->setFocus(); }
            else if( buttonRotate[6]->hasFocus() )  { buttonRotate[5]->setFocus(); }
            else if( buttonRotate[7]->hasFocus() )  { buttonRotate[6]->setFocus(); }

            else if( buttonPreview  ->hasFocus() )  { buttonMirror[7]->setFocus(); }
            else if( buttonSave     ->hasFocus() )  { buttonFlip[7]  ->setFocus(); }
            else if( buttonClose    ->hasFocus() )  { buttonRotate[7]->setFocus(); }

            break;

        case Qt::Key_Down:

            if     ( buttonMirror[8]->hasFocus() )  { buttonMirror[0]->setFocus(); }
            else if( buttonMirror[0]->hasFocus() )  { buttonMirror[1]->setFocus(); }
            else if( buttonMirror[1]->hasFocus() )  { buttonMirror[2]->setFocus(); }
            else if( buttonMirror[2]->hasFocus() )  { buttonMirror[3]->setFocus(); }
            else if( buttonMirror[3]->hasFocus() )  { buttonMirror[4]->setFocus(); }
            else if( buttonMirror[4]->hasFocus() )  { buttonMirror[5]->setFocus(); }
            else if( buttonMirror[5]->hasFocus() )  { buttonMirror[6]->setFocus(); }
            else if( buttonMirror[6]->hasFocus() )  { buttonMirror[7]->setFocus(); }
            else if( buttonMirror[7]->hasFocus() )  { buttonPreview  ->setFocus(); }

            else if( buttonFlip[8]  ->hasFocus() )  { buttonFlip[0]  ->setFocus(); }
            else if( buttonFlip[0]  ->hasFocus() )  { buttonFlip[1]  ->setFocus(); }
            else if( buttonFlip[1]  ->hasFocus() )  { buttonFlip[2]  ->setFocus(); }
            else if( buttonFlip[2]  ->hasFocus() )  { buttonFlip[3]  ->setFocus(); }
            else if( buttonFlip[3]  ->hasFocus() )  { buttonFlip[4]  ->setFocus(); }
            else if( buttonFlip[4]  ->hasFocus() )  { buttonFlip[5]  ->setFocus(); }
            else if( buttonFlip[5]  ->hasFocus() )  { buttonFlip[6]  ->setFocus(); }
            else if( buttonFlip[6]  ->hasFocus() )  { buttonFlip[7]  ->setFocus(); }
            else if( buttonFlip[7]  ->hasFocus() )  { buttonSave     ->setFocus(); }

            else if( buttonRotate[8]->hasFocus() )  { buttonRotate[0]->setFocus(); }
            else if( buttonRotate[0]->hasFocus() )  { buttonRotate[1]->setFocus(); }
            else if( buttonRotate[1]->hasFocus() )  { buttonRotate[2]->setFocus(); }
            else if( buttonRotate[2]->hasFocus() )  { buttonRotate[3]->setFocus(); }
            else if( buttonRotate[3]->hasFocus() )  { buttonRotate[4]->setFocus(); }
            else if( buttonRotate[4]->hasFocus() )  { buttonRotate[5]->setFocus(); }
            else if( buttonRotate[5]->hasFocus() )  { buttonRotate[6]->setFocus(); }
            else if( buttonRotate[6]->hasFocus() )  { buttonRotate[7]->setFocus(); }
            else if( buttonRotate[7]->hasFocus() )  { buttonClose    ->setFocus(); }

            else if( buttonPreview  ->hasFocus() )  { buttonMirror[8]->setFocus(); }
            else if( buttonSave     ->hasFocus() )  { buttonFlip[8]  ->setFocus(); }
            else if( buttonClose    ->hasFocus() )  { buttonRotate[8]->setFocus(); }

            break;

        case Qt::Key_Left:

            if     ( buttonMirror[8]->hasFocus() )  { buttonRotate[8]->setFocus(); }
            else if( buttonMirror[0]->hasFocus() )  { buttonRotate[0]->setFocus(); }
            else if( buttonMirror[1]->hasFocus() )  { buttonRotate[1]->setFocus(); }
            else if( buttonMirror[2]->hasFocus() )  { buttonRotate[2]->setFocus(); }
            else if( buttonMirror[3]->hasFocus() )  { buttonRotate[3]->setFocus(); }
            else if( buttonMirror[4]->hasFocus() )  { buttonRotate[4]->setFocus(); }
            else if( buttonMirror[5]->hasFocus() )  { buttonRotate[5]->setFocus(); }
            else if( buttonMirror[6]->hasFocus() )  { buttonRotate[6]->setFocus(); }
            else if( buttonMirror[7]->hasFocus() )  { buttonRotate[7]->setFocus(); }

            else if( buttonFlip[8]  ->hasFocus() )  { buttonMirror[8]->setFocus(); }
            else if( buttonFlip[0]  ->hasFocus() )  { buttonMirror[0]->setFocus(); }
            else if( buttonFlip[1]  ->hasFocus() )  { buttonMirror[1]->setFocus(); }
            else if( buttonFlip[2]  ->hasFocus() )  { buttonMirror[2]->setFocus(); }
            else if( buttonFlip[3]  ->hasFocus() )  { buttonMirror[3]->setFocus(); }
            else if( buttonFlip[4]  ->hasFocus() )  { buttonMirror[4]->setFocus(); }
            else if( buttonFlip[5]  ->hasFocus() )  { buttonMirror[5]->setFocus(); }
            else if( buttonFlip[6]  ->hasFocus() )  { buttonMirror[6]->setFocus(); }
            else if( buttonFlip[7]  ->hasFocus() )  { buttonMirror[7]->setFocus(); }

            else if( buttonRotate[8]->hasFocus() )  { buttonFlip[8]  ->setFocus(); }
            else if( buttonRotate[0]->hasFocus() )  { buttonFlip[0]  ->setFocus(); }
            else if( buttonRotate[1]->hasFocus() )  { buttonFlip[1]  ->setFocus(); }
            else if( buttonRotate[2]->hasFocus() )  { buttonFlip[2]  ->setFocus(); }
            else if( buttonRotate[3]->hasFocus() )  { buttonFlip[3]  ->setFocus(); }
            else if( buttonRotate[4]->hasFocus() )  { buttonFlip[4]  ->setFocus(); }
            else if( buttonRotate[5]->hasFocus() )  { buttonFlip[5]  ->setFocus(); }
            else if( buttonRotate[6]->hasFocus() )  { buttonFlip[6]  ->setFocus(); }
            else if( buttonRotate[7]->hasFocus() )  { buttonFlip[7]  ->setFocus(); }

            else if( buttonPreview  ->hasFocus() )  { buttonClose    ->setFocus(); }
            else if( buttonSave     ->hasFocus() )  { buttonPreview  ->setFocus(); }
            else if( buttonClose    ->hasFocus() )  { buttonSave     ->setFocus(); }

            break;;

        case Qt::Key_Right:

            if     ( buttonMirror[8]->hasFocus() )  { buttonFlip[8]  ->setFocus(); }
            else if( buttonMirror[0]->hasFocus() )  { buttonFlip[0]  ->setFocus(); }
            else if( buttonMirror[1]->hasFocus() )  { buttonFlip[1]  ->setFocus(); }
            else if( buttonMirror[2]->hasFocus() )  { buttonFlip[2]  ->setFocus(); }
            else if( buttonMirror[3]->hasFocus() )  { buttonFlip[3]  ->setFocus(); }
            else if( buttonMirror[4]->hasFocus() )  { buttonFlip[4]  ->setFocus(); }
            else if( buttonMirror[5]->hasFocus() )  { buttonFlip[5]  ->setFocus(); }
            else if( buttonMirror[6]->hasFocus() )  { buttonFlip[6]  ->setFocus(); }
            else if( buttonMirror[7]->hasFocus() )  { buttonFlip[7]  ->setFocus(); }

            else if( buttonFlip[8]  ->hasFocus() )  { buttonRotate[8]->setFocus(); }
            else if( buttonFlip[0]  ->hasFocus() )  { buttonRotate[0]->setFocus(); }
            else if( buttonFlip[1]  ->hasFocus() )  { buttonRotate[1]->setFocus(); }
            else if( buttonFlip[2]  ->hasFocus() )  { buttonRotate[2]->setFocus(); }
            else if( buttonFlip[3]  ->hasFocus() )  { buttonRotate[3]->setFocus(); }
            else if( buttonFlip[4]  ->hasFocus() )  { buttonRotate[4]->setFocus(); }
            else if( buttonFlip[5]  ->hasFocus() )  { buttonRotate[5]->setFocus(); }
            else if( buttonFlip[6]  ->hasFocus() )  { buttonRotate[6]->setFocus(); }
            else if( buttonFlip[7]  ->hasFocus() )  { buttonRotate[7]->setFocus(); }

            else if( buttonRotate[8]->hasFocus() )  { buttonMirror[8]->setFocus(); }
            else if( buttonRotate[0]->hasFocus() )  { buttonMirror[0]->setFocus(); }
            else if( buttonRotate[1]->hasFocus() )  { buttonMirror[1]->setFocus(); }
            else if( buttonRotate[2]->hasFocus() )  { buttonMirror[2]->setFocus(); }
            else if( buttonRotate[3]->hasFocus() )  { buttonMirror[3]->setFocus(); }
            else if( buttonRotate[4]->hasFocus() )  { buttonMirror[4]->setFocus(); }
            else if( buttonRotate[5]->hasFocus() )  { buttonMirror[5]->setFocus(); }
            else if( buttonRotate[6]->hasFocus() )  { buttonMirror[6]->setFocus(); }
            else if( buttonRotate[7]->hasFocus() )  { buttonMirror[7]->setFocus(); }

            else if( buttonPreview  ->hasFocus() )  { buttonSave     ->setFocus(); }
            else if( buttonSave     ->hasFocus() )  { buttonClose    ->setFocus(); }
            else if( buttonClose    ->hasFocus() )  { buttonPreview  ->setFocus(); }

            break;

        case Qt::Key_Enter:

            if     ( buttonMirror[8]->hasFocus() )  { onButtonMirrorAll();         }
            else if( buttonMirror[0]->hasFocus() )  { onButtonMirror(0);           }
            else if( buttonMirror[1]->hasFocus() )  { onButtonMirror(1);           }
            else if( buttonMirror[2]->hasFocus() )  { onButtonMirror(2);           }
            else if( buttonMirror[3]->hasFocus() )  { onButtonMirror(3);           }
            else if( buttonMirror[4]->hasFocus() )  { onButtonMirror(4);           }
            else if( buttonMirror[5]->hasFocus() )  { onButtonMirror(5);           }
            else if( buttonMirror[6]->hasFocus() )  { onButtonMirror(6);           }
            else if( buttonMirror[7]->hasFocus() )  { onButtonMirror(7);           }

            else if( buttonFlip[8]  ->hasFocus() )  { onButtonFlipAll();           }
            else if( buttonFlip[0]  ->hasFocus() )  { onButtonFlip(0);             }
            else if( buttonFlip[1]  ->hasFocus() )  { onButtonFlip(1);             }
            else if( buttonFlip[2]  ->hasFocus() )  { onButtonFlip(2);             }
            else if( buttonFlip[3]  ->hasFocus() )  { onButtonFlip(3);             }
            else if( buttonFlip[4]  ->hasFocus() )  { onButtonFlip(4);             }
            else if( buttonFlip[5]  ->hasFocus() )  { onButtonFlip(5);             }
            else if( buttonFlip[6]  ->hasFocus() )  { onButtonFlip(6);             }
            else if( buttonFlip[7]  ->hasFocus() )  { onButtonFlip(7);             }

            else if( buttonRotate[8]->hasFocus() )  { onButtonRotateAll();         }
            else if( buttonRotate[0]->hasFocus() )  { onButtonRotate(0);           }
            else if( buttonRotate[1]->hasFocus() )  { onButtonRotate(1);           }
            else if( buttonRotate[2]->hasFocus() )  { onButtonRotate(2);           }
            else if( buttonRotate[3]->hasFocus() )  { onButtonRotate(3);           }
            else if( buttonRotate[4]->hasFocus() )  { onButtonRotate(4);           }
            else if( buttonRotate[5]->hasFocus() )  { onButtonRotate(5);           }
            else if( buttonRotate[6]->hasFocus() )  { onButtonRotate(6);           }
            else if( buttonRotate[7]->hasFocus() )  { onButtonRotate(7);           }

            else if( buttonPreview  ->hasFocus() )  { onButtonPreview();           }
            else if( buttonSave     ->hasFocus() )  { onButtonSave();              }
            else if( buttonClose    ->hasFocus() )  { onButtonClose();             }

            break;

        case Qt::Key_Escape:

            onButtonClose();

            break;

        default:

            return;
    }
}
