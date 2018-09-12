#include <QtGui>
#include "searchdialog.h"
#include "calendarpage.h"
#include "eventlogpage.h"
#include "systemlogpage.h"
#include "Event.h"
#include "main/mainglobal.h"

SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	setPalette(QPalette(QColor(255, 128, 64)));
	frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
	labelSearch->setStyleSheet("color:white; font-weight:bold; font-size:48px;");

	pbChBit = 0xf;
	pbSplit = Split_4;
	SelectPbSplit = pbType = recType = 0;

	connect(buttonNormal, SIGNAL(released()), this, SLOT(onNormal()));
	connect(buttonEvent,  SIGNAL(released()), this, SLOT(onEvent()));
	connect(buttonLog,    SIGNAL(released()), this, SLOT(onLog()));
	connect(buttonClose,  SIGNAL(released()), this, SLOT(onButtonClose(void)));

    calendarPage = new CalendarPage(this);
	connect(calendarPage, SIGNAL(previousSearch (int)), this, SLOT(onHideCalendarPage (int)));
	connect(calendarPage, SIGNAL(closeSearch    (int)), this, SLOT(onButtonClose      (int)));
	connect(calendarPage, SIGNAL(startPlayback  ()),    this, SLOT(onStartPlayback    ()));

    eventPage    = new EventLogPage(this);
	connect(eventPage, SIGNAL(previousSearch (int)), this, SLOT(onHideCalendarPage (int)));
	connect(eventPage, SIGNAL(closeSearch    (int)), this, SLOT(onButtonClose      (int)));
	connect(eventPage, SIGNAL(startPlayback  ()),    this, SLOT(onStartPlayback    ()));

    systemLogPage= new SystemLogPage(this);
    connect(systemLogPage, SIGNAL(previousSearch(int)), this, SLOT(onHideCalendarPage(int)));
    connect(systemLogPage, SIGNAL(closeSearch   (int)),       this, SLOT(onButtonClose(int)));

	connect(this, SIGNAL(searchDataRead()), calendarPage, SLOT(onUpdateTimeLine()));

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(calendarPage);
    stackedLayout->addWidget(eventPage);
    stackedLayout->addWidget(systemLogPage);
	setLayout(stackedLayout);

	eventPage->hide();
	calendarPage->hide();
    systemLogPage->hide();
}
SearchDialog::~SearchDialog()
{
}
void SearchDialog::onButtonClose(void)
{
    QDialog::reject();

    buttonNormal       ->show();
    buttonEvent        ->show();
    buttonClose        ->show();
    buttonLog          ->show();
    labelSearch        ->show();
    calendarPage       ->hide();
    eventPage          ->hide();
    systemLogPage      ->hide();
}
void SearchDialog::onButtonClose(int type)
{
    this->onButtonClose();

    switch(type)
    {
        case 0: { appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Normal Exit"); } break;
        case 1: { appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Event Exit" ); } break;
        case 2: { appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Log Exit" ); } break;
    }
}
void SearchDialog::onStartPlayback(void)
{
	QDialog::accept();
}
void SearchDialog::onHideCalendarPage(int type)
{
	buttonNormal->show();
	buttonEvent->show();
	buttonClose->show();
    buttonLog->show();
    labelSearch->show();

	calendarPage->hide();
	eventPage->hide();
    systemLogPage->hide();

	switch(type)
	{
		case 0: { buttonNormal->setFocus(); appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Normal Exit"); } break;
		case 1: { buttonEvent ->setFocus(); appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Event Exit" ); } break;
		case 2: { buttonLog   ->setFocus(); appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Log Exit"   ); } break;
	}
}
void SearchDialog::onEvent(void)
{
	buttonNormal->hide();
	buttonEvent->hide();
	buttonClose->hide();
    buttonLog->hide();
    labelSearch->hide();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Event Enter" );
	eventPage->resetSearch();
    stackedLayout->setCurrentWidget(eventPage);
	eventPage->show();
}
void SearchDialog::onNormal(void)
{
	buttonNormal->hide();
	buttonEvent->hide();
	buttonClose->hide();
    buttonLog->hide();
    labelSearch->hide();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Normal Enter" );
	calendarPage->ResetSearch();
	calendarPage->QuerySearchData(0);
	calendarPage->UpdateSelectTime();
	stackedLayout->setCurrentWidget(calendarPage);
	calendarPage->show();
}

void SearchDialog::onLog(void)
{
    buttonNormal->hide();
    buttonEvent->hide();
    buttonClose->hide();
    buttonLog->hide();
    labelSearch->hide();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Log Enter" );
    systemLogPage->resetLog();
    stackedLayout->setCurrentWidget(systemLogPage);
    systemLogPage->show();
}

void SearchDialog::onQueryLogCount()
{
	eventPage->onQueryLogCount();
}
void SearchDialog::onQueryLogData()
{
	eventPage->onQueryLogData();
}
void SearchDialog::onSystemLogCount()
{
    systemLogPage->onQueryLogCount();
}
void SearchDialog::onSystemLogData()
{
    systemLogPage->onQueryLogData();
}
void SearchDialog::onSystemLogBackup()
{
    // systemLogPage->onQueryLogBackup();
}
void SearchDialog::onSearchDataUpdate(int type)
{
	emit searchDataRead();
}
void SearchDialog::onSearchCalendarUpdate(int type)
{
	calendarPage->UpdateDates(type);
}

void SearchDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if(calendarPage->isVisible())   			{ calendarPage->KeyPressEvent(Qt::Key_Up);      }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_Up);         }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Up);     }
            else
            {
                if(buttonNormal->hasFocus())            { buttonLog->setFocus();    }
                else if(buttonEvent->hasFocus())        { buttonClose->setFocus();  }
                else if(buttonLog->hasFocus())          { buttonNormal->setFocus(); }
                else if(buttonClose->hasFocus())        { buttonEvent->setFocus();  }
            }

            return;
        }
        case Qt::Key_Down:
        {
            if(calendarPage->isVisible())               { calendarPage->KeyPressEvent(Qt::Key_Down);    }
            else if(eventPage->isVisible()) 			{ eventPage->KeyPressEvent(Qt::Key_Down);       }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Down);   }
            else
            {
                if(buttonNormal->hasFocus())            { buttonLog->setFocus();    }
                else if(buttonEvent->hasFocus())        { buttonClose->setFocus();  }
                else if(buttonLog->hasFocus())          { buttonNormal->setFocus(); }
                else if(buttonClose->hasFocus())        { buttonEvent->setFocus();  }
            }

            return;
        }
        case Qt::Key_Left:
        {
            if(calendarPage->isVisible())           	{ calendarPage->KeyPressEvent(Qt::Key_Left);    }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_Left);       }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Left);   }
            else
            {
                if(buttonNormal->hasFocus())            { buttonEvent->setFocus();  }
                else if(buttonEvent->hasFocus())		{ buttonNormal->setFocus(); }
                else if(buttonLog->hasFocus())          { buttonClose->setFocus();  }
                else if(buttonClose->hasFocus())        { buttonLog->setFocus();    }
            }

            return;
        }
        case Qt::Key_Right:
        {
            if(calendarPage->isVisible())   			{ calendarPage->KeyPressEvent(Qt::Key_Right);   }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_Right);      }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Right);  }
            else
            {
                if(buttonNormal->hasFocus())            { buttonEvent->setFocus();  }
                else if(buttonEvent->hasFocus())		{ buttonNormal->setFocus(); }
                else if(buttonLog->hasFocus())          { buttonClose->setFocus();  }
                else if(buttonClose->hasFocus())        { buttonLog->setFocus();    }
            }

            return;
        }
        case Qt::Key_Enter:
        {
            if(calendarPage->isVisible())               { calendarPage->KeyPressEvent(Qt::Key_Enter);   }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_Enter);      }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Enter);  }
            else
            {
                if(buttonNormal->hasFocus())            { onNormal();               }
                else if(buttonEvent->hasFocus())        { onEvent();                }
                else if(buttonLog->hasFocus())          { onLog();                  }
                else if(buttonClose->hasFocus())        { this->onButtonClose();    }
            }

            return;
        }
        case Qt::Key_Escape:
        {
            if(calendarPage->isVisible())               { calendarPage->KeyPressEvent(Qt::Key_Escape);  }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_Escape);     }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Escape); }
            else                                        { this->onButtonClose();                        }

            return;
        }
        case Qt::Key_PageUp:
        {
            if(calendarPage->isVisible())               { calendarPage->KeyPressEvent(Qt::Key_PageUp);  }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_PageUp);     }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_PageUp); }

            return;
        }
        case Qt::Key_PageDown:
        {
            if(calendarPage->isVisible())               { calendarPage->KeyPressEvent(Qt::Key_PageDown);    }
            else if(eventPage->isVisible())             { eventPage->KeyPressEvent(Qt::Key_PageDown);       }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_PageDown);   }

            return;
        }
        default:
        {
            return;
        }
    }

    QDialog::keyPressEvent(event);
}
