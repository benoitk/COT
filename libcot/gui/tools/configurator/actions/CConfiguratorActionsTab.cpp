#include "CConfiguratorActionsTab.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "ConfiguratorActionsUIHandler.h"
#include "IVariableObjectDescriber.h"
#include "CEditActionWindow.h"
#include "CPCWindow.h"

#include <CAutomate.h>
#include <CActionFactory.h>

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

    IAction * action = CActionFactory::build(type, CAutomate::getInstance());
    Q_ASSERT(action);

    if (type == type_block) {
        // not yet handled.
    }
    else {
        CPCWindow::openModal<CEditActionWindow>(action);
    }
}

void CConfiguratorActionsTab::slotUpdateLayout()
{
    m_iactionUIHandler->layout();
}
