#include "CVariableInputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
CVariableInputInt::CVariableInputInt(QObject *parent)
	: QObject(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableInputInt::~CVariableInputInt()
{

}

CVariableInputInt::CVariableInputInt(const QMap<QString, QVariant> &mapVar)
    : QObject()
    , m_modelExtensionCard(Q_NULLPTR)
{

}
QString CVariableInputInt::getName()const{
    return m_name;
}
void CVariableInputInt::setName(const QString& name){
    m_name = name;
}
CModelExtensionCard* CVariableInputInt::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableInputInt::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableInputInt::getOrganneName()const{
	return m_organneName;
}
QString CVariableInputInt::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableInputInt::setOrganne(CModelExtensionCard* arg_model,const QString &arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

IVariable* CVariableInputInt::readValue(){
    if (m_modelExtensionCard) {
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toFloat());
    }

	return this;
}
QString CVariableInputInt::toString(){
	this->readValue();
	return QString::number(m_iValeur);
}
int CVariableInputInt::toInt(){
	this->readValue();
	return m_iValeur;
}
float CVariableInputInt::toFloat(){
	this->readValue();
	return m_iValeur;
}
bool CVariableInputInt::toBool(){
	this->readValue();
	return m_iValeur;
}
void CVariableInputInt::setValue(const QVariant & value){
	setValue(value.toFloat());
}
void CVariableInputInt::setValue(float value){
	m_iValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInputInt::setToBindedValue(const QVariant & value){
	m_iValeur = value.toFloat();
}
QString CVariableInputInt::getLabel()const{
	return m_label;
}
void CVariableInputInt::setLabel(const QString & lbl){
	m_label = lbl;
}
void CVariableInputInt::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableInputInt::getType()const{
    return type_int;
}
IVariable* CVariableInputInt::getIVariable(){
	return this;
}
void CVariableInputInt::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_iValeur));
	if(!var.isNull())
		m_iValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableInputInt::delBind(IVariable*){

}
CUnit * CVariableInputInt::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableInputInt::isStreamRelated()const{
	return false;
}
QString  CVariableInputInt::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableInputInt::isMeasureRelated()const{
	return false;
}
QString  CVariableInputInt::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableInputInt::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableInputInt::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableInputInt::getListInBinds()const{
	return m_listBinds;

}
