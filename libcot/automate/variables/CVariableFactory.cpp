#include "CVariableFactory.h"
#include "CVariableInt.h"
#include "CVariableBool.h"
#include "CVariableFloat.h"
#include "CVariableString.h"
#include "CVariableUnknow.h"
#include "CVariableInputFloat.h"
#include "CVariableInputBool.h"
#include "CVariableInputInt.h"
#include "CVariableOutputBool.h"
#include "CVariableOutputFloat.h"
#include "CVariableOutputInt.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"
#include "CVariableOutputListVariables.h"
#include "CVariableMutable.h"
#include "CVariableAlarm.h"
#include "CVariableCurve.h"
#include "cotautomate_debug.h"

#include <QVariant>
#include <QDateTime>

IVariable* CVariableFactory::build(CAutomate* arg_automate, QObject* parent, const QVariantMap &mapVar){

    QString type = mapVar.value(QStringLiteral("type")).toString();
    IVariable *variable = Q_NULLPTR;

    if(type == QStringLiteral("boolean")){
        variable = new CVariableBool(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("integer")){
        variable = new CVariableInt(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("float")){
        variable = new CVariableFloat(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("stream")){
        variable = new CVariableStream(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("measure")){
        variable = new CVariableMeasure(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("string")){
        variable = new CVariableString(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("input_boolean")){
        variable = new CVariableInputBool(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("input_integer")){
        variable = new CVariableInputInt(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("input_float")){
        variable = new CVariableInputFloat(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("output_boolean")){
        variable = new CVariableOutputBool(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("output_integer")){
        variable = new CVariableOutputInt(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("output_float")){
        variable = new CVariableOutputFloat(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("alarm")){
        variable = new CVariableAlarm(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("curve")){
        variable = new CVariableCurve(mapVar, arg_automate, parent);
    }else if(type == QStringLiteral("output_list_variables")){
        variable = new CVariableUnknow(mapVar, arg_automate, parent);
    }else{
        variable = new CVariableUnknow(mapVar, arg_automate, parent);
    }
    return variable;
}

//var alarm non traité dans les fonctions suivantes :

IVariable *CVariableFactory::build(CAutomate* arg_automate, QObject *parent,enumVariableType type, enumVariableOrganType organType, const QVariant &data)
{
    switch (organType) {
        case e_type_organ_none: {
            switch (type) {
            case e_type_bool:
                return new CVariableBool(arg_automate, parent, data.toBool());

            case e_type_float:
                return new CVariableFloat(arg_automate, parent, data.toFloat());

            case e_type_int:
                return new CVariableInt(arg_automate, parent, data.toInt());

            case e_type_string:
                return new CVariableString(data.toString(), arg_automate, parent);

            case e_type_stream:
                return new CVariableStream(data.toMap(), arg_automate, parent);

            case e_type_measure:
                return new CVariableMeasure(data.toMap(), arg_automate, parent);

            case e_type_list_variables:
                break;

            case type_mutable:
                return new CVariableMutable(data, arg_automate, parent);
                break;
                //case type_unknow:
                //       return new CVariableUnknow;
                //break;

            }

            break;
        }

        case e_type_organ_input: {
            switch (type) {
            case e_type_bool:
                return new CVariableInputBool(data.toMap(), arg_automate, parent);

            case e_type_float:
                return new CVariableInputFloat(data.toMap(), arg_automate, parent);

            case e_type_int:
                return new CVariableInputInt(data.toMap(), arg_automate, parent);

            case e_type_string:
            case e_type_stream:
            case e_type_measure:
            case e_type_list_variables:
            case e_type_unknow:
                break;
            }

            break;
        }

        case e_type_organ_output: {
            switch (type) {
            case e_type_bool:
                return new CVariableOutputBool(data.toMap(), arg_automate, parent);

            case e_type_float:
                return new CVariableOutputFloat(data.toMap(), arg_automate, parent);

            case e_type_int:
                return new CVariableOutputInt(data.toMap(), arg_automate, parent);

            case e_type_string:
            case e_type_stream:
            case e_type_measure:
                break;

            case e_type_list_variables:
                return new CVariableOutputListVariables(data.toMap(), arg_automate, parent);

//            case type_unknow:
//                break;
            }

            break;
        }
    }

//    return Q_NULLPTR;
    return new CVariableUnknow(arg_automate, parent);
}

IVariable* CVariableFactory::build(CAutomate* arg_automate, QObject* parent, const QString &type, const QVariantMap &data){
    static QHash<QString, QPair<enumVariableType, enumVariableOrganType>> types;

    if (types.isEmpty()) {
        types[QStringLiteral("boolean")] = qMakePair(e_type_bool, e_type_organ_none);
        types[QStringLiteral("float")] = qMakePair(e_type_float, e_type_organ_none);
        types[QStringLiteral("integer")] = qMakePair(e_type_int, e_type_organ_none);
        types[QStringLiteral("string")] = qMakePair(e_type_string, e_type_organ_none);
        types[QStringLiteral("stream")] = qMakePair(e_type_stream, e_type_organ_none);
        types[QStringLiteral("measure")] = qMakePair(e_type_measure, e_type_organ_none);
        //
        types[QStringLiteral("input_boolean")] = qMakePair(e_type_bool, e_type_organ_input);
        types[QStringLiteral("input_float")] = qMakePair(e_type_float, e_type_organ_input);
        types[QStringLiteral("input_integer")] = qMakePair(e_type_int, e_type_organ_input);
        //
        types[QStringLiteral("output_boolean")] = qMakePair(e_type_bool, e_type_organ_output);
        types[QStringLiteral("output_float")] = qMakePair(e_type_float, e_type_organ_output);
        types[QStringLiteral("output_integer")] = qMakePair(e_type_int, e_type_organ_output);
        types[QStringLiteral("output_list_variables")] = qMakePair(e_type_list_variables, e_type_organ_output);
        //types[QStringLiteral("map_float_float")] = type_;
        //types[QStringLiteral("output_struct")] = type_;
        //types[QStringLiteral("")] = type_;
    }

    if (!types.contains(type)) {
        qCDebug(COTAUTOMATE_LOG) << "Type variable INCONNU " << type;
    }

    const QPair<enumVariableType, enumVariableOrganType> pair = types.value(type, qMakePair(e_type_unknow, e_type_organ_none));
    if(data.contains(QStringLiteral("value")) && pair.second == e_type_organ_none){
        return CVariableFactory::build(arg_automate, parent, pair.first, pair.second, data.value(QStringLiteral("value")));
    }
    else
        return CVariableFactory::build(arg_automate, parent, pair.first, pair.second, data);

//    return CVariableFactory::build(pair.first, pair.second, data.contains(QStringLiteral("value"))
//                                   ? data.value(QStringLiteral("value"))
//                                   : data );
}

QString CVariableFactory::buildTemporaryName(const QString &baseName)
{
    static int count = 0;
    return QStringLiteral("%1_%2_%3")
            .arg(baseName)
            .arg(QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_HHmm")))
            .arg(count++);
}

IVariablePtr CVariableFactory::buildTemporary(CAutomate* arg_automate, QObject *parent, const QString& name, enumVariableType type, enumVariableOrganType organType) {
    IVariable *ivar = CVariableFactory::build(arg_automate, parent, type, organType);
    ivar->setName(name);
    ivar->setLabel(name);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporary(CAutomate* arg_automate, QObject *parent, const QString& name, const QString &label, enumVariableType type, enumVariableOrganType organType) {
    IVariable *ivar = CVariableFactory::build(arg_automate, parent, type, organType);
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporary(CAutomate* arg_automate, QObject *parent, const QString& name, const QString &label, const QVariant &value, enumVariableType type, enumVariableOrganType organType) {
    IVariable *ivar = CVariableFactory::build(arg_automate, parent, type, organType);
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    ivar->setValue(value);
    return ivar;
}

IVariablePtrList CVariableFactory::buildTemporary(CAutomate* arg_automate, QObject *parent, const QStringList& names, enumVariableType type, enumVariableOrganType organType) {
    IVariablePtrList ivars;

    foreach (const QString& name, names) {
        ivars << buildTemporary(arg_automate, parent, name, type, organType);
    }

    return ivars;
}

IVariablePtr CVariableFactory::duplicateTemporary(CAutomate* arg_automate, QObject *parent, IVariablePtr variable)
{
    IVariable *ivar = CVariableFactory::buildTemporary(arg_automate, parent, variable->getName(), variable->getLabel(), variable->toVariant(),
                                                       variable->getType(), e_type_organ_none);
    ivar->setAccess(variable->getAccess());
    return ivar;
}

void CVariableFactory::deleteVariables(IVariablePtrList &ivars)
{
    qDeleteAll(ivars);
    ivars.clear();
}

void CVariableFactory::deleteVariables(QHash<QString, IVariablePtr> &ivars)
{
    qDeleteAll(ivars);
    ivars.clear();
}

void CVariableFactory::deleteVariables(QMap<QString, IVariablePtr> &ivars)
{
    qDeleteAll(ivars);
    ivars.clear();
}
