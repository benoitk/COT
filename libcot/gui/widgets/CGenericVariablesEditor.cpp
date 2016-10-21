#include "CGenericVariablesEditor.h"
#include "CGenericVariablesUIHandler.h"
#include "IVariableObjectDescriber.h"

#include <CVariableFactory.h>

CGenericVariablesEditor::CGenericVariablesEditor(CAutomate* arg_automate, QWidget *parent)
    : IScrollableUIWidget(parent)
    , m_handler(new CGenericVariablesUIHandler(arg_automate, scrollableWidget(), this))
    , m_validator(Q_NULLPTR)
    , m_userData1(Q_NULLPTR)
    , m_userData2(Q_NULLPTR)
{
}

IVariable *CGenericVariablesEditor::getVariable(const QString &name) const
{
    return m_handler->getVariable(name);
}

void CGenericVariablesEditor::setValidator(CGenericVariablesEditor::ValidatorFunc validator, void *userData1, void *userData2)
{
    m_validator = validator;
    m_userData1 = userData1;
    m_userData2 = userData2;
}

void CGenericVariablesEditor::setVariables(const IVariablePtrList &variables, bool makeCopies)
{
    m_handler->layoutVariables(variables, makeCopies);
}

bool CGenericVariablesEditor::applyProperties()
{
    if (m_validator) {
        if (!m_validator(this, m_userData1, m_userData2)) {
            return false;
        }
    }

    m_handler->applyProperties();
    emit signalPropertiesApplied();
    return true;
}
