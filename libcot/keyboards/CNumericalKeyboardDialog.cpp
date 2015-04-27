#include "CNumericalKeyboardDialog.h"
#include "CNumericalKeyboardWidget.h"

#include <QVBoxLayout>

CNumericalKeyboardDialog::CNumericalKeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_numericalKeyboardWidget = new CNumericalKeyboardWidget(this);
    connect(m_numericalKeyboardWidget, &CNumericalKeyboardWidget::returnPressed, this, &CNumericalKeyboardDialog::accept);
    m_numericalKeyboardWidget->setObjectName(QStringLiteral("numericalkeyboard"));
    mainLayout->addWidget(m_numericalKeyboardWidget);
}

CNumericalKeyboardDialog::~CNumericalKeyboardDialog()
{

}

double CNumericalKeyboardDialog::number() const
{
    return m_numericalKeyboardWidget->number();
}

