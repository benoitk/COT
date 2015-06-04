#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
#include "cotgui_debug.h"

#include <QAction>
#include <QScrollBar>

CScrollableWidget::CScrollableWidget(QWidget *parent)
    : QScrollArea(parent)
    , m_scrollable(true)
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollableWidget::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollableWidget::slotMoveUp);

    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateActions();
}

CScrollableWidget::CScrollableWidget(bool scrollable, QWidget *parent)
    : QScrollArea(parent)
    , m_scrollable(scrollable)
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollableWidget::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollableWidget::slotMoveUp);

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
    // QtDesigner do create a content child, let delete it if there.
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
    m_moveDown->setEnabled(verticalScrollBar()->value() != verticalScrollBar()->maximum());
    m_moveUp->setEnabled(verticalScrollBar()->value() > 0);
}

// CScrollablePlainTextEdit

CScrollablePlainTextEdit::CScrollablePlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    m_moveDown = new QAction(tr("Move down"), this);
    connect(m_moveDown, &QAction::triggered, this, &CScrollablePlainTextEdit::slotMoveDown);
    m_moveUp = new QAction(tr("Move up"), this);
    connect(m_moveUp, &QAction::triggered, this, &CScrollablePlainTextEdit::slotMoveUp);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateActions();
}

CScrollablePlainTextEdit::~CScrollablePlainTextEdit()
{

}

QAction *CScrollablePlainTextEdit::moveDown() const
{
    return m_moveDown;
}

QAction *CScrollablePlainTextEdit::moveUp() const
{
    return m_moveUp;
}

void CScrollablePlainTextEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    updateActions();
}

void CScrollablePlainTextEdit::slotMoveUp()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepSub);
    updateActions();
}

void CScrollablePlainTextEdit::slotMoveDown()
{
    verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
    updateActions();
}

void CScrollablePlainTextEdit::updateActions()
{
    m_moveDown->setEnabled(verticalScrollBar()->value() != verticalScrollBar()->maximum());
    m_moveUp->setEnabled(verticalScrollBar()->value() > 0);
}
