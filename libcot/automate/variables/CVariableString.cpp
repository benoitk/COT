#include "CVariableString.h"
#include "CUnit.h"

CVariableString::CVariableString(QObject *parent)
	: QObject(parent)
{

}
CVariableString::CVariableString(const QString &arg_value)
	: QObject()
{
	m_sValeur = arg_value;
}
CVariableString::~CVariableString()
{

}

QString CVariableString::toString(){
	return m_sValeur;
}
int CVariableString::toInt(){
	return m_sValeur.toInt();
}
float CVariableString::toFloat(){
	return m_sValeur.toFloat();
}
bool CVariableString::toBool(){
	if(m_sValeur == tr("vrai"))	return true;
	else if(m_sValeur == tr("faux")) return false;
	else return m_sValeur.toInt();
}
void CVariableString::setValue(QVariant value){
	setValue(value.toString());
}
void CVariableString::setValue(QString value){
	m_sValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableString::setToBindedValue(QVariant value){
	m_sValeur = value.toString();
}
QString CVariableString::getLabel()const{
	return m_label;
}
void CVariableString::setLabel(QString lbl){
	m_label = lbl;
}
void CVariableString::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableString::getType()const{
    return type_string;
}
void CVariableString::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_sValeur));
	if(!var.isNull())
		m_sValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableString::delBind(IVariable*){

}
void  CVariableString::getUnit(){

}
bool  CVariableString::isStreamRelated()const{
	return false;
}
QString  CVariableString::getRelatedStreamName()const{
	return "voie a changer";
}
bool  CVariableString::isMeasureRelated()const{
	return false;
}
QString  CVariableString::getRelatedMeasureName()const{
	return "mesure a changer";
}
bool  CVariableString::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableString::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableString::getListInBinds()const{
	return m_listBinds;

}