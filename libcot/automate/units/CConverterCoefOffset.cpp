#include "CConverterCoefOffset.h"

CConverterCoefOffset::CConverterCoefOffset(const QVariantMap &variantMap)
    : QObject()
{
    m_coef = 1;
    m_offset = 0;
}

CConverterCoefOffset::~CConverterCoefOffset()
{

}

QVariant CConverterCoefOffset::convert(const QVariant &valueToConvert){
    float value = valueToConvert.toFloat();
    value *= m_coef;
    value += m_offset;
    QVariant result(value);
    return result;
}
CUnit* CConverterCoefOffset::getTarget()const{
    return m_targetUnit;
}

QVariantMap CConverterCoefOffset::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_targetUnit->getName());
    mapSerialise.insert(QStringLiteral("coef"), m_coef);
    mapSerialise.insert(QStringLiteral("offset"), m_offset);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("coef_offset"));
    return mapSerialise;
}
