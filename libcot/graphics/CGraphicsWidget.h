#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

#include <QWidget>
#include <QDateTime>
#include "cot_global.h"

class KPlotWidget;
class CPlotObject;
class LIBCOT_EXPORT CGraphicsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CGraphicsWidget(QWidget *parent = Q_NULLPTR);
    ~CGraphicsWidget();

    /**
     * Ensure plot object is shown (as the single plot object)
     */
    void showPlotObject(CPlotObject *object);

    /**
     * Add plot object
     */
    void addPlotObject(CPlotObject *object);

    /**
     * Updates X for next time and recalculates limits
     */
    void addPoint(float value, CPlotObject *curve);

    /**
     * Updates X for next time and recalculates limits
     */
    void doneUpdatingPlotting();

private:
    void changeLimits(double x1, double x2, double y1, double y2);
    void initializeGraphic();
    int m_x;
    int m_verticalMaximumValue;
    KPlotWidget *m_plotWidget;
};

#endif // CGRAPHICSWIDGET_H
