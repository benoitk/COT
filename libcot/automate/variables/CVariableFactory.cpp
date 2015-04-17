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


#include "qvariant.h"
#include "qdebug.h"

IVariable* CVariableFactory::build(const QMap<QString, QVariant> &mapVar){
	
	IVariable* variable = NULL;
    if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("integer")){
        variable = new CVariableInt(mapVar[QStringLiteral("value")].toInt());
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("float")){
        variable = new CVariableFloat(mapVar[QStringLiteral("value")].toFloat());
	}
    else if(mapVar[QStringLiteral("type")].toString() == QStringLiteral("boolean")){
        variable = new CVariableBool(mapVar[QStringLiteral("value")].toBool());
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
	variable->setLabel(mapVar[tr("FR_lbl")].toString());
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
