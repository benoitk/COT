#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

#include <QWidget>
#include <QDateTime>
#include "cot_global.h"

class KPlotWidget;
class KPlotObject;
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

    /*
     * Change graphics limit.
     */
    void changeLimits(double x1, double x2, double y1, double y2);

    /*
     * Add a new curve to graphics and return curve object
     */
    KPlotObject *addCurve(const QList<QPointF> &listPoints, const QString &measureName = QString(), const QColor &col = QColor());

    /*
     * Create or update a curve based on measurename
     * If measurename doesn't exist this function will create a new curve
     * otherwise it will update curve data
     */
    void addOrUpdateCurve(const QList<QPointF> &listPoints, const QString &measureName);

    /*
     * Create or update a curve based on measurename
     * If measurename doesn't exist this function will create a new curve
     * otherwise it will update curve data
     * It will add a new Y value (X is based on QDateTime).
     */
    void addOrUpdateCurve(float value, const QString &mesureName);

    /*
     * Generate new randow color
     */
    static QColor createNewColor();
private:
    KPlotObject *addCurve(double value, const QString &measureName, const QColor &col);
    void addPoint(float value, const QString &measureName, KPlotObject *curve);
    void addPoints(const QList<QPointF> &listPoints, const QString &measureName, KPlotObject *curve);
    void initializeGraphic();
    QDateTime m_initDateTime;
    int m_horizontalMaximumValue;
    int m_verticalMaximumValue;
    KPlotWidget *m_plotWidget;
    QHash<QString, KPlotObject *> m_plotObjectHash;
};

#endif // CGRAPHICSWIDGET_H
