#ifndef ICONVERTER_H
#define ICONVERTER_H

#include "qvariant.h"

class IConverter
{


public:
    virtual QVariant convert(const QVariant &)=0;
    virtual CUnit* getTarget()const=0;

private:
	
};

#endif // ICONVERTER_H
