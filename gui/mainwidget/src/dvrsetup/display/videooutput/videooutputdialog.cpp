#include <QtGui>
#include "videooutputdialog.h"
#include "main/mainglobal.h"
#include "ui/numkeypaddialog/numkeypaddialog.h"
#include "textmessagebox/textmessagedialog.h"

VideoOutputDialog::VideoOutputDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    buttonHdmi->setFocus();

    msgBox    = NULL;
    numKeypad = NULL;

#if 1 //yjsin [18/01/22] if text is long, change button size.
    if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
    {
        buttonDefault->setGeometry(13, 540, 340, 91);
        //buttonDefault->setStyleSheet("font:38px");
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
    {
        buttonDefault->setGeometry(13, 540, 300, 91);
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
    {
        buttonDefault->setGeometry(13, 540, 300, 91);
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        buttonDefault->setGeometry(13, 540, 250, 91);
    }
#endif

    connect(buttonHdmi,         SIGNAL(released(void)), this, SLOT(onVideoOutputHdmi           (void)));
    connect(buttonCvbs,         SIGNAL(released(void)), this, SLOT(onVideoOutputCvbs           (void)));
    connect(button_cvbs_x,      SIGNAL(released(void)), this, SLOT(onVideoOutput_xClicked      (void)));
    connect(button_cvbs_y,      SIGNAL(released(void)), this, SLOT(onVideoOutput_yClicked      (void)));
    connect(button_cvbs_width,  SIGNAL(released(void)), this, SLOT(onVideoOutput_widthClicked  (void)));
    connect(button_cvbs_height, SIGNAL(released(void)), this, SLOT(onVideoOutput_heightClicked (void)));
    connect(buttonSave,         SIGNAL(released(void)), this, SLOT(onVideoOutputSaveClicked    (void)));
    connect(buttonClose,        SIGNAL(released(void)), this, SLOT(reject                      (void)));
    connect(buttonDefault,      SIGNAL(released(void)), this, SLOT(onVideoOutputDefaultClicked (void)));
}
VideoOutputDialog::~VideoOutputDialog()
{
}
void VideoOutputDialog::initVideoOutputConfig(void)
{

    if(utils_cfg_cmp_item(DisplayCfg.video_output_hdmi, "1280 x 720") == 0)
    {
        buttonHdmi->setText(tr("%1\n%2").arg(tr("HD"), tr("720p")));
        indexHdmi = 1;
        oldHdmi   = 1;
    }
    else if(utils_cfg_cmp_item(DisplayCfg.video_output_hdmi, "1920 x 1080") == 0)
    {
        buttonHdmi->setText(tr("%1\n%2").arg(tr("FHD"), tr("1080p")));
        indexHdmi = 0;
        oldHdmi   = 0;
    }

         if(utils_cfg_cmp_item(DisplayCfg.video_output_cvbs, "LIST1")  == 0) { buttonCvbs->setText(tr("%1\n%2").arg(tr("CVBS"),tr("List1")));  indexCvbs = 0; }
    else if(utils_cfg_cmp_item(DisplayCfg.video_output_cvbs, "LIST2")  == 0) { buttonCvbs->setText(tr("%1\n%2").arg(tr("CVBS"),tr("List2")));  indexCvbs = 1; }
    else if(utils_cfg_cmp_item(DisplayCfg.video_output_cvbs, "MANUAL") == 0) { buttonCvbs->setText(tr("%1\n%2").arg(tr("CVBS"),tr("Manual"))); indexCvbs = 2; }
    else                                                                     { buttonCvbs->setText(tr("%1\n%2").arg(tr("CVBS"),tr("LIST1")));  indexCvbs = 0; }

    if(indexCvbs != 2)
    {
        label2->setStyleSheet("background-color:rgb(39,0,79)");
        label3->setStyleSheet("background-color:rgb(39,0,79)");
        label4->setStyleSheet("background-color:rgb(39,0,79)");
        label5->setStyleSheet("background-color:rgb(39,0,79)");
        label6->setStyleSheet("background-color:rgb(39,0,79)");
        button_cvbs_x      ->setText(tr("X"));
        button_cvbs_y      ->setText(tr("Y"));
        button_cvbs_width  ->setText(tr("WIDTH"));
        button_cvbs_height ->setText(tr("HEIGHT"));
        button_cvbs_x      ->setEnabled(false);
        button_cvbs_y      ->setEnabled(false);
        button_cvbs_width  ->setEnabled(false);
        button_cvbs_height ->setEnabled(false);
        buttonDefault      ->setEnabled(false);
        buttonDefault      ->hide();
    }
    else
    {
        label2->setStyleSheet("background-color:rgb(50,57,83)");
        label3->setStyleSheet("background-color:rgb(50,57,83)");
        label4->setStyleSheet("background-color:rgb(50,57,83)");
        label5->setStyleSheet("background-color:rgb(50,57,83)");
        label6->setStyleSheet("background-color:rgb(50,57,83)");
        buttonDefault->setEnabled(true);
        buttonDefault->show();

        if(cfgSetup.gbl.ntsc)
        {
            button_cvbs_x      ->setText(tr("%1\n %2 ").arg(tr("X"     ), DisplayCfg.cvbs_ntsc_x_value     ));
            button_cvbs_y      ->setText(tr("%1\n %2 ").arg(tr("Y"     ), DisplayCfg.cvbs_ntsc_y_value     ));
            button_cvbs_width  ->setText(tr("%1\n %2 ").arg(tr("WIDTH" ), DisplayCfg.cvbs_ntsc_width_value ));
            button_cvbs_height ->setText(tr("%1\n %2 ").arg(tr("HEIGHT"), DisplayCfg.cvbs_ntsc_height_value));
        }
        else
        {
            button_cvbs_x      ->setText(tr("%1\n %2 ").arg(tr("X"     ), DisplayCfg.cvbs_pal_x_value     ));
            button_cvbs_y      ->setText(tr("%1\n %2 ").arg(tr("Y"     ), DisplayCfg.cvbs_pal_y_value     ));
            button_cvbs_width  ->setText(tr("%1\n %2 ").arg(tr("WIDTH" ), DisplayCfg.cvbs_pal_width_value ));
            button_cvbs_height ->setText(tr("%1\n %2 ").arg(tr("HEIGHT"), DisplayCfg.cvbs_pal_height_value));
        }
    }
}
void VideoOutputDialog::onVideoOutputHdmi()
{
    if(indexHdmi == 0)
    {
        buttonHdmi->setText(tr("%1\n%2").arg(tr("HD"), tr("720p")));
        utils_cfg_cpy_item(DisplayCfg.video_output_hdmi, "1280 x 720");
        indexHdmi = 1;
    }
    else if(indexHdmi == 1)
    {
        buttonHdmi->setText(tr("%1\n%2").arg(tr("FHD"), tr("1080p")));
        utils_cfg_cpy_item(DisplayCfg.video_output_hdmi, "1920 x 1080");
        indexHdmi = 0;
    }
}
void VideoOutputDialog::onVideoOutputCvbs()
{
    if(indexCvbs == 0)
    {
        label2->setStyleSheet("background-color:rgb(39,0,79)");
        label3->setStyleSheet("background-color:rgb(39,0,79)");
        label4->setStyleSheet("background-color:rgb(39,0,79)");
        label5->setStyleSheet("background-color:rgb(39,0,79)");
        label6->setStyleSheet("background-color:rgb(39,0,79)");

        buttonCvbs         ->setText(tr("%1\n%2").arg(tr("CVBS"),tr("List2")));
        utils_cfg_cpy_item(DisplayCfg.video_output_cvbs, "LIST2");
        button_cvbs_x      ->setText(tr("X"));
        button_cvbs_y      ->setText(tr("Y"));
        button_cvbs_width  ->setText(tr("WIDTH"));
        button_cvbs_height ->setText(tr("HEIGHT"));
        button_cvbs_x      ->setEnabled(false);
        button_cvbs_y      ->setEnabled(false);
        button_cvbs_width  ->setEnabled(false);
        button_cvbs_height ->setEnabled(false);
        buttonDefault      ->setEnabled(false);
        buttonDefault      ->hide();
        indexCvbs = 1;
    }
    else if(indexCvbs == 1)
    {
        label2->setStyleSheet("background-color:rgb(50,57,83)");
        label3->setStyleSheet("background-color:rgb(50,57,83)");
        label4->setStyleSheet("background-color:rgb(50,57,83)");
        label5->setStyleSheet("background-color:rgb(50,57,83)");
        label6->setStyleSheet("background-color:rgb(50,57,83)");

        buttonCvbs         ->setText(tr("%1\n%2").arg(tr("CVBS"),tr("Manual")));
        utils_cfg_cpy_item(DisplayCfg.video_output_cvbs, "MANUAL");
        button_cvbs_x      ->setEnabled(true);
        button_cvbs_y      ->setEnabled(true);
        button_cvbs_width  ->setEnabled(true);
        button_cvbs_height ->setEnabled(true);
        buttonDefault      ->setEnabled(true);
        buttonDefault      ->show();

        if(cfgSetup.gbl.ntsc)
        {
            button_cvbs_x      ->setText(tr("%1\n %2 ").arg(tr("X"     )).arg(DisplayCfg.cvbs_ntsc_x_value     ));
            button_cvbs_y      ->setText(tr("%1\n %2 ").arg(tr("Y"     )).arg(DisplayCfg.cvbs_ntsc_y_value     ));
            button_cvbs_width  ->setText(tr("%1\n %2 ").arg(tr("WIDTH" )).arg(DisplayCfg.cvbs_ntsc_width_value ));
            button_cvbs_height ->setText(tr("%1\n %2 ").arg(tr("HEIGHT")).arg(DisplayCfg.cvbs_ntsc_height_value));
        }
        else
        {
            button_cvbs_x      ->setText(tr("%1\n %2 ").arg(tr("X"     )).arg(DisplayCfg.cvbs_pal_x_value     ));
            button_cvbs_y      ->setText(tr("%1\n %2 ").arg(tr("Y"     )).arg(DisplayCfg.cvbs_pal_y_value     ));
            button_cvbs_width  ->setText(tr("%1\n %2 ").arg(tr("WIDTH" )).arg(DisplayCfg.cvbs_pal_width_value ));
            button_cvbs_height ->setText(tr("%1\n %2 ").arg(tr("HEIGHT")).arg(DisplayCfg.cvbs_pal_height_value));
        }

        indexCvbs = 2;
    }
    else if(indexCvbs == 2)
    {
        label2->setStyleSheet("background-color:rgb(39,0,79)");
        label3->setStyleSheet("background-color:rgb(39,0,79)");
        label4->setStyleSheet("background-color:rgb(39,0,79)");
        label5->setStyleSheet("background-color:rgb(39,0,79)");
        label6->setStyleSheet("background-color:rgb(39,0,79)");

        buttonCvbs         ->setText(tr("%1\n%2").arg(tr("CVBS"),tr("List1")));
        utils_cfg_cpy_item(DisplayCfg.video_output_cvbs, "LIST1");
        button_cvbs_x      ->setText(tr("X"));
        button_cvbs_y      ->setText(tr("Y"));
        button_cvbs_width  ->setText(tr("WIDTH"));
        button_cvbs_height ->setText(tr("HEIGHT"));
        button_cvbs_x      ->setEnabled(false);
        button_cvbs_y      ->setEnabled(false);
        button_cvbs_width  ->setEnabled(false);
        button_cvbs_height ->setEnabled(false);
        buttonDefault      ->setEnabled(false);
        buttonDefault      ->hide();
        indexCvbs = 0;
    }
}
void VideoOutputDialog::onVideoOutput_xClicked()
{
    if(!numKeypad)
    {
        numKeypad = new NumKeypadDialog(this);
    }

    QString qstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_x_value : DisplayCfg.cvbs_pal_x_value);

    numKeypad->updateConfig(1);
    numKeypad->setText(qstr);

    numKeypad->move((appmgr_get_mainwidget_width()-numKeypad->width())/2, (appmgr_get_mainwidget_height()-numKeypad->height())/2);

    if(numKeypad->exec())
    {
        QString str = numKeypad->text();

        button_cvbs_x->setText(tr("%1\n %2 ").arg(tr("X")).arg(str));

        printf("%s \n", qPrintable(str));

        if(cfgSetup.gbl.ntsc)
        {
            sprintf(DisplayCfg.cvbs_ntsc_x_value, "%s", qPrintable(str));
        }
        else
        {
            sprintf(DisplayCfg.cvbs_pal_x_value, "%s", qPrintable(str));
        }
    }

    delete numKeypad;
    numKeypad = NULL;
}
void VideoOutputDialog::onVideoOutput_yClicked()
{
    if(!numKeypad)
    {
        numKeypad = new NumKeypadDialog(this);
    }

    QString qstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_y_value : DisplayCfg.cvbs_pal_y_value);

    numKeypad->updateConfig(1);
    numKeypad->setText(qstr);

    numKeypad->move((appmgr_get_mainwidget_width()-numKeypad->width())/2, (appmgr_get_mainwidget_height()-numKeypad->height())/2);

    if(numKeypad->exec())
    {
        QString str = numKeypad->text();

        button_cvbs_y->setText(tr("%1\n %2 ").arg(tr("Y")).arg(str));

        printf("%s \n", qPrintable(str));

        if(cfgSetup.gbl.ntsc)
        {
            sprintf(DisplayCfg.cvbs_ntsc_y_value, "%s", qPrintable(str));
        }
        else
        {
            sprintf(DisplayCfg.cvbs_pal_y_value, "%s", qPrintable(str));
        }

    }

    delete numKeypad;
    numKeypad = NULL;
}
void VideoOutputDialog::onVideoOutput_widthClicked()
{
    if(!numKeypad)
    {
        numKeypad = new NumKeypadDialog(this);
    }

    QString wstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_width_value : DisplayCfg.cvbs_pal_width_value);

    numKeypad->updateConfig(1);
    numKeypad->setText(wstr);

    numKeypad->move((appmgr_get_mainwidget_width()-numKeypad->width())/2, (appmgr_get_mainwidget_height()-numKeypad->height())/2);

    if(numKeypad->exec())
    {
        QString str = numKeypad->text();

        button_cvbs_width->setText(tr("%1\n %2 ").arg(tr("WIDTH")).arg(str));

        printf("%s \n", qPrintable(str));

        if(cfgSetup.gbl.ntsc)
        {
            sprintf(DisplayCfg.cvbs_ntsc_width_value, "%s", qPrintable(str));
        }
        else
        {
            sprintf(DisplayCfg.cvbs_pal_width_value, "%s", qPrintable(str));
        }

    }

    delete numKeypad;
    numKeypad = NULL;
}
void VideoOutputDialog::onVideoOutput_heightClicked()
{
    if(!numKeypad)
    {
        numKeypad = new NumKeypadDialog(this);
    }

    QString hstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_height_value : DisplayCfg.cvbs_pal_height_value);

    numKeypad->updateConfig(1);
    numKeypad->setText(hstr);

    numKeypad->move((appmgr_get_mainwidget_width()-numKeypad->width())/2, (appmgr_get_mainwidget_height()-numKeypad->height())/2);

    if(numKeypad->exec())
    {
        QString str = numKeypad->text();

        button_cvbs_height->setText(tr("%1\n %2 ").arg(tr("HEIGHT")).arg(str));

        printf("%s \n", qPrintable(str));

        if(cfgSetup.gbl.ntsc)
        {
            sprintf(DisplayCfg.cvbs_ntsc_height_value, "%s", qPrintable(str));
        }
        else
        {
            sprintf(DisplayCfg.cvbs_pal_height_value, "%s", qPrintable(str));
        }
    }

    delete numKeypad;
    numKeypad = NULL;
}
void VideoOutputDialog::onVideoOutputSaveClicked()
{
    int maxValue_H = 720;
    int maxValue_V = (cfgSetup.gbl.ntsc) ? 480 : 576;
    int minValue_H = 320;
    int minValue_V = (cfgSetup.gbl.ntsc) ? 240 : 288;

    if(indexCvbs == 2)
    {
        QString xstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_x_value       : DisplayCfg.cvbs_pal_x_value     );
        QString wstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_width_value   : DisplayCfg.cvbs_pal_width_value );
        QString ystr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_y_value       : DisplayCfg.cvbs_pal_y_value     );
        QString hstr = QString::fromUtf8(cfgSetup.gbl.ntsc ? DisplayCfg.cvbs_ntsc_height_value  : DisplayCfg.cvbs_pal_height_value);

        printf("X:%s Y:%s W:%s H:%s \n", qPrintable(xstr), qPrintable(ystr), qPrintable(wstr), qPrintable(hstr));

        if(msgBox)
        {
            delete msgBox;
            msgBox = NULL;
        }

        if((xstr.toInt() + wstr.toInt()) > maxValue_H)
        {
            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("INVALID X OR WIDTH"),
                        tr("\nPlease check X or Width value!\n"
                            "\nTotal horizontal pixel should be below %1.\n").arg(maxValue_H),
                        2, this);
            }
        }
        else if((ystr.toInt() + hstr.toInt()) > maxValue_V)
        {
            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("INVALID Y OR HEIGHT"),
                        tr("\nPlease check Y or Height value!\n"
                            "\nTotal vertical pixel should be below %1.\n").arg(maxValue_V),
                        2, this);
            }
        }
        else if(wstr.toInt() < minValue_H)
        {
            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("INVALID WIDTH"),
                        tr("\nPlease check Width value!\n"
                            "\nWidth pixel should be over %1.\n").arg(minValue_H),
                        2, this);
            }
        }
        else if(hstr.toInt() < minValue_V)
        {
            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("INVALID HEIGHT"),
                        tr("\nPlease check Height value!\n"
                            "\nHeight pixel should be over %1.\n").arg(minValue_V),
                        2, this);
            }
        }
        else
        {
            accept();
        }

        if(msgBox)
        {
            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

            if(msgBox->exec())
            {
                ;
            }

            delete msgBox;
            msgBox = NULL;
        }
    }
    else
    {
        accept();
    }
}
void VideoOutputDialog::onVideoOutputDefaultClicked(void)
{
    if(cfgSetup.gbl.ntsc)
    {
        sprintf(DisplayCfg.cvbs_ntsc_x_value, "%s", "24");
        sprintf(DisplayCfg.cvbs_ntsc_y_value, "%s", "12");
        sprintf(DisplayCfg.cvbs_ntsc_width_value, "%s", "672");
        sprintf(DisplayCfg.cvbs_ntsc_height_value, "%s", "456");

        button_cvbs_x      ->setText(tr("%1\n %2 ").arg(tr("X"     )).arg(DisplayCfg.cvbs_ntsc_x_value     ));
        button_cvbs_y      ->setText(tr("%1\n %2 ").arg(tr("Y"     )).arg(DisplayCfg.cvbs_ntsc_y_value     ));
        button_cvbs_width  ->setText(tr("%1\n %2 ").arg(tr("WIDTH" )).arg(DisplayCfg.cvbs_ntsc_width_value ));
        button_cvbs_height ->setText(tr("%1\n %2 ").arg(tr("HEIGHT")).arg(DisplayCfg.cvbs_ntsc_height_value));
    }
    else
    {
        sprintf(DisplayCfg.cvbs_pal_x_value, "%s", "24");
        sprintf(DisplayCfg.cvbs_pal_y_value, "%s", "12");
        sprintf(DisplayCfg.cvbs_pal_width_value, "%s", "672");
        sprintf(DisplayCfg.cvbs_pal_height_value, "%s", "526");

        button_cvbs_x      ->setText(tr("%1\n %2 ").arg(tr("X"     )).arg(DisplayCfg.cvbs_pal_x_value     ));
        button_cvbs_y      ->setText(tr("%1\n %2 ").arg(tr("Y"     )).arg(DisplayCfg.cvbs_pal_y_value     ));
        button_cvbs_width  ->setText(tr("%1\n %2 ").arg(tr("WIDTH" )).arg(DisplayCfg.cvbs_pal_width_value ));
        button_cvbs_height ->setText(tr("%1\n %2 ").arg(tr("HEIGHT")).arg(DisplayCfg.cvbs_pal_height_value));
    }
}
void VideoOutputDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(buttonHdmi->hasFocus() && buttonDefault->isEnabled())           { buttonDefault->setFocus();        }
            else if(buttonHdmi->hasFocus() && !buttonDefault->isEnabled())          { buttonSave->setFocus();           }
            else if(button_cvbs_x->hasFocus())                                      { buttonHdmi->setFocus();           }
            else if(button_cvbs_y->hasFocus())                                      { button_cvbs_x->setFocus();        }
            else if(buttonDefault->hasFocus())                                      { button_cvbs_y->setFocus();        }
            else if(buttonCvbs->hasFocus())                                         { buttonClose->setFocus();          }
            else if(button_cvbs_width->hasFocus())                                  { buttonCvbs->setFocus();           }
            else if(button_cvbs_height->hasFocus())                                 { button_cvbs_width->setFocus();    }
            else if(buttonSave->hasFocus() && button_cvbs_height->isEnabled())      { button_cvbs_height->setFocus();   }
            else if(buttonSave->hasFocus() && !button_cvbs_height->isEnabled())     { buttonCvbs->setFocus();           }
            else if(buttonClose->hasFocus() && button_cvbs_height->isEnabled())     { button_cvbs_height->setFocus();   }
            else if(buttonClose->hasFocus() && !button_cvbs_height->isEnabled())    { buttonCvbs->setFocus();           }

            return;

        case Qt::Key_Down:

                 if(buttonHdmi->hasFocus() && button_cvbs_x->isEnabled())           { button_cvbs_x->setFocus();        }
            else if(buttonHdmi->hasFocus() && !button_cvbs_x->isEnabled())          { buttonSave->setFocus();           }
            else if(button_cvbs_x->hasFocus())                                      { button_cvbs_y->setFocus();        }
            else if(button_cvbs_y->hasFocus())                                      { buttonDefault->setFocus();        }
            else if(buttonDefault->hasFocus())                                      { buttonHdmi->setFocus();           }
            else if(buttonCvbs->hasFocus() && button_cvbs_width->isEnabled())       { button_cvbs_width->setFocus();    }
            else if(buttonCvbs->hasFocus() && !button_cvbs_width->isEnabled())      { buttonClose->setFocus();          }
            else if(button_cvbs_width->hasFocus())                                  { button_cvbs_height->setFocus();   }
            else if(button_cvbs_height->hasFocus())                                 { buttonClose->setFocus();          }
            else if(buttonSave->hasFocus())                                         { buttonCvbs->setFocus();           }
            else if(buttonClose->hasFocus())                                        { buttonCvbs->setFocus();           }

            return;

        case Qt::Key_Left:

                 if(buttonHdmi->hasFocus())                                         { buttonCvbs->setFocus();           }
            else if(button_cvbs_x->hasFocus())                                      { button_cvbs_width->setFocus();    }
            else if(button_cvbs_y->hasFocus())                                      { button_cvbs_height->setFocus();   }
            else if(buttonDefault->hasFocus())                                      { buttonClose->setFocus();          }
            else if(buttonCvbs->hasFocus())                                         { buttonHdmi->setFocus();           }
            else if(button_cvbs_width->hasFocus())                                  { button_cvbs_x->setFocus();        }
            else if(button_cvbs_height->hasFocus())                                 { button_cvbs_y->setFocus();        }
            else if(buttonSave->hasFocus() && buttonDefault->isEnabled())           { buttonDefault->setFocus();        }
            else if(buttonSave->hasFocus() && !buttonDefault->isEnabled())          { buttonClose->setFocus();          }
            else if(buttonClose->hasFocus())                                        { buttonSave->setFocus();           }

            return;

        case Qt::Key_Right:

                 if(buttonHdmi->hasFocus())                                         { buttonCvbs->setFocus();           }
            else if(button_cvbs_x->hasFocus())                                      { button_cvbs_width->setFocus();    }
            else if(button_cvbs_y->hasFocus())                                      { button_cvbs_height->setFocus();   }
            else if(buttonDefault->hasFocus())                                      { buttonSave->setFocus();           }
            else if(buttonCvbs->hasFocus())                                         { buttonHdmi->setFocus();           }
            else if(button_cvbs_width->hasFocus())                                  { button_cvbs_x->setFocus();        }
            else if(button_cvbs_height->hasFocus())                                 { button_cvbs_y->setFocus();        }
            else if(buttonSave->hasFocus())                                         { buttonClose->setFocus();          }
            else if(buttonClose->hasFocus() && buttonDefault->isEnabled())          { buttonDefault->setFocus();        }
            else if(buttonClose->hasFocus() && !buttonDefault->isEnabled())         { buttonSave->setFocus();           }

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
void VideoOutputDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
