#include "CConverterCoef.h"

CConverterCoef::CConverterCoef(const QVariantMap &variantMap):QObject()
{
    m_coef = 1;
}

CConverterCoef::~CConverterCoef()
{

}

QVariant CConverterCoef::convert(const QVariant &valueToConvert){
    float value = valueToConvert.toFloat();
    value *= m_coef;
    QVariant result(value);
    return result;
}

CUnit* CConverterCoef::getTarget()const{
    return m_targetUnit;
}

QVariantMap CConverterCoef::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_targetUnit->getName());
    mapSerialise.insert(QStringLiteral("coef"), m_coef);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("coef"));
    return mapSerialise;
}

