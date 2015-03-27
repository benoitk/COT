#include "CConverterCoef.h"

CConverterCoef::CConverterCoef(QVariantMap variantMap):QObject()
{
	m_coef = 1;
}

CConverterCoef::~CConverterCoef()
{

}

QVariant CConverterCoef::convert(const QVariant valueToConvert){
	float value = valueToConvert.toFloat();
	value *= m_coef;
	QVariant result(value);
	return result;
}

