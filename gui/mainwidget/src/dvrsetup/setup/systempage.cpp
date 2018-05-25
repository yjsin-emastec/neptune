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
    setupUi(this);

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

#if 1 //yjsin [17/10/12] if text is long, change font size
    if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
    {
        buttonLicensePlate->setStyleSheet("font:43px;color:white");
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
    {
        buttonUpgrade->setStyleSheet("font:40px;color:white");
    }
    else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        buttonFactoryDefault->setStyleSheet("font:40px;color:white");
    }
#endif

    connect(buttonDateTime,       SIGNAL(released()), this, SLOT(onButtonDateTime()));
    connect(buttonSecurity,       SIGNAL(released()), this, SLOT(onButtonSecurity()));
    connect(buttonConfig,         SIGNAL(released()), this, SLOT(onButtonConfig()));
    connect(buttonUpgrade,        SIGNAL(released()), this, SLOT(onButtonUpgrade()));
    connect(buttonFactoryDefault, SIGNAL(released()), this, SLOT(onButtonFactoryDefault()));
    connect(buttonLanguage,       SIGNAL(released()), this, SLOT(onButtonLanguage()));
    connect(buttonLicensePlate,   SIGNAL(released()), this, SLOT(onButtonLicensePlate()));
    connect(buttonInformation,    SIGNAL(released()), this, SLOT(onButtonInformation()));
    connect(buttonClose,          SIGNAL(released()), this, SLOT(onButtonClose()));
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
            msgBox = new TextMessageDialog(tr("SET DATE & TIME"),
                    tr("\t\t\tWARNING\n\n"
                        "Do you want to change time?\n\nIf yes, system will restart.\n"),
                    0, this);
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
        msgBox = new TextMessageDialog(tr("FACTORY DEFAULT"), tr("\t\t\t   WARNING\n\n" "Do you want to set factory default?\n\n" "If yes, system will restart.\n"), 0, this);
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
