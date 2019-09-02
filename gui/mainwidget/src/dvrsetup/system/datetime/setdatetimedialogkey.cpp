#include <QtGui>
#include "setdatetimedialog.h"

void SetDateTimeDialog::changeComboBoxValue(int n)
{
    //n=1:up, 2:down
    int currentValue = comboBoxTimeZone->currentIndex();
    int maxIndex = comboBoxTimeZone->count();

    if( n == 2 )
    {
        currentValue++;
        if( currentValue >= maxIndex )
        {
            currentValue=0;
        }
    }
    else
    {
        currentValue--;
        if( currentValue < 0 )
        {
            currentValue = maxIndex -1;
        }
    }

    comboBoxTimeZone->setCurrentIndex(currentValue);
}
void SetDateTimeDialog::changeDateTimeEditFocus(int n)
{
    //n=1:left, 2:right

    if( n == 2 )
    {
        switch( dateTimeEdit->currentSectionIndex() )
        {
            case 0 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::MonthSection);   break; }
            case 1 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::DaySection);     break; }
            case 2 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::HourSection);    break; }
            case 3 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::MinuteSection);  break; }
            case 4 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::SecondSection);  break; }
            case 5 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::YearSection);    break; }
        }
    }
    else if( n == 1 )
    {
        switch( dateTimeEdit->currentSectionIndex() )
        {
            case 0 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::SecondSection);  break; }
            case 1 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::YearSection);    break; }
            case 2 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::MonthSection);   break; }
            case 3 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::DaySection);     break; }
            case 4 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::HourSection);    break; }
            case 5 : { dateTimeEdit->setSelectedSection(QDateTimeEdit::MinuteSection);  break; }
        }
    }
}
void SetDateTimeDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up :

            if     ( buttonTimeFormat->hasFocus())                  { buttonSave->setFocus();       }
            else if( buttonGpsSync->hasFocus())                     { buttonClose->setFocus();      }
            else if( comboBoxTimeZone->hasFocus() && isKeyLock )    { changeComboBoxValue(1);       }
            else if( comboBoxTimeZone->hasFocus() )                 { buttonTimeFormat->setFocus(); }
            else if( dateTimeEdit->hasFocus() && isKeyLock )        { dateTimeEdit->stepUp();       }
            else if( dateTimeEdit->hasFocus() )
            {
                if ( comboBoxTimeZone->isEnabled() )                { comboBoxTimeZone->setFocus(); }
                else                                                { buttonTimeFormat->setFocus(); }
            }
            else if( buttonSave->hasFocus() || buttonClose->hasFocus() )
            {
                if ( dateTimeEdit->isEnabled() )                    { dateTimeEdit->setFocus();     }
                else                                                { comboBoxTimeZone->setFocus(); }
            }
            break;

        case Qt::Key_Down :

            if     ( buttonTimeFormat->hasFocus() || buttonGpsSync->hasFocus() )
            {
                if ( comboBoxTimeZone->isEnabled() )                { comboBoxTimeZone->setFocus(); }
                else                                                { dateTimeEdit->setFocus();     }
            }
            else if( comboBoxTimeZone->hasFocus() && isKeyLock )    { changeComboBoxValue(2);       }
            else if( comboBoxTimeZone->hasFocus() )
            {
                if ( dateTimeEdit->isEnabled() )                    { dateTimeEdit->setFocus();     }
                else                                                { buttonSave->setFocus();       }
            }
            else if( dateTimeEdit->hasFocus() && isKeyLock )        { dateTimeEdit->stepDown();     }
            else if( dateTimeEdit->hasFocus() )                     { buttonSave->setFocus();       }
            else if( buttonSave->hasFocus() )                       { buttonTimeFormat->setFocus(); }
            else if( buttonClose->hasFocus() )                      { buttonGpsSync->setFocus();    }

            break;

        case Qt::Key_Left :

            if     ( buttonTimeFormat->hasFocus() )                 { buttonGpsSync->setFocus();    }
            else if( buttonGpsSync->hasFocus() )                    { buttonTimeFormat->setFocus(); }
            else if( dateTimeEdit->hasFocus() && isKeyLock )        { changeDateTimeEditFocus(1);   }
            else if( buttonSave->hasFocus() )                       { buttonClose->setFocus();      }
            else if( buttonClose->hasFocus() )                      { buttonSave->setFocus();       }

            break;

        case Qt::Key_Right :

            if     ( buttonTimeFormat->hasFocus() )                 { buttonGpsSync->setFocus();    }
            else if( buttonGpsSync->hasFocus() )                    { buttonTimeFormat->setFocus(); }
            else if( dateTimeEdit->hasFocus() && isKeyLock )        { changeDateTimeEditFocus(2);   }
            else if( buttonSave->hasFocus() )                       { buttonClose->setFocus();      }
            else if( buttonClose->hasFocus() )                      { buttonSave->setFocus();       }

            break;

        case Qt::Key_Enter :

            if     ( buttonTimeFormat->hasFocus() )                 { onButtonTimeFormat();         }
            else if( buttonGpsSync->hasFocus() )                    { onButtonGpsSync();            }
            else if( comboBoxTimeZone->hasFocus() )                 { isKeyLock = true;             }
            else if( dateTimeEdit->hasFocus() )                     { isKeyLock = true;             }
            else if( buttonSave->hasFocus() )                       { onButtonSave();               }
            else if( buttonClose->hasFocus() )                      { onButtonClose();              }

            break;

        case Qt::Key_Escape :

            if( isKeyLock )                                         { isKeyLock = false;            }
            else                                                    { onButtonClose();              }

            break;

        default :
            return;

    }
}
