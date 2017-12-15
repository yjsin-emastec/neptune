#include <QtGui>
#include <dev/gps.h>
#include <dev/Rtc.h>
#include <dev/Ver.h>
#include <testmgr.h>
#include <utils.h>
#include <appmgr.h>
#include "diagmaindialog.h"
#include "testwidget.h"

DiagMainDialog::DiagMainDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint | Qt::FramelessWindowHint);
    setPalette(QPalette(QColor(20, 22, 24)));
    setAutoFillBackground(true);

    Main        = parent;
    flagBuzzLed = 0;
    flagAudio   = 0;
    int hdd_num = utils_get_hdd_nums();

    buttonGps1             ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonGps2             ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonDateTime1        ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonDateTime2        ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonSataTemp         ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonSata             ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonTemperature      ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonGsensor1         ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonGsensor2         ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonUsbMouse1        ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonUsbMouse2        ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonRemoteCtrl1      ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonRemoteCtrl2      ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonTrigger1         ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonTrigger2         ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonMac1             ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonMac2             ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonNetworkPing1     ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonNetworkPing2     ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonAudio1           ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonAudio2           ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonLedBuzzer1       ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonLedBuzzer2       ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonFormat1          ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonFormat2          ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonFactoryDefault1  ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonFactoryDefault2  ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");
    buttonApplication1     ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(39,0,79);color:white;}");
    buttonApplication2     ->setStyleSheet("QPushButton{font-size:32px;background-color:rgb(50,57,83);color:white;}QPushButton:focus{background-color:rgb(152,14,69);}");

    connect(buttonMac2,            SIGNAL(clicked(void)), this, SLOT(onButtonMac2            (void)));
    connect(buttonNetworkPing2,    SIGNAL(clicked(void)), this, SLOT(onButtonNetworkPing2    (void)));
    connect(buttonAudio2,          SIGNAL(clicked(void)), this, SLOT(onButtonAudio2          (void)));
    connect(buttonLedBuzzer2,      SIGNAL(clicked(void)), this, SLOT(onButtonLedBuzzer2      (void)));
    connect(buttonFormat2,         SIGNAL(clicked(void)), this, SLOT(onButtonFormat2         (void)));
    connect(buttonFactoryDefault2, SIGNAL(clicked(void)), this, SLOT(onButtonFactoryDefault2 (void)));
    connect(buttonApplication2,    SIGNAL(clicked(void)), this, SLOT(onButtonApplication2    (void)));

    pTestWidget = (TestWidget *)Main;

    if(hdd_num == 0)
    {
        buttonSata->setText(tr("Not Detected"));
    }
    else
    {
        buttonSata->setText(tr("Detected"));
    }

    char tmp[128];
    testmgr_get_mac(tmp);
    buttonMac2->setText(tr("%1 [%2]").arg(tr("Set")).arg(QString::fromUtf8(tmp)));
    buttonMac2->setFocus();

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(onGsensorUpdate()));

    timer->start(100);
}
DiagMainDialog::~DiagMainDialog()
{
}
void DiagMainDialog::DisplayUsbMouse2(QMouseEvent *event)
{
    buttonUsbMouse2->setText(tr("%1 [X:%2 Y:%3]").arg(tr("Mouse")).arg(event->pos().x()).arg(event->pos().y()));
}
void DiagMainDialog::DisplayRemoteCtrl2(QString str)
{
    buttonRemoteCtrl2->setText(tr("%1 [%2]").arg(tr("Controller")).arg(str));
}
void DiagMainDialog::onButtonMac2()
{
}
void DiagMainDialog::onButtonNetworkPing2()
{
    buttonNetworkPing2->setText(tr("Please wait a moment."));

    this->Delay(100);

    if(testmgr_ping_test() == 0)
    {
        buttonNetworkPing2->setText(tr("%1 %2").arg(tr("Ping Test"),tr("Success")));
    }
    else
    {
        buttonNetworkPing2->setText(tr("%1 %2").arg(tr("Ping Test"),tr("Fail")));
    }
}
void DiagMainDialog::Delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
void DiagMainDialog::onButtonAudio2()
{

    if(flagAudio)
    {
        return;
    }

    flagAudio = 1;

    int maxCh = ver_get_video();

    for(int ch = 0; ch < maxCh; ch++)
    {
        buttonAudio2->setText(tr("%1 : %2").arg("Ouput Channel").arg(ch+1));
        this->Delay(100);
        testmgr_set_audio(0, ch);
        this->Delay(2000);
    }

    testmgr_set_audio(2, 0);
    buttonAudio2->setText(tr("%1").arg("Ouput Test"));

    flagAudio = 0;
}
void DiagMainDialog::onButtonLedBuzzer2()
{
    if(!flagBuzzLed)
    {
        flagBuzzLed = 1;
        buttonLedBuzzer2->setText(tr("%1 %2").arg(tr("Test"),tr("ON")));
    }
    else
    {
        flagBuzzLed = 0;
        buttonLedBuzzer2->setText(tr("%1 %2").arg(tr("Test"),tr("OFF")));
        testmgr_led_ctrl(0);
    }	
}
void DiagMainDialog::onButtonFormat2()
{
    if(utils_get_sata_link())
    {
        if(utils_exist_usb_stick())
        {
            buttonFormat2->setText(tr("Unplug USB"));
        }
        else
        {
            utils_system("/usr/lib/sysconfig");
            pTestWidget->diskFormatNum = (1 << 0);
            pTestWidget->DiskFormatStart();
        }
    }
    else
    {
        buttonFormat2->setText(tr("No Storage"));
    }
}
void DiagMainDialog::onButtonFactoryDefault2()
{
    testmgr_factory_default();
    buttonFactoryDefault2->setText(tr("%1 %2").arg(tr("Default"),tr("Completion")));
}
void DiagMainDialog::onButtonApplication2()
{
    testmgr_deinit();
    buttonApplication2->setText(tr("Rebooting..."));
}
void DiagMainDialog::onGsensorUpdate()
{	
    int x,y,z;
    char tmp[32] = {0, };
    QString str;

    testmgr_gsensor_data_read(&x, &y, &z);
    memset(tmp, 0x0, 32);

    sprintf(tmp, "X[%+.3f] Y[%+.3f] Z[%+.3f]", x/1000.0,y/1000.0,z/1000.0);
    str = QString::fromAscii(tmp);
    buttonGsensor2->setText(str);
}
void DiagMainDialog::onCheckStart()
{
    time_t        now,
                  nowTime;

    double        lat,
                  lon,
                  spd;

    struct tm     tmNow;

    char          arr_trigger[4] = {0, },
                  tmp[32]        = {0, };

    unsigned int  trigger;

    int           ii,
                  isValid,
                  sata_link;

    QString       str;

    static int    isConnectedGps = 0;


    isValid = gps_get_data(&lat, &lon, &spd);

    if(isValid)
    {
        if(isConnectedGps == 0)
        {
            (void)gps_get_time2(&nowTime);

            if(nowTime >= RTC_BASE_TIME && nowTime < RTC_Y2K38_TIME)
            {
                testmgr_set_rtc(nowTime);
                buttonGps2->setText(tr("%1 && %2 %3").arg(tr("Connected"),tr("Synchronized"),tr("RTC")));
                isConnectedGps = 1;
            }
            else
            {
                buttonGps2->setText(tr("%1").arg(tr("Connected")));
            }
        }
    }
    else
    {
        if(isConnectedGps == 1)
        {
            buttonGps2->setText(tr("%1").arg(tr("Not Connected")));
            isConnectedGps = 0;
        }
    }

#if 1 // jungyver [17/07/25]
    now = testmgr_get_rtc();
    localtime_r(&now, &tmNow);
#else
    time(&now);
    localtime_r(&now, &tmNow);
#endif

    sprintf(tmp, "%04d/%02d/%02d %02d:%02d:%02d", tmNow.tm_year+1900, tmNow.tm_mon+1, tmNow.tm_mday, tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
    str = QString::fromAscii(tmp);
    buttonDateTime2->setText(str);

    trigger = testmgr_get_trigger();

    for(ii = 0; ii < 4; ii++)
    {
        if(((trigger >> ii) & 0x01))
        {
            arr_trigger[ii] = 1;
        }
    }

    memset(tmp, 0x0, 32);
    sprintf(tmp, "[%d][%d][%d][%d]", arr_trigger[3],arr_trigger[2],arr_trigger[1],arr_trigger[0]);
    str = QString::fromAscii(tmp);
    buttonTrigger2->setText(str);

    if(flagBuzzLed)
    {
        testmgr_buzzer_ctrl(1);
        testmgr_led_ctrl(tmNow.tm_sec%3);
    }

    sata_link = utils_get_sata_link();

    if(sata_link)
    {
        buttonSata->setText(tr("%1 [%2: %3]").arg(tr("Detected")).arg("Slot").arg(sata_link));
    }
    else
    {
        buttonSata->setText(tr("Not Detected"));
    }

    buttonTemperature->setText(tr("%1 %2").arg(appmgr_get_board_temperature()).arg(QString::fromUtf8("℃")));

    buttonFormat2->setText(tr("Start"));
}
void DiagMainDialog::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *key    = NULL;
    QWidget   *target = QApplication::focusWidget();

    switch(event->key()) 
    {
        case Qt::Key_Up:

                 if(buttonMac2            ->hasFocus()) { buttonApplication2    ->setFocus(); }
            else if(buttonNetworkPing2    ->hasFocus()) { buttonMac2            ->setFocus(); }
            else if(buttonAudio2          ->hasFocus()) { buttonNetworkPing2    ->setFocus(); }
            else if(buttonLedBuzzer2      ->hasFocus()) { buttonAudio2          ->setFocus(); }
            else if(buttonFormat2         ->hasFocus()) { buttonLedBuzzer2      ->setFocus(); }
            else if(buttonFactoryDefault2 ->hasFocus()) { buttonFormat2         ->setFocus(); }
            else if(buttonApplication2    ->hasFocus()) { buttonFactoryDefault2 ->setFocus(); }

            return;

        case Qt::Key_Down:

                 if(buttonMac2            ->hasFocus()) { buttonNetworkPing2    ->setFocus(); }
            else if(buttonNetworkPing2    ->hasFocus()) { buttonAudio2          ->setFocus(); }
            else if(buttonAudio2          ->hasFocus()) { buttonLedBuzzer2      ->setFocus(); }
            else if(buttonLedBuzzer2      ->hasFocus()) { buttonFormat2         ->setFocus(); }
            else if(buttonFormat2         ->hasFocus()) { buttonFactoryDefault2 ->setFocus(); }
            else if(buttonFactoryDefault2 ->hasFocus()) { buttonApplication2    ->setFocus(); }
            else if(buttonApplication2    ->hasFocus()) { buttonMac2            ->setFocus(); }

            return;

        case Qt::Key_Enter:

                 if(buttonMac2            ->hasFocus())  onButtonMac2            ();
            else if(buttonNetworkPing2    ->hasFocus())  onButtonNetworkPing2    ();
            else if(buttonAudio2          ->hasFocus())  onButtonAudio2          ();
            else if(buttonLedBuzzer2      ->hasFocus())  onButtonLedBuzzer2      ();
            else if(buttonFormat2         ->hasFocus())  onButtonFormat2         ();
            else if(buttonFactoryDefault2 ->hasFocus())  onButtonFactoryDefault2 ();
            else if(buttonApplication2    ->hasFocus())  onButtonApplication2    ();

            return;

        default:

            return;
    }

    QDialog::keyPressEvent(event);
}
