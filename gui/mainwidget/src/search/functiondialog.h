#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H


#include <QtGui/QDialog>
#include "ui_functiondialog.h"
#include "main/mainglobal.h"

class TextMessageDialog;
class SystemLogPage;
class UiKeyboardDialog;

class FunctionDialog : public QDialog, public Ui::FunctionDialog
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

private slots:
    void onButtonFilter();
    void onButtonSort();
    void onButtonBackup();
    void onButtonDelete();
    void onButtonClose();

private:
    UiKeyboardDialog *keyboard;
    TextMessageDialog *msgBox;

    QString logFilter, logSort;

};

#endif // FUNCTIONDIALOG_H
