#include "CVariableOutputInt.h"
#include "CModelExtensionCard.h"

CVariableOutputInt::CVariableOutputInt(QObject *parent)
	: QObject(parent)
{

}

CVariableOutputInt::~CVariableOutputInt()
{

}

CVariableOutputInt::CVariableOutputInt(QMap<QString, QVariant> mapVar): QObject(){

}

CModelExtensionCard* CVariableOutputInt::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableOutputInt::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableOutputInt::getOrganneName()const{
	return m_organneName;
}
QString CVariableOutputInt::getOrganneAddr()const{
	return "return ADDR";
}
void CVariableOutputInt::setOrganne(CModelExtensionCard* arg_model,QString arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

void CVariableOutputInt::writeValue(){
	

}
QString CVariableOutputInt::toString(){
	return QString::number(m_iValeur);
}
int CVariableOutputInt::toInt(){
	return m_iValeur;
}
float CVariableOutputInt::toFloat(){
	return m_iValeur;
}
void CVariableOutputInt::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableOutputInt::setValue(float value){
	m_iValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableOutputInt::setToBindedValue(QVariant value){
	m_iValeur = value.toFloat();
}
QString CVariableOutputInt::getLabel()const{
	return m_label;
}
void CVariableOutputInt::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableOutputInt::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableOutputInt::getType()const{
	return variableType::type_int;
}
organneOutputType CVariableOutputInt::getTypeOrganne()const{
	return m_organneType;
}
IVariable* CVariableOutputInt::getIVariable(){
	return this;
}
bool CVariableOutputInt::toBool(){
	return m_iValeur;
}