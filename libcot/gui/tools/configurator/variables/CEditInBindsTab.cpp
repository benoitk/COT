#include "CEditInBindsTab.h"
#include "CAutomate.h"
#include "CEditInBindsUIHandler.h"

#include <IVariableObjectDescriber.h>

CEditInBindsTab::CEditInBindsTab(IVariable *ivar, QWidget *parent)
    : IConfiguratorEditTab(parent)
    , m_handler(new CEditInBindsUIHandler(scrollableWidget(), this))
{
    Q_ASSERT(ivar);
    m_handler->layout(ivar);
    initBaseTab();
}

void CEditInBindsTab::applyProperties(const QVariant &object)
{
    Q_UNUSED(object);
    // Nothing to do here
}
