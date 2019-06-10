#include "uikeyboarddialog.h"
#include "main/mainglobal.h"
#include <QtGui>

UiKeyboardDialog::UiKeyboardDialog(QWidget *parent) :
    QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::UiKeyboardDialog ui720;
        ui720.setupUi(this);

        frame = ui720.frame;
        pushButton_0 = ui720.pushButton_0;
        pushButton_1 = ui720.pushButton_1;
        pushButton_2 = ui720.pushButton_2;
        pushButton_3 = ui720.pushButton_3;
        pushButton_4 = ui720.pushButton_4;
        pushButton_5 = ui720.pushButton_5;
        pushButton_6 = ui720.pushButton_6;
        pushButton_7 = ui720.pushButton_7;
        pushButton_8 = ui720.pushButton_8;
        pushButton_9 = ui720.pushButton_9;
        pushButton_backspace = ui720.pushButton_backspace;
        pushButton_a = ui720.pushButton_a;
        pushButton_b = ui720.pushButton_b;
        pushButton_c = ui720.pushButton_c;
        pushButton_d = ui720.pushButton_d;
        pushButton_e = ui720.pushButton_e;
        pushButton_f = ui720.pushButton_f;
        pushButton_g = ui720.pushButton_g;
        pushButton_h = ui720.pushButton_h;
        pushButton_i = ui720.pushButton_i;
        pushButton_j = ui720.pushButton_j;
        pushButton_k = ui720.pushButton_k;
        pushButton_l = ui720.pushButton_l;
        pushButton_m = ui720.pushButton_m;
        pushButton_n = ui720.pushButton_n;
        pushButton_o = ui720.pushButton_o;
        pushButton_p = ui720.pushButton_p;
        pushButton_q = ui720.pushButton_q;
        pushButton_r = ui720.pushButton_r;
        pushButton_s = ui720.pushButton_s;
        pushButton_t = ui720.pushButton_t;
        pushButton_u = ui720.pushButton_u;
        pushButton_v = ui720.pushButton_v;
        pushButton_w = ui720.pushButton_w;
        pushButton_x = ui720.pushButton_x;
        pushButton_y = ui720.pushButton_y;
        pushButton_z = ui720.pushButton_z;
        pushButton_hyphen = ui720.pushButton_hyphen;
        pushButton_shift_left = ui720.pushButton_shift_left;
        pushButton_shift_right = ui720.pushButton_shift_right;
        pushButton_space = ui720.pushButton_space;
        pushButton_clear = ui720.pushButton_clear;
        pushButton_close = ui720.pushButton_close;
        pushButton_enter = ui720.pushButton_enter;
        label_text = ui720.label_text;

        frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
        pushButton_0->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_1->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_2->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_3->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_4->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_5->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_6->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_7->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_8->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_9->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

        pushButton_a->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_b->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_c->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_d->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_e->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_f->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_g->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_h->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_i->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_j->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_k->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_l->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_m->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_n->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_o->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_p->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_q->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_r->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_s->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_t->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_u->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_v->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_w->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_x->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_y->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_z->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_hyphen->setStyleSheet("QPushButton{font:48px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

        label_text->setStyleSheet("QLineEdit{font:65px;background-color:rgb(50,57,83);color:white;border-width:1px;border-style:inset;border-color:white;}");
        pushButton_shift_left->setStyleSheet("QPushButton{font:48px;background:rgb(67,74,86);} QPushButton:focus{color:white;background:rgb(152,14,69);}");

        //yjsin [19/02/21] if text is long, change button font size
        if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            pushButton_shift_left->setStyleSheet("font:40px;");
        }
    }
    else
    {
        Ui::UiKeyboardDialog1080p ui1080;
        ui1080.setupUi(this);

        frame = ui1080.frame;
        pushButton_0 = ui1080.pushButton_0;
        pushButton_1 = ui1080.pushButton_1;
        pushButton_2 = ui1080.pushButton_2;
        pushButton_3 = ui1080.pushButton_3;
        pushButton_4 = ui1080.pushButton_4;
        pushButton_5 = ui1080.pushButton_5;
        pushButton_6 = ui1080.pushButton_6;
        pushButton_7 = ui1080.pushButton_7;
        pushButton_8 = ui1080.pushButton_8;
        pushButton_9 = ui1080.pushButton_9;
        pushButton_backspace = ui1080.pushButton_backspace;
        pushButton_a = ui1080.pushButton_a;
        pushButton_b = ui1080.pushButton_b;
        pushButton_c = ui1080.pushButton_c;
        pushButton_d = ui1080.pushButton_d;
        pushButton_e = ui1080.pushButton_e;
        pushButton_f = ui1080.pushButton_f;
        pushButton_g = ui1080.pushButton_g;
        pushButton_h = ui1080.pushButton_h;
        pushButton_i = ui1080.pushButton_i;
        pushButton_j = ui1080.pushButton_j;
        pushButton_k = ui1080.pushButton_k;
        pushButton_l = ui1080.pushButton_l;
        pushButton_m = ui1080.pushButton_m;
        pushButton_n = ui1080.pushButton_n;
        pushButton_o = ui1080.pushButton_o;
        pushButton_p = ui1080.pushButton_p;
        pushButton_q = ui1080.pushButton_q;
        pushButton_r = ui1080.pushButton_r;
        pushButton_s = ui1080.pushButton_s;
        pushButton_t = ui1080.pushButton_t;
        pushButton_u = ui1080.pushButton_u;
        pushButton_v = ui1080.pushButton_v;
        pushButton_w = ui1080.pushButton_w;
        pushButton_x = ui1080.pushButton_x;
        pushButton_y = ui1080.pushButton_y;
        pushButton_z = ui1080.pushButton_z;
        pushButton_hyphen = ui1080.pushButton_hyphen;
        pushButton_shift_left = ui1080.pushButton_shift_left;
        pushButton_shift_right = ui1080.pushButton_shift_right;
        pushButton_space = ui1080.pushButton_space;
        pushButton_clear = ui1080.pushButton_clear;
        pushButton_close = ui1080.pushButton_close;
        pushButton_enter = ui1080.pushButton_enter;
        label_text = ui1080.label_text;

        frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
        pushButton_0->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_1->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_2->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_3->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_4->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_5->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_6->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_7->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_8->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_9->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

        pushButton_a->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_b->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_c->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_d->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_e->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_f->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_g->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_h->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_i->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_j->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_k->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_l->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_m->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_n->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_o->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_p->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_q->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_r->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_s->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_t->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_u->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_v->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_w->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_x->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_y->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_z->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(206,255,206);}QPushButton:focus{color:white;background:rgb(152,14,69);}");
        pushButton_hyphen->setStyleSheet("QPushButton{font:65px;color:black;background:rgb(136,136,255);}QPushButton:focus{color:white;background:rgb(152,14,69);}");

        label_text->setStyleSheet("QLineEdit{font:65px;background-color:rgb(50,57,83);color:white;border-width:1px;border-style:inset;border-color:white;}");
        pushButton_shift_left->setStyleSheet("QPushButton{font:65px;background:rgb(67,74,86);} QPushButton:focus{color:white;background:rgb(152,14,69);}");

        //yjsin [19/02/21] if text is long, change button font size
        if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
        {
            pushButton_shift_left->setStyleSheet("font:55px;");
        }
    }

    connect(pushButton_shift_right,    SIGNAL(released()), this, SLOT(on_pushButton_shift_left_clicked()));

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    text                       = "";
    maxCharCount               = 16;
    shiftStatus                = 0;

    setPalette(QPalette(QColor(255, 128, 64)));

    label_text->setText(text);
    pushButton_enter->setFocus();
}
UiKeyboardDialog::~UiKeyboardDialog()
{
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
    label_text->setText(text);
}
void UiKeyboardDialog::setPasswordMode(int mode)
{
    if(mode)
    {
        label_text->setEchoMode(QLineEdit::Password);
    }
    else
    {
        label_text->setEchoMode(QLineEdit::Normal);
    }
}
void UiKeyboardDialog::buttonPressed(QString string)
{
    emit signalResetTimer();

    if((text.length() + string.length()) <= maxCharCount)
    {
        text = text + string;
        label_text->setText(text);
    }

    if ( shiftStatus == 1 )
    {
        shiftStatus=0;
        updateButtonShift();
    }
}
void UiKeyboardDialog::on_pushButton_1_clicked()
{
    pushButton_1->setFocus();
    buttonPressed(pushButton_1->text());
}
void UiKeyboardDialog::on_pushButton_2_clicked()
{
    pushButton_2->setFocus();
    buttonPressed(pushButton_2->text());
}
void UiKeyboardDialog::on_pushButton_3_clicked()
{
    pushButton_3->setFocus();
    buttonPressed(pushButton_3->text());
}
void UiKeyboardDialog::on_pushButton_4_clicked()
{
    pushButton_4->setFocus();
    buttonPressed(pushButton_4->text());
}
void UiKeyboardDialog::on_pushButton_5_clicked()
{
    pushButton_5->setFocus();
    buttonPressed(pushButton_5->text());
}
void UiKeyboardDialog::on_pushButton_6_clicked()
{
    pushButton_6->setFocus();
    buttonPressed(pushButton_6->text());
}
void UiKeyboardDialog::on_pushButton_7_clicked()
{
    pushButton_7->setFocus();
    buttonPressed(pushButton_7->text());
}
void UiKeyboardDialog::on_pushButton_8_clicked()
{
    pushButton_8->setFocus();
    buttonPressed(pushButton_8->text());
}
void UiKeyboardDialog::on_pushButton_9_clicked()
{
    pushButton_9->setFocus();
    buttonPressed(pushButton_9->text());
}
void UiKeyboardDialog::on_pushButton_0_clicked()
{
    pushButton_0->setFocus();
    buttonPressed(pushButton_0->text());
}
void UiKeyboardDialog::on_pushButton_hyphen_clicked()
{
    pushButton_hyphen->setFocus();
    buttonPressed(pushButton_hyphen->text());
}
void UiKeyboardDialog::on_pushButton_backspace_clicked()
{
    emit signalResetTimer();

    pushButton_backspace->setFocus();

    text.chop(1);

    label_text->setText(text);
}
void UiKeyboardDialog::on_pushButton_a_clicked()
{
    pushButton_a->setFocus();
    buttonPressed(pushButton_a->text());
}
void UiKeyboardDialog::on_pushButton_b_clicked()
{
    pushButton_b->setFocus();
    buttonPressed(pushButton_b->text());
}
void UiKeyboardDialog::on_pushButton_c_clicked()
{
    pushButton_c->setFocus();
    buttonPressed(pushButton_c->text());
}
void UiKeyboardDialog::on_pushButton_d_clicked()
{
    pushButton_d->setFocus();
    buttonPressed(pushButton_d->text());
}
void UiKeyboardDialog::on_pushButton_e_clicked()
{
    pushButton_e->setFocus();
    buttonPressed(pushButton_e->text());
}
void UiKeyboardDialog::on_pushButton_f_clicked()
{
    pushButton_f->setFocus();
    buttonPressed(pushButton_f->text());
}
void UiKeyboardDialog::on_pushButton_g_clicked()
{
    pushButton_g->setFocus();
    buttonPressed(pushButton_g->text());
}
void UiKeyboardDialog::on_pushButton_h_clicked()
{
    pushButton_h->setFocus();
    buttonPressed(pushButton_h->text());
}
void UiKeyboardDialog::on_pushButton_i_clicked()
{
    pushButton_i->setFocus();
    buttonPressed(pushButton_i->text());
}
void UiKeyboardDialog::on_pushButton_j_clicked()
{
    pushButton_j->setFocus();
    buttonPressed(pushButton_j->text());
}
void UiKeyboardDialog::on_pushButton_k_clicked()
{
    pushButton_k->setFocus();
    buttonPressed(pushButton_k->text());
}
void UiKeyboardDialog::on_pushButton_l_clicked()
{
    pushButton_l->setFocus();
    buttonPressed(pushButton_l->text());
}
void UiKeyboardDialog::on_pushButton_m_clicked()
{
    pushButton_m->setFocus();
    buttonPressed(pushButton_m->text());
}
void UiKeyboardDialog::on_pushButton_n_clicked()
{
    pushButton_n->setFocus();
    buttonPressed(pushButton_n->text());
}
void UiKeyboardDialog::on_pushButton_o_clicked()
{
    pushButton_o->setFocus();
    buttonPressed(pushButton_o->text());
}
void UiKeyboardDialog::on_pushButton_p_clicked()
{
    pushButton_p->setFocus();
    buttonPressed(pushButton_p->text());
}
void UiKeyboardDialog::on_pushButton_q_clicked()
{
    pushButton_q->setFocus();
    buttonPressed(pushButton_q->text());
}
void UiKeyboardDialog::on_pushButton_r_clicked()
{
    pushButton_r->setFocus();
    buttonPressed(pushButton_r->text());
}
void UiKeyboardDialog::on_pushButton_s_clicked()
{
    pushButton_s->setFocus();
    buttonPressed(pushButton_s->text());
}
void UiKeyboardDialog::on_pushButton_t_clicked()
{
    pushButton_t->setFocus();
    buttonPressed(pushButton_t->text());
}
void UiKeyboardDialog::on_pushButton_u_clicked()
{
    pushButton_u->setFocus();
    buttonPressed(pushButton_u->text());
}
void UiKeyboardDialog::on_pushButton_v_clicked()
{
    pushButton_v->setFocus();
    buttonPressed(pushButton_v->text());
}
void UiKeyboardDialog::on_pushButton_w_clicked()
{
    pushButton_w->setFocus();
    buttonPressed(pushButton_w->text());
}
void UiKeyboardDialog::on_pushButton_x_clicked()
{
    pushButton_x->setFocus();
    buttonPressed(pushButton_x->text());
}
void UiKeyboardDialog::on_pushButton_y_clicked()
{
    pushButton_y->setFocus();
    buttonPressed(pushButton_y->text());
}
void UiKeyboardDialog::on_pushButton_z_clicked()
{
    pushButton_z->setFocus();
    buttonPressed(pushButton_z->text());
}
void UiKeyboardDialog::updateButtonShift()
{
    if( shiftStatus == 2 )
    {
        if( mainHeight == 720 )
        {
            pushButton_shift_left->setStyleSheet("QPushButton{font:48px;background:rgb(06,86,159);} QPushButton:focus{color:white;background:rgb(152,14,69);}");

            if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
            {
                pushButton_shift_left->setStyleSheet("QPushButton{font:40px;background:rgb(06,86,159);} QPushButton:focus{color:white;background:rgb(152,14,69);}");
            }
        }
        else
        {
            pushButton_shift_left->setStyleSheet("QPushButton{font:65px;background:rgb(06,86,159);} QPushButton:focus{color:white;background:rgb(152,14,69);}");

            if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
            {
                pushButton_shift_left->setStyleSheet("QPushButton{font:55px;background:rgb(06,86,159);} QPushButton:focus{color:white;background:rgb(152,14,69);}");
            }
        }
    }
    else
    {
        if( mainHeight == 720 )
        {
            pushButton_shift_left->setStyleSheet("QPushButton{font:48px;background:rgb(67,74,86);} QPushButton:focus{color:white;background:rgb(152,14,69);}");

            if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
            {
                pushButton_shift_left->setStyleSheet("QPushButton{font:40px;background:rgb(67,74,86);} QPushButton:focus{color:white;background:rgb(152,14,69);}");
            }
        }
        else
        {
            pushButton_shift_left->setStyleSheet("QPushButton{font:65px;background:rgb(67,74,86);} QPushButton:focus{color:white;background:rgb(152,14,69);}");

            if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
            {
                pushButton_shift_left->setStyleSheet("QPushButton{font:55px;background:rgb(67,74,86);} QPushButton:focus{color:white;background:rgb(152,14,69);}");
            }
        }
    }

    if(shiftStatus>0)
    {
        pushButton_1->setText("!");
        pushButton_2->setText("@");
        pushButton_3->setText("#");
        pushButton_4->setText("$");
        pushButton_5->setText("%");
        pushButton_6->setText("^");
        pushButton_7->setText("&");
        pushButton_8->setText("*");
        pushButton_9->setText("(");
        pushButton_0->setText(")");
        pushButton_hyphen->setText("_");

        pushButton_a->setText("A");
        pushButton_b->setText("B");
        pushButton_c->setText("C");
        pushButton_d->setText("D");
        pushButton_e->setText("E");
        pushButton_f->setText("F");
        pushButton_g->setText("G");
        pushButton_h->setText("H");
        pushButton_i->setText("I");
        pushButton_j->setText("J");
        pushButton_k->setText("K");
        pushButton_l->setText("L");
        pushButton_m->setText("M");
        pushButton_n->setText("N");
        pushButton_o->setText("O");
        pushButton_p->setText("P");
        pushButton_q->setText("Q");
        pushButton_r->setText("R");
        pushButton_s->setText("S");
        pushButton_t->setText("T");
        pushButton_u->setText("U");
        pushButton_v->setText("V");
        pushButton_w->setText("W");
        pushButton_x->setText("X");
        pushButton_y->setText("Y");
        pushButton_z->setText("Z");
    }
    else
    {
        pushButton_1->setText("1");
        pushButton_2->setText("2");
        pushButton_3->setText("3");
        pushButton_4->setText("4");
        pushButton_5->setText("5");
        pushButton_6->setText("6");
        pushButton_7->setText("7");
        pushButton_8->setText("8");
        pushButton_9->setText("9");
        pushButton_0->setText("0");
        pushButton_hyphen->setText("-");

        pushButton_a->setText("a");
        pushButton_b->setText("b");
        pushButton_c->setText("c");
        pushButton_d->setText("d");
        pushButton_e->setText("e");
        pushButton_f->setText("f");
        pushButton_g->setText("g");
        pushButton_h->setText("h");
        pushButton_i->setText("i");
        pushButton_j->setText("j");
        pushButton_k->setText("k");
        pushButton_l->setText("l");
        pushButton_m->setText("m");
        pushButton_n->setText("n");
        pushButton_o->setText("o");
        pushButton_p->setText("p");
        pushButton_q->setText("q");
        pushButton_r->setText("r");
        pushButton_s->setText("s");
        pushButton_t->setText("t");
        pushButton_u->setText("u");
        pushButton_v->setText("v");
        pushButton_w->setText("w");
        pushButton_x->setText("x");
        pushButton_y->setText("y");
        pushButton_z->setText("z");
    }

    disableForbiddenChar();
}
void UiKeyboardDialog::on_pushButton_space_clicked()
{
    pushButton_space->setFocus();
    buttonPressed(" ");
}
void UiKeyboardDialog::on_pushButton_clear_clicked()
{
    emit signalResetTimer();
    pushButton_clear->setFocus();
    text = "";
    label_text->setText(text);
}
void UiKeyboardDialog::on_pushButton_enter_clicked()
{
    emit signalResetTimer();

    pushButton_enter->setFocus();

    shiftStatus = 0;

    updateButtonShift();

    pushButton_clear->setEnabled(true);
    pushButton_clear->setText("CLEAR");

    accept();
}
void UiKeyboardDialog::on_pushButton_close_clicked()
{
    emit signalResetTimer();

    pushButton_close->setFocus();

    shiftStatus = 0;

    updateButtonShift();

    pushButton_clear->setEnabled(true);
    pushButton_clear->setText("CLEAR");

    reject();
}
void UiKeyboardDialog::on_pushButton_shift_left_clicked()
{
    /*
        shiftStatus 0 : lower case
        shiftStatus 1 : upper case 1 time
        shiftStatus 2 : upper case retain
    */

    emit signalResetTimer();

    if( shiftStatus<2 )  { shiftStatus++; }
    else                 { shiftStatus=0; }

    updateButtonShift();
}
void UiKeyboardDialog::disableCapsShift()
{
    pushButton_shift_left->setEnabled(false);
    pushButton_shift_right->setEnabled(false);
}
void UiKeyboardDialog::disableSpecialLetter()
{
    pushButton_space->setEnabled(false);
    pushButton_hyphen->setEnabled(false);
}
void UiKeyboardDialog::setNumberLowerAlphabetOnly()
{
    disableCapsShift();
    disableSpecialLetter();
}
void UiKeyboardDialog::disableForbiddenChar()
{
    if( shiftStatus > 0 )
    {
        pushButton_4->setEnabled(false);  // $
        pushButton_6->setEnabled(false);  // ^
        pushButton_7->setEnabled(false);  // &
        pushButton_8->setEnabled(false);  // *
        pushButton_9->setEnabled(false);  // (
        pushButton_0->setEnabled(false);  // )

        pushButton_4->setText("");  // $
        pushButton_6->setText("");  // ^
        pushButton_7->setText("");  // &
        pushButton_8->setText("");  // *
        pushButton_9->setText("");  // (
        pushButton_0->setText("");  // )
    }
    else
    {
        pushButton_4->setEnabled(true);  // $
        pushButton_6->setEnabled(true);  // ^
        pushButton_7->setEnabled(true);  // &
        pushButton_8->setEnabled(true);  // *
        pushButton_9->setEnabled(true);  // (
        pushButton_0->setEnabled(true);  // )

        pushButton_4->setText("4");  // $
        pushButton_6->setText("6");  // ^
        pushButton_7->setText("7");  // &
        pushButton_8->setText("8");  // *
        pushButton_9->setText("9");  // (
        pushButton_0->setText("0");  // )
    }
}
