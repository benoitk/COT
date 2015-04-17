#include "CVerticalButtonBar.h"
#include "CToolButton.h"

#include <QVBoxLayout>
#include <QAction>

CVerticalButtonBar::CVerticalButtonBar(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->setMargin(0);
}

CVerticalButtonBar::~CVerticalButtonBar()
{
}

QAction *CVerticalButtonBar::addAction(CVerticalButtonBar::Button button, QAction *action)
{
    Q_UNUSED(button);
    QAction *act = m_actions.value(button);

    if (!act) {
        act = action ? action : new QAction(this);
        act->setText(QString::number(button));
        CToolButton *btn = new CToolButton(act, this);
        layout()->addWidget(btn);
        m_actions[button] = act;
        m_buttons[button] = btn;
    }

    return act;
}

QAction *CVerticalButtonBar::action(CVerticalButtonBar::Button button) const
{
    return m_actions.value(button);
}

CToolButton *CVerticalButtonBar::button(CVerticalButtonBar::Button button) const
{
    return m_buttons.value(button);
}
