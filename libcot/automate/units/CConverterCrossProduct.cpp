#include "CConverterCrossProduct.h"

CConverterCrossProduct::CConverterCrossProduct(const QVariantMap &variantMap) : QObject()
{
    m_coef = variantMap.value(QStringLiteral("coef")).toFloat();
    m_divisor = variantMap.value(QStringLiteral("divisor")).toFloat();

}

QVariant CConverterCrossProduct::convert(const QVariant &valueToConvert){
    float value = valueToConvert.toFloat();
    value *= m_coef;
    value /= m_divisor;
    QVariant result(value);
    return result;
}

CUnit* CConverterCrossProduct::getTarget()const{
    return m_targetUnit;
}


