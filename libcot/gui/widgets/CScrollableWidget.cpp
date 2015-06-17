#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
#include "cotgui_debug.h"

#include <QAction>
#include <QScrollBar>

CScrollableWidget::CScrollableWidget(QWidget *parent)
    : QScrollArea(parent)
    , m_scrollable(true)
{
    init();
}

CScrollableWidget::CScrollableWidget(bool scrollable, QWidget *parent)
    : QScrollArea(parent)
    , m_scrollable(scrollable)
{
    init();
}

void CScrollableWidget::init()
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollableWidget::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollableWidget::slotMoveUp);

    setFrameStyle(QFrame::NoFrame);
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateActions();
}

CScrollableWidget::~CScrollableWidget()
{
}

QSize CScrollableWidget::minimumSizeHint() const
{
    const QSize msh = QScrollArea::minimumSizeHint();
    return m_scrollable || !widget() ? msh : QSize(msh.width(), widget()->minimumSizeHint().height());
}

QSize CScrollableWidget::sizeHint() const
{
    const QSize sh = QScrollArea::sizeHint();
    return m_scrollable || !widget() ? sh : QSize(sh.width(), widget()->sizeHint().height());
}

bool CScrollableWidget::scrollable() const
{
    return m_scrollable;
}

void CScrollableWidget::setScrollable(bool scrollable)
{
    if (m_scrollable != scrollable) {
        m_scrollable = scrollable;
        updateGeometry();
    }
}

QAction *CScrollableWidget::moveDown() const
{
    return m_moveDown;
}

QAction *CScrollableWidget::moveUp() const
{
    return m_moveUp;
}

void CScrollableWidget::setScrollablePagerWidget(CScrollablePagerWidget *w)
{
    // QtDesigner creates a content child, let's delete it if there.
    if (widget()) {
        takeWidget()->deleteLater();
    }

    setWidget(w);
    w->installEventFilter(this);
    w->show();
    updateActions();
}

CScrollablePagerWidget *CScrollableWidget::scrollablePagerWidget() const
{
    return qobject_cast<CScrollablePagerWidget *>(widget());
}

bool CScrollableWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (!m_scrollable && obj == widget() && event->type() == QEvent::LayoutRequest) {
        updateGeometry();
    }

    return QScrollArea::eventFilter(obj, event);
}

void CScrollableWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    if (scrollablePagerWidget()) {
        scrollablePagerWidget()->setHostHeight(event->size().height());
    }

    updateActions();
}

void CScrollableWidget::wheelEvent(QWheelEvent *event)
{
    QScrollArea::wheelEvent(event);
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
    const auto value = verticalScrollBar()->value();
    const auto maximum = verticalScrollBar()->maximum();
    const auto needsScrolling = maximum > verticalScrollBar()->pageStep();
    m_moveDown->setEnabled(value != maximum && needsScrolling);
    m_moveUp->setEnabled(value > 0);
    m_moveDown->setVisible(needsScrolling);
    m_moveUp->setVisible(needsScrolling);
}

