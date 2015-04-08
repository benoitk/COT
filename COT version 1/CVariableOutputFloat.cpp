#include "CVariableOutputFloat.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
CVariableOutputFloat::CVariableOutputFloat(QObject *parent)
	: QObject(parent)
{

}

CVariableOutputFloat::~CVariableOutputFloat()
{

}

CVariableOutputFloat::CVariableOutputFloat(QMap<QString, QVariant> mapVar): QObject(){

}

CModelExtensionCard* CVariableOutputFloat::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableOutputFloat::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableOutputFloat::getOrganneName()const{
	return m_organneName;
}
QString CVariableOutputFloat::getOrganneAddr()const{
	return "return ADDR";
}
void CVariableOutputFloat::setOrganne(CModelExtensionCard* arg_model,QString arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

void CVariableOutputFloat::writeValue(){
	

}
QString CVariableOutputFloat::toString(){
	return QString::number(m_fValeur);
}
int CVariableOutputFloat::toInt(){
	return m_fValeur;
}
float CVariableOutputFloat::toFloat(){
	return m_fValeur;
}
void CVariableOutputFloat::setValue(QVariant value){
	setValue(value.toFloat());
}
void CVariableOutputFloat::setValue(float value){
	m_fValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableOutputFloat::setToBindedValue(QVariant value){
	m_fValeur = value.toFloat();
}
QString CVariableOutputFloat::getLabel()const{
	return m_label;
}
void CVariableOutputFloat::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableOutputFloat::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableOutputFloat::getType()const{
	return variableType::type_float;
}
organneOutputType CVariableOutputFloat::getTypeOrganne()const{
	return m_organneType;
}
IVariable* CVariableOutputFloat::getIVariable(){
	return this;
}
bool CVariableOutputFloat::toBool(){
	return m_fValeur;
}
void CVariableOutputFloat::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_fValeur));
	if(!var.isNull())
		m_fValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableOutputFloat::delBind(IVariable*){

}
void  CVariableOutputFloat::getUnit(){

}
bool  CVariableOutputFloat::isStreamRelated()const{
	return false;
}
QString  CVariableOutputFloat::getRelatedStreamName()const{
	return "voie a changer";
}
bool  CVariableOutputFloat::isMeasureRelated()const{
	return false;
}
QString  CVariableOutputFloat::getRelatedMeasureName()const{
	return "mesure a changer";
}
bool  CVariableOutputFloat::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableOutputFloat::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableOutputFloat::getListInBinds()const{
	return m_listBinds;

}