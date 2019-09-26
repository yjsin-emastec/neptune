#ifndef CUSTOMIMAGELABEL_H
#define CUSTOMIMAGELABEL_H

#include<QLabel>
#include<QWidget>
#include<QMouseEvent>

class CustomImageLabel : public QLabel
{
    Q_OBJECT

public :
    explicit CustomImageLabel(QWidget *parent);
    ~CustomImageLabel();

    void setFocusState(bool b);
    bool hasFocusState();


signals:
    void pressed();
    void focusIn();
    void focusOut();

protected :
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private :
    bool focusState;
};

#endif // CUSTOMIMAGELABEL_H
