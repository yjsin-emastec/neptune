#include "uikeyboarddialog.h"
#include "ui_uikeyboarddialog.h"
#include <QtGui>

UiKeyboardDialog::UiKeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UiKeyboardDialog)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    ui->setupUi(this);
    ui->label_text->setText(text);

    text                       = "";
    maxCharCount               = 16;
    capsStatus                 = false;
    shiftStatus                = false;

    ui->frame_Body->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    ui->frame_Border->setStyleSheet(".QFrame{background: rgb(255, 128, 64);}");
    ui->label_text->setStyleSheet("QLineEdit{font:48px;background-color:rgb(50,57,83);color:white;border-width:1px;border-style:inset;border-color:white;}");

    ui->pushButton_0->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_1->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_2->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_3->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_4->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_5->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_6->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_7->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_8->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_9->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_hyphen->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_equal->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

    ui->pushButton_a->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_b->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_c->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_d->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_e->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_f->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_g->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_h->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_i->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_j->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_k->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_l->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_m->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

    ui->pushButton_n->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_o->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_p->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_q->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_r->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_s->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_t->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_u->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_v->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_w->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_x->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_y->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_z->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

    ui->pushButton_comma->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_period->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    ui->pushButton_forward_slash->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

    ui->pushButton_enter->setFocus();
}
UiKeyboardDialog::~UiKeyboardDialog()
{
    delete ui;
}
void UiKeyboardDialog::setKeyboadProperty(QString strLabel, QString strPrev, bool isPassword, int maxLen)
{
    this->title = strLabel;
    this->text  = strPrev;

    if(isPassword)
    {
        this->setPasswordMode(1);
    }
    else
    {
        this->setPasswordMode(0);
    }

    this->maxCharCount = maxLen;
    this->updateKeyboard();
}
void UiKeyboardDialog::updateKeyboard()
{
    ui->label_text->setText(text);
}
void UiKeyboardDialog::setPasswordMode(int mode)
{
    if(mode)
    {
        ui->label_text->setEchoMode(QLineEdit::Password);
    }
    else
    {
        ui->label_text->setEchoMode(QLineEdit::Normal);
    }
}
void UiKeyboardDialog::buttonPressed(QString string)
{
    emit signalResetTimer();

    if((text.length() + string.length()) <= maxCharCount)
    {
        text = text + string;
        ui->label_text->setText(text);
    }

    if(shiftStatus)
    {
        shiftStatus = false;
        buttonShift(capsStatus);
    }
}
void UiKeyboardDialog::on_pushButton_1_clicked()
{
    ui->pushButton_1->setFocus();
    buttonPressed(ui->pushButton_1->text());
}
void UiKeyboardDialog::on_pushButton_2_clicked()
{
    ui->pushButton_2->setFocus();
    buttonPressed(ui->pushButton_2->text());
}
void UiKeyboardDialog::on_pushButton_3_clicked()
{
    ui->pushButton_3->setFocus();
    buttonPressed(ui->pushButton_3->text());
}
void UiKeyboardDialog::on_pushButton_4_clicked()
{
    ui->pushButton_4->setFocus();
    buttonPressed(ui->pushButton_4->text());
}
void UiKeyboardDialog::on_pushButton_5_clicked()
{
    ui->pushButton_5->setFocus();
    buttonPressed(ui->pushButton_5->text());
}
void UiKeyboardDialog::on_pushButton_6_clicked()
{
    ui->pushButton_6->setFocus();
    buttonPressed(ui->pushButton_6->text());
}
void UiKeyboardDialog::on_pushButton_7_clicked()
{
    ui->pushButton_7->setFocus();
    buttonPressed(ui->pushButton_7->text());
}
void UiKeyboardDialog::on_pushButton_8_clicked()
{
    ui->pushButton_8->setFocus();
    buttonPressed(ui->pushButton_8->text());
}
void UiKeyboardDialog::on_pushButton_9_clicked()
{
    ui->pushButton_9->setFocus();
    buttonPressed(ui->pushButton_9->text());
}
void UiKeyboardDialog::on_pushButton_0_clicked()
{
    ui->pushButton_0->setFocus();
    buttonPressed(ui->pushButton_0->text());
}
void UiKeyboardDialog::on_pushButton_hyphen_clicked()
{
    ui->pushButton_hyphen->setFocus();
    buttonPressed(ui->pushButton_hyphen->text());
}
void UiKeyboardDialog::on_pushButton_equal_clicked()
{
#if 0 // GyverJeong [17/12/22]
    ui->pushButton_equal->setFocus();
    buttonPressed(ui->pushButton_equal->text());
#endif
}
void UiKeyboardDialog::on_pushButton_backspace_clicked()
{
    emit signalResetTimer();

    ui->pushButton_backspace->setFocus();

    text.chop(1);

    ui->label_text->setText(text);
}
void UiKeyboardDialog::on_pushButton_a_clicked()
{
    ui->pushButton_a->setFocus();
    buttonPressed(ui->pushButton_a->text());
}
void UiKeyboardDialog::on_pushButton_b_clicked()
{
    ui->pushButton_b->setFocus();
    buttonPressed(ui->pushButton_b->text());
}
void UiKeyboardDialog::on_pushButton_c_clicked()
{
    ui->pushButton_c->setFocus();
    buttonPressed(ui->pushButton_c->text());
}
void UiKeyboardDialog::on_pushButton_d_clicked()
{
    ui->pushButton_d->setFocus();
    buttonPressed(ui->pushButton_d->text());
}
void UiKeyboardDialog::on_pushButton_e_clicked()
{
    ui->pushButton_e->setFocus();
    buttonPressed(ui->pushButton_e->text());
}
void UiKeyboardDialog::on_pushButton_f_clicked()
{
    ui->pushButton_f->setFocus();
    buttonPressed(ui->pushButton_f->text());
}
void UiKeyboardDialog::on_pushButton_g_clicked()
{
    ui->pushButton_g->setFocus();
    buttonPressed(ui->pushButton_g->text());
}
void UiKeyboardDialog::on_pushButton_h_clicked()
{
    ui->pushButton_h->setFocus();
    buttonPressed(ui->pushButton_h->text());
}
void UiKeyboardDialog::on_pushButton_i_clicked()
{
    ui->pushButton_i->setFocus();
    buttonPressed(ui->pushButton_i->text());
}
void UiKeyboardDialog::on_pushButton_j_clicked()
{
    ui->pushButton_j->setFocus();
    buttonPressed(ui->pushButton_j->text());
}
void UiKeyboardDialog::on_pushButton_k_clicked()
{
    ui->pushButton_k->setFocus();
    buttonPressed(ui->pushButton_k->text());
}
void UiKeyboardDialog::on_pushButton_l_clicked()
{
    ui->pushButton_l->setFocus();
    buttonPressed(ui->pushButton_l->text());
}
void UiKeyboardDialog::on_pushButton_m_clicked()
{
    ui->pushButton_m->setFocus();
    buttonPressed(ui->pushButton_m->text());
}
void UiKeyboardDialog::on_pushButton_n_clicked()
{
    ui->pushButton_n->setFocus();
    buttonPressed(ui->pushButton_n->text());
}
void UiKeyboardDialog::on_pushButton_o_clicked()
{
    ui->pushButton_o->setFocus();
    buttonPressed(ui->pushButton_o->text());
}
void UiKeyboardDialog::on_pushButton_p_clicked()
{
    ui->pushButton_p->setFocus();
    buttonPressed(ui->pushButton_p->text());
}
void UiKeyboardDialog::on_pushButton_q_clicked()
{
    ui->pushButton_q->setFocus();
    buttonPressed(ui->pushButton_q->text());
}
void UiKeyboardDialog::on_pushButton_r_clicked()
{
    ui->pushButton_r->setFocus();
    buttonPressed(ui->pushButton_r->text());
}
void UiKeyboardDialog::on_pushButton_s_clicked()
{
    ui->pushButton_s->setFocus();
    buttonPressed(ui->pushButton_s->text());
}
void UiKeyboardDialog::on_pushButton_t_clicked()
{
    ui->pushButton_t->setFocus();
    buttonPressed(ui->pushButton_t->text());
}
void UiKeyboardDialog::on_pushButton_u_clicked()
{
    ui->pushButton_u->setFocus();
    buttonPressed(ui->pushButton_u->text());
}
void UiKeyboardDialog::on_pushButton_v_clicked()
{
    ui->pushButton_v->setFocus();
    buttonPressed(ui->pushButton_v->text());
}
void UiKeyboardDialog::on_pushButton_w_clicked()
{
    ui->pushButton_w->setFocus();
    buttonPressed(ui->pushButton_w->text());
}
void UiKeyboardDialog::on_pushButton_x_clicked()
{
    ui->pushButton_x->setFocus();
    buttonPressed(ui->pushButton_x->text());
}
void UiKeyboardDialog::on_pushButton_y_clicked()
{
    ui->pushButton_y->setFocus();
    buttonPressed(ui->pushButton_y->text());
}
void UiKeyboardDialog::on_pushButton_z_clicked()
{
    ui->pushButton_z->setFocus();
    buttonPressed(ui->pushButton_z->text());
}
void UiKeyboardDialog::buttonShift(bool shift)
{
    if(shift)
    {
        ui->pushButton_1->setText("!");
        ui->pushButton_2->setText("@");
        ui->pushButton_3->setText("#");
        ui->pushButton_4->setText("$");
        ui->pushButton_5->setText("%");
        ui->pushButton_6->setText("^");
        ui->pushButton_7->setText("");
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setText("*");
        ui->pushButton_9->setText("(");
        ui->pushButton_0->setText(")");
        ui->pushButton_hyphen->setText("_");
#if 0 // GyverJeong [17/12/22]
        ui->pushButton_equal->setText("+");
#endif

        ui->pushButton_a->setText("A");
        ui->pushButton_b->setText("B");
        ui->pushButton_c->setText("C");
        ui->pushButton_d->setText("D");
        ui->pushButton_e->setText("E");
        ui->pushButton_f->setText("F");
        ui->pushButton_g->setText("G");
        ui->pushButton_h->setText("H");
        ui->pushButton_i->setText("I");
        ui->pushButton_j->setText("J");
        ui->pushButton_k->setText("K");
        ui->pushButton_l->setText("L");
        ui->pushButton_m->setText("M");

        ui->pushButton_n->setText("N");
        ui->pushButton_o->setText("O");
        ui->pushButton_p->setText("P");
        ui->pushButton_q->setText("Q");
        ui->pushButton_r->setText("R");
        ui->pushButton_s->setText("S");
        ui->pushButton_t->setText("T");
        ui->pushButton_u->setText("U");
        ui->pushButton_v->setText("V");
        ui->pushButton_w->setText("W");
        ui->pushButton_x->setText("X");
        ui->pushButton_y->setText("Y");
        ui->pushButton_z->setText("Z");

#if 0 // GyverJeong [17/12/22]
        ui->pushButton_comma->setText(",");
        ui->pushButton_period->setText(".");
        ui->pushButton_forward_slash->setText("?");
#endif
    }
    else
    {
        ui->pushButton_1->setText("1");
        ui->pushButton_2->setText("2");
        ui->pushButton_3->setText("3");
        ui->pushButton_4->setText("4");
        ui->pushButton_5->setText("5");
        ui->pushButton_6->setText("6");
        ui->pushButton_7->setText("7");
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setText("8");
        ui->pushButton_9->setText("9");
        ui->pushButton_0->setText("0");
        ui->pushButton_hyphen->setText("-");
#if 0 // GyverJeong [17/12/22]
        ui->pushButton_equal->setText("=");
#endif

        ui->pushButton_a->setText("a");
        ui->pushButton_b->setText("b");
        ui->pushButton_c->setText("c");
        ui->pushButton_d->setText("d");
        ui->pushButton_e->setText("e");
        ui->pushButton_f->setText("f");
        ui->pushButton_g->setText("g");
        ui->pushButton_h->setText("h");
        ui->pushButton_i->setText("i");
        ui->pushButton_j->setText("j");
        ui->pushButton_k->setText("k");
        ui->pushButton_l->setText("l");
        ui->pushButton_m->setText("m");

        ui->pushButton_n->setText("n");
        ui->pushButton_o->setText("o");
        ui->pushButton_p->setText("p");
        ui->pushButton_q->setText("q");
        ui->pushButton_r->setText("r");
        ui->pushButton_s->setText("s");
        ui->pushButton_t->setText("t");
        ui->pushButton_u->setText("u");
        ui->pushButton_v->setText("v");
        ui->pushButton_w->setText("w");
        ui->pushButton_x->setText("x");
        ui->pushButton_y->setText("y");
        ui->pushButton_z->setText("z");

#if 0 // GyverJeong [17/12/22]
        ui->pushButton_comma->setText(",");
        ui->pushButton_period->setText(".");
        ui->pushButton_forward_slash->setText("/");
#endif
    }

    disableForbiddenChar();
}
void UiKeyboardDialog::on_pushButton_space_clicked()
{
    ui->pushButton_space->setFocus();
    buttonPressed(" ");
}
void UiKeyboardDialog::on_pushButton_comma_clicked()
{
#if 0 // GyverJeong [17/12/22]
    ui->pushButton_comma->setFocus();
    buttonPressed(ui->pushButton_comma->text());
#endif
}
void UiKeyboardDialog::on_pushButton_period_clicked()
{
#if 0 // GyverJeong [17/12/22]
    ui->pushButton_period->setFocus();
    buttonPressed(ui->pushButton_period->text());
#endif
}
void UiKeyboardDialog::on_pushButton_forward_slash_clicked()
{
#if 0 // GyverJeong [17/12/22]
    ui->pushButton_forward_slash->setFocus();
    buttonPressed(ui->pushButton_forward_slash->text());
#endif
}
void UiKeyboardDialog::on_pushButton_clear_clicked()
{
    emit signalResetTimer();
    ui->pushButton_clear->setFocus();
    text = "";
    ui->label_text->setText(text);
}
void UiKeyboardDialog::on_pushButton_enter_clicked()
{
    emit signalResetTimer();

    ui->pushButton_enter->setFocus();

    capsStatus  = false;
    shiftStatus = false;

    buttonShift(false);

    ui->pushButton_clear->setEnabled(true);
    ui->pushButton_clear->setText("CLEAR");

    accept();
}
void UiKeyboardDialog::on_pushButton_close_clicked()
{
    emit signalResetTimer();

    ui->pushButton_close->setFocus();

    capsStatus  = false;
    shiftStatus = false;

    buttonShift(false);

    ui->pushButton_clear->setEnabled(true);
    ui->pushButton_clear->setText("CLEAR");

    reject();
}
void UiKeyboardDialog::on_pushButton_shift_left_clicked()
{
    emit signalResetTimer();

    ui->pushButton_shift_left->setFocus();

    if(shiftStatus==true)
    {
        shiftStatus = false;
    }
    else
    {
        shiftStatus = true;
    }

    buttonShift(capsStatus ^ shiftStatus);
}
void UiKeyboardDialog::disableCapsShift()
{
    ui->pushButton_shift_left->setEnabled(false);
}
void UiKeyboardDialog::disablePunctuation()
{
    ui->pushButton_hyphen->setEnabled(false);
    ui->pushButton_equal->setEnabled(false);
    ui->pushButton_comma->setEnabled(false);
    ui->pushButton_forward_slash->setEnabled(false);
}
void UiKeyboardDialog::disableSpace()
{
    ui->pushButton_space->setEnabled(false);
}
void UiKeyboardDialog::setNumberLowerAlphabetOnly()
{
    disableCapsShift();
    disablePunctuation();
    disableSpace();
}
void UiKeyboardDialog::disableForbiddenChar()
{
    if(!(capsStatus ^ shiftStatus))
    {
        ui->pushButton_4->setEnabled(true);  // $
        ui->pushButton_6->setEnabled(true);  // ^
        ui->pushButton_8->setEnabled(true);  // *
        ui->pushButton_9->setEnabled(true);  // (
        ui->pushButton_0->setEnabled(true);  // )
#if 1 // GyverJeong [17/12/22]
        ui->pushButton_equal->setEnabled(false);  // +
        ui->pushButton_comma->setEnabled(false);
        ui->pushButton_period->setEnabled(false);
        ui->pushButton_forward_slash->setEnabled(false);  // ?
#else
        ui->pushButton_equal->setEnabled(true);  // +
        ui->pushButton_forward_slash->setEnabled(true);  // ?
#endif
        ui->pushButton_4->setText("4");  // $
        ui->pushButton_6->setText("6");  // ^
        ui->pushButton_8->setText("8");  // *
        ui->pushButton_9->setText("9");  // (
        ui->pushButton_0->setText("0");  // )
#if 1 // GyverJeong [17/12/22]
        ui->pushButton_equal->setText("");  // +
        ui->pushButton_comma->setText("");
        ui->pushButton_period->setText("");
        ui->pushButton_forward_slash->setText("");  // ?
#else
        ui->pushButton_equal->setText("=");  // +
        ui->pushButton_forward_slash->setText("/");  // ?
#endif
    }

    if(capsStatus ^ shiftStatus)
    {
        ui->pushButton_4->setEnabled(false);  // $
        ui->pushButton_6->setEnabled(false);  // ^
        ui->pushButton_8->setEnabled(false);  // *
        ui->pushButton_9->setEnabled(false);  // (
        ui->pushButton_0->setEnabled(false);  // )
        ui->pushButton_equal->setEnabled(false);  // +
#if 1 // GyverJeong [17/12/22]
        ui->pushButton_comma->setEnabled(false);
        ui->pushButton_period->setEnabled(false);
#endif
        ui->pushButton_forward_slash->setEnabled(false);  // ?
        ui->pushButton_4->setText("");  // $
        ui->pushButton_6->setText("");  // ^
        ui->pushButton_8->setText("");  // *
        ui->pushButton_9->setText("");  // (
        ui->pushButton_0->setText("");  // )
        ui->pushButton_equal->setText("");  // +
#if 1 // GyverJeong [17/12/22]
        ui->pushButton_comma->setText("");
        ui->pushButton_period->setText("");
#endif
        ui->pushButton_forward_slash->setText("");  // ?
    }
}
