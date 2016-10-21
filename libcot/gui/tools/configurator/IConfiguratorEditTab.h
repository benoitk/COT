#ifndef ICONFIGURATOREDITTAB_H
#define ICONFIGURATOREDITTAB_H

#include "IScrollableUIWidget.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"

#include <QAction>

/*
 * This class is used in configurator part needed specific editing window (see IConfiguratorEditWindow).
 * Each tabs has to inherits that and call initBaseTab() as last membr in your constructor.
 * When validating the IConfiguratorEditWindow, it will call applyProperties() for each tabs whith the edited object
 * encapsuled in a QVariant.
 */
class IConfiguratorEditTab : public IScrollableUIWidget
{
    Q_OBJECT

public:
    explicit IConfiguratorEditTab(QWidget *parent = Q_NULLPTR) : IScrollableUIWidget(parent) {
    }

    void initBaseTab() {
        buttonBar()->addAction(CToolButton::ScrollUp, scrollableWidget()->moveUp());
        buttonBar()->addAction(CToolButton::ScrollDown, scrollableWidget()->moveDown());
        connect(buttonBar()->addAction(CToolButton::Ok), &QAction::triggered, this, &IConfiguratorEditTab::signalOkTriggered);
        connect(buttonBar()->addAction(CToolButton::Cancel), &QAction::triggered, this, &IConfiguratorEditTab::signalCancelTriggered);
    }

    virtual void applyProperties(const QVariant &object) = 0;

signals:
    void signalOkTriggered();
    void signalCancelTriggered();

};

#endif // ICONFIGURATOREDITTAB_H
