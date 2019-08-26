#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

#include <QtGui/QWidget>
#include "ui_devicepage.h"
#include "ui_devicepage1080p.h"
#include "DVR.h"

class TextMessageDialog;
class VideoInputDialog;
class TriggerInputDialog;
class GsensorDialog;
class BuzzerDialog;

class DevicePage : public QWidget
{
    Q_OBJECT

public:
    DevicePage(QWidget *parent = 0);
    ~DevicePage();

    QPushButton *buttonVideo;
    QPushButton *buttonTrigger;
    QPushButton *buttonGsensor;
    QPushButton *buttonBuzzer;
    QPushButton *buttonDiskFormat;
    QPushButton *buttonClose;

signals:
	void saveDevicePage(int type);
	void escapeTabFocus(void);
	void closeSetupMenu(void);
    void makeTransparent(int n);
    void videoInputPreview();

public slots:

private slots:
	void onButtonVideo(void);
	void onButtonTrigger(void);
	void onButtonGsensor(void);
	void onButtonBuzzer(void);
	void onDiskFormat(void);
	void onButtonClose(void);
    void onMakeTransparent(int n);
    void onVideoInputPreview();

private:
	TextMessageDialog   *msgBox;
	VideoInputDialog    *videoInputDialog;
	TriggerInputDialog  *triggerInputDialog;
	GsensorDialog       *gsensorDialog;
	BuzzerDialog        *buzzerDialog;
    disk_used_info_t     diskInfo[MAX_HDD_COUNT];
};

#endif // DEVICEPAGE_H
