#include "CVariableInt.h"

CVariableInt::CVariableInt(QObject *parent):QObject(parent)
{
	
}
CVariableInt::CVariableInt(int arg_int):QObject()
{
	m_iValeur = arg_int;
}

CVariableInt::~CVariableInt()
{

}
QString CVariableInt::toString(){
	return QString::number(m_iValeur);
}
int CVariableInt::toInt(){
	return m_iValeur;
}
float CVariableInt::toFloat(){
	return m_iValeur;
}
bool CVariableInt::toBool(){
	return m_iValeur;
}
void CVariableInt::setValue(int value){
	m_iValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInt::setToBindedValue(QVariant value){
	m_iValeur = value.toInt();
}
void CVariableInt::setValue(QVariant value){
	setValue(value.toInt());
}
QString CVariableInt::getLabel()const{
	return m_label;
}
void CVariableInt::setLabel(QString label){
	m_label = label;
}
void CVariableInt::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableInt::getType()const{
	return variableType::type_int;
}
