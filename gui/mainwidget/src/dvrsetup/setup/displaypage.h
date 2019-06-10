#ifndef DISPLAYPAGE_H
#define DISPLAYPAGE_H

#include <QtGui/QWidget>
#include "ui_displaypage.h"
#include "ui_displaypage1080p.h"

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

    QPushButton *buttonVideoOutput;
    QPushButton *buttonCameraName;
    QPushButton *buttonOsd;
    QPushButton *buttonClose;

signals:
    void saveDisplayPage(int type);
	void escapeTabFocus(void);
	void closeSetupMenu(void);

public slots:

private slots:
	void onButtonCameraName(void);
	void onButtonVideoOutput(void);
	void onButtonOsd(void);
	void onButtonClose(void);

private:
    TextMessageDialog  *msgBox;
	CameraNameDialog   *cameraNameDialog;
	VideoOutputDialog  *videoOutputDialog;
	OsdDialog          *osdDialog;
};

#endif // DISPLAYPAGE_H
