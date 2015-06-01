#include "CScrollablePagerWidget.h"

#include <QtMath>
#include <QDebug>

CScrollablePagerWidget::CScrollablePagerWidget(QWidget *parent)
    : QWidget(parent)
    ,m_hostHeight(-1)
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

    const int pages = qCeil((double)sh.height() /(double)m_hostHeight);
    const QSize nsh = QSize(sh.width(), m_hostHeight *pages);
    return nsh;
}

int CScrollablePagerWidget::hostHeight() const
{
    return m_hostHeight;
}

void CScrollablePagerWidget::setHostHeight(int hostHeight)
{
    if (m_hostHeight != hostHeight) {
        m_hostHeight = hostHeight;
        updateGeometry();
    }
}
