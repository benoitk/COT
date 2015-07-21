#include "CGenericListDelegate.h"
#include "CGenericListModel.h"

#include <QPainter>
#include <QApplication>
#include <QToolTip>
#include <QHelpEvent>
#include <QAbstractItemView>
#include "cotgui_debug.h"

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

    // highlight selected / default value
    if (index.data(CGenericListModel::IsCurrentItem).toBool()) {
        buttonOption.features |= QStyleOptionButton::DefaultButton;
    }

    QStyle *style = option.widget ? option.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_PushButton, &buttonOption, painter);

    const QString text = index.data().toString();
    int flags = Qt::AlignCenter | Qt::TextWordWrap;

    // only add Qt::TextWrapAnywhere if no spaces
    if (!text.contains(" ")) {
        flags |= Qt::TextWrapAnywhere;
    }

    // Draw text adding small margin around to avoid text on button borders.
    painter->drawText(buttonOption.rect.adjusted(2, 2, -2, -2), flags, text);
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
