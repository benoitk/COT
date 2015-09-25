#ifndef CCONVERTERCROSSPRODUCT_H
#define CCONVERTERCROSSPRODUCT_H

#include <QObject>
#include "IConverter.h"

class CUnit;
class CConverterCrossProduct : public QObject, public IConverter
{
    Q_OBJECT
public:
    explicit CConverterCrossProduct(const QVariantMap &);


    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;
    CUnit* getTarget()const Q_DECL_OVERRIDE;
    QVariantMap serialize()Q_DECL_OVERRIDE;

private:
    float m_coef;
    float m_divisor;
    CUnit* m_targetUnit;
};

#endif // CCONVERTERCROSSPRODUCT_H
