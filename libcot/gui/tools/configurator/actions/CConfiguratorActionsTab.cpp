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

CConfiguratorActionsTab::CConfiguratorActionsTab(CAutomate* arg_automate, QWidget *parent)
    : IConfiguratorTab(parent)
    , m_automate(arg_automate)
{
    m_iactionUIHandler = new ConfiguratorActionsUIHandler(arg_automate, scrollableWidget(), this);
    slotUpdateLayout();

    connect(buttonBar()->addAction(CToolButton::Add), &QAction::triggered, this, &CConfiguratorActionsTab::slotAddAction);
    connect(arg_automate, &CAutomate::signalActionsUpdated, this, &CConfiguratorActionsTab::slotUpdateLayout);

    initBaseTab();
}

void CConfiguratorActionsTab::slotAddAction()
{
    actionType type;
    if (!m_iactionUIHandler->selectActionType(type)) {
        return;
    }

    IAction * action = CActionFactory::build(type, m_automate);
    Q_ASSERT(action);
    CPCWindow::openModal<CEditActionWindow>(m_automate, action);
}

void CConfiguratorActionsTab::slotUpdateLayout()
{
    m_iactionUIHandler->layout();
}
