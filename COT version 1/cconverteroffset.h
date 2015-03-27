#ifndef CCONVERTEROFFSET_H
#define CCONVERTEROFFSET_H

#include "IConverter.h"

#include <QObject>

class CConverterOffset : public QObject, public IConverter
{
	Q_OBJECT

public:
	CConverterOffset(QVariantMap);
	~CConverterOffset();
	QVariant convert(const QVariant);

private:
	float m_offset;
};

#endif // CCONVERTEROFFSET_H
