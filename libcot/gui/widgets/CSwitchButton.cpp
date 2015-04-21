#include "CSwitchButton.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QButtonGroup>
#include <QHBoxLayout>

CSwitchButton::CSwitchButton(QWidget *parent)
    : QWidget(parent)
    , m_buttonGroup(new QButtonGroup(this))
    , m_onButton(new CToolButton(this))
    , m_offButton(new CToolButton(this))
{
    m_onButton->setCheckable(true);
    m_onButton->setIcon(CToolButton::buttonIcon(CToolButton::On));
    m_onButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_onButton->setChecked(true);

    m_offButton->setCheckable(true);
    m_offButton->setIcon(CToolButton::buttonIcon(CToolButton::Off));
    m_offButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(m_onButton, Qt::Checked);
    m_buttonGroup->addButton(m_offButton, Qt::Unchecked);

    QHBoxLayout *hl = new QHBoxLayout(this);
    hl->setMargin(0);
    hl->addWidget(m_onButton);
    hl->addWidget(m_offButton);

    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    connect(m_onButton, &CToolButton::clicked, this, &CSwitchButton::buttonClicked);
    connect(m_offButton, &CToolButton::clicked, this, &CSwitchButton::buttonClicked);
}

bool CSwitchButton::isChecked() const
{
    return m_buttonGroup->checkedId() == Qt::Checked;
}

void CSwitchButton::setChecked(bool checked)
{
    m_buttonGroup->button(checked ? Qt::Checked : Qt::Unchecked)->setChecked(true);
}

void CSwitchButton::buttonClicked()
{
    emit checkedChanged(isChecked());
}

