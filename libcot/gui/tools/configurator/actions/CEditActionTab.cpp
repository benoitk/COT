#include "CEditActionTab.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"
#include "CEditActionTabUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <IVariable.h>
#include <IAction.h>

CEditActionTab::CEditActionTab(IAction *action, QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_handler = new CEditActionTabUIHandler(scrollableWidget(), this);
    m_handler->layout(action);

    initBaseTab();
}

void CEditActionTab::applyProperties(const QVariant &object)
{
    IVariableObjectDescriber *describer = m_handler->describer();

    // We know hard coded variable names from our describer so just use them.
    // KDAB_TODO
//    action->setName(describer->getVariable(QStringLiteral("name"))->toString());
//    action->setLbl(describer->getVariable(QStringLiteral("label"))->toString());
}
