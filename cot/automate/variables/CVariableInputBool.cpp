#include "CVariableInputBool.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "CUnit.h"
CVariableInputBool::CVariableInputBool(QObject *parent)
	: QObject(parent)
{

}

CVariableInputBool::~CVariableInputBool()
{

}
CVariableInputBool::CVariableInputBool(QMap<QString, QVariant> mapVar): QObject(){

}

CModelExtensionCard* CVariableInputBool::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableInputBool::getComObserver()const{
	return m_modelExtensionCard;
}

QString CVariableInputBool::getOrganneName()const{
	return m_organneName;
}
QString CVariableInputBool::getOrganneAddr()const{
	return "return ADDR";
}
void CVariableInputBool::setOrganne(CModelExtensionCard* arg_model,QString arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

IVariable* CVariableInputBool::readValue(){
	QVariant var = m_modelExtensionCard->readOrganneValue(this);
	this->setValue(var.toFloat());

	return this;
}
QString CVariableInputBool::toString(){
	this->readValue();
	return QString::number(m_bValeur);
}
int CVariableInputBool::toInt(){
	this->readValue();
	return m_bValeur;
}
float CVariableInputBool::toFloat(){
	this->readValue();
	return m_bValeur;
}
bool CVariableInputBool::toBool(){
	this->readValue();
	return m_bValeur;
}
void CVariableInputBool::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableInputBool::setValue(float value){
	m_bValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInputBool::setToBindedValue(QVariant value){
	m_bValeur = value.toFloat();
}
QString CVariableInputBool::getLabel()const{
	return m_label;
}
void CVariableInputBool::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableInputBool::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableInputBool::getType()const{
    return type_bool;
}
organneInputType CVariableInputBool::getTypeOrganne()const{
	return m_organneType;
}

IVariable* CVariableInputBool::getIVariable(){
	return this;
}
void CVariableInputBool::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_bValeur));
	if(!var.isNull())
		m_bValeur = var.toBool();
	m_unit = targetUnit;
}
