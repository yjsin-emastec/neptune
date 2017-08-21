#include <QtGui>
#include "setupdialog.h"
#include "systempage.h"
#include "recordpage.h"
#include "displaypage.h"
#include "devicepage.h"

void SetupDialog::setTabFocus(int isLeftRight, int tabCurInx, int colIndex)
{
    if(isLeftRight == 0)
    {
        switch(tabCurInx)
        {
            case 0: { indexSystem  = colIndex; break; }
            case 1: { indexRecord  = colIndex; break; }
            case 2: { indexDisplay = colIndex; break; }
            case 3: { indexDevice  = colIndex; break; }
        }

        tabLayout->setCurrentIndex(tabCurInx);
    }
    else if(isLeftRight == 1)
    {
        if(tabCurInx == 0)
        {
            tabLayout->setCurrentIndex(tabLayout->count()-1);
        }
        else
        {
            tabLayout->setCurrentIndex(tabCurInx-1);
        }
    }
    else if(isLeftRight == 2)
    {
        if(++tabCurInx >= tabLayout->count())
        {
            tabLayout->setCurrentIndex(0);
        }
        else
        {
            tabLayout->setCurrentIndex(tabCurInx);
        }
    }

    tabLayout->setFocus();
    tabLayout->setStyleSheet("QTabBar::tab:selected{background:rgb(152,14,69)}");
}
void SetupDialog::resetTabFocus(int isUp, int tabCurInx)
{
    if(isUp)
    {
        switch(tabCurInx)
        {
            case 0:

                     if(indexSystem == 0)  { systemPage->buttonLicensePlate->setFocus();    }
                else if(indexSystem == 1)  { systemPage->buttonInformation->setFocus();     }
                else if(indexSystem == 2)  { systemPage->buttonClose->setFocus();           }

                break;

            case 1:

                     if(indexRecord == 0)  { recordPage->buttonNormal->setFocus();          }
                else if(indexRecord == 1)  { recordPage->buttonEvent->setFocus();           }
                else if(indexRecord == 1)  { recordPage->buttonClose->setFocus();           }

                break;

            case 2:

                     if(indexDisplay == 0) { displayPage->buttonOsd->setFocus();            }
                else if(indexDisplay == 1) { displayPage->buttonCameraName->setFocus();     }
                else if(indexDisplay == 2) { displayPage->buttonClose->setFocus();          }

                break;

            case 3:

                     if(indexDevice == 0)  { devicePage->buttonBuzzer->setFocus();          }
                else if(indexDevice == 1)  { devicePage->buttonDiskFormat->setFocus();      }
                else if(indexDevice == 2)  { devicePage->buttonClose->setFocus();           }

                break;
        }
    }
    else
    {
        switch(tabCurInx)
        {
            case 0:

                     if(indexSystem == 0)  { systemPage->buttonDateTime->setFocus();        }
                else if(indexSystem == 1)  { systemPage->buttonSecurity->setFocus();        }
                else if(indexSystem == 2)  { systemPage->buttonConfig->setFocus();          }

                break;

            case 1:

                     if(indexRecord == 0)  { recordPage->buttonNormal->setFocus();          }
                else if(indexRecord == 1)  { recordPage->buttonEvent->setFocus();           }
                else if(indexRecord == 2)  { recordPage->buttonClose->setFocus();           }

                break;

            case 2:

                     if(indexDisplay == 0) { displayPage->buttonVideoOutput->setFocus();    }
                else if(indexDisplay == 1) { displayPage->buttonCameraName->setFocus();     }
                else if(indexDisplay == 2) { displayPage->buttonClose->setFocus();          }

                break;

            case 3:

                     if(indexDevice == 0)  { devicePage->buttonVideo->setFocus();           }
                else if(indexDevice == 1)  { devicePage->buttonTrigger->setFocus();         }
                else if(indexDevice == 2)  { devicePage->buttonGsensor->setFocus();         }

                break;
        }
    }

    tabLayout->setStyleSheet("QTabBar::tab:selected{background:rgb(06,86,159)}");
}
void SetupDialog::keyPressEvent(QKeyEvent *event)
{
    int tabCurInx = tabLayout->currentIndex();
    switch(event->key())
    {
        case Qt::Key_Up:

                 if(systemPage->buttonDateTime->hasFocus())              { setTabFocus(0, tabCurInx, 0);                     }
            else if(systemPage->buttonUpgrade->hasFocus())               { systemPage->buttonDateTime->setFocus();           }
            else if(systemPage->buttonLicensePlate->hasFocus())          { systemPage->buttonUpgrade->setFocus();            }
            else if(systemPage->buttonSecurity->hasFocus())              { setTabFocus(0, tabCurInx, 1);                     }
            else if(systemPage->buttonFactoryDefault->hasFocus())        { systemPage->buttonSecurity->setFocus();           }
            else if(systemPage->buttonInformation->hasFocus())           { systemPage->buttonFactoryDefault->setFocus();     }
            else if(systemPage->buttonConfig->hasFocus())                { setTabFocus(0, tabCurInx, 2);                     }
            else if(systemPage->buttonLanguage->hasFocus())              { systemPage->buttonConfig->setFocus();             }
            else if(systemPage->buttonClose->hasFocus())                 { systemPage->buttonLanguage->setFocus();           }
            else if(recordPage->buttonNormal->hasFocus())                { setTabFocus(0, tabCurInx, 0);                     }
            else if(recordPage->buttonEvent->hasFocus())                 { setTabFocus(0, tabCurInx, 1);                     }
            else if(recordPage->buttonClose->hasFocus())                 { setTabFocus(0, tabCurInx, 2);                     }
            else if(displayPage->buttonVideoOutput->hasFocus())          { setTabFocus(0, tabCurInx, 0);                     }
            else if(displayPage->buttonOsd->hasFocus())                  { displayPage->buttonVideoOutput->setFocus();       }
            else if(displayPage->buttonCameraName->hasFocus())           { setTabFocus(0, tabCurInx, 1);                     }
            else if(displayPage->buttonClose->hasFocus())                { setTabFocus(0, tabCurInx, 2);                     }
            else if(devicePage->buttonVideo->hasFocus())                 { setTabFocus(0, tabCurInx, 0);                     }
            else if(devicePage->buttonBuzzer->hasFocus())                { devicePage->buttonVideo->setFocus();              }
            else if(devicePage->buttonTrigger->hasFocus())               { setTabFocus(0, tabCurInx, 1);                     }
            else if(devicePage->buttonDiskFormat->hasFocus())            { devicePage->buttonTrigger->setFocus();            }
            else if(devicePage->buttonGsensor->hasFocus())               { setTabFocus(0, tabCurInx, 2);                     }
            else if(devicePage->buttonClose->hasFocus())                 { devicePage->buttonGsensor->setFocus();            }
            else if(tabLayout->hasFocus())                               { resetTabFocus(1, tabCurInx);                      }

            return;

        case Qt::Key_Down:

                 if(systemPage->buttonDateTime->hasFocus())              { systemPage->buttonUpgrade->setFocus();            }
            else if(systemPage->buttonUpgrade->hasFocus())               { systemPage->buttonLicensePlate->setFocus();       }
            else if(systemPage->buttonLicensePlate->hasFocus())          { setTabFocus(0, tabCurInx, 0);                     }
            else if(systemPage->buttonSecurity->hasFocus())              { systemPage->buttonFactoryDefault->setFocus();     }
            else if(systemPage->buttonFactoryDefault->hasFocus())        { systemPage->buttonInformation->setFocus();        }
            else if(systemPage->buttonInformation->hasFocus())           { setTabFocus(0, tabCurInx, 1);                     }
            else if(systemPage->buttonConfig->hasFocus())                { systemPage->buttonLanguage->setFocus();           }
            else if(systemPage->buttonLanguage->hasFocus())              { systemPage->buttonClose->setFocus();              }
            else if(systemPage->buttonClose->hasFocus())                 { setTabFocus(0, tabCurInx, 2);                     }
            else if(recordPage->buttonNormal->hasFocus())                { setTabFocus(0, tabCurInx, 0);                     }
            else if(recordPage->buttonEvent->hasFocus())                 { setTabFocus(0, tabCurInx, 1);                     }
            else if(recordPage->buttonClose->hasFocus())                 { setTabFocus(0, tabCurInx, 2);                     }
            else if(displayPage->buttonVideoOutput->hasFocus())          { displayPage->buttonOsd->setFocus();               }
            else if(displayPage->buttonOsd->hasFocus())                  { setTabFocus(0, tabCurInx, 0);                     }
            else if(displayPage->buttonCameraName->hasFocus())           { setTabFocus(0, tabCurInx, 1);                     }
            else if(displayPage->buttonClose->hasFocus())                { setTabFocus(0, tabCurInx, 2);                     }
            else if(devicePage->buttonVideo->hasFocus())                 { devicePage->buttonBuzzer->setFocus();             }
            else if(devicePage->buttonBuzzer->hasFocus())                { setTabFocus(0, tabCurInx, 0);                     }
            else if(devicePage->buttonTrigger->hasFocus())               { devicePage->buttonDiskFormat->setFocus();         }
            else if(devicePage->buttonDiskFormat->hasFocus())            { setTabFocus(0, tabCurInx, 1);                     }
            else if(devicePage->buttonGsensor->hasFocus())               { devicePage->buttonClose->setFocus();              }
            else if(devicePage->buttonClose->hasFocus())                 { setTabFocus(0, tabCurInx, 2);                     }
            else if(tabLayout->hasFocus())                               { resetTabFocus(0, tabCurInx);                      }

            return;

        case Qt::Key_Left:

                 if(systemPage->buttonDateTime->hasFocus())              { systemPage->buttonConfig->setFocus();             }
            else if(systemPage->buttonSecurity->hasFocus())              { systemPage->buttonDateTime->setFocus();           }
            else if(systemPage->buttonConfig->hasFocus())                { systemPage->buttonSecurity->setFocus();           }
            else if(systemPage->buttonUpgrade->hasFocus())               { systemPage->buttonLanguage->setFocus();           }
            else if(systemPage->buttonFactoryDefault->hasFocus())        { systemPage->buttonUpgrade->setFocus();            }
            else if(systemPage->buttonLanguage->hasFocus())              { systemPage->buttonFactoryDefault->setFocus();     }
            else if(systemPage->buttonLicensePlate->hasFocus())          { systemPage->buttonClose->setFocus();              }
            else if(systemPage->buttonInformation->hasFocus())           { systemPage->buttonLicensePlate->setFocus();       }
            else if(systemPage->buttonClose->hasFocus())                 { systemPage->buttonInformation->setFocus();        }
            else if(recordPage->buttonNormal->hasFocus())                { recordPage->buttonClose->setFocus();              }
            else if(recordPage->buttonEvent->hasFocus())                 { recordPage->buttonNormal->setFocus();             }
            else if(recordPage->buttonClose->hasFocus())                 { recordPage->buttonEvent->setFocus();              }
            else if(displayPage->buttonVideoOutput->hasFocus())          { displayPage->buttonCameraName->setFocus();        }
            else if(displayPage->buttonCameraName->hasFocus())           { displayPage->buttonVideoOutput->setFocus();       }
            else if(displayPage->buttonOsd->hasFocus())                  { displayPage->buttonClose->setFocus();             }
            else if(displayPage->buttonClose->hasFocus())                { displayPage->buttonOsd->setFocus();               }
            else if(devicePage->buttonVideo->hasFocus())                 { devicePage->buttonGsensor->setFocus();            }
            else if(devicePage->buttonTrigger->hasFocus())               { devicePage->buttonVideo->setFocus();              }
            else if(devicePage->buttonGsensor->hasFocus())               { devicePage->buttonTrigger->setFocus();            }
            else if(devicePage->buttonBuzzer->hasFocus())                { devicePage->buttonClose->setFocus();              }
            else if(devicePage->buttonDiskFormat->hasFocus())            { devicePage->buttonBuzzer->setFocus();             }
            else if(devicePage->buttonClose->hasFocus())                 { devicePage->buttonDiskFormat->setFocus();         }
            else if(tabLayout->hasFocus())                               { setTabFocus(1, tabCurInx, -1);                    }

            return;

        case Qt::Key_Right:

                 if(systemPage->buttonDateTime->hasFocus())              { systemPage->buttonSecurity->setFocus();           }
            else if(systemPage->buttonSecurity->hasFocus())              { systemPage->buttonConfig->setFocus();             }
            else if(systemPage->buttonConfig->hasFocus())                { systemPage->buttonDateTime->setFocus();           }
            else if(systemPage->buttonUpgrade->hasFocus())               { systemPage->buttonFactoryDefault->setFocus();     }
            else if(systemPage->buttonFactoryDefault->hasFocus())        { systemPage->buttonLanguage->setFocus();           }
            else if(systemPage->buttonLanguage->hasFocus())              { systemPage->buttonUpgrade->setFocus();            }
            else if(systemPage->buttonLicensePlate->hasFocus())          { systemPage->buttonInformation->setFocus();        }
            else if(systemPage->buttonInformation->hasFocus())           { systemPage->buttonClose->setFocus();              }
            else if(systemPage->buttonClose->hasFocus())                 { systemPage->buttonLicensePlate->setFocus();       }
            else if(recordPage->buttonNormal->hasFocus())                { recordPage->buttonEvent->setFocus();              }
            else if(recordPage->buttonEvent->hasFocus())                 { recordPage->buttonClose->setFocus();              }
            else if(recordPage->buttonClose->hasFocus())                 { recordPage->buttonNormal->setFocus();             }
            else if(displayPage->buttonVideoOutput->hasFocus())          { displayPage->buttonCameraName->setFocus();        }
            else if(displayPage->buttonCameraName->hasFocus())           { displayPage->buttonVideoOutput->setFocus();       }
            else if(displayPage->buttonOsd->hasFocus())                  { displayPage->buttonClose->setFocus();             }
            else if(displayPage->buttonClose->hasFocus())                { displayPage->buttonOsd->setFocus();               }
            else if(devicePage->buttonVideo->hasFocus())                 { devicePage->buttonTrigger->setFocus();            }
            else if(devicePage->buttonTrigger->hasFocus())               { devicePage->buttonGsensor->setFocus();            }
            else if(devicePage->buttonGsensor->hasFocus())               { devicePage->buttonVideo->setFocus();              }
            else if(devicePage->buttonBuzzer->hasFocus())                { devicePage->buttonDiskFormat->setFocus();         }
            else if(devicePage->buttonDiskFormat->hasFocus())            { devicePage->buttonClose->setFocus();              }
            else if(devicePage->buttonClose->hasFocus())                 { devicePage->buttonBuzzer->setFocus();             }
            else if(tabLayout->hasFocus())                               { setTabFocus(2, tabCurInx, -1);                    }

            return;

        case Qt::Key_Enter:

            if(tabLayout->hasFocus())
            {
                return;
            }
            else
            {
                break;
            }

        case Qt::Key_Escape:

            reject();

            return;

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
void SetupDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
