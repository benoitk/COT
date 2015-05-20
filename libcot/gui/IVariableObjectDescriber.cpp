#include "IVariableObjectDescriber.h"
#include "IVariableUIHandler.h"
#include "CVariableFactory.h"
#include "CVariableString.h"
#include "CVariableInt.h"
#include "CVariableMutable.h"
#include "ICycle.h"
#include "CUnit.h"

#include <CVariableBool.h>
#include <CVariableFloat.h>
#include <CVariableMeasure.h>
#include <IAction.h>
#include <CStep.h>

#include "cotgui_debug.h"

IVariableObjectDescriber::IVariableObjectDescriber(IVariableUIHandler *parent)
    : QObject(parent)
{
    Q_ASSERT(parent);
}

IVariableObjectDescriber::~IVariableObjectDescriber()
{
    clear();
}

IVariablePtrList IVariableObjectDescriber::getVariables() const
{
    return m_variables;
}

#if 0 // currently unused
QHash<QString, IVariablePtr> IVariableObjectDescriber::getVariablesHash() const
{
    return m_variablesHash;
}
#endif

IVariablePtr IVariableObjectDescriber::getVariable(const QString &name) const
{
    return m_variablesHash.value(name, Q_NULLPTR);
}

void IVariableObjectDescriber::clear() {
    CVariableFactory::deleteVariables(m_variables);
    m_variables.clear();
    m_variablesHash.clear();
}

void IVariableObjectDescriber::setVariables(IVariablePtrList variables)
{
    m_variables = variables;

    foreach (IVariable *ivar, m_variables) {
        m_variablesHash[ivar->getName()] = ivar;
        connect(ivar, &IVariable::signalVariableChanged, this, &IVariableObjectDescriber::slotVariableChanged);
    }
}

void IVariableObjectDescriber::setVariableAccess(IVariable *ivar, int access)
{
    ivar->setAccess(variableAccess(access));
}

void IVariableObjectDescriber::slotVariableChanged()
{
    IVariable *variable = qobject_cast<IVariable *>(sender());
    Q_ASSERT(variable);
    emit signalVariableChanged(variable->getName());
}

// ICycle Describer

CVariableICycleDescriber::CVariableICycleDescriber(IVariableUIHandler *parent)
    : IVariableObjectDescriber(parent)
{
}

void CVariableICycleDescriber::describe(const QVariant &object)
{
    ICycle *cycle = object.value<ICycle *>();
    Q_ASSERT(cycle);
    QString streamName = cycle->getRelatedStreamName();

    clear();

    CVariableString *name = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, cycle->getName());
    setVariableAccess(name, access_read);
    name->setName("name");
    name->setLabel(tr("Name"));

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, cycle->getLabel());
    label->setName("label");
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, cycle->getType());
    setVariableAccess(type, access_read);
    type->setName("type");
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::CycleType);

    CVariableInt *timer = CVariableFactory::castedBuild<CVariableInt *>(type_int, VariableOrganTypeNone, /*cycle->get()*/ -1); // SERES_TODO: Add api
    setVariableAccess(timer, access_read_write);
    timer->setName("timer");
    timer->setLabel(tr("Timer"));

    CVariableMutable *stream = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, streamName);
    stream->setName("stream");
    stream->setLabel(tr("Stream"));
    stream->setMutableType(CVariableMutable::Stream);

    setVariables(IVariablePtrList() << name << label << type << timer << stream);
}


CVariableIVariableDescriber::CVariableIVariableDescriber(IVariableUIHandler *parent)
    : IVariableObjectDescriber(parent)
{
}

void CVariableIVariableDescriber::describe(const QVariant &object)
{
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    clear();

    IVariablePtrList ivars;

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, ivar->getLabel());
    label->setName(QStringLiteral("label"));
    label->setLabel(CVariableString::tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, ivar->getType());
    type->setName(QStringLiteral("type"));
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::VariableType);
    setVariableAccess(type, access_read);

    QString unitName = ivar->getUnit() ? ivar->getUnit()->getName() : QString();
    CVariableMutable *unit = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, unitName);
    unit->setName(QStringLiteral("unit"));
    unit->setLabel(tr("Unit"));
    unit->setMutableType(CVariableMutable::Unit);


    CVariableMutable *measure = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, ivar->getLabel());
    measure->setName(QStringLiteral("measure"));
    measure->setLabel(tr("Measure"));
    measure->setMutableType(CVariableMutable::Measure);

    ivars << label << type << unit << measure;

    switch (ivar->getType()) {
    case type_float: {
        CVariableFloat *floatVariable = CVariableFactory::castedBuild<CVariableFloat *>(type_float, VariableOrganTypeNone, ivar->toFloat());
        setVariableAccess(floatVariable, access_read_write);
        floatVariable->setName(QStringLiteral("value"));
        floatVariable->setLabel(tr("Value"));
        ivars << floatVariable;
        break;
    }
    case type_int: {
        CVariableInt *intVariable = CVariableFactory::castedBuild<CVariableInt *>(type_int, VariableOrganTypeNone, ivar->toInt());
        setVariableAccess(intVariable, access_read_write);
        intVariable->setName(QStringLiteral("value"));
        intVariable->setLabel(tr("Value"));
        ivars << intVariable;
        break;
    }
    case type_bool: {
        CVariableBool *boolVariable = CVariableFactory::castedBuild<CVariableBool *>(type_bool, VariableOrganTypeNone, ivar->toBool());
        setVariableAccess(boolVariable, access_read_write);
        boolVariable->setName(QStringLiteral("value"));
        boolVariable->setLabel(tr("Value"));
        ivars << boolVariable;
        break;
    }
    default:
        break;
    }

    setVariables(ivars);
}


CVariableIActionDescriber::CVariableIActionDescriber(IVariableUIHandler *parent)
    : IVariableObjectDescriber(parent)
{
}

void CVariableIActionDescriber::describe(const QVariant &object)
{
    IAction *action = object.value<IAction *>();
    Q_ASSERT(action);

    clear();
    IVariablePtrList ivars;
    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, action->getLabel());
    label->setName("label");
    label->setLabel(CVariableMutable::tr("Label"));
    ivars << label;
    setVariables(ivars);
}


CVariableCStepDescriber::CVariableCStepDescriber(IVariableUIHandler *parent)
    : IVariableObjectDescriber(parent)
{
}

void CVariableCStepDescriber::describe(const QVariant &object)
{
    CStep *step = object.value<CStep *>();
    Q_ASSERT(step);

    clear();

    CVariableInt *interval = CVariableFactory::castedBuild<CVariableInt *>(type_int, VariableOrganTypeNone, step->getNumStep());
    setVariableAccess(interval, access_read_write);
    interval->setName("interval");
    interval->setLabel(tr("Interval"));

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, step->getLabel());
    label->setName("label");
    label->setLabel(tr("Label"));

    setVariables(IVariablePtrList() << interval << label);
}
