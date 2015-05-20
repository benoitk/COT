#include "CVariableMeasure.h"
#include "CAutomate.h"
#include "IVariable.h"

#include "CUnit.h"
#include "qlinkedlist.h"

#define QSL QStringLiteral

CVariableMeasure::CVariableMeasure(QObject *parent)
    :IVariable(parent)
    , m_access(access_read_write)
{
}
CVariableMeasure::CVariableMeasure(const QMap<QString, QVariant> &mapVar)
    :IVariable()
    , m_access(access_read_write)
{
    m_name = mapVar.value(QSL("name")).toString();
    if (m_name.isEmpty())
        m_name = QSL("Stream unamed");

    m_label = mapVar.value(tr("fr_FR")).toString();
    if (m_label.isEmpty())
        m_label = tr("Stream no label");

    m_measure = CAutomate::getInstance()->getVariable(mapVar.value(QSL("variable_measure")).toString());
    m_measureMax = CAutomate::getInstance()->getVariable(mapVar.value(QSL("variable_range_max")).toString());
    m_measureMin = CAutomate::getInstance()->getVariable(mapVar.value(QSL("variable_range_min")).toString());

    QVariantList listVariable = mapVar.value(QStringLiteral("variables")).toList();
    foreach(const QVariant &variant, listVariable){
        m_listVariables.append(CAutomate::getInstance()->getVariable(variant.toString()));
    }
}
IVariable* CVariableMeasure::getMeasureMax(){
    return m_measureMax;
}
IVariable* CVariableMeasure::getMeasureMin(){
    return m_measureMin;
}

void CVariableMeasure::delVariable(IVariable *ivar)
{
    m_listVariables.removeOne(ivar);
}

QList<IVariable*>  CVariableMeasure::getListVariables(){
    return m_listVariables;
}
IVariable* CVariableMeasure::getMeasureVariable(){
    return m_measure;
}
QString CVariableMeasure::getName()const{
    return m_name;
}
void CVariableMeasure::setName(const QString& name){
    m_name = name;
    emit signalVariableChanged();
}
QString CVariableMeasure::toString(){
    return m_label;
}
int CVariableMeasure::toInt(){
    return 0;
}
float CVariableMeasure::toFloat(){
    return 0;
}
bool CVariableMeasure::toBool(){
    return false;
}
QString CVariableMeasure::getLabel()const{
    return m_label;
}
void CVariableMeasure::setLabel(const QString & label){
    m_label = label;
    emit signalVariableChanged();
}

void CVariableMeasure::setValue(int iValue){
}
void CVariableMeasure::setValue(const QVariant & value){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableMeasure::setToBindedValue(const QVariant & value){

}
variableType CVariableMeasure::getType()const{
    return type_measure;
}
void CVariableMeasure::switchToUnit(CUnit* targetUnit){

}
void  CVariableMeasure::delBind(IVariable*){

}
void  CVariableMeasure::addBind(IVariable*){

}
CUnit * CVariableMeasure::getUnit() const{
    return Q_NULLPTR;
}
bool  CVariableMeasure::isStreamRelated()const{
    return !m_streamRelatedVariableName.isEmpty();
}
QString  CVariableMeasure::getRelatedStreamName()const{
    return m_streamRelatedVariableName.isEmpty() ? QStringLiteral("stream_1") : m_streamRelatedVariableName;
}
bool  CVariableMeasure::isMeasureRelated()const{
    return false;
}
QString  CVariableMeasure::getRelatedMeasureName()const{
    return QStringLiteral("mesure a changer");
}
bool  CVariableMeasure::isDisplay()const{
    return false;
}
QList<IVariable*>  CVariableMeasure::getListOutBinds()const{
    QList<IVariable*> list;
    return list;
}
QList<IVariable*>  CVariableMeasure::getListInBinds()const{
    QList<IVariable*> list;
    return list;

}
QVariantMap CVariableMeasure::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(tr("variable_measure"), m_measure->getName());
    mapSerialise.insert(tr("variable_range_max"), m_measureMax->getName());
    mapSerialise.insert(tr("variable_range_min"), m_measureMin->getName());
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("measure"));
    QList<QVariant> listVars;
    foreach(IVariable* var, m_listVariables){
        listVars.append(var->getName());
    }

    return mapSerialise;
}
void CVariableMeasure::setListOutBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}

void CVariableMeasure::setListInBinds(const QList<IVariable *> &)
{
    //SERES_TODO: Implement that for each variable
}
variableAccess CVariableMeasure::getAccess()const{
    return m_access;
}
int CVariableMeasure::getAddress()const{
    return m_address;
}

void CVariableMeasure::setRelatedStreamName(const QString &variableName)
{
    m_streamRelatedVariableName = variableName;
}

void CVariableMeasure::setAccess(variableAccess access)
{
    m_access = access;
}
