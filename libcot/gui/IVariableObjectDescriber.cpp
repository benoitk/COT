#include "IVariableObjectDescriber.h"
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

#include <QDebug>

typedef QPair<QString, ICycle *> CyclePair; // Stream Name, ICycle

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

void IVariableObjectDescriber::setVariables(IVariablePtrList variables)
{
    m_variables = variables;

    foreach (IVariable *ivar, m_variables) {
        m_variablesHash[ivar->getName()] = ivar;
        connect(ivar, &IVariable::signalVariableChanged, this, &IVariableObjectDescriber::slotVariableChanged);
    }
}

void IVariableObjectDescriber::slotVariableChanged()
{
    IVariable *variable = qobject_cast<IVariable *>(sender());
    Q_ASSERT(variable);
    emit signalVariableChanged(variable->getName());
}

// ICycle Describer

CVariableICycleDescriber::CVariableICycleDescriber(QObject *parent)
    : IVariableObjectDescriber(parent)
{
}

void CVariableICycleDescriber::describe(const QVariant &object)
{
    QString streamName;
    ICycle *cycle = Q_NULLPTR;

    if (object.canConvert<CyclePair>()) {
        const CyclePair cyclePair = object.value<CyclePair>();
        streamName = cyclePair.first;
        cycle = cyclePair.second;
    }
    else {
        cycle = object.value<ICycle *>();
        streamName = cycle->getRelatedStreamName();
    }

    Q_ASSERT(cycle);

    clear();

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, cycle->getLbl());
    label->setName("label");
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, cycle->getType());
    type->setName("type");
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::CycleType);

    CVariableInt *timer = CVariableFactory::castedBuild<CVariableInt *>(type_int, VariableOrganTypeNone, /*cycle->get()*/ -1); // KDAB_TODO: No customer api
    timer->setName("timer");
    timer->setLabel(tr("Timer"));

    CVariableMutable *stream = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, streamName);
    stream->setName("stream");
    stream->setLabel(tr("Stream"));
    stream->setMutableType(CVariableMutable::Stream);

    setVariables(IVariablePtrList() << label << type << timer << stream);
}


CVariableIVariableDescriber::CVariableIVariableDescriber(QObject *parent)
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

    QString unitName = ivar->getUnit() ? ivar->getUnit()->getName() : QString();
    CVariableMutable *unit = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, VariableOrganTypeNone, unitName);
    unit->setName(QStringLiteral("unit"));
    unit->setLabel(tr("Unit"));
    unit->setMutableType(CVariableMutable::Unit);

    //TODO add measure
    CVariableMeasure *measure = CVariableFactory::castedBuild<CVariableMeasure *>(type_measure, VariableOrganTypeNone);
    measure->setName(QStringLiteral("measure"));
    measure->setLabel(tr("Measure"));

    ivars << label << type << unit << measure;

    switch (ivar->getType()) {
    case type_float: {
        CVariableFloat *floatVariable = CVariableFactory::castedBuild<CVariableFloat *>(type_float, VariableOrganTypeNone, ivar->toFloat());
        floatVariable->setName(QStringLiteral("value"));
        floatVariable->setLabel(tr("Value"));
        ivars << floatVariable;
        break;
    }
    case type_int: {
        CVariableInt *intVariable = CVariableFactory::castedBuild<CVariableInt *>(type_int, VariableOrganTypeNone, ivar->toInt());
        intVariable->setName(QStringLiteral("value"));
        intVariable->setLabel(tr("Value"));
        ivars << intVariable;
        break;
    }
    case type_bool: {
        CVariableBool *boolVariable = CVariableFactory::castedBuild<CVariableBool *>(type_bool, VariableOrganTypeNone, ivar->toBool());
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


CVariableIActionDescriber::CVariableIActionDescriber(QObject *parent)
    : IVariableObjectDescriber(parent)
{

}

void CVariableIActionDescriber::describe(const QVariant &object)
{
    IAction *action = object.value<IAction *>();
    Q_ASSERT(action);

    clear();

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, VariableOrganTypeNone, action->getLabel());
    label->setName("label");
    label->setLabel(CVariableMutable::tr("Label"));

    m_variables << label;
    foreach (IVariable *ivar, m_variables) {
        m_variablesHash[ivar->getName()] = ivar;
    }
}
