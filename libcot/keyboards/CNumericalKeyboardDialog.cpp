#include "CNumericalKeyboardDialog.h"
#include "CVerticalButtonBar.h"

#include <QVBoxLayout>
#include <QAction>

CNumericalKeyboardDialog::CNumericalKeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    initialize(CNumericalKeyboardWidget::Double);
}

CNumericalKeyboardDialog::CNumericalKeyboardDialog(CNumericalKeyboardWidget::Mode mode, QWidget *parent)
    : QDialog(parent)
{
    initialize(mode);
}

CNumericalKeyboardDialog::~CNumericalKeyboardDialog()
{

}

int CNumericalKeyboardDialog::integerValue() const
{
    return static_cast<int>(m_numericalKeyboardWidget->number());
}

double CNumericalKeyboardDialog::doubleValue() const
{
    return m_numericalKeyboardWidget->number();
}

void CNumericalKeyboardDialog::initialize(CNumericalKeyboardWidget::Mode mode)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_numericalKeyboardWidget = new CNumericalKeyboardWidget(mode, this);
    m_buttonBar = new CVerticalButtonBar(this);
    m_numericalKeyboardWidget->setObjectName(QStringLiteral("numericalkeyboard"));
    mainLayout->addWidget(m_numericalKeyboardWidget);
    mainLayout->addWidget(m_buttonBar);
    connect(m_buttonBar->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CNumericalKeyboardDialog::accept);
    connect(m_buttonBar->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &CNumericalKeyboardDialog::reject);
}

