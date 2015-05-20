#include "CEditOutBindsTab.h"
#include "CAutomate.h"
#include "CEditOutBindsUIHandler.h"

#include <IVariableObjectDescriber.h>

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
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    IVariableObjectDescriber *describer = m_configuratorUIHandler->describer();
    ivar->setListOutBinds(describer->getVariables());
}

