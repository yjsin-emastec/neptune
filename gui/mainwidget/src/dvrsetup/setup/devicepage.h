#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

#include <QtGui/QWidget>
#include "ui_devicepage.h"
#include "ui_devicepage1080p.h"
#include "DVR.h"
#include "ui/customwidget/customimagelabel.h"

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

    CustomImageLabel *buttonVideo;
    CustomImageLabel *buttonTrigger;
    CustomImageLabel *buttonGsensor;
    CustomImageLabel *buttonBuzzer;
    CustomImageLabel *buttonFormat;
    CustomImageLabel *buttonClose;

    QLabel *labelVideoText;
    QLabel *labelTriggerText;
    QLabel *labelGsensorText;
    QLabel *labelBuzzerText;
    QLabel *labelFormatText;
    QLabel *labelCloseText;

signals:
	void saveDevicePage(int type);
	void escapeTabFocus(void);
	void closeSetupMenu(void);
    void makeTransparent(int n);
    void videoInputPreview();
    void viewMarkerEdit(int state);
    void changeMarkerChannel(int ch);
    void updateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4);

public slots:
	void onButtonVideo(void);
	void onButtonTrigger(void);
	void onButtonGsensor(void);
	void onButtonBuzzer(void);
    void onButtonFormat(void);
	void onButtonClose(void);

    void setFocusVideo(void);
    void setFocusTrigger(void);
    void setFocusGsensor(void);
    void setFocusBuzzer(void);
    void setFocusFormat(void);
    void setFocusClose(void);
    void setFocusTabLayout(void);

    void onMakeTransparent(int n);
    void onVideoInputPreview();
    void onViewMarkerEdit(int state);
    void onChangeMarkerChannel(int ch);
    void onUpdateMarker(QPoint p1, QPoint p2, QPoint p3, QPoint p4);

private:
	TextMessageDialog   *msgBox;
	VideoInputDialog    *videoInputDialog;
	TriggerInputDialog  *triggerInputDialog;
	GsensorDialog       *gsensorDialog;
	BuzzerDialog        *buzzerDialog;
    disk_used_info_t     diskInfo[MAX_HDD_COUNT];

    QPixmap iconImageNormal[6];
    QPixmap iconImageFocus[6];

    void changeFocus(int n);

    int iconSize;
};

#endif // DEVICEPAGE_H
