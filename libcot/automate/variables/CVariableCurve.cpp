#include "CVariableCurve.h"

#include "CUnit.h"

#include "qdebug.h"
CVariableCurve::CVariableCurve(CAutomate* arg_automate, QObject *parent)
    : IVariable(arg_automate, parent)

{

}
CVariableCurve::CVariableCurve(const QVariantMap& mapVar,CAutomate* arg_automate, QObject* parent)
    :IVariable(mapVar, arg_automate, parent){
    QVariantList listPair = mapVar.value(QStringLiteral("values")).toList();
    foreach (QVariant variantPair, listPair) {
        QVariantMap mapPair = variantPair.toMap();
        const QPair<float, float> pair(mapPair.value("x").toFloat(), mapPair.value("y").toFloat());
        m_listCurve.append(pair);
    }

}
float CVariableCurve::getLiearisedY(float arg_x){
    QPair<float, float> pair;
    float value;
    for(int i=0; i< m_listCurve.count(); ++i){
        if( (i == 0 && arg_x < m_listCurve.at(i).first) || arg_x == m_listCurve.at(i).first ){
            value = m_listCurve.at(i).second;
            break;
        }
        else if(arg_x < m_listCurve.at(i).first && i != 0){
            value = (m_listCurve.at(i).second / m_listCurve.at(i).first) * (arg_x - m_listCurve.at(i-1).first) + m_listCurve.at(i-1).second;
            break;
        }
    }
    return value;
}

//linéarisation inverse
float CVariableCurve::getLiearisedX(float arg_y){
    return 0;
}


CVariableCurve::CVariableCurve(CAutomate* arg_automate, QObject *parent, bool arg_value, int arg_address, enumVariableAccess arg_access)
    : IVariable(arg_automate, parent)
{

    m_access = arg_access;
    m_address = arg_address;
}


CVariableCurve::~CVariableCurve()
{

}


QString CVariableCurve::toString(){
            return m_label;
}
int CVariableCurve::toInt(){
    return 0;
}
float CVariableCurve::toFloat(){
    return 0;
}
bool CVariableCurve::toBool(){
    return 0;
}

void CVariableCurve::setValue(const QVariant & value){
    this->setValue(value.toBool());
}
void CVariableCurve::setValue(float x, float y){

    //checkBindedVariable(QVariant(value));

    emit signalVariableChanged(this);
}

//Pas de récursivité dans les binds pour l'instant pour ne pas gérer les binds croisés({var1, var2}, {var2, var1})
void CVariableCurve::setToBindedValue(const QVariant & value){

    emit signalVariableChanged(this);
}
enumVariableType CVariableCurve::getType()const{
    return e_type_curve;
}

QVariantMap CVariableCurve::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("curve"));
    QVariantList listPair;
    QPair<float, float> pair;
    foreach(pair, m_listCurve){
        QVariantMap mapPair;
        mapPair.insert("x", pair.first);
        mapPair.insert("y", pair.second);
        listPair.append(mapPair);
    }

    mapSerialise.insert(QStringLiteral("values"), listPair);
    return mapSerialise;
}

void CVariableCurve::switchToUnit(CUnit* targetUnit){
//    QVariant var = m_unit->convert(targetUnit->getName(), QVariant(m_value));
//    if(!var.isNull())
//        m_value = var.toBool();
//    m_unit = targetUnit;
}
QVariant CVariableCurve::toVariant() {
    return toFloat();
}
