#include <QtGui>
#include "searchdialog.h"
#include "calendarpage.h"
#include "eventlogpage.h"
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
	connect(buttonEvent, SIGNAL(released()), this, SLOT(onEvent()));
	connect(buttonClose, SIGNAL(released()), this, SLOT(onButtonClose()));

    calendarPage = new CalendarPage(this);
	connect(calendarPage, SIGNAL(previousSearch(int)), this, SLOT(onHideCalendarPage(int)));
	connect(calendarPage, SIGNAL(closeSearch()), this, SLOT(onButtonClose()));
	connect(calendarPage, SIGNAL(startPlayback()), this, SLOT(onStartPlayback()));

    eventPage    = new EventLogPage(this);
	connect(eventPage, SIGNAL(previousSearch(int)), this, SLOT(onHideCalendarPage(int)));
	connect(eventPage, SIGNAL(closeSearch()), this, SLOT(onButtonClose()));
	connect(eventPage, SIGNAL(startPlayback()), this, SLOT(onStartPlayback()));

	connect(this, SIGNAL(searchDataRead()), calendarPage, SLOT(onUpdateTimeLine()));

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(calendarPage);
    stackedLayout->addWidget(eventPage);
	setLayout(stackedLayout);

	eventPage->hide();
	calendarPage->hide();
}
SearchDialog::~SearchDialog()
{
}
void SearchDialog::onButtonClose(void)
{
	QDialog::reject();

	buttonNormal->show();
	buttonEvent->show();
	buttonClose->show();

	calendarPage->hide();
	eventPage->hide();
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

	calendarPage->hide();
	eventPage->hide();

	switch(type)
	{
		case 0: { buttonNormal->setFocus(); } break;
		case 1: { buttonEvent->setFocus();  } break;
	}
}
void SearchDialog::onEvent(void)
{
	buttonNormal->hide();
	buttonEvent->hide();
	buttonClose->hide();
	eventPage->resetSearch();
    stackedLayout->setCurrentWidget(eventPage);
	eventPage->show();
}
void SearchDialog::onNormal(void)
{
	buttonNormal->hide();
	buttonEvent->hide();
	buttonClose->hide();
	calendarPage->ResetSearch();
	calendarPage->QuerySearchData(0);
	calendarPage->UpdateSelectTime();
	stackedLayout->setCurrentWidget(calendarPage);
	calendarPage->show();
}
void SearchDialog::onQueryLogCount()
{
	eventPage->onQueryLogCount();
}
void SearchDialog::onQueryLogData()
{
	eventPage->onQueryLogData();
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
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_Up);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_Up);
			}
			else
			{
				if(buttonEvent->hasFocus())
				{
					buttonClose->setFocus();
				}
				else if(buttonClose->hasFocus())
				{
					buttonEvent->setFocus();
				}
			}

			return;
		}
		case Qt::Key_Down:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_Down);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_Down);
			}
			else
			{
				if(buttonEvent->hasFocus())
				{
					buttonClose->setFocus();
				}
				else if(buttonClose->hasFocus())
				{
					buttonEvent->setFocus();
				}
			}

			return;
		}
		case Qt::Key_Left:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_Left);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_Left);
			}
			else
			{
				if(buttonNormal->hasFocus())
				{
					buttonEvent->setFocus();
				}
				else if(buttonEvent->hasFocus())
				{
					buttonNormal->setFocus();
				}
			}

			return;
		}
		case Qt::Key_Right:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_Right);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_Right);
			}
			else
			{
				if(buttonNormal->hasFocus())
				{
					buttonEvent->setFocus();
				}
				else if(buttonEvent->hasFocus())
				{
					buttonNormal->setFocus();
				}
			}

			return;
		}
		case Qt::Key_Enter:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_Enter);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_Enter);
			}
			else
			{
				if(buttonNormal->hasFocus())
				{
					onNormal();
				}
				else if(buttonEvent->hasFocus())
				{
					onEvent();
				}
				else if(buttonClose->hasFocus())
				{
					onButtonClose();
				}
			}

			return;
		}
		case Qt::Key_Escape:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_Escape);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_Escape);
			}
			else
			{
				onButtonClose();
			}

			return;
		}
		case Qt::Key_PageUp:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_PageUp);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_PageUp);
			}

			return;
		}
		case Qt::Key_PageDown:
		{
			if(calendarPage->isVisible())
			{
				calendarPage->KeyPressEvent(Qt::Key_PageDown);
			}
			else if(eventPage->isVisible())
			{
				eventPage->KeyPressEvent(Qt::Key_PageDown);
			}

			return;
		}
		default:
		{
			return;
		}
	}

	QDialog::keyPressEvent(event);
}
