#include "customimagelabel.h"

CustomImageLabel::CustomImageLabel(QWidget *parent) :QLabel(parent)
{
    focusState = false;
}

CustomImageLabel::~CustomImageLabel()
{
}

void CustomImageLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        emit pressed();
    }
}

void CustomImageLabel::enterEvent(QEvent *e)
{
    emit focusIn();

    QWidget::enterEvent(e);
}

void CustomImageLabel::leaveEvent(QEvent *e)
{
    emit focusOut();

    QWidget::leaveEvent(e);
}

void CustomImageLabel::setFocusState(bool b)
{
    focusState = b;
}
bool CustomImageLabel::hasFocusState()
{
    return focusState;
}
