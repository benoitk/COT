#include "CVariableMeasure.h"
#include "CAutomate.h"
#include "IVariable.h"

#include "CUnit.h"
#include "qlinkedlist.h"

#define QSL QStringLiteral

CVariableMeasure::CVariableMeasure(QObject *parent)
    :IVariable(parent)
{
}
CVariableMeasure::CVariableMeasure(const QMap<QString, QVariant> &mapVar)
    :IVariable()
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

void CVariableMeasure::removeVariable(IVariable *ivar)
{
    m_listVariables.removeOne(ivar);

    emit signalVariableChanged(this);
}
void CVariableMeasure::addVariable(IVariable *ivar){
    m_listVariables.append(ivar);

    emit signalVariableChanged(this);
}


void CVariableMeasure::setColor(const QColor &col)
{
    m_color = col;
}

QColor CVariableMeasure::color() const
{
    return m_color;
}

QList<IVariable*>  CVariableMeasure::getListVariables(){
    return m_listVariables;
}
IVariable* CVariableMeasure::getMeasureVariable(){
    return m_measure;
}

QString CVariableMeasure::toString(){
    return m_label;
}
int CVariableMeasure::toInt(){
    return m_measure->toInt();
}
float CVariableMeasure::toFloat(){
    return m_measure->toFloat();
}
bool CVariableMeasure::toBool(){
    return m_measure->toBool();
}
QVariant CVariableMeasure::toVariant(){
        return m_measure->toVariant();
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
