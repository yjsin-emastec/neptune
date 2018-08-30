#include <QtGui>
#include "functiondialog.h"
#include "main/mainglobal.h"
#include "main/mainwidget.h"
#include "textmessagebox/textmessagedialog.h"
#include "ui/keyboard/uikeyboarddialog.h"

FunctionDialog::FunctionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255,128,64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
    setAutoFillBackground(true);

    connect(buttonFilter, SIGNAL(clicked()), this, SLOT(onButtonFilter()));
    connect(buttonSort, SIGNAL(clicked()), this, SLOT(onButtonSort()));
    connect(buttonBackup, SIGNAL(clicked()), this, SLOT(onButtonBackup()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDelete()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(onButtonOk()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancel()));

    logSort="";
    logFilter="";
    keyboard=NULL;
    msgBox=NULL;
    buttonFilter->setFocus();
}

FunctionDialog::~FunctionDialog()
{
}

void FunctionDialog::onButtonFilter()
{
    int maxLen=10;
    QString str;

    if(!keyboard)
    {
        keyboard=new UiKeyboardDialog(this);
    }

    keyboard->setKeyboadProperty(str, logFilter, false, maxLen);
    keyboard->move((mainWidth-keyboard->width())/2, (mainHeight-keyboard->height())/2);

    if(keyboard->exec())
    {
        setLogFilter(keyboard->text);
    }

    delete keyboard;
    keyboard = NULL;
}

QString FunctionDialog::getLogFilter()
{
    return logFilter;
}
QString FunctionDialog::getLogSort()
{
    return logSort;
}
void FunctionDialog::setLogFilter(QString filter)
{
    logFilter=filter;

    if( logFilter.length() == 0 )
    {
        buttonFilter->setText(tr("Filter"));
    }
    else
    {
        buttonFilter->setText(tr("%1\n%2").arg("Filter").arg(logFilter));
    }
}
void FunctionDialog::setLogSort(QString sort)
{
    logSort=sort;

    if(logSort.compare(SYSTEM_LOG_DESC))
    {
        buttonSort->setText(QString("%1\n%2").arg(tr("Sort Order")).arg(tr("Ascending")));
    }
    else
    {
        buttonSort->setText(QString("%1\n%2").arg(tr("Sort Order")).arg(tr("Descending")));
    }
}

void FunctionDialog::onButtonSort()
{
    if( logSort.compare(SYSTEM_LOG_DESC) )  { setLogSort(SYSTEM_LOG_DESC); }
    else                                    { setLogSort(SYSTEM_LOG_ASC);  }
}

void FunctionDialog::onButtonBackup()
{
#if 1 //yjsin[18/08/30] Not implemented

    if(!msgBox)
    {
        msgBox = new TextMessageDialog("Log Backup", tr("onButtonBackup()"), 2, this);
    }
    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

    if(msgBox->exec())
    {
        delete msgBox;
        msgBox=NULL;
    }
#endif
}

void FunctionDialog::onButtonDelete()
{
    //confirm message
    if(!msgBox)
    {
        msgBox = new TextMessageDialog("Log Delete", tr("\t\t\t WARNING\n\n" "Do you want to delete all logs?"), 0, this);
    }
    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

    if(msgBox->exec())
    {
        //delete all log
        SYSTEM_LOG_QUERY_S *pQuery = g_new0(SYSTEM_LOG_QUERY_S, 1);
        pQuery->type = SYSTEM_LOG_TYPE_EVENT;
        event_send(QUEUE_QT_CORE, QUEUE_SYSTEM_LOG, SYSTEM_LOG_DELETE_ALL, pQuery, g_free, NULL);

        delete msgBox;
        msgBox=NULL;

        //print result message
        msgBox = new TextMessageDialog("Log Delete", tr("\t\tNotice\n\n" "All log was deleted."), 2, this);
        msgBox->exec();
    }

    if(msgBox)
    {
        delete msgBox;
        msgBox=NULL;
    }
}

void FunctionDialog::onButtonOk()
{
    accept();
}

void FunctionDialog::onButtonCancel()
{
    reject();
}


void FunctionDialog::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if(buttonFilter->hasFocus())        { buttonBackup->setFocus(); }
            else if(buttonSort->hasFocus())     { buttonCancel->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonFilter->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonSort->setFocus();   }
            else if(buttonOk->hasFocus())       { buttonDelete->setFocus(); }
            else if(buttonCancel->hasFocus())   { buttonDelete->setFocus(); }

            break;
        }
        case Qt::Key_Down:
        {
            if(buttonFilter->hasFocus())        { buttonBackup->setFocus(); }
            else if(buttonSort->hasFocus())     { buttonDelete->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonFilter->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonCancel->setFocus(); }
            else if(buttonOk->hasFocus())       { buttonSort->setFocus();   }
            else if(buttonCancel->hasFocus())   { buttonSort->setFocus();   }

            break;
        }
        case Qt::Key_Left:
        {
            if(buttonFilter->hasFocus())        { buttonSort->setFocus();   }
            else if(buttonSort->hasFocus())     { buttonFilter->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonDelete->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonBackup->setFocus(); }
            else if(buttonOk->hasFocus())       { buttonCancel->setFocus(); }
            else if(buttonCancel->hasFocus())   { buttonOk->setFocus();     }

            break;
        }
        case Qt::Key_Right:
        {
            if(buttonFilter->hasFocus())        { buttonSort->setFocus();   }
            else if(buttonSort->hasFocus())     { buttonFilter->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonDelete->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonBackup->setFocus(); }
            else if(buttonOk->hasFocus())       { buttonCancel->setFocus(); }
            else if(buttonCancel->hasFocus())   { buttonOk->setFocus();     }

            break;
        }
        case Qt::Key_Enter:
        {
            if(buttonFilter->hasFocus())        { onButtonFilter();         }
            else if(buttonSort->hasFocus())     { onButtonSort();           }
            else if(buttonBackup->hasFocus())   { onButtonBackup();         }
            else if(buttonDelete->hasFocus())   { onButtonDelete();         }
            else if(buttonOk->hasFocus())       { onButtonOk();             }
            else if(buttonCancel->hasFocus())   { onButtonCancel();         }

            break;
        }
        case Qt::Key_Escape:
        {
            onButtonCancel();

            break;
        }
        default:
        {
            return;
        }
    }
    return;
}
