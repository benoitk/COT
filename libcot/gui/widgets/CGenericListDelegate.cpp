#include "CGenericListDelegate.h"

#include <QPainter>
#include <QApplication>
#include <QToolTip>
#include <QHelpEvent>
#include <QAbstractItemView>
#include <QDebug>

namespace {
    static const int DEFAULT_ITEM_SIZE = 90;
}

CGenericListDelegate::CGenericListDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_itemSize(DEFAULT_ITEM_SIZE)
{
}

void CGenericListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    QStyleOptionButton buttonOption;
    buttonOption.initFrom(option.widget);
    buttonOption.state = opt.state;
    buttonOption.rect = option.rect;

    QStyle * style = option.widget ? option.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
    painter->drawText(buttonOption.rect, Qt::AlignCenter | Qt::TextWordWrap, index.data().toString());
}

QSize CGenericListDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return QSize(m_itemSize, m_itemSize);
}

bool CGenericListDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    QToolTip::showText(event->globalPos(), index.data().toString(), view);
    return true;
}

int CGenericListDelegate::itemSize() const
{
    return m_itemSize;
}

void CGenericListDelegate::setItemSize(const int size)
{
    if (size >= 0) {
        m_itemSize = size;
    }
}
