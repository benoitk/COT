#include "CVariableUnknow.h"
#include "CUnit.h"
#include "qlinkedlist.h"
CVariableUnknow::CVariableUnknow()
    : IVariable()
{
    m_name = QStringLiteral("unknown_var");
    m_label = tr("Type unknow variable ");
}
CVariableUnknow::CVariableUnknow(const QVariantMap& mapVar)
    :IVariable(mapVar){
    m_label = m_label + tr("Type unknow ") + mapVar.value(QStringLiteral("type")).toString();
}
CVariableUnknow::~CVariableUnknow()
{

}


QString CVariableUnknow::toString(){
    return tr("Unknow variable");
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
QVariant CVariableUnknow::toVariant(){
    return tr("Unknow variable");
}
void CVariableUnknow::setValue(const QVariant &){
}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableUnknow::setToBindedValue(const QVariant & value){
}
enumVariableType CVariableUnknow::getType()const{
    return e_type_unknow;
}
void CVariableUnknow::switchToUnit(CUnit* targetUnit){

}

QVariantMap CVariableUnknow::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("unserialized"), QStringLiteral("CVariableUnknow"));
    return mapSerialise;
}

