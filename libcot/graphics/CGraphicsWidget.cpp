#include "CGraphicsWidget.h"
#include "kplotwidget.h"
#include "kplotaxis.h"
#include <QVBoxLayout>
CGraphicsWidget::CGraphicsWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    m_plotWidget = new KPlotWidget(this);
    m_plotWidget->setObjectName(QStringLiteral("plotwidget"));
    m_plotWidget->setLimits(0, 300, 0, 300);
    layout->addWidget(m_plotWidget);
    m_plotWidget->axis(KPlotWidget::RightAxis)->setVisible(false);
    m_plotWidget->axis(KPlotWidget::TopAxis)->setVisible(false);
}

CGraphicsWidget::~CGraphicsWidget()
{

}

