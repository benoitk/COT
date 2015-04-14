#include "CVariableVoie.h"
#include "CUnit.h"
#include "qlinkedlist.h"
CVariableVoie::CVariableVoie(QObject *parent):QObject(parent)
{	
}
CVariableVoie::CVariableVoie(QObject * parent, int iNumVoie):QObject(parent){
	m_iNumVoie = iNumVoie;	 
}

CVariableVoie::~CVariableVoie()
{
}


QString CVariableVoie::toString(){
	return QString::number(m_iNumVoie);
}
int CVariableVoie::toInt(){
	return m_iNumVoie;
}
float CVariableVoie::toFloat(){
	return m_iNumVoie;
}
bool CVariableVoie::toBool(){
	return false;
}
QString CVariableVoie::getLabel()const{
	return m_label;
}
void CVariableVoie::setLabel(const QString & label){
	m_label = label;
}

void CVariableVoie::setValue(int iValue){
	m_iNumVoie = iValue;
}
void CVariableVoie::setValue(const QVariant & value){
	m_iNumVoie = value.toInt();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableVoie::setToBindedValue(const QVariant & value){
	
}
variableType CVariableVoie::getType()const{
    return type_stream;
}
void CVariableVoie::switchToUnit(CUnit* targetUnit){

}
void  CVariableVoie::delBind(IVariable*){

}
void  CVariableVoie::getUnit(){

}
bool  CVariableVoie::isStreamRelated()const{
	return false;
}
QString  CVariableVoie::getRelatedStreamName()const{
    return QStringLiteral("voie a changer");
}
bool  CVariableVoie::isMeasureRelated()const{
	return false;
}
QString  CVariableVoie::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableVoie::isDisplay()const{
	return false;
}
QLinkedList<IVariable*>  CVariableVoie::getListOutBinds()const{
	QLinkedList<IVariable*> list;
	return list;
}
QLinkedList<IVariable*>  CVariableVoie::getListInBinds()const{
	QLinkedList<IVariable*> list;
	return list;

}
