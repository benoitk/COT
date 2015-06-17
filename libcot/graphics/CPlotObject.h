#ifndef CPLOTOBJECT_H
#define CPLOTOBJECT_H

#include <kplotobject.h>

class CPlotObject : public KPlotObject
{
public:
    CPlotObject();
    ~CPlotObject();

    void addValue(int x, float value);
};

#endif // CPLOTOBJECT_H
