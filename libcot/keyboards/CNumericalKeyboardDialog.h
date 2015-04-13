#include "CNumericalKeyboardDialog.h"
#include "CNumericalKeyboardWidget.h"

#include <QVBoxLayout>

CNumericalKeyboardDialog::NumericalKeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_numericalKeyboardWidget = new CNumericalKeyboardWidget(this);
    connect(m_numericalKeyboardWidget, &CNumericalKeyboardWidget::returnPressed, this, &NumericalKeyboardDialog::accept);
    m_numericalKeyboardWidget->setObjectName(QStringLiteral("numericalkeyboard"));
    mainLayout->addWidget(m_numericalKeyboardWidget);
}

NumericalKeyboardDialog::~NumericalKeyboardDialog()
{

}

double NumericalKeyboardDialog::number() const
{
    return m_numericalKeyboardWidget->number();
}

