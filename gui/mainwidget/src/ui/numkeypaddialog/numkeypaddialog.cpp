#include "numkeypaddialog.h"
#include <QtGui>
#include <QWSServer>
#include <appmgr/appmgr.h>
#include "main/mainglobal.h"

NumKeypadDialog::NumKeypadDialog(QWidget *parent) :
    QDialog(parent)
{
    if(mainHeight == 720)
    {
        Ui::NumKeypadDialog ui720;
        ui720.setupUi(this);

        frame_Border = ui720.frame_Border;
        frame_Body = ui720.frame_Body;
        lineEdit_Text = ui720.lineEdit_Text;
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
        pushButton_Backspace = ui720.pushButton_Backspace;
        pushButton_Clear = ui720.pushButton_Clear;
        pushButton_Close = ui720.pushButton_Close;
        pushButton_Dot = ui720.pushButton_Dot;
        pushButton_Enter = ui720.pushButton_Enter;
        pushButton_Not = ui720.pushButton_Not;

        lineEdit_Text->setStyleSheet("QLineEdit{font:48px;background-color:rgb(50,57,83);color:white;border-width:1px;border-style:inset;border-color:white;}");
    }
    else
    {
        Ui::NumKeypadDialog1080p ui1080;
        ui1080.setupUi(this);

        frame_Border = ui1080.frame_Border;
        frame_Body = ui1080.frame_Body;
        lineEdit_Text = ui1080.lineEdit_Text;
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
        pushButton_Backspace = ui1080.pushButton_Backspace;
        pushButton_Clear = ui1080.pushButton_Clear;
        pushButton_Close = ui1080.pushButton_Close;
        pushButton_Dot = ui1080.pushButton_Dot;
        pushButton_Enter = ui1080.pushButton_Enter;
        pushButton_Not = ui1080.pushButton_Not;

        lineEdit_Text->setStyleSheet("QLineEdit{font:70px;background-color:rgb(50,57,83);color:white;border-width:1px;border-style:inset;border-color:white;}");
    }

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    msgBox = NULL;

    frame_Body->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    frame_Border->setStyleSheet(".QFrame{background: rgb(255,128, 64);}");
}
NumKeypadDialog::~NumKeypadDialog()
{

}
void NumKeypadDialog::updateConfig(bool isNumberOnly)
{
    isPhoneNumber = false;

    if(isNumberOnly)
    {
        lineEdit_Text->setMaxLength(5);
        isNetworkPort = true;
        isNetworkIPv4 = false;
        maxNumber = 65535;
    }
    else
    {
        lineEdit_Text->setMaxLength(15);
        isNetworkPort = false;
        isNetworkIPv4 = true;
        maxNumber = 255;
    }

#if 0 // jungyver [16/12/19]
    if(isNumberOnly)
    {
        pushButton_Dot->hide();
    }
#endif

    lineEdit_Text->clear();
}
void NumKeypadDialog::setPhoneNumber(bool enable)
{
    isPhoneNumber = enable;
    lineEdit_Text->setMaxLength(16);
}
void NumKeypadDialog::setText(QString text)
{
    lineEdit_Text->setText(text);
}
void NumKeypadDialog::setMaximumNumber(int max)
{
    maxNumber = max;
}
QString NumKeypadDialog::text()
{
    return Text;
}
void NumKeypadDialog::on_pushButton_Close_clicked()
{
    this->reject();
}
void NumKeypadDialog::on_pushButton_Enter_clicked()
{
    this->Text = lineEdit_Text->text();
    this->accept();
}
void NumKeypadDialog::on_pushButton_Clear_clicked()
{
    lineEdit_Text->clear();
}
void NumKeypadDialog::on_pushButton_Backspace_clicked()
{
    lineEdit_Text->backspace();
}
void NumKeypadDialog::on_pushButton_0_clicked()
{
    if(this->checkMaximumNumber("0"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"0");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_1_clicked()
{
    if(this->checkMaximumNumber("1"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"1");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_2_clicked()
{
    if(this->checkMaximumNumber("2"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"2");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_3_clicked()
{
    if(this->checkMaximumNumber("3"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"3");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_4_clicked()
{
    if(this->checkMaximumNumber("4"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"4");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_5_clicked()
{
    if(this->checkMaximumNumber("5"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"5");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_6_clicked()
{
    if(this->checkMaximumNumber("6"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"6");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_7_clicked()
{
    if(this->checkMaximumNumber("7"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"7");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_8_clicked()
{
    if(this->checkMaximumNumber("8"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"8");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_9_clicked()
{
    if(this->checkMaximumNumber("9"))
    {
        lineEdit_Text->setText(lineEdit_Text->text()+"9");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_Dot_clicked()
{
    if(this->checkMaximumNumber("."))
        lineEdit_Text->setText(lineEdit_Text->text()+".");
}
bool NumKeypadDialog::checkMaximumNumber(QString addVal)
{
    int curNum;
    int addNum;
    int ret = 0;
    QString currentStr = lineEdit_Text->text();

    if(this->isPhoneNumber)
    {
        if(currentStr.length()<lineEdit_Text->maxLength())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if(this->isNetworkIPv4)
    {
        int numOfDot = currentStr.count(".");

        if(currentStr.length()<lineEdit_Text->maxLength())
        {
            if(addVal==".")
            {
                if(numOfDot>=3)
                {
                    if(currentStr.endsWith("."))
                    {
                        lineEdit_Text->setText(currentStr+"0");
                    }

                    return false;
                }
                else
                {
                    if(currentStr.isEmpty())
                    {
                        lineEdit_Text->setText(currentStr+"0");
                    }

                    if(currentStr.endsWith("."))
                    {
                        lineEdit_Text->setText(currentStr+"0");
                    }

                    return true;
                }
            }
            else if(currentStr.endsWith("."))
            {
                return true;
            }
            else
            {
                QStringList splitList = currentStr.split(".", QString::SkipEmptyParts);
                QString removedStr;

                if(splitList.count()<1)
                {
                    removedStr = currentStr;
                }
                else
                {
                    removedStr = splitList.last();
                }

                curNum = removedStr.toInt();
                addNum = addVal.toInt();

                if(curNum==0)
                {
                    if(numOfDot<3)
                    {
                        if(currentStr.isEmpty())
                        {
                            return true;
                        }

                        lineEdit_Text->setText(currentStr+".");

                        return true;
                    }
                    else
                    {
                        if(currentStr.endsWith("."))
                        {
                            return true;
                        }

                        return false;
                    }
                }
                else if(((curNum*10)+addNum)<=255)
                {
                    return true;
                }
                else
                {
                    if(numOfDot<3)
                    {
                        lineEdit_Text->setText(currentStr+".");
                        return true;
                    }

                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        curNum = currentStr.toInt();
        addNum = addVal.toInt();

        if(((curNum*10)+addNum) > this->maxNumber)
        {
            if(!msgBox)
            {
                msgBox = new TextMessageDialog(tr("INVALID INPUT"),
                        tr("Please input below 65535."),
                        2, this);
            }

            msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

            ret = msgBox->exec();

            delete msgBox;
            msgBox = NULL;

            return false;
        }
        else
        {
            return true;
        }
    }

}
void NumKeypadDialog::checkAutoDot()
{
    if(this->isNetworkIPv4)
    {
        QString currentStr = lineEdit_Text->text();
        int numOfDot = currentStr.count(".");

        if(numOfDot<3)
        {
            if(currentStr.endsWith(".")==false)
            {
                QStringList splitList = currentStr.split(".", QString::SkipEmptyParts);

                if(splitList.count()>0)
                {
                    QString removedStr = splitList.last();

                    if(removedStr.toInt()>25 || removedStr.toInt()==0)
                    {
                        lineEdit_Text->setText(currentStr+".");
                    }
                }
            }
        }
    }
}
void NumKeypadDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
                 if(pushButton_7->hasFocus())                { pushButton_1->setFocus();                }
            else if(pushButton_4->hasFocus())                { pushButton_7->setFocus();                }
            else if(pushButton_1->hasFocus())                { pushButton_4->setFocus();                }
            else if(pushButton_8->hasFocus())                { pushButton_0->setFocus();                }
            else if(pushButton_5->hasFocus())                { pushButton_8->setFocus();                }
            else if(pushButton_2->hasFocus())                { pushButton_5->setFocus();                }
            else if(pushButton_0->hasFocus())                { pushButton_2->setFocus();                }
            else if(pushButton_9->hasFocus())                { pushButton_3->setFocus();                }
            else if(pushButton_6->hasFocus())                { pushButton_9->setFocus();                }
            else if(pushButton_3->hasFocus())                { pushButton_6->setFocus();                }
            else if(pushButton_Backspace->hasFocus())        { pushButton_Close->setFocus();            }
            else if(pushButton_Clear->hasFocus())            { pushButton_Backspace->setFocus();        }
            else if(pushButton_Enter->hasFocus())            { pushButton_Clear->setFocus();            }
            else if(pushButton_Close->hasFocus())            { pushButton_Enter->setFocus();            }

            return;
        }
        case Qt::Key_Down:
        {
                 if(pushButton_7->hasFocus())                { pushButton_4->setFocus();                }
            else if(pushButton_4->hasFocus())                { pushButton_1->setFocus();                }
            else if(pushButton_1->hasFocus())                { pushButton_7->setFocus();                }
            else if(pushButton_8->hasFocus())                { pushButton_5->setFocus();                }
            else if(pushButton_5->hasFocus())                { pushButton_2->setFocus();                }
            else if(pushButton_2->hasFocus())                { pushButton_0->setFocus();                }
            else if(pushButton_0->hasFocus())                { pushButton_8->setFocus();                }
            else if(pushButton_9->hasFocus())                { pushButton_6->setFocus();                }
            else if(pushButton_6->hasFocus())                { pushButton_3->setFocus();                }
            else if(pushButton_3->hasFocus())                { pushButton_9->setFocus();                }
            else if(pushButton_Backspace->hasFocus())        { pushButton_Clear->setFocus();            }
            else if(pushButton_Clear->hasFocus())            { pushButton_Enter->setFocus();            }
            else if(pushButton_Enter->hasFocus())            { pushButton_Close->setFocus();            }
            else if(pushButton_Close->hasFocus())            { pushButton_Backspace->setFocus();        }

            return;
        }
        case Qt::Key_Left:
        {
                 if(pushButton_7->hasFocus())                { pushButton_Backspace->setFocus();        }
            else if(pushButton_8->hasFocus())                { pushButton_7->setFocus();                }
            else if(pushButton_9->hasFocus())                { pushButton_8->setFocus();                }
            else if(pushButton_Backspace->hasFocus())        { pushButton_9->setFocus();                }
            else if(pushButton_4->hasFocus())                { pushButton_Clear->setFocus();            }
            else if(pushButton_5->hasFocus())                { pushButton_4->setFocus();                }
            else if(pushButton_6->hasFocus())                { pushButton_5->setFocus();                }
            else if(pushButton_Clear->hasFocus())            { pushButton_6->setFocus();                }
            else if(pushButton_1->hasFocus())                { pushButton_Enter->setFocus();            }
            else if(pushButton_2->hasFocus())                { pushButton_1->setFocus();                }
            else if(pushButton_3->hasFocus())                { pushButton_2->setFocus();                }
            else if(pushButton_Enter->hasFocus())            { pushButton_3->setFocus();                }
            else if(pushButton_0->hasFocus())                { pushButton_Close->setFocus();            }
            else if(pushButton_Close->hasFocus())            { pushButton_0->setFocus();                }

            return;
        }
        case Qt::Key_Right:
        {
                 if(pushButton_7->hasFocus())                { pushButton_8->setFocus();                }
            else if(pushButton_8->hasFocus())                { pushButton_9->setFocus();                }
            else if(pushButton_9->hasFocus())                { pushButton_Backspace->setFocus();        }
            else if(pushButton_Backspace->hasFocus())        { pushButton_7->setFocus();                }
            else if(pushButton_4->hasFocus())                { pushButton_5->setFocus();                }
            else if(pushButton_5->hasFocus())                { pushButton_6->setFocus();                }
            else if(pushButton_6->hasFocus())                { pushButton_Clear->setFocus();            }
            else if(pushButton_Clear->hasFocus())            { pushButton_4->setFocus();                }
            else if(pushButton_1->hasFocus())                { pushButton_2->setFocus();                }
            else if(pushButton_2->hasFocus())                { pushButton_3->setFocus();                }
            else if(pushButton_3->hasFocus())                { pushButton_Enter->setFocus();            }
            else if(pushButton_Enter->hasFocus())            { pushButton_1->setFocus();                }
            else if(pushButton_0->hasFocus())                { pushButton_Close->setFocus();            }
            else if(pushButton_Close->hasFocus())            { pushButton_0->setFocus();                }

            return;
        }
        case Qt::Key_Enter:
        {
            QWSServer::sendKeyEvent(-1, Qt::Key_Space,0, true, false);
            QWSServer::sendKeyEvent(-1, Qt::Key_Space,0, false, false);

            return;
        }
        case Qt::Key_Escape:
        {
            reject();

            return;
        }
        default:
        {
            return;
        }
    }
}
