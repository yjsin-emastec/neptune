#ifndef CAMERANAMEDIALOG_H
#define CAMERANAMEDIALOG_H

#include <QtGui/QDialog>
#include "ui_cameranamedialog.h"
#include "ui_cameranamedialog1080p.h"
#include "DVR.h"

class CameraNameDialog;
class UiKeyboardDialog;

class CameraNameDialog : public QDialog
{
    Q_OBJECT

public:
    CameraNameDialog(QWidget *parent = 0);
    ~CameraNameDialog();
	void initCameraNameConfig(void);

signals:

public slots:
    void onCameraName(int ch);
	void onCameraName1(void);
	void onCameraName2(void);
	void onCameraName3(void);
	void onCameraName4(void);
    void onCameraName5(void);
    void onCameraName6(void);
    void onCameraName7(void);
    void onCameraName8(void);

protected:
    void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	UiKeyboardDialog *keyboard;

    QFrame *frame;

    QLabel *labelCameraName[8];
    QLineEdit *lineEditName[8];
    QPushButton *buttonVirtualKeyboard[8];

    QPushButton *buttonSave;
    QPushButton *buttonClose;
};

#endif // CAMERANAMEDIALOG_H
