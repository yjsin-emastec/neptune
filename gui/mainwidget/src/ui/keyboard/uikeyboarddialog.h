#ifndef UIKEYBOARDDIALOG_H
#define UIKEYBOARDDIALOG_H

#include <QDialog>

namespace Ui {
    class UiKeyboardDialog;
}

class UiKeyboardDialog : public QDialog
{
Q_OBJECT

public:
    explicit UiKeyboardDialog(QWidget *parent = 0);
    ~UiKeyboardDialog();
    void setKeyboadProperty(QString strLabel, QString strPrev = tr(""), bool isPassword = false, int maxLen = -1);
    void disableCapsShift();
    void disablePunctuation();
    void disableSpace();
    void setNumberLowerAlphabetOnly();
    void buttonShift(bool shift);
    QString text;
    QString title;
    int maxCharCount;
    void updateKeyboard();
    void setPasswordMode(int mode);
    void buttonPressed(QString string);
    bool capsStatus;
    bool shiftStatus;

signals:
    void signalResetTimer();

private:
    Ui::UiKeyboardDialog *ui;
    void disableForbiddenChar();

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_hyphen_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_backspace_clicked();

    void on_pushButton_a_clicked();
    void on_pushButton_b_clicked();
    void on_pushButton_c_clicked();
    void on_pushButton_d_clicked();
    void on_pushButton_e_clicked();
    void on_pushButton_f_clicked();
    void on_pushButton_g_clicked();
    void on_pushButton_h_clicked();
    void on_pushButton_i_clicked();
    void on_pushButton_j_clicked();
    void on_pushButton_k_clicked();
    void on_pushButton_l_clicked();
    void on_pushButton_m_clicked();
    void on_pushButton_n_clicked();
    void on_pushButton_o_clicked();
    void on_pushButton_p_clicked();
    void on_pushButton_q_clicked();
    void on_pushButton_v_clicked();
    void on_pushButton_r_clicked();
    void on_pushButton_s_clicked();
    void on_pushButton_t_clicked();
    void on_pushButton_u_clicked();
    void on_pushButton_w_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_y_clicked();
    void on_pushButton_z_clicked();

    void on_pushButton_shift_left_clicked();
    void on_pushButton_space_clicked();
    void on_pushButton_comma_clicked();
    void on_pushButton_period_clicked();
    void on_pushButton_forward_slash_clicked();

    void on_pushButton_clear_clicked();
    void on_pushButton_enter_clicked();
    void on_pushButton_close_clicked();
};

#endif // UIKEYBOARDDIALOG_H
