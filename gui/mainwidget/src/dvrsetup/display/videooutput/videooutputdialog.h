#ifndef VIDEOOUTPUTDIALOG_H
#define VIDEOOUTPUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_videooutputdialog.h"
#include "ui_videooutputdialog1080p.h"
#include "textmessagebox/textmessagedialog.h"
#include "DVR.h"

class VideoOutputDialog;
class TextMessageDialog;
class NumKeypadDialog;

class VideoOutputDialog : public QDialog
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
    void onVideoOutputDefaultClicked(void);

protected:
    int indexCvbs;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    TextMessageDialog *msgBox;
    NumKeypadDialog *numKeypad;

    QFrame *frame;
    QPushButton *buttonHdmi;
    QPushButton *buttonCvbs;
    QPushButton *button_cvbs_x;
    QPushButton *button_cvbs_y;
    QPushButton *button_cvbs_width;
    QPushButton *button_cvbs_height;
    QPushButton *buttonDefault;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
};

#endif // VIDEOOUTPUTDIALOG_H
