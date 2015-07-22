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
    static const int MARGIN = 2;

    static int textFlags(const QString &text)
    {
        int flags = Qt::AlignCenter | Qt::TextWordWrap;
        // only add Qt::TextWrapAnywhere if no spaces
        if (!text.contains(' ')) {
            flags |= Qt::TextWrapAnywhere;
        }
        return flags;
    }
}

CGenericListDelegate::CGenericListDelegate(QWidget *view, QAbstractItemModel *model)
    : QStyledItemDelegate(model),
      m_itemSize(DEFAULT_ITEM_SIZE, DEFAULT_ITEM_SIZE)
{
    // Determine item size based on text to avoid truncation in case of long words
    const int rowCount = model->rowCount();
    const QFontMetrics fontMetrics = view->fontMetrics();
    const QRect initialRect(0, 0, DEFAULT_ITEM_SIZE, DEFAULT_ITEM_SIZE);
    for (int row = 0; row < rowCount; ++row) {
        const QModelIndex index = model->index(row, 0);
        const QString text = index.data().toString();
        const QRect br = fontMetrics.boundingRect(initialRect, textFlags(text), text);
        const QSize size = br.size() + QSize(MARGIN*2, MARGIN*2);
        if (size.width() > m_itemSize.width()) {
            // We only enlarge the width, and hope that it all fits in 90 pixels height
            // If it doesn't, then a second loop will be needed, to adjust for the final width
            m_itemSize.rwidth() = size.width();
        }
    }
}

void CGenericListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index); // like QStyledItemDelegate does

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

    // Draw text adding small margin around to avoid text on button borders.
    painter->drawText(buttonOption.rect.adjusted(MARGIN, MARGIN, -MARGIN, -MARGIN), textFlags(text), text);
}

QSize CGenericListDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return m_itemSize;
}

bool CGenericListDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    QToolTip::showText(event->globalPos(), index.data().toString(), view);
    return true;
}
