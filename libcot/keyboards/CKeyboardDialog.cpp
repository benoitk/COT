#include "CKeyboardDialog.h"
#include "CKeyboardWidget.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QAction>

CKeyboardDialog::CKeyboardDialog(QWidget *parent)
    : CDialog(parent)
{
    m_kwKeyboard = new CKeyboardWidget(this);
    setMainWidget(m_kwKeyboard);

    connect(buttonBar()->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CKeyboardDialog::accept);
    connect(buttonBar()->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &CKeyboardDialog::reject);
}

CKeyboardDialog::~CKeyboardDialog()
{
}

QString CKeyboardDialog::stringValue() const
{
    return m_kwKeyboard->text();
}

void CKeyboardDialog::setStringValue(const QString &value)
{
    m_kwKeyboard->setText(value);
}

