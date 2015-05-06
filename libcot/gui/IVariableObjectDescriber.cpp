#include "IVariableObjectDescriber.h"
#include "CVariableFactory.h"
#include "CVariableString.h"
#include "CVariableInt.h"
#include "CVariableMutable.h"
#include "ICycle.h"

IVariableObjectDescriber::IVariableObjectDescriber(QObject *parent)
    : QObject(parent)
{
}

IVariableObjectDescriber::~IVariableObjectDescriber()
{
    clear();
}

IVariablePtrList IVariableObjectDescriber::getVariables() const
{
    return m_variables;
}

IVariablePtr IVariableObjectDescriber::getVariable(const QString &name) const
{
    return m_variablesHash.value(name, Q_NULLPTR);
}

void IVariableObjectDescriber::clear() {
    CVariableFactory::deleteVariables(m_variables);
    m_variables.clear();
    m_variablesHash.clear();
}

// ICycle Describer

void IVariableICycleDescriber::describe(const QVariant &object)
{
    ICycle *cycle = object.value<ICycle *>();
    Q_ASSERT(cycle);

    clear();

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, cycle->getLbl());
    label->setName("label");
    label->setLabel(CVariableMutable::tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, cycle->getType());
    type->setName("type");
    type->setLabel(CVariableMutable::tr("Type"));
    type->setMutableType(CVariableMutable::CycleType);

    // KDAB_TODO: No customer api for timer property
    /*CVariableInt *timer = CVariableFactory::castedBuild<CVariableString *>(type_int, VariableOrganTypeNone, cycle->get());
    timer->setName("timer");
    timer->setLabel(CVariableMutable::tr("Timer"));*/

    m_variables << label << type /*<< timer*/;

    foreach (IVariable *ivar, m_variables) {
        m_variablesHash[ivar->getName()] = ivar;
    }
}
