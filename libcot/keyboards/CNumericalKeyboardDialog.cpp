#include "CNumericalKeyboardDialog.h"

#include <CPCWindow.h>
#include <QAction>

CNumericalKeyboardDialog::CNumericalKeyboardDialog(QWidget *parent)
    : CDialog(parent)
{
    initialize(CNumericalKeyboardWidget::Double);
}

CNumericalKeyboardDialog::CNumericalKeyboardDialog(CNumericalKeyboardWidget::Mode mode, QWidget *parent)
    : CDialog(parent)
{
    initialize(mode);
}

CNumericalKeyboardDialog::~CNumericalKeyboardDialog()
{
}

int CNumericalKeyboardDialog::integerValue() const
{
    return m_nkwKeyboard->integerNumber();
}

void CNumericalKeyboardDialog::setIntegerValue(int value)
{
    m_nkwKeyboard->setIntegerNumber(value);
}

float CNumericalKeyboardDialog::floatValue() const
{
    return m_nkwKeyboard->floatNumber();
}

void CNumericalKeyboardDialog::setFloatValue(float value, int precision)
{
    m_nkwKeyboard->setFloatNumber(value, precision);
}

bool CNumericalKeyboardDialog::getInteger(int &value, const QString &title, QWidget *parent)
{
    CNumericalKeyboardDialog dlg(CNumericalKeyboardWidget::Integer, parent);
    dlg.setTitle(!title.isEmpty() ? title : tr("Enter a new value"));
    dlg.setIntegerValue(value);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
        value = dlg.integerValue();
        return true;
    }

    return false;
}

void CNumericalKeyboardDialog::initialize(CNumericalKeyboardWidget::Mode mode)
{
    m_nkwKeyboard = new CNumericalKeyboardWidget(mode, this);
    setMainWidget(m_nkwKeyboard);

    connect(buttonBar()->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CNumericalKeyboardDialog::accept);
    connect(buttonBar()->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &CNumericalKeyboardDialog::reject);
}

