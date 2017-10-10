#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QtGui/QDialog>
#include "ui_informationdialog.h"
#include "DVR.h"

class InformationDialog;
class UiKeyboardDialog;

class InformationDialog : public QDialog, public Ui::InformationDialog
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

private slots:
    void onUpdateStatus(void);
    void onClose(void);
};

#endif // INFORMATIONDIALOG_H
