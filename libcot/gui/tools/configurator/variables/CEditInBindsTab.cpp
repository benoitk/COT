#include "CEditInBindsTab.h"
#include "CAutomate.h"
#include "CEditInBindsUIHandler.h"
#include <IConfiguratorUIHandler.h>

CEditInBindsTab::CEditInBindsTab(QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    
    m_configuratorUIHandler = new CEditInBindsUIHandler(scrollableWidget(), this);

    initBaseTab();
}

void CEditInBindsTab::setVariables(IVariable *ivar)
{
    Q_ASSERT(ivar);
    const QList<IVariable *> listInBinds = ivar->getListInBinds();
    m_configuratorUIHandler->layout(listInBinds);
}

void CEditInBindsTab::applyProperties(const QVariant &object)
{
    Q_UNUSED(object);
    //ReadOnly => nothing to do
}
