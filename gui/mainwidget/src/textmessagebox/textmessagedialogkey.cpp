#include <QtGui>
#include "textmessagedialog.h"
#include "../main/mainglobal.h"

void TextMessageDialog::mousePressEvent(QMouseEvent *event)
{
    emit signalResetTimer();
}
void TextMessageDialog::keyPressEvent(QKeyEvent *event)
{
    emit signalResetTimer();
    QKeyEvent *key = NULL;

    switch (event->key()) 
    {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier, QString(QChar(Qt::Key_Tab)));
            QApplication::sendEvent(this , key);

            return;

        case Qt::Key_Enter:

            if(msgType == 3 || msgType == 5 || msgType == 9 || msgType == 13)
            {
                return;
            }
            else if(msgType == 4)
            {
                if(this->buttonOk->hasFocus())
                {
                    buttonReject();
                }
                else
                {
                    buttonAccept();
                }
            }
            else
            {
                if(this->buttonOk->hasFocus())
                {
                    buttonAccept();
                }
                else
                {
                    buttonReject();
                }
            }

            break;

        case Qt::Key_Escape:

            if(msgBoxEsckey)
            {
                break;
            }
            else
            {
                return;  // GOTO Test Mode's ESC BLOCKING
            }

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
