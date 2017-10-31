#include <QtGui>
#include "logindialog.h"

void LoginDialog::keyPressEvent(QKeyEvent *event)
{
    //qDebug("event->key() : %d", event->key());

    switch(event->key())
    {
        case Qt::Key_Up:

                 if(lineEditPassword->hasFocus()) { buttonOk->setFocus();         }
            else if(buttonEdit->hasFocus())       { buttonCancel->setFocus();     }
            else if(buttonCancel->hasFocus())     { buttonEdit->setFocus();       }
            else if(buttonOk->hasFocus())         { lineEditPassword->setFocus(); }

            return;

        case Qt::Key_Down:

                 if(lineEditPassword->hasFocus()) { buttonOk->setFocus();         }
            else if(buttonEdit->hasFocus())       { buttonCancel->setFocus();     }
            else if(buttonCancel->hasFocus())     { buttonEdit->setFocus();       }
            else if(buttonOk->hasFocus())         { lineEditPassword->setFocus(); }

            return;

        case Qt::Key_Right:

                 if(buttonOk->hasFocus())         { buttonCancel->setFocus();     }
            else if(buttonCancel->hasFocus())     { buttonOk->setFocus();         }
            else if(buttonEdit->hasFocus())       { lineEditPassword->setFocus(); }
            else if(lineEditPassword->hasFocus()) { buttonEdit->setFocus();       }

            return;

        case Qt::Key_Left:

                 if(buttonOk->hasFocus())         { buttonCancel->setFocus();     }
            else if(buttonCancel->hasFocus())     { buttonOk->setFocus();         }
            else if(buttonEdit->hasFocus())       { lineEditPassword->setFocus(); }
            else if(lineEditPassword->hasFocus()) { buttonEdit->setFocus();       }

            return;

        case Qt::Key_0:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"0");
            }

            return;

        case Qt::Key_1:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"1");
            }

            return;

        case Qt::Key_2:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"2");
            }

            return;

        case Qt::Key_3:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"3");
            }

            return;

        case Qt::Key_4:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"4");
            }

            return;

        case Qt::Key_5:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"5");
            }

            return;

        case Qt::Key_6:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"6");
            }

            return;

        case Qt::Key_7:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"7");
            }

            return;

        case Qt::Key_8:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"8");
            }

            return;

        case Qt::Key_9:

            if(lineEditPassword->hasFocus())
            {
                lineEditPassword->setText(lineEditPassword->text()+"9");
            }

            return;

        case Qt::Key_Enter:

            if(lineEditPassword->hasFocus())
            {
                if(lineEditPassword->text()=="")
                {
                    showKeyboard();
                }
                else
                {
                    PasswordString = lineEditPassword->text();
                    checkPassword();
                }
            }
            else if(buttonOk->hasFocus())
            {
                checkPassword();
            }
            else if(buttonCancel->hasFocus())
            {
                reject();
            }
            else if(buttonEdit->hasFocus())
            {
                showKeyboard();
            }

            return;

        case Qt::Key_Escape:

            if(lineEditPassword->hasFocus()==1 && lineEditPassword->text()!="")
            {
                lineEditPassword->setText("");
            }
            else
            {
                reject();
            }

            return;
    }

    QDialog::keyPressEvent(event);
}
