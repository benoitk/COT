#include "proxystyle.h"

#include <QPainter>
#include <qstyleoption.h>

int ProxyStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

int ProxyStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch(metric) {
    case QStyle::PM_TabBarTabHSpace:
        return 10;
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}

void ProxyStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
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
        painter->drawRoundedRect(option->rect.adjusted(4, 0, -4, 7), 7, 7);
    }
        break;
    case QStyle::CE_TabBarTabLabel:
    {
        const bool selected = option->state & QStyle::State_Selected;
        const QFont oldFont = painter->font();
        if (selected) {
            QFont font = oldFont;
            font.setBold(true);
            painter->setFont(font);
        }
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

QSize ProxyStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    switch (type) {
    case QStyle::CT_TabBarTab:
        return size + QSize(8, 10);
    default:
        return QProxyStyle::sizeFromContents(type, option, size, widget);
    }
}
