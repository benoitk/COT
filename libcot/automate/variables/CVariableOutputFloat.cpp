#include "CVariableOutputFloat.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "cotautomate_debug.h"
CVariableOutputFloat::CVariableOutputFloat(QObject *parent)
    : IVariable(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableOutputFloat::~CVariableOutputFloat()
{

}

CVariableOutputFloat::CVariableOutputFloat(const QMap<QString, QVariant> &mapVar)
    : IVariable()
    , m_modelExtensionCard(Q_NULLPTR)
{

}
QString CVariableOutputFloat::getName()const{
    return m_name;
}
void CVariableOutputFloat::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
}
CModelExtensionCard* CVariableOutputFloat::getExtensionCard()const{
	return m_modelExtensionCard;
}
IComObserver* CVariableOutputFloat::getComObserver()const{
	return m_modelExtensionCard;
}
QString CVariableOutputFloat::getOrganneName()const{
	return m_organneName;
}
QString CVariableOutputFloat::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableOutputFloat::setOrganne(CModelExtensionCard* arg_model, const QString &arg_organneName){
	m_modelExtensionCard = arg_model;
	m_organneName = arg_organneName;
}

void CVariableOutputFloat::writeValue(){
	

}
QString CVariableOutputFloat::toString(){
	return QString::number(m_fValeur);
}
int CVariableOutputFloat::toInt(){
	return m_fValeur;
}
float CVariableOutputFloat::toFloat(){
	return m_fValeur;
}
void CVariableOutputFloat::setValue(const QVariant & value){
	setValue(value.toFloat());
}
void CVariableOutputFloat::setValue(float value){
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
void CVariableOutputFloat::setToBindedValue(const QVariant & value){
	m_fValeur = value.toFloat();
}
QString CVariableOutputFloat::getLabel()const{
	return m_label;
}
void CVariableOutputFloat::setLabel(const QString & lbl){
	m_label = lbl;
    emit signalVariableChanged();
}
void CVariableOutputFloat::addBind(IVariable* arg_var){
	if(arg_var)
		m_listBinds.append(arg_var);
}
variableType CVariableOutputFloat::getType()const{
    return type_float;
}
IVariable* CVariableOutputFloat::getIVariable(){
	return this;
}
bool CVariableOutputFloat::toBool(){
	return m_fValeur;
}
void CVariableOutputFloat::switchToUnit(CUnit* targetUnit){
	QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_fValeur));
	if(!var.isNull())
		m_fValeur = var.toFloat();
	m_unit = targetUnit;
}
void  CVariableOutputFloat::delBind(IVariable*){

}
CUnit * CVariableOutputFloat::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableOutputFloat::isStreamRelated()const{
	return false;
}
QString  CVariableOutputFloat::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableOutputFloat::isMeasureRelated()const{
	return false;
}
QString  CVariableOutputFloat::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableOutputFloat::isDisplay()const{
	return false;
}
QList<IVariable*>  CVariableOutputFloat::getListOutBinds()const{
	return m_listBinds;
}
QList<IVariable*>  CVariableOutputFloat::getListInBinds()const{
	return m_listBinds;

}

void CVariableOutputFloat::setListOutBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

void CVariableOutputFloat::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

QVariantMap CVariableOutputFloat::serialise()
{
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_float"));
    mapSerialise.insert(QStringLiteral("value"), m_fValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
variableAccess CVariableOutputFloat::getAccess()const{
    return m_access;
}
int CVariableOutputFloat::getAddress()const{
    return m_address;
}

void CVariableOutputFloat::setRelatedStreamName(const QString &variableName)
{

}
