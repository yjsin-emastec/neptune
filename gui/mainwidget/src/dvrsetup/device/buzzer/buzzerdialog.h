#ifndef BUZZERDIALOG_H
#define BUZZERDIALOG_H

#include <QtGui/QDialog>
#include "ui_buzzerdialog.h"
#include "DVR.h"

class BuzzerDialog : public QDialog, public Ui::BuzzerDialog
{
    Q_OBJECT

public:
    BuzzerDialog(QWidget *parent = 0);
    ~BuzzerDialog();
	void initBuzzerConfig(void);

signals:

public slots:
	void onButtonBuzzer(void);

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	int indexBuzzer;
};

#endif // BUZZERDIALOG_H
