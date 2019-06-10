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
	;

public slots:
	void onCameraName1(void);
	void onCameraName2(void);
	void onCameraName3(void);
	void onCameraName4(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	UiKeyboardDialog *keyboard;

    QFrame *frame;
    QLabel *labelCameraName1;
    QLabel *labelCameraName2;
    QLabel *labelCameraName3;
    QLabel *labelCameraName4;
    QLineEdit *lineEditName1;
    QLineEdit *lineEditName2;
    QLineEdit *lineEditName3;
    QLineEdit *lineEditName4;
    QPushButton *buttonVirtualKeyboard1;
    QPushButton *buttonVirtualKeyboard2;
    QPushButton *buttonVirtualKeyboard3;
    QPushButton *buttonVirtualKeyboard4;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
};

#endif // CAMERANAMEDIALOG_H
