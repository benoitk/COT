#include "CVariableUnknow.h"

CVariableUnknow::CVariableUnknow()
	: IVariable()
{

}

CVariableUnknow::~CVariableUnknow()
{

}


QString CVariableUnknow::toString()const{
	return tr("Variable inconnu");
}
int CVariableUnknow::toInt()const{
	return 0;
}
float CVariableUnknow::toFloat()const{
	return 0;
}
void CVariableUnknow::setValue(QVariant){
}
QString CVariableUnknow::getLabel()const{
	return tr("Variable inconnu");
}
void CVariableUnknow::setLabel(QString){
}