#ifndef CCONVERTEROFFSETCOEF_H
#define CCONVERTEROFFSETCOEF_H

#include "IConverter.h"
#include <QObject>

class CConverterOffsetCoef : public QObject, public IConverter 
{
	Q_OBJECT

public:
	CConverterOffsetCoef(QVariantMap);
	~CConverterOffsetCoef();

	QVariant convert(const QVariant);

private:
	float m_offset;
	float m_coef;
};

#endif // CCONVERTEROFFSETCOEF_H
