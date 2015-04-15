#include "CGenericListDelegate.h"

#include <QApplication>
#include <QDebug>


namespace {
    static const int DEFAULT_ITEM_SIZE = 130;
}

CGenericListDelegate::CGenericListDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_itemSize(DEFAULT_ITEM_SIZE)
{
}

void CGenericListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton buttonOption;
    buttonOption.initFrom(option.widget);
    buttonOption.rect = option.rect;
    buttonOption.text = index.data().toString();

    QStyle * style = option.widget ? option.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
}

QSize CGenericListDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return QSize(m_itemSize, m_itemSize);
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