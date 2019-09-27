#include <QtGui>
#include "videoinputbar.h"
#include "main/mainglobal.h"

VideoInputBar::VideoInputBar(QWidget *parent)
    : QDialog(parent)
{
    if( mainHeight == 720 )
    {
        Ui::VideoInputBar ui720;
        ui720.setupUi(this);

        frame = ui720.frame;

        buttonCh[0] = ui720.buttonCh1;
        buttonCh[1] = ui720.buttonCh2;
        buttonCh[2] = ui720.buttonCh3;
        buttonCh[3] = ui720.buttonCh4;
        buttonCh[4] = ui720.buttonCh5;
        buttonCh[5] = ui720.buttonCh6;
        buttonCh[6] = ui720.buttonCh7;
        buttonCh[7] = ui720.buttonCh8;
        buttonCh[8] = ui720.buttonChAll;

        buttonMirror = ui720.buttonMirror;
        buttonFlip = ui720.buttonFlip;
        buttonClose = ui720.buttonClose;

        buttonMirror->setIcon(QIcon(":/images/mirror.png"));
        buttonMirror->setIconSize(QSize(60,60));
        buttonFlip->setIcon(QIcon(":images/flip.png"));
        buttonFlip->setIconSize(QSize(60,60));
        buttonClose->setIcon(QIcon(":images/close2.png"));
        buttonClose->setIconSize(QSize(60,60));
    }
    else
    {
        Ui::VideoInputBar1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;

        buttonCh[0] = ui1080.buttonCh1;
        buttonCh[1] = ui1080.buttonCh2;
        buttonCh[2] = ui1080.buttonCh3;
        buttonCh[3] = ui1080.buttonCh4;
        buttonCh[4] = ui1080.buttonCh5;
        buttonCh[5] = ui1080.buttonCh6;
        buttonCh[6] = ui1080.buttonCh7;
        buttonCh[7] = ui1080.buttonCh8;
        buttonCh[8] = ui1080.buttonChAll;

        buttonMirror = ui1080.buttonMirror;
        buttonFlip = ui1080.buttonFlip;
        buttonClose = ui1080.buttonClose;

        buttonMirror->setIcon(QIcon(":images/mirror.png"));
        buttonMirror->setIconSize(QSize(80,80));
        buttonFlip->setIcon(QIcon(":images/flip.png"));
        buttonFlip->setIconSize(QSize(80,80));
        buttonClose->setIcon(QIcon(":images/close2.png"));
        buttonClose->setIconSize(QSize(80,80));
    }
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    connect(buttonCh[0],   SIGNAL(clicked()), this, SLOT(onButtonCh1()));
    connect(buttonCh[1],   SIGNAL(clicked()), this, SLOT(onButtonCh2()));
    connect(buttonCh[2],   SIGNAL(clicked()), this, SLOT(onButtonCh3()));
    connect(buttonCh[3],   SIGNAL(clicked()), this, SLOT(onButtonCh4()));
    connect(buttonCh[4],   SIGNAL(clicked()), this, SLOT(onButtonCh5()));
    connect(buttonCh[5],   SIGNAL(clicked()), this, SLOT(onButtonCh6()));
    connect(buttonCh[6],   SIGNAL(clicked()), this, SLOT(onButtonCh7()));
    connect(buttonCh[7],   SIGNAL(clicked()), this, SLOT(onButtonCh8()));
    connect(buttonCh[8],   SIGNAL(clicked()), this, SLOT(onButtonChAll()));
    connect(buttonMirror,  SIGNAL(clicked()), this, SLOT(onButtonMirror()));
    connect(buttonFlip,    SIGNAL(clicked()), this, SLOT(onButtonFlip()));
    connect(buttonClose,   SIGNAL(clicked()), this, SLOT(onButtonClose()));
}
VideoInputBar::~VideoInputBar()
{
}
void VideoInputBar::onButtonCh1()   { onButtonCh(0); }
void VideoInputBar::onButtonCh2()   { onButtonCh(1); }
void VideoInputBar::onButtonCh3()   { onButtonCh(2); }
void VideoInputBar::onButtonCh4()   { onButtonCh(3); }
void VideoInputBar::onButtonCh5()   { onButtonCh(4); }
void VideoInputBar::onButtonCh6()   { onButtonCh(5); }
void VideoInputBar::onButtonCh7()   { onButtonCh(6); }
void VideoInputBar::onButtonCh8()   { onButtonCh(7); }
void VideoInputBar::onButtonChAll()
{
    selectedCh = NUMOFCH;

    int countM = 0;
    int countF = 0;

    for(int ch=0; ch<NUMOFCH; ch++)
    {
        if( infoMirror[ch] == 1 )           { countM++; }
        if( infoFlip[ch] == 1 )             { countF++; }
    }

    if( countM >= NUMOFCH )                 { infoMirror[NUMOFCH] = 1; }
    else                                    { infoMirror[NUMOFCH] = 0; }

    if( countF >= NUMOFCH )                 { infoFlip[NUMOFCH] = 1; }
    else                                    { infoFlip[NUMOFCH] = 0; }

    updateButton();
}
void VideoInputBar::onButtonCh(int n)
{
    selectedCh = n;

    updateButton();
}
void VideoInputBar::onButtonMirror()
{
    if( selectedCh >= NUMOFCH )             //selectCh All
    {
        int count = 0;

        for(int i=0; i<NUMOFCH; i++)
        {
            if( infoMirror[i] == 0 )        { count++; }
        }

        for(int i=0; i<=NUMOFCH; i++)
        {
            if( count >= NUMOFCH )          { infoMirror[i] = 1; }
            else                            { infoMirror[i] = 0; }
        }
    }
    else
    {
        if( infoMirror[selectedCh] == 0 )   { infoMirror[selectedCh] = 1; }
        else                                { infoMirror[selectedCh] = 0; }
    }

    updateButton();

    //save config for preview
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst = NULL;
        switch(i)
        {
            case 0 : { dst = DeviceCfg.camera_mirror00; break; }
            case 1 : { dst = DeviceCfg.camera_mirror01; break; }
            case 2 : { dst = DeviceCfg.camera_mirror02; break; }
            case 3 : { dst = DeviceCfg.camera_mirror03; break; }
#if 0 // yjsin DeviceCfg was defined up to 4ch
            case 4 : { dst = DeviceCfg.camera_mirror04; break; }
            case 5 : { dst = DeviceCfg.camera_mirror05; break; }
            case 6 : { dst = DeviceCfg.camera_mirror06; break; }
            case 7 : { dst = DeviceCfg.camera_mirror07; break; }
#endif
            default: { dst = NULL;                             }
        }

        if( dst != NULL )
        {
            if( infoMirror[i] == 1 )        { utils_cfg_cpy_item(dst, "MIRROR"); }
            else                            { utils_cfg_cpy_item(dst, "NORMAL"); }
        }
        else
        {
            qDebug("[Error] %s, DeviceCfg struct member dose not exitst.", __func__);
        }
    }
    emit videoInputPreview();
}
void VideoInputBar::onButtonFlip()
{
    if( selectedCh >= NUMOFCH )             //selectCh All
    {
        int count = 0;

        for(int i=0; i<NUMOFCH; i++)
        {
            if( infoFlip[i] == 0 )          { count++; }
        }

        for(int i=0; i<=NUMOFCH; i++)
        {
            if( count >= NUMOFCH )          { infoFlip[i] = 1; }
            else                            { infoFlip[i] = 0; }
        }
    }
    else
    {
        if( infoFlip[selectedCh] == 0 )     { infoFlip[selectedCh] = 1; }
        else                                { infoFlip[selectedCh] = 0; }
    }

    updateButton();

    //save config for preview
    for(int i=0; i<devInfo.videoNum; i++)
    {
        char *dst = NULL;
        switch(i)
        {
            case 0 : { dst = DeviceCfg.camera_flip00; break; }
            case 1 : { dst = DeviceCfg.camera_flip01; break; }
            case 2 : { dst = DeviceCfg.camera_flip02; break; }
            case 3 : { dst = DeviceCfg.camera_flip03; break; }
#if 0 // yjsin DeviceCfg was defined up to 4ch
            case 4 : { dst = DeviceCfg.camera_flip04; break; }
            case 5 : { dst = DeviceCfg.camera_flip05; break; }
            case 6 : { dst = DeviceCfg.camera_flip06; break; }
            case 7 : { dst = DeviceCfg.camera_flip07; break; }
#endif
            default: { dst = NULL;                           }
        }

        if( dst != NULL )
        {
            if( infoFlip[i] == 1 )          { utils_cfg_cpy_item(dst, "DOWN"); }
            else                            { utils_cfg_cpy_item(dst, "UP");   }
        }
        else
        {
            qDebug("[Error] %s, DeviceCfg struct member dose not exitst.", __func__);
        }
    }
    emit videoInputPreview();
}
void VideoInputBar::onButtonClose()
{
    accept();
}
void VideoInputBar::setInfo(int mirror[], int flip[])
{
    for(int i=0; i<NUMOFCH; i++)
    {
        infoMirror[i] = mirror[i];
        infoFlip[i] = flip[i];
    }

    selectedCh = NUMOFCH;
    buttonCh[selectedCh]->setFocus();

    updateButton();
}
void VideoInputBar::getInfo(int mirror[], int flip[])
{
    for(int i=0; i<NUMOFCH; i++)
    {
        mirror[i] = infoMirror[i];
        flip[i] = infoFlip[i];
    }
}
void VideoInputBar::updateButton()
{
    //update mirror, flip button state
    int countM = 0;
    int countF = 0;

    for(int i=0; i<NUMOFCH; i++)
    {
        if( infoMirror[i] == 1 )            { countM++; }
        if( infoFlip[i] == 1)               { countF++; }
    }

    if( countM >= NUMOFCH )                 { infoMirror[NUMOFCH] = 1; }
    else                                    { infoMirror[NUMOFCH] = 0; }

    if( countF >= NUMOFCH )                 { infoFlip[NUMOFCH] = 1; }
    else                                    { infoFlip[NUMOFCH] = 0; }

    if( infoMirror[selectedCh] == 1 )       { buttonMirror->setStyleSheet("QPushButton{background-color:rgb(6, 86, 159);} QPushButton:focus{background-color:rgb(152, 14, 69);}"); }
    else                                    { buttonMirror->setStyleSheet("QPushButton{background-color:rgb(67, 74, 86);} QPushButton:focus{background-color:rgb(152, 14, 69);}"); }

    if( infoFlip[selectedCh] == 1)          { buttonFlip->setStyleSheet("QPushButton{background-color:rgb(6, 86, 159);} QPushButton:focus{background-color:rgb(152, 14, 69);}"); }
    else                                    { buttonFlip->setStyleSheet("QPushButton{background-color:rgb(67, 74, 86);} QPushButton:focus{background-color:rgb(152, 14, 69);}"); }

    //change background color
    for(int i=0; i<=NUMOFCH; i++)
    {
         buttonCh[i]->setStyleSheet("QPushButton{background-color:rgb(67, 74, 86);} QPushButton:focus{background-color:rgb(152, 14, 69);}");
    }
    buttonCh[selectedCh]->setStyleSheet("QPushButton{background-color:rgb(6, 86, 159);} QPushButton:focus{background-color:rgb(152, 14, 69);}");
}
void VideoInputBar::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

            if     ( buttonCh[8]->hasFocus()  )     { buttonCh[0]->setFocus();  }
            else if( buttonCh[0]->hasFocus()  )     { buttonCh[1]->setFocus();  }
            else if( buttonCh[1]->hasFocus()  )     { buttonCh[2]->setFocus();  }
            else if( buttonCh[2]->hasFocus()  )     { buttonCh[3]->setFocus();  }
            else if( buttonCh[3]->hasFocus()  )     { buttonCh[4]->setFocus();  }
            else if( buttonCh[4]->hasFocus()  )     { buttonCh[5]->setFocus();  }
            else if( buttonCh[5]->hasFocus()  )     { buttonCh[6]->setFocus();  }
            else if( buttonCh[6]->hasFocus()  )     { buttonCh[7]->setFocus();  }
            else if( buttonCh[7]->hasFocus()  )     { buttonMirror->setFocus(); }
            else if( buttonMirror->hasFocus() )     { buttonFlip->setFocus();   }
            else if( buttonFlip->hasFocus()   )     { buttonClose->setFocus();  }
            else if( buttonClose->hasFocus()  )     { buttonCh[8]->setFocus();  }

            break;

        case Qt::Key_Down:

            if     ( buttonCh[8]->hasFocus()  )     { buttonClose->setFocus();  }
            else if( buttonCh[0]->hasFocus()  )     { buttonCh[8]->setFocus();  }
            else if( buttonCh[1]->hasFocus()  )     { buttonCh[0]->setFocus();  }
            else if( buttonCh[2]->hasFocus()  )     { buttonCh[1]->setFocus();  }
            else if( buttonCh[3]->hasFocus()  )     { buttonCh[2]->setFocus();  }
            else if( buttonCh[4]->hasFocus()  )     { buttonCh[3]->setFocus();  }
            else if( buttonCh[5]->hasFocus()  )     { buttonCh[4]->setFocus();  }
            else if( buttonCh[6]->hasFocus()  )     { buttonCh[5]->setFocus();  }
            else if( buttonCh[7]->hasFocus()  )     { buttonCh[6]->setFocus();  }
            else if( buttonMirror->hasFocus() )     { buttonCh[7]->setFocus();  }
            else if( buttonFlip->hasFocus()   )     { buttonMirror->setFocus(); }
            else if( buttonClose->hasFocus()  )     { buttonFlip->setFocus();   }

            break;

        case Qt::Key_Left:

            if     ( buttonCh[8]->hasFocus()  )     { buttonClose->setFocus();  }
            else if( buttonCh[0]->hasFocus()  )     { buttonCh[8]->setFocus();  }
            else if( buttonCh[1]->hasFocus()  )     { buttonCh[0]->setFocus();  }
            else if( buttonCh[2]->hasFocus()  )     { buttonCh[1]->setFocus();  }
            else if( buttonCh[3]->hasFocus()  )     { buttonCh[2]->setFocus();  }
            else if( buttonCh[4]->hasFocus()  )     { buttonCh[3]->setFocus();  }
            else if( buttonCh[5]->hasFocus()  )     { buttonCh[4]->setFocus();  }
            else if( buttonCh[6]->hasFocus()  )     { buttonCh[5]->setFocus();  }
            else if( buttonCh[7]->hasFocus()  )     { buttonCh[6]->setFocus();  }
            else if( buttonMirror->hasFocus() )     { buttonCh[7]->setFocus();  }
            else if( buttonFlip->hasFocus()   )     { buttonMirror->setFocus(); }
            else if( buttonClose->hasFocus()  )     { buttonFlip->setFocus();   }

            break;

        case Qt::Key_Right:

            if     ( buttonCh[8]->hasFocus()  )     { buttonCh[0]->setFocus();  }
            else if( buttonCh[0]->hasFocus()  )     { buttonCh[1]->setFocus();  }
            else if( buttonCh[1]->hasFocus()  )     { buttonCh[2]->setFocus();  }
            else if( buttonCh[2]->hasFocus()  )     { buttonCh[3]->setFocus();  }
            else if( buttonCh[3]->hasFocus()  )     { buttonCh[4]->setFocus();  }
            else if( buttonCh[4]->hasFocus()  )     { buttonCh[5]->setFocus();  }
            else if( buttonCh[5]->hasFocus()  )     { buttonCh[6]->setFocus();  }
            else if( buttonCh[6]->hasFocus()  )     { buttonCh[7]->setFocus();  }
            else if( buttonCh[7]->hasFocus()  )     { buttonMirror->setFocus(); }
            else if( buttonMirror->hasFocus() )     { buttonFlip->setFocus();   }
            else if( buttonFlip->hasFocus()   )     { buttonClose->setFocus();  }
            else if( buttonClose->hasFocus()  )     { buttonCh[8]->setFocus();  }

            break;

        case Qt::Key_Enter:

            if     ( buttonCh[8]->hasFocus()  )     { onButtonChAll();          }
            else if( buttonCh[0]->hasFocus()  )     { onButtonCh(0);            }
            else if( buttonCh[1]->hasFocus()  )     { onButtonCh(1);            }
            else if( buttonCh[2]->hasFocus()  )     { onButtonCh(2);            }
            else if( buttonCh[3]->hasFocus()  )     { onButtonCh(3);            }
            else if( buttonCh[4]->hasFocus()  )     { onButtonCh(4);            }
            else if( buttonCh[5]->hasFocus()  )     { onButtonCh(5);            }
            else if( buttonCh[6]->hasFocus()  )     { onButtonCh(6);            }
            else if( buttonCh[7]->hasFocus()  )     { onButtonCh(7);            }
            else if( buttonMirror->hasFocus() )     { onButtonMirror();         }
            else if( buttonFlip->hasFocus()   )     { onButtonFlip();           }
            else if( buttonClose->hasFocus()  )     { onButtonClose();          }

            break;

        case Qt::Key_Escape:

            onButtonClose();

            break;

        default:

            return;
    }
}
