#include "CGraphicsWidget.h"
#include "kplotwidget.h"
#include "kplotobject.h"
#include "kplotaxis.h"
#include <QVBoxLayout>
#include <QPen>
CGraphicsWidget::CGraphicsWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    m_plotWidget = new KPlotWidget(this);
    m_plotWidget->setObjectName(QStringLiteral("plotwidget"));
    layout->addWidget(m_plotWidget);
    initializeGraphic();
}

CGraphicsWidget::~CGraphicsWidget()
{

}

void CGraphicsWidget::initializeGraphic()
{
    m_plotWidget->setLimits(0, 350, 0, 350);
    m_plotWidget->axis(KPlotWidget::LeftAxis)->setVisible(false);
    m_plotWidget->axis(KPlotWidget::TopAxis)->setVisible(false);
    m_plotWidget->setAntialiasing(true);
    m_plotWidget->setShowGrid(true);
    m_plotWidget->setBackgroundColor(palette().background().color());
    m_plotWidget->setForegroundColor(Qt::black);
    m_plotWidget->axis(KPlotWidget::RightAxis)->setTickLabelsShown(true);
    m_plotWidget->setObjectToolTipShown(true);
}

void CGraphicsWidget::clear()
{
    m_plotWidget->removeAllPlotObjects();
}

void CGraphicsWidget::changeLimits(double x1, double x2, double y1, double y2)
{
    m_plotWidget->setLimits(x1, x2, y1, y2);
}

KPlotObject *CGraphicsWidget::addCurves(const QList<QPointF> &listPoints, const QString &mesureName, const QColor &col)
{
    KPlotObject *curve = new KPlotObject();
    if (col.isValid()) {
        QPen pen = curve->linePen();
        pen.setColor(col);
        curve->setLinePen(pen);
    }
    curve->setShowLines(true);
    //curve->setShowPoints(false);
    Q_FOREACH(const QPointF &point, listPoints) {
        curve->addPoint(point, mesureName);
    }
    m_plotWidget->addPlotObject(curve);
    return curve;
}
