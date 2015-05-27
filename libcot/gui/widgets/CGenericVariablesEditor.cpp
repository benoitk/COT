#include "CGenericVariablesEditor.h"
#include "CGenericVariablesUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <CVariableFactory.h>

CGenericVariablesEditor::CGenericVariablesEditor(QWidget *parent)
    : IScrollableUIWidget(parent)
    , m_handler(new CGenericVariablesUIHandler(scrollableWidget(), this))
{
}

void CGenericVariablesEditor::setVariables(const IVariablePtrList &variables, bool makeCopies)
{
    m_handler->layoutVariables(variables, makeCopies);
}

void CGenericVariablesEditor::applyProperties()
{
    m_handler->applyProperties();
}
