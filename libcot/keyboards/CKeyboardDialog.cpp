#include "CKeyboardDialog.h"
#include "CKeyboardWidget.h"
#include <QGridLayout>
#include <QLocale>
#include <QLineEdit>

CKeyboardDialog::CKeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_keyboardWidget = new CKeyboardWidget(this);
    mainLayout->addWidget(m_keyboardWidget);
    connect(m_keyboardWidget, &CKeyboardWidget::returnPressed, this, &QDialog::accept);
}

CKeyboardDialog::~CKeyboardDialog()
{

}

QString CKeyboardDialog::text() const
{
    return m_keyboardWidget->text();
}

