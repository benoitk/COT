#include "keyboarddialog.h"
#include "keyboardwidget.h"
#include <QGridLayout>
#include <QLocale>
#include <QLineEdit>

KeyboardDialog::KeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_keyboardWidget = new KeyboardWidget(this);
    mainLayout->addWidget(m_keyboardWidget);
    connect(m_keyboardWidget, &KeyboardWidget::returnPressed, this, &QDialog::accept);
}

KeyboardDialog::~KeyboardDialog()
{

}

QString KeyboardDialog::text() const
{
    return m_keyboardWidget->text();
}

