#include "CVariableInputBool.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "IVariable.h"
#include "CUnit.h"
CVariableInputBool::CVariableInputBool(QObject *parent)
    : IVariable(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableInputBool::~CVariableInputBool()
{

}
CVariableInputBool::CVariableInputBool(const QMap<QString, QVariant> &mapVar)
    : IVariable()
    , m_modelExtensionCard(Q_NULLPTR)
{

}
QString CVariableInputBool::getName()const{
    return m_name;
}
void CVariableInputBool::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
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
    return QStringLiteral("return ADDR");
}
void CVariableInputBool::setOrganne(CModelExtensionCard* arg_model,const QString &arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

IVariable* CVariableInputBool::readValue(){
    if (m_modelExtensionCard) {
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toFloat());
    }

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
void CVariableInputBool::setValue(const QVariant & value){
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

    emit signalVariableChanged();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInputBool::setToBindedValue(const QVariant & value){
	m_bValeur = value.toFloat();
}
QString CVariableInputBool::getLabel()const{
	return m_label;
}
void CVariableInputBool::setLabel(const QString & lbl){
	m_label = lbl;
    emit signalVariableChanged();
}
void CVariableInputBool::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableInputBool::getType()const{
    return type_bool;
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
void  CVariableInputBool::delBind(IVariable*){

}
CUnit * CVariableInputBool::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableInputBool::isStreamRelated()const{
	return false;
}
QString  CVariableInputBool::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableInputBool::isMeasureRelated()const{
	return false;
}
QString  CVariableInputBool::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableInputBool::isDisplay()const{
	return false;
}
QList<IVariable*>  CVariableInputBool::getListOutBinds()const{
	return m_listBinds;
}
QList<IVariable*>  CVariableInputBool::getListInBinds()const{
	return m_listBinds;

}
QVariantMap CVariableInputBool::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_bValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
variableAccess CVariableInputBool::getAccess()const{
    return m_access;
}
int CVariableInputBool::getAddress()const{
    return m_address;
}
