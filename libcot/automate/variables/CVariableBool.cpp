#include "CVariableBool.h"
#include "CUnit.h"

#include "qdebug.h"
CVariableBool::CVariableBool(CAutomate* arg_automate, QObject *parent)
    : IVariable(arg_automate, parent)

{

}
CVariableBool::CVariableBool(const QVariantMap& mapVar,CAutomate* arg_automate, QObject* parent)
    :IVariable(mapVar, arg_automate, parent)
{
    m_value = mapVar.value(QStringLiteral("value")).toBool();
    m_defaultValue = m_value;
}

CVariableBool::CVariableBool(CAutomate* arg_automate, QObject *parent,bool arg_value, int arg_address, enumVariableAccess arg_access)
    : IVariable(arg_automate, parent){
    m_value = arg_value;
    m_access = arg_access;
    m_address = arg_address;
}


CVariableBool::~CVariableBool(){

}


QString CVariableBool::toString(){
    if(m_value)
        return tr("true");
    else
        return tr("false");
}
int CVariableBool::toInt(){
    return m_value;
}
float CVariableBool::toFloat(){
    return m_value;
}
bool CVariableBool::toBool(){
    return m_value;
}

void CVariableBool::setValue(const QVariant & value){
    this->setValue(value.toBool());
}

void CVariableBool::setValue(bool value){
    if(m_value != value){
        m_value = value;
        checkBindedVariable(QVariant(value));
        emit signalVariableChanged(this);
    }
}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableBool::setToBindedValue(const QVariant & value){
    if(m_value != value.toBool()){
        m_value = value.toBool();
        emit signalVariableChanged(this);
    }
}

enumVariableType CVariableBool::getType()const{
    return e_type_bool;
}

QVariantMap CVariableBool::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_defaultValue);
    return mapSerialise;
}

void CVariableBool::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_value));
    if(!var.isNull())
        m_value = var.toBool();
    m_unit = targetUnit;
}
QVariant CVariableBool::toVariant() {
    return toFloat();
}
