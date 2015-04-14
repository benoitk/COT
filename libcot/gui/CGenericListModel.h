#ifndef CGenericListModel_H
#define CGenericListModel_H

#include <QAbstractListModel>

#include "IVariable.h"

/**
 * @brief The CGenericListModel model keeps a list of IVariables.
 */
class CGenericListModel : public QAbstractListModel
{
public:
    CGenericListModel(const IVariablePtrList &list, QObject *parent = Q_NULLPTR);
    ~CGenericListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    /// Returns the stored IVariable pointer using the provided index row
    IVariablePtr IVariableForIndex(const QModelIndex &index) const;

private:
    IVariablePtrList m_IVariableList;
};

#endif // CGenericListModel_H
