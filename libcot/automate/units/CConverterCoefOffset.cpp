#include "CConverterCoefOffset.h"

CCOnverterCoefOffset::CCOnverterCoefOffset(const QVariantMap &variantMap)
	: QObject()
{
	m_coef = 1;
	m_offset = 0;
}

CCOnverterCoefOffset::~CCOnverterCoefOffset()
{

}

QVariant CCOnverterCoefOffset::convert(const QVariant &valueToConvert){
	float value = valueToConvert.toFloat();
	value *= m_coef;
	value += m_offset;
	QVariant result(value);
	return result;
}
CUnit* CCOnverterCoefOffset::getTarget()const{
    return m_targetUnit;
}