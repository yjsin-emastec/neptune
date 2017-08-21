#ifndef CAMERANAMEDIALOG_H
#define CAMERANAMEDIALOG_H

#include <QtGui/QDialog>
#include "ui_cameranamedialog.h"
#include "DVR.h"

class CameraNameDialog;
class UiKeyboardDialog;

class CameraNameDialog : public QDialog, public Ui::CameraNameDialog
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

};

#endif // CAMERANAMEDIALOG_H
