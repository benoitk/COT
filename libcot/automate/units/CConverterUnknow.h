#ifndef CCONVERTERUNKNOW_H
#define CCONVERTERUNKNOW_H

#include "IConverter.h"
#include <QObject>


class CUnit;
class CConverterUnknow : public QObject, public IConverter
{
    Q_OBJECT
public:
    CConverterUnknow();
    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;
    CUnit* getTarget()const Q_DECL_OVERRIDE;

private:
    CUnit* m_targetUnit;
};

#endif // CCONVERTERUNKNOW_H
