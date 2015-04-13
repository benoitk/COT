#include "widget.h"
#include "CNumericalKeyboardWidget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_keyboardWidget = new CNumericalKeyboardWidget(this);
    mainLayout->addWidget(m_keyboardWidget);
}

