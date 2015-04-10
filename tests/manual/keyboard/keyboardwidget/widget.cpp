#include "widget.h"

#include "../../../../cot/keyboards/keyboardwidget.h"
#include "localcombobox.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QApplication>
#include <QTranslator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    LocalComboBox *combobox = new LocalComboBox(this);

    connect(combobox, &LocalComboBox::localeSelected, this, &Widget::slotChangeLocale);
    mainLayout->addWidget(combobox);
    m_keyboardWidget = new KeyboardWidget(this);
    mainLayout->addWidget(m_keyboardWidget);
}

void Widget::slotChangeLocale(QLocale::Language local)
{
    QLocale loc(local, QLocale::AnyCountry);
    QLocale::setDefault(loc);
}
