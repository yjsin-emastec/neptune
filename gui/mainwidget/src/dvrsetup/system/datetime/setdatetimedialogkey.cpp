#include <QtGui>
#include "setdatetimedialog.h"

void SetDateTimeDialog::mousePressEvent(QMouseEvent *event)
{
    emit signalResetTimer();
}
void SetDateTimeDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:

            if(isKeyLock)
            {
                changeFocusedItemValue(1);
            }
            else
            {
                     if(buttonTimeFormat->hasFocus())                               { buttonBox->button(QDialogButtonBox::Ok)->setFocus();        }
                else if(buttonGpsSync->hasFocus())                                  { buttonBox->button(QDialogButtonBox::Cancel)->setFocus();    }
                else if(comboBoxTimeZone->hasFocus())                               { buttonTimeFormat->setFocus();                               }
                else if(comboBoxTime_1->hasFocus())                                 { comboBoxTimeZone->setFocus();                               }
                else if(comboBoxTime_2->hasFocus())                                 { comboBoxTimeZone->setFocus();                               }
                else if(comboBoxTime_3->hasFocus())                                 { comboBoxTimeZone->setFocus();                               }
                else if(comboBoxTime_4->hasFocus())                                 { comboBoxTime_1->setFocus();                                 }
                else if(comboBoxTime_5->hasFocus())                                 { comboBoxTime_2->setFocus();                                 }
                else if(comboBoxTime_6->hasFocus())                                 { comboBoxTime_3->setFocus();                                 }
                else if(buttonBox->button(QDialogButtonBox::Ok)->hasFocus())        { comboBoxTime_5->setFocus();                                 }
                else if(buttonBox->button(QDialogButtonBox::Cancel)->hasFocus())    { comboBoxTime_6->setFocus();                                 }
            }

            return;

        case Qt::Key_Down:

            if(isKeyLock)
            {
                changeFocusedItemValue(0);
            }
            else
            {
                     if(buttonTimeFormat->hasFocus())                               { comboBoxTimeZone->setFocus();                               }
                else if(buttonGpsSync->hasFocus())                                  { comboBoxTimeZone->setFocus();                               }
                else if(comboBoxTimeZone->hasFocus())                               { comboBoxTime_2->setFocus();                                 }
                else if(comboBoxTime_1->hasFocus())                                 { comboBoxTime_4->setFocus();                                 }
                else if(comboBoxTime_2->hasFocus())                                 { comboBoxTime_5->setFocus();                                 }
                else if(comboBoxTime_3->hasFocus())                                 { comboBoxTime_6->setFocus();                                 }
                else if(comboBoxTime_4->hasFocus())                                 { buttonTimeFormat->setFocus();                               }
                else if(comboBoxTime_5->hasFocus())                                 { buttonBox->button(QDialogButtonBox::Ok)->setFocus();        }
                else if(comboBoxTime_6->hasFocus())                                 { buttonBox->button(QDialogButtonBox::Cancel)->setFocus();    }
                else if(buttonBox->button(QDialogButtonBox::Ok)->hasFocus())        { buttonTimeFormat->setFocus();                               }
                else if(buttonBox->button(QDialogButtonBox::Cancel)->hasFocus())    { buttonGpsSync->setFocus();                                  }
            }

            return;

        case Qt::Key_Left:

            if(isKeyLock)
            {
                ;
            }
            else
            {
                     if(buttonTimeFormat->hasFocus())                               { buttonGpsSync->setFocus();                                  }
                else if(buttonGpsSync->hasFocus())                                  { buttonTimeFormat->setFocus();                               }
                else if(comboBoxTime_1->hasFocus())                                 { comboBoxTime_3->setFocus();                                 }
                else if(comboBoxTime_2->hasFocus())                                 { comboBoxTime_1->setFocus();                                 }
                else if(comboBoxTime_3->hasFocus())                                 { comboBoxTime_2->setFocus();                                 }
                else if(comboBoxTime_4->hasFocus())                                 { comboBoxTime_6->setFocus();                                 }
                else if(comboBoxTime_5->hasFocus())                                 { comboBoxTime_4->setFocus();                                 }
                else if(comboBoxTime_6->hasFocus())                                 { comboBoxTime_5->setFocus();                                 }
                else if(buttonBox->button(QDialogButtonBox::Ok)->hasFocus())        { buttonBox->button(QDialogButtonBox::Cancel)->setFocus();    }
                else if(buttonBox->button(QDialogButtonBox::Cancel)->hasFocus())    { buttonBox->button(QDialogButtonBox::Ok)->setFocus();        }
            }

            return;

        case Qt::Key_Right:

            if(isKeyLock)
            {
                ;
            }
            else
            {
                     if(buttonTimeFormat->hasFocus())                               { buttonGpsSync->setFocus();                                  }
                else if(buttonGpsSync->hasFocus())                                  { buttonTimeFormat->setFocus();                               }
                else if(comboBoxTime_1->hasFocus())                                 { comboBoxTime_2->setFocus();                                 }
                else if(comboBoxTime_2->hasFocus())                                 { comboBoxTime_3->setFocus();                                 }
                else if(comboBoxTime_3->hasFocus())                                 { comboBoxTime_1->setFocus();                                 }
                else if(comboBoxTime_4->hasFocus())                                 { comboBoxTime_5->setFocus();                                 }
                else if(comboBoxTime_5->hasFocus())                                 { comboBoxTime_6->setFocus();                                 }
                else if(comboBoxTime_6->hasFocus())                                 { comboBoxTime_4->setFocus();                                 }
                else if(buttonBox->button(QDialogButtonBox::Ok)->hasFocus())        { buttonBox->button(QDialogButtonBox::Cancel)->setFocus();    }
                else if(buttonBox->button(QDialogButtonBox::Cancel)->hasFocus())    { buttonBox->button(QDialogButtonBox::Ok)->setFocus();        }
            }

            return;

        case Qt::Key_Enter:

                 if(comboBoxTimeZone->hasFocus())                                   { isKeyLock = 1; return;                                      }
            else if(comboBoxTime_1->hasFocus())                                     { isKeyLock = 1; return;                                      }
            else if(comboBoxTime_2->hasFocus())                                     { isKeyLock = 1; return;                                      }
            else if(comboBoxTime_3->hasFocus())                                     { isKeyLock = 1; return;                                      }
            else if(comboBoxTime_4->hasFocus())                                     { isKeyLock = 1; return;                                      }
            else if(comboBoxTime_5->hasFocus())                                     { isKeyLock = 1; return;                                      }
            else if(comboBoxTime_6->hasFocus())                                     { isKeyLock = 1; return;                                      }

            break;

        case Qt::Key_Escape:

            if(isKeyLock)                                                           { isKeyLock = 0; return;                                      }
            else                                                                    { reject();      return;                                      }

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
