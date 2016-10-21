#include "CEditCycleTabUIHandler.h"
#include "IVariableObjectDescriber.h"

CEditCycleTabUIHandler::CEditCycleTabUIHandler(CAutomate* arg_automate,CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(arg_automate, scrollable, parent)
{
    setDescriber(new CVariableICycleDescriber(arg_automate, this));
}

void CEditCycleTabUIHandler::layout(ICycle *cycle)
{
    describer()->describe(QVariant::fromValue(cycle));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
