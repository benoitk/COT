#ifndef CGENERICITEMSELECTOR_H
#define CGENERICITEMSELECTOR_H

#include <QDialog>
#include <QModelIndex>

#include "cot_global.h"

#include "IVariable.h"

/**
 * @brief The CGenericItemSelector dialog allows the user to select labelled icons in a grid.
 *  It is connected to a model that contains a list of IVariables. Clicked item can be retrieved via the "Item" property.
 */

class QListView;
class CGenericListModel;
class QToolButton;

class LIBCOT_EXPORT CGenericItemSelector : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(IVariablePtr selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)

public:
    explicit CGenericItemSelector(const IVariablePtrList &list, QWidget *parent = Q_NULLPTR);

    IVariablePtr selectedItem() const;

    /// selects an item (The item must be of type CVariableString)
    void setSelectedItem(IVariablePtr item);

    /// Scroll the listview in either direction.
    /// Scroll a whole page everytime this method is called.
    enum Direction {
        ScrollUp,
        ScrollDown
    };
    void scroll(Direction dir);

private Q_SLOTS:
    /// reached when the user selects an item in the view. sets the property selectedItem.
    void itemSelected(const QModelIndex &index);

    /// connected to the scroll buttons
    void scrollUp();
    void scrollDown();

Q_SIGNALS:
    void selectedItemChanged(IVariablePtr newItem);

private:
    QListView *m_listView;
    CGenericListModel *m_model;
    IVariablePtr m_currentItem;
    QToolButton *m_upButton;
    QToolButton *m_downButton;
};

#endif // CGENERICITEMSELECTOR_H
