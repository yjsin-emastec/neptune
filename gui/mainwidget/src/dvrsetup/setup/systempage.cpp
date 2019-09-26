#include "systempage.h"
#include "ui/keyboard/uikeyboarddialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "dvrsetup/system/datetime/setdatetimedialog.h"
#include "dvrsetup/system/security/securitydialog.h"
#include "dvrsetup/system/config/configdialog.h"
#include "dvrsetup/system/upgrade/appupgradedialog.h"
#include "dvrsetup/system/language/languagedialog.h"
#include "dvrsetup/system/licenseplate/licenseplatedialog.h"
#include "dvrsetup/system/information/informationdialog.h"
#include "main/mainglobal.h"
#include "main/languagedefine.h"
#include "appmgr.h"

SystemPage::SystemPage(QWidget *parent)
    : QWidget(parent)
{
    if(mainHeight == 720)
    {
        Ui::SystemPage ui720;
        ui720.setupUi(this);

        buttonDateTime          = ui720.buttonDateTime;
        buttonSecurity          = ui720.buttonSecurity;
        buttonConfig            = ui720.buttonConfig;
        buttonUpgrade           = ui720.buttonUpgrade;
        buttonFactoryDefault    = ui720.buttonFactoryDefault;
        buttonLanguage          = ui720.buttonLanguage;
        buttonLicensePlate      = ui720.buttonLicensePlate;
        buttonInformation       = ui720.buttonInformation;
        buttonClose             = ui720.buttonClose;

        labelDateTimeText       = ui720.labelDateTimeText;
        labelSecurityText       = ui720.labelSecurityText;
        labelConfigText         = ui720.labelConfigText;
        labelUpgradeText        = ui720.labelUpgradeText;
        labelFactoryDefaultText = ui720.labelFactoryDefaultText;
        labelLanguageText       = ui720.labelLanguageText;
        labelLicensePalteText   = ui720.labelLicensePlateText;
        labelInformationText    = ui720.labelInformationText;
        labelCloseText          = ui720.labelCloseText;

        labelDateTimeText       ->setStyleSheet("font:40px;");
        labelSecurityText       ->setStyleSheet("font:40px;");
        labelConfigText         ->setStyleSheet("font:40px;");
        labelUpgradeText        ->setStyleSheet("font:40px;");
        labelFactoryDefaultText ->setStyleSheet("font:40px;");
        labelLanguageText       ->setStyleSheet("font:40px;");
        labelLicensePalteText   ->setStyleSheet("font:40px;");
        labelInformationText    ->setStyleSheet("font:40px;");
        labelCloseText          ->setStyleSheet("font:40px;");
    }
    else
    {
        Ui::SystemPage1080p ui1080;
        ui1080.setupUi(this);

        buttonDateTime          = ui1080.buttonDateTime;
        buttonSecurity          = ui1080.buttonSecurity;
        buttonConfig            = ui1080.buttonConfig;
        buttonUpgrade           = ui1080.buttonUpgrade;
        buttonFactoryDefault    = ui1080.buttonFactoryDefault;
        buttonLanguage          = ui1080.buttonLanguage;
        buttonLicensePlate      = ui1080.buttonLicensePlate;
        buttonInformation       = ui1080.buttonInformation;
        buttonClose             = ui1080.buttonClose;

        labelDateTimeText       = ui1080.labelDateTimeText;
        labelSecurityText       = ui1080.labelSecurityText;
        labelConfigText         = ui1080.labelConfigText;
        labelUpgradeText        = ui1080.labelUpgradeText;
        labelFactoryDefaultText = ui1080.labelFactoryDefaultText;
        labelLanguageText       = ui1080.labelLanguageText;
        labelLicensePalteText   = ui1080.labelLicensePlateText;
        labelInformationText    = ui1080.labelInformationText;
        labelCloseText          = ui1080.labelCloseText;

        labelDateTimeText       ->setStyleSheet("font:65px;");
        labelSecurityText       ->setStyleSheet("font:65px;");
        labelConfigText         ->setStyleSheet("font:65px;");
        labelUpgradeText        ->setStyleSheet("font:65px;");
        labelFactoryDefaultText ->setStyleSheet("font:65px;");
        labelLanguageText       ->setStyleSheet("font:65px;");
        labelLicensePalteText   ->setStyleSheet("font:65px;");
        labelInformationText    ->setStyleSheet("font:65px;");
        labelCloseText          ->setStyleSheet("font:65px;");
    }

    setPalette(QPalette(QColor(26, 32, 46)));
    setAutoFillBackground(true);

    keyboard            = NULL;
    msgBox              = NULL;
    clockDlg            = NULL;
    securityDialog      = NULL;
    configDialog        = NULL;
    upgradeDialog       = NULL;
    languageDialog      = NULL;
    licensePlateDialog  = NULL;
    informationDialog   = NULL;

    iconImageNormal[0].load(":images/dvrsetup/system/datetime.png");
    iconImageNormal[1].load(":images/dvrsetup/system/security.png");
    iconImageNormal[2].load(":images/dvrsetup/system/config.png");
    iconImageNormal[3].load(":images/dvrsetup/system/upgrade.png");
    iconImageNormal[4].load(":images/dvrsetup/system/factorydefault.png");
    iconImageNormal[5].load(":images/dvrsetup/system/language.png");
    iconImageNormal[6].load(":images/dvrsetup/system/licenseplate.png");
    iconImageNormal[7].load(":images/dvrsetup/system/information.png");
    iconImageNormal[8].load(":images/dvrsetup/system/close.png");

    iconImageFocus[0].load(":images/dvrsetup/system/datetime2.png");
    iconImageFocus[1].load(":images/dvrsetup/system/security2.png");
    iconImageFocus[2].load(":images/dvrsetup/system/config2.png");
    iconImageFocus[3].load(":images/dvrsetup/system/upgrade2.png");
    iconImageFocus[4].load(":images/dvrsetup/system/factorydefault2.png");
    iconImageFocus[5].load(":images/dvrsetup/system/language2.png");
    iconImageFocus[6].load(":images/dvrsetup/system/licenseplate2.png");
    iconImageFocus[7].load(":images/dvrsetup/system/information2.png");
    iconImageFocus[8].load(":images/dvrsetup/system/close2.png");

    buttonDateTime      ->setPixmap(iconImageNormal[0]);
    buttonSecurity      ->setPixmap(iconImageNormal[1]);
    buttonConfig        ->setPixmap(iconImageNormal[2]);
    buttonUpgrade       ->setPixmap(iconImageNormal[3]);
    buttonFactoryDefault->setPixmap(iconImageNormal[4]);
    buttonLanguage      ->setPixmap(iconImageNormal[5]);
    buttonLicensePlate  ->setPixmap(iconImageNormal[6]);
    buttonInformation   ->setPixmap(iconImageNormal[7]);
    buttonClose         ->setPixmap(iconImageNormal[8]);

    buttonDateTime      ->setScaledContents(true);  //resize img to label size
    buttonDateTime      ->setScaledContents(true);
    buttonSecurity      ->setScaledContents(true);
    buttonConfig        ->setScaledContents(true);
    buttonUpgrade       ->setScaledContents(true);
    buttonFactoryDefault->setScaledContents(true);
    buttonLanguage      ->setScaledContents(true);
    buttonLicensePlate  ->setScaledContents(true);
    buttonInformation   ->setScaledContents(true);
    buttonClose         ->setScaledContents(true);

    connect(buttonDateTime,         SIGNAL(pressed()), this, SLOT(onButtonDateTime()));
    connect(buttonSecurity,         SIGNAL(pressed()), this, SLOT(onButtonSecurity()));
    connect(buttonConfig,           SIGNAL(pressed()), this, SLOT(onButtonConfig()));
    connect(buttonUpgrade,          SIGNAL(pressed()), this, SLOT(onButtonUpgrade()));
    connect(buttonFactoryDefault,   SIGNAL(pressed()), this, SLOT(onButtonFactoryDefault()));
    connect(buttonLanguage,         SIGNAL(pressed()), this, SLOT(onButtonLanguage()));
    connect(buttonLicensePlate,     SIGNAL(pressed()), this, SLOT(onButtonLicensePlate()));
    connect(buttonInformation,      SIGNAL(pressed()), this, SLOT(onButtonInformation()));
    connect(buttonClose,            SIGNAL(pressed()), this, SLOT(onButtonClose()));

    connect(buttonDateTime,         SIGNAL(focusIn()), this, SLOT(setFocusDateTime()));
    connect(buttonSecurity,         SIGNAL(focusIn()), this, SLOT(setFocusSecurity()));
    connect(buttonConfig,           SIGNAL(focusIn()), this, SLOT(setFocusConfig()));
    connect(buttonUpgrade,          SIGNAL(focusIn()), this, SLOT(setFocusUpgrade()));
    connect(buttonFactoryDefault,   SIGNAL(focusIn()), this, SLOT(setFocusFactoryDefault()));
    connect(buttonLanguage,         SIGNAL(focusIn()), this, SLOT(setFocusLanguage()));
    connect(buttonLicensePlate,     SIGNAL(focusIn()), this, SLOT(setFocusLicensePlate()));
    connect(buttonInformation,      SIGNAL(focusIn()), this, SLOT(setFocusInformation()));
    connect(buttonClose,            SIGNAL(focusIn()), this, SLOT(setFocusClose()));
}
SystemPage::~SystemPage()
{
}
void SystemPage::onButtonDateTime(void)
{
    time_t now = 0;

    emit escapeTabFocus();

    if(!clockDlg)
    {
        clockDlg = new SetDateTimeDialog(this, cfgSetup.system.date_format, &cfgSetup.system.dls);
    }

    clockDlg->move((appmgr_get_mainwidget_width()-clockDlg->width())/2, (appmgr_get_mainwidget_height()-clockDlg->height())/2);

    if(clockDlg->exec())
    {
        clockDlg->getChangedConfig(&now, &cfgSetup.system.dls);
        if(now == 0)
        {
            emit saveSystemPage(2, 0);
        }
    }
    else
    {
        emit saveSystemPage(0, 0);
    }

    delete clockDlg;
    clockDlg = NULL;

    if(now > 0)
    {
        if(!msgBox)
        {
            msgBox = new TextMessageDialog(tr("CHANGE DATE & TIME"),
                    tr("Do you want to change time?\n" "If yes, system will restart."), 0, this);
        }
        msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
        msgBoxEsckey = 1;

        if(msgBox->exec())
        {
            qDebug("%s has changed ......................", __func__);
            emit saveSystemPage(1, now);
        }
        else
        {
            emit saveSystemPage(0, 0);
        }

        delete msgBox;
        msgBox = NULL;

        msgBoxEsckey = 0;
    }
}
void SystemPage::onButtonSecurity(void)
{
    emit escapeTabFocus();

    if(!securityDialog)
    {
        securityDialog = new SecurityDialog(this);
    }

    securityDialog->initSecurityConfig();
    securityDialog->move((appmgr_get_mainwidget_width()-securityDialog->size().width())/2,(appmgr_get_mainwidget_height()-securityDialog->size().height())/2);

    if(securityDialog->exec())
    {
        qDebug("%s has changed ......................", __func__);
        emit saveSystemPage(5, 0);
    }
    else
    {
        emit saveSystemPage(0, 0);
    }

    delete securityDialog;
    securityDialog = NULL;
}
void SystemPage::onButtonConfig(void)
{
    emit escapeTabFocus();

    if(!configDialog)
    {
        configDialog = new ConfigDialog(this);
    }

    configDialog->initConfigConfig();
    configDialog->move((appmgr_get_mainwidget_width()-configDialog->size().width())/2,(appmgr_get_mainwidget_height()-configDialog->size().height())/2);

    if(configDialog->exec())
    {
        qDebug("%s has changed ......................", __func__);
        emit saveSystemPage(7, 0);
    }

    delete configDialog;
    configDialog = NULL;

}
void SystemPage::onUpgradeProgress(int percent)
{
    emit upgradeProgress(percent);
}
void SystemPage::onButtonUpgrade(void)
{
    emit escapeTabFocus();

    if(!upgradeDialog)
    {
        upgradeDialog = new AppUpgradeDialog(this);
    }

    connect(this, SIGNAL(upgradeProgress(int)), upgradeDialog, SLOT(onUpgradeProgress(int)));

    upgradeDialog->initAppUpgradeConfig();
    upgradeDialog->move((appmgr_get_mainwidget_width()-upgradeDialog->size().width())/2,(appmgr_get_mainwidget_height()-upgradeDialog->size().height())/2);

    if(upgradeDialog->exec())
    {
        qDebug("%s has changed ......................", __func__);
        emit saveSystemPage(8, 0);
    }

    disconnect(this, SIGNAL(upgradeProgress(int)), upgradeDialog, SLOT(onUpgradeProgress(int)));
    delete upgradeDialog;
    upgradeDialog = NULL;
}
void SystemPage::onButtonFactoryDefault(void)
{
    emit escapeTabFocus();

    if(!msgBox)
    {
        msgBox = new TextMessageDialog(tr("FACTORY DEFAULT"), tr("Do you want to set factory default?\n" "If yes, system will restart."), 0, this);
    }

    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);
    msgBoxEsckey = 1;

    if(msgBox->exec())
    {
        qDebug("%s has changed ......................", __func__);
        emit saveSystemPage(4, 0);
    }

    delete msgBox;
    msgBox = NULL;
    msgBoxEsckey = 0;
}
void SystemPage::onButtonLanguage(void)
{
    emit escapeTabFocus();

    if(!languageDialog)
    {
        languageDialog = new LanguageDialog(this);
    }

    languageDialog->initLanguageConfig();
    languageDialog->move((appmgr_get_mainwidget_width()-languageDialog->size().width())/2,(appmgr_get_mainwidget_height()-languageDialog->size().height())/2);

    if(languageDialog->exec())
    {
        qDebug("%s has changed ......................", __func__);

        emit saveSystemPage(6, 0);
    }
    else
    {
        emit saveSystemPage(0, 0);
    }

    delete languageDialog;
    languageDialog = NULL;

}
void SystemPage::onButtonLicensePlate(void)
{
    emit escapeTabFocus();

    if(!licensePlateDialog)
    {
        licensePlateDialog = new LicensePlateDialog(this);
    }

    licensePlateDialog->initLicensePlateConfig();
    licensePlateDialog->move((appmgr_get_mainwidget_width()-licensePlateDialog->size().width())/2,(appmgr_get_mainwidget_height()-licensePlateDialog->size().height())/2);

    if(licensePlateDialog->exec())
    {
        qDebug("%s has changed ......................", __func__);
        emit saveSystemPage(3, 0);
    }
    else
    {
        emit saveSystemPage(0, 0);
    }

    delete licensePlateDialog;
    licensePlateDialog = NULL;
}
void SystemPage::onButtonInformation(void)
{
    emit escapeTabFocus();

    if(!informationDialog)
    {
        informationDialog = new InformationDialog(this);
    }

    informationDialog->initInformationConfig();
    informationDialog->move((appmgr_get_mainwidget_width()-informationDialog->size().width())/2,(appmgr_get_mainwidget_height()-informationDialog->size().height())/2);

    if(informationDialog->exec())
    {
        ;
    }

    delete informationDialog;
    informationDialog = NULL;
}
void SystemPage::onButtonClose()
{
    emit escapeTabFocus();
    emit closeSetupMenu();
}
void SystemPage::dateFormatChanged(int val)
{
    if(val == 0)
    {
        utils_cfg_cpy_item(SystemCfg.date_format, "YYYY/MM/DD");
    }
    else if(val == 1)
    {
        utils_cfg_cpy_item(SystemCfg.date_format, "MM/DD/YYYY");
    }
    else if(val == 2)
    {
        utils_cfg_cpy_item(SystemCfg.date_format, "DD/MM/YYYY");
    }
    else if(val == 3)
    {
        utils_cfg_cpy_item(SystemCfg.date_format, "YYYY-MM-DD");
    }
    else if(val == 4)
    {
        utils_cfg_cpy_item(SystemCfg.date_format, "MM-DD-YYYY");
    }
    else if(val == 5)
    {
        utils_cfg_cpy_item(SystemCfg.date_format, "DD-MM-YYYY");
    }

    DateFormat = val;
}
void SystemPage::setFocusTabLayout()        { changeFocus(0); }
void SystemPage::setFocusDateTime()         { changeFocus(1); }
void SystemPage::setFocusSecurity()         { changeFocus(2); }
void SystemPage::setFocusConfig()           { changeFocus(3); }
void SystemPage::setFocusUpgrade()          { changeFocus(4); }
void SystemPage::setFocusFactoryDefault()   { changeFocus(5); }
void SystemPage::setFocusLanguage()         { changeFocus(6); }
void SystemPage::setFocusLicensePlate()     { changeFocus(7); }
void SystemPage::setFocusInformation()      { changeFocus(8); }
void SystemPage::setFocusClose()            { changeFocus(9); }
void SystemPage::changeFocus(int n)
{
    buttonDateTime      ->setPixmap(iconImageNormal[0]);
    buttonSecurity      ->setPixmap(iconImageNormal[1]);
    buttonConfig        ->setPixmap(iconImageNormal[2]);
    buttonUpgrade       ->setPixmap(iconImageNormal[3]);
    buttonFactoryDefault->setPixmap(iconImageNormal[4]);
    buttonLanguage      ->setPixmap(iconImageNormal[5]);
    buttonLicensePlate  ->setPixmap(iconImageNormal[6]);
    buttonInformation   ->setPixmap(iconImageNormal[7]);
    buttonClose         ->setPixmap(iconImageNormal[8]);

    buttonDateTime      ->setFocusState(false);
    buttonSecurity      ->setFocusState(false);
    buttonConfig        ->setFocusState(false);
    buttonUpgrade       ->setFocusState(false);
    buttonFactoryDefault->setFocusState(false);
    buttonLanguage      ->setFocusState(false);
    buttonLicensePlate  ->setFocusState(false);
    buttonInformation   ->setFocusState(false);
    buttonClose         ->setFocusState(false);

    switch(n)
    {
        case 0 :
            break;

        case 1 :
            buttonDateTime      ->setPixmap(iconImageFocus[0]);
            buttonDateTime      ->setFocusState(true);
            break;

        case 2:
            buttonSecurity      ->setPixmap(iconImageFocus[1]);
            buttonSecurity      ->setFocusState(true);
            break;

        case 3:
            buttonConfig        ->setPixmap(iconImageFocus[2]);
            buttonConfig        ->setFocusState(true);
            break;

        case 4:
            buttonUpgrade       ->setPixmap(iconImageFocus[3]);
            buttonUpgrade       ->setFocusState(true);
            break;

        case 5:
            buttonFactoryDefault->setPixmap(iconImageFocus[4]);
            buttonFactoryDefault->setFocusState(true);
            break;

        case 6:
            buttonLanguage      ->setPixmap(iconImageFocus[5]);
            buttonLanguage      ->setFocusState(true);
            break;

        case 7:
            buttonLicensePlate  ->setPixmap(iconImageFocus[6]);
            buttonLicensePlate  ->setFocusState(true);
            break;

        case 8:
            buttonInformation   ->setPixmap(iconImageFocus[7]);
            buttonInformation   ->setFocusState(true);
            break;

        case 9:
            buttonClose         ->setPixmap(iconImageFocus[8]);
            buttonClose         ->setFocusState(true);
            break;

        default :
            buttonDateTime      ->setPixmap(iconImageFocus[0]);
            buttonDateTime      ->setFocusState(true);
            break;
    }
}
