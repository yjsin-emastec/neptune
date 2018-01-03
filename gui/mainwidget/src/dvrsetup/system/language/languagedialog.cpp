#include <QDir>
#include <iostream>
#include <QtGui>
#include "languagedialog.h"
#include "../../../main/mainglobal.h"
#include "textmessagebox/textmessagedialog.h"

LanguageDialog::LanguageDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    msgBox = NULL;
    buttonLanguageUp->setFocus();

    lineEditLanguage->setStyleSheet("QLineEdit{font:64px;color:white;background-color:rgb(50,57,83);border-width:1px;border-style:inset;border-color:white;}");
    lineEditLanguage->setAlignment(Qt::AlignCenter);

    buttonLanguageUp->setIcon(QIcon(":/images/arrow_up.png"));
    buttonLanguageUp->setIconSize(QSize(90, 90));

    buttonLanguageDown->setIcon(QIcon(":/images/arrow_down.png"));
    buttonLanguageDown->setIconSize(QSize(90, 90));

    connect(buttonLanguageUp,   SIGNAL(released()), this, SLOT(onButtonLanguageUp()));
    connect(buttonLanguageDown, SIGNAL(released()), this, SLOT(onButtonLanguageDown()));
    connect(buttonSave,         SIGNAL(released()), this, SLOT(onButtonLanguageSave()));
    connect(buttonClose,        SIGNAL(released()), this, SLOT(reject()));

    previousLanguage=lineEditLanguage->text();
}
LanguageDialog::~LanguageDialog()
{
}
void LanguageDialog::onButtonLanguageSave()
{
    if( strcmp (&SystemCfg.language[0], &SystemCfgTemp.language[0]) == 0)
    {
        QTimer::singleShot(10, this, SLOT(reject()));
    }
    else
    {
        if(!msgBox)
        {
            msgBox = new TextMessageDialog(tr("Language Change"), tr("WARNING\n\n" "After changing the language,\n" "System will restart."), 15, this);
        }
        msgBox->setMsgAlignment(Qt::AlignCenter);
        msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
        msgBoxEsckey = 1;

        if(msgBox->exec())
        {
            QTimer::singleShot(0, this, SLOT(accept()));
        }
        delete msgBox;
        msgBox = NULL;
        msgBoxEsckey = 0;
    }
}
void LanguageDialog::initLanguageConfig(void)
{
    buttonLanguageUp->setFocus();

    if(utils_cfg_cmp_item(SystemCfg.language, "ENGLISH") == 0)
    {
        lineEditLanguage->setText(tr("English"));
        indexLanguage = 1;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "KOREAN") == 0)
    {
        lineEditLanguage->setText(tr("Korean"));
        indexLanguage = 2;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
    {
        lineEditLanguage->setText(tr("Spanish"));
        indexLanguage = 3;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
    {
        lineEditLanguage->setText(tr("French"));
        indexLanguage = 4;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
    {
        lineEditLanguage->setText(tr("Italian"));
        indexLanguage = 5;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0)
    {
        lineEditLanguage->setText(tr("Portuguese"));
        indexLanguage = 6;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
    {
        lineEditLanguage->setText(tr("Japanese"));
        indexLanguage = 7;
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        lineEditLanguage->setText(tr("German"));
        indexLanguage = 8;
    }
}
void LanguageDialog::onButtonLanguageUp()
{
//    if(indexLanguage <= 1) { indexLanguage = 9; }
    if(indexLanguage <= 1) { indexLanguage = 7; }

    switch(--indexLanguage)
    {
        case 1: { lineEditLanguage->setText(tr("English"   ));  utils_cfg_cpy_item(SystemCfg.language, "ENGLISH"   );  break; }
        case 2: { lineEditLanguage->setText(tr("Korean"    ));  utils_cfg_cpy_item(SystemCfg.language, "KOREAN"    );  break; }
        case 3: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
        case 4: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
        case 5: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
        case 6: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }

#if 0    //yjsin [17/08/31] temporary use only english, korean
        case 3: { lineEditLanguage->setText(tr("German"    ));  utils_cfg_cpy_item(SystemCfg.language, "GERMAN"    );  break; }
        case 4: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
        case 5: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
        case 6: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
        case 7: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }
        case 8: { lineEditLanguage->setText(tr("Japanese"  ));  utils_cfg_cpy_item(SystemCfg.language, "JAPANESE"  );  break; }
#endif
    }
    /*
     * when you change the language to spanish, see below code.
     * 1. check the dvrsetup/system/upgrade/appupgradedialog. label size was modified.
     * 2. check the search/backupdialog. label size and button size was modified.
     * 3. check the stylesheet and MainWidget::loadStyleSheet(). Qbutton font was modified to small.
     * 4. check the device/triggerinputdialog. Qbutton size and font was modified.
     *
     * when you change the language to french, see below code.
     * 1. check the dvrsetup/system/upgrade/appupgradedialog. label size was modified.
     * 2. check the dvrsetup/system/information/informationdialog. font size was modified.
     * 3. check the dvrsetup/system/licenseplate/licenseplatedialog. font size was modified.
     *
     * when you change the language to Italian, see below code.
     * 1. check the device/triggerinputdialog. Qbutton size and font was modified.
     */
}
void LanguageDialog::onButtonLanguageDown()
{
    if(indexLanguage >= 6) { indexLanguage = 0; }
    //if(indexLanguage >= 8) { indexLanguage = 0; }
    switch(++indexLanguage)
    {
        case 1: { lineEditLanguage->setText(tr("English"   ));  utils_cfg_cpy_item(SystemCfg.language, "ENGLISH"   );  break; }
        case 2: { lineEditLanguage->setText(tr("Korean"    ));  utils_cfg_cpy_item(SystemCfg.language, "KOREAN"    );  break; }
        case 3: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
        case 4: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
        case 5: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
        case 6: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }

#if 0   //yjsin [17/08/31] temporary use only english, korean
        case 3: { lineEditLanguage->setText(tr("German"    ));  utils_cfg_cpy_item(SystemCfg.language, "GERMAN"    );  break; }
        case 4: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
        case 5: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
        case 6: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
        case 7: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }
        case 8: { lineEditLanguage->setText(tr("Japanese"  ));  utils_cfg_cpy_item(SystemCfg.language, "JAPANESE"  );  break; }
#endif
    }
}
void LanguageDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
                 if(buttonLanguageUp   ->hasFocus())    { buttonClose        ->setFocus(); }
            else if(buttonLanguageDown ->hasFocus())    { buttonLanguageUp   ->setFocus(); }
            else if(buttonClose        ->hasFocus())    { buttonLanguageDown ->setFocus(); }
            return;
        }
        case Qt::Key_Down:
        {
                 if(buttonLanguageUp   ->hasFocus())    { buttonLanguageDown ->setFocus(); }
            else if(buttonLanguageDown ->hasFocus())    { buttonClose        ->setFocus(); }
            else if(buttonClose        ->hasFocus())    { buttonLanguageUp   ->setFocus(); }
            return;
        }
        case Qt::Key_Left:
        {
                 if(buttonSave         ->hasFocus())    { buttonClose        ->setFocus(); }
            else if(buttonClose        ->hasFocus())    { buttonSave         ->setFocus(); }
            return;
        }
        case Qt::Key_Right:
        {
                 if(buttonSave         ->hasFocus())    { buttonClose        ->setFocus(); }
            else if(buttonClose        ->hasFocus())    { buttonSave         ->setFocus(); }
            return;
        }
        case Qt::Key_Enter:
        {
            break;
        }
        case Qt::Key_Escape:
        {
            reject();
            return;
        }
        default:
        {
            reject();
            return;
        }
    }

    QDialog::keyPressEvent(event);
}
void LanguageDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
