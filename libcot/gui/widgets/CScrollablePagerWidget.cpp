#include "CScrollablePagerWidget.h"

#include <QtMath>
#include <QDebug>

CScrollablePagerWidget::CScrollablePagerWidget(QWidget *parent)
    : QWidget(parent)
    ,m_hostHeight(-1)
    ,m_pageHeight(-1)
{
}

CScrollablePagerWidget::~CScrollablePagerWidget()
{
}

QSize CScrollablePagerWidget::minimumSizeHint() const
{
    return sizeHint();
}

QSize CScrollablePagerWidget::sizeHint() const
{
    const QSize sh = QWidget::sizeHint(); // size hint from the layout

    if (m_hostHeight == -1) {
        return sh;
    }

    const int pages = numPages();

    // The last page is the full height. All others are just page height (integer number of items).
    const QSize nsh = QSize(sh.width(), m_pageHeight * (pages-1) + m_hostHeight);
    //qDebug() << "making height" << m_hostPageHeight << "*" << (pages-1) << "+" << m_hostHeight << "=" << nsh.height() << "instead of" << height();
    return nsh;
}

void CScrollablePagerWidget::setHostHeight(int hostHeight)
{
    if (m_hostHeight != hostHeight) {
        m_hostHeight = hostHeight;
        updateGeometry();
    }
}

void CScrollablePagerWidget::setPageHeight(int pageHeight)
{
    if (m_pageHeight != pageHeight) {
        m_pageHeight = pageHeight;
        updateGeometry();
    }
}

int CScrollablePagerWidget::numPages() const
{
    if (m_pageHeight == -1) {
        return 0;
    }
    return qCeil(static_cast<double>(QWidget::sizeHint().height()) / static_cast<double>(m_pageHeight));
}
