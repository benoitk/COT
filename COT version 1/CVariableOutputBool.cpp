#include "CVariableOutputBool.h"
#include "CModelExtensionCard.h"

CVariableOutputBool::CVariableOutputBool(QObject *parent)
	: QObject(parent)
{

}

CVariableOutputBool::~CVariableOutputBool()
{

}

CVariableOutputBool::CVariableOutputBool(QMap<QString, QVariant> mapVar): QObject(){

}

CModelExtensionCard* CVariableOutputBool::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableOutputBool::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableOutputBool::getOrganneName()const{
	return m_organneName;
}
QString CVariableOutputBool::getOrganneAddr()const{
	return "return ADDR";
}
void CVariableOutputBool::setOrganne(CModelExtensionCard* arg_model,QString arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

void CVariableOutputBool::writeValue(){
	

}
QString CVariableOutputBool::toString(){
	return QString::number(m_bValeur);
}
int CVariableOutputBool::toInt(){
	return m_bValeur;
}
float CVariableOutputBool::toFloat(){
	return m_bValeur;
}
void CVariableOutputBool::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableOutputBool::setValue(float value){
	m_bValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableOutputBool::setToBindedValue(QVariant value){
	m_bValeur = value.toFloat();
}
QString CVariableOutputBool::getLabel()const{
	return m_label;
}
void CVariableOutputBool::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableOutputBool::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableOutputBool::getType()const{
	return variableType::type_bool;
}
organneOutputType CVariableOutputBool::getTypeOrganne()const{
	return m_organneType;
}

IVariable* CVariableOutputBool::getIVariable(){
	return this;
}
bool CVariableOutputBool::toBool(){
	return m_bValeur;
}