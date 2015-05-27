#include "CEditCycleTabUIHandler.h"
#include "IVariableObjectDescriber.h"

CEditCycleTabUIHandler::CEditCycleTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableICycleDescriber(this));
}

void CEditCycleTabUIHandler::layout(ICycle *cycle)
{
    describer()->describe(QVariant::fromValue(cycle));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
