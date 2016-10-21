#include "CGenericVariablesUIHandler.h"

#include <CVariableFactory.h>

CGenericVariablesUIHandler::CGenericVariablesUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable, QObject *parent)
    : IVariableUIHandler(arg_automate, scrollable, parent)
{
}

CGenericVariablesUIHandler::~CGenericVariablesUIHandler()
{
    unwatchVariables(m_editedVariables.values());
    CVariableFactory::deleteVariables(m_variablesCopies);
}

IVariable *CGenericVariablesUIHandler::getVariable(const QString &name) const
{
    IVariablePtr ivar = m_editedVariables.value(name);

    if (!ivar) {
        ivar = IVariableUIHandler::getVariable(name);
    }

    return ivar;
}

void CGenericVariablesUIHandler::layoutVariables(const QList<IVariable *> &variables, bool makeCopies)
{
    unwatchVariables(m_editedVariables.values());
    m_editedVariables.clear();
    m_variables = variables;
    CVariableFactory::deleteVariables(m_variablesCopies);

    foreach (IVariable *ivar, m_variables) {
        Q_ASSERT(ivar);
        Q_ASSERT(!ivar->getName().isEmpty());

        if (makeCopies) {
            IVariable *ivarCopy = CVariableFactory::duplicateTemporary(ivar->getAutomate(), this, ivar);
            m_variablesCopies << ivarCopy;
            m_editedVariables[ivarCopy->getName()] = ivarCopy;
        }
        else {
            m_editedVariables[ivar->getName()] = ivar;
        }
    }

    watchVariables(m_editedVariables.values());
    IVariableUIHandler::layout(m_variablesCopies.isEmpty() ? m_variables : m_variablesCopies);
}

void CGenericVariablesUIHandler::applyProperties()
{
    if (m_variablesCopies.isEmpty()) {
        // nothing to do
    }
    else {
        Q_ASSERT(m_variables.count() == m_variablesCopies.count());

        for (int i = 0; i < m_variables.count(); ++i) {
            m_variables[i]->setValue(m_variablesCopies[i]->toVariant());
        }
    }
}

void CGenericVariablesUIHandler::watchVariables(const IVariablePtrList &variables)
{
    foreach (IVariable *ivar, variables) {
        connect(ivar, &IVariable::signalVariableChanged, this, &CGenericVariablesUIHandler::slotVariableChanged);
    }
}

void CGenericVariablesUIHandler::unwatchVariables(const IVariablePtrList &variables)
{
    foreach (IVariable *ivar, variables) {
        disconnect(ivar, &IVariable::signalVariableChanged, this, &CGenericVariablesUIHandler::slotVariableChanged);
    }
}

void CGenericVariablesUIHandler::slotVariableChanged()
{
    IVariable *ivar = qobject_cast<IVariable *>(sender());
    Q_ASSERT(ivar);
    IVariableUIHandler::slotVariableChanged(ivar->getName());
}
