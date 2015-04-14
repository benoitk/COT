#include "CVariableOutputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"

CVariableOutputInt::CVariableOutputInt(QObject *parent)
	: QObject(parent)
{

}

CVariableOutputInt::~CVariableOutputInt()
{

}

CVariableOutputInt::CVariableOutputInt(const QMap<QString, QVariant> &mapVar): QObject(){

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
    return QStringLiteral("return ADDR");
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
void CVariableOutputInt::setValue(const QVariant & value){
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
void CVariableOutputInt::setToBindedValue(const QVariant & value){
	m_iValeur = value.toFloat();
}
QString CVariableOutputInt::getLabel()const{
	return m_label;
}
void CVariableOutputInt::setLabel(const QString & lbl){
	m_label = lbl;
}
void CVariableOutputInt::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableOutputInt::getType()const{
    return type_int;
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
void CVariableOutputInt::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_iValeur));
	if(!var.isNull())
		m_iValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableOutputInt::delBind(IVariable*){

}
void  CVariableOutputInt::getUnit(){

}
bool  CVariableOutputInt::isStreamRelated()const{
	return false;
}
QString  CVariableOutputInt::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableOutputInt::isMeasureRelated()const{
	return false;
}
QString  CVariableOutputInt::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableOutputInt::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableOutputInt::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableOutputInt::getListInBinds()const{
	return m_listBinds;

}
