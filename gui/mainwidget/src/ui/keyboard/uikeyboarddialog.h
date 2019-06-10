#ifndef UIKEYBOARDDIALOG_H
#define UIKEYBOARDDIALOG_H

#include <QDialog>
#include "ui_uikeyboarddialog.h"
#include "ui_uikeyboarddialog1080p.h"

class UiKeyboardDialog : public QDialog
{
Q_OBJECT

public:
    explicit UiKeyboardDialog(QWidget *parent = 0);
    ~UiKeyboardDialog();
    void setKeyboadProperty(QString strLabel, QString strPrev = tr(""), bool isPassword = false, int maxLen = -1);
    QString text;

signals:
    void signalResetTimer();

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
    void on_pushButton_clear_clicked();
    void on_pushButton_enter_clicked();
    void on_pushButton_close_clicked();

private:
    void disableForbiddenChar();
    void updateButtonShift();
    void disableCapsShift();
    void disableSpecialLetter();
    void setNumberLowerAlphabetOnly();
    void updateKeyboard();
    void setPasswordMode(int mode);
    void buttonPressed(QString string);

    QString title;
    int maxCharCount;
    int shiftStatus;

    QFrame *frame;
    QPushButton *pushButton_0;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_backspace;
    QPushButton *pushButton_hyphen;
    QPushButton *pushButton_a;
    QPushButton *pushButton_b;
    QPushButton *pushButton_c;
    QPushButton *pushButton_d;
    QPushButton *pushButton_e;
    QPushButton *pushButton_f;
    QPushButton *pushButton_g;
    QPushButton *pushButton_h;
    QPushButton *pushButton_i;
    QPushButton *pushButton_j;
    QPushButton *pushButton_k;
    QPushButton *pushButton_l;
    QPushButton *pushButton_m;
    QPushButton *pushButton_n;
    QPushButton *pushButton_o;
    QPushButton *pushButton_p;
    QPushButton *pushButton_q;
    QPushButton *pushButton_r;
    QPushButton *pushButton_s;
    QPushButton *pushButton_t;
    QPushButton *pushButton_u;
    QPushButton *pushButton_v;
    QPushButton *pushButton_w;
    QPushButton *pushButton_x;
    QPushButton *pushButton_y;
    QPushButton *pushButton_z;
    QPushButton *pushButton_shift_left;
    QPushButton *pushButton_shift_right;
    QPushButton *pushButton_space;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_close;
    QPushButton *pushButton_enter;
    QLineEdit *label_text;
};

#endif // UIKEYBOARDDIALOG_H
