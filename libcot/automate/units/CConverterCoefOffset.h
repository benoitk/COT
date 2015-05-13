#ifndef CConverterCoefOffset_H
#define CConverterCoefOffset_H

#include "IConverter.h"
#include <QObject>

class CUnit;
class CConverterCoefOffset : public QObject, public IConverter
{
    Q_OBJECT

public:
    CConverterCoefOffset(const QVariantMap &);
    ~CConverterCoefOffset();

    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;
    CUnit* getTarget()const Q_DECL_OVERRIDE;

private:
    float m_offset;
    float m_coef;
    CUnit* m_targetUnit;
};

#endif // CConverterCoefOffset_H
