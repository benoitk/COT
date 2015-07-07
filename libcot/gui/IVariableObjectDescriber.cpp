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

    CVariableStream * cycleStream = CAutomate::getInstance()->getCycleStream(cycle);
    QString streamName = cycleStream ? cycleStream->getName() : QString();


    clear();

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, type_organ_none, cycle->getLabel());
    label->setName("label");
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, cycle->getType());
    setVariableAccess(type, access_read);
    type->setName("type");
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::CycleType);

    CVariableInt *timer = CVariableFactory::castedBuild<CVariableInt *>(type_int, type_organ_none, /*cycle->get()*/ -1); // SERES_TODO: Add api
    setVariableAccess(timer, access_read_write);
    timer->setName("timer");
    timer->setLabel(tr("Timer"));

    CVariableMutable *stream = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, streamName);
    setVariableAccess(stream, access_read_write);
    stream->setName("stream");
    stream->setLabel(tr("Stream"));
    stream->setMutableType(CVariableMutable::Stream);

    setVariables(IVariablePtrList() << label << type << timer << stream);
}


CVariableIVariableDescriber::CVariableIVariableDescriber(IVariableUIHandler *parent)
    : IVariableObjectDescriber(parent)
{
}

void CVariableIVariableDescriber::describe(const QVariant &object)
{
    const CAutomate *automate = CAutomate::getInstance();
    IVariable *ivar = object.value<IVariable *>();
    Q_ASSERT(ivar);
    clear();

    IVariablePtrList ivars;
    CVariableMutable *organ = Q_NULLPTR;
    IVariable *value = Q_NULLPTR;

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, type_organ_none, ivar->getLabel());
    label->setName(QStringLiteral("label"));
    label->setLabel(tr("Label"));

    CVariableMutable *type = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, ivar->getType());
    setVariableAccess(type, access_read);
    type->setName(QStringLiteral("type"));
    type->setLabel(tr("Type"));
    type->setMutableType(CVariableMutable::VariableType);

    switch (ivar->getType()) {
        case type_float:
            value = CVariableFactory::castedBuild<CVariableFloat *>(type_float, type_organ_none, ivar->toFloat());
            break;

        case type_int:
            value = CVariableFactory::castedBuild<CVariableInt *>(type_int, type_organ_none, ivar->toInt());
            break;

        case type_bool:
            value = CVariableFactory::castedBuild<CVariableBool *>(type_bool, type_organ_none, ivar->toBool());
            break;

        case type_string:
            value = CVariableFactory::castedBuild<CVariableString *>(type_string, type_organ_none, ivar->toString());
            break;

        default:
            Q_ASSERT(false);
            return;
    }
    setVariableAccess(value, access_read_write);
    value->setName(QStringLiteral("value"));
    value->setLabel(tr("Value"));

    const QString unitName = ivar->getUnit() ? ivar->getUnit()->getName() : QString();
    CVariableMutable *unit = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, unitName);
    setVariableAccess(unit, access_read_write);
    unit->setName(QStringLiteral("unit"));
    unit->setLabel(tr("Unit"));
    unit->setMutableType(CVariableMutable::Unit);

    switch (ivar->getOrganType()) {
        case type_organ_input: {
            IVariableInput *iivar = dynamic_cast<IVariableInput *>(ivar);
            Q_ASSERT(iivar);
            const IOrgan * iorgan = iivar->getOrgan();
            const QString organName = iorgan ? iorgan->getName() : QString();
            organ = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, organName);
            break;
        }

        case type_organ_output: {
            IVariableOutput *oivar = dynamic_cast<IVariableOutput *>(ivar);
            Q_ASSERT(oivar);
            const IOrgan * iorgan = oivar->getOrgan();
            const QString organName = iorgan ? iorgan->getName() : QString();
            organ = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, organName);
            break;
        }

        default:
            break;
    }
    if (organ) {
        setVariableAccess(organ, access_read_write);
        organ->setName(QStringLiteral("organ"));
        organ->setLabel(tr("Organ"));
        organ->setMutableType(CVariableMutable::Organ);
    }

    CVariableStream *stream = automate->getVariableStream(ivar);
    CVariableMeasure *measure = Q_NULLPTR; // SERES_TODO automate->getVariableMeasure(ivar);
    const QString streamOrMeasureName = stream ? stream->getName() : (measure ? measure->getName() : QString());
    CVariableMutable *streamOrMeasure = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, streamOrMeasureName);
    setVariableAccess(streamOrMeasure, access_read_write);
    streamOrMeasure->setName(QStringLiteral("streamOrMeasure"));
    streamOrMeasure->setLabel(tr("Stream / Measure"));
    streamOrMeasure->setMutableType(CVariableMutable::StreamOrMeasure);

    ivars << label << type << value << unit;

    if (organ) {
        ivars << organ;
    }

    ivars << streamOrMeasure;

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
    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, type_organ_none, action->getLabel());
    label->setName("label");
    label->setLabel(tr("Label"));
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

    CVariableFloat *interval = CVariableFactory::castedBuild<CVariableFloat *>(type_float, type_organ_none, step->getNumStep());
    setVariableAccess(interval, step->getNumStep() < 0 ? access_read : access_read_write);
    interval->setName("interval");
    interval->setLabel(tr("Interval"));

    CVariableString *label = CVariableFactory::castedBuild<CVariableString *>(type_string, type_organ_none, step->getLabel());
    setVariableAccess(label, access_read_write);
    label->setName("label");
    label->setLabel(tr("Label"));

    setVariables(IVariablePtrList() << interval << label);
}


CVariableIVariableOutBindsDescriber::CVariableIVariableOutBindsDescriber(IVariableUIHandler *parent)
    :  IVariableObjectDescriber(parent)
{

}

void CVariableIVariableOutBindsDescriber::describe(const QVariant &object)
{
    IVariable *var = object.value<IVariable *>();
    Q_ASSERT(var);

    clear();
    IVariablePtrList lst;
    const QList<IVariable *> listOutBind = var->getListOutBinds();
    foreach(IVariable *var, listOutBind) {
        CVariableMutable *outBind = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, var->getLabel());
        outBind->setName(QStringLiteral("target"));
        outBind->setLabel(tr("Target"));
        outBind->setMutableType(CVariableMutable::Variable);
        lst << outBind;
    }
    setVariables(lst);
}


CVariableCStepActionsDescriber::CVariableCStepActionsDescriber(IVariableUIHandler *parent)
    : IVariableObjectDescriber(parent)
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
        CAutomate *automate = CAutomate::getInstance();
        QStringList names = object.toStringList();

        foreach (const QString &name, names) {
            IAction *action = automate->getAction(name);
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
        CVariableMutable *ivar = CVariableFactory::castedBuild<CVariableMutable *>(type_mutable, type_organ_none, action->getName());
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
