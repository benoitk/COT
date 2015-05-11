#include "CVariableOutputBool.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"

CVariableOutputBool::CVariableOutputBool(QObject *parent)
    : IVariable(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableOutputBool::~CVariableOutputBool()
{

}

CVariableOutputBool::CVariableOutputBool(const QMap<QString, QVariant> &mapVar)
    : IVariable()
    , m_modelExtensionCard(Q_NULLPTR)
{

}
QString CVariableOutputBool::getName()const{
    return m_name;
}
void CVariableOutputBool::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
}
CModelExtensionCard* CVariableOutputBool::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableOutputBool::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableOutputBool::getOrganneName()const{
	return m_organneName;
}
QString CVariableOutputBool::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableOutputBool::setOrganne(CModelExtensionCard* arg_model,const  QString  &arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

void CVariableOutputBool::writeValue(){
	

}
QString CVariableOutputBool::toString(){
	return QString::number(m_bValeur);
}
int CVariableOutputBool::toInt(){
	return m_bValeur;
}
float CVariableOutputBool::toFloat(){
	return m_bValeur;
}
void CVariableOutputBool::setValue(const QVariant & value){
	setValue(value.toFloat());
}
void CVariableOutputBool::setValue(float value){
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
void CVariableOutputBool::setToBindedValue(const QVariant & value){
	m_bValeur = value.toFloat();
}
QString CVariableOutputBool::getLabel()const{
	return m_label;
}
void CVariableOutputBool::setLabel(const QString & lbl){
	m_label = lbl;
    emit signalVariableChanged();
}
void CVariableOutputBool::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableOutputBool::getType()const{
    return type_bool;
}
IVariable* CVariableOutputBool::getIVariable(){
	return this;
}
bool CVariableOutputBool::toBool(){
	return m_bValeur;
}void CVariableOutputBool::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_bValeur));
	if(!var.isNull())
		m_bValeur = var.toBool();
	m_unit = targetUnit;
}
void  CVariableOutputBool::delBind(IVariable*){

}
CUnit * CVariableOutputBool::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableOutputBool::isStreamRelated()const{
	return false;
}
QString  CVariableOutputBool::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableOutputBool::isMeasureRelated()const{
	return false;
}
QString  CVariableOutputBool::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableOutputBool::isDisplay()const{
	return false;
}
QList<IVariable*>  CVariableOutputBool::getListOutBinds()const{
	return m_listBinds;
}
QList<IVariable*>  CVariableOutputBool::getListInBinds()const{
	return m_listBinds;

}
QVariantMap CVariableOutputBool::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_bValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
variableAccess CVariableOutputBool::getAccess()const{
    return m_access;
}
int CVariableOutputBool::getAddress()const{
    return m_address;
}
