#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include "ui_setupdialog.h"
#include "ui_setupdialog1080p.h"

class QTabWidget;
class SystemPage;
class RecordPage;
class DisplayPage;
class DevicePage;
class InitProgressDialog;
class TextMessageDialog;

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    SetupDialog(QWidget *parent = 0);
    void updateConfig(int userId);
    void tabChangeIcon();
    int  diskFormat;
    int  criticalChangeType;
    int  setupMdinVideoOutput;
    int  tabCurIdx;
    int  tabPreIdx;
    bool tabChangeFlag;

    QFrame       *frame;

signals:
    void progressEvent(int type, int progressType, int progress);
    void saveSystemPage(int type, int val);
    void saveRecordPage(int type);
    void saveDisplayPage(int type);
    void saveDevicePage(int type);
    void upgradeProgress(int percent);
    void videoInputPreview();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);

public slots:
    void updateConfigProgress(int cfgType, int progress);    
    void onUpgradeProgress(int percent);

private slots:
    void setupPageChanged(int pageNum);
    void onSaveSystemPage(int type, int val);
    void onSaveRecordPage(int type);
    void onSaveDisplayPage(int type);
    void onSaveDevicePage(int type);
    void onEscapeTabFocus(void);
    void onMakeTransparent(int n);
    void onVideoInputPreview();

private:
    void createTabLayout();
    void createButtonLayout();
    void setTabFocus(int isLeftRight, int tabCurInx, int colIndex);
    void resetTabFocus(int isUp, int tabCurInx);

    QTabWidget   *tabLayout;

    QHBoxLayout  *hBoxLayout;
    QPushButton  *button_Ok;
    QPushButton  *button_Cancel;

    SystemPage   *systemPage;
    DisplayPage  *displayPage;
    RecordPage   *recordPage;
    DevicePage   *devicePage;

    InitProgressDialog  *progressDialog;
    TextMessageDialog   *msgBox;

    int progressType, indexSystem, indexRecord, indexDisplay, indexDevice;
};

#endif // SETUPDIALOG_H
