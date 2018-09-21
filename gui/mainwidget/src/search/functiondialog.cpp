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

#if 1 //yjsin [18/09/21] if text is long, change button size

    if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
    {
        buttonClose->setGeometry(705,495,230,91);
    }
#endif


    connect(buttonFilter, SIGNAL(clicked()), this, SLOT(onButtonFilter()));
    connect(buttonSort, SIGNAL(clicked()), this, SLOT(onButtonSort()));
    connect(buttonBackup, SIGNAL(clicked()), this, SLOT(onButtonBackup()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDelete()));
    connect(buttonClose, SIGNAL(clicked()), this, SLOT(onButtonClose()));

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
        buttonFilter->setText(QString("%1\n%2").arg(tr("Filter")).arg(logFilter));
    }
}
void FunctionDialog::setLogSort(QString sort)
{
    logSort=sort;

    if( logSort.compare(SYSTEM_LOG_ASC) == 0 )
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
    if( logSort.compare(SYSTEM_LOG_ASC) == 0 )  { setLogSort(SYSTEM_LOG_DESC); }
    else                                        { setLogSort(SYSTEM_LOG_ASC);  }
}

void FunctionDialog::onButtonBackup()
{
#if 1 //yjsin[18/08/30] Not implemented

    if(!msgBox)
    {
        msgBox = new TextMessageDialog("Log Backup", "onButtonBackup()", 2, this);
    }
    msgBox->setMsgAlignment(Qt::AlignCenter);
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
        msgBox = new TextMessageDialog("System Log Delete", tr("WARNING\n\n" "Do you want to delete all system logs?"), 0, this);
    }
    msgBox->setMsgAlignment(Qt::AlignCenter);
    msgBox->move((appmgr_get_mainwidget_width()-msgBox->sizeHint().width())/2,(appmgr_get_mainwidget_height()-msgBox->sizeHint().height())/2);

    if(msgBox->exec())
    {
        //delete all log
        SYSTEM_LOG_QUERY_S *pQuery = g_new0(SYSTEM_LOG_QUERY_S, 1);
        pQuery->type = SYSTEM_LOG_TYPE_EVENT;
        event_send(QUEUE_QT_CORE, QUEUE_SYSTEM_LOG, SYSTEM_LOG_DELETE_ALL, pQuery, g_free, NULL);
    }

    if(msgBox)
    {
        delete msgBox;
        msgBox=NULL;
    }
}

void FunctionDialog::onButtonClose()
{
    done(1);
}


void FunctionDialog::KeyPressEvent(int key)
{
    switch(key)
    {
        case Qt::Key_Up:
        {
            if(buttonFilter->hasFocus())        { buttonFilter->setFocus(); }
            else if(buttonSort->hasFocus())     { buttonClose->setFocus();  }
            else if(buttonBackup->hasFocus())   { buttonFilter->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonSort->setFocus();   }
            else if(buttonClose->hasFocus())    { buttonDelete->setFocus(); }

            break;
        }
        case Qt::Key_Down:
        {
            if(buttonFilter->hasFocus())        { buttonFilter->setFocus(); }
            else if(buttonSort->hasFocus())     { buttonDelete->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonFilter->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonClose->setFocus();  }
            else if(buttonClose->hasFocus())    { buttonSort->setFocus();   }

            break;
        }
        case Qt::Key_Left:
        {
            if(buttonFilter->hasFocus())        { buttonSort->setFocus();   }
            else if(buttonSort->hasFocus())     { buttonFilter->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonDelete->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonDelete->setFocus(); }
            else if(buttonClose->hasFocus())    { buttonClose->setFocus();  }

            break;
        }
        case Qt::Key_Right:
        {
            if(buttonFilter->hasFocus())        { buttonSort->setFocus();   }
            else if(buttonSort->hasFocus())     { buttonFilter->setFocus(); }
            else if(buttonBackup->hasFocus())   { buttonDelete->setFocus(); }
            else if(buttonDelete->hasFocus())   { buttonDelete->setFocus(); }
            else if(buttonClose->hasFocus())    { buttonClose->setFocus();  }

            break;
        }
        case Qt::Key_Enter:
        {
            if(buttonFilter->hasFocus())        { onButtonFilter(); }
            else if(buttonSort->hasFocus())     { onButtonSort();   }
            else if(buttonBackup->hasFocus())   { onButtonBackup(); }
            else if(buttonDelete->hasFocus())   { onButtonDelete(); }
            else if(buttonClose->hasFocus())    { onButtonClose();  }

            break;
        }
        case Qt::Key_Escape:
        {
            onButtonClose();

            break;
        }
        default:
        {
            break;
        }
    }
    return;
}

