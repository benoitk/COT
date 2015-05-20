#include "CEditOutBindsTab.h"
#include "CAutomate.h"
#include "CEditOutBindsUIHandler.h"

CEditOutBindsTab::CEditOutBindsTab(QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    m_configuratorUIHandler = new CEditOutBindsUIHandler(scrollableWidget(), this);

    initBaseTab();
}

void CEditOutBindsTab::setVariables(IVariable *ivar)
{
    m_configuratorUIHandler->layout(ivar);
}

void CEditOutBindsTab::applyProperties(const QVariant &object)
{
    //TODO
#if 0
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    IVariableObjectDescriber *describer = m_configuratorUIHandler->describer();
    ivar->setLabel(describer->getVariable(QStringLiteral("label"))->toString());
    //TODO add type/unit
    ivar->setListOutBinds(lstVar);
#endif
}

