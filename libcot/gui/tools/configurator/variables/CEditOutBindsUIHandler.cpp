#include "CEditOutBindsUIHandler.h"

#include <IVariableObjectDescriber.h>

CEditOutBindsUIHandler::CEditOutBindsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
    setDescriber(new CVariableIVariableOutBindsDescriber(this));
}

CEditOutBindsUIHandler::~CEditOutBindsUIHandler()
{
}

void CEditOutBindsUIHandler::layout(IVariable *ivar)
{
    describer()->describe(QVariant::fromValue(ivar));
    IConfiguratorUIHandler::layout(describer()->getVariables());
}
