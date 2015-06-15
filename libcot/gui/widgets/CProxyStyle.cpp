#include "CProxyStyle.h"

#include <QPainter>
#include <QDebug>
#include <qstyleoption.h>

int CProxyStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

int CProxyStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch(metric) {
    case QStyle::PM_TabBarTabHSpace: // empty space on left+right of the text, within the tab
        // Fusion style has 24 here... we need to make things tighter though
        return 8;
    case QStyle::PM_TabBarTabVSpace: // empty space below+above the text, within the tab
        return 12 /* from fusion style */ + 10 /* extra height */;
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}

static const int emptySpaceBetweenTabs = 4;

void CProxyStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch(element) {
    case QStyle::CE_TabBarTabShape:
    {
        const bool selected = option->state & QStyle::State_Selected;
        if (!selected) {
            painter->setBrush(QColor(0xdc, 0xdc, 0xdc));
            painter->setPen(Qt::NoPen);
        } else {
            painter->setBrush(Qt::white);
            painter->setPen(Qt::black);
        }
        // To get only the top corners rounded, I draw a higher-than-visible rounded-rect
        painter->drawRoundedRect(option->rect.adjusted(emptySpaceBetweenTabs / 2, 0, - emptySpaceBetweenTabs / 2, 7), 7, 7);
    }
        break;
    case QStyle::CE_TabBarTabLabel:
    {
        const bool selected = option->state & QStyle::State_Selected;
        const QFont oldFont = painter->font();
        QFont font = oldFont;
        if (selected) {
            font.setBold(true);
        } else {
            font.setBold(false);
        }
        painter->setFont(font);
        QProxyStyle::drawControl(element, option, painter, widget);
        if (selected) {
            painter->setFont(oldFont);
        }
        break;
    }
    default:
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

void CProxyStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case QStyle::PE_FrameTabWidget:
        if (const QStyleOptionTabWidgetFrameV2 *tabframe = qstyleoption_cast<const QStyleOptionTabWidgetFrameV2*>(option)) {
            // just one line, 1 pixel under the tabbar
            const QRect r = tabframe->tabBarRect;
            painter->drawLine(r.left(), r.bottom() + 1, option->rect.right(), r.bottom() + 1);
        }
        break;
    default:
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}

QSize CProxyStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    // unused now
    return QProxyStyle::sizeFromContents(type, option, size, widget);
}

void CProxyStyle::polish(QWidget *widget)
{
    if (QTabBar *tabBar = qobject_cast<QTabBar *>(widget)) {
        // Make the QTabBar font bold by default, so that the size computation in QTabBar::sizeHint uses
        // the (usually wider) font. We revert to a non-bold font at drawing time.
        QFont boldFont = tabBar->font();
        boldFont.setBold(true);
        tabBar->setFont(boldFont);

        tabBar->setUsesScrollButtons(false);
    }

    QProxyStyle::polish(widget);
}
