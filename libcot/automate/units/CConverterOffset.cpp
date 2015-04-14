#include "CConverterOffset.h"

CConverterOffset::CConverterOffset(const QVariantMap &variantMap)
	: QObject()
{
	m_offset = 0;
}

CConverterOffset::~CConverterOffset()
{

}
QVariant CConverterOffset::convert(const QVariant &valueToConvert){
	float value = valueToConvert.toFloat();
	value += m_offset;
	QVariant result(value);
	return result;
}

