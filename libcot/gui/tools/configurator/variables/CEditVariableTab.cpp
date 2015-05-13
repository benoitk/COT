#include "CEditVariableTab.h"
#include "CAutomate.h"
#include "CEditVariableTabUIHandler.h"
#include <IConfiguratorUIHandler.h>
#include <IVariableObjectDescriber.h>

CEditVariableTab::CEditVariableTab(QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_configuratorUIHandler = new CEditVariableTabUIHandler(scrollableWidget(), this);
    initBaseTab();
}

void CEditVariableTab::setVariables(IVariable *ivar)
{
    m_configuratorUIHandler->layout(ivar);
}

void CEditVariableTab::applyProperties(const QVariant &object)
{
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    IVariableObjectDescriber *describer = m_configuratorUIHandler->describer();
    ivar->setName(describer->getVariable(QStringLiteral("name"))->toString());
    ivar->setLabel(describer->getVariable(QStringLiteral("label"))->toString());
    //TODO add type/unit
}

