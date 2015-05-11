#include "CVariableFloat.h"
#include "CUnit.h"
CVariableFloat::CVariableFloat(QObject *parent)
    : IVariable(parent)
{

}
CVariableFloat::CVariableFloat()
    : IVariable()
{

}
CVariableFloat::CVariableFloat(float arg_value, int arg_address, variableAccess arg_access)
    : IVariable()
{
	m_fValeur = arg_value;
    m_access = arg_access;
    m_address = arg_address;
}
CVariableFloat::~CVariableFloat()
{

}
QString CVariableFloat::getName()const{
    return m_name;
}
void CVariableFloat::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
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
void CVariableFloat::setValue(const QVariant & value){
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

    emit signalVariableChanged();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableFloat::setToBindedValue(const QVariant & value){
	m_fValeur = value.toFloat();
}
QString CVariableFloat::getLabel()const{
	return m_label;
}
void CVariableFloat::setLabel(const QString & lbl){
	m_label = lbl;
    emit signalVariableChanged();
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
CUnit *CVariableFloat::getUnit() const{
    return Q_NULLPTR;
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
QList<IVariable*>  CVariableFloat::getListOutBinds()const{
	return m_listBinds;
}
QList<IVariable*>  CVariableFloat::getListInBinds()const{
	return m_listBinds;

}
QVariantMap CVariableFloat::serialise(){
     QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("float"));
    mapSerialise.insert(QStringLiteral("value"), m_fValeur);
    return mapSerialise;
}
variableAccess CVariableFloat::getAccess()const{
    return m_access;
}
int CVariableFloat::getAddress()const{
    return m_address;
}

void CVariableFloat::setAccess(variableAccess access)
{
    m_access = access;
}

void CVariableFloat::setAddress(int address)
{
    m_address = address;
}
