#include "CVariableInputFloat.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "CUnit.h"

CVariableInputFloat::CVariableInputFloat(QObject *parent)
	: QObject(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableInputFloat::~CVariableInputFloat()
{

}

CVariableInputFloat::CVariableInputFloat(const QMap<QString, QVariant> &mapVar)
    : QObject()
    , m_modelExtensionCard(Q_NULLPTR)
{

}
QString CVariableInputFloat::getName()const{
    return m_name;
}
void CVariableInputFloat::setName(const QString& name){
    m_name = name;
}
CModelExtensionCard* CVariableInputFloat::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableInputFloat::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableInputFloat::getOrganneName()const{
	return m_organneName;
}
QString CVariableInputFloat::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableInputFloat::setOrganne(CModelExtensionCard* arg_model,QString arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

IVariable* CVariableInputFloat::readValue(){
    if (m_modelExtensionCard) {
        qDebug("%s: %i", Q_FUNC_INFO, quintptr(m_modelExtensionCard));
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toFloat());
    }

	return this;
}
QString CVariableInputFloat::toString(){
	this->readValue();
	return QString::number(m_fValeur);
}
int CVariableInputFloat::toInt(){
	this->readValue();
	return m_fValeur;
}
float CVariableInputFloat::toFloat(){
	this->readValue();
	return m_fValeur;
}
bool CVariableInputFloat::toBool(){
	this->readValue();
	return m_fValeur;
}
void CVariableInputFloat::setValue(const QVariant & value){
	setValue(value.toFloat());
}
void CVariableInputFloat::setValue(float value){
	m_fValeur = value;
	if(!m_listBinds.isEmpty()){
		IVariable* var;
		foreach(var,  m_listBinds){
			var->setValue(QVariant(value));
		}
	}
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInputFloat::setToBindedValue(const QVariant & value){
	m_fValeur = value.toFloat();
}
QString CVariableInputFloat::getLabel()const{
	return m_label;
}
void CVariableInputFloat::setLabel(const QString & lbl){
	m_label = lbl;
}
void CVariableInputFloat::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}


variableType CVariableInputFloat::getType()const{
    return type_float;
}
organneInputType CVariableInputFloat::getTypeOrganne()const{
	return m_organneType;
}
IVariable* CVariableInputFloat::getIVariable(){
	return this;
}
void CVariableInputFloat::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_fValeur));
	if(!var.isNull())
		m_fValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableInputFloat::delBind(IVariable*){

}
CUnit * CVariableInputFloat::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableInputFloat::isStreamRelated()const{
	return false;
}
QString  CVariableInputFloat::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableInputFloat::isMeasureRelated()const{
	return false;
}
QString  CVariableInputFloat::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableInputFloat::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableInputFloat::getListOutBinds()const{
	return m_listBinds;
}
QLinkedList<IVariable*>  CVariableInputFloat::getListInBinds()const{
	return m_listBinds;

}
