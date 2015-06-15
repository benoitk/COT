#include "CGraphicsWidget.h"
#include "kplotwidget.h"
#include "kplotobject.h"
#include "kplotaxis.h"
#include <QVBoxLayout>
#include <QPen>
#include "cotgui_debug.h"

static int INCREMENT_X = 50;
static int INCREMENT_Y = 50;

CGraphicsWidget::CGraphicsWidget(QWidget *parent)
    : QWidget(parent),
      m_horizontalMaximumValue(10),
      m_verticalMaximumValue(INCREMENT_Y)
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
   m_plotObjectHash.clear();
}

void CGraphicsWidget::initializeGraphic()
{
    m_plotWidget->setLimits(0, m_horizontalMaximumValue, 0, m_verticalMaximumValue);
    m_plotWidget->axis(KPlotWidget::LeftAxis)->setVisible(false);
    m_plotWidget->axis(KPlotWidget::TopAxis)->setVisible(false);
    m_plotWidget->setAntialiasing(true);
    m_plotWidget->setShowGrid(true);
    m_plotWidget->setBackgroundColor(palette().background().color());
    m_plotWidget->setForegroundColor(Qt::black);
    m_plotWidget->axis(KPlotWidget::RightAxis)->setTickLabelsShown(true);
    m_plotWidget->axis(KPlotWidget::BottomAxis)->setTickLabelsShown(false);
    m_plotWidget->setObjectToolTipShown(true);
}

void CGraphicsWidget::clear()
{
    m_plotWidget->removeAllPlotObjects();
    m_plotObjectHash.clear();
}

void CGraphicsWidget::changeLimits(double x1, double x2, double y1, double y2)
{
    m_plotWidget->setLimits(x1, x2, y1, y2);
}

void CGraphicsWidget::addOrUpdateCurve(float value, const QString &measureName)
{
    KPlotObject *searchPlot = m_plotObjectHash.value(measureName);
    if (searchPlot) {
        int i = m_plotWidget->plotObjects().indexOf(searchPlot);
        Q_ASSERT(i >= 0);
        addPoint(value, measureName, searchPlot);
        m_plotWidget->replacePlotObject(i, searchPlot);
    } else {
        KPlotObject *plot = addCurve(value, measureName, createNewColor());
        m_plotObjectHash.insert(measureName, plot);
    }
    m_plotWidget->update();
}

void CGraphicsWidget::addPoint(float value, const QString &measureName, KPlotObject *curve )
{
    const QDateTime dt = QDateTime::currentDateTime();
    bool needToChangeGraphicLimit = false;
    int x = curve->points().count();
    if (x >= m_horizontalMaximumValue) {
        needToChangeGraphicLimit = true;
        m_horizontalMaximumValue += INCREMENT_X;
    }
    // SERES_TODO: add API for range, so a fixedrange can be used here?
    if (value >= m_verticalMaximumValue) {
        needToChangeGraphicLimit = true;
        m_verticalMaximumValue += INCREMENT_Y;
    }
    if (needToChangeGraphicLimit) {
        qCDebug(COTGUI_LOG) << "new limits" << m_horizontalMaximumValue << m_verticalMaximumValue;
        changeLimits(0, m_horizontalMaximumValue, 0, m_verticalMaximumValue);
    }
    //qCDebug(COTGUI_LOG) << "addPoint" << QPointF(x, value);
    curve->addPoint(QPointF(x, value), tr("Mesure name: %1\nValue: %2\n Date: %3").arg(measureName).arg(value).arg(dt.toString()));
}

KPlotObject *CGraphicsWidget::addCurve(double value, const QString &measureName, const QColor &col)
{
    KPlotObject *curve = new KPlotObject();
    if (col.isValid()) {
        QPen pen = curve->linePen();
        pen.setColor(col);
        curve->setLinePen(pen);
        curve->setPen(pen);
    }
    curve->setShowLines(true);
    addPoint(value, measureName, curve);
    m_plotWidget->addPlotObject(curve);
    return curve;
}


void CGraphicsWidget::addOrUpdateCurve(const QList<QPointF> &listPoints, const QString &measureName)
{
    KPlotObject *searchPlot = m_plotObjectHash.value(measureName);
    if (searchPlot) {
        int i = m_plotWidget->plotObjects().indexOf(searchPlot);
        Q_ASSERT(i >= 0);
        addPoints(listPoints, measureName, searchPlot);
        m_plotWidget->replacePlotObject(i, searchPlot);
    } else {
        KPlotObject *plot = addCurve(listPoints, measureName, createNewColor());
        m_plotObjectHash.insert(measureName, plot);
    }
    m_plotWidget->update();
}

void CGraphicsWidget::addPoints(const QList<QPointF> &listPoints, const QString &measureName, KPlotObject *curve )
{
    foreach(const QPointF &point, listPoints) {
        curve->addPoint(point, QStringLiteral("%1\n%2-%3").arg(measureName).arg(point.x()).arg(point.y()));
    }
}

KPlotObject *CGraphicsWidget::addCurve(const QList<QPointF> &listPoints, const QString &measureName, const QColor &col)
{
    KPlotObject *curve = new KPlotObject();
    if (col.isValid()) {
        QPen pen = curve->linePen();
        pen.setColor(col);
        curve->setLinePen(pen);
        curve->setPen(pen);
    }
    curve->setShowLines(true);
    addPoints(listPoints, measureName, curve);
    m_plotWidget->addPlotObject(curve);
    return curve;
}

QColor CGraphicsWidget::createNewColor()
{
    const QColor col = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
    return col;
}
