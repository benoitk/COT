#ifndef CCONVERTEROFFSET_H
#define CCONVERTEROFFSET_H

#include "IConverter.h"

#include <QObject>

class CUnit;
class CConverterOffset : public QObject, public IConverter
{
    Q_OBJECT

public:
    CConverterOffset(const QVariantMap &);
    ~CConverterOffset();
    QVariant convert(const QVariant &) Q_DECL_OVERRIDE;
    CUnit* getTarget()const Q_DECL_OVERRIDE;

private:
    float m_offset;
    CUnit* m_targetUnit;
};

#endif // CCONVERTEROFFSET_H
