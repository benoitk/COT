#ifndef CGENERICLISTDELEGATE_H
#define CGENERICLISTDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief The CGenericListDelegate delegate draws buttons frames in a listView
 */

class CGenericListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:   
    explicit CGenericListDelegate(QObject *parent = Q_NULLPTR);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
    bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex& index) Q_DECL_OVERRIDE;

    int itemSize()const;
    void setItemSize(const int size);

private:
    int m_itemSize;
};

#endif // CGENERICLISTDELEGATE_H
