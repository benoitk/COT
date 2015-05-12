#include "CVariableString.h"
#include "CUnit.h"


CVariableString::CVariableString(QObject *parent)
    : IVariable(parent)
{

}
CVariableString::CVariableString(const QString &arg_value)
    : IVariable()
{
	m_sValeur = arg_value;
}
CVariableString::~CVariableString()
{

}
QString CVariableString::getName()const{
    return m_name;
}
void CVariableString::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
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
void CVariableString::setValue(const QVariant & value){
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

    emit signalVariableChanged();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableString::setToBindedValue(const QVariant & value){
	m_sValeur = value.toString();
}
QString CVariableString::getLabel()const{
	return m_label;
}
void CVariableString::setLabel(const QString & lbl){
	m_label = lbl;
    emit signalVariableChanged();
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
        m_sValeur = QString::number(var.toFloat());
	m_unit = targetUnit;
}
void  CVariableString::delBind(IVariable*){

}
CUnit *CVariableString::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableString::isStreamRelated()const{
	return false;
}
QString  CVariableString::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableString::isMeasureRelated()const{
	return false;
}
QString  CVariableString::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableString::isDisplay()const{
	return false;
}
QList<IVariable*>  CVariableString::getListOutBinds()const{
	return m_listBinds;
}
QList<IVariable*>  CVariableString::getListInBinds()const{
	return m_listBinds;

}
QVariantMap CVariableString::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("string"));
    mapSerialise.insert(QStringLiteral("value"), m_sValeur);
    return mapSerialise;
}
variableAccess CVariableString::getAccess()const{
    return m_access;
}
int CVariableString::getAddress()const{
    return m_address;
}

void CVariableString::setRelatedStreamName(const QString &variableName)
{

}
