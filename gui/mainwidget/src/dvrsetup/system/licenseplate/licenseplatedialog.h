#ifndef LICENSEPLATEDIALOG_H
#define LICENSEPLATEDIALOG_H

#include <QtGui/QDialog>
#include "ui_licenseplatedialog.h"
#include "ui_licenseplatedialog1080p.h"
#include "DVR.h"

class LicensePlateDialog;
class UiKeyboardDialog;

class LicensePlateDialog : public QDialog
{
    Q_OBJECT

public:
    LicensePlateDialog(QWidget *parent = 0);
    ~LicensePlateDialog();
	void initLicensePlateConfig(void);

signals:
	;

public slots:
	void onButtonLicensePlate(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	UiKeyboardDialog *keyboard;

    QFrame *frame;
    QLabel *labelLicensePlate;
    QLineEdit *lineEditLicensePlate;
    QPushButton *buttonLicensePlate;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonClose;
};

#endif // LICENSEPLATEDIALOG_H
