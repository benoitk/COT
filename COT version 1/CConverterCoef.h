#ifndef CCONVERTERCOEF_H
#define CCONVERTERCOEF_H

#include <QObject>
#include "IConverter.h"

class CConverterCoef : public QObject, public IConverter
{
	Q_OBJECT

public:
	CConverterCoef(QVariantMap);
	~CConverterCoef();

	QVariant convert(const QVariant);


private:
	float m_coef;
};

#endif // CCONVERTERCOEF_H
