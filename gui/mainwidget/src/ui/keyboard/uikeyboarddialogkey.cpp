#include <QtGui>
#include "uikeyboarddialog.h"
#include "main/mainglobal.h"
#include <QWSServer>

void UiKeyboardDialog::mousePressEvent(QMouseEvent *event)
{
    emit signalResetTimer();
}

void UiKeyboardDialog::keyPressEvent(QKeyEvent *event)
{
    emit signalResetTimer();

    switch(event->key())
    {
        case Qt::Key_Up :
        {
                 if( pushButton_1->hasFocus() )             { pushButton_clear->setFocus(); }
            else if( pushButton_2->hasFocus() )             { pushButton_clear->setFocus(); }
            else if( pushButton_3->hasFocus() )             { pushButton_clear->setFocus(); }
            else if( pushButton_4->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_5->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_6->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_7->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_8->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_9->hasFocus() )             { pushButton_close->setFocus(); }
            else if( pushButton_0->hasFocus() )             { pushButton_close->setFocus(); }
            else if( pushButton_hyphen->hasFocus() )        { pushButton_close->setFocus(); }
            else if( pushButton_backspace->hasFocus() )     { pushButton_hyphen->setFocus(); }

            else if( pushButton_q->hasFocus() )             { pushButton_1->setFocus(); }
            else if( pushButton_w->hasFocus() )             { pushButton_2->setFocus(); }
            else if( pushButton_e->hasFocus() )             { pushButton_3->setFocus(); }
            else if( pushButton_r->hasFocus()
                 && !pushButton_4->isEnabled() )            { pushButton_space->setFocus(); }
            else if( pushButton_r->hasFocus() )             { pushButton_4->setFocus(); }
            else if( pushButton_t->hasFocus() )             { pushButton_5->setFocus(); }
            else if( pushButton_y->hasFocus()
                 && !pushButton_6->isEnabled() )            { pushButton_space->setFocus(); }
            else if( pushButton_y->hasFocus() )             { pushButton_6->setFocus(); }
            else if( pushButton_u->hasFocus()
                 && !pushButton_7->isEnabled() )            { pushButton_space->setFocus(); }
            else if( pushButton_u->hasFocus() )             { pushButton_7->setFocus(); }
            else if( pushButton_i->hasFocus()
                 && !pushButton_8->isEnabled() )            { pushButton_space->setFocus(); }
            else if( pushButton_i->hasFocus() )             { pushButton_8->setFocus(); }
            else if( pushButton_o->hasFocus()
                 && !pushButton_9->isEnabled() )            { pushButton_close->setFocus(); }
            else if( pushButton_o->hasFocus() )             { pushButton_9->setFocus(); }
            else if( pushButton_p->hasFocus()
                 && !pushButton_0->isEnabled() )            { pushButton_close->setFocus(); }
            else if( pushButton_p->hasFocus() )             { pushButton_0->setFocus(); }
            else if( pushButton_a->hasFocus() )             { pushButton_q->setFocus(); }
            else if( pushButton_s->hasFocus() )             { pushButton_w->setFocus(); }
            else if( pushButton_d->hasFocus() )             { pushButton_e->setFocus(); }
            else if( pushButton_f->hasFocus() )             { pushButton_r->setFocus(); }
            else if( pushButton_g->hasFocus() )             { pushButton_t->setFocus(); }
            else if( pushButton_h->hasFocus() )             { pushButton_y->setFocus(); }
            else if( pushButton_j->hasFocus() )             { pushButton_u->setFocus(); }
            else if( pushButton_k->hasFocus() )             { pushButton_i->setFocus(); }
            else if( pushButton_l->hasFocus() )             { pushButton_o->setFocus(); }
            else if( pushButton_enter->hasFocus() )         { pushButton_backspace->setFocus(); }

            else if( pushButton_shift_left->hasFocus() )    { pushButton_a->setFocus(); }
            else if( pushButton_z->hasFocus() )             { pushButton_s->setFocus(); }
            else if( pushButton_x->hasFocus() )             { pushButton_d->setFocus(); }
            else if( pushButton_c->hasFocus() )             { pushButton_f->setFocus(); }
            else if( pushButton_v->hasFocus() )             { pushButton_g->setFocus(); }
            else if( pushButton_b->hasFocus() )             { pushButton_h->setFocus(); }
            else if( pushButton_n->hasFocus() )             { pushButton_j->setFocus(); }
            else if( pushButton_m->hasFocus() )             { pushButton_k->setFocus(); }

            else if( pushButton_clear->hasFocus() )         { pushButton_z->setFocus(); }
            else if( pushButton_space->hasFocus() )         { pushButton_b->setFocus(); }
            else if( pushButton_close->hasFocus() )         { pushButton_enter->setFocus(); }
            break;
        }
        case Qt::Key_Down :
        {
                 if( pushButton_1->hasFocus() )             { pushButton_q->setFocus(); }
            else if( pushButton_2->hasFocus() )             { pushButton_w->setFocus(); }
            else if( pushButton_3->hasFocus() )             { pushButton_e->setFocus(); }
            else if( pushButton_4->hasFocus() )             { pushButton_r->setFocus(); }
            else if( pushButton_5->hasFocus() )             { pushButton_t->setFocus(); }
            else if( pushButton_6->hasFocus() )             { pushButton_y->setFocus(); }
            else if( pushButton_7->hasFocus() )             { pushButton_u->setFocus(); }
            else if( pushButton_8->hasFocus() )             { pushButton_i->setFocus(); }
            else if( pushButton_9->hasFocus() )             { pushButton_o->setFocus(); }
            else if( pushButton_0->hasFocus() )             { pushButton_p->setFocus(); }
            else if( pushButton_hyphen->hasFocus() )        { pushButton_backspace->setFocus(); }
            else if( pushButton_backspace->hasFocus() )     { pushButton_enter->setFocus(); }

            else if( pushButton_q->hasFocus() )             { pushButton_a->setFocus(); }
            else if( pushButton_w->hasFocus() )             { pushButton_s->setFocus(); }
            else if( pushButton_e->hasFocus() )             { pushButton_d->setFocus(); }
            else if( pushButton_r->hasFocus() )             { pushButton_f->setFocus(); }
            else if( pushButton_t->hasFocus() )             { pushButton_g->setFocus(); }
            else if( pushButton_y->hasFocus() )             { pushButton_h->setFocus(); }
            else if( pushButton_u->hasFocus() )             { pushButton_j->setFocus(); }
            else if( pushButton_i->hasFocus() )             { pushButton_k->setFocus(); }
            else if( pushButton_o->hasFocus() )             { pushButton_l->setFocus(); }
            else if( pushButton_p->hasFocus() )             { pushButton_enter->setFocus(); }

            else if( pushButton_a->hasFocus() )             { pushButton_shift_left->setFocus(); }
            else if( pushButton_s->hasFocus() )             { pushButton_z->setFocus(); }
            else if( pushButton_d->hasFocus() )             { pushButton_x->setFocus(); }
            else if( pushButton_f->hasFocus() )             { pushButton_c->setFocus(); }
            else if( pushButton_g->hasFocus() )             { pushButton_v->setFocus(); }
            else if( pushButton_h->hasFocus() )             { pushButton_b->setFocus(); }
            else if( pushButton_j->hasFocus() )             { pushButton_n->setFocus(); }
            else if( pushButton_k->hasFocus() )             { pushButton_m->setFocus(); }
            else if( pushButton_l->hasFocus() )             { pushButton_close->setFocus(); }
            else if( pushButton_enter->hasFocus() )         { pushButton_close->setFocus(); }

            else if( pushButton_shift_left->hasFocus() )    { pushButton_clear->setFocus(); }
            else if( pushButton_z->hasFocus() )             { pushButton_clear->setFocus(); }
            else if( pushButton_x->hasFocus() )             { pushButton_clear->setFocus(); }
            else if( pushButton_c->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_v->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_b->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_n->hasFocus() )             { pushButton_space->setFocus(); }
            else if( pushButton_m->hasFocus() )             { pushButton_space->setFocus(); }

            else if( pushButton_clear->hasFocus() )         { pushButton_2->setFocus(); }
            else if( pushButton_space->hasFocus()
                 && !pushButton_6->isEnabled() )            { pushButton_5->setFocus(); }
            else if( pushButton_space->hasFocus() )         { pushButton_6->setFocus(); }
            else if( pushButton_close->hasFocus()
                 && !pushButton_0->isEnabled() )            { pushButton_hyphen->setFocus(); }
            else if( pushButton_close->hasFocus() )         { pushButton_0->setFocus(); }
            break;
        }
        case Qt::Key_Left :
        {
                 if( pushButton_1->hasFocus() )             { pushButton_hyphen->setFocus(); }
            else if( pushButton_2->hasFocus() )             { pushButton_1->setFocus(); }
            else if( pushButton_3->hasFocus() )             { pushButton_2->setFocus(); }
            else if( pushButton_4->hasFocus() )             { pushButton_3->setFocus(); }
            else if( pushButton_5->hasFocus()
                 && !pushButton_4->isEnabled() )            { pushButton_3->setFocus(); }
            else if( pushButton_5->hasFocus() )             { pushButton_4->setFocus(); }
            else if( pushButton_6->hasFocus() )             { pushButton_5->setFocus(); }
            else if( pushButton_7->hasFocus() )             { pushButton_6->setFocus(); }
            else if( pushButton_8->hasFocus() )             { pushButton_7->setFocus(); }
            else if( pushButton_9->hasFocus() )             { pushButton_8->setFocus(); }
            else if( pushButton_0->hasFocus() )             { pushButton_9->setFocus(); }
            else if( pushButton_hyphen->hasFocus()
                 && !pushButton_0->isEnabled() )             { pushButton_5->setFocus(); }
            else if( pushButton_hyphen->hasFocus() )        { pushButton_0->setFocus(); }
            else if( pushButton_backspace->hasFocus() )     { pushButton_p->setFocus(); }

            else if( pushButton_q->hasFocus() )             { pushButton_backspace->setFocus(); }
            else if( pushButton_w->hasFocus() )             { pushButton_q->setFocus(); }
            else if( pushButton_e->hasFocus() )             { pushButton_w->setFocus(); }
            else if( pushButton_r->hasFocus() )             { pushButton_e->setFocus(); }
            else if( pushButton_t->hasFocus() )             { pushButton_r->setFocus(); }
            else if( pushButton_y->hasFocus() )             { pushButton_t->setFocus(); }
            else if( pushButton_u->hasFocus() )             { pushButton_y->setFocus(); }
            else if( pushButton_i->hasFocus() )             { pushButton_u->setFocus(); }
            else if( pushButton_o->hasFocus() )             { pushButton_i->setFocus(); }
            else if( pushButton_p->hasFocus() )             { pushButton_o->setFocus(); }

            else if( pushButton_a->hasFocus() )             { pushButton_enter->setFocus(); }
            else if( pushButton_s->hasFocus() )             { pushButton_a->setFocus(); }
            else if( pushButton_d->hasFocus() )             { pushButton_s->setFocus(); }
            else if( pushButton_f->hasFocus() )             { pushButton_d->setFocus(); }
            else if( pushButton_g->hasFocus() )             { pushButton_f->setFocus(); }
            else if( pushButton_h->hasFocus() )             { pushButton_g->setFocus(); }
            else if( pushButton_j->hasFocus() )             { pushButton_h->setFocus(); }
            else if( pushButton_k->hasFocus() )             { pushButton_j->setFocus(); }
            else if( pushButton_l->hasFocus() )             { pushButton_k->setFocus(); }
            else if( pushButton_enter->hasFocus() )         { pushButton_l->setFocus(); }

            else if( pushButton_shift_left->hasFocus() )    { pushButton_enter->setFocus(); }
            else if( pushButton_z->hasFocus() )             { pushButton_shift_left->setFocus(); }
            else if( pushButton_x->hasFocus() )             { pushButton_z->setFocus(); }
            else if( pushButton_c->hasFocus() )             { pushButton_x->setFocus(); }
            else if( pushButton_v->hasFocus() )             { pushButton_c->setFocus(); }
            else if( pushButton_b->hasFocus() )             { pushButton_v->setFocus(); }
            else if( pushButton_n->hasFocus() )             { pushButton_b->setFocus(); }
            else if( pushButton_m->hasFocus() )             { pushButton_n->setFocus(); }

            else if( pushButton_clear->hasFocus() )         { pushButton_close->setFocus(); }
            else if( pushButton_space->hasFocus() )         { pushButton_clear->setFocus(); }
            else if( pushButton_close->hasFocus() )         { pushButton_space->setFocus(); }
            break;
        }
        case Qt::Key_Right :
        {
                 if( pushButton_1->hasFocus() )             { pushButton_2->setFocus(); }
            else if( pushButton_2->hasFocus() )             { pushButton_3->setFocus(); }
            else if( pushButton_3->hasFocus()
                 && !pushButton_4->isEnabled() )            { pushButton_5->setFocus(); }
            else if( pushButton_3->hasFocus() )             { pushButton_4->setFocus(); }
            else if( pushButton_4->hasFocus() )             { pushButton_5->setFocus(); }
            else if( pushButton_5->hasFocus()
                 && !pushButton_6->isEnabled() )            { pushButton_hyphen->setFocus(); }
            else if( pushButton_5->hasFocus() )             { pushButton_6->setFocus(); }
            else if( pushButton_6->hasFocus() )             { pushButton_7->setFocus(); }
            else if( pushButton_7->hasFocus() )             { pushButton_8->setFocus(); }
            else if( pushButton_8->hasFocus() )             { pushButton_9->setFocus(); }
            else if( pushButton_9->hasFocus() )             { pushButton_0->setFocus(); }
            else if( pushButton_0->hasFocus() )             { pushButton_hyphen->setFocus(); }
            else if( pushButton_hyphen->hasFocus() )        { pushButton_1->setFocus(); }
            else if( pushButton_backspace->hasFocus() )     { pushButton_q->setFocus(); }

            else if( pushButton_q->hasFocus() )             { pushButton_w->setFocus(); }
            else if( pushButton_w->hasFocus() )             { pushButton_e->setFocus(); }
            else if( pushButton_e->hasFocus() )             { pushButton_r->setFocus(); }
            else if( pushButton_r->hasFocus() )             { pushButton_t->setFocus(); }
            else if( pushButton_t->hasFocus() )             { pushButton_y->setFocus(); }
            else if( pushButton_y->hasFocus() )             { pushButton_u->setFocus(); }
            else if( pushButton_u->hasFocus() )             { pushButton_i->setFocus(); }
            else if( pushButton_i->hasFocus() )             { pushButton_o->setFocus(); }
            else if( pushButton_o->hasFocus() )             { pushButton_p->setFocus(); }
            else if( pushButton_p->hasFocus() )             { pushButton_backspace->setFocus(); }

            else if( pushButton_a->hasFocus() )             { pushButton_s->setFocus(); }
            else if( pushButton_s->hasFocus() )             { pushButton_d->setFocus(); }
            else if( pushButton_d->hasFocus() )             { pushButton_f->setFocus(); }
            else if( pushButton_f->hasFocus() )             { pushButton_g->setFocus(); }
            else if( pushButton_g->hasFocus() )             { pushButton_h->setFocus(); }
            else if( pushButton_h->hasFocus() )             { pushButton_j->setFocus(); }
            else if( pushButton_j->hasFocus() )             { pushButton_k->setFocus(); }
            else if( pushButton_k->hasFocus() )             { pushButton_l->setFocus(); }
            else if( pushButton_l->hasFocus() )             { pushButton_enter->setFocus(); }
            else if( pushButton_enter->hasFocus() )         { pushButton_a->setFocus(); }

            else if( pushButton_shift_left->hasFocus() )    { pushButton_z->setFocus(); }
            else if( pushButton_z->hasFocus() )             { pushButton_x->setFocus(); }
            else if( pushButton_x->hasFocus() )             { pushButton_c->setFocus(); }
            else if( pushButton_c->hasFocus() )             { pushButton_v->setFocus(); }
            else if( pushButton_v->hasFocus() )             { pushButton_b->setFocus(); }
            else if( pushButton_b->hasFocus() )             { pushButton_n->setFocus(); }
            else if( pushButton_n->hasFocus() )             { pushButton_m->setFocus(); }
            else if( pushButton_m->hasFocus() )             { pushButton_enter->setFocus(); }

            else if( pushButton_clear->hasFocus() )         { pushButton_space->setFocus(); }
            else if( pushButton_space->hasFocus() )         { pushButton_close->setFocus(); }
            else if( pushButton_close->hasFocus() )         { pushButton_clear->setFocus(); }
            break;
        }
        case Qt::Key_Enter:
        {
            qDebug("Key_Eenter............");

            if(pushButton_enter->hasFocus())
            {
                on_pushButton_enter_clicked();
            }
            else if(pushButton_close->hasFocus())
            {
                on_pushButton_close_clicked();
            }
            else
            {
                QWSServer::sendKeyEvent( -1, Qt::Key_Space,0, true, false);
                QWSServer::sendKeyEvent( -1, Qt::Key_Space,0, false, false);
                return;
            }

            break;
        }
        case Qt::Key_Escape:
        {
            qDebug("Key_Escape............");

            if(pushButton_enter->hasFocus())
            {
                reject();
            }
            else if(pushButton_close->hasFocus())
            {
                reject();
            }
            else
            {
                reject();
            }

            break;
        }
        default:
        {
            break;
        }
    } //end switch
    QDialog::keyPressEvent(event);
}

void UiKeyboardDialog::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug(".............. UiSetupDialog key press keyDepth %d", keyDepth);
    return;
}
