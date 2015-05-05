#include "CVariableBool.h"
#include "CUnit.h"
CVariableBool::CVariableBool(QObject *parent)
	: QObject(parent)
{

}

CVariableBool::CVariableBool(bool arg_value, int arg_address, variableAccess arg_access)
	: QObject()
{
	m_bValeur = arg_value;
    m_access = arg_access;
    m_address = arg_address;
}


CVariableBool::~CVariableBool()
{

}

QString CVariableBool::getName()const{
    return m_name;
}
void CVariableBool::setName(const QString& name){
    m_name = name;
}

QString CVariableBool::toString(){
	if(m_bValeur)
		return tr("vrai");
	else
		return tr("faux");
}
int CVariableBool::toInt(){
	return m_bValeur;
}
float CVariableBool::toFloat(){
	return m_bValeur;
}
bool CVariableBool::toBool(){
	return m_bValeur;
}

void CVariableBool::setValue(const QVariant & value){
	setValue(value.toBool());
}
void CVariableBool::setValue(bool value){
	m_bValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setToBindedValue(QVariant(value));
		}
	}
}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableBool::setToBindedValue(const QVariant & value){
	m_bValeur = value.toBool();
}

QString CVariableBool::getLabel()const{
	return m_label;
}
void CVariableBool::setLabel(const QString & lbl){
	m_label = lbl;
}

void CVariableBool::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}

variableType CVariableBool::getType()const{
    return type_bool;
}

void CVariableBool::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_bValeur));
	if(!var.isNull())
		m_bValeur = var.toBool();
	m_unit = targetUnit;
}

void  CVariableBool::delBind(IVariable*){

}
CUnit * CVariableBool::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableBool::isStreamRelated()const{
	return false;
}
QString  CVariableBool::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableBool::isMeasureRelated()const{
	return false;
}
QString  CVariableBool::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableBool::isDisplay()const{
	return false;
}
QList<IVariable*>  CVariableBool::getListOutBinds()const{
	return m_listBinds;
}
QList<IVariable*>  CVariableBool::getListInBinds()const{
	return m_listBinds;

}
QVariantMap CVariableBool::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_bValeur);
    return mapSerialise;
}
variableAccess CVariableBool::getAccess()const{
    return m_access;
}
int CVariableBool::getAddress()const{
    return m_address;
}
