#include "CGraphicsWidget.h"
#include "kplotwidget.h"
#include "CPlotObject.h"
#include "kplotaxis.h"
#include "kplotpoint.h"
#include <QVBoxLayout>
#include <QPen>
#include "cotgui_debug.h"

static const int INCREMENT_Y = 60;
double s_maxPointsInCurve = 400;

CGraphicsWidget::CGraphicsWidget(QWidget *parent)
    : QWidget(parent)
      , m_x(0)
      , m_verticalMaximumValue(INCREMENT_Y)
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
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    changeLimits(0, 23, 0, m_verticalMaximumValue); //Axe des x en heure
    //changeLimits(0, s_maxPointsInCurve - 1, 0, m_verticalMaximumValue);
    m_plotWidget->axis(KPlotWidget::LeftAxis)->setVisible(true);
    m_plotWidget->axis(KPlotWidget::TopAxis)->setVisible(false);

    m_plotWidget->setAntialiasing(true);
    m_plotWidget->setShowGrid(true);
    m_plotWidget->setBackgroundColor(palette().background().color());
    m_plotWidget->setForegroundColor(Qt::black);
    m_plotWidget->axis(KPlotWidget::RightAxis)->setTickLabelsShown(true);
    m_plotWidget->axis(KPlotWidget::BottomAxis)->setTickLabelsShown(true);
    m_plotWidget->axis(KPlotWidget::BottomAxis)->setTickLabelFormat('t');
    m_plotWidget->axis(KPlotWidget::BottomAxis)->setVisible(true);
    m_plotWidget->setObjectToolTipShown(true);
    m_plotWidget->setLeftPadding(1);
    m_plotWidget->setTopPadding(1);
    m_plotWidget->setBottomPadding(-1);
    m_plotWidget->setMinimumSize(200, 100); // the 150 in KPlotWidget is too high
}

void CGraphicsWidget::doneUpdatingPlotting()
{
    //m_x++;
    m_plotWidget->update();
}

void CGraphicsWidget::showPlotObject(CPlotObject *object)
{
    if (m_plotWidget->plotObjects().count() == 1) {
        m_plotWidget->replacePlotObject(0, object);
    } else {
        m_plotWidget->addPlotObject(object);
    }
}

void CGraphicsWidget::addPlotObject(CPlotObject *object)
{
    m_plotWidget->addPlotObject(object);
}

void CGraphicsWidget::changeLimits(double x1, double x2, double y1, double y2)
{
    //qCDebug(COTGUI_LOG) << "new limits" << x1 << x2 << y1 << y2;
    m_plotWidget->setLimits(x1, x2, y1, y2);
}

void CGraphicsWidget::addPoint(float value, CPlotObject *curve, float arg_valueMin,float arg_valueMax)
{
    m_verticalMaximumValue = arg_valueMax+(arg_valueMax*0.10f);
    double currentTimeInHour = QDateTime::currentDateTime().time().hour() + (QDateTime::currentDateTime().time().minute()/60);

    //TEST
//    m_x = m_x+0.1;
//    currentTimeInHour = m_x;
//    if(arg_valueMax !=0)
//        value = rand() % int(arg_valueMax*0.05f);
//    value = value + (arg_valueMax*0.70f);

    curve->addValue(currentTimeInHour, value);
    changeLimits(currentTimeInHour - 12, currentTimeInHour, 0, m_verticalMaximumValue);

}
