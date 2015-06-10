#include "CVariableBool.h"
#include "CUnit.h"

#include "qdebug.h"
CVariableBool::CVariableBool(QObject *parent)
    : IVariable(parent)

{

}
CVariableBool::CVariableBool(const QVariantMap& mapVar):IVariable(mapVar){
    m_bValeur = mapVar.value(QStringLiteral("value")).toBool();
}

CVariableBool::CVariableBool(bool arg_value, int arg_address, variableAccess arg_access)
    : IVariable()
{
    m_bValeur = arg_value;
    m_access = arg_access;
    m_address = arg_address;
}


CVariableBool::~CVariableBool()
{

}


QString CVariableBool::toString(){
    if(m_bValeur)
        return tr("vrai");
    else
        return tr("faux");
}
int CVariableBool::toInt(){
    return m_bValeur;
}
float CVariableBool::toFloat(){
    return m_bValeur;
}
bool CVariableBool::toBool(){
    return m_bValeur;
}

void CVariableBool::setValue(const QVariant & value){
    setValue(value.toBool());
}
void CVariableBool::setValue(bool value){
    m_bValeur = value;
    if(!m_listBinds.isEmpty()){
        IVariable* var;
        foreach(var,  m_listBinds){
            var->setToBindedValue(QVariant(value));
        }
    }

    emit signalVariableChanged();
}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableBool::setToBindedValue(const QVariant & value){
    m_bValeur = value.toBool();
}
variableType CVariableBool::getType()const{
    return type_bool;
}

QVariantMap CVariableBool::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_bValeur);
    return mapSerialise;
}

void CVariableBool::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_bValeur));
    if(!var.isNull())
        m_bValeur = var.toBool();
    m_unit = targetUnit;
}
QVariant CVariableBool::toVariant() {
    return toFloat();
}
