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