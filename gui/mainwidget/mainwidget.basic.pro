DEFINES      += _TTY_POSIX_                                                                          \
                QT_BASE                                                                              \
                QT_SHARED                                                                            \

TRANSLATIONS  = src/dvrsetup/system/language/translator/language_english.ts                          \
                src/dvrsetup/system/language/translator/language_korean.ts                           \
                src/dvrsetup/system/language/translator/language_spanish.ts                          \
                src/dvrsetup/system/language/translator/language_french.ts                           \
                src/dvrsetup/system/language/translator/language_italian.ts                          \

UI_DIR        = obj
MOC_DIR       = obj
RCC_DIR       = obj

INCLUDEPATH  += src                                                                                  \
                obj                                                                                  \
                ../../include                                                                        \
                ../../include/utils                                                                  \
                ../../include/appmgr                                                                 \
                ../../include/event                                                                  \
                ../../include/testmgr                                                                \

DEPENDPATH   += src                                                                                  \
                obj                                                                                  \

LIBS         += -L../../lib                                                                          \
                -L../../lib/arm-hisiv100                                                             \
                -levent                                                                              \
                -lsqlite3                                                                            \
                -lcore                                                                               \
                -lvenc                                                                               \
                -lpb                                                                                 \
                -lnetipc                                                                             \
                -lsocket                                                                             \
                -lutils                                                                              \
                -lappmanager                                                                         \
                -ldevmanager                                                                         \
                -lkeypad                                                                             \
                -lrtc                                                                                \
                -lgsensor                                                                            \
                -ltemperature                                                                        \
                -lnmea                                                                               \
                -lgps                                                                                \
                -lver                                                                                \
                -lnetmanager                                                                         \
                -lwork                                                                               \
                -ldata                                                                               \
                -ldiskmgr                                                                            \
                -lglib-2.0                                                                           \
                -lgthread-2.0                                                                        \
                -lintl                                                                               \
                -lmediabackup                                                                        \
                -lipc                                                                                \
                -losal                                                                               \
                -lhimem                                                                              \
                -ltestmgr                                                                            \

SOURCES      += src/main.cpp                                                                         \
                src/login/logindialog.cpp                                                            \
                src/login/logindialogkey.cpp                                                         \
                src/ui/keyboard/uikeyboarddialog.cpp                                                 \
                src/ui/keyboard/uikeyboarddialogkey.cpp                                              \
                src/ui/numkeypaddialog/numkeypaddialog.cpp                                           \
                src/firstcheck/timesetdialog.cpp                                                     \
                src/firstcheck/rtcsetdialog.cpp                                                      \
                src/textmessagebox/textmessagedialog.cpp                                             \
                src/textmessagebox/textmessagedialogkey.cpp                                          \
                src/main/mainMenu.cpp                                                                \
                src/main/mainwidget.cpp                                                              \
                src/main/statusbardialog.cpp                                                         \
                src/main/maininitsys.cpp                                                             \
                src/main/maineventproc.cpp                                                           \
                src/main/mainscreen.cpp                                                              \
                src/main/eventrecvthread.cpp                                                         \
                src/main/playtimebar.cpp                                                             \
                src/main/playbardialog.cpp                                                           \
                src/main/videopane.cpp                                                               \
                src/dvrsetup/setup/setupdialog.cpp                                                   \
                src/dvrsetup/setup/setupdialogkey.cpp                                                \
                src/dvrsetup/setup/systempage.cpp                                                    \
                src/dvrsetup/setup/recordpage.cpp                                                    \
                src/dvrsetup/setup/displaypage.cpp                                                   \
                src/dvrsetup/setup/devicepage.cpp                                                    \
                src/dvrsetup/system/datetime/setdatetimedialog.cpp                                   \
                src/dvrsetup/system/datetime/setdatetimedialogkey.cpp                                \
                src/dvrsetup/system/security/securitydialog.cpp                                      \
                src/dvrsetup/system/config/configdialog.cpp                                          \
                src/dvrsetup/system/upgrade/appupgradedialog.cpp                                     \
                src/dvrsetup/system/language/languagedialog.cpp                                      \
                src/dvrsetup/system/licenseplate/licenseplatedialog.cpp                              \
                src/dvrsetup/system/information/informationdialog.cpp                                \
                src/dvrsetup/record/normal/normaldialog.cpp                                          \
                src/dvrsetup/record/event/eventdialog.cpp                                            \
                src/dvrsetup/display/cameraname/cameranamedialog.cpp                                 \
                src/dvrsetup/display/videooutput/videooutputdialog.cpp                               \
                src/dvrsetup/display/osd/osddialog.cpp                                               \
                src/dvrsetup/device/videoinput/videoinputdialog.cpp                                  \
                src/dvrsetup/device/triggerinput/triggerinputdialog.cpp                              \
                src/dvrsetup/device/gsensor/gsensordialog.cpp                                        \
                src/dvrsetup/device/buzzer/buzzerdialog.cpp                                          \
                src/dvrsetup/device/diskformat/diskformatprocess.cpp                                 \
                src/search/timeline.cpp                                                              \
                src/search/searchdialog.cpp                                                          \
                src/search/eventsortfilterproxymodel.cpp                                             \
                src/search/eventlogpage.cpp                                                          \
                src/search/calendarpage.cpp                                                          \
                src/search/calendarwidget.cpp                                                        \
                src/search/backupdialog/backupdialog.cpp                                             \
                src/test/diagmaindialog.cpp                                                          \
                src/test/macdialog.cpp                                                               \
                src/test/testwidget.cpp                                                              \
                src/test/testeventcontroller.cpp                                                     \

