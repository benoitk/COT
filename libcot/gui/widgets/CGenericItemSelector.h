#ifndef CGENERICITEMSELECTOR_H
#define CGENERICITEMSELECTOR_H

#include <QDialog>
#include <QModelIndex>
#include <QVariant>

#include "cot_global.h"
#include "IVariable.h"

/**
 * @brief The CGenericItemSelector dialog allows the user to select labelled icons in a grid.
 *  It is connected to a model that contains a list of IVariables. Clicked item can be retrieved via the "Item" property.
 */

namespace Ui {
class CGenericItemSelector;
}

class CGenericListModel;

class LIBCOT_EXPORT CGenericItemSelector : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(IVariablePtr selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged)

public:
    explicit CGenericItemSelector(const IVariablePtrList &list, QWidget *parent = Q_NULLPTR);
    ~CGenericItemSelector();

    void setTitle(const QString &title);

    IVariablePtr selectedItem() const;

    /// selects an item (The item must be of type CVariableString)
    void setSelectedItem(IVariablePtr item);

    // Select a variable by its nama
    void setSelectedName(const QString &name);
    void setSelectedValue(const QVariant &value);

    /// Scroll the listview in either direction.
    /// Scroll a whole page everytime this method is called.
    enum Direction {
        ScrollUp,
        ScrollDown
    };
    void scroll(Direction dir);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    /// reached when the user selects an item in the view. sets the property selectedItem.
    void itemSelected(const QModelIndex &index);

    /// connected to the scroll buttons
    void scrollUp();
    void scrollDown();

Q_SIGNALS:
    void selectedItemChanged(IVariablePtr newItem);

private:
    Ui::CGenericItemSelector *ui;
    CGenericListModel *m_model;
    IVariablePtr m_currentItem;

    void updateScrollButtons();
};

#endif // CGENERICITEMSELECTOR_H
