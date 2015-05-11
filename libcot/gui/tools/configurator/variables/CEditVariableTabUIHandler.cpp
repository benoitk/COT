#include "CEditVariableTabUIHandler.h"
#include "IVariableObjectDescriber.h"

CEditVariableTabUIHandler::CEditVariableTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableIVariableDescriber(this));
}

CEditVariableTabUIHandler::~CEditVariableTabUIHandler()
{
}

void CEditVariableTabUIHandler::layout()
{
#if 0
    describer()->describe(QVariant::fromValue(cyclePair));
#endif
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
