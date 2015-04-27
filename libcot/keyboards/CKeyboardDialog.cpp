#include "CKeyboardDialog.h"
#include "CKeyboardWidget.h"
#include "CVerticalButtonBar.h"
#include <QGridLayout>
#include <QLocale>
#include <QLineEdit>
#include <QAction>

CKeyboardDialog::CKeyboardDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_keyboardWidget = new CKeyboardWidget(this);
    m_buttonBar = new CVerticalButtonBar(this);
    mainLayout->addWidget(m_keyboardWidget);
    mainLayout->addWidget(m_buttonBar);
    connect(m_buttonBar->addAction(CToolButton::Ok), &QAction::triggered,
            this, &CKeyboardDialog::accept);
    connect(m_buttonBar->addAction(CToolButton::Cancel), &QAction::triggered,
            this, &CKeyboardDialog::reject);
}

CKeyboardDialog::~CKeyboardDialog()
{

}

QString CKeyboardDialog::stringValue() const
{
    return m_keyboardWidget->text();
}

