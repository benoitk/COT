#include "numericalkeyboarddialog.h"
#include "numericalkeyboardwidget.h"

#include <QVBoxLayout>

NumericalKeyboardDialog::NumericalKeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_numericalKeyboardWidget = new NumericalKeyboardWidget(this);
    connect(m_numericalKeyboardWidget, &NumericalKeyboardWidget::returnPressed, this, &NumericalKeyboardDialog::accept);
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

