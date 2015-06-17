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
    const QSize sh = QWidget::sizeHint();

    if (m_hostHeight == -1) {
        return sh;
    }

    const int pages = qCeil(static_cast<double>(sh.height()) / static_cast<double>(m_hostPageHeight));
    //qDebug() << "making height" << (m_hostHeight * pages) << "instead of" << height();

    // The last page is the full height. All others are just page height (integer number of items).
    const QSize nsh = QSize(sh.width(), m_hostPageHeight * (pages-1) + m_hostHeight);
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
