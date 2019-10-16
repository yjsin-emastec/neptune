#ifndef SYSTEMPAGE_H
#define SYSTEMPAGE_H

#include <QtGui/QWidget>
#include "ui_systempage.h"
#include "ui_systempage1080p.h"
#include "ui/customwidget/customimagelabel.h"

class UiKeyboardDialog;
class TextMessageDialog;
class SetDateTimeDialog;
class SecurityDialog;
class ConfigDialog;
class AppUpgradeDialog;
class LanguageDialog;
class LicensePlateDialog;
class InformationDialog;

class SystemPage : public QWidget
{
    Q_OBJECT

public:
    SystemPage(QWidget *parent = 0);
    ~SystemPage();

    CustomImageLabel    *buttonDateTime;
    CustomImageLabel    *buttonSecurity;
    CustomImageLabel    *buttonConfig;
    CustomImageLabel    *buttonUpgrade;
    CustomImageLabel    *buttonFactoryDefault;
    CustomImageLabel    *buttonLanguage;
    CustomImageLabel    *buttonLicensePlate;
    CustomImageLabel    *buttonInformation;
    CustomImageLabel    *buttonClose;

    QLabel              *labelDateTimeText;
    QLabel              *labelSecurityText;
    QLabel              *labelConfigText;
    QLabel              *labelUpgradeText;
    QLabel              *labelFactoryDefaultText;
    QLabel              *labelLanguageText;
    QLabel              *labelLicensePalteText;
    QLabel              *labelInformationText;
    QLabel              *labelCloseText;

signals:
    void saveSystemPage(int type, int val);
    void upgradeProgress(int percent);
	void escapeTabFocus(void);
    void closeSetupMenu(void);

public slots:
    void onButtonDateTime(void);
    void onButtonSecurity(void);
    void onButtonConfig(void);
    void onButtonUpgrade(void);
    void onButtonFactoryDefault(void);
    void onButtonLanguage(void);
    void onButtonLicensePlate(void);
    void onButtonInformation(void);
    void onButtonClose(void);
    void onUpgradeProgress(int percent);
    void dateFormatChanged(int val);

    void setFocusDateTime(void);
    void setFocusSecurity(void);
    void setFocusConfig(void);
    void setFocusUpgrade(void);
    void setFocusFactoryDefault(void);
    void setFocusLanguage(void);
    void setFocusLicensePlate(void);
    void setFocusInformation(void);
    void setFocusClose(void);
    void setFocusTabLayout(void);

private:
    TextMessageDialog    *msgBox;
    UiKeyboardDialog     *keyboard;
    SetDateTimeDialog    *clockDlg;
    SecurityDialog       *securityDialog;
    ConfigDialog         *configDialog;
    AppUpgradeDialog     *upgradeDialog;
    LanguageDialog       *languageDialog;
    LicensePlateDialog   *licensePlateDialog;
    InformationDialog    *informationDialog;

    QPixmap iconImageNormal[9];
    QPixmap iconImageFocus[9];

    void changeFocus(int n);

    int iconSize;
};

#endif // SYSTEMPAGE_H
