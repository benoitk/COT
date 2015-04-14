#ifndef CCONVERTERCOEF_H
#define CCONVERTERCOEF_H

#include <QObject>
#include "IConverter.h"

class CConverterCoef : public QObject, public IConverter
{
	Q_OBJECT

public:
    CConverterCoef(const QVariantMap &);
	~CConverterCoef();

    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;


private:
	float m_coef;
};

#endif // CCONVERTERCOEF_H
