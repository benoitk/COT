#include "CPlotObject.h"

#include <QPen>
#include <QDebug>

extern int s_maxPointsInCurve; // see CGraphicsWidget.cpp

static QColor createNewColor()
{
    const QColor col = QColor::fromHsv(qrand() % 360, 255, 200);
    return col;
}

CPlotObject::CPlotObject()
{
    setShowLines(true);
    const QColor col = createNewColor();
    QPen pen(col);
    setLinePen(pen);
    setPen(pen);
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
