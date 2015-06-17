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

    /*
     * Clear the graphic and remove hash list
     */
    void clear();

    /**
     * High-level
     * Create or update a curve based on measurename
     * If measurename doesn't exist this function will create a new curve
     * otherwise it will update curve data
     */
    void addOrUpdateCurve(float value, const QString &mesureName);

    /**
     * High-level
     * Updates X for next time and recalculates limits
     */
    void doneUpdatingPlotting();

    /**
     * Low-level
     * Updates X for next time and recalculates limits
     */
    void addPoint(float value, CPlotObject *curve);

    /**
     * Low-level
     * Ensure plot object is shown (TODO remove)
     */
    void showPlotObject(CPlotObject *object);

private:
    void changeLimits(double x1, double x2, double y1, double y2);
    void initializeGraphic();
    int m_x;
    int m_verticalMaximumValue;
    KPlotWidget *m_plotWidget;
    QHash<QString, CPlotObject *> m_plotObjectHash;
};

#endif // CGRAPHICSWIDGET_H
