#include "CScrollablePagerWidget.h"

#include <QtMath>
#include <QDebug>

CScrollablePagerWidget::CScrollablePagerWidget(QWidget *parent)
    : QWidget(parent)
    ,m_hostHeight(-1)
    ,m_hostPageHeight(-1)
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
    const QSize nsh = QSize(sh.width(), m_hostPageHeight * (pages-1) + m_hostHeight);
    //qDebug() << "making height" << m_hostPageHeight << "*" << (pages-1) << "+" << m_hostHeight << "=" << nsh.height() << "instead of" << height();
    return nsh;
}

void CScrollablePagerWidget::setHostHeight(int hostHeight, int hostPageHeight)
{
    if (m_hostHeight != hostHeight || m_hostPageHeight != hostPageHeight) {
        m_hostHeight = hostHeight;
        m_hostPageHeight = hostPageHeight;
        updateGeometry();
    }
}

int CScrollablePagerWidget::numPages() const
{
    if (m_hostHeight == -1) {
        return 0;
    }
    return qCeil(static_cast<double>(QWidget::sizeHint().height()) / static_cast<double>(m_hostPageHeight));
}
