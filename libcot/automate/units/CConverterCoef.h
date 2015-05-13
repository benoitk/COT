#ifndef CCONVERTERCOEF_H
#define CCONVERTERCOEF_H

#include <QObject>
#include "IConverter.h"

class CUnit;
class CConverterCoef : public QObject, public IConverter
{
    Q_OBJECT

public:
    CConverterCoef(const QVariantMap &);
    ~CConverterCoef();

    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;
    CUnit* getTarget()const Q_DECL_OVERRIDE;


private:
    float m_coef;
    CUnit* m_targetUnit;
};

#endif // CCONVERTERCOEF_H
