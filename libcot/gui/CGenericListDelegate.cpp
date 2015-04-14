#include "CGenericListDelegate.h"

#include <QApplication>
#include <QDebug>

const static int defaultItemSize = 130;

CGenericListDelegate::CGenericListDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_itemSize(defaultItemSize)
{
}

void CGenericListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton buttonOption;
    buttonOption.rect = option.rect;
    buttonOption.text = option.text.isEmpty()?index.data().toString():option.text;

    QStyle * style = option.widget ? option.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
}

QSize CGenericListDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return QSize(m_itemSize, m_itemSize);
}

unsigned int CGenericListDelegate::itemSize() const
{
    return m_itemSize;
}

void CGenericListDelegate::setItemSize(const unsigned int size)
{
    m_itemSize = size;
}
