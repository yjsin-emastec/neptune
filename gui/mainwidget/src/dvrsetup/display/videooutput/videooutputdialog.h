#ifndef VIDEOOUTPUTDIALOG_H
#define VIDEOOUTPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_videooutputdialog.h"
#include "textmessagebox/textmessagedialog.h"
#include "DVR.h"

class VideoOutputDialog;
class TextMessageDialog;
class NumKeypadDialog;

class VideoOutputDialog : public QDialog, public Ui::VideoOutputDialog
{
    Q_OBJECT

public:
    VideoOutputDialog(QWidget *parent = 0);
    ~VideoOutputDialog();
    void initVideoOutputConfig(void);
    int oldHdmi;
    int indexHdmi;

signals:

 public slots:
    void onVideoOutputHdmi(void);
    void onVideoOutputCvbs(void);
    void onVideoOutput_xClicked(void);
    void onVideoOutput_yClicked(void);
    void onVideoOutput_widthClicked(void);
    void onVideoOutput_heightClicked(void);
    void onVideoOutputSaveClicked(void);

protected:
    int indexCvbs;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    TextMessageDialog *msgBox;
    NumKeypadDialog *numKeypad;
};

#endif // VIDEOOUTPUTDIALOG_H
