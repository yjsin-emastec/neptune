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
    if(mainHeight == 720)
    {
        Ui::SearchDialog ui720;
        ui720.setupUi(this);

        frame           = ui720.frame;
        frameTitle      = ui720.frameTitle;
        frameContents   = ui720.frameContents;

        buttonTitle     = ui720.buttonTitle;
        buttonNormal    = ui720.buttonNormal;
        buttonEvent     = ui720.buttonEvent;
        buttonLog       = ui720.buttonLog;
        buttonClose     = ui720.buttonClose;

        labelTitleText  = ui720.labelTitleText;
        labelNormalText = ui720.labelNormalText;
        labelEventText  = ui720.labelEventText;
        labelLogText    = ui720.labelLogText;
        labelCloseText  = ui720.labelCloseText;

        frameTitle      ->setStyleSheet("background-color:rgb(67, 74, 86)");
        frameContents   ->setStyleSheet("background-color:rgb(26, 32, 46)");

        buttonNormal    ->setStyleSheet("padding-top: 50px; background-color:rgb(255,255,255,0);");
        buttonEvent     ->setStyleSheet("padding-top: 50px; background-color:rgb(255,255,255,0);");
        buttonLog       ->setStyleSheet("padding-top: 50px; background-color:rgb(255,255,255,0);");
        buttonClose     ->setStyleSheet("padding-top: 50px; background-color:rgb(255,255,255,0);");

        labelTitleText  ->setStyleSheet("font: 65px;");
        labelNormalText ->setStyleSheet("font: 40px;");
        labelEventText  ->setStyleSheet("font: 40px;");
        labelLogText    ->setStyleSheet("font: 40px;");
        labelCloseText  ->setStyleSheet("font: 40px;");

        iconSize = 160;
    }
    else
    {
        Ui::SearchDialog1080p ui1080;
        ui1080.setupUi(this);

        frame           = ui1080.frame;
        frameTitle      = ui1080.frameTitle;
        frameContents   = ui1080.frameContents;

        buttonTitle     = ui1080.buttonTitle;
        buttonNormal    = ui1080.buttonNormal;
        buttonEvent     = ui1080.buttonEvent;
        buttonLog       = ui1080.buttonLog;
        buttonClose     = ui1080.buttonClose;

        labelTitleText  = ui1080.labelTitleText;
        labelNormalText = ui1080.labelNormalText;
        labelEventText  = ui1080.labelEventText;
        labelLogText    = ui1080.labelLogText;
        labelCloseText  = ui1080.labelCloseText;

        frameTitle      ->setStyleSheet("background-color:rgb(67, 74, 86)");
        frameContents   ->setStyleSheet("background-color:rgb(26, 32, 46)");

        buttonNormal    ->setStyleSheet("padding-top: 80px; background-color:rgb(255,255,255,0);");
        buttonEvent     ->setStyleSheet("padding-top: 80px; background-color:rgb(255,255,255,0);");
        buttonLog       ->setStyleSheet("padding-top: 80px; background-color:rgb(255,255,255,0);");
        buttonClose     ->setStyleSheet("padding-top: 80px; background-color:rgb(255,255,255,0);");

        labelTitleText  ->setStyleSheet("font: 90px;");
        labelNormalText ->setStyleSheet("font: 65px;");
        labelEventText  ->setStyleSheet("font: 65px;");
        labelLogText    ->setStyleSheet("font: 65px;");
        labelCloseText  ->setStyleSheet("font: 65px;");

        iconSize = 240;
    }

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	setPalette(QPalette(QColor(255, 128, 64)));
	frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

	pbChBit = 0xf;
    pbSplit = Split_9;
	SelectPbSplit = pbType = recType = 0;

    iconImageNormal[0].load(":images/main/search.png");
    iconImageNormal[1].load(":images/dvrsetup/record/normal.png");
    iconImageNormal[2].load(":images/dvrsetup/record/event.png");
    iconImageNormal[3].load(":images/search/log.png");
    iconImageNormal[4].load(":images/dvrsetup/system/close.png");

    iconImageFocus[0].load(":images/main/search2.png");
    iconImageFocus[1].load(":images/dvrsetup/record/normal2.png");
    iconImageFocus[2].load(":images/dvrsetup/record/event2.png");
    iconImageFocus[3].load(":images/search/log2.png");
    iconImageFocus[4].load(":images/dvrsetup/system/close2.png");

    buttonTitle     ->setPixmap(iconImageNormal[0].scaled(iconSize*1.3, iconSize*1.3, Qt::KeepAspectRatio));
    buttonNormal    ->setPixmap(iconImageNormal[1].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
    buttonEvent     ->setPixmap(iconImageNormal[2].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
    buttonLog       ->setPixmap(iconImageNormal[3].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
    buttonClose     ->setPixmap(iconImageNormal[4].scaled(iconSize, iconSize, Qt::KeepAspectRatio));

    connect(buttonNormal, SIGNAL(pressed()), this, SLOT(onNormal()));
    connect(buttonEvent,  SIGNAL(pressed()), this, SLOT(onEvent()));
    connect(buttonLog,    SIGNAL(pressed()), this, SLOT(onLog()));
    connect(buttonClose,  SIGNAL(pressed()), this, SLOT(onButtonClose()));

    connect(buttonNormal, SIGNAL(focusIn()), this, SLOT(setFocusNormal()));
    connect(buttonEvent,  SIGNAL(focusIn()), this, SLOT(setFocusEvent()));
    connect(buttonLog,    SIGNAL(focusIn()), this, SLOT(setFocusLog()));
    connect(buttonClose,  SIGNAL(focusIn()), this, SLOT(setFocusClose()));

    calendarPage = new CalendarPage(this);
    connect(calendarPage, SIGNAL(previousSearch(int)), this, SLOT(onHideCalendarPage (int)));
    connect(calendarPage, SIGNAL(closeSearch   (int)), this, SLOT(onButtonClose      (int)));
    connect(calendarPage, SIGNAL(startPlayback ()),    this, SLOT(onStartPlayback    ()));

    eventPage    = new EventLogPage(this);
    connect(eventPage,    SIGNAL(previousSearch(int)), this, SLOT(onHideCalendarPage (int)));
    connect(eventPage,    SIGNAL(closeSearch   (int)), this, SLOT(onButtonClose      (int)));
    connect(eventPage,    SIGNAL(startPlayback ()),    this, SLOT(onStartPlayback    ()));

    systemLogPage= new SystemLogPage(this);
    connect(systemLogPage,SIGNAL(previousSearch(int)), this, SLOT(onHideCalendarPage (int)));
    connect(systemLogPage,SIGNAL(closeSearch   (int)), this, SLOT(onButtonClose      (int)));

    connect(this, SIGNAL(searchDataRead()), calendarPage, SLOT(onUpdateTimeLine()));

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(calendarPage);
    stackedLayout->addWidget(eventPage);
    stackedLayout->addWidget(systemLogPage);
	setLayout(stackedLayout);

    eventPage    ->hide();
    calendarPage ->hide();
    systemLogPage->hide();
}
SearchDialog::~SearchDialog()
{
}
void SearchDialog::onButtonClose(void)
{
    QDialog::reject();

    frameTitle   ->show();
    frameContents->show();

    calendarPage ->hide();
    eventPage    ->hide();
    systemLogPage->hide();
}
void SearchDialog::onButtonClose(int type)
{
    this->onButtonClose();

    switch(type)
    {
        case 0: { appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Normal Exit"); }        break;
        case 1: { appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Event Exit" ); }        break;
        case 2: { appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "System Log Exit" ); }   break;
    }
}
void SearchDialog::onStartPlayback(void)
{
	QDialog::accept();
}
void SearchDialog::onHideCalendarPage(int type)
{
    frameTitle   ->show();
    frameContents->show();

    calendarPage ->hide();
    eventPage    ->hide();
    systemLogPage->hide();

	switch(type)
	{
        case 0: { setFocusNormal(); appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Normal Exit"); }      break;
        case 1: { setFocusEvent();  appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Event Exit" ); }      break;
        case 2: { setFocusLog();    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "System Log Exit" ); } break;
	}
}
void SearchDialog::onEvent(void)
{
    frameTitle   ->hide();
    frameContents->hide();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Event Enter" );
    eventPage    ->resetSearch();
    stackedLayout->setCurrentWidget(eventPage);
    eventPage    ->show();
}
void SearchDialog::onNormal(void)
{
    frameTitle   ->hide();
    frameContents->hide();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "Normal Enter" );
    calendarPage ->ResetSearch();
    calendarPage ->QuerySearchData(0);
    calendarPage ->UpdateSelectTime();
	stackedLayout->setCurrentWidget(calendarPage);
    calendarPage ->show();
}
void SearchDialog::onLog(void)
{
    frameTitle   ->hide();
    frameContents->hide();

    appmgr_write_system_log(SYSTEM_LOG_TYPE_ALL, "System Log Enter" );
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

void SearchDialog::setFocusNormal()     { changeFocus(0); }
void SearchDialog::setFocusEvent()      { changeFocus(1); }
void SearchDialog::setFocusLog()        { changeFocus(2); }
void SearchDialog::setFocusClose()      { changeFocus(3); }

void SearchDialog::changeFocus(int n)
{
    buttonNormal->setPixmap(iconImageNormal[1].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
    buttonEvent ->setPixmap(iconImageNormal[2].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
    buttonLog   ->setPixmap(iconImageNormal[3].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
    buttonClose ->setPixmap(iconImageNormal[4].scaled(iconSize, iconSize, Qt::KeepAspectRatio));

    buttonNormal->setFocusState(false);
    buttonEvent ->setFocusState(false);
    buttonLog   ->setFocusState(false);
    buttonClose ->setFocusState(false);

    switch(n)
    {
        case 0 :
            buttonNormal->setPixmap(iconImageFocus[1].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
            buttonNormal->setFocusState(true);
            break;

        case 1 :
            buttonEvent ->setPixmap(iconImageFocus[2].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
            buttonEvent ->setFocusState(true);
            break;

        case 2 :
            buttonLog   ->setPixmap(iconImageFocus[3].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
            buttonLog   ->setFocusState(true);
            break;

        case 3 :
            buttonClose ->setPixmap(iconImageFocus[4].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
            buttonClose ->setFocusState(true);
            break;

        default :
            buttonNormal->setPixmap(iconImageFocus[1].scaled(iconSize, iconSize, Qt::KeepAspectRatio));
            buttonNormal->setFocusState(true);
            break;
    }
}
void SearchDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if     (calendarPage ->isVisible())   		{ calendarPage  ->KeyPressEvent(Qt::Key_Up);    }
            else if(eventPage    ->isVisible())         { eventPage     ->KeyPressEvent(Qt::Key_Up);    }
            else if(systemLogPage->isVisible())         { systemLogPage ->KeyPressEvent(Qt::Key_Up);    }
            else
            {
                if     (buttonNormal->hasFocusState())  { setFocusLog();    }
                else if(buttonEvent ->hasFocusState())  { setFocusClose();  }
                else if(buttonLog   ->hasFocusState())  { setFocusNormal(); }
                else if(buttonClose ->hasFocusState())  { setFocusEvent();  }
            }

            return;
        }
        case Qt::Key_Down:
        {
            if     (calendarPage ->isVisible())         { calendarPage ->KeyPressEvent(Qt::Key_Down);   }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_Down);   }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Down);   }
            else
            {
                if     (buttonNormal->hasFocusState())  { setFocusLog();    }
                else if(buttonEvent ->hasFocusState())  { setFocusClose();  }
                else if(buttonLog   ->hasFocusState())  { setFocusNormal(); }
                else if(buttonClose ->hasFocusState())  { setFocusEvent();  }
            }

            return;
        }
        case Qt::Key_Left:
        {
            if     (calendarPage ->isVisible())         { calendarPage ->KeyPressEvent(Qt::Key_Left);   }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_Left);   }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Left);   }
            else
            {
                if     (buttonNormal->hasFocusState())  { setFocusEvent();  }
                else if(buttonEvent ->hasFocusState())	{ setFocusNormal(); }
                else if(buttonLog   ->hasFocusState())  { setFocusClose();  }
                else if(buttonClose ->hasFocusState())  { setFocusLog();    }
            }

            return;
        }
        case Qt::Key_Right:
        {
            if     (calendarPage ->isVisible())   		{ calendarPage ->KeyPressEvent(Qt::Key_Right);  }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_Right);  }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Right);  }
            else
            {
                if     (buttonNormal->hasFocusState())  { setFocusEvent();  }
                else if(buttonEvent ->hasFocusState())	{ setFocusNormal(); }
                else if(buttonLog   ->hasFocusState())  { setFocusClose();  }
                else if(buttonClose ->hasFocusState())  { setFocusLog();    }
            }

            return;
        }
        case Qt::Key_Enter:
        {
            if     (calendarPage ->isVisible())         { calendarPage ->KeyPressEvent(Qt::Key_Enter);  }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_Enter);  }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Enter);  }
            else
            {
                if     (buttonNormal->hasFocusState())  { onNormal();               }
                else if(buttonEvent ->hasFocusState())  { onEvent();                }
                else if(buttonLog   ->hasFocusState())  { onLog();                  }
                else if(buttonClose ->hasFocusState())  { this->onButtonClose();    }
            }

            return;
        }
        case Qt::Key_Escape:
        {
            if     (calendarPage ->isVisible())         { calendarPage ->KeyPressEvent(Qt::Key_Escape); }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_Escape); }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_Escape); }
            else                                        { this->onButtonClose();                        }

            return;
        }
        case Qt::Key_PageUp:
        {
            if     (calendarPage ->isVisible())         { calendarPage ->KeyPressEvent(Qt::Key_PageUp); }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_PageUp); }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_PageUp); }

            return;
        }
        case Qt::Key_PageDown:
        {
            if     (calendarPage ->isVisible())         { calendarPage ->KeyPressEvent(Qt::Key_PageDown); }
            else if(eventPage    ->isVisible())         { eventPage    ->KeyPressEvent(Qt::Key_PageDown); }
            else if(systemLogPage->isVisible())         { systemLogPage->KeyPressEvent(Qt::Key_PageDown); }

            return;
        }
        case Qt::Key_Bar:
        {
            if     (calendarPage ->isVisible())         { calendarPage->KeyPressEvent(Qt::Key_Bar);     }

            return;
        }
        case Qt::Key_Play:
        {
            if     (calendarPage ->isVisible())         { calendarPage->KeyPressEvent(Qt::Key_Play);    }

            return;
        }

        default:
        {
            return;
        }
    }

    QDialog::keyPressEvent(event);
}
