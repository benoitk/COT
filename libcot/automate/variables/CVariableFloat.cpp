#include "CVariableFloat.h"
#include "CUnit.h"
CVariableFloat::CVariableFloat(QObject *parent)
    : IVariable(parent)
{

}
CVariableFloat::CVariableFloat(const QVariantMap& mapVar):IVariable(mapVar){
    m_value = mapVar.value(QStringLiteral("value")).toFloat();
}
CVariableFloat::CVariableFloat(float arg_value, int arg_address, variableAccess arg_access)
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
    return QString::number(m_value, 'f', IVariable::FLOAT_PRECISION);
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
    m_value = value;
    checkBindedVariable(QVariant(value));

    emit signalVariableChanged();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableFloat::setToBindedValue(const QVariant & value){
    m_value = value.toFloat();

    emit signalVariableChanged();
}

variableType CVariableFloat::getType()const{
    return type_float;
}
void CVariableFloat::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_value));
    if(!var.isNull())
        m_value = var.toFloat();
    m_unit = targetUnit;
}

QVariantMap CVariableFloat::serialise(){
     QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("float"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    return mapSerialise;
}

 QVariant CVariableFloat::toVariant() {
     return toFloat();
 }
int CVariableFloat::getPrecision(){
    //TO DO : mettre la precision en donnée membre
    return  IVariable::FLOAT_PRECISION;
}
