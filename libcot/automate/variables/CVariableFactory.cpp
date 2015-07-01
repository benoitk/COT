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
#include "cotautomate_debug.h"

#include <QVariant>
#include <QDateTime>

IVariable* CVariableFactory::build(const QVariantMap &mapVar){

    QString type = mapVar.value(QStringLiteral("type")).toString();
    IVariable *variable = Q_NULLPTR;

    if(type == QStringLiteral("boolean")){
        variable = new CVariableBool(mapVar);
    }else if(type == QStringLiteral("integer")){
        variable = new CVariableInt(mapVar);
    }else if(type == QStringLiteral("float")){
        variable = new CVariableFloat(mapVar);
    }else if(type == QStringLiteral("stream")){
        variable = new CVariableStream(mapVar);
    }else if(type == QStringLiteral("measure")){
        variable = new CVariableMeasure(mapVar);
    }else if(type == QStringLiteral("string")){
        variable = new CVariableString(mapVar);
    }else if(type == QStringLiteral("input_boolean")){
        variable = new CVariableInputBool(mapVar);
    }else if(type == QStringLiteral("input_integer")){
        variable = new CVariableInputInt(mapVar);
    }else if(type == QStringLiteral("input_float")){
        variable = new CVariableInputFloat(mapVar);
    }else if(type == QStringLiteral("output_boolean")){
        variable = new CVariableOutputBool(mapVar);
    }else if(type == QStringLiteral("output_integer")){
        variable = new CVariableOutputInt(mapVar);
    }else if(type == QStringLiteral("output_float")){
        variable = new CVariableOutputFloat(mapVar);
    }else if(type == QStringLiteral("output_list_variables")){
        variable = new CVariableUnknow();
    }else{
        variable = new CVariableUnknow();
    }
    return variable;
}

IVariable *CVariableFactory::build(variableType type, VariableOrganType organType, const QVariant &data)
{
    switch (organType) {
        case type_organ_none: {
            switch (type) {
            case type_bool:
                return new CVariableBool(data.toBool());

            case type_float:
                return new CVariableFloat(data.toFloat());

            case type_int:
                return new CVariableInt(data.toInt());

            case type_string:
                return new CVariableString(data.toString());

            case type_stream:
                return new CVariableStream(data.toMap());

            case type_measure:
                return new CVariableMeasure(data.toMap());

            case type_list_variables:
                break;

            case type_mutable:
                return new CVariableMutable(data);
                break;
                //case type_unknow:
                //       return new CVariableUnknow;
                //break;

            }

            break;
        }

        case type_organ_input: {
            switch (type) {
            case type_bool:
                return new CVariableInputBool(data.toMap());

            case type_float:
                return new CVariableInputFloat(data.toMap());

            case type_int:
                return new CVariableInputInt(data.toMap());

            case type_string:
            case type_stream:
            case type_measure:
            case type_list_variables:
            case type_unknow:
                break;
            }

            break;
        }

        case type_organ_output: {
            switch (type) {
            case type_bool:
                return new CVariableOutputBool(data.toMap());

            case type_float:
                return new CVariableOutputFloat(data.toMap());

            case type_int:
                return new CVariableOutputInt(data.toMap());

            case type_string:
            case type_stream:
            case type_measure:
                break;

            case type_list_variables:
                return new CVariableOutputListVariables(data.toMap());

//            case type_unknow:
//                break;
            }

            break;
        }
    }

//    return Q_NULLPTR;
    return new CVariableUnknow;
}

IVariable* CVariableFactory::build(const QString &type, const QVariantMap &data){
    static QHash<QString, QPair<variableType, VariableOrganType>> types;

    if (types.isEmpty()) {
        types[QStringLiteral("boolean")] = qMakePair(type_bool, type_organ_none);
        types[QStringLiteral("float")] = qMakePair(type_float, type_organ_none);
        types[QStringLiteral("integer")] = qMakePair(type_int, type_organ_none);
        types[QStringLiteral("string")] = qMakePair(type_string, type_organ_none);
        types[QStringLiteral("stream")] = qMakePair(type_stream, type_organ_none);
        types[QStringLiteral("measure")] = qMakePair(type_measure, type_organ_none);
        //
        types[QStringLiteral("input_boolean")] = qMakePair(type_bool, type_organ_input);
        types[QStringLiteral("input_float")] = qMakePair(type_float, type_organ_input);
        types[QStringLiteral("input_integer")] = qMakePair(type_int, type_organ_input);
        //
        types[QStringLiteral("output_boolean")] = qMakePair(type_bool, type_organ_output);
        types[QStringLiteral("output_float")] = qMakePair(type_float, type_organ_output);
        types[QStringLiteral("output_integer")] = qMakePair(type_int, type_organ_output);
        types[QStringLiteral("output_list_variables")] = qMakePair(type_list_variables, type_organ_output);
        //types[QStringLiteral("map_float_float")] = type_;
        //types[QStringLiteral("output_struct")] = type_;
        //types[QStringLiteral("")] = type_;
    }

    if (!types.contains(type)) {
        qCDebug(COTAUTOMATE_LOG) << "Type variable INCONNU " << type;
    }

    const QPair<variableType, VariableOrganType> pair = types.value(type, qMakePair(type_unknow, type_organ_none));
    if(data.contains(QStringLiteral("value")) && pair.second == type_organ_none){
        return CVariableFactory::build(pair.first, pair.second, data.value(QStringLiteral("value")));
    }
    else
        return CVariableFactory::build(pair.first, pair.second, data);

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

IVariablePtr CVariableFactory::buildTemporary(const QString& name, variableType type, VariableOrganType organType) {
    IVariable *ivar = CVariableFactory::build(type, organType);
    ivar->setName(name);
    ivar->setLabel(name);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporary(const QString& name, const QString &label, variableType type, VariableOrganType organType) {
    IVariable *ivar = CVariableFactory::build(type, organType);
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporary(const QString& name, const QString &label, const QVariant &value, variableType type, VariableOrganType organType) {
    IVariable *ivar = CVariableFactory::build(type, organType);
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    ivar->setValue(value);
    return ivar;
}

IVariablePtrList CVariableFactory::buildTemporary(const QStringList& names, variableType type, VariableOrganType organType) {
    IVariablePtrList ivars;

    foreach (const QString& name, names) {
        ivars << buildTemporary(name, type, organType);
    }

    return ivars;
}

IVariablePtr CVariableFactory::duplicateTemporary(IVariablePtr variable)
{
    IVariable *ivar = CVariableFactory::buildTemporary(variable->getName(), variable->getLabel(), variable->toVariant(),
                                                       variable->getType(), variable->getOrganType());
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
