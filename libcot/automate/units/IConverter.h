#ifndef ICONVERTER_H
#define ICONVERTER_H

#include "qvariant.h"

class CUnit;
class IConverter
{
public:
    virtual ~IConverter() {}
    virtual QVariant convert(const QVariant &)=0;
    virtual CUnit* getTarget()const=0;

private:

};

#endif // ICONVERTER_H
