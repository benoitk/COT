#ifndef ICONFIGURATORTAB_H
#define ICONFIGURATORTAB_H

#include "IScrollableUIWidget.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"

#include <QAction>

/*
 * This is teh base class for tabs added in the Configurator window.
 * Each tabs has to inherits that and call initBaseTab() as last membr in your constructor.
 */
class IConfiguratorTab : public IScrollableUIWidget
{
    Q_OBJECT

public:
    explicit IConfiguratorTab(QWidget *parent = Q_NULLPTR) : IScrollableUIWidget(parent) { }

    void initBaseTab() {
        buttonBar()->addAction(CToolButton::ScrollUp, scrollableWidget()->moveUp());
        buttonBar()->addAction(CToolButton::ScrollDown, scrollableWidget()->moveDown());
        connect(buttonBar()->addAction(CToolButton::Back), &QAction::triggered, this, &IConfiguratorTab::signalBackTriggered);
    }

signals:
    void signalBackTriggered();
};

#endif // ICONFIGURATORTAB_H
