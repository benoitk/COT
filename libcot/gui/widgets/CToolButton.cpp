#include "CToolButton.h"

#include <QAction>
#include <QTimer>

CToolButton::CToolButton(QWidget *parent)
    : QToolButton(parent)
{
}

CToolButton::CToolButton(QAction *action, QWidget *parent)
    : QToolButton(parent)
{
    Q_ASSERT(action);
    setDefaultAction(action);
    QTimer::singleShot(25, this, &CToolButton::updateVisibility);
    connect(action, &QAction::changed, this, &CToolButton::updateVisibility);
}

CToolButton::~CToolButton()
{
}

void CToolButton::updateVisibility()
{
    setVisible(defaultAction()->isVisible());
}
