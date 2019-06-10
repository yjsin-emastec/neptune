#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QtGui/QDialog>
#include "ui_informationdialog.h"
#include "ui_informationdialog1080p.h"
#include "DVR.h"

class InformationDialog;
class UiKeyboardDialog;

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    InformationDialog(QWidget *parent = 0);
    ~InformationDialog();
    void initInformationConfig(void);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QTimer             *updateTimer;
    disk_used_info_t    diskInfo;

    QFrame *frame;
    QLabel *labelLicensePlate;
    QLabel *labelLicensePlate2;
    QLabel *labelModelName;
    QLabel *labelModelName2;
    QLabel *labelVersion;
    QLabel *labelVersion2;
    QLabel *labelHddSize;
    QLabel *labelNormalSize2;
    QLabel *labelEventSize2;
    QLabel *labelDVRTemperature;
    QLabel *labelDVRTemperature2;
    QLabel *labelDiskTemperature;
    QLabel *labelGps;
    QLabel *labelGps2;
    QPushButton *buttonClose;

private slots:
    void onUpdateStatus(void);
    void onClose(void);
};

#endif // INFORMATIONDIALOG_H
