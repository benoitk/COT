#include "CVerticalButtonBar.h"

#include <QVBoxLayout>
#include <QAction>

CVerticalButtonBar::CVerticalButtonBar(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->setMargin(0);
    vl->addStretch();
}

CVerticalButtonBar::~CVerticalButtonBar()
{
}

QAction *CVerticalButtonBar::addAction(CToolButton::Type type, QAction *action)
{
    Q_ASSERT(type != CToolButton::Invalid);

    QAction *act = m_actions.value(type);

    if (!act) {
        act = action ? action : new QAction(this);
        CToolButton *btn = new CToolButton(type, act, this);
        layout()->addWidget(btn);
        m_actions[type] = act;
        m_buttons[type] = btn;

        if (btn->icon().isNull()) {
            act->setText(QString::number(type));
        }
    }

    return act;
}

void CVerticalButtonBar::removeAction(CToolButton::Type type)
{
    CToolButton *button = m_buttons.take(type);
    QAction *action = m_actions.take(type);

    if (button) {
        button->deleteLater();
    }

    if (action && action->parent() == this) {
        action->deleteLater();
    }
}

QAction *CVerticalButtonBar::action(CToolButton::Type type) const
{
    return m_actions.value(type);
}

CToolButton *CVerticalButtonBar::button(CToolButton::Type type) const
{
    return m_buttons.value(type);
}
