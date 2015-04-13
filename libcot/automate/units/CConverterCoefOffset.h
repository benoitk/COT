#ifndef CCONVERTERCOEFOFFSET_H
#define CCONVERTERCOEFOFFSET_H

#include "IConverter.h"
#include <QObject>

class CCOnverterCoefOffset : public QObject, public IConverter
{
	Q_OBJECT

public:
	CCOnverterCoefOffset(QVariantMap);
	~CCOnverterCoefOffset();

	QVariant convert(const QVariant);

private:
	float m_offset;
	float m_coef;
};

#endif // CCONVERTERCOEFOFFSET_H
