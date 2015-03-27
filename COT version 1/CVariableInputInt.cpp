#include "CVariableInputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
CVariableInputInt::CVariableInputInt(QObject *parent)
	: QObject(parent)
{

}

CVariableInputInt::~CVariableInputInt()
{

}

CVariableInputInt::CVariableInputInt(QMap<QString, QVariant> mapVar): QObject(){

}

CModelExtensionCard* CVariableInputInt::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableInputInt::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableInputInt::getOrganneName()const{
	return m_organneName;
}
QString CVariableInputInt::getOrganneAddr()const{
	return "return ADDR";
}
void CVariableInputInt::setOrganne(CModelExtensionCard* arg_model,QString arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

IVariable* CVariableInputInt::readValue(){
	QVariant var = m_modelExtensionCard->readOrganneValue(this);
	this->setValue(var.toFloat());

	return this;
}
QString CVariableInputInt::toString(){
	this->readValue();
	return QString::number(m_iValeur);
}
int CVariableInputInt::toInt(){
	this->readValue();
	return m_iValeur;
}
float CVariableInputInt::toFloat(){
	this->readValue();
	return m_iValeur;
}
bool CVariableInputInt::toBool(){
	this->readValue();
	return m_iValeur;
}
void CVariableInputInt::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableInputInt::setValue(float value){
	m_iValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInputInt::setToBindedValue(QVariant value){
	m_iValeur = value.toFloat();
}
QString CVariableInputInt::getLabel()const{
	return m_label;
}
void CVariableInputInt::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableInputInt::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableInputInt::getType()const{
	return variableType::type_int;
}
organneInputType CVariableInputInt::getTypeOrganne()const{
	return m_organneType;
}
IVariable* CVariableInputInt::getIVariable(){
	return this;
}
void CVariableInputInt::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_iValeur));
	if(!var.isNull())
		m_iValeur = var.toFloat();
	m_unit = targetUnit;
}
