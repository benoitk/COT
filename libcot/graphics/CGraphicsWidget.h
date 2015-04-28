#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

#include <QWidget>
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
private:
    void initializeGraphic();
    KPlotWidget *m_plotWidget;
    QHash<QString, KPlotObject *> m_plotObjectHash;
};

#endif // CGRAPHICSWIDGET_H
