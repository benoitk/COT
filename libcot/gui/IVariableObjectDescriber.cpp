#include "IVariableObjectDescriber.h"
#include "IVariableUIHandler.h"
#include "CVariableFactory.h"
#include "CVariableString.h"
#include "CVariableStream.h"
#include "CVariableInt.h"
#include "CVariableMutable.h"

#include <ICycle.h>
#include <CUnit.h>
#include <CAutomate.h>
#include <CVariableBool.h>
#include <CVariableFloat.h>
#include <CVariableMeasure.h>
#include <CVariableStream.h>
#include <IAction.h>
#include <CStep.h>
#include <IOrgan.h>

#include "cotgui_debug.h"

// IVariableObjectDescriber

IVariableObjectDescriber::IVariableObjectDescriber(CAutomate* arg_automate, IVariableUIHandler *parent)
    : QObject(parent), m_automate(arg_automate)
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

bool IVariableObjectDescriber::hasValue(const QVariant &value) const
{
    foreach (IVariable *ivar, m_variables) {
        if (ivar->toVariant() == value) {
            return true;
        }
    }

    return false;
}

void IVariableObjectDescriber::changeVariable(const QString &name, IVariable *ivar)
{
    IVariable *oldIVar = m_variablesHash.take(name);

    if (!oldIVar) {
        return;
    }

    delete oldIVar;

    const int index = m_variables.indexOf(oldIVar);
    m_variablesHash[name] = ivar;
    m_variables[index] = ivar;
    connect(ivar, &IVariable::signalVariableChanged, this, &IVariableObjectDescriber::slotVariableChanged);
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
    ivar->setAccess(enumVariableAccess(access));
}

void IVariableObjectDescriber::slotVariableChanged()
{
    IVariable *variable = qobject_cast<IVariable *>(sender());
    Q_ASSERT(variable);
    emit signalVariableChanged(variable->getName());
}

// CVariableICycleDescriber

CVariableICycleDescriber::CVariableICycleDescriber(CAutomate* arg_automate,IVariableUIHandler *parent)
    : IVariableObjectDescriber(arg_automate, parent)
{
}

void CVariableICycleDescriber::describe(const QVariant &object)
{
    ICycle *cycle = object.value<ICycle *>();
    Q_ASSERT(cycle);

    CVariableStream * cycleStream = m_automate->getCycleStream(cycle);
    QString streamName = cycleStream ? cycleStream->getName() : QString();


    clear();

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(m_automate, this, e_type_string, e_type_organ_none, cycle->getLabel());
    label->setName("label");
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, cycle->getType());
    setVariableAccess(type, e_access_read);
    type->setName("type");
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::CycleType);

    CVariableInt *timer = CVariableFactory::castedBuild<CVariableInt *>(m_automate, this, e_type_int, e_type_organ_none, /*cycle->get()*/ -1); // SERES_TODO: Add api
    setVariableAccess(timer, e_access_read_write);
    timer->setName("timer");
    timer->setLabel(tr("Timer"));

    CVariableMutable *stream = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, streamName);
    setVariableAccess(stream, e_access_read_write);
    stream->setName("stream");
    stream->setLabel(tr("Stream"));
    stream->setMutableType(CVariableMutable::Stream);

    setVariables(IVariablePtrList() << label << type << timer << stream);
}

// CVariableIVariableDescriber

CVariableIVariableDescriber::CVariableIVariableDescriber(CAutomate* arg_automate,IVariableUIHandler *parent)
    : IVariableObjectDescriber(arg_automate, parent)
{
}

