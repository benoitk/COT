#include "CVariableUnknow.h"
#include "CUnit.h"

CVariableUnknow::CVariableUnknow()
	: QObject()
{

}

CVariableUnknow::~CVariableUnknow()
{

}


QString CVariableUnknow::toString(){
	return tr("Variable inconnu");
}
int CVariableUnknow::toInt(){
	return 0;
}
float CVariableUnknow::toFloat(){
	return 0;
}
bool CVariableUnknow::toBool(){
	return false;
}
void CVariableUnknow::setValue(QVariant){
}
QString CVariableUnknow::getLabel()const{
	return tr("Variable inconnu");
}
void CVariableUnknow::setLabel(QString){
}
void CVariableUnknow::addBind(IVariable* arg_var){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableUnknow::setToBindedValue(QVariant value){
}
variableType CVariableUnknow::getType()const{
    return type_unknow;
}
void CVariableUnknow::switchToUnit(CUnit* targetUnit){
	
}
