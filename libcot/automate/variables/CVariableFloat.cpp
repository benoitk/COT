#include "CVariableFloat.h"
#include "CUnit.h"
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
    return type_float;
}
void CVariableFloat::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_fValeur));
	if(!var.isNull())
		m_fValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableFloat::delBind(IVariable*){

}
void  CVariableFloat::getUnit(){

}
bool  CVariableFloat::isStreamRelated()const{
	return false;
}
QString  CVariableFloat::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableFloat::isMeasureRelated()const{
	return false;
}
QString  CVariableFloat::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableFloat::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableFloat::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableFloat::getListInBinds()const{
	return m_listBinds;

}