void CVariableIVariableDescriber::describe(const QVariant &object)
{
       IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    clear();

    IVariablePtrList ivars;
    CVariableMutable *organ = Q_NULLPTR;
    IVariable *value = Q_NULLPTR;

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(m_automate, this, e_type_string, e_type_organ_none, ivar->getLabel());
    label->setName(QStringLiteral("label"));
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, ivar->getType());
    setVariableAccess(type, e_access_read);
    type->setName(QStringLiteral("type"));
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::VariableType);

    CVariableMutable *subType = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, ivar->getOrganType());
    setVariableAccess(subType, e_access_read);
    subType->setName(QStringLiteral("subtype"));
    subType->setLabel(tr("SubType"));
    subType->setMutableType(CVariableMutable::VarOrganType);

    switch (ivar->getType()) {
        case e_type_float:
            value = CVariableFactory::castedBuild<CVariableFloat *>(m_automate, this, e_type_float, e_type_organ_none, ivar->toFloat());
            break;

        case e_type_int:
            value = CVariableFactory::castedBuild<CVariableInt *>(m_automate, this, e_type_int, e_type_organ_none, ivar->toInt());
            break;

        case e_type_bool:
            value = CVariableFactory::castedBuild<CVariableBool *>(m_automate, this, e_type_bool, e_type_organ_none, ivar->toBool());
            break;

        case e_type_string:
            value = CVariableFactory::castedBuild<CVariableString *>(m_automate, this, e_type_string, e_type_organ_none, ivar->toString());
            break;

        default:
            Q_ASSERT(false);
            return;
    }
    setVariableAccess(value, e_access_read_write);
    value->setName(QStringLiteral("value"));
    value->setLabel(tr("Value"));

    const QString unitName = ivar->getUnit() ? ivar->getUnit()->getName() : QString();
    CVariableMutable *unit = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, unitName);
    setVariableAccess(unit, e_access_read_write);
    unit->setName(QStringLiteral("unit"));
    unit->setLabel(tr("Unit"));
    unit->setMutableType(CVariableMutable::Unit);

    switch (ivar->getOrganType()) {
        case e_type_organ_input: {
            IVariableInput *iivar = dynamic_cast<IVariableInput *>(ivar);
            Q_ASSERT(iivar);
            const IOrgan * iorgan = iivar->getOrgan();
            const QString organName = iorgan ? iorgan->getName() : QString();
            organ = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, organName);
            break;
        }

        case e_type_organ_output: {
            IVariableOutput *oivar = dynamic_cast<IVariableOutput *>(ivar);
            Q_ASSERT(oivar);
            const IOrgan * iorgan = oivar->getOrgan();
            const QString organName = iorgan ? iorgan->getName() : QString();
            organ = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, organName);
            break;
        }

        default:
            break;
    }
    if (organ) {
        setVariableAccess(organ, e_access_read_write);
        organ->setName(QStringLiteral("organ"));
        organ->setLabel(tr("Organ"));
        organ->setMutableType(CVariableMutable::Organ);
    }

    CVariableStream *stream = m_automate->getVariableStream(ivar);
    CVariableMeasure *measure = m_automate->getVariableMeasure(ivar);
    const QString streamOrMeasureName = stream ? stream->getName() : (measure ? measure->getName() : QString());
    CVariableMutable *streamOrMeasure = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, streamOrMeasureName);
    setVariableAccess(streamOrMeasure, e_access_read_write);
    streamOrMeasure->setName(QStringLiteral("streamOrMeasure"));
    streamOrMeasure->setLabel(tr("Stream / Measure"));
    streamOrMeasure->setMutableType(CVariableMutable::StreamOrMeasure);

    ivars << label << type << subType << value << unit;

    if (organ) {
        ivars << organ;
    }

    ivars << streamOrMeasure;

    setVariables(ivars);
}

// CVariableIActionDescriber

CVariableIActionDescriber::CVariableIActionDescriber(CAutomate* arg_automate, IVariableUIHandler *parent)
    : IVariableObjectDescriber(arg_automate, parent)
{
}

void CVariableIActionDescriber::describe(const QVariant &object)
{
    IAction *action = object.value<IAction *>();
    Q_ASSERT(action);

    clear();
    IVariablePtrList ivars;

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(m_automate, this, e_type_string, e_type_organ_none, action->getLabel());
    label->setName("label");
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, action->getType());
    setVariableAccess(type, e_access_read);
    type->setName("type");
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::ActionType);

    ivars << label << type;

    // handle properties
    const QMap<QString, IVariable *> properties = action->getMapIVariableParameters();
    const QMap<QString, IVariable *>::ConstIterator propertiesEnd = properties.constEnd();
    QMap<QString, IVariable *>::ConstIterator propertiesIt = properties.constBegin();
    for(; propertiesIt != propertiesEnd; ++propertiesIt) {
        IVariable *ivar = propertiesIt.value();
        // We stock current value in ivar value and current variable name in ivar label
        IVariable *property = CVariableFactory::castedBuild<IVariable *>(m_automate, this, propertiesIt.value()->getType(), e_type_organ_none, ivar ? ivar->toVariant() : QVariant());
        setVariableAccess(property, e_access_read_write);
        property->setName(QString("property_%1").arg(propertiesIt.key()));
        property->setLabel(ivar ? ivar->getName() : QString());
        ivars << property;
    }

    // handle constants
    const QMap<QString, IVariable *> constants = action->getMapCstParameters();
    const QMap<QString, IVariable *>::ConstIterator constantsEnd = constants.constEnd();
    QMap<QString, IVariable *>::ConstIterator constantsIt = constants.constBegin();
    for(; constantsIt != constantsEnd; ++constantsIt) {
        IVariable *ivar = constantsIt.value();
        // We stock current value in ivar value and current variable name in ivar label
        IVariable *constant = CVariableFactory::castedBuild<IVariable *>(m_automate, this, constantsIt.value()->getType(), e_type_organ_none, ivar ? ivar->toVariant() : QVariant());
        setVariableAccess(constant, e_access_read_write);
        constant->setName(QString("constant_%1").arg(constantsIt.key()));
        constant->setLabel(ivar ? ivar->getName() : QString());
        ivars << constant;
    }

    setVariables(ivars);
}

// CVariableCStepDescriber

CVariableCStepDescriber::CVariableCStepDescriber(CAutomate* arg_automate,IVariableUIHandler *parent)
    : IVariableObjectDescriber(arg_automate, parent)
{
}

void CVariableCStepDescriber::describe(const QVariant &object)
{
    CStep *step = object.value<CStep *>();
    Q_ASSERT(step);

    clear();
    CVariableFloat *interval = CVariableFactory::castedBuild<CVariableFloat *>(m_automate, this, e_type_float, e_type_organ_none, step->getNumStep());
    setVariableAccess(interval, step->getNumStep() < 0 ? e_access_read : e_access_read_write);
    interval->setName("interval");
    interval->setLabel(tr("Interval"));

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(m_automate, this, e_type_string, e_type_organ_none, step->getLabel());
    setVariableAccess(label, e_access_read_write);
    label->setName("label");
    label->setLabel(tr("Label"));

    setVariables(IVariablePtrList() << interval << label);
}

// CVariableIVariableOutBindsDescriber

CVariableIVariableOutBindsDescriber::CVariableIVariableOutBindsDescriber(CAutomate* arg_automate, IVariableUIHandler *parent)
    :  IVariableObjectDescriber(arg_automate, parent)
{

}

void CVariableIVariableOutBindsDescriber::describe(const QVariant &object)
{
    QList<IVariable *> bindings;
    QList<IVariable *> bindingsMapping;

    if (object.canConvert<IVariable *>()) {
        const IVariable *ivar = object.value<IVariable *>();
        Q_ASSERT(ivar);
        bindings = ivar->getListOutBinds();
    }
    else if (object.canConvert<QStringList>()) {

        const QStringList names = object.toStringList();
        bindings = m_automate->getVariables(names);
    }
    else {
        Q_ASSERT(false);
    }

    int i = 0;
    foreach (IVariable *ivar, bindings) {
        CVariableMutable *outBind = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this,  type_mutable, e_type_organ_none, ivar->getName());
        setVariableAccess(outBind, e_access_read_write);
        outBind->setName(QString("target_%1").arg(++i));
        outBind->setLabel(ivar->getLabel());
        outBind->setMutableType(CVariableMutable::Variable);
        bindingsMapping << outBind;
    }

    clear();

    setVariables(bindingsMapping);
}

// CVariableIVariableInBindsDescriber

CVariableIVariableInBindsDescriber::CVariableIVariableInBindsDescriber(CAutomate* arg_automate,IVariableUIHandler *parent)
    :  IVariableObjectDescriber(arg_automate,parent)
{

}

void CVariableIVariableInBindsDescriber::describe(const QVariant &object)
{
    QList<IVariable *> bindings;
    QList<IVariable *> bindingsMapping;

    if (object.canConvert<IVariable *>()) {
        const IVariable *ivar = object.value<IVariable *>();
        Q_ASSERT(ivar);
        bindings = ivar->getListInBinds();
    }
    else if (object.canConvert<QStringList>()) {

        const QStringList names = object.toStringList();
        bindings = m_automate->getVariables(names);
    }
    else {
        Q_ASSERT(false);
    }

    int i = 0;
    foreach (IVariable *ivar, bindings) {
        CVariableMutable *inBind = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, ivar->getName());
        setVariableAccess(inBind, e_access_read);
        inBind->setName(QString("source_%1").arg(++i));
        inBind->setLabel(ivar->getLabel());
        inBind->setMutableType(CVariableMutable::Variable);
        bindingsMapping << inBind;
    }

    clear();

    setVariables(bindingsMapping);
}

// CVariableCStepActionsDescriber

CVariableCStepActionsDescriber::CVariableCStepActionsDescriber(CAutomate* arg_automate,IVariableUIHandler *parent)
    : IVariableObjectDescriber(arg_automate,parent)
{
}

void CVariableCStepActionsDescriber::describe(const QVariant &object)
{
    QList<IAction *> actions;

    if (object.canConvert<CStep *>()) {
        CStep *step = object.value<CStep *>();
        Q_ASSERT(step);
        actions << step->getListActions();
    }
    else if (object.canConvert<QStringList>()) {

        QStringList names = object.toStringList();

        foreach (const QString &name, names) {
            IAction *action = m_automate->getAction(name);
            Q_ASSERT(action);
            actions << action;
        }
    }
    else {
        Q_ASSERT(false);
    }

    clear();

    IVariablePtrList ivars;

    foreach (IAction *action, actions) {
        CVariableMutable *ivar = CVariableFactory::castedBuild<CVariableMutable *>(m_automate, this, type_mutable, e_type_organ_none, action->getName());
        ivar->setName(CVariableFactory::buildTemporaryName(QStringLiteral("actionName")));
        ivar->setMutableType(CVariableMutable::Action);
        ivar->setLabel(action->getLabel());
        ivars << ivar;
    }

    setVariables(ivars);
}

QStringList CVariableCStepActionsDescriber::getActionList() const
{
    QStringList actions;

    foreach (IVariable *ivar, getVariables()) {
        actions << ivar->toString();
    }

    return actions;
}
