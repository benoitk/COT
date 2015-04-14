#ifndef CGENERICLISTDELEGATE_H
#define CGENERICLISTDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief The CGenericListDelegate delegate draws buttons frames in a listView
 */

class CGenericListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    Q_PROPERTY(unsigned int itemSize READ itemSize WRITE setItemSize)

public:   
    explicit CGenericListDelegate(QObject *parent = Q_NULLPTR);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const;

    unsigned int itemSize()const;
    void setItemSize(const unsigned int size);

private:
    unsigned int m_itemSize;
};

#endif // CGENERICLISTDELEGATE_H
