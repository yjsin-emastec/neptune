#ifndef DISPLAYPAGE_H
#define DISPLAYPAGE_H

#include <QtGui/QWidget>
#include "ui_displaypage.h"
#include "ui_displaypage1080p.h"
#include "ui/customwidget/customimagelabel.h"

class TextMessageDialog;
class CameraNameDialog;
class VideoOutputDialog;
class OsdDialog;

class DisplayPage : public QWidget
{
    Q_OBJECT

public:
    DisplayPage(QWidget *parent = 0);
    ~DisplayPage();

    CustomImageLabel *buttonVideoOutput;
    CustomImageLabel *buttonCameraName;
    CustomImageLabel *buttonNotAvailable;
    CustomImageLabel *buttonOsd;
    CustomImageLabel *buttonNotAvailable2;
    CustomImageLabel *buttonClose;

    QLabel *labelVideoOutputText;
    QLabel *labelCameraNameText;
    QLabel *labelNotAvailableText;
    QLabel *labelOsdText;
    QLabel *labelNotAvailableText2;
    QLabel *labelCloseText;

signals:
    void saveDisplayPage(int type);
	void escapeTabFocus(void);
	void closeSetupMenu(void);

public slots:
	void onButtonCameraName(void);
	void onButtonVideoOutput(void);
	void onButtonOsd(void);
	void onButtonClose(void);

    void setFocusVideoOutput(void);
    void setFocusCameraName(void);
    void setFocusOsd(void);
    void setFocusClose(void);
    void setFocusTabLayout(void);

private:
    TextMessageDialog  *msgBox;
	CameraNameDialog   *cameraNameDialog;
	VideoOutputDialog  *videoOutputDialog;
	OsdDialog          *osdDialog;

    QPixmap iconImageNormal[6];
    QPixmap iconImageFocus[6];

    void changeFocus(int n);

    int iconSize;
};

#endif // DISPLAYPAGE_H
