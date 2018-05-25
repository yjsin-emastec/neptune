#ifndef SETDATETIMEDIALOG_H
#define SETDATETIMEDIALOG_H

#include <QtGui/QDialog>
#include "DVR.h"
#include "ui_setdatetimedialog.h"

class TextMessageDialog;

class SetDateTimeDialog : public QDialog, public Ui::SetDateTimeDialog
{
    Q_OBJECT

public:
    SetDateTimeDialog(QWidget *parent = 0, int dateFormat = 0, cfg_dls_t *cfg = NULL);
    ~SetDateTimeDialog();
    void getChangedConfig(time_t *newTime, cfg_dls_t *cfg);

signals:
    void signalResetTimer();

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_comboBoxTime_6_currentIndexChanged(int index);
    void on_comboBoxTime_5_currentIndexChanged(int index);
    void on_comboBoxTime_4_currentIndexChanged(int index);
    void on_comboBoxEndHour_currentIndexChanged(int index);
    void on_comboBoxEndDay_currentIndexChanged(int index);
    void on_comboBoxEndWeek_currentIndexChanged(int index);
    void on_comboBoxEndMonth_currentIndexChanged(int index);
    void on_comboBoxBeginHour_currentIndexChanged(int index);
    void on_comboBoxBeginDay_currentIndexChanged(int index);
    void on_comboBoxBeginWeek_currentIndexChanged(int index);
    void on_comboBoxBeginMonth_currentIndexChanged(int index);
    void changeDlsType(int dls);
    void enableSetTime();
    void checkChangeTime();
    void time1Changed(int val);
    void time2Changed(int val);
    void time3Changed(int val);
    void onButtonTimeFormat(void);
    void onButtonGpsSync(void);

private:
    void initComboBox();
    void getChangedTime(time_t *newTime);
    void changeFocusedItemValue(int isPlus);
    void monthDayCheck(int type);
    void resetHour();
    void checkTimezone();
    void setTimezone();
    void setTimeFormat();
    cfg_dls_t cfgDls;
    int timeFormat, dlsZone;
    bool bOnce;
    TextMessageDialog *msgBox;
    int indexTimeFormat, indexGpsSync;
    time_t oldTime;
    int isKeyLock;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SETDATETIMEDIALOG_H
