#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H


#include <QtGui/QDialog>
#include "ui_functiondialog.h"
#include "ui_functiondialog1080p.h"
#include "main/mainglobal.h"

class TextMessageDialog;
class SystemLogPage;
class UiKeyboardDialog;

class FunctionDialog : public QDialog
{
    Q_OBJECT

public:
    FunctionDialog(QWidget *parent=0);
    ~FunctionDialog();

    QString getLogFilter();
    QString getLogSort();

    void setLogFilter(QString filter);
    void setLogSort(QString sort);
    void KeyPressEvent(int key);

    QFrame *frame;
    QPushButton *buttonBackup;
    QPushButton *buttonClose;
    QPushButton *buttonDelete;
    QPushButton *buttonFilter;
    QPushButton *buttonSort;

private slots:
    void onButtonFilter();
    void onButtonSort();
    void onButtonBackup();
    void onButtonDelete();
    void onButtonClose();

private:
    UiKeyboardDialog *keyboard;
    TextMessageDialog *msgBox;

    void loadStyleSheet();

    QString logFilter, logSort;
};

#endif // FUNCTIONDIALOG_H
