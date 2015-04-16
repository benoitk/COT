#include "CConverterUnknow.h"
#include "CUnit.h"

CConverterUnknow::CConverterUnknow(){
    m_targetUnit = new CUnit(this);
}
QVariant CConverterUnknow::convert(const QVariant &valueToConvert){
    QVariant result(QStringLiteral("Converter Unknow"));
	return result;
}
CUnit* CConverterUnknow::getTarget()const{
    return m_targetUnit;
}