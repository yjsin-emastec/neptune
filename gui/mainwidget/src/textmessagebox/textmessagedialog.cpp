#include <QtGui>
#include "textmessagedialog.h"
#include "ui_textmessagedialog.h"
#include "DVR.h"
#include "main/mainglobal.h"

TextMessageDialog::TextMessageDialog(const QString & title, const QString & text, int buttonType, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    setAutoFillBackground(true);

    labelMsg = new QLabel(text);

    QHBoxLayout	*buttonLayout = new QHBoxLayout;
    buttonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    msgType = buttonType;

    switch(buttonType)
    {
        case 0:

            buttonOk = new QPushButton(tr("Yes"));
            buttonCancel = new QPushButton(tr("No"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            break;

        case 1:

            buttonOk = new QPushButton(tr("Ok"));
            buttonCancel = new QPushButton(tr("Cancel"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            break;

        case 2:

            buttonOk = new QPushButton(tr("Ok"));
            buttonOk->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));

            break;

        case 3:

            QTimer::singleShot(3000, this, SLOT(buttonAccept()));

            break;

        case 4:

            buttonOk = new QPushButton(tr("Delete data"));
            buttonCancel = new QPushButton(tr("Change time"));
            buttonOk->setMinimumSize(300,100);
            buttonCancel->setMinimumSize(300,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonReject()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonAccept()));

            break;

        case 5:

            break;

        case 6:

            buttonOk = new QPushButton(tr("Yes"));
            buttonOk->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));

            break;

        case 7:

            buttonOk = new QPushButton(tr("Confirm"));
            buttonCancel = new QPushButton(tr("Cancel"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            break;

        case 8:

            buttonOk = new QPushButton(tr("Format"));
            buttonCancel = new QPushButton(tr("System Shutdown"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(450,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            break;

        case 9:

            break;

        case 10:

            buttonOk = new QPushButton(tr("Confirm"));
            buttonCancel = new QPushButton(tr("System Shutdown"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(450,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            int i, n;
            labelMsg1 = new QLabel(tr("Serial Number"));
            labelMsg2 = new QLabel(tr(""));
            n = appmgr_get_disk_detached_number();
            fprintf(stderr, "%d disk detached.\n", n);

            for(i = 0; i < n; i++)
            {
                fprintf(stderr, "'%s' detached.\n", appmgr_get_disk_detached_serial(i));
            }

            if(n == 1)
            {
                labelMsg2->setText(tr(" '%1' detached.\n").arg(appmgr_get_disk_detached_serial(0)));
            }
            else if(n == 2)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n").arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)));
            }
            else if(n == 3)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)));
            }
            else if(n == 4)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)));
            }
            else if(n == 5)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)));
            }
            else if(n == 6)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n '%6' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)).arg(appmgr_get_disk_detached_serial(5)));
            }
            else if(n == 7)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n '%6' detached.\n '%7' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)).arg(appmgr_get_disk_detached_serial(5)).arg(appmgr_get_disk_detached_serial(6)));
            }
            else
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n '%6' detached.\n '%7' detached.\n '%8' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)).arg(appmgr_get_disk_detached_serial(5)).arg(appmgr_get_disk_detached_serial(6)).arg(appmgr_get_disk_detached_serial(7)));
            }

            break;

        case 11:

            buttonOk = new QPushButton(tr("Close"));
            buttonCancel = new QPushButton(tr("System Shutdown"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(450,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            labelMsg1 = new QLabel(tr("Serial Number"));
            labelMsg2 = new QLabel(tr(""));
            n = appmgr_get_disk_detached_number(); 
            fprintf(stderr, "%d disk detached.\n", n);

            for(i = 0; i < n; i++)
            {
                fprintf(stderr, "'%s' detached.\n", appmgr_get_disk_detached_serial(i));
            }

            if(n == 0)
            {
                ;
            }
            else if(n == 1)
            {
                labelMsg2->setText(tr(" '%1' detached.\n").arg(appmgr_get_disk_detached_serial(0)));
            }
            else if(n == 2)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n").arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)));
            }
            else if(n == 3)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)));
            }
            else if(n == 4)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)));
            }
            else if(n == 5)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)));
            }
            else if(n == 6)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n '%6' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)).arg(appmgr_get_disk_detached_serial(5)));
            }
            else if(n == 7)
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n '%6' detached.\n '%7' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)).arg(appmgr_get_disk_detached_serial(5)).arg(appmgr_get_disk_detached_serial(6)));
            }
            else
            {
                labelMsg2->setText(tr(" '%1' detached.\n '%2' detached.\n '%3' detached.\n '%4' detached.\n '%5' detached.\n '%6' detached.\n '%7' detached.\n '%8' detached.\n").
                        arg(appmgr_get_disk_detached_serial(0)).arg(appmgr_get_disk_detached_serial(1)).arg(appmgr_get_disk_detached_serial(2)).arg(appmgr_get_disk_detached_serial(3)).
                        arg(appmgr_get_disk_detached_serial(4)).arg(appmgr_get_disk_detached_serial(5)).arg(appmgr_get_disk_detached_serial(6)).arg(appmgr_get_disk_detached_serial(7)));
            }

            break;

        case 12:

            buttonOk = new QPushButton(tr("Test"));
            buttonCancel = new QPushButton(tr("Cancel"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(doTest()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            break;

        case 13:



            break;

        case 14:

            buttonOk = new QPushButton(tr("Close"));
            buttonOk->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));

            break;

        case 15:    //LanguageDialog::onButtonLanguageSave
qDebug("textmessagebox create");
            buttonOk = new QPushButton(tr("Ok"));
            buttonCancel = new QPushButton(tr("Cancel"));
            buttonOk->setMinimumSize(250,100);
            buttonCancel->setMinimumSize(250,100);
            buttonLayout->addWidget(buttonOk);
            buttonLayout->addWidget(buttonCancel);
            connect(buttonOk, SIGNAL(clicked()), this, SLOT(buttonAccept()));
            connect(buttonCancel, SIGNAL(clicked()), this, SLOT(buttonReject()));

            break;

        default:

            break;
    }

    QVBoxLayout *layout = new QVBoxLayout;
    labelMsg->setStyleSheet("font: 48px;");
    layout->addWidget(labelMsg);

    if(buttonType == 4)
    {
        layout->addSpacing(60);
    }
    else if(buttonType == 10 || buttonType == 11)
    {
        layout->addSpacing(10);
        layout->addWidget(labelMsg1);
        layout->addWidget(labelMsg2);
        layout->addSpacing(20);
    }
    else
    {
        layout->addSpacing(20);
    }

    layout->addStretch();
    layout->addLayout(buttonLayout);

    setLayout(layout);

    frame->setGeometry(4, 4, sizeHint().width()-8, sizeHint().height()-8);

    if(msgType == 5)
    {
        QTimer::singleShot(500, this, SLOT(doWait()));
    }
    else if(msgType == 6)
    {
        QTimer::singleShot(10000, this, SLOT(doWait()));
    }
    else if(msgType == 9)
    {
        QTimer::singleShot(10000, this, SLOT(timeMismatchEndCheck()));
    }
    else if(msgType == 13)
    {
        QTimer::singleShot(10000, this, SLOT(doWait()));
    }

    if(parent->isLeftToRight() && isRightToLeft())
    {
        setLayoutDirection(Qt::LeftToRight);
    }
    else if(parent->isRightToLeft() && isLeftToRight())
    {
        setLayoutDirection(Qt::RightToLeft);
    }
}
TextMessageDialog::~TextMessageDialog()
{
}
void TextMessageDialog::doWait()
{
    if(msgType == 5)
    {
        emit waitDlgReady();
    }
    else if(msgType == 6)
    {
        emit waitVideoOutput();
    }
    else if(msgType == 13)
    {
        QTimer::singleShot(10, this, SLOT(buttonAccept()));
    }
}
void TextMessageDialog::buttonAccept()
{
    emit signalResetTimer();
    this->accept();
}
void TextMessageDialog::buttonReject()
{
    emit signalResetTimer();
    this->reject();
}
void TextMessageDialog::timeMismatchEndCheck()
{
    appmgr_disk_file_deletion(0, 0, 1);

    for(;;)
    {
        if(appmgr_get_boot_fs_state() == FS_TIME_MISMATCH_DONE)
        {
            emit timeMismatchCheckClose();
            break;
        }

        usleep(100000); //sleep(1);
    }
}
void TextMessageDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}
void TextMessageDialog::setMsgAlignment(Qt::Alignment alignment)
{
    labelMsg->setAlignment(alignment);
}

void TextMessageDialog::doTest()
{
    labelMsg->setText("\nNetwork Testing...\nPlase wait a few seconds.");
    buttonOk->hide();
    buttonCancel->hide();
    QTimer::singleShot(5000, this, SLOT(buttonAccept()));
}
