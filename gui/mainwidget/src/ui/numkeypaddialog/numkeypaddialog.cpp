#include "numkeypaddialog.h"
#include "ui_numkeypaddialog.h"
#include <QtGui>
#include <QWSServer>
#include <appmgr/appmgr.h>

NumKeypadDialog::NumKeypadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumKeypadDialog)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->setupUi(this);

    msgBox = NULL;

    ui->frame_Body->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    ui->frame_Border->setStyleSheet(".QFrame{background: rgb(255,128, 64);}");
    ui->lineEdit_Text->setStyleSheet("QLineEdit{font:48px;background-color:rgb(50,57,83);color:white;border-width:1px;border-style:inset;border-color:white;}");
}
NumKeypadDialog::~NumKeypadDialog()
{
    delete ui;
}
void NumKeypadDialog::updateConfig(bool isNumberOnly)
{
    isPhoneNumber = false;

    if(isNumberOnly)
    {
        ui->lineEdit_Text->setMaxLength(5);
        isNetworkPort = true;
        isNetworkIPv4 = false;
        maxNumber = 65535;
    }
    else
    {
        ui->lineEdit_Text->setMaxLength(15);
        isNetworkPort = false;
        isNetworkIPv4 = true;
        maxNumber = 255;
    }

#if 0 // jungyver [16/12/19]
    if(isNumberOnly)
    {
        ui->pushButton_Dot->hide();
    }
#endif

    ui->lineEdit_Text->clear();
}
void NumKeypadDialog::setPhoneNumber(bool enable)
{
    isPhoneNumber = enable;
    ui->lineEdit_Text->setMaxLength(16);
}
void NumKeypadDialog::setText(QString text)
{
    ui->lineEdit_Text->setText(text);
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
    this->Text = ui->lineEdit_Text->text();
    this->accept();
}
void NumKeypadDialog::on_pushButton_Clear_clicked()
{
    ui->lineEdit_Text->clear();
}
void NumKeypadDialog::on_pushButton_Backspace_clicked()
{
    ui->lineEdit_Text->backspace();
}
void NumKeypadDialog::on_pushButton_0_clicked()
{
    if(this->checkMaximumNumber("0"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"0");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_1_clicked()
{
    if(this->checkMaximumNumber("1"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"1");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_2_clicked()
{
    if(this->checkMaximumNumber("2"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"2");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_3_clicked()
{
    if(this->checkMaximumNumber("3"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"3");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_4_clicked()
{
    if(this->checkMaximumNumber("4"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"4");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_5_clicked()
{
    if(this->checkMaximumNumber("5"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"5");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_6_clicked()
{
    if(this->checkMaximumNumber("6"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"6");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_7_clicked()
{
    if(this->checkMaximumNumber("7"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"7");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_8_clicked()
{
    if(this->checkMaximumNumber("8"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"8");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_9_clicked()
{
    if(this->checkMaximumNumber("9"))
    {
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+"9");
        checkAutoDot();
    }
}
void NumKeypadDialog::on_pushButton_Dot_clicked()
{
    if(this->checkMaximumNumber("."))
        ui->lineEdit_Text->setText(ui->lineEdit_Text->text()+".");
}
bool NumKeypadDialog::checkMaximumNumber(QString addVal)
{
    int curNum;
    int addNum;
    int ret = 0;
    QString currentStr = ui->lineEdit_Text->text();

    if(this->isPhoneNumber)
    {
        if(currentStr.length()<ui->lineEdit_Text->maxLength())
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

        if(currentStr.length()<ui->lineEdit_Text->maxLength())
        {
            if(addVal==".")
            {
                if(numOfDot>=3)
                {
                    if(currentStr.endsWith("."))
                    {
                        ui->lineEdit_Text->setText(currentStr+"0");
                    }

                    return false;
                }
                else
                {
                    if(currentStr.isEmpty())
                    {
                        ui->lineEdit_Text->setText(currentStr+"0");
                    }

                    if(currentStr.endsWith("."))
                    {
                        ui->lineEdit_Text->setText(currentStr+"0");
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

                        ui->lineEdit_Text->setText(currentStr+".");

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
                        ui->lineEdit_Text->setText(currentStr+".");
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
                msgBox = new TextMessageDialog(tr(" "),
                        tr("\nPlease input below 65535.\n"),
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
        QString currentStr = ui->lineEdit_Text->text();
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
                        ui->lineEdit_Text->setText(currentStr+".");
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
                 if(ui->pushButton_7->hasFocus())                { ui->pushButton_1->setFocus();                }
            else if(ui->pushButton_4->hasFocus())                { ui->pushButton_7->setFocus();                }
            else if(ui->pushButton_1->hasFocus())                { ui->pushButton_4->setFocus();                }
            else if(ui->pushButton_8->hasFocus())                { ui->pushButton_0->setFocus();                }
            else if(ui->pushButton_5->hasFocus())                { ui->pushButton_8->setFocus();                }
            else if(ui->pushButton_2->hasFocus())                { ui->pushButton_5->setFocus();                }
            else if(ui->pushButton_0->hasFocus())                { ui->pushButton_2->setFocus();                }
            else if(ui->pushButton_9->hasFocus())                { ui->pushButton_3->setFocus();                }
            else if(ui->pushButton_6->hasFocus())                { ui->pushButton_9->setFocus();                }
            else if(ui->pushButton_3->hasFocus())                { ui->pushButton_6->setFocus();                }
            else if(ui->pushButton_Backspace->hasFocus())        { ui->pushButton_Close->setFocus();            }
            else if(ui->pushButton_Clear->hasFocus())            { ui->pushButton_Backspace->setFocus();        }
            else if(ui->pushButton_Enter->hasFocus())            { ui->pushButton_Clear->setFocus();            }
            else if(ui->pushButton_Close->hasFocus())            { ui->pushButton_Enter->setFocus();            }

            return;
        }
        case Qt::Key_Down:
        {
                 if(ui->pushButton_7->hasFocus())                { ui->pushButton_4->setFocus();                }
            else if(ui->pushButton_4->hasFocus())                { ui->pushButton_1->setFocus();                }
            else if(ui->pushButton_1->hasFocus())                { ui->pushButton_7->setFocus();                }
            else if(ui->pushButton_8->hasFocus())                { ui->pushButton_5->setFocus();                }
            else if(ui->pushButton_5->hasFocus())                { ui->pushButton_2->setFocus();                }
            else if(ui->pushButton_2->hasFocus())                { ui->pushButton_0->setFocus();                }
            else if(ui->pushButton_0->hasFocus())                { ui->pushButton_8->setFocus();                }
            else if(ui->pushButton_9->hasFocus())                { ui->pushButton_6->setFocus();                }
            else if(ui->pushButton_6->hasFocus())                { ui->pushButton_3->setFocus();                }
            else if(ui->pushButton_3->hasFocus())                { ui->pushButton_9->setFocus();                }
            else if(ui->pushButton_Backspace->hasFocus())        { ui->pushButton_Clear->setFocus();            }
            else if(ui->pushButton_Clear->hasFocus())            { ui->pushButton_Enter->setFocus();            }
            else if(ui->pushButton_Enter->hasFocus())            { ui->pushButton_Close->setFocus();            }
            else if(ui->pushButton_Close->hasFocus())            { ui->pushButton_Backspace->setFocus();        }

            return;
        }
        case Qt::Key_Left:
        {
                 if(ui->pushButton_7->hasFocus())                { ui->pushButton_Backspace->setFocus();        }
            else if(ui->pushButton_8->hasFocus())                { ui->pushButton_7->setFocus();                }
            else if(ui->pushButton_9->hasFocus())                { ui->pushButton_8->setFocus();                }
            else if(ui->pushButton_Backspace->hasFocus())        { ui->pushButton_9->setFocus();                }
            else if(ui->pushButton_4->hasFocus())                { ui->pushButton_Clear->setFocus();            }
            else if(ui->pushButton_5->hasFocus())                { ui->pushButton_4->setFocus();                }
            else if(ui->pushButton_6->hasFocus())                { ui->pushButton_5->setFocus();                }
            else if(ui->pushButton_Clear->hasFocus())            { ui->pushButton_6->setFocus();                }
            else if(ui->pushButton_1->hasFocus())                { ui->pushButton_Enter->setFocus();            }
            else if(ui->pushButton_2->hasFocus())                { ui->pushButton_1->setFocus();                }
            else if(ui->pushButton_3->hasFocus())                { ui->pushButton_2->setFocus();                }
            else if(ui->pushButton_Enter->hasFocus())            { ui->pushButton_3->setFocus();                }
            else if(ui->pushButton_0->hasFocus())                { ui->pushButton_Close->setFocus();            }
            else if(ui->pushButton_Close->hasFocus())            { ui->pushButton_0->setFocus();                }

            return;
        }
        case Qt::Key_Right:
        {
                 if(ui->pushButton_7->hasFocus())                { ui->pushButton_8->setFocus();                }
            else if(ui->pushButton_8->hasFocus())                { ui->pushButton_9->setFocus();                }
            else if(ui->pushButton_9->hasFocus())                { ui->pushButton_Backspace->setFocus();        }
            else if(ui->pushButton_Backspace->hasFocus())        { ui->pushButton_7->setFocus();                }
            else if(ui->pushButton_4->hasFocus())                { ui->pushButton_5->setFocus();                }
            else if(ui->pushButton_5->hasFocus())                { ui->pushButton_6->setFocus();                }
            else if(ui->pushButton_6->hasFocus())                { ui->pushButton_Clear->setFocus();            }
            else if(ui->pushButton_Clear->hasFocus())            { ui->pushButton_4->setFocus();                }
            else if(ui->pushButton_1->hasFocus())                { ui->pushButton_2->setFocus();                }
            else if(ui->pushButton_2->hasFocus())                { ui->pushButton_3->setFocus();                }
            else if(ui->pushButton_3->hasFocus())                { ui->pushButton_Enter->setFocus();            }
            else if(ui->pushButton_Enter->hasFocus())            { ui->pushButton_1->setFocus();                }
            else if(ui->pushButton_0->hasFocus())                { ui->pushButton_Close->setFocus();            }
            else if(ui->pushButton_Close->hasFocus())            { ui->pushButton_0->setFocus();                }

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
