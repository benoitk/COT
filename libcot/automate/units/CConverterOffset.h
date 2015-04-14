#ifndef CCONVERTEROFFSET_H
#define CCONVERTEROFFSET_H

#include "IConverter.h"

#include <QObject>

class CConverterOffset : public QObject, public IConverter
{
	Q_OBJECT

public:
    CConverterOffset(const QVariantMap &);
	~CConverterOffset();
    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;

private:
	float m_offset;
};

#endif // CCONVERTEROFFSET_H
