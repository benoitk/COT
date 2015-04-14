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

