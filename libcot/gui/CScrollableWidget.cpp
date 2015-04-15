#include "CScrollableWidget.h"
#include <QAction>
#include <QScrollBar>

CScrollableWidget::CScrollableWidget(QWidget *parent)
    : QScrollArea(parent)
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollableWidget::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollableWidget::slotMoveUp);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CScrollableWidget::~CScrollableWidget()
{

}
QAction *CScrollableWidget::moveDown() const
{
    return m_moveDown;
}
QAction *CScrollableWidget::moveUp() const
{
    return m_moveUp;
}

void CScrollableWidget::setScrollableWidget(QWidget *w)
{
    setWidget(w);
    w->show();
}

void CScrollableWidget::slotMoveUp()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
}

void CScrollableWidget::slotMoveDown()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
}



