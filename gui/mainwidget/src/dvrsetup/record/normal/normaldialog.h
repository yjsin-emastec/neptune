#ifndef NORMALDIALOG_H
#define NORMALDIALOG_H

#include <QtGui/QDialog>
#include "ui_normaldialog.h"
#include "DVR.h"

class NormalDialog : public QDialog, public Ui::NormalDialog
{
    Q_OBJECT

public:
    NormalDialog(QWidget *parent = 0);
    ~NormalDialog();
    void initNormalConfig(void);

signals:

public slots:
    void onButtonChannel(void);
    void onButtonFrameRate(void);
    void onButtonQuality(void);
    void onButtonRecording(void);
    void onButtonAudio(void);
    void onButtonDefault(void);
    void onButtonSave(void);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int indexChannel;
    int indexFrameRate;
    int indexQuality;
    int indexRecording;
    int indexAudio;
    int ChAllFrameRate;
    int ChAllQuality;
    int ChAllRecording;
    int ChAllAudio;

    int getMaxFrame(void);

};

#endif // NORMALDIALOG_H
