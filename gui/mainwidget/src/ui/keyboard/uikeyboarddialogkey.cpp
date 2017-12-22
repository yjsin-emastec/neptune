#include <QtGui>
#include "uikeyboarddialog.h"
#include "ui_uikeyboarddialog.h"
#include "src/main/mainglobal.h"
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
		case Qt::Key_Up:
		{
                 if(ui->pushButton_1->hasFocus())               { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_2->hasFocus())               { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_3->hasFocus())               { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_4->hasFocus())               { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_5->hasFocus())               { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_6->hasFocus())               { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_7->hasFocus())               { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_8->hasFocus())               { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_9->hasFocus())               { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_0->hasFocus())               { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_hyphen->hasFocus())          { ui->pushButton_close->setFocus();           }
#if 0 // GyverJeong [17/12/22]
            else if(ui->pushButton_equal->hasFocus())           { ui->pushButton_close->setFocus();           }
#endif
            else if(ui->pushButton_backspace->hasFocus())       { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_a->hasFocus())               { ui->pushButton_1->setFocus();               }
            else if(ui->pushButton_b->hasFocus())               { ui->pushButton_2->setFocus();               }
            else if(ui->pushButton_c->hasFocus())               { ui->pushButton_3->setFocus();               }
            else if(ui->pushButton_d->hasFocus() &&
                   !ui->pushButton_4->isEnabled())              { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_d->hasFocus())               { ui->pushButton_4->setFocus();               }
            else if(ui->pushButton_e->hasFocus())               { ui->pushButton_5->setFocus();               }
            else if(ui->pushButton_f->hasFocus() &&
                   !ui->pushButton_6->isEnabled())              { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_f->hasFocus())               { ui->pushButton_6->setFocus();               }
            else if(ui->pushButton_g->hasFocus() &&
                   !ui->pushButton_7->isEnabled())              { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_g->hasFocus())               { ui->pushButton_7->setFocus();               }
            else if(ui->pushButton_h->hasFocus() &&
                   !ui->pushButton_8->isEnabled())              { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_h->hasFocus())               { ui->pushButton_8->setFocus();               }
            else if(ui->pushButton_i->hasFocus() &&
                   !ui->pushButton_9->isEnabled())              { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_i->hasFocus())               { ui->pushButton_9->setFocus();               }
            else if(ui->pushButton_j->hasFocus() &&
                   !ui->pushButton_0->isEnabled())              { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_j->hasFocus())               { ui->pushButton_0->setFocus();               }
            else if(ui->pushButton_k->hasFocus())               { ui->pushButton_hyphen->setFocus();          }
#if 1 // GyverJeong [17/12/22]
            else if(ui->pushButton_l->hasFocus())               { ui->pushButton_close->setFocus();           }
#else
            else if(ui->pushButton_l->hasFocus() &&
                   !ui->pushButton_equal->isEnabled())          { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_l->hasFocus())               { ui->pushButton_equal->setFocus();           }
#endif
            else if(ui->pushButton_m->hasFocus())               { ui->pushButton_backspace->setFocus();       }
            else if(ui->pushButton_n->hasFocus())               { ui->pushButton_a->setFocus();               }
            else if(ui->pushButton_o->hasFocus())               { ui->pushButton_b->setFocus();               }
            else if(ui->pushButton_p->hasFocus())               { ui->pushButton_c->setFocus();               }
            else if(ui->pushButton_q->hasFocus())               { ui->pushButton_d->setFocus();               }
            else if(ui->pushButton_r->hasFocus())               { ui->pushButton_e->setFocus();               }
            else if(ui->pushButton_s->hasFocus())               { ui->pushButton_f->setFocus();               }
            else if(ui->pushButton_t->hasFocus())               { ui->pushButton_g->setFocus();               }
            else if(ui->pushButton_u->hasFocus())               { ui->pushButton_h->setFocus();               }
            else if(ui->pushButton_v->hasFocus())               { ui->pushButton_i->setFocus();               }
            else if(ui->pushButton_w->hasFocus())               { ui->pushButton_j->setFocus();               }
            else if(ui->pushButton_x->hasFocus())               { ui->pushButton_k->setFocus();               }
            else if(ui->pushButton_y->hasFocus())               { ui->pushButton_l->setFocus();               }
            else if(ui->pushButton_z->hasFocus())               { ui->pushButton_m->setFocus();               }
            else if(ui->pushButton_shift_left->hasFocus())      { ui->pushButton_p->setFocus();               }
            else if(ui->pushButton_space->hasFocus())           { ui->pushButton_u->setFocus();               }
            else if(ui->pushButton_comma->hasFocus())           { ui->pushButton_x->setFocus();               }
            else if(ui->pushButton_period->hasFocus())          { ui->pushButton_y->setFocus();               }
            else if(ui->pushButton_forward_slash->hasFocus())   { ui->pushButton_z->setFocus();               }
            else if(ui->pushButton_clear->hasFocus())           { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_enter->hasFocus())           { ui->pushButton_space->setFocus();           }
#if 1 // GyverJeong [17/12/22]
            else if(ui->pushButton_close->hasFocus())           { ui->pushButton_x->setFocus();               }
#else
            else if(ui->pushButton_close->hasFocus())           { ui->pushButton_period->setFocus();          }
#endif

            break;
		}
		case Qt::Key_Down:
		{
                 if(ui->pushButton_1->hasFocus())               { ui->pushButton_a->setFocus();               }
            else if(ui->pushButton_2->hasFocus())               { ui->pushButton_b->setFocus();               }
            else if(ui->pushButton_3->hasFocus())               { ui->pushButton_c->setFocus();               }
            else if(ui->pushButton_4->hasFocus())               { ui->pushButton_d->setFocus();               }
            else if(ui->pushButton_5->hasFocus())               { ui->pushButton_e->setFocus();               }
            else if(ui->pushButton_6->hasFocus())               { ui->pushButton_f->setFocus();               }
            else if(ui->pushButton_7->hasFocus())               { ui->pushButton_g->setFocus();               }
            else if(ui->pushButton_8->hasFocus())               { ui->pushButton_h->setFocus();               }
            else if(ui->pushButton_9->hasFocus())               { ui->pushButton_i->setFocus();               }
            else if(ui->pushButton_0->hasFocus())               { ui->pushButton_j->setFocus();               }
            else if(ui->pushButton_hyphen->hasFocus())          { ui->pushButton_k->setFocus();               }
#if 0 // GyverJeong [17/12/22]
            else if(ui->pushButton_equal->hasFocus())           { ui->pushButton_l->setFocus();               }
#endif
            else if(ui->pushButton_backspace->hasFocus())       { ui->pushButton_m->setFocus();               }
            else if(ui->pushButton_a->hasFocus())               { ui->pushButton_n->setFocus();               }
            else if(ui->pushButton_b->hasFocus())               { ui->pushButton_o->setFocus();               }
            else if(ui->pushButton_c->hasFocus())               { ui->pushButton_p->setFocus();               }
            else if(ui->pushButton_d->hasFocus())               { ui->pushButton_q->setFocus();               }
            else if(ui->pushButton_e->hasFocus())               { ui->pushButton_r->setFocus();               }
            else if(ui->pushButton_f->hasFocus())               { ui->pushButton_s->setFocus();               }
            else if(ui->pushButton_g->hasFocus())               { ui->pushButton_t->setFocus();               }
            else if(ui->pushButton_h->hasFocus())               { ui->pushButton_u->setFocus();               }
            else if(ui->pushButton_i->hasFocus())               { ui->pushButton_v->setFocus();               }
            else if(ui->pushButton_j->hasFocus())               { ui->pushButton_w->setFocus();               }
            else if(ui->pushButton_k->hasFocus())               { ui->pushButton_x->setFocus();               }
            else if(ui->pushButton_l->hasFocus())               { ui->pushButton_y->setFocus();               }
            else if(ui->pushButton_m->hasFocus())               { ui->pushButton_z->setFocus();               }
            else if(ui->pushButton_n->hasFocus())               { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_o->hasFocus())               { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_p->hasFocus())               { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_q->hasFocus())               { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_r->hasFocus())               { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_s->hasFocus())               { ui->pushButton_space->setFocus();           }
            else if(ui->pushButton_t->hasFocus())               { ui->pushButton_space->setFocus();           }
            else if(ui->pushButton_u->hasFocus())               { ui->pushButton_space->setFocus();           }
            else if(ui->pushButton_v->hasFocus())               { ui->pushButton_space->setFocus();           }
            else if(ui->pushButton_w->hasFocus())               { ui->pushButton_space->setFocus();           }
#if 1 // GyverJeong [17/12/22]
            else if(ui->pushButton_x->hasFocus())               { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_y->hasFocus())               { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_z->hasFocus())               { ui->pushButton_close->setFocus();           }
#else
            else if(ui->pushButton_x->hasFocus())               { ui->pushButton_comma->setFocus();           }
            else if(ui->pushButton_y->hasFocus())               { ui->pushButton_period->setFocus();          }
            else if(ui->pushButton_z->hasFocus() &&
                   !ui->pushButton_forward_slash->isEnabled())  { ui->pushButton_close->setFocus();           }
#endif
            else if(ui->pushButton_z->hasFocus())               { ui->pushButton_forward_slash->setFocus();   }
            else if(ui->pushButton_shift_left->hasFocus())      { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_space->hasFocus())           { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_comma->hasFocus())           { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_period->hasFocus())          { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_forward_slash->hasFocus())   { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_clear->hasFocus())           { ui->pushButton_3->setFocus();               }
            else if(ui->pushButton_enter->hasFocus() &&
                   !ui->pushButton_8->isEnabled())              { ui->pushButton_h->setFocus();               }
            else if(ui->pushButton_enter->hasFocus())           { ui->pushButton_8->setFocus();               }
#if 1 // GyverJeong [17/12/22]
            else if(ui->pushButton_close->hasFocus())           { ui->pushButton_hyphen->setFocus();          }
#else
            else if(ui->pushButton_close->hasFocus() &&
                   !ui->pushButton_equal->isEnabled())          { ui->pushButton_l->setFocus();               }
            else if(ui->pushButton_close->hasFocus())           { ui->pushButton_equal->setFocus();           }
#endif

            break;
		}
		case Qt::Key_Left:
		{
                 if(ui->pushButton_1->hasFocus())               { ui->pushButton_backspace->setFocus();       }
            else if(ui->pushButton_2->hasFocus())               { ui->pushButton_1->setFocus();               }
            else if(ui->pushButton_3->hasFocus())               { ui->pushButton_2->setFocus();               }
            else if(ui->pushButton_4->hasFocus())               { ui->pushButton_3->setFocus();               }
            else if(ui->pushButton_5->hasFocus() &&
                   !ui->pushButton_4->isEnabled())              { ui->pushButton_3->setFocus();               }
            else if(ui->pushButton_5->hasFocus())               { ui->pushButton_4->setFocus();               }
            else if(ui->pushButton_6->hasFocus())               { ui->pushButton_5->setFocus();               }
            else if(ui->pushButton_7->hasFocus())               { ui->pushButton_6->setFocus();               }
            else if(ui->pushButton_8->hasFocus())               { ui->pushButton_7->setFocus();               }
            else if(ui->pushButton_9->hasFocus())               { ui->pushButton_8->setFocus();               }
            else if(ui->pushButton_0->hasFocus())               { ui->pushButton_9->setFocus();               }
            else if(ui->pushButton_hyphen->hasFocus() &&
                   !ui->pushButton_0->isEnabled())              { ui->pushButton_5->setFocus();               }
            else if(ui->pushButton_hyphen->hasFocus())          { ui->pushButton_0->setFocus();               }
#if 0 // GyverJeong [17/12/22]
            else if(ui->pushButton_equal->hasFocus())           { ui->pushButton_hyphen->setFocus();          }
#endif
            else if(ui->pushButton_backspace->hasFocus() &&
                   !ui->pushButton_equal->isEnabled())          { ui->pushButton_hyphen->setFocus();          }
            else if(ui->pushButton_backspace->hasFocus())       { ui->pushButton_equal->setFocus();           }
            else if(ui->pushButton_a->hasFocus())               { ui->pushButton_m->setFocus();               }
            else if(ui->pushButton_b->hasFocus())               { ui->pushButton_a->setFocus();               }
            else if(ui->pushButton_c->hasFocus())               { ui->pushButton_b->setFocus();               }
            else if(ui->pushButton_d->hasFocus())               { ui->pushButton_c->setFocus();               }
            else if(ui->pushButton_e->hasFocus())               { ui->pushButton_d->setFocus();               }
            else if(ui->pushButton_f->hasFocus())               { ui->pushButton_e->setFocus();               }
            else if(ui->pushButton_g->hasFocus())               { ui->pushButton_f->setFocus();               }
            else if(ui->pushButton_h->hasFocus())               { ui->pushButton_g->setFocus();               }
            else if(ui->pushButton_i->hasFocus())               { ui->pushButton_h->setFocus();               }
            else if(ui->pushButton_j->hasFocus())               { ui->pushButton_i->setFocus();               }
            else if(ui->pushButton_k->hasFocus())               { ui->pushButton_j->setFocus();               }
            else if(ui->pushButton_l->hasFocus())               { ui->pushButton_k->setFocus();               }
            else if(ui->pushButton_m->hasFocus())               { ui->pushButton_l->setFocus();               }
            else if(ui->pushButton_n->hasFocus())               { ui->pushButton_z->setFocus();               }
            else if(ui->pushButton_o->hasFocus())               { ui->pushButton_n->setFocus();               }
            else if(ui->pushButton_p->hasFocus())               { ui->pushButton_o->setFocus();               }
            else if(ui->pushButton_q->hasFocus())               { ui->pushButton_p->setFocus();               }
            else if(ui->pushButton_r->hasFocus())               { ui->pushButton_q->setFocus();               }
            else if(ui->pushButton_s->hasFocus())               { ui->pushButton_r->setFocus();               }
            else if(ui->pushButton_t->hasFocus())               { ui->pushButton_s->setFocus();               }
            else if(ui->pushButton_u->hasFocus())               { ui->pushButton_t->setFocus();               }
            else if(ui->pushButton_v->hasFocus())               { ui->pushButton_u->setFocus();               }
            else if(ui->pushButton_w->hasFocus())               { ui->pushButton_v->setFocus();               }
            else if(ui->pushButton_x->hasFocus())               { ui->pushButton_w->setFocus();               }
            else if(ui->pushButton_y->hasFocus())               { ui->pushButton_x->setFocus();               }
            else if(ui->pushButton_z->hasFocus())               { ui->pushButton_y->setFocus();               }
#if 1 // GyverJeong [17/12/22]
            else if(ui->pushButton_shift_left->hasFocus())      { ui->pushButton_space->setFocus();           }
#else
            else if(ui->pushButton_shift_left->hasFocus() &&
                   !ui->pushButton_forward_slash->isEnabled())  { ui->pushButton_period->setFocus();          }
            else if(ui->pushButton_shift_left->hasFocus())      { ui->pushButton_forward_slash->setFocus();   }
#endif
            else if(ui->pushButton_space->hasFocus())           { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_comma->hasFocus())           { ui->pushButton_space->setFocus();           }
            else if(ui->pushButton_period->hasFocus())          { ui->pushButton_comma->setFocus();           }
            else if(ui->pushButton_forward_slash->hasFocus())   { ui->pushButton_period->setFocus();          }
            else if(ui->pushButton_clear->hasFocus())           { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_enter->hasFocus())           { ui->pushButton_clear->setFocus();           }
            else if(ui->pushButton_close->hasFocus())           { ui->pushButton_enter->setFocus();           }

            break;
		}
		case Qt::Key_Right:
		{
                 if(ui->pushButton_1->hasFocus())               { ui->pushButton_2->setFocus();               }
            else if(ui->pushButton_2->hasFocus())               { ui->pushButton_3->setFocus();               }
            else if(ui->pushButton_3->hasFocus() &&
                   !ui->pushButton_4->isEnabled())              { ui->pushButton_5->setFocus();               }
            else if(ui->pushButton_3->hasFocus())               { ui->pushButton_4->setFocus();               }
            else if(ui->pushButton_4->hasFocus())               { ui->pushButton_5->setFocus();               }
            else if(ui->pushButton_5->hasFocus() &&
                   !ui->pushButton_6->isEnabled())              { ui->pushButton_hyphen->setFocus();          }
            else if(ui->pushButton_5->hasFocus())               { ui->pushButton_6->setFocus();               }
            else if(ui->pushButton_6->hasFocus())               { ui->pushButton_7->setFocus();               }
            else if(ui->pushButton_7->hasFocus())               { ui->pushButton_8->setFocus();               }
            else if(ui->pushButton_8->hasFocus())               { ui->pushButton_9->setFocus();               }
            else if(ui->pushButton_9->hasFocus())               { ui->pushButton_0->setFocus();               }
            else if(ui->pushButton_0->hasFocus())               { ui->pushButton_hyphen->setFocus();          }
            else if(ui->pushButton_hyphen->hasFocus() &&
                   !ui->pushButton_equal->isEnabled())          { ui->pushButton_backspace->setFocus();       }
            else if(ui->pushButton_hyphen->hasFocus())          { ui->pushButton_equal->setFocus();           }
#if 0 // GyverJeong [17/12/22]
            else if(ui->pushButton_equal->hasFocus())           { ui->pushButton_backspace->setFocus();       }
#endif
            else if(ui->pushButton_backspace->hasFocus())       { ui->pushButton_1->setFocus();               }
            else if(ui->pushButton_a->hasFocus())               { ui->pushButton_b->setFocus();               }
            else if(ui->pushButton_b->hasFocus())               { ui->pushButton_c->setFocus();               }
            else if(ui->pushButton_c->hasFocus())               { ui->pushButton_d->setFocus();               }
            else if(ui->pushButton_d->hasFocus())               { ui->pushButton_e->setFocus();               }
            else if(ui->pushButton_e->hasFocus())               { ui->pushButton_f->setFocus();               }
            else if(ui->pushButton_f->hasFocus())               { ui->pushButton_g->setFocus();               }
            else if(ui->pushButton_g->hasFocus())               { ui->pushButton_h->setFocus();               }
            else if(ui->pushButton_h->hasFocus())               { ui->pushButton_i->setFocus();               }
            else if(ui->pushButton_i->hasFocus())               { ui->pushButton_j->setFocus();               }
            else if(ui->pushButton_j->hasFocus())               { ui->pushButton_k->setFocus();               }
            else if(ui->pushButton_k->hasFocus())               { ui->pushButton_l->setFocus();               }
            else if(ui->pushButton_l->hasFocus())               { ui->pushButton_m->setFocus();               }
            else if(ui->pushButton_m->hasFocus())               { ui->pushButton_a->setFocus();               }
            else if(ui->pushButton_n->hasFocus())               { ui->pushButton_o->setFocus();               }
            else if(ui->pushButton_o->hasFocus())               { ui->pushButton_p->setFocus();               }
            else if(ui->pushButton_p->hasFocus())               { ui->pushButton_q->setFocus();               }
            else if(ui->pushButton_q->hasFocus())               { ui->pushButton_r->setFocus();               }
            else if(ui->pushButton_r->hasFocus())               { ui->pushButton_s->setFocus();               }
            else if(ui->pushButton_s->hasFocus())               { ui->pushButton_t->setFocus();               }
            else if(ui->pushButton_t->hasFocus())               { ui->pushButton_u->setFocus();               }
            else if(ui->pushButton_u->hasFocus())               { ui->pushButton_v->setFocus();               }
            else if(ui->pushButton_v->hasFocus())               { ui->pushButton_w->setFocus();               }
            else if(ui->pushButton_w->hasFocus())               { ui->pushButton_x->setFocus();               }
            else if(ui->pushButton_x->hasFocus())               { ui->pushButton_y->setFocus();               }
            else if(ui->pushButton_y->hasFocus())               { ui->pushButton_z->setFocus();               }
            else if(ui->pushButton_z->hasFocus())               { ui->pushButton_n->setFocus();               }
            else if(ui->pushButton_shift_left->hasFocus())      { ui->pushButton_space->setFocus();           }
#if 1 // GyverJeong [17/12/22]
            else if(ui->pushButton_space->hasFocus())           { ui->pushButton_shift_left->setFocus();      }
#else
            else if(ui->pushButton_space->hasFocus())           { ui->pushButton_comma->setFocus();           }
            else if(ui->pushButton_comma->hasFocus())           { ui->pushButton_period->setFocus();          }
            else if(ui->pushButton_period->hasFocus() &&
                   !ui->pushButton_forward_slash->isEnabled())  { ui->pushButton_shift_left->setFocus();      }
            else if(ui->pushButton_period->hasFocus())          { ui->pushButton_forward_slash->setFocus();   }
            else if(ui->pushButton_forward_slash->hasFocus())   { ui->pushButton_shift_left->setFocus();      }
#endif
            else if(ui->pushButton_clear->hasFocus())           { ui->pushButton_enter->setFocus();           }
            else if(ui->pushButton_enter->hasFocus())           { ui->pushButton_close->setFocus();           }
            else if(ui->pushButton_close->hasFocus())           { ui->pushButton_clear->setFocus();           }

            break;
		}
		case Qt::Key_Enter:
		{
            qDebug("Key_Eenter............");

            if(ui->pushButton_enter->hasFocus())
            {
                on_pushButton_enter_clicked();
            }
            else if(ui->pushButton_close->hasFocus())
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

            if(ui->pushButton_enter->hasFocus())
            {
                reject();
            }
            else if(ui->pushButton_close->hasFocus())
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
    }
	QDialog::keyPressEvent(event);
}

void UiKeyboardDialog::keyReleaseEvent(QKeyEvent *event)
{
	//qDebug(".............. UiSetupDialog key press keyDepth %d", keyDepth);
	return;
}
