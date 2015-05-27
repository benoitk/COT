#ifndef CVERTICALBUTTONBAR_H
#define CVERTICALBUTTONBAR_H

#include <QWidget>

#include "CToolButton.h"

class CVerticalButtonBar : public QWidget
{
    Q_OBJECT

public:
    explicit CVerticalButtonBar(QWidget *parent = Q_NULLPTR);
    ~CVerticalButtonBar();

    QAction *addAction(CToolButton::Type type, QAction *action = Q_NULLPTR);
    void removeAction(CToolButton::Type type);
    QAction *action(CToolButton::Type type) const;
    CToolButton *button(CToolButton::Type type) const;

private:
    QHash<CToolButton::Type, QAction *> m_actions;
    QHash<CToolButton::Type, CToolButton *> m_buttons;
};

#endif // CVERTICALBUTTONBAR_H
