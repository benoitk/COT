#include "CVariableFloat.h"

CVariableFloat::CVariableFloat(QObject *parent)
	: QObject(parent)
{

}
CVariableFloat::CVariableFloat()
	: QObject()
{

}
CVariableFloat::CVariableFloat(float arg_value)
	: QObject()
{
	m_fValeur = arg_value;
}
CVariableFloat::~CVariableFloat()
{

}


QString CVariableFloat::toString(){
	return QString::number(m_fValeur);
}
int CVariableFloat::toInt(){
	return m_fValeur;
}
float CVariableFloat::toFloat(){
	return m_fValeur;
}
bool CVariableFloat::toBool(){
	return m_fValeur;
}
void CVariableFloat::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableFloat::setValue(float value){
	m_fValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableFloat::setToBindedValue(QVariant value){
	m_fValeur = value.toFloat();
}
QString CVariableFloat::getLabel()const{
	return m_label;
}
void CVariableFloat::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableFloat::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableFloat::getType()const{
	return variableType::type_float;
}
