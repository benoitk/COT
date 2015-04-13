#include "CVariableInt.h"
#include "CUnit.h"

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
    return type_int;
}
void CVariableInt::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_iValeur));
	if(!var.isNull())
		m_iValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableInt::delBind(IVariable*){

}
void  CVariableInt::getUnit(){

}
bool  CVariableInt::isStreamRelated()const{
	return false;
}
QString  CVariableInt::getRelatedStreamName()const{
	return "voie a changer";
}
bool  CVariableInt::isMeasureRelated()const{
	return false;
}
QString  CVariableInt::getRelatedMeasureName()const{
	return "mesure a changer";
}
bool  CVariableInt::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableInt::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableInt::getListInBinds()const{
	return m_listBinds;

}