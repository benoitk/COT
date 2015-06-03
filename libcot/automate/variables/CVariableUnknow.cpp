#include "CVariableUnknow.h"
#include "CUnit.h"
#include "qlinkedlist.h"
CVariableUnknow::CVariableUnknow()
    : IVariable()
{

}

CVariableUnknow::~CVariableUnknow()
{

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
QVariant CVariableUnknow::toVariant(){
    return tr("Variable inconnu");
}
void CVariableUnknow::setValue(const QVariant &){
}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableUnknow::setToBindedValue(const QVariant & value){
}
variableType CVariableUnknow::getType()const{
    return type_unknow;
}
void CVariableUnknow::switchToUnit(CUnit* targetUnit){

}

QVariantMap CVariableUnknow::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("unserialized"), QStringLiteral("CVariableUnknow"));
    return mapSerialise;
}

