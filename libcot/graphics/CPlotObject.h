#ifndef CPLOTOBJECT_H
#define CPLOTOBJECT_H

#include <kplotobject.h>
#include "cot_global.h"

class LIBCOT_EXPORT CPlotObject : public KPlotObject
{
public:
    CPlotObject(const QColor &col);
    ~CPlotObject();

    void addValue(int x, float value);

    static QColor createNewColor();

};

#endif // CPLOTOBJECT_H
