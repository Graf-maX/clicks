#include "Label.h"

#include <QMouseEvent>

Label::Label(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
}

Label::~Label()
{
}

void Label::mousePressEvent(QMouseEvent* /*event*/)
{
    emit clicked();
}

