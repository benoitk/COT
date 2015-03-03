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

IVariable* CVariableFactory::build(QMap<QString, QVariant> mapVar){
	
	IVariable* variable = NULL;
	if(mapVar["type"].toString() == "integer"){
		variable = new CVariableInt(mapVar["value"].toInt());
	}
	else if(mapVar["type"].toString() == "float"){
		variable = new CVariableFloat(mapVar["value"].toFloat());
	}
	else if(mapVar["type"].toString() == "boolean"){
		variable = new CVariableBool(mapVar["value"].toBool());
	}
	else if(mapVar["type"].toString() == "string"){
		variable = new CVariableString(mapVar["value"].toString());
	}
	else if(mapVar["type"].toString() == "input_float"){
		variable = new CVariableInputFloat(mapVar);
	}
	else{
		variable = new CVariableUnknow();
		qDebug() << "Type variable INCONNU " << mapVar["type"].toString() ;

	}
	variable->setLabel(mapVar[tr("FR_lbl")].toString());
	return variable;
}

IVariable* CVariableFactory::build(QString arg_type){
	
	IVariable* variable = NULL;

	
	if(arg_type == "integer"){
		variable = new CVariableInt(0);
	}
	else if(arg_type == "float"){
		variable = new CVariableFloat(0.0);
	}
	else if(arg_type == "boolean"){
		variable = new CVariableBool(false);
	}
	else if(arg_type == "string"){
		variable = new CVariableString("");
	}else 
	{
		qDebug() << "Type variable INCONNU " << arg_type;
		variable = new CVariableUnknow();
	}
	
	
	return variable;
}
