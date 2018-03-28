#ifndef RECORDSTATUS_H
#define RECORDSTATUS_H

#include <QtGui/QDialog>
#include "ui_recordstatus.h"
#include "DVR.h"

class RecordStatus : public QDialog, public Ui::RecordStatus
{
    Q_OBJECT

public:
    RecordStatus(QWidget *parent = 0);
    ~RecordStatus();
    void updateRecordStatus(void);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int indexChannel;
    int indexFrameRate;
    int indexQuality;
    int indexRecording;
    int indexAudio;

};

#endif // RECORDSTATUS_H
