#ifndef SETDATETIMEDIALOG_H
#define SETDATETIMEDIALOG_H

#include <QtGui/QDialog>
#include "DVR.h"
#include "ui_setdatetimedialog.h"
#include "ui_setdatetimedialog1080p.h"

class TextMessageDialog;

class SetDateTimeDialog : public QDialog
{
    Q_OBJECT

public:
    SetDateTimeDialog(QWidget *parent = 0, int dateFormat = 0, cfg_dls_t *cfg = NULL);
    ~SetDateTimeDialog();
    void getChangedConfig(time_t *newTime, cfg_dls_t *cfg);

signals:

protected:
    void keyPressEvent(QKeyEvent *event);
    void changeComboBoxValue(int n);
    void changeDateTimeEditFocus(int n);

private slots:
    void onButtonTimeFormat();
    void onButtonGpsSync();
    void onButtonSave();
    void onButtonClose();

private:
    TextMessageDialog *msgBox;

    time_t beforeChageTime;

    int timeFormat;
    int infoTimeFormat, infoGpsSync;
    bool isKeyLock;

    void initComboBox();
    void enableSetTime();
    void checkTimeZone();
    void saveTimeZone();
    void saveDateTime();
    void getChangedTime(time_t *newTime);
    bool eventFilter(QObject *obj, QEvent *event);

    QFrame *layoutFrame;
    QPushButton *buttonTimeFormat;
    QPushButton *buttonGpsSync;
    QPushButton *buttonClose;
    QPushButton *buttonSave;
    QComboBox *comboBoxTimeZone;
    QDateTimeEdit *dateTimeEdit;
};

#endif // SETDATETIMEDIALOG_H
