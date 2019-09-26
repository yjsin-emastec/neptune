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
            case 0: { indexSystem  = colIndex; systemPage ->setFocusTabLayout(); break; }
            case 1: { indexRecord  = colIndex; recordPage ->setFocusTabLayout(); break; }
            case 2: { indexDisplay = colIndex; displayPage->setFocusTabLayout(); break; }
            case 3: { indexDevice  = colIndex; devicePage ->setFocusTabLayout(); break; }
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

                     if(indexSystem == 0)   { systemPage->setFocusLicensePlate();   }
                else if(indexSystem == 1)   { systemPage->setFocusInformation();    }
                else if(indexSystem == 2)   { systemPage->setFocusClose();          }

                break;

            case 1:

                if     (indexRecord == 0)   { recordPage->setFocusNormal();         }
                else if(indexRecord == 1)   { recordPage->setFocusEvent();          }
                else if(indexRecord == 2)   { recordPage->setFocusClose();          }

                break;

            case 2:

                if     (indexDisplay == 0)  { displayPage->setFocusOsd();           }
                else if(indexDisplay == 1)  { displayPage->setFocusCameraName();    }
                else if(indexDisplay == 2)  { displayPage->setFocusClose();         }

                break;

            case 3:
                if     (indexDevice == 0)   { devicePage->setFocusBuzzer();         }
                else if(indexDevice == 1)   { devicePage->setFocusFormat();         }
                else if(indexDevice == 2)   { devicePage->setFocusClose();          }

                break;
        }
    }
    else
    {
        switch(tabCurInx)
        {
            case 0:
                if     (indexSystem == 0)   { systemPage->setFocusDateTime();       }
                else if(indexSystem == 1)   { systemPage->setFocusSecurity();       }
                else if(indexSystem == 2)   { systemPage->setFocusConfig();         }

                break;

            case 1:

                if     (indexRecord == 0)   { recordPage->setFocusNormal();         }
                else if(indexRecord == 1)   { recordPage->setFocusEvent();          }
                else if(indexRecord == 2)   { recordPage->setFocusClose();          }

                break;

            case 2:

                if     (indexDisplay == 0)  { displayPage->setFocusVideoOutput();   }
                else if(indexDisplay == 1)  { displayPage->setFocusCameraName();    }
                else if(indexDisplay == 2)  { displayPage->setFocusClose();         }

                break;

            case 3:

                if     (indexDevice == 0)   { devicePage->setFocusVideo();          }
                else if(indexDevice == 1)   { devicePage->setFocusTrigger();        }
                else if(indexDevice == 2)   { devicePage->setFocusGsensor();        }

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

            if     (systemPage->buttonDateTime->hasFocusState())        { setTabFocus(0, tabCurInx, 0);                     }
            else if(systemPage->buttonSecurity->hasFocusState())        { setTabFocus(0, tabCurInx, 1);                     }
            else if(systemPage->buttonConfig->hasFocusState())          { setTabFocus(0, tabCurInx, 2);                     }
            else if(systemPage->buttonUpgrade->hasFocusState())         { systemPage->setFocusDateTime();                   }
            else if(systemPage->buttonFactoryDefault->hasFocusState())  { systemPage->setFocusSecurity();                   }
            else if(systemPage->buttonLanguage->hasFocusState())        { systemPage->setFocusConfig();                     }
            else if(systemPage->buttonLicensePlate->hasFocusState())    { systemPage->setFocusUpgrade();                    }
            else if(systemPage->buttonInformation->hasFocusState())     { systemPage->setFocusFactoryDefault();             }
            else if(systemPage->buttonClose->hasFocusState())           { systemPage->setFocusLanguage();                   }

            else if(recordPage->buttonNormal->hasFocusState())          { setTabFocus(0, tabCurInx, 0);                     }
            else if(recordPage->buttonEvent->hasFocusState())           { setTabFocus(0, tabCurInx, 1);                     }
            else if(recordPage->buttonClose->hasFocusState())           { setTabFocus(0, tabCurInx, 2);                     }

            else if(displayPage->buttonVideoOutput->hasFocusState())    { setTabFocus(0, tabCurInx, 0);                     }
            else if(displayPage->buttonCameraName->hasFocusState())     { setTabFocus(0, tabCurInx, 1);                     }
            else if(displayPage->buttonOsd->hasFocusState())            { displayPage->setFocusVideoOutput();               }
            else if(displayPage->buttonClose->hasFocusState())          { setTabFocus(0, tabCurInx, 2);                     }

            else if(devicePage->buttonVideo->hasFocusState())           { setTabFocus(0, tabCurInx, 0);                     }
            else if(devicePage->buttonTrigger->hasFocusState())         { setTabFocus(0, tabCurInx, 1);                     }
            else if(devicePage->buttonGsensor->hasFocusState())         { setTabFocus(0, tabCurInx, 2);                     }
            else if(devicePage->buttonBuzzer->hasFocusState())          { devicePage->setFocusVideo();                      }
            else if(devicePage->buttonFormat->hasFocusState())          { devicePage->setFocusTrigger();                    }
            else if(devicePage->buttonClose->hasFocusState())           { devicePage->setFocusGsensor();                    }

            else if(tabLayout->hasFocus())                              { resetTabFocus(1, tabCurInx);                      }

            return;

        case Qt::Key_Down:

            if     (systemPage->buttonDateTime->hasFocusState())        { systemPage->setFocusUpgrade();                    }
            else if(systemPage->buttonSecurity->hasFocusState())        { systemPage->setFocusFactoryDefault();             }
            else if(systemPage->buttonConfig->hasFocusState())          { systemPage->setFocusLanguage();                   }
            else if(systemPage->buttonUpgrade->hasFocusState())         { systemPage->setFocusLicensePlate();               }
            else if(systemPage->buttonFactoryDefault->hasFocusState())  { systemPage->setFocusInformation();                }
            else if(systemPage->buttonLanguage->hasFocusState())        { systemPage->setFocusClose();                      }
            else if(systemPage->buttonLicensePlate->hasFocusState())    { setTabFocus(0, tabCurInx, 0);                     }
            else if(systemPage->buttonInformation->hasFocusState())     { setTabFocus(0, tabCurInx, 1);                     }
            else if(systemPage->buttonClose->hasFocusState())           { setTabFocus(0, tabCurInx, 2);                     }

            else if(recordPage->buttonNormal->hasFocusState())          { setTabFocus(0, tabCurInx, 0);                     }
            else if(recordPage->buttonEvent->hasFocusState())           { setTabFocus(0, tabCurInx, 1);                     }
            else if(recordPage->buttonClose->hasFocusState())           { setTabFocus(0, tabCurInx, 2);                     }

            else if(displayPage->buttonVideoOutput->hasFocusState())    { displayPage->setFocusOsd(); }
            else if(displayPage->buttonCameraName->hasFocusState())     { setTabFocus(0, tabCurInx, 1); }
            else if(displayPage->buttonOsd->hasFocusState())            { setTabFocus(0, tabCurInx, 0); }
            else if(displayPage->buttonClose->hasFocusState())          { setTabFocus(0, tabCurInx, 2); }

            else if(devicePage->buttonVideo->hasFocusState())           { devicePage->setFocusBuzzer();                     }
            else if(devicePage->buttonTrigger->hasFocusState())         { devicePage->setFocusFormat();                     }
            else if(devicePage->buttonGsensor->hasFocusState())         { devicePage->setFocusClose();                      }
            else if(devicePage->buttonBuzzer->hasFocusState())          { setTabFocus(0, tabCurInx, 0);                     }
            else if(devicePage->buttonFormat->hasFocusState())          { setTabFocus(0, tabCurInx, 1);                     }
            else if(devicePage->buttonClose->hasFocusState())           { setTabFocus(0, tabCurInx, 2);                     }

            else if(tabLayout->hasFocus())                              { resetTabFocus(0, tabCurInx);                      }

            return;

        case Qt::Key_Left:

            if     (systemPage->buttonDateTime->hasFocusState())        { systemPage->setFocusConfig();                     }
            else if(systemPage->buttonSecurity->hasFocusState())        { systemPage->setFocusDateTime();                   }
            else if(systemPage->buttonConfig->hasFocusState())          { systemPage->setFocusSecurity();                   }
            else if(systemPage->buttonUpgrade->hasFocusState())         { systemPage->setFocusLanguage();                   }
            else if(systemPage->buttonFactoryDefault->hasFocusState())  { systemPage->setFocusUpgrade();                    }
            else if(systemPage->buttonLanguage->hasFocusState())        { systemPage->setFocusFactoryDefault();             }
            else if(systemPage->buttonLicensePlate->hasFocusState())    { systemPage->setFocusClose();                      }
            else if(systemPage->buttonInformation->hasFocusState())     { systemPage->setFocusLicensePlate();               }
            else if(systemPage->buttonClose->hasFocusState())           { systemPage->setFocusInformation();                }

            else if(recordPage->buttonNormal->hasFocusState())          { recordPage->setFocusClose();                      }
            else if(recordPage->buttonEvent->hasFocusState())           { recordPage->setFocusNormal();                     }
            else if(recordPage->buttonClose->hasFocusState())           { recordPage->setFocusEvent();                      }

            else if(displayPage->buttonVideoOutput->hasFocusState())    { displayPage->setFocusCameraName();                }
            else if(displayPage->buttonCameraName->hasFocusState())     { displayPage->setFocusVideoOutput();               }
            else if(displayPage->buttonOsd->hasFocusState())            { displayPage->setFocusClose();                     }
            else if(displayPage->buttonClose->hasFocusState())          { displayPage->setFocusOsd();                       }

            else if(devicePage->buttonVideo->hasFocusState())           { devicePage->setFocusGsensor();                    }
            else if(devicePage->buttonTrigger->hasFocusState())         { devicePage->setFocusVideo();                      }
            else if(devicePage->buttonGsensor->hasFocusState())         { devicePage->setFocusTrigger();                    }
            else if(devicePage->buttonBuzzer->hasFocusState())          { devicePage->setFocusClose();                      }
            else if(devicePage->buttonFormat->hasFocusState())          { devicePage->setFocusBuzzer();                     }
            else if(devicePage->buttonClose->hasFocusState())           { devicePage->setFocusFormat();                     }

            else if(tabLayout->hasFocus())                              { setTabFocus(1, tabCurInx, -1);                    }

            return;

        case Qt::Key_Right:
            if     (systemPage->buttonDateTime->hasFocusState())        { systemPage->setFocusSecurity();                   }
            else if(systemPage->buttonSecurity->hasFocusState())        { systemPage->setFocusConfig();                     }
            else if(systemPage->buttonConfig->hasFocusState())          { systemPage->setFocusDateTime();                   }
            else if(systemPage->buttonUpgrade->hasFocusState())         { systemPage->setFocusFactoryDefault();             }
            else if(systemPage->buttonFactoryDefault->hasFocusState())  { systemPage->setFocusLanguage();                   }
            else if(systemPage->buttonLanguage->hasFocusState())        { systemPage->setFocusUpgrade();                    }
            else if(systemPage->buttonLicensePlate->hasFocusState())    { systemPage->setFocusInformation();                }
            else if(systemPage->buttonInformation->hasFocusState())     { systemPage->setFocusClose();                      }
            else if(systemPage->buttonClose->hasFocusState())           { systemPage->setFocusLicensePlate();               }

            else if(recordPage->buttonNormal->hasFocusState())          { recordPage->setFocusEvent();                      }
            else if(recordPage->buttonEvent->hasFocusState())           { recordPage->setFocusClose();                      }
            else if(recordPage->buttonClose->hasFocusState())           { recordPage->setFocusNormal();                     }

            else if(displayPage->buttonVideoOutput->hasFocusState())    { displayPage->setFocusCameraName();                }
            else if(displayPage->buttonCameraName->hasFocusState())     { displayPage->setFocusVideoOutput();               }
            else if(displayPage->buttonOsd->hasFocusState())            { displayPage->setFocusClose();                     }
            else if(displayPage->buttonClose->hasFocusState())          { displayPage->setFocusOsd();                       }

            else if(devicePage->buttonVideo->hasFocusState())           { devicePage->setFocusTrigger();                    }
            else if(devicePage->buttonTrigger->hasFocusState())         { devicePage->setFocusGsensor();                    }
            else if(devicePage->buttonGsensor->hasFocusState())         { devicePage->setFocusVideo();                      }
            else if(devicePage->buttonBuzzer->hasFocusState())          { devicePage->setFocusFormat();                     }
            else if(devicePage->buttonFormat->hasFocusState())          { devicePage->setFocusClose();                      }
            else if(devicePage->buttonClose->hasFocusState())           { devicePage->setFocusBuzzer();                     }

            else if(tabLayout->hasFocus())                              { setTabFocus(2, tabCurInx, -1);                    }

            return;

        case Qt::Key_Enter:

            switch (tabCurInx)
            {
                case 0 :
                    if     (systemPage->buttonDateTime->hasFocusState())        { systemPage->onButtonDateTime();           }
                    else if(systemPage->buttonSecurity->hasFocusState())        { systemPage->onButtonSecurity();           }
                    else if(systemPage->buttonConfig->hasFocusState())          { systemPage->onButtonConfig();             }
                    else if(systemPage->buttonUpgrade->hasFocusState())         { systemPage->onButtonUpgrade();            }
                    else if(systemPage->buttonFactoryDefault->hasFocusState())  { systemPage->onButtonFactoryDefault();     }
                    else if(systemPage->buttonLanguage->hasFocusState())        { systemPage->onButtonLanguage();           }
                    else if(systemPage->buttonLicensePlate->hasFocusState())    { systemPage->onButtonLicensePlate();       }
                    else if(systemPage->buttonInformation->hasFocusState())     { systemPage->onButtonInformation();        }
                    else if(systemPage->buttonClose->hasFocusState())           { systemPage->onButtonClose();              }
                    else                                                        { systemPage->setFocusDateTime();           }
                    break;

                case 1 :
                    if     (recordPage->buttonNormal->hasFocusState())          { recordPage->onButtonNormal();             }
                    else if(recordPage->buttonEvent->hasFocusState())           { recordPage->onButtonEvent();              }
                    else if(recordPage->buttonClose->hasFocusState())           { recordPage->onButtonClose();              }
                    break;

                case 2 :
                    if     (displayPage->buttonVideoOutput->hasFocusState())    { displayPage->onButtonVideoOutput();       }
                    else if(displayPage->buttonCameraName->hasFocusState())     { displayPage->onButtonCameraName();        }
                    else if(displayPage->buttonOsd->hasFocusState())            { displayPage->onButtonOsd();               }
                    else if(displayPage->buttonClose->hasFocusState())          { displayPage->onButtonClose();             }
                    break;

                case 3 :
                    if     (devicePage->buttonVideo->hasFocusState())           { devicePage->onButtonVideo();              }
                    else if(devicePage->buttonTrigger->hasFocusState())         { devicePage->onButtonTrigger();            }
                    else if(devicePage->buttonGsensor->hasFocusState())         { devicePage->onButtonGsensor();            }
                    else if(devicePage->buttonBuzzer->hasFocusState())          { devicePage->onButtonBuzzer();             }
                    else if(devicePage->buttonFormat->hasFocusState())          { devicePage->onButtonFormat();             }
                    else if(devicePage->buttonClose->hasFocusState())           { devicePage->onButtonClose();              }
                    break;

                default :
                    break;
            }

            return;

        case Qt::Key_Escape:

            reject();

            return;

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
