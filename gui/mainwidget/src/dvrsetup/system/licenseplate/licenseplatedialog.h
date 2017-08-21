#ifndef LICENSEPLATEDIALOG_H
#define LICENSEPLATEDIALOG_H

#include <QtGui/QDialog>
#include "ui_licenseplatedialog.h"
#include "DVR.h"

class LicensePlateDialog;
class UiKeyboardDialog;

class LicensePlateDialog : public QDialog, public Ui::LicensePlateDialog
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
};

#endif // LICENSEPLATEDIALOG_H
