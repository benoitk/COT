#ifndef CCONVERTERCOEFOFFSET_H
#define CCONVERTERCOEFOFFSET_H

#include "IConverter.h"
#include <QObject>

class CUnit;
class CCOnverterCoefOffset : public QObject, public IConverter
{
	Q_OBJECT

public:
    CCOnverterCoefOffset(const QVariantMap &);
	~CCOnverterCoefOffset();

    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;
    CUnit* getTarget()const Q_DECL_OVERRIDE;

private:
	float m_offset;
	float m_coef;
    CUnit* m_targetUnit;
};

#endif // CCONVERTERCOEFOFFSET_H
