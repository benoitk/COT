#include "CVariableInt.h"
#include "CUnit.h"

CVariableInt::CVariableInt(CAutomate* arg_automate, QObject *parent)
    : IVariable(arg_automate, parent)
    , m_value(-1)
{

}

CVariableInt::CVariableInt(const QVariantMap& mapVar, CAutomate* arg_automate, QObject* parent)
    :IVariable(mapVar, arg_automate, parent)
{
    m_value = mapVar.value(QStringLiteral("value")).toInt();
    m_valueMin = mapVar.value(QStringLiteral("value_min")).toInt();
    m_valueMax = mapVar.value(QStringLiteral("value_max")).toInt();
}
CVariableInt::CVariableInt(CAutomate* arg_automate, QObject *parent, int arg_int, int arg_address, enumVariableAccess arg_access)
    : IVariable(arg_automate, parent)
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
    m_value = IVariable::setValue(value, m_valueMin, m_valueMax);
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

enumVariableType CVariableInt::getType()const{
    return e_type_int;
}
void CVariableInt::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_value));
    if(!var.isNull())
        m_value = var.toFloat();
    m_unit = targetUnit;
}

QVariantMap CVariableInt::serialize(){
   QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("integer"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("value_min"), m_valueMin);
    mapSerialise.insert(QStringLiteral("value_max"), m_valueMax);
    return mapSerialise;
}
QVariant CVariableInt::toVariant(){
    return toInt();
}
