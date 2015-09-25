#include "CConverterOffsetCoef.h"

CConverterOffsetCoef::CConverterOffsetCoef(const QVariantMap &variantMap)
    : QObject()
{
    m_coef = 1;
    m_offset = 0;
}

CConverterOffsetCoef::~CConverterOffsetCoef()
{

}

QVariant CConverterOffsetCoef::convert(const QVariant &valueToConvert){
    float value = valueToConvert.toFloat();
    value += m_offset;
    value *= m_coef;
    QVariant result(value);
    return result;
}

CUnit* CConverterOffsetCoef::getTarget()const{
    return m_targetUnit;
}

QVariantMap CConverterOffsetCoef::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_targetUnit->getName());
    mapSerialise.insert(QStringLiteral("coef"), m_coef);
    mapSerialise.insert(QStringLiteral("offset"), m_offset);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("offset_coef"));
    return mapSerialise;
}
