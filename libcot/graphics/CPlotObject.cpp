#include "CPlotObject.h"

#include <QPen>
#include <QDebug>

extern int s_maxPointsInCurve; // see CGraphicsWidget.cpp

CPlotObject::CPlotObject(const QColor &col)
    : KPlotObject(col)
{
    setShowLines(true);
}

CPlotObject::~CPlotObject()
{
}

void CPlotObject::addValue(int x, float value)
{
    if (x >= s_maxPointsInCurve) {
        removePoint(0);
    }
    //qCDebug(COTGUI_LOG) << "addPoint" << QPointF(x, value);
    addPoint(QPointF(x, value));
}

QColor CPlotObject::createNewColor()
{
    static int lastHue = 0;
    lastHue = (lastHue + 149) % 360;
    return QColor::fromHsv(lastHue, 255, 200);
}
