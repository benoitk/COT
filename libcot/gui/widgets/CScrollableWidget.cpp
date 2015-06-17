#include "CScrollableWidget.h"
#include "CScrollablePagerWidget.h"
#include "cotgui_debug.h"

#include <QAction>
#include <QScrollBar>
#include <qlayout.h>

CScrollableWidget::CScrollableWidget(QWidget *parent)
    : QScrollArea(parent)
    , m_viewportMargin(0)
    , m_scrollable(true)
{
    init();
}

CScrollableWidget::CScrollableWidget(bool scrollable, QWidget *parent)
    : QScrollArea(parent)
    , m_viewportMargin(0)
    , m_scrollable(scrollable)
{
    init();
}

void CScrollableWidget::init()
{
    m_pageStep = 0;

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
        updateActions();
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

void CScrollableWidget::updatePageHeight()
{
    CScrollablePagerWidget *pager = scrollablePagerWidget();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(pager->layout());
    if (gridLayout) {
        // Determine how many entire items fit into one page
        // This assumes all items have the same height, but IVariableUIHandler::layout takes care of that.
        const int itemHeight = gridLayout->cellRect(0, 0).height() + gridLayout->spacing();
        const int numItems = height() / itemHeight; // truncation on purpose

        m_pageStep = numItems * itemHeight;
        //qDebug() << parentWidget() << "itemHeight=" << itemHeight << "host height" << height() << "viewport height" << viewport()->height() << "numItems=" << numItems << "-> pagestep=" << m_pageStep;
    } else {
        m_pageStep = viewport()->height();
    }
    pager->setPageHeight(m_pageStep);

    if (pager->numPages() > 1) {
        // Hide the half item at the bottom
        int viewportMargin = qMax(0, viewport()->height() + m_viewportMargin - m_pageStep);
        if (viewportMargin != m_viewportMargin) {
            m_viewportMargin = viewportMargin;
            //qDebug() << "setViewportMargins" << m_viewportMargin;
            setViewportMargins(0, 0, 0, m_viewportMargin);
        }
    }
}

bool CScrollableWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == widget() && event->type() == QEvent::LayoutRequest) {
        if (!m_scrollable) {
            updateGeometry();
        } else {
            updatePageHeight();
        }
    }
    return QScrollArea::eventFilter(obj, event);
}

void CScrollableWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    CScrollablePagerWidget *pager = scrollablePagerWidget();
    if (pager && m_scrollable) {
        updatePageHeight();
        pager->setHostHeight(viewport()->height());
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
    verticalScrollBar()->setSliderPosition(verticalScrollBar()->sliderPosition() - m_pageStep);
    updateActions();
}

void CScrollableWidget::slotMoveDown()
{
    verticalScrollBar()->setSliderPosition(verticalScrollBar()->sliderPosition() + m_pageStep);
    updateActions();
}

void CScrollableWidget::updateActions()
{
    bool needsScrolling = false;
    if (widget() && m_pageStep > 0) {
        const auto value = verticalScrollBar()->value();
        const auto maximum = verticalScrollBar()->maximum();
        CScrollablePagerWidget *pager = scrollablePagerWidget();
        needsScrolling = pager ? (pager->numPages() > 1) : (widget()->height() > m_pageStep);

        //qDebug() << "pageStep=" << m_pageStep << "widget height=" << widget()->height() << "-> needsScrolling=" << needsScrolling;

        m_moveDown->setEnabled(value != maximum && needsScrolling);
        m_moveUp->setEnabled(value > 0);
    }
    m_moveDown->setVisible(needsScrolling);
    m_moveUp->setVisible(needsScrolling);
}

