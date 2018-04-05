#include <QtGui>
#include "macdialog.h"
#include "main/mainglobal.h"

MacDialog::MacDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setPalette(QPalette(QColor(255, 128, 64)));
    frame->setStyleSheet(".QFrame{background: rgb(39, 0, 79);}");

    buttonUp1->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp1->setIconSize(QSize(42, 42));
    buttonMac1->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac1->installEventFilter(this);
    buttonDn1->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn1->setIconSize(QSize(42, 42));

    buttonUp2->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp2->setIconSize(QSize(42, 42));
    buttonMac2->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac2->installEventFilter(this);
    buttonDn2->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn2->setIconSize(QSize(42, 42));

    buttonUp3->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp3->setIconSize(QSize(42, 42));
    buttonMac3->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac3->installEventFilter(this);
    buttonDn3->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn3->setIconSize(QSize(42, 42));

    buttonUp4->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp4->setIconSize(QSize(42, 42));
    buttonMac4->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac4->installEventFilter(this);
    buttonDn4->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn4->setIconSize(QSize(42, 42));

    buttonUp5->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp5->setIconSize(QSize(42, 42));
    buttonMac5->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac5->installEventFilter(this);
    buttonDn5->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn5->setIconSize(QSize(42, 42));

    buttonUp6->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp6->setIconSize(QSize(42, 42));
    buttonMac6->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac6->installEventFilter(this);
    buttonDn6->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn6->setIconSize(QSize(42, 42));

    buttonUp7->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp7->setIconSize(QSize(42, 42));
    buttonMac7->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac7->installEventFilter(this);
    buttonDn7->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn7->setIconSize(QSize(42, 42));

    buttonUp8->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp8->setIconSize(QSize(42, 42));
    buttonMac8->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac8->installEventFilter(this);
    buttonDn8->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn8->setIconSize(QSize(42, 42));

    buttonUp9->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp9->setIconSize(QSize(42, 42));
    buttonMac9->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac9->installEventFilter(this);
    buttonDn9->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn9->setIconSize(QSize(42, 42));

    buttonUp10->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp10->setIconSize(QSize(42, 42));
    buttonMac10->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac10->installEventFilter(this);
    buttonDn10->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn10->setIconSize(QSize(42, 42));

    buttonUp11->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp11->setIconSize(QSize(42, 42));
    buttonMac11->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac11->installEventFilter(this);
    buttonDn11->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn11->setIconSize(QSize(42, 42));

    buttonUp12->setIcon(QIcon(":/images/arrow_up.png"));
    buttonUp12->setIconSize(QSize(42, 42));
    buttonMac12->setStyleSheet("QPushButton{font:48px;background-color:rgb(39,0,79);color:white;}QPushButton:focus{color:white;background:rgb(152,14,69);}");
    buttonMac12->installEventFilter(this);
    buttonDn12->setIcon(QIcon(":/images/arrow_down.png"));
    buttonDn12->setIconSize(QSize(42, 42));

    connect(buttonUp1,       SIGNAL(released()), this, SLOT(onButtonUp1()));
    connect(buttonDn1,       SIGNAL(released()), this, SLOT(onButtonDn1()));
    connect(buttonUp2,       SIGNAL(released()), this, SLOT(onButtonUp2()));
    connect(buttonDn2,       SIGNAL(released()), this, SLOT(onButtonDn2()));
    connect(buttonUp3,       SIGNAL(released()), this, SLOT(onButtonUp3()));
    connect(buttonDn3,       SIGNAL(released()), this, SLOT(onButtonDn3()));
    connect(buttonUp4,       SIGNAL(released()), this, SLOT(onButtonUp4()));
    connect(buttonDn4,       SIGNAL(released()), this, SLOT(onButtonDn4()));
    connect(buttonUp5,       SIGNAL(released()), this, SLOT(onButtonUp5()));
    connect(buttonDn5,       SIGNAL(released()), this, SLOT(onButtonDn5()));
    connect(buttonUp6,       SIGNAL(released()), this, SLOT(onButtonUp6()));
    connect(buttonDn6,       SIGNAL(released()), this, SLOT(onButtonDn6()));
    connect(buttonUp7,       SIGNAL(released()), this, SLOT(onButtonUp7()));
    connect(buttonDn7,       SIGNAL(released()), this, SLOT(onButtonDn7()));
    connect(buttonUp8,       SIGNAL(released()), this, SLOT(onButtonUp8()));
    connect(buttonDn8,       SIGNAL(released()), this, SLOT(onButtonDn8()));
    connect(buttonUp9,       SIGNAL(released()), this, SLOT(onButtonUp9()));
    connect(buttonDn9,       SIGNAL(released()), this, SLOT(onButtonDn9()));
    connect(buttonUp10,      SIGNAL(released()), this, SLOT(onButtonUp10()));
    connect(buttonDn10,      SIGNAL(released()), this, SLOT(onButtonDn10()));
    connect(buttonUp11,      SIGNAL(released()), this, SLOT(onButtonUp11()));
    connect(buttonDn11,      SIGNAL(released()), this, SLOT(onButtonDn11()));
    connect(buttonUp12,      SIGNAL(released()), this, SLOT(onButtonUp12()));
    connect(buttonDn12,      SIGNAL(released()), this, SLOT(onButtonDn12()));
    connect(buttonAllClear,  SIGNAL(released()), this, SLOT(onButtonAllClear()));
    connect(buttonDefault,   SIGNAL(released()), this, SLOT(onButtonDefault()));
    connect(buttonSave,      SIGNAL(released()), this, SLOT(onButtonSave()));
    connect(buttonCancel,    SIGNAL(released()), this, SLOT(reject()));

    for(ii = 0; ii < 12; ii++)
    {
        idxMac[ii] = 0;
    }

    isLockEsc = false;

    buttonMac1->setFocus();
}
MacDialog::~MacDialog()
{
}
void MacDialog::initMac(char *mac)
{
    memset(tmp, 0, sizeof(tmp));

    for(ii=0,kk=0; *(mac+ii); ii++)
    {
        if(*(mac+ii) != ':')
        {
            char c = *(mac+ii);

            if((c >= 0x41 && c <= 0x46) || (c >= 0x61 && c <= 0x66))
            {
                if(c >= 0x61)
                {
                    tmp[kk++] = idxMac[kk] = c-0x61+10;
                }
                else
                {
                    tmp[kk++] = idxMac[kk] = c-0x41+10;
                }

            }
            else if(c >= 0x30 && c <= 0x39)
            {
                tmp[kk++] = idxMac[kk] = c-0x30;
            }
        }
    }

    buttonMac1  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 0])));
    buttonMac2  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 1])));
    buttonMac3  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 2])));
    buttonMac4  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 3])));
    buttonMac5  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 4])));
    buttonMac6  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 5])));
    buttonMac7  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 6])));
    buttonMac8  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 7])));
    buttonMac9  ->setText(tr("%1").arg(Dec2Hex(&tmp[ 8])));
    buttonMac10 ->setText(tr("%1").arg(Dec2Hex(&tmp[ 9])));
    buttonMac11 ->setText(tr("%1").arg(Dec2Hex(&tmp[10])));
    buttonMac12 ->setText(tr("%1").arg(Dec2Hex(&tmp[11])));
}
char *MacDialog::Dec2Hex(char *val)
{
    switch(*val)
    {
        case 0x0: { return (char *)"0"; }
        case 0x1: { return (char *)"1"; }
        case 0x2: { return (char *)"2"; }
        case 0x3: { return (char *)"3"; }
        case 0x4: { return (char *)"4"; }
        case 0x5: { return (char *)"5"; }
        case 0x6: { return (char *)"6"; }
        case 0x7: { return (char *)"7"; }
        case 0x8: { return (char *)"8"; }
        case 0x9: { return (char *)"9"; }
        case 0xa: { return (char *)"A"; }
        case 0xb: { return (char *)"B"; }
        case 0xc: { return (char *)"C"; }
        case 0xd: { return (char *)"D"; }
        case 0xe: { return (char *)"E"; }
        case 0xf: { return (char *)"F"; }
    }

    return NULL;
}
void MacDialog::onButtonUp1(void)
{
    if(idxMac[0] >= 0xf)
    {
        idxMac[0] = -(0x1);
    }

    switch(++idxMac[0])
    {
        case 0x0: { buttonMac1->setText("0"); break; }
        case 0x1: { buttonMac1->setText("1"); break; }
        case 0x2: { buttonMac1->setText("2"); break; }
        case 0x3: { buttonMac1->setText("3"); break; }
        case 0x4: { buttonMac1->setText("4"); break; }
        case 0x5: { buttonMac1->setText("5"); break; }
        case 0x6: { buttonMac1->setText("6"); break; }
        case 0x7: { buttonMac1->setText("7"); break; }
        case 0x8: { buttonMac1->setText("8"); break; }
        case 0x9: { buttonMac1->setText("9"); break; }
        case 0xa: { buttonMac1->setText("A"); break; }
        case 0xb: { buttonMac1->setText("B"); break; }
        case 0xc: { buttonMac1->setText("C"); break; }
        case 0xd: { buttonMac1->setText("D"); break; }
        case 0xe: { buttonMac1->setText("E"); break; }
        case 0xf: { buttonMac1->setText("F"); break; }
    }

    buttonMac1->setFocus();
}
void MacDialog::onButtonDn1(void)
{
    if(idxMac[0] <= 0x0)
    {
        idxMac[0] = 0x10;
    }

    switch(--idxMac[0])
    {
        case 0x0: { buttonMac1->setText("0"); break; }
        case 0x1: { buttonMac1->setText("1"); break; }
        case 0x2: { buttonMac1->setText("2"); break; }
        case 0x3: { buttonMac1->setText("3"); break; }
        case 0x4: { buttonMac1->setText("4"); break; }
        case 0x5: { buttonMac1->setText("5"); break; }
        case 0x6: { buttonMac1->setText("6"); break; }
        case 0x7: { buttonMac1->setText("7"); break; }
        case 0x8: { buttonMac1->setText("8"); break; }
        case 0x9: { buttonMac1->setText("9"); break; }
        case 0xa: { buttonMac1->setText("A"); break; }
        case 0xb: { buttonMac1->setText("B"); break; }
        case 0xc: { buttonMac1->setText("C"); break; }
        case 0xd: { buttonMac1->setText("D"); break; }
        case 0xe: { buttonMac1->setText("E"); break; }
        case 0xf: { buttonMac1->setText("F"); break; }
    }

    buttonMac1->setFocus();
}
void MacDialog::onButtonUp2(void)
{
    if(idxMac[1] >= 0xf)
    {
        idxMac[1] = -(0x1);
    }

    switch(++idxMac[1])
    {
        case 0x0: { buttonMac2->setText("0"); break; }
        case 0x1: { buttonMac2->setText("1"); break; }
        case 0x2: { buttonMac2->setText("2"); break; }
        case 0x3: { buttonMac2->setText("3"); break; }
        case 0x4: { buttonMac2->setText("4"); break; }
        case 0x5: { buttonMac2->setText("5"); break; }
        case 0x6: { buttonMac2->setText("6"); break; }
        case 0x7: { buttonMac2->setText("7"); break; }
        case 0x8: { buttonMac2->setText("8"); break; }
        case 0x9: { buttonMac2->setText("9"); break; }
        case 0xa: { buttonMac2->setText("A"); break; }
        case 0xb: { buttonMac2->setText("B"); break; }
        case 0xc: { buttonMac2->setText("C"); break; }
        case 0xd: { buttonMac2->setText("D"); break; }
        case 0xe: { buttonMac2->setText("E"); break; }
        case 0xf: { buttonMac2->setText("F"); break; }
    }

    buttonMac2->setFocus();

}
void MacDialog::onButtonDn2(void)
{
    if(idxMac[1] <= 0x0)
    {
        idxMac[1] = 0x10;
    }

    switch(--idxMac[1])
    {
        case 0x0: { buttonMac2->setText("0"); break; }
        case 0x1: { buttonMac2->setText("1"); break; }
        case 0x2: { buttonMac2->setText("2"); break; }
        case 0x3: { buttonMac2->setText("3"); break; }
        case 0x4: { buttonMac2->setText("4"); break; }
        case 0x5: { buttonMac2->setText("5"); break; }
        case 0x6: { buttonMac2->setText("6"); break; }
        case 0x7: { buttonMac2->setText("7"); break; }
        case 0x8: { buttonMac2->setText("8"); break; }
        case 0x9: { buttonMac2->setText("9"); break; }
        case 0xa: { buttonMac2->setText("A"); break; }
        case 0xb: { buttonMac2->setText("B"); break; }
        case 0xc: { buttonMac2->setText("C"); break; }
        case 0xd: { buttonMac2->setText("D"); break; }
        case 0xe: { buttonMac2->setText("E"); break; }
        case 0xf: { buttonMac2->setText("F"); break; }
    }

    buttonMac2->setFocus();
}
void MacDialog::onButtonUp3(void)
{
    if(idxMac[2] >= 0xf)
    {
        idxMac[2] = -(0x1);
    }

    switch(++idxMac[2])
    {
        case 0x0: { buttonMac3->setText("0"); break; }
        case 0x1: { buttonMac3->setText("1"); break; }
        case 0x2: { buttonMac3->setText("2"); break; }
        case 0x3: { buttonMac3->setText("3"); break; }
        case 0x4: { buttonMac3->setText("4"); break; }
        case 0x5: { buttonMac3->setText("5"); break; }
        case 0x6: { buttonMac3->setText("6"); break; }
        case 0x7: { buttonMac3->setText("7"); break; }
        case 0x8: { buttonMac3->setText("8"); break; }
        case 0x9: { buttonMac3->setText("9"); break; }
        case 0xa: { buttonMac3->setText("A"); break; }
        case 0xb: { buttonMac3->setText("B"); break; }
        case 0xc: { buttonMac3->setText("C"); break; }
        case 0xd: { buttonMac3->setText("D"); break; }
        case 0xe: { buttonMac3->setText("E"); break; }
        case 0xf: { buttonMac3->setText("F"); break; }
    }

    buttonMac3->setFocus();
}
void MacDialog::onButtonDn3(void)
{
    if(idxMac[2] <= 0x0)
    {
        idxMac[2] = 0x10;
    }

    switch(--idxMac[2])
    {
        case 0x0: { buttonMac3->setText("0"); break; }
        case 0x1: { buttonMac3->setText("1"); break; }
        case 0x2: { buttonMac3->setText("2"); break; }
        case 0x3: { buttonMac3->setText("3"); break; }
        case 0x4: { buttonMac3->setText("4"); break; }
        case 0x5: { buttonMac3->setText("5"); break; }
        case 0x6: { buttonMac3->setText("6"); break; }
        case 0x7: { buttonMac3->setText("7"); break; }
        case 0x8: { buttonMac3->setText("8"); break; }
        case 0x9: { buttonMac3->setText("9"); break; }
        case 0xa: { buttonMac3->setText("A"); break; }
        case 0xb: { buttonMac3->setText("B"); break; }
        case 0xc: { buttonMac3->setText("C"); break; }
        case 0xd: { buttonMac3->setText("D"); break; }
        case 0xe: { buttonMac3->setText("E"); break; }
        case 0xf: { buttonMac3->setText("F"); break; }
    }

    buttonMac3->setFocus();
}
void MacDialog::onButtonUp4(void)
{
    if(idxMac[3] >= 0xf)
    {
        idxMac[3] = -(0x1);
    }

    switch(++idxMac[3])
    {
        case 0x0: { buttonMac4->setText("0"); break; }
        case 0x1: { buttonMac4->setText("1"); break; }
        case 0x2: { buttonMac4->setText("2"); break; }
        case 0x3: { buttonMac4->setText("3"); break; }
        case 0x4: { buttonMac4->setText("4"); break; }
        case 0x5: { buttonMac4->setText("5"); break; }
        case 0x6: { buttonMac4->setText("6"); break; }
        case 0x7: { buttonMac4->setText("7"); break; }
        case 0x8: { buttonMac4->setText("8"); break; }
        case 0x9: { buttonMac4->setText("9"); break; }
        case 0xa: { buttonMac4->setText("A"); break; }
        case 0xb: { buttonMac4->setText("B"); break; }
        case 0xc: { buttonMac4->setText("C"); break; }
        case 0xd: { buttonMac4->setText("D"); break; }
        case 0xe: { buttonMac4->setText("E"); break; }
        case 0xf: { buttonMac4->setText("F"); break; }
    }

    buttonMac4->setFocus();
}
void MacDialog::onButtonDn4(void)
{
    if(idxMac[3] <= 0x0)
    {
        idxMac[3] = 0x10;
    }

    switch(--idxMac[3])
    {
        case 0x0: { buttonMac4->setText("0"); break; }
        case 0x1: { buttonMac4->setText("1"); break; }
        case 0x2: { buttonMac4->setText("2"); break; }
        case 0x3: { buttonMac4->setText("3"); break; }
        case 0x4: { buttonMac4->setText("4"); break; }
        case 0x5: { buttonMac4->setText("5"); break; }
        case 0x6: { buttonMac4->setText("6"); break; }
        case 0x7: { buttonMac4->setText("7"); break; }
        case 0x8: { buttonMac4->setText("8"); break; }
        case 0x9: { buttonMac4->setText("9"); break; }
        case 0xa: { buttonMac4->setText("A"); break; }
        case 0xb: { buttonMac4->setText("B"); break; }
        case 0xc: { buttonMac4->setText("C"); break; }
        case 0xd: { buttonMac4->setText("D"); break; }
        case 0xe: { buttonMac4->setText("E"); break; }
        case 0xf: { buttonMac4->setText("F"); break; }
    }

    buttonMac4->setFocus();
}
void MacDialog::onButtonUp5(void)
{
    if(idxMac[4] >= 0xf)
    {
        idxMac[4] = -(0x1);
    }

    switch(++idxMac[4])
    {
        case 0x0: { buttonMac5->setText("0"); break; }
        case 0x1: { buttonMac5->setText("1"); break; }
        case 0x2: { buttonMac5->setText("2"); break; }
        case 0x3: { buttonMac5->setText("3"); break; }
        case 0x4: { buttonMac5->setText("4"); break; }
        case 0x5: { buttonMac5->setText("5"); break; }
        case 0x6: { buttonMac5->setText("6"); break; }
        case 0x7: { buttonMac5->setText("7"); break; }
        case 0x8: { buttonMac5->setText("8"); break; }
        case 0x9: { buttonMac5->setText("9"); break; }
        case 0xa: { buttonMac5->setText("A"); break; }
        case 0xb: { buttonMac5->setText("B"); break; }
        case 0xc: { buttonMac5->setText("C"); break; }
        case 0xd: { buttonMac5->setText("D"); break; }
        case 0xe: { buttonMac5->setText("E"); break; }
        case 0xf: { buttonMac5->setText("F"); break; }
    }

    buttonMac5->setFocus();
}
void MacDialog::onButtonDn5(void)
{
    if(idxMac[4] <= 0x0)
    {
        idxMac[4] = 0x10;
    }

    switch(--idxMac[4])
    {
        case 0x0: { buttonMac5->setText("0"); break; }
        case 0x1: { buttonMac5->setText("1"); break; }
        case 0x2: { buttonMac5->setText("2"); break; }
        case 0x3: { buttonMac5->setText("3"); break; }
        case 0x4: { buttonMac5->setText("4"); break; }
        case 0x5: { buttonMac5->setText("5"); break; }
        case 0x6: { buttonMac5->setText("6"); break; }
        case 0x7: { buttonMac5->setText("7"); break; }
        case 0x8: { buttonMac5->setText("8"); break; }
        case 0x9: { buttonMac5->setText("9"); break; }
        case 0xa: { buttonMac5->setText("A"); break; }
        case 0xb: { buttonMac5->setText("B"); break; }
        case 0xc: { buttonMac5->setText("C"); break; }
        case 0xd: { buttonMac5->setText("D"); break; }
        case 0xe: { buttonMac5->setText("E"); break; }
        case 0xf: { buttonMac5->setText("F"); break; }
    }

    buttonMac5->setFocus();
}
void MacDialog::onButtonUp6(void)
{
    if(idxMac[5] >= 0xf)
    {
        idxMac[5] = -(0x1);
    }

    switch(++idxMac[5])
    {
        case 0x0: { buttonMac6->setText("0"); break; }
        case 0x1: { buttonMac6->setText("1"); break; }
        case 0x2: { buttonMac6->setText("2"); break; }
        case 0x3: { buttonMac6->setText("3"); break; }
        case 0x4: { buttonMac6->setText("4"); break; }
        case 0x5: { buttonMac6->setText("5"); break; }
        case 0x6: { buttonMac6->setText("6"); break; }
        case 0x7: { buttonMac6->setText("7"); break; }
        case 0x8: { buttonMac6->setText("8"); break; }
        case 0x9: { buttonMac6->setText("9"); break; }
        case 0xa: { buttonMac6->setText("A"); break; }
        case 0xb: { buttonMac6->setText("B"); break; }
        case 0xc: { buttonMac6->setText("C"); break; }
        case 0xd: { buttonMac6->setText("D"); break; }
        case 0xe: { buttonMac6->setText("E"); break; }
        case 0xf: { buttonMac6->setText("F"); break; }
    }

    buttonMac6->setFocus();
}
void MacDialog::onButtonDn6(void)
{
    if(idxMac[5] <= 0x0)
    {
        idxMac[5] = 0x10;
    }

    switch(--idxMac[5])
    {
        case 0x0: { buttonMac6->setText("0"); break; }
        case 0x1: { buttonMac6->setText("1"); break; }
        case 0x2: { buttonMac6->setText("2"); break; }
        case 0x3: { buttonMac6->setText("3"); break; }
        case 0x4: { buttonMac6->setText("4"); break; }
        case 0x5: { buttonMac6->setText("5"); break; }
        case 0x6: { buttonMac6->setText("6"); break; }
        case 0x7: { buttonMac6->setText("7"); break; }
        case 0x8: { buttonMac6->setText("8"); break; }
        case 0x9: { buttonMac6->setText("9"); break; }
        case 0xa: { buttonMac6->setText("A"); break; }
        case 0xb: { buttonMac6->setText("B"); break; }
        case 0xc: { buttonMac6->setText("C"); break; }
        case 0xd: { buttonMac6->setText("D"); break; }
        case 0xe: { buttonMac6->setText("E"); break; }
        case 0xf: { buttonMac6->setText("F"); break; }
    }

    buttonMac6->setFocus();
}
void MacDialog::onButtonUp7(void)
{
    if(idxMac[6] >= 0xf)
    {
        idxMac[6] = -(0x1);
    }

    switch(++idxMac[6])
    {
        case 0x0: { buttonMac7->setText("0"); break; }
        case 0x1: { buttonMac7->setText("1"); break; }
        case 0x2: { buttonMac7->setText("2"); break; }
        case 0x3: { buttonMac7->setText("3"); break; }
        case 0x4: { buttonMac7->setText("4"); break; }
        case 0x5: { buttonMac7->setText("5"); break; }
        case 0x6: { buttonMac7->setText("6"); break; }
        case 0x7: { buttonMac7->setText("7"); break; }
        case 0x8: { buttonMac7->setText("8"); break; }
        case 0x9: { buttonMac7->setText("9"); break; }
        case 0xa: { buttonMac7->setText("A"); break; }
        case 0xb: { buttonMac7->setText("B"); break; }
        case 0xc: { buttonMac7->setText("C"); break; }
        case 0xd: { buttonMac7->setText("D"); break; }
        case 0xe: { buttonMac7->setText("E"); break; }
        case 0xf: { buttonMac7->setText("F"); break; }
    }

    buttonMac7->setFocus();
}
void MacDialog::onButtonDn7(void)
{
    if(idxMac[6] <= 0x0)
    {
        idxMac[6] = 0x10;
    }

    switch(--idxMac[6])
    {
        case 0x0: { buttonMac7->setText("0"); break; }
        case 0x1: { buttonMac7->setText("1"); break; }
        case 0x2: { buttonMac7->setText("2"); break; }
        case 0x3: { buttonMac7->setText("3"); break; }
        case 0x4: { buttonMac7->setText("4"); break; }
        case 0x5: { buttonMac7->setText("5"); break; }
        case 0x6: { buttonMac7->setText("6"); break; }
        case 0x7: { buttonMac7->setText("7"); break; }
        case 0x8: { buttonMac7->setText("8"); break; }
        case 0x9: { buttonMac7->setText("9"); break; }
        case 0xa: { buttonMac7->setText("A"); break; }
        case 0xb: { buttonMac7->setText("B"); break; }
        case 0xc: { buttonMac7->setText("C"); break; }
        case 0xd: { buttonMac7->setText("D"); break; }
        case 0xe: { buttonMac7->setText("E"); break; }
        case 0xf: { buttonMac7->setText("F"); break; }
    }

    buttonMac7->setFocus();
}
void MacDialog::onButtonUp8(void)
{
    if(idxMac[7] >= 0xf)
    {
        idxMac[7] = -(0x1);
    }

    switch(++idxMac[7])
    {
        case 0x0: { buttonMac8->setText("0"); break; }
        case 0x1: { buttonMac8->setText("1"); break; }
        case 0x2: { buttonMac8->setText("2"); break; }
        case 0x3: { buttonMac8->setText("3"); break; }
        case 0x4: { buttonMac8->setText("4"); break; }
        case 0x5: { buttonMac8->setText("5"); break; }
        case 0x6: { buttonMac8->setText("6"); break; }
        case 0x7: { buttonMac8->setText("7"); break; }
        case 0x8: { buttonMac8->setText("8"); break; }
        case 0x9: { buttonMac8->setText("9"); break; }
        case 0xa: { buttonMac8->setText("A"); break; }
        case 0xb: { buttonMac8->setText("B"); break; }
        case 0xc: { buttonMac8->setText("C"); break; }
        case 0xd: { buttonMac8->setText("D"); break; }
        case 0xe: { buttonMac8->setText("E"); break; }
        case 0xf: { buttonMac8->setText("F"); break; }
    }

    buttonMac8->setFocus();
}
void MacDialog::onButtonDn8(void)
{
    if(idxMac[7] <= 0x0)
    {
        idxMac[7] = 0x10;
    }

    switch(--idxMac[7])
    {
        case 0x0: { buttonMac8->setText("0"); break; }
        case 0x1: { buttonMac8->setText("1"); break; }
        case 0x2: { buttonMac8->setText("2"); break; }
        case 0x3: { buttonMac8->setText("3"); break; }
        case 0x4: { buttonMac8->setText("4"); break; }
        case 0x5: { buttonMac8->setText("5"); break; }
        case 0x6: { buttonMac8->setText("6"); break; }
        case 0x7: { buttonMac8->setText("7"); break; }
        case 0x8: { buttonMac8->setText("8"); break; }
        case 0x9: { buttonMac8->setText("9"); break; }
        case 0xa: { buttonMac8->setText("A"); break; }
        case 0xb: { buttonMac8->setText("B"); break; }
        case 0xc: { buttonMac8->setText("C"); break; }
        case 0xd: { buttonMac8->setText("D"); break; }
        case 0xe: { buttonMac8->setText("E"); break; }
        case 0xf: { buttonMac8->setText("F"); break; }
    }

    buttonMac8->setFocus();
}
void MacDialog::onButtonUp9(void)
{
    if(idxMac[8] >= 0xf)
    {
        idxMac[8] = -(0x1);
    }

    switch(++idxMac[8])
    {
        case 0x0: { buttonMac9->setText("0"); break; }
        case 0x1: { buttonMac9->setText("1"); break; }
        case 0x2: { buttonMac9->setText("2"); break; }
        case 0x3: { buttonMac9->setText("3"); break; }
        case 0x4: { buttonMac9->setText("4"); break; }
        case 0x5: { buttonMac9->setText("5"); break; }
        case 0x6: { buttonMac9->setText("6"); break; }
        case 0x7: { buttonMac9->setText("7"); break; }
        case 0x8: { buttonMac9->setText("8"); break; }
        case 0x9: { buttonMac9->setText("9"); break; }
        case 0xa: { buttonMac9->setText("A"); break; }
        case 0xb: { buttonMac9->setText("B"); break; }
        case 0xc: { buttonMac9->setText("C"); break; }
        case 0xd: { buttonMac9->setText("D"); break; }
        case 0xe: { buttonMac9->setText("E"); break; }
        case 0xf: { buttonMac9->setText("F"); break; }
    }

    buttonMac9->setFocus();
}
void MacDialog::onButtonDn9(void)
{
    if(idxMac[8] <= 0x0)
    {
        idxMac[8] = 0x10;
    }

    switch(--idxMac[8])
    {
        case 0x0: { buttonMac9->setText("0"); break; }
        case 0x1: { buttonMac9->setText("1"); break; }
        case 0x2: { buttonMac9->setText("2"); break; }
        case 0x3: { buttonMac9->setText("3"); break; }
        case 0x4: { buttonMac9->setText("4"); break; }
        case 0x5: { buttonMac9->setText("5"); break; }
        case 0x6: { buttonMac9->setText("6"); break; }
        case 0x7: { buttonMac9->setText("7"); break; }
        case 0x8: { buttonMac9->setText("8"); break; }
        case 0x9: { buttonMac9->setText("9"); break; }
        case 0xa: { buttonMac9->setText("A"); break; }
        case 0xb: { buttonMac9->setText("B"); break; }
        case 0xc: { buttonMac9->setText("C"); break; }
        case 0xd: { buttonMac9->setText("D"); break; }
        case 0xe: { buttonMac9->setText("E"); break; }
        case 0xf: { buttonMac9->setText("F"); break; }
    }

    buttonMac9->setFocus();
}
void MacDialog::onButtonUp10(void)
{
    if(idxMac[9] >= 0xf)
    {
        idxMac[9] = -(0x1);
    }

    switch(++idxMac[9])
    {
        case 0x0: { buttonMac10->setText("0"); break; }
        case 0x1: { buttonMac10->setText("1"); break; }
        case 0x2: { buttonMac10->setText("2"); break; }
        case 0x3: { buttonMac10->setText("3"); break; }
        case 0x4: { buttonMac10->setText("4"); break; }
        case 0x5: { buttonMac10->setText("5"); break; }
        case 0x6: { buttonMac10->setText("6"); break; }
        case 0x7: { buttonMac10->setText("7"); break; }
        case 0x8: { buttonMac10->setText("8"); break; }
        case 0x9: { buttonMac10->setText("9"); break; }
        case 0xa: { buttonMac10->setText("A"); break; }
        case 0xb: { buttonMac10->setText("B"); break; }
        case 0xc: { buttonMac10->setText("C"); break; }
        case 0xd: { buttonMac10->setText("D"); break; }
        case 0xe: { buttonMac10->setText("E"); break; }
        case 0xf: { buttonMac10->setText("F"); break; }
    }

    buttonMac10->setFocus();
}
void MacDialog::onButtonDn10(void)
{
    if(idxMac[9] <= 0x0)
    {
        idxMac[9] = 0x10;
    }

    switch(--idxMac[9])
    {
        case 0x0: { buttonMac10->setText("0"); break; }
        case 0x1: { buttonMac10->setText("1"); break; }
        case 0x2: { buttonMac10->setText("2"); break; }
        case 0x3: { buttonMac10->setText("3"); break; }
        case 0x4: { buttonMac10->setText("4"); break; }
        case 0x5: { buttonMac10->setText("5"); break; }
        case 0x6: { buttonMac10->setText("6"); break; }
        case 0x7: { buttonMac10->setText("7"); break; }
        case 0x8: { buttonMac10->setText("8"); break; }
        case 0x9: { buttonMac10->setText("9"); break; }
        case 0xa: { buttonMac10->setText("A"); break; }
        case 0xb: { buttonMac10->setText("B"); break; }
        case 0xc: { buttonMac10->setText("C"); break; }
        case 0xd: { buttonMac10->setText("D"); break; }
        case 0xe: { buttonMac10->setText("E"); break; }
        case 0xf: { buttonMac10->setText("F"); break; }
    }

    buttonMac10->setFocus();
}
void MacDialog::onButtonUp11(void)
{
    if(idxMac[10] >= 0xf)
    {
        idxMac[10] = -(0x1);
    }

    switch(++idxMac[10])
    {
        case 0x0: { buttonMac11->setText("0"); break; }
        case 0x1: { buttonMac11->setText("1"); break; }
        case 0x2: { buttonMac11->setText("2"); break; }
        case 0x3: { buttonMac11->setText("3"); break; }
        case 0x4: { buttonMac11->setText("4"); break; }
        case 0x5: { buttonMac11->setText("5"); break; }
        case 0x6: { buttonMac11->setText("6"); break; }
        case 0x7: { buttonMac11->setText("7"); break; }
        case 0x8: { buttonMac11->setText("8"); break; }
        case 0x9: { buttonMac11->setText("9"); break; }
        case 0xa: { buttonMac11->setText("A"); break; }
        case 0xb: { buttonMac11->setText("B"); break; }
        case 0xc: { buttonMac11->setText("C"); break; }
        case 0xd: { buttonMac11->setText("D"); break; }
        case 0xe: { buttonMac11->setText("E"); break; }
        case 0xf: { buttonMac11->setText("F"); break; }
    }

    buttonMac11->setFocus();
}
void MacDialog::onButtonDn11(void)
{
    if(idxMac[10] <= 0x0)
    {
        idxMac[10] = 0x10;
    }

    switch(--idxMac[10])
    {
        case 0x0: { buttonMac11->setText("0"); break; }
        case 0x1: { buttonMac11->setText("1"); break; }
        case 0x2: { buttonMac11->setText("2"); break; }
        case 0x3: { buttonMac11->setText("3"); break; }
        case 0x4: { buttonMac11->setText("4"); break; }
        case 0x5: { buttonMac11->setText("5"); break; }
        case 0x6: { buttonMac11->setText("6"); break; }
        case 0x7: { buttonMac11->setText("7"); break; }
        case 0x8: { buttonMac11->setText("8"); break; }
        case 0x9: { buttonMac11->setText("9"); break; }
        case 0xa: { buttonMac11->setText("A"); break; }
        case 0xb: { buttonMac11->setText("B"); break; }
        case 0xc: { buttonMac11->setText("C"); break; }
        case 0xd: { buttonMac11->setText("D"); break; }
        case 0xe: { buttonMac11->setText("E"); break; }
        case 0xf: { buttonMac11->setText("F"); break; }
    }

    buttonMac11->setFocus();
}
void MacDialog::onButtonUp12(void)
{
    if(idxMac[11] >= 0xf)
    {
        idxMac[11] = -(0x1);
    }

    switch(++idxMac[11])
    {
        case 0x0: { buttonMac12->setText("0"); break; }
        case 0x1: { buttonMac12->setText("1"); break; }
        case 0x2: { buttonMac12->setText("2"); break; }
        case 0x3: { buttonMac12->setText("3"); break; }
        case 0x4: { buttonMac12->setText("4"); break; }
        case 0x5: { buttonMac12->setText("5"); break; }
        case 0x6: { buttonMac12->setText("6"); break; }
        case 0x7: { buttonMac12->setText("7"); break; }
        case 0x8: { buttonMac12->setText("8"); break; }
        case 0x9: { buttonMac12->setText("9"); break; }
        case 0xa: { buttonMac12->setText("A"); break; }
        case 0xb: { buttonMac12->setText("B"); break; }
        case 0xc: { buttonMac12->setText("C"); break; }
        case 0xd: { buttonMac12->setText("D"); break; }
        case 0xe: { buttonMac12->setText("E"); break; }
        case 0xf: { buttonMac12->setText("F"); break; }
    }

    buttonMac12->setFocus();
}
void MacDialog::onButtonDn12(void)
{
    if(idxMac[11] <= 0x0)
    {
        idxMac[11] = 0x10;
    }

    switch(--idxMac[11])
    {
        case 0x0: { buttonMac12->setText("0"); break; }
        case 0x1: { buttonMac12->setText("1"); break; }
        case 0x2: { buttonMac12->setText("2"); break; }
        case 0x3: { buttonMac12->setText("3"); break; }
        case 0x4: { buttonMac12->setText("4"); break; }
        case 0x5: { buttonMac12->setText("5"); break; }
        case 0x6: { buttonMac12->setText("6"); break; }
        case 0x7: { buttonMac12->setText("7"); break; }
        case 0x8: { buttonMac12->setText("8"); break; }
        case 0x9: { buttonMac12->setText("9"); break; }
        case 0xa: { buttonMac12->setText("A"); break; }
        case 0xb: { buttonMac12->setText("B"); break; }
        case 0xc: { buttonMac12->setText("C"); break; }
        case 0xd: { buttonMac12->setText("D"); break; }
        case 0xe: { buttonMac12->setText("E"); break; }
        case 0xf: { buttonMac12->setText("F"); break; }
    }

    buttonMac12->setFocus();
}
void MacDialog::onButtonAllClear(void)
{
    for(ii = 0; ii < 12; ii++)
    {
        idxMac[ii] = 0x0;
    }

    buttonMac1 ->setText("0");
    buttonMac2 ->setText("0");
    buttonMac3 ->setText("0");
    buttonMac4 ->setText("0");
    buttonMac5 ->setText("0");
    buttonMac6 ->setText("0");
    buttonMac7 ->setText("0");
    buttonMac8 ->setText("0");
    buttonMac9 ->setText("0");
    buttonMac10->setText("0");
    buttonMac11->setText("0");
    buttonMac12->setText("0");

    buttonMac1->setFocus();
}
void MacDialog::onButtonDefault(void)
{
    idxMac[ 0] = 0x0;
    idxMac[ 1] = 0x0;
    idxMac[ 2] = 0x0;
    idxMac[ 3] = 0x9;
    idxMac[ 4] = 0x1;
    idxMac[ 5] = 0xb;
    idxMac[ 6] = 0x0;
    idxMac[ 7] = 0x0;
    idxMac[ 8] = 0x0;
    idxMac[ 9] = 0x0;
    idxMac[10] = 0x0;
    idxMac[11] = 0x0;

    buttonMac1 ->setText("0");
    buttonMac2 ->setText("0");
    buttonMac3 ->setText("0");
    buttonMac4 ->setText("9");
    buttonMac5 ->setText("1");
    buttonMac6 ->setText("B");
    buttonMac7 ->setText("0");
    buttonMac8 ->setText("0");
    buttonMac9 ->setText("0");
    buttonMac10->setText("0");
    buttonMac11->setText("0");
    buttonMac12->setText("0");

    buttonMac7->setFocus();
}
void MacDialog::onButtonSave(void)
{
    mac = QString("%1%2:%3%4:%5%6:%7%8:%9%10:%11%12")
        .arg(idxMac[0],0,16).arg(idxMac[1],0,16).arg(idxMac[2],0,16).arg(idxMac[3],0,16).arg(idxMac[ 4],0,16).arg(idxMac[ 5],0,16)
        .arg(idxMac[6],0,16).arg(idxMac[7],0,16).arg(idxMac[8],0,16).arg(idxMac[9],0,16).arg(idxMac[10],0,16).arg(idxMac[11],0,16);

    QDialog::accept();
}
bool MacDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(((obj==buttonMac1) || (obj==buttonMac2)  || (obj==buttonMac3)  || (obj==buttonMac4)   ||
        (obj==buttonMac5) || (obj==buttonMac6)  || (obj==buttonMac7)  || (obj==buttonMac8)   ||
        (obj==buttonMac9) || (obj==buttonMac10) || (obj==buttonMac11) || (obj==buttonMac12)) && (event->type()==QEvent::FocusOut))
    {
        if ((buttonMac1->hasFocus() || buttonMac2 ->hasFocus() || buttonMac3 ->hasFocus() || buttonMac4 ->hasFocus()  ||
             buttonMac5->hasFocus() || buttonMac6 ->hasFocus() || buttonMac7 ->hasFocus() || buttonMac8 ->hasFocus()  ||
             buttonMac9->hasFocus() || buttonMac10->hasFocus() || buttonMac11->hasFocus() || buttonMac12->hasFocus()) && (isLockEsc==true))
        {
            isLockEsc=true;
        }
        else
        {
            isLockEsc=false;
        }
    }

    return QDialog::eventFilter(obj, event);
}
void MacDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
                 if(buttonMac1     ->hasFocus() && isLockEsc)  { onButtonUp1();                         }
            else if(buttonMac2     ->hasFocus() && isLockEsc)  { onButtonUp2();                         }
            else if(buttonMac3     ->hasFocus() && isLockEsc)  { onButtonUp3();                         }
            else if(buttonMac4     ->hasFocus() && isLockEsc)  { onButtonUp4();                         }
            else if(buttonMac5     ->hasFocus() && isLockEsc)  { onButtonUp5();                         }
            else if(buttonMac6     ->hasFocus() && isLockEsc)  { onButtonUp6();                         }
            else if(buttonMac7     ->hasFocus() && isLockEsc)  { onButtonUp7();                         }
            else if(buttonMac8     ->hasFocus() && isLockEsc)  { onButtonUp8();                         }
            else if(buttonMac9     ->hasFocus() && isLockEsc)  { onButtonUp9();                         }
            else if(buttonMac10    ->hasFocus() && isLockEsc)  { onButtonUp10();                        }
            else if(buttonMac11    ->hasFocus() && isLockEsc)  { onButtonUp11();                        }
            else if(buttonMac12    ->hasFocus() && isLockEsc)  { onButtonUp12();                        }
            else if(buttonMac1     ->hasFocus())               { buttonAllClear ->setFocus();           }
            else if(buttonMac2     ->hasFocus())               { buttonAllClear ->setFocus();           }
            else if(buttonMac3     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac4     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac5     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac6     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac7     ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac8     ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac9     ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac10    ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac11    ->hasFocus())               { buttonCancel   ->setFocus();           }
            else if(buttonMac12    ->hasFocus())               { buttonCancel   ->setFocus();           }
            else if(buttonAllClear ->hasFocus())               { buttonMac1     ->setFocus();           }
            else if(buttonDefault  ->hasFocus())               { buttonMac5     ->setFocus();           }
            else if(buttonSave     ->hasFocus())               { buttonMac8     ->setFocus();           }
            else if(buttonCancel   ->hasFocus())               { buttonMac12    ->setFocus();           }
            return;
        }
        case Qt::Key_Down:
        {
                 if(buttonMac1     ->hasFocus() && isLockEsc)  { onButtonDn1();                         }
            else if(buttonMac2     ->hasFocus() && isLockEsc)  { onButtonDn2();                         }
            else if(buttonMac3     ->hasFocus() && isLockEsc)  { onButtonDn3();                         }
            else if(buttonMac4     ->hasFocus() && isLockEsc)  { onButtonDn4();                         }
            else if(buttonMac5     ->hasFocus() && isLockEsc)  { onButtonDn5();                         }
            else if(buttonMac6     ->hasFocus() && isLockEsc)  { onButtonDn6();                         }
            else if(buttonMac7     ->hasFocus() && isLockEsc)  { onButtonDn7();                         }
            else if(buttonMac8     ->hasFocus() && isLockEsc)  { onButtonDn8();                         }
            else if(buttonMac9     ->hasFocus() && isLockEsc)  { onButtonDn9();                         }
            else if(buttonMac10    ->hasFocus() && isLockEsc)  { onButtonDn10();                        }
            else if(buttonMac11    ->hasFocus() && isLockEsc)  { onButtonDn11();                        }
            else if(buttonMac12    ->hasFocus() && isLockEsc)  { onButtonDn12();                        }
            else if(buttonMac1     ->hasFocus())               { buttonAllClear ->setFocus();           }
            else if(buttonMac2     ->hasFocus())               { buttonAllClear ->setFocus();           }
            else if(buttonMac3     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac4     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac5     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac6     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonMac7     ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac8     ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac9     ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac10    ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonMac11    ->hasFocus())               { buttonCancel   ->setFocus();           }
            else if(buttonMac12    ->hasFocus())               { buttonCancel   ->setFocus();           }
            else if(buttonAllClear ->hasFocus())               { buttonMac1     ->setFocus();           }
            else if(buttonDefault  ->hasFocus())               { buttonMac5     ->setFocus();           }
            else if(buttonSave     ->hasFocus())               { buttonMac8     ->setFocus();           }
            else if(buttonCancel   ->hasFocus())               { buttonMac12    ->setFocus();           }
            return;
        }
        case Qt::Key_Left:
        {
                 if(buttonMac1     ->hasFocus())               { buttonMac12    ->setFocus();           }
            else if(buttonMac2     ->hasFocus())               { buttonMac1     ->setFocus();           }
            else if(buttonMac3     ->hasFocus())               { buttonMac2     ->setFocus();           }
            else if(buttonMac4     ->hasFocus())               { buttonMac3     ->setFocus();           }
            else if(buttonMac5     ->hasFocus())               { buttonMac4     ->setFocus();           }
            else if(buttonMac6     ->hasFocus())               { buttonMac5     ->setFocus();           }
            else if(buttonMac7     ->hasFocus())               { buttonMac6     ->setFocus();           }
            else if(buttonMac8     ->hasFocus())               { buttonMac7     ->setFocus();           }
            else if(buttonMac9     ->hasFocus())               { buttonMac8     ->setFocus();           }
            else if(buttonMac10    ->hasFocus())               { buttonMac9     ->setFocus();           }
            else if(buttonMac11    ->hasFocus())               { buttonMac10    ->setFocus();           }
            else if(buttonMac12    ->hasFocus())               { buttonMac11    ->setFocus();           }
            else if(buttonAllClear ->hasFocus())               { buttonCancel   ->setFocus();           }
            else if(buttonDefault  ->hasFocus())               { buttonAllClear ->setFocus();           }
            else if(buttonSave     ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonCancel   ->hasFocus())               { buttonSave     ->setFocus();           }
            return;
        }
        case Qt::Key_Right:
        {
                 if(buttonMac1     ->hasFocus())               { buttonMac2     ->setFocus();           }
            else if(buttonMac2     ->hasFocus())               { buttonMac3     ->setFocus();           }
            else if(buttonMac3     ->hasFocus())               { buttonMac4     ->setFocus();           }
            else if(buttonMac4     ->hasFocus())               { buttonMac5     ->setFocus();           }
            else if(buttonMac5     ->hasFocus())               { buttonMac6     ->setFocus();           }
            else if(buttonMac6     ->hasFocus())               { buttonMac7     ->setFocus();           }
            else if(buttonMac7     ->hasFocus())               { buttonMac8     ->setFocus();           }
            else if(buttonMac8     ->hasFocus())               { buttonMac9     ->setFocus();           }
            else if(buttonMac9     ->hasFocus())               { buttonMac10    ->setFocus();           }
            else if(buttonMac10    ->hasFocus())               { buttonMac11    ->setFocus();           }
            else if(buttonMac11    ->hasFocus())               { buttonMac12    ->setFocus();           }
            else if(buttonMac12    ->hasFocus())               { buttonMac1     ->setFocus();           }
            else if(buttonAllClear ->hasFocus())               { buttonDefault  ->setFocus();           }
            else if(buttonDefault  ->hasFocus())               { buttonSave     ->setFocus();           }
            else if(buttonSave     ->hasFocus())               { buttonCancel   ->setFocus();           }
            else if(buttonCancel   ->hasFocus())               { buttonAllClear ->setFocus();           }
            return;
        }
        case Qt::Key_Enter:
        {
            if(!isLockEsc)
            {
                     if(buttonMac1 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac2 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac3 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac4 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac5 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac6 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac7 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac8 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac9 ->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac10->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac11->hasFocus())               { isLockEsc = true;                      }
                else if(buttonMac12->hasFocus())               { isLockEsc = true;                      }
            }

            break;
        }
        case Qt::Key_Escape:
        {
            if(isLockEsc)
            {

                if(buttonMac1 ->hasFocus() || buttonMac2 ->hasFocus() || buttonMac3 ->hasFocus() ||
                   buttonMac4 ->hasFocus() || buttonMac5 ->hasFocus() || buttonMac6 ->hasFocus() ||
                   buttonMac7 ->hasFocus() || buttonMac8 ->hasFocus() || buttonMac9 ->hasFocus() ||
                   buttonMac10->hasFocus() || buttonMac11->hasFocus() || buttonMac12->hasFocus())
                {
                    isLockEsc = false;
                    buttonSave->setFocus();
                }
            }
            else
            {
                reject();
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
void MacDialog::keyReleaseEvent(QKeyEvent *event)
{
    return;
}
