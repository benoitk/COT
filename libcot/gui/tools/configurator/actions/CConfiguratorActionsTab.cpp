#include "CConfiguratorActionsTab.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "ConfiguratorActionsUIHandler.h"
#include "IVariableObjectDescriber.h"

#include "CAutomate.h"

#include <QAction>

CConfiguratorActionsTab::CConfiguratorActionsTab(QWidget *parent)
    : IConfiguratorTab(parent)
{
    m_iactionUIHandler = new ConfiguratorActionsUIHandler(scrollableWidget(), this);
    slotUpdateLayout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorActionsTab::slotAddAction);
    connect(CAutomate::getInstance(), &CAutomate::signalActionsUpdated, this, &CConfiguratorActionsTab::slotUpdateLayout);

    initBaseTab();
}

void CConfiguratorActionsTab::slotAddAction()
{
    actionType type;
    if (!m_iactionUIHandler->selectActionType(type)) {
        return;
    }
}

void CConfiguratorActionsTab::slotUpdateLayout()
{
    m_iactionUIHandler->layout();
}
