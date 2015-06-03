#include "CVariableFloat.h"
#include "CUnit.h"
CVariableFloat::CVariableFloat(QObject *parent)
    : IVariable(parent)
{

}
CVariableFloat::CVariableFloat(float arg_value, int arg_address, variableAccess arg_access)
    : IVariable()
{
    m_fValeur = arg_value;
    m_access = arg_access;
    m_address = arg_address;
}
CVariableFloat::~CVariableFloat()
{

}

QString CVariableFloat::toString(){
    return QString::number(m_fValeur, 'f', IVariable::FLOAT_PRECISION);
}
int CVariableFloat::toInt(){
    return m_fValeur;
}
float CVariableFloat::toFloat(){
    return m_fValeur;
}
bool CVariableFloat::toBool(){
    return m_fValeur;
}
void CVariableFloat::setValue(const QVariant & value){
    setValue(value.toFloat());
}
void CVariableFloat::setValue(float value){
    m_fValeur = value;
    if(!m_listBinds.isEmpty()){
        IVariable* var;
        foreach(var,  m_listBinds){
            var->setValue(QVariant(value));
        }
    }

    emit signalVariableChanged();
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableFloat::setToBindedValue(const QVariant & value){
    m_fValeur = value.toFloat();
}

variableType CVariableFloat::getType()const{
    return type_float;
}
void CVariableFloat::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_fValeur));
    if(!var.isNull())
        m_fValeur = var.toFloat();
    m_unit = targetUnit;
}

QVariantMap CVariableFloat::serialise(){
     QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("float"));
    mapSerialise.insert(QStringLiteral("value"), m_fValeur);
    return mapSerialise;
}

 QVariant CVariableFloat::toVariant() {
     return toFloat();
 }

