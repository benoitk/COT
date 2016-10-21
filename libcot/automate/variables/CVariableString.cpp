#include "CVariableString.h"
#include "CUnit.h"


CVariableString::CVariableString(CAutomate* arg_automate, QObject *parent)
    : IVariable(arg_automate, parent)
{

}
CVariableString::CVariableString(const QString &arg_value, CAutomate* arg_automate, QObject* parent)
    : IVariable(arg_automate, parent)
{
    m_sValeur = arg_value;
}
CVariableString::CVariableString(const QVariantMap& mapVar, CAutomate* arg_automate, QObject* parent)
    :IVariable(mapVar, arg_automate, parent)
{
    m_sValeur = mapVar.value(QStringLiteral("value")).toString();
}
CVariableString::~CVariableString()
{

}

QString CVariableString::toString(){
    return m_sValeur;
}
int CVariableString::toInt(){
    return m_sValeur.toInt();
}
float CVariableString::toFloat(){
    return m_sValeur.toFloat();
}
bool CVariableString::toBool(){
    if(m_sValeur == tr("true"))    return true;
    else if(m_sValeur == tr("false")) return false;
    else return m_sValeur.toInt();
}
QVariant CVariableString::toVariant(){
    return QVariant(m_sValeur);
}
void CVariableString::setValue(const QVariant & value){
    setValue(value.toString());
}
void CVariableString::setValue(QString value){
    m_sValeur = value;
    checkBindedVariable(QVariant(value));

    emit signalVariableChanged(this);
}
//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableString::setToBindedValue(const QVariant & value){
    m_sValeur = value.toString();

    emit signalVariableChanged(this);
}

enumVariableType CVariableString::getType()const{
    return e_type_string;
}
void CVariableString::switchToUnit(CUnit* targetUnit){
    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_sValeur));
    if(!var.isNull())
        m_sValeur = QString::number(var.toFloat());
    m_unit = targetUnit;
}

QVariantMap CVariableString::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("string"));
    mapSerialise.insert(QStringLiteral("value"), m_sValeur);
    return mapSerialise;
}
