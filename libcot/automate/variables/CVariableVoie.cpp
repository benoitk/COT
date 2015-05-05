#include "CVariableVoie.h"
#include "CUnit.h"
#include "IVariable.h"
#include "ICycle.h"
#include "CAutomate.h"
#include "CVariableFactory.h"

#include "qlinkedlist.h"
CVariableVoie::CVariableVoie(QObject *parent):QObject(parent)
{	
}
CVariableVoie::CVariableVoie(const QMap<QString, QVariant> &mapVar):QObject(){
    if(mapVar.contains(QStringLiteral("name")))
        m_name = mapVar.value(QStringLiteral("name")).toString();
    else m_name = QStringLiteral("Stream unamed");
    
    if(mapVar.contains(tr("fr_FR")))
        m_label = mapVar.value(tr("fr_FR")).toString();
    else m_name = QStringLiteral("Stream no label");
    
    m_activeState = CAutomate::getInstance()->getVariable(mapVar.value(tr("active_state")).toString());
    
    if(mapVar.contains(QStringLiteral("variables"))){
        QVariantList listVariable = mapVar.value(QStringLiteral("variables")).toList();
        foreach(QVariant variant, listVariable){
            m_listVariables.append(CAutomate::getInstance()->getVariable(variant.toString()));
        }
    }

    if(mapVar.contains(QStringLiteral("cycles"))){
        QVariantList listVariable = mapVar.value(QStringLiteral("cycles")).toList();
        foreach(QVariant variant, listVariable){
            m_listCycles.append(CAutomate::getInstance()->getCycle(variant.toString(), CYCLE_MESURE));
        }
    }

    if(mapVar.contains(QStringLiteral("measures"))){
        QVariantList listVariable = mapVar.value(QStringLiteral("measures")).toList();
        foreach(QVariant variant, listVariable){
            QVariantMap map = variant.toMap();
            map.insert(QStringLiteral("type"), QStringLiteral("measure"));
            IVariable* var = CVariableFactory::build(map); 
            m_listMeasures.append(var);
        }
    }


}

CVariableVoie::~CVariableVoie()
{
}
QList<IVariable*> CVariableVoie::getListMeasures(){
    return m_listMeasures;
}
QList<ICycle*> CVariableVoie::getListCycles(){
    return m_listCycles;
}
IVariable* CVariableVoie::getActiveState(){
    return m_activeState;
}
QString CVariableVoie::getName()const{
    return m_name;
}
void CVariableVoie::setName(const QString& name){
    m_name = name;
}
QString CVariableVoie::toString(){
    return m_label;
}
int CVariableVoie::toInt(){
	return 0;
}
float CVariableVoie::toFloat(){
	return 0;
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
}
void CVariableVoie::setValue(const QVariant & value){
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
void  CVariableVoie::addBind(IVariable*){

}
CUnit * CVariableVoie::getUnit() const{
    return Q_NULLPTR;
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
//TO DO : change name to CVariableStream()
QVariantMap CVariableVoie::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("stream"));
    QList<QVariant> listVars;
    foreach(IVariable* var, m_listVariables){
        listVars.append(var->getName());
    }
    mapSerialise.insert(QStringLiteral("variables"), listVars);
    QList<QVariant> listMeasures;
    foreach(IVariable* var, m_listMeasures){
        listMeasures.append(var->serialise());
    }
    mapSerialise.insert(QStringLiteral("measures"), listMeasures);
    QList<QVariant> listCycles;
    foreach(IVariable* cycle, m_listMeasures){
        listCycles.append(cycle->getName());
    }
    mapSerialise.insert(QStringLiteral("measures"), listMeasures);
    return mapSerialise;
}