#include <QWidget>
#include <QWSServer>
#include <QTimer>
#include <QKeyEvent>
#include <QScreen>
#include <KeypadCode.h>
#include "testwidget.h"
#include "diagmaindialog.h"
#include "main/eventrecvthread.h"
#include "hal/diskservice.h"
#include "testeventcontroller.h"

static int displayWidth  = 0;
static int displayheight = 0;

TestWidget::TestWidget()
{
    QString style;
    QFont font;
    char buffer[64];
    QString tmp;
    char *cutDate;

    eventController = new TestEventController();

    setWindowFlags(Qt::WindowSystemMenuHint | Qt::FramelessWindowHint);

    QWSServer::setBackground(QColor(0,0,0));
    setPalette(QPalette(QColor(20, 22, 24)));
    setAutoFillBackground(true);

    testmgr_checking_resolution(&displayWidth, &displayheight);
    resize(displayWidth, displayheight);

    MainDialog = new DiagMainDialog(this);

    if(displayheight == 720)
    {
        MainDialog->resize(100, 100);
    }
    else if(displayheight == 1080)
    {
        MainDialog->resize(800, 600);
    }

    QTimer::singleShot(10, this, SLOT(onRunDiagnosticsMenu()));

    connect(eventController, SIGNAL(sendKey(int)), this, SLOT(onPassKeypadEvent (int)));

    Thread = new EventRecvThread();
    Thread->start();

    this->LoadStyleSheet();

    connect(Thread, SIGNAL(eventReady(Event *)), eventController, SLOT(handleEvent(Event *)));
    connect(Thread, SIGNAL(timerReady(void)),    MainDialog,      SLOT(onCheckStart()));

    testmgr_wait_diskmgr_boot();
    testmgr_wait_diskmgr_disk_state();

    setMouseTracking(true);

    pDiskFormatProcessDialog = NULL;
}
TestWidget::~TestWidget()
{
}
void TestWidget::onRunDiagnosticsMenu()
{
    MainDialog->show();
    MainDialog->activateWindow();
}
void TestWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->MainDialog->DisplayUsbMouse2(event);
}
void TestWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        ;
    }
    else if(event->button() == Qt::RightButton)
    {
        ;
    }
}
void TestWidget::LoadStyleSheet()
{
    QFile file(":/qss/darkstyle.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    qDebug("-------------------- Dark Style");
}
void TestWidget::onPassKeypadEvent(int KeyCode)
{	
    QKeyEvent *key = NULL;

    qDebug("%s: keycode [%x]", __func__, KeyCode);

    switch(KeyCode)
    {
        case KPD_EVENT_POWER:      this->MainDialog->DisplayRemoteCtrl2(QString("POWER"));       return;
        case KPD_EVENT_SETUP:      this->MainDialog->DisplayRemoteCtrl2(QString("SETUP/PgUp"));  return;
        case KPD_EVENT_SEARCH:     this->MainDialog->DisplayRemoteCtrl2(QString("SEARCH/PgDn")); return;
        case KPD_EVENT_AUDIO:      this->MainDialog->DisplayRemoteCtrl2(QString("AUDIO"));       return;
        case KPD_EVENT_STATUS:     this->MainDialog->DisplayRemoteCtrl2(QString("STATUS"));      return;
        case KPD_EVENT_SPLIT:      this->MainDialog->DisplayRemoteCtrl2(QString("SPLIT"));       return;
        case KPD_EVENT_REW:        this->MainDialog->DisplayRemoteCtrl2(QString("REW"));         return;
        case KPD_EVENT_PLAY_PAUSE: this->MainDialog->DisplayRemoteCtrl2(QString("PLAY/PAUSE"));  return;
        case KPD_EVENT_FF:         this->MainDialog->DisplayRemoteCtrl2(QString("FF"));          return;
        case KPD_EVENT_FREW:       this->MainDialog->DisplayRemoteCtrl2(QString("FREW"));        return;
        case KPD_EVENT_ARCHIVE:    this->MainDialog->DisplayRemoteCtrl2(QString("BACK UP"));     return;
        case KPD_EVENT_FADJ:       this->MainDialog->DisplayRemoteCtrl2(QString("FADJ"));        return;

        case KPD_EVENT_ESC:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Escape,   Qt::NoModifier, QString(QChar(Qt::Key_Escape)));
            this->MainDialog->DisplayRemoteCtrl2(QString("ESC"));
            break;

        case KPD_EVENT_UP:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up,       Qt::NoModifier, QString(QChar(Qt::Key_Up)));
            this->MainDialog->DisplayRemoteCtrl2(QString("UP"));
            break;

        case KPD_EVENT_DOWN:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down,     Qt::NoModifier, QString(QChar(Qt::Key_Down)));
            this->MainDialog->DisplayRemoteCtrl2(QString("DOWN"));
            break;

        case KPD_EVENT_LEFT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left,     Qt::NoModifier, QString(QChar(Qt::Key_Left)));
            this->MainDialog->DisplayRemoteCtrl2(QString("LEFT"));
            break;

        case KPD_EVENT_RIGHT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right,    Qt::NoModifier, QString(QChar(Qt::Key_Right)));
            this->MainDialog->DisplayRemoteCtrl2(QString("RIGHT"));
            break;

        case KPD_EVENT_SELECT:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter,    Qt::NoModifier, QString(QChar(Qt::Key_Enter)));
            this->MainDialog->DisplayRemoteCtrl2(QString("OK"));
            break;

        case KPD_EVENT_1:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_1,        Qt::NoModifier, QString(QChar(Qt::Key_1)));
            this->MainDialog->DisplayRemoteCtrl2(QString("1"));
            break;

        case KPD_EVENT_2:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_2,        Qt::NoModifier, QString(QChar(Qt::Key_2)));
            this->MainDialog->DisplayRemoteCtrl2(QString("2"));
            break;

        case KPD_EVENT_3:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_3,        Qt::NoModifier, QString(QChar(Qt::Key_3)));
            this->MainDialog->DisplayRemoteCtrl2(QString("3"));
            break;

        case KPD_EVENT_4:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_4,        Qt::NoModifier, QString(QChar(Qt::Key_4)));
            this->MainDialog->DisplayRemoteCtrl2(QString("4"));
            break;

        case KPD_EVENT_5:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_5,        Qt::NoModifier, QString(QChar(Qt::Key_5)));
            this->MainDialog->DisplayRemoteCtrl2(QString("5"));
            break;

        case KPD_EVENT_6:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_6,        Qt::NoModifier, QString(QChar(Qt::Key_6)));
            this->MainDialog->DisplayRemoteCtrl2(QString("6"));
            break;

        case KPD_EVENT_7:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_7,        Qt::NoModifier, QString(QChar(Qt::Key_7)));
            this->MainDialog->DisplayRemoteCtrl2(QString("7"));
            break;

        case KPD_EVENT_8:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_8,        Qt::NoModifier, QString(QChar(Qt::Key_8)));
            this->MainDialog->DisplayRemoteCtrl2(QString("8"));
            break;

        case KPD_EVENT_9:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_9,        Qt::NoModifier, QString(QChar(Qt::Key_9)));
            this->MainDialog->DisplayRemoteCtrl2(QString("9"));
            break;

        case KPD_EVENT_10:

            key = new QKeyEvent(QEvent::KeyPress, Qt::Key_0,        Qt::NoModifier, QString(QChar(Qt::Key_0)));
            this->MainDialog->DisplayRemoteCtrl2(QString("0"));
            break;

        default:

            return;
    }

    QApplication::postEvent(QApplication::activeWindow() , key);
}
int TestWidget::DiskFormatStart()
{
    this->DiskFormatProcessDlgOpen();
}
void TestWidget::DiskFormatProcessDlgOpen()
{
    int ret = 0;

    if(pDiskFormatProcessDialog == NULL)
    {
        pDiskFormatProcessDialog = new DiskFormatProcessDialog(this);

        connect(eventController,          SIGNAL(diskFormatProgress(int, unsigned long, unsigned long, unsigned long)),
                pDiskFormatProcessDialog, SLOT(onDiskFormatupdateprocess(int, unsigned long, unsigned long, unsigned long)));
        connect(eventController,          SIGNAL(diskFormatEnd()),    pDiskFormatProcessDialog, SLOT(onDiskFormatupdateEnd()));
        connect(pDiskFormatProcessDialog, SIGNAL(diskformatReboot()), this,                     SLOT(onDiskFormatProcessDlgClose()));
    }

    pDiskFormatProcessDialog ->move((1280-pDiskFormatProcessDialog->sizeHint().width())/2,(720-pDiskFormatProcessDialog->sizeHint().height())/2);
    pDiskFormatProcessDialog ->TestDiskFormatInit();
    pDiskFormatProcessDialog ->StartTimer();
    DiskService::impl()      ->format(diskFormatNum);

    (void)pDiskFormatProcessDialog->exec();
}
void TestWidget::onDiskFormatProcessDlgClose()
{
    if(pDiskFormatProcessDialog)
    {
        delete pDiskFormatProcessDialog;
        pDiskFormatProcessDialog = NULL;
    }
}
