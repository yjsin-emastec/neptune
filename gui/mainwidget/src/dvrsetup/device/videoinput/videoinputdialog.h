#ifndef VIDEOINPUTDIALOG_H
#define VIDEOINPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_videoinputdialog.h"
#include "DVR.h"

class VideoInputDialog : public QDialog, public Ui::VideoInputDialog
{
    Q_OBJECT

public:
    VideoInputDialog(QWidget *parent = 0);
    ~VideoInputDialog();
	void initVideoInputConfig(void);

signals:

public slots:
	void onButtonCamera(void);
	void onButtonMirror(void);
	void onButtonFlip(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	int indexCamera;
	int indexMirror;
	int indexFlip;
};

#endif // VIDEOINPUTDIALOG_H
