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

void CEditVariableTabUIHandler::layout(IVariable *ivar)
{
    describer()->describe(QVariant::fromValue(ivar));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
