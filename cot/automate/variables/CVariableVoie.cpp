#include "CVariableVoie.h"
#include "CUnit.h"

CVariableVoie::CVariableVoie(QObject *parent):QObject(parent)
{	
}
CVariableVoie::CVariableVoie(QObject * parent, int iNumVoie):QObject(parent){
	m_iNumVoie = iNumVoie;	 
}

CVariableVoie::~CVariableVoie()
{
}


QString CVariableVoie::toString(){
	return QString::number(m_iNumVoie);
}
int CVariableVoie::toInt(){
	return m_iNumVoie;
}
float CVariableVoie::toFloat(){
	return m_iNumVoie;
}
bool CVariableVoie::toBool(){
	return false;
}
QString CVariableVoie::getLabel()const{
	return m_label;
}
void CVariableVoie::setLabel(QString label){
	m_label = label;
}

void CVariableVoie::setValue(int iValue){
	m_iNumVoie = iValue;
}
void CVariableVoie::setValue(QVariant value){
	m_iNumVoie = value.toInt();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableVoie::setToBindedValue(QVariant value){
	
}
variableType CVariableVoie::getType()const{
	return variableType::type_stream;
}
void CVariableVoie::switchToUnit(CUnit* targetUnit){

}
