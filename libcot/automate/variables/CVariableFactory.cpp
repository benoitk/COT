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
#include "CVariableVoie.h"
#include "CVariableMeasure.h"
#include "CVariableOutputListVariables.h"
#include "CVariableMutable.h"

#include "qvariant.h"
#include "qdebug.h"

IVariable* CVariableFactory::build(const QMap<QString, QVariant> &mapVar){
	
    int address = 0;
    if(mapVar.contains(QStringLiteral("address")))
         address = mapVar[QStringLiteral("address")].toInt();

    variableAccess access = access_read;
    if(mapVar.contains(QStringLiteral("access"))){
        if(mapVar[QStringLiteral("access")].toString() == QStringLiteral("write")) access = access_write;
        if(mapVar[QStringLiteral("access")].toString() == QStringLiteral("read_write")) access = access_read_write;
    }

    const QString type = mapVar[QStringLiteral("type")].toString();
    IVariable *variable = build(type, mapVar);

    switch (variable->getType()) {
        case type_int: {
            CVariableInt * ivar = static_cast<CVariableInt *>(variable);
            ivar->setAddress(address);
            ivar->setAccess(access);
            break;
        }

        case type_float: {
            CVariableFloat * ivar = static_cast<CVariableFloat *>(variable);
            ivar->setAddress(address);
            ivar->setAccess(access);
            break;
        }

        case type_bool: {
            CVariableBool * ivar = static_cast<CVariableBool *>(variable);
            ivar->setAddress(address);
            ivar->setAccess(access);
            break;
        }

        default:
            break;
    }

    variable->setName(mapVar[QStringLiteral("name")].toString());
    variable->setLabel(mapVar[QStringLiteral("fr_FR")].toString());
    return variable;
}

IVariable *CVariableFactory::build(variableType type, VariableOrganType organType, const QVariant &data)
{
    switch (organType) {
        case VariableOrganTypeNone: {
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
                    return new CVariableVoie(data.toMap());

                case type_measure:
                    return new CVariableMeasure(data.toMap());

                case type_list_variables:
                    break;

                case type_unknow:
                    return new CVariableUnknow;

                case type_mutable:
                    return new CVariableMutable(data);
            }

            break;
        }

        case VariableOrganTypeInput: {
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

        case VariableOrganTypeOutput: {
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

                case type_unknow:
                    break;
            }

            break;
        }
    }

    return Q_NULLPTR;
}

IVariable* CVariableFactory::build(const QString &type, const QVariantMap &data){
    static QHash<QString, QPair<variableType, VariableOrganType>> types;

    if (types.isEmpty()) {
        types[QStringLiteral("boolean")] = qMakePair(type_bool, VariableOrganTypeNone);
        types[QStringLiteral("float")] = qMakePair(type_float, VariableOrganTypeNone);
        types[QStringLiteral("integer")] = qMakePair(type_int, VariableOrganTypeNone);
        types[QStringLiteral("string")] = qMakePair(type_string, VariableOrganTypeNone);
        types[QStringLiteral("stream")] = qMakePair(type_stream, VariableOrganTypeNone);
        types[QStringLiteral("measure")] = qMakePair(type_measure, VariableOrganTypeNone);
        //
        types[QStringLiteral("input_boolean")] = qMakePair(type_bool, VariableOrganTypeInput);
        types[QStringLiteral("input_float")] = qMakePair(type_float, VariableOrganTypeInput);
        types[QStringLiteral("input_integer")] = qMakePair(type_int, VariableOrganTypeInput);
        //
        types[QStringLiteral("output_boolean")] = qMakePair(type_bool, VariableOrganTypeOutput);
        types[QStringLiteral("output_float")] = qMakePair(type_float, VariableOrganTypeOutput);
        types[QStringLiteral("output_integer")] = qMakePair(type_int, VariableOrganTypeOutput);
        types[QStringLiteral("output_list_variables")] = qMakePair(type_list_variables, VariableOrganTypeOutput);
        //types[QStringLiteral("map_float_float")] = type_;
        //types[QStringLiteral("output_struct")] = type_;
        //types[QStringLiteral("")] = type_;
    }

    if (!types.contains(type)) {
        qDebug() << "Type variable INCONNU " << type;
    }

    const QPair<variableType, VariableOrganType> pair = types.value(type, qMakePair(type_unknow, VariableOrganTypeNone));
    return CVariableFactory::build(pair.first, pair.second, data.contains(QStringLiteral("value"))
                                   ? data.value(QStringLiteral("value"))
                                   : data );
}


IVariablePtr CVariableFactory::buildTemporary(const QString& name, variableType type) {
    IVariable *ivar = CVariableFactory::build(type);
    ivar->setName(name);
    ivar->setLabel(name);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporary(const QString& name, const QString &label, variableType type) {
    IVariable *ivar = CVariableFactory::build(type);
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporary(const QString& name, const QString &label, const QVariant &value, variableType type) {
    IVariable *ivar = CVariableFactory::build(type);
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    ivar->setValue(value);
    return ivar;
}

IVariablePtrList CVariableFactory::buildTemporary(const QStringList& names, variableType type) {
    IVariablePtrList ivars;

    foreach (const QString& name, names) {
        ivars << buildTemporary(name, type);
    }

    return ivars;
}

void CVariableFactory::deleteVariables(IVariablePtrList &ivars)
{
    qDeleteAll(ivars);
    ivars.clear();
}

void CVariableFactory::deleteVariables(QHash<QString, IVariablePtr> &ivars)
{
    qDeleteAll(ivars.values());
    ivars.clear();
}

void CVariableFactory::deleteVariables(QMap<QString, IVariablePtr> &ivars)
{
    qDeleteAll(ivars.values());
    ivars.clear();
}
