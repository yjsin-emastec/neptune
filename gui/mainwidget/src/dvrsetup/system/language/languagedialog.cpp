#include <QtGui>
#include "languagedialog.h"
#include "../../../main/mainglobal.h"

LanguageDialog::LanguageDialog(QWidget *parent)
    : QDialog(parent)
{
	setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	setPalette(QPalette(QColor(255, 128, 64)));
	frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");
#if 1 // jungyver [17/03/29] temporary
	buttonClose->setFocus();
#else
	buttonLanguageUp->setFocus();
#endif

	lineEditLanguage->setStyleSheet("QLineEdit{font:64px;color:white;background-color:rgb(50,57,83);border-width:1px;border-style:inset;border-color:white;}");
	lineEditLanguage->setAlignment(Qt::AlignCenter);
#if 1 // jungyver [17/03/29] temporary
	buttonLanguageUp->setEnabled(false);
#endif
	buttonLanguageUp->setIcon(QIcon(":/images/arrow_up.png"));
	buttonLanguageUp->setIconSize(QSize(90, 90));
#if 1 // jungyver [17/03/29] temporary
	buttonLanguageDown->setEnabled(false);
#endif
	buttonLanguageDown->setIcon(QIcon(":/images/arrow_down.png"));
	buttonLanguageDown->setIconSize(QSize(90, 90));

#if 1 // jungyver [17/03/29] temporary
    buttonSave->setEnabled(false);
#endif
    connect(buttonLanguageUp,   SIGNAL(released()), this, SLOT(onButtonLanguageUp()));
    connect(buttonLanguageDown, SIGNAL(released()), this, SLOT(onButtonLanguageDown()));
    connect(buttonSave,         SIGNAL(released()), this, SLOT(accept()));
    connect(buttonClose,        SIGNAL(released()), this, SLOT(reject()));
}
LanguageDialog::~LanguageDialog()
{
}
void LanguageDialog::initLanguageConfig(void)
{
	buttonLanguageUp->setFocus();

	if(utils_cfg_cmp_item(SystemCfg.language, "ENGLISH") == 0)
	{
		lineEditLanguage->setText(tr("English"));
		indexLanguage = 1;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "KOREAN") == 0)
	{
		lineEditLanguage->setText(tr("Korean"));
		indexLanguage = 2;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "GERMAN") == 0)
	{
		lineEditLanguage->setText(tr("German"));
		indexLanguage = 3;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "SPANISH") == 0)
	{
		lineEditLanguage->setText(tr("Spanish"));
		indexLanguage = 4;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "FRENCH") == 0)
	{
		lineEditLanguage->setText(tr("French"));
		indexLanguage = 5;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "ITALIAN") == 0)
	{
		lineEditLanguage->setText(tr("Italian"));
		indexLanguage = 6;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "PORTUGUESE") == 0)
	{
		lineEditLanguage->setText(tr("Portuguese"));
		indexLanguage = 7;
	}
	else if(utils_cfg_cmp_item(SystemCfg.language, "JAPANESE") == 0)
	{
		lineEditLanguage->setText(tr("Japanese"));
		indexLanguage = 8;
	}
}
void LanguageDialog::onButtonLanguageUp()
{
	if(indexLanguage <= 1) { indexLanguage = 9; }

	switch(--indexLanguage)
	{
		case 1: { lineEditLanguage->setText(tr("English"   ));  utils_cfg_cpy_item(SystemCfg.language, "ENGLISH"   );  break; }
		case 2: { lineEditLanguage->setText(tr("Korean"    ));  utils_cfg_cpy_item(SystemCfg.language, "KOREAN"    );  break; }
		case 3: { lineEditLanguage->setText(tr("German"    ));  utils_cfg_cpy_item(SystemCfg.language, "GERMAN"    );  break; }
		case 4: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
		case 5: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
		case 6: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
		case 7: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }
		case 8: { lineEditLanguage->setText(tr("Japanese"  ));  utils_cfg_cpy_item(SystemCfg.language, "JAPANESE"  );  break; }
	}
}
void LanguageDialog::onButtonLanguageDown()
{
	if(indexLanguage >= 8) { indexLanguage = 0; }

	switch(++indexLanguage)
	{
		case 1: { lineEditLanguage->setText(tr("English"   ));  utils_cfg_cpy_item(SystemCfg.language, "ENGLISH"   );  break; }
		case 2: { lineEditLanguage->setText(tr("Korean"    ));  utils_cfg_cpy_item(SystemCfg.language, "KOREAN"    );  break; }
		case 3: { lineEditLanguage->setText(tr("German"    ));  utils_cfg_cpy_item(SystemCfg.language, "GERMAN"    );  break; }
		case 4: { lineEditLanguage->setText(tr("Spanish"   ));  utils_cfg_cpy_item(SystemCfg.language, "SPANISH"   );  break; }
		case 5: { lineEditLanguage->setText(tr("French"    ));  utils_cfg_cpy_item(SystemCfg.language, "FRENCH"    );  break; }
		case 6: { lineEditLanguage->setText(tr("Italian"   ));  utils_cfg_cpy_item(SystemCfg.language, "ITALIAN"   );  break; }
		case 7: { lineEditLanguage->setText(tr("Portuguese"));  utils_cfg_cpy_item(SystemCfg.language, "PORTUGUESE");  break; }
		case 8: { lineEditLanguage->setText(tr("Japanese"  ));  utils_cfg_cpy_item(SystemCfg.language, "JAPANESE"  );  break; }
	}
}
void LanguageDialog::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
		case Qt::Key_Up:
			{
#if 0 // jungyver [17/03/29] temporary
				     if(buttonLanguageUp->hasFocus())     { buttonClose->setFocus();            }
				else if(buttonLanguageDown->hasFocus())   { buttonLanguageUp->setFocus();       }
				else if(buttonClose->hasFocus())          { buttonLanguageDown->setFocus();     }
#endif
				return;
			}
		case Qt::Key_Down:
			{
#if 0 // jungyver [17/03/29] temporary
				     if(buttonLanguageUp->hasFocus())     { buttonLanguageDown->setFocus();     }
				else if(buttonLanguageDown->hasFocus())   { buttonClose->setFocus();            }
				else if(buttonClose->hasFocus())          { buttonLanguageUp->setFocus();       }
#endif
				return;
			}
		case Qt::Key_Left:
			{
#if 0 // jungyver [17/03/29] temporary
				     if(buttonSave->hasFocus())           { buttonClose->setFocus();            }
				else if(buttonClose->hasFocus())          { buttonSave->setFocus();             }
#endif
				return;
			}
		case Qt::Key_Right:
			{
#if 0 // jungyver [17/03/29] temporary
				     if(buttonSave->hasFocus())           { buttonClose->setFocus();            }
				else if(buttonClose->hasFocus())          { buttonSave->setFocus();             }
#endif
				return;
			}
		case Qt::Key_Enter:
			{
				break;
			}
		case Qt::Key_Escape:
			{
				reject();
				return;
			}
		default:
			{
				reject();
				return;
			}
	}

	QDialog::keyPressEvent(event);
}
void LanguageDialog::keyReleaseEvent(QKeyEvent *event)
{
	return;
}