HEADERS      += src/login/logindialog.h                                                              \
                src/ui/keyboard/uikeyboarddialog.h                                                   \
                src/ui/numkeypaddialog/numkeypaddialog.h                                             \
                src/firstcheck/timesetdialog.h                                                       \
                src/firstcheck/rtcsetdialog.h                                                        \
                src/textmessagebox/textmessagedialog.h                                               \
                src/main/mainMenu.h                                                                  \
                src/main/mainwidget.h                                                                \
                src/main/statusbardialog.h                                                           \
                src/main/mainglobal.h                                                                \
                src/main/playbardialog.h                                                             \
                src/main/playtimebar.h                                                               \
                src/main/videopane.h                                                                 \
                src/main/eventrecvthread.h                                                           \
                src/dvrsetup/setup/setupdialog.h                                                     \
                src/dvrsetup/setup/systempage.h                                                      \
                src/dvrsetup/setup/recordpage.h                                                      \
                src/dvrsetup/setup/displaypage.h                                                     \
                src/dvrsetup/setup/devicepage.h                                                      \
                src/dvrsetup/system/datetime/setdatetimedialog.h                                     \
                src/dvrsetup/system/security/securitydialog.h                                        \
                src/dvrsetup/system/config/configdialog.h                                            \
                src/dvrsetup/system/upgrade/appupgradedialog.h                                       \
                src/dvrsetup/system/language/languagedialog.h                                        \
                src/dvrsetup/system/licenseplate/licenseplatedialog.h                                \
                src/dvrsetup/system/information/informationdialog.h                                  \
                src/dvrsetup/record/normal/normaldialog.h                                            \
                src/dvrsetup/record/event/eventdialog.h                                              \
                src/dvrsetup/display/cameraname/cameranamedialog.h                                   \
                src/dvrsetup/display/videooutput/videooutputdialog.h                                 \
                src/dvrsetup/display/osd/osddialog.h                                                 \
                src/dvrsetup/device/videoinput/videoinputdialog.h                                    \
                src/dvrsetup/device/triggerinput/triggerinputdialog.h                                \
                src/dvrsetup/device/buzzer/buzzerdialog.h                                            \
                src/dvrsetup/device/gsensor/gsensordialog.h                                          \
                src/dvrsetup/device/diskformat/diskformatprocess.h                                   \
                src/search/timeline.h                                                                \
                src/search/searchdialog.h                                                            \
                src/search/eventsortfilterproxymodel.h                                               \
                src/search/eventlogpage.h                                                            \
                src/search/calendarpage.h                                                            \
                src/search/calendarwidget.h                                                          \
                src/search/backupdialog/backupdialog.h                                               \
                src/test/diagmaindialog.h                                                            \
                src/test/macdialog.h                                                                 \
                src/test/testwidget.h                                                                \
                src/test/testeventcontroller.h                                                       \

FORMS        += src/login/logindialog.ui                                                             \
                src/ui/keyboard/uikeyboarddialog.ui                                                  \
                src/ui/numkeypaddialog/numkeypaddialog.ui                                            \
                src/firstcheck/timesetdialog.ui                                                      \
                src/firstcheck/rtcsetdialog.ui                                                       \
                src/textmessagebox/textmessagedialog.ui                                              \
                src/main/mainMenu.ui                                                                 \
                src/main/statusbardialog.ui                                                          \
                src/main/playbardialog.ui                                                            \
                src/dvrsetup/setup/setupdialog.ui                                                    \
                src/dvrsetup/setup/systempage.ui                                                     \
                src/dvrsetup/setup/recordpage.ui                                                     \
                src/dvrsetup/setup/displaypage.ui                                                    \
                src/dvrsetup/setup/devicepage.ui                                                     \
                src/dvrsetup/system/datetime/setdatetimedialog.ui                                    \
                src/dvrsetup/system/datetime/setdatetimedialog_line.ui                               \
                src/dvrsetup/system/security/securitydialog.ui                                       \
                src/dvrsetup/system/config/configdialog.ui                                           \
                src/dvrsetup/system/upgrade/appupgradedialog.ui                                      \
                src/dvrsetup/system/language/languagedialog.ui                                       \
                src/dvrsetup/system/licenseplate/licenseplatedialog.ui                               \
                src/dvrsetup/system/information/informationdialog.ui                                 \
                src/dvrsetup/record/normal/normaldialog.ui                                           \
                src/dvrsetup/record/event/eventdialog.ui                                             \
                src/dvrsetup/display/cameraname/cameranamedialog.ui                                  \
                src/dvrsetup/display/videooutput/videooutputdialog.ui                                \
                src/dvrsetup/display/osd/osddialog.ui                                                \
                src/dvrsetup/device/videoinput/videoinputdialog.ui                                   \
                src/dvrsetup/device/triggerinput/triggerinputdialog.ui                               \
                src/dvrsetup/device/buzzer/buzzerdialog.ui                                           \
                src/dvrsetup/device/gsensor/gsensordialog.ui                                         \
                src/dvrsetup/device/diskformat/diskformatprocess.ui                                  \
                src/search/searchdialog.ui                                                           \
                src/search/calendarpage.ui                                                           \
                src/search/backupdialog/backupdialog.ui                                              \
                src/test/diagmaindialog.ui                                                           \
                src/test/macdialog.ui                                                                \

RESOURCES    += mainwidget.qrc

OTHER_FILES  +=
