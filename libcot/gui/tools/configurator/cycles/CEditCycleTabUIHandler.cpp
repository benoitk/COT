#include "CEditCycleTabUIHandler.h"
#include "IVariableObjectDescriber.h"

CEditCycleTabUIHandler::CEditCycleTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableICycleDescriber(this));
}

CEditCycleTabUIHandler::~CEditCycleTabUIHandler()
{
}

void CEditCycleTabUIHandler::layout(const CyclePair &cyclePair)
{
    describer()->describe(QVariant::fromValue(cyclePair));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
