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

#include "qvariant.h"
#include "qdebug.h"

IVariable* CVariableFactory::build(const QMap<QString, QVariant> &mapVar){
	
	IVariable* variable = NULL;
    int address = 0;
    if(mapVar.contains(QStringLiteral("address")))
         address = mapVar[QStringLiteral("address")].toInt();

    variableAccess access = read;
    if(mapVar.contains(QStringLiteral("access"))){
        if(mapVar[QStringLiteral("access")].toString() == QStringLiteral("write")) access = write;
        if(mapVar[QStringLiteral("access")].toString() == QStringLiteral("read_write")) access = read_write;
    }

    if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("integer")){
        variable = new CVariableInt(mapVar[QStringLiteral("value")].toInt(), address, access);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("float")){
        variable = new CVariableFloat(mapVar[QStringLiteral("value")].toFloat(), address, access);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("boolean")){
        variable = new CVariableBool(mapVar[QStringLiteral("value")].toBool(), address, access);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("string")){
        variable = new CVariableString(mapVar[QStringLiteral("value")].toString());
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("input_float")){
		variable = new CVariableInputFloat(mapVar);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("output_float")){
		variable = new CVariableOutputFloat(mapVar);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("output_boolean")){
        variable = new CVariableOutputBool(mapVar);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("stream")){
        variable = new CVariableVoie(mapVar);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("measure")){
        variable = new CVariableMeasure(mapVar);
	}
    /*else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("map_float_float")){
		variable = new CVariableInputFloat(mapVar);
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("output_struct")){
		variable = new CVariableInputFloat(mapVar);
	}*/
	else{
		variable = new CVariableUnknow();
        qDebug() << "Type variable INCONNU " << mapVar[QStringLiteral("type")].toString() ;
	}
    variable->setName(mapVar[QStringLiteral("name")].toString());
    variable->setLabel(mapVar[QStringLiteral("fr_FR")].toString());
	return variable;
}

IVariable* CVariableFactory::build(const QString &arg_type){
	
	IVariable* variable = NULL;

	
    if(arg_type == QStringLiteral("integer")){
		variable = new CVariableInt(0);
	}
    else if(arg_type == QStringLiteral("float")){
		variable = new CVariableFloat(0.0);
	}
    else if(arg_type == QStringLiteral("boolean")){
		variable = new CVariableBool(false);
	}
    else if(arg_type == QStringLiteral("string")){
        variable = new CVariableString(QStringLiteral(""));
	}else 
	{
		qDebug() << "Type variable INCONNU " << arg_type;
		variable = new CVariableUnknow();
	}
	
	
	return variable;
}


IVariablePtr CVariableFactory::buildTemporaryString(const QString& name) {
    IVariable *ivar = new CVariableString;
    ivar->setName(name);
    ivar->setLabel(name);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporaryString(const QString& name, const QString &label) {
    IVariable *ivar = new CVariableString;
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    return ivar;
}

IVariablePtr CVariableFactory::buildTemporaryString(const QString& name, const QString &label, const QVariant &value) {
    IVariable *ivar = new CVariableString;
    ivar->setName(name);
    ivar->setLabel(label.isEmpty() ? name : label);
    ivar->setValue(value);
    return ivar;
}

IVariablePtrList CVariableFactory::buildTemporaryString(const QStringList& names) {
    IVariablePtrList ivars;

    foreach (const QString& name, names) {
        ivars << buildTemporaryString(name);
    }

    return ivars;
}

void CVariableFactory::deleteTemporaryStringList(IVariablePtrList &ivars)
{
    qDeleteAll(ivars);
    ivars.clear();
}

