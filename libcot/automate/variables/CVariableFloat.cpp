#include "CVariableFloat.h"
#include "CUnit.h"
CVariableFloat::CVariableFloat(QObject *parent)
    : IVariable(parent)
{

}
CVariableFloat::CVariableFloat(const QVariantMap& mapVar):IVariable(mapVar){
    m_value = mapVar.value(QStringLiteral("value")).toFloat();
    m_valueMin = mapVar.value(QStringLiteral("value_min")).toFloat();
    m_valueMax = mapVar.value(QStringLiteral("value_max")).toFloat();
    if(mapVar.contains(QStringLiteral("precision")))
        m_precision = mapVar.value(QStringLiteral("precision")).toInt();
    else
        m_precision = 2;
}
CVariableFloat::CVariableFloat(float arg_value, int arg_address, enumVariableAccess arg_access)
    : IVariable()
{
    m_value = arg_value;
    m_access = arg_access;
    m_address = arg_address;
}
CVariableFloat::~CVariableFloat()
{

}

QString CVariableFloat::toString(){
    // ## this doesn't handle the locale, and always has trailing zeros.
    // consider moving the code from CNumericalKeyboardWidget::formatDouble here.
    return QString::number(m_value, 'f', m_precision);
}
int CVariableFloat::toInt(){
    return m_value;
}
float CVariableFloat::toFloat(){
    return m_value;
}
bool CVariableFloat::toBool(){
    return m_value;
}
void CVariableFloat::setValue(const QVariant & value){
    setValue(value.toFloat());
}
void CVariableFloat::setValue(float value){
    m_value = IVariable::setValue(value, m_valueMin, m_valueMax);

    checkBindedVariable(QVariant(value));

    emit signalVariableChanged(this);
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableFloat::setToBindedValue(const QVariant & value){
    m_value = value.toFloat();

    emit signalVariableChanged(this);
}

enumVariableType CVariableFloat::getType()const{
    return e_type_float;
}
void CVariableFloat::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_value));
    if(!var.isNull())
        m_value = var.toFloat();
    m_unit = targetUnit;
}

QVariantMap CVariableFloat::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("float"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("value_min"), m_valueMin);
    mapSerialise.insert(QStringLiteral("value_max"), m_valueMax);
    return mapSerialise;
}

 QVariant CVariableFloat::toVariant() {
     return toFloat();
 }
int CVariableFloat::getPrecision(){
    //TO DO : mettre la precision en donnée membre
    return  IVariable::FLOAT_PRECISION;
}
