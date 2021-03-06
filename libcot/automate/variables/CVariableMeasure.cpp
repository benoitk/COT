#include "CVariableMeasure.h"
#include "CAutomate.h"
#include "IVariable.h"

#include "CUnit.h"
#include "qlinkedlist.h"

#define QSL QStringLiteral

CVariableMeasure::CVariableMeasure(CAutomate* arg_automate, QObject *parent)
    :IVariable(arg_automate, parent)
{
}
CVariableMeasure::CVariableMeasure(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject *parent)
    :IVariable(arg_automate, parent)
{
    m_name = mapVar.value(QSL("name")).toString();
    if (m_name.isEmpty())
        m_name = QSL("Stream unamed");

    m_label = mapVar.value(tr("en_US")).toString();
    if (m_label.isEmpty())
        m_label = tr("Stream no label");

    m_measure = m_automate->getVariable(mapVar.value(QSL("variable_measure")).toString());
    m_measureMax = m_automate->getVariable(mapVar.value(QSL("variable_range_max")).toString());
    m_measureMin = m_automate->getVariable(mapVar.value(QSL("variable_range_min")).toString());

    QVariantList listVariable = mapVar.value(QStringLiteral("variables")).toList();
    foreach(const QVariant &variant, listVariable){
        m_listVariables.append(m_automate->getVariable(variant.toString()));
    }
}
IVariable* CVariableMeasure::getMeasureMax(){
    return m_measureMax;
}
IVariable* CVariableMeasure::getMeasureMin(){
    return m_measureMin;
}

bool CVariableMeasure::removeVariable(IVariable *ivar)
{
    const bool result = m_listVariables.removeOne(ivar);

    if (result) {
        emit signalVariableChanged(this);
    }

    return result;
}
bool CVariableMeasure::addVariable(IVariable *ivar){
    bool result = !m_listVariables.contains(ivar);

    if (result) {
        m_listVariables.append(ivar);
        emit signalVariableChanged(this);
    }

    return result;
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
    if(m_measure->toInt() > m_measureMax->toInt())
        return m_measureMax->toInt();
    if(m_measure->toInt() < m_measureMin->toInt())
        return m_measureMin->toInt();
    return m_measure->toInt();
}
float CVariableMeasure::toFloat(){
    if(m_measure->toFloat() > m_measureMax->toFloat())
        return m_measureMax->toFloat();
    if(m_measure->toFloat() < m_measureMin->toFloat())
        return m_measureMin->toFloat();
    return m_measure->toFloat();

}
bool CVariableMeasure::toBool(){
    return m_measure->toBool();
}
QVariant CVariableMeasure::toVariant(){
    if(m_measure->toVariant() > m_measureMax->toVariant())
        return m_measureMax->toVariant();
    if(m_measure->toVariant() < m_measureMin->toVariant())
        return m_measureMin->toVariant();
    return m_measure->toVariant();
}

void CVariableMeasure::setValue(int iValue){
}
void CVariableMeasure::setValue(const QVariant & value){
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableMeasure::setToBindedValue(const QVariant & value){

}
enumVariableType CVariableMeasure::getType()const{
    return e_type_measure;
}
void CVariableMeasure::switchToUnit(CUnit* targetUnit){

}

QVariantMap CVariableMeasure::serialize(){
   QVariantMap mapSerialise = IVariable::serialize();

    mapSerialise.insert(QStringLiteral("variable_measure"), m_measure->getName());
    mapSerialise.insert(QStringLiteral("variable_range_max"), m_measureMax->getName());
    mapSerialise.insert(QStringLiteral("variable_range_min"), m_measureMin->getName());
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("measure"));
    QList<QVariant> listVars;
    foreach(IVariable* var, m_listVariables){
        listVars.append(var->getName());
    }
    mapSerialise.insert(QStringLiteral("variables"), listVars);

    return mapSerialise;
}
