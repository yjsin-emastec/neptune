#ifndef VIDEOINPUTDIALOG_H
#define VIDEOINPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_videoinputdialog.h"
#include "ui_videoinputdialog1080p.h"
#include "DVR.h"

class VideoInputDialog : public QDialog
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

    QFrame *frame;
    QPushButton *buttonCamera;
    QPushButton *buttonMirror;
    QPushButton *buttonNotAvailable;
    QPushButton *buttonFlip;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
};

#endif // VIDEOINPUTDIALOG_H
