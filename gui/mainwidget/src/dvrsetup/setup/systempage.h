#ifndef SYSTEMPAGE_H
#define SYSTEMPAGE_H

#include <QtGui/QWidget>
#include "ui_systempage.h"

class UiKeyboardDialog;
class TextMessageDialog;
class SetDateTimeDialog;
class SecurityDialog;
class ConfigDialog;
class AppUpgradeDialog;
class LanguageDialog;
class LicensePlateDialog;
class InformationDialog;

class SystemPage : public QWidget, public Ui::SystemPage
{
    Q_OBJECT

public:
    SystemPage(QWidget *parent = 0);
    ~SystemPage();

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
    void onUpgradeProgress(int percent);
    void dateFormatChanged(int val);

private slots:
	void onButtonClose(void);

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
};

#endif // SYSTEMPAGE_H
