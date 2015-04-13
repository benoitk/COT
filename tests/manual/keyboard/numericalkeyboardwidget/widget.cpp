#include "widget.h"
#include "numericalkeyboardwidget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_keyboardWidget = new NumericalKeyboardWidget(this);
    mainLayout->addWidget(m_keyboardWidget);
}

