#include "CVariableUnknow.h"
#include "CUnit.h"
#include "qlinkedlist.h"
CVariableUnknow::CVariableUnknow()
	: QObject()
{

}

CVariableUnknow::~CVariableUnknow()
{

}

QString CVariableUnknow::getName()const{
    return QStringLiteral("unknow var");
}
void CVariableUnknow::setName(const QString& name){
}
QString CVariableUnknow::toString(){
	return tr("Variable inconnu");
}
int CVariableUnknow::toInt(){
	return 0;
}
float CVariableUnknow::toFloat(){
	return 0;
}
bool CVariableUnknow::toBool(){
	return false;
}
void CVariableUnknow::setValue(const QVariant &){
}
QString CVariableUnknow::getLabel()const{
	return tr("Variable inconnu");
}
void CVariableUnknow::setLabel(const QString &){
}
void CVariableUnknow::addBind(IVariable* arg_var){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableUnknow::setToBindedValue(const QVariant & value){
}
variableType CVariableUnknow::getType()const{
    return type_unknow;
}
void CVariableUnknow::switchToUnit(CUnit* targetUnit){
	
}
void  CVariableUnknow::delBind(IVariable*){

}
CUnit * CVariableUnknow::getUnit() const {
    return Q_NULLPTR;
}
bool  CVariableUnknow::isStreamRelated()const{
	return false;
}
QString  CVariableUnknow::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableUnknow::isMeasureRelated()const{
	return false;
}
QString  CVariableUnknow::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableUnknow::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableUnknow::getListOutBinds()const{
	QLinkedList<IVariable*> list;
	return list;
}
QLinkedList<IVariable*>  CVariableUnknow::getListInBinds()const{
	QLinkedList<IVariable*> list;
	return list;

}
