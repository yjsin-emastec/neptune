#include <QDir>
#include <iostream>
#include <QtGui>
#include "languagedialog.h"
#include "../../../main/mainglobal.h"
#include "textmessagebox/textmessagedialog.h"

LanguageDialog::LanguageDialog(QWidget *parent)
    : QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::LanguageDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        lineEditLanguage = ui720.lineEditLanguage;
        buttonLanguageUp = ui720.buttonLanguageUp;
        buttonLanguageDown = ui720.buttonLanguageDown;
        buttonSave = ui720.buttonSave;
        buttonClose = ui720.buttonClose;

        lineEditLanguage->setStyleSheet("QLineEdit{font:64px;color:white;background-color:rgb(50,57,83);border-width:1px;border-style:inset;border-color:white;}");
    }
    else
    {
        Ui::LanguageDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        lineEditLanguage = ui1080.lineEditLanguage;
        buttonLanguageUp = ui1080.buttonLanguageUp;
        buttonLanguageDown = ui1080.buttonLanguageDown;
        buttonSave = ui1080.buttonSave;
        buttonClose = ui1080.buttonClose;

        lineEditLanguage->setStyleSheet("QLineEdit{font:110px;color:white;background-color:rgb(50,57,83);border-width:1px;border-style:inset;border-color:white;}");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    msgBox = NULL;
    buttonLanguageUp->setFocus();

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
            msgBox = new TextMessageDialog(tr("Language Change"), tr("After changing the language,\n" "System will restart."), 1, this);
        }
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
    if(indexLanguage <= 1) { indexLanguage = 9; }

    switch(--indexLanguage)
    {
        case 1: { lineEditLanguage->setText(tr("English"   ));  utils_cfg_cpy_item(SystemCfg.language, "ENGLISH"   );  break; }
        case 2: { lineEditLanguage->setText(tr("Korean"    ));  utils_cfg_cpy_item(SystemCfg.language, "KOREAN"    );  break; }
        case 3: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
        case 4: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
        case 5: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
        case 6: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }
        case 7: { lineEditLanguage->setText(tr("Japanese"  ));  utils_cfg_cpy_item(SystemCfg.language, "JAPANESE"  );  break; }
        case 8: { lineEditLanguage->setText(tr("German"  ));    utils_cfg_cpy_item(SystemCfg.language, "GERMAN"    );  break; }
    }
    /*
     * when you change the language to Spanish, see below code.
     * 1. check the search/backupdialog. label size and button size was modified.
     * 2. check the stylesheet and MainWidget::loadStyleSheet(). Qbutton font was modified to small.
     * 3. check the device/triggerinputdialog. QLabel font size was modified.
     * 4. check the search/systemlogpage. QLabel size was modified.
     *
     * when you change the language to French, see below code.
     * 1. check the dvrsetup/system/upgrade/appupgradedialog. label size was modified.
     * 2. check the dvrsetup/system/information/informationdialog. font size was modified.
     * 3. check the dvrsetup/system/licenseplate/licenseplatedialog. font size was modified.
     * 4. check the search/systemlogpage. QLabel size and font size was modified.
     * 5. check the dvrsetup/record/event/eventdialog. font size was modified.
     * 6. check the search/backupdialog. progressBar font size was modified.
     * 7. check the dvrsetup/system/display/videooutputdialog. Qbutton size was modified.
     * 8. check the dvrsetup/setup/systempage. Qbutton size was modified.
     *
     * when you change the language to Italian, see below code.
     * 1. check the device/triggerinputdialog. Qbutton size and font was modified.
     * 2. check the display/videooutput/videooutputdialog. Qbutton size was modified.
     * 3. check the search/systemlogpage. QLabel size was modified.
     * 4. check the dvrsetup/record/normal/normaldialog. Qbutton size was modified.
     * 5. check the dvrsetup/security/securitydialog. Qlabel font size was modified.
     * 6. check the dvrsetup/device/videoinput/videoinputdialog. QButton size was modified.
     *
     * when you change the language to Portuguese, see below code.
     * 1. check the stylesheet and MainWidget::loadStyleSheet(). Qbutton font was modified to small.
     * 2. check the search/backupdialog. font size was modified.
     * 3. check the search/systemlogpage. QLabel size and font size was modified.
     *
     * when you change the language to Japanese, see below code.
     * 1. check the dvrsetup/device/diskformat/diskformatprocess. font size was modified.
     * 2. check the dvrsetup/device/triggerinput/triggerinputdialog. label size was modified.
     * 3. check the dvrsetup/display/osd/osddialog. font size was modified.
     * 4. check the dvrsetup/setup/systempage. font size was modified.
     * 5. check the dvrsetup/system/upgrade/appupgradedialog. label size was modified.
     * 6. check the firstcheck/rtcsetdialog. font size was modified.
     * 7. check the login/logindialog. font size was modified.
     * 8. check the display/videooutput/videooutputdialog. Qbutton size was modified.
     * 9. check the search/systemlogpage. QLabel size was modified.
     * 10.check the dvrsetup/record/normal/normaldialog. Qbutton size was modified.
     * 11.check the dvrsetup/record/event/eventdialog. font size was modified.
     * 12.check the dvrsetup/security/securitydialog. Qlabel font size was modified.
     * 13.check the ui/keyboard/uikeyboarddialog. Qbutton font size was modified.
     *
     * when you change the language to German, see below code.
     * 1. check the dvrsetup/system/upgrade/appupgradedialog. font size was modified.
     * 2. check the search/calendarpage. font size was modified.
     * 3. check the dvrsetup/device/diskformat/diskformatprocess. font size was modified.
     * 4. check the dvrsetup/display/osd/osddialog. font size was modified.
     * 5. check the firstcheck/rtcsetdialog. button size was modified.
     * 6. check the dvrsetup/setup/systempage. font size was modified.
     * 7. check the display/videooutput/videooutputdialog. Qbutton size was modified.
     * 8. check the search/systemlogpage. QLabel size was modified.
     * 9. check the search/functiondialog. Qbutton size was modified.
     * 10.check the dvrsetup/record/normal/normaldialog. Qbutton size was modified.
     * 11.check the login/logindialog. font size was modified.
     * 12.check the dvrsetup/device/triggerinput/triggerinputdialog. Qbutton size was modified.
     */
}
void LanguageDialog::onButtonLanguageDown()
{
    if(indexLanguage >= 8) { indexLanguage = 0; }
    switch(++indexLanguage)
    {
        case 1: { lineEditLanguage->setText(tr("English"   ));  utils_cfg_cpy_item(SystemCfg.language, "ENGLISH"   );  break; }
        case 2: { lineEditLanguage->setText(tr("Korean"    ));  utils_cfg_cpy_item(SystemCfg.language, "KOREAN"    );  break; }
        case 3: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
        case 4: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
        case 5: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
        case 6: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }
        case 7: { lineEditLanguage->setText(tr("Japanese"  ));  utils_cfg_cpy_item(SystemCfg.language, "JAPANESE"  );  break; }
        case 8: { lineEditLanguage->setText(tr("German"    ));  utils_cfg_cpy_item(SystemCfg.language, "GERMAN"    );  break; }
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
            return;
        }
    }

    QDialog::keyPressEvent(event);
}
void LanguageDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
