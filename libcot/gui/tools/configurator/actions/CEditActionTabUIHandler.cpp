#include "CEditActionTabUIHandler.h"
#include "IVariableObjectDescriber.h"
#include <IAction.h>

CEditActionTabUIHandler::CEditActionTabUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableIActionDescriber(this));
}

CEditActionTabUIHandler::~CEditActionTabUIHandler()
{
}

void CEditActionTabUIHandler::layout(IAction *action)
{
    describer()->describe(QVariant::fromValue(action));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
