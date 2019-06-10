#ifndef BUZZERDIALOG_H
#define BUZZERDIALOG_H

#include <QtGui/QDialog>
#include "ui_buzzerdialog.h"
#include "ui_buzzerdialog1080p.h"
#include "DVR.h"

class BuzzerDialog : public QDialog
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

    QFrame *frame;
    QPushButton *buttonBuzzer;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSave;
};

#endif // BUZZERDIALOG_H
