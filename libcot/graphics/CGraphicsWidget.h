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

    void clear();
    void changeLimits(double x1, double x2, double y1, double y2);

    KPlotObject *addCurve(const QList<QPointF> &listPoints, const QString &mesureName = QString(), const QColor &col = QColor());
    static QColor createNewColor();
    void addOrUpdateCurve(const QList<QPointF> &listPoints, const QString &mesureName);
    void addOrUpdateCurve(float value, const QString &mesureName);
private:
    KPlotObject *addCurve(double value, const QString &mesureName, const QColor &col);
    void addPoint(float value, const QString &mesureName, KPlotObject *curve);
    void addPoints(const QList<QPointF> &listPoints, const QString &mesureName, KPlotObject *curve);
    void initializeGraphic();
    QDateTime m_initDateTime;
    int m_horizontalMaximumValue;
    int m_verticalMaximumValue;
    KPlotWidget *m_plotWidget;
    QHash<QString, KPlotObject *> m_plotObjectHash;
};

#endif // CGRAPHICSWIDGET_H
