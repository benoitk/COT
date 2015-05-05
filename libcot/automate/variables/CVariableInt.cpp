#include "CVariableInt.h"
#include "CUnit.h"

CVariableInt::CVariableInt(QObject *parent):QObject(parent),m_iValeur(-1)
{
	
}
CVariableInt::CVariableInt(int arg_int, int arg_address, variableAccess arg_access):QObject()
{
	m_iValeur = arg_int;
    m_access = arg_access;
    m_address = arg_address;
}

CVariableInt::~CVariableInt()
{

}
QString CVariableInt::getName()const{
    return m_name;
}
void CVariableInt::setName(const QString& name){
    m_name = name;
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
void CVariableInt::setToBindedValue(const QVariant & value){
	m_iValeur = value.toInt();
}
void CVariableInt::setValue(const QVariant & value){
	setValue(value.toInt());
}
QString CVariableInt::getLabel()const{
	return m_label;
}
void CVariableInt::setLabel(const QString & label){
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
CUnit * CVariableInt::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableInt::isStreamRelated()const{
	return false;
}
QString  CVariableInt::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableInt::isMeasureRelated()const{
	return false;
}
QString  CVariableInt::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
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
QVariantMap CVariableInt::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("integer"));
    mapSerialise.insert(QStringLiteral("value"), m_iValeur);
    return mapSerialise;
}
variableAccess CVariableInt::getAccess()const{
    return m_access;
}
int CVariableInt::getAddress()const{
    return m_address;
}