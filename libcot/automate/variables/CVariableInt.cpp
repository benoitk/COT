#include "CVariableInt.h"
#include "CUnit.h"

CVariableInt::CVariableInt(QObject *parent)
    : IVariable(parent)
    , m_value(-1)
{

}

CVariableInt::CVariableInt(const QVariantMap& mapVar):IVariable(mapVar){
    m_value = mapVar.value(QStringLiteral("value")).toInt();
}
CVariableInt::CVariableInt(int arg_int, int arg_address, variableAccess arg_access)
    : IVariable()
{
    m_value = arg_int;
    m_access = arg_access;
    m_address = arg_address;
}
CVariableInt::~CVariableInt()
{

}

QString CVariableInt::toString(){
    return QString::number(m_value);
}
int CVariableInt::toInt(){
    return m_value;
}
float CVariableInt::toFloat(){
    return m_value;
}
bool CVariableInt::toBool(){
    return m_value;
}
void CVariableInt::setValue(int value){
    m_value = value;
    checkBindedVariable(QVariant(value));

    emit signalVariableChanged(this);
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableInt::setToBindedValue(const QVariant & value){
    m_value = value.toInt();

    emit signalVariableChanged(this);
}
void CVariableInt::setValue(const QVariant & value){
    setValue(value.toInt());
}

variableType CVariableInt::getType()const{
    return type_int;
}
void CVariableInt::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_value));
    if(!var.isNull())
        m_value = var.toFloat();
    m_unit = targetUnit;
}

QVariantMap CVariableInt::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("integer"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    return mapSerialise;
}
QVariant CVariableInt::toVariant(){
    return toInt();
}
