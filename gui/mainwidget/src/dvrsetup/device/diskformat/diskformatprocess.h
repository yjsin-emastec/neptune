#ifndef DISKFORMATPROCESS_H
#define DISKFORMATPROCESS_H

#include <QtGui/QDialog>
#include <DVR.h>
#include "ui_diskformatprocess.h"

class QLabel;
class QProgressBar;
class QPushButton;

class DiskFormatProcessDialog : public QDialog, public Ui::DiskFormatProcessDialog
{
    Q_OBJECT

public:
    DiskFormatProcessDialog        (QWidget *parent = 0);
    ~DiskFormatProcessDialog       (void);

    QTimer *formatTimer;

    void TestDiskFormatInit        (void);
    void DiskFormatInit            (void);
    void StartFormat               (void);
    void StartTimer                (void);

signals:
    void diskformatReboot          (void);

public slots:
    void onDiskFormatupdateprocess (int disk, unsigned long total, unsigned long percent, unsigned long remain_time);
    void onDiskFormatupdateEnd     (void);

protected:

private slots:
    void onDiskformatupdate        (void);
    void onSystemReboot            (void);

private:
    QPushButton       *buttonStart,
                      *buttonCancel,
                      *buttonSystemReboot;

    QProgressBar      *diskformatProgressBar;

    QLabel            *labelStatus;

    disk_used_info_t   diskInfo[MAX_HDD_COUNT];

    time_t             totalTime;

    unsigned int       ProgressValue;
};
#endif // DISKFORMATPROCESS_H
