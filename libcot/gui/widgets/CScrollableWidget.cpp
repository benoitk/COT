#include "CScrollableWidget.h"
#include <QAction>
#include <QScrollBar>
#include <QDebug>

CScrollableWidget::CScrollableWidget(QWidget *parent)
    : QScrollArea(parent)
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollableWidget::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollableWidget::slotMoveUp);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateActions();
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
    // QtDesigner do create a content child, let delete it if there.
    if (widget()) {
        takeWidget()->deleteLater();
    }

    setWidget(w);
    w->show();
    updateActions();
}

void CScrollableWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);
    updateActions();
}

void CScrollableWidget::slotMoveUp()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
    updateActions();
}

void CScrollableWidget::slotMoveDown()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
    updateActions();
}

void CScrollableWidget::updateActions()
{
    m_moveDown->setEnabled(verticalScrollBar()->value() != verticalScrollBar()->maximum());
    m_moveUp->setEnabled(verticalScrollBar()->value() > 0);
}
