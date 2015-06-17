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
     * Create or update a curve based on measurename
     * If measurename doesn't exist this function will create a new curve
     * otherwise it will update curve data
     * It will add a new Y value (X is incremented every time).
     */
    void addOrUpdateCurve(float value, const QString &mesureName);

    /*
     * Generate new randow color
     */
    static QColor createNewColor();
private:
    KPlotObject *addCurve(double value, const QString &measureName, const QColor &col);
    void changeLimits(double x1, double x2, double y1, double y2);
    void addPoint(float value, const QString &measureName, KPlotObject *curve);
    void initializeGraphic();
    int m_horizontalMaximumValue;
    int m_verticalMaximumValue;
    KPlotWidget *m_plotWidget;
    QHash<QString, KPlotObject *> m_plotObjectHash;
};

#endif // CGRAPHICSWIDGET_H
