#ifndef CGENERICLISTMODEL_H
#define CGENERICLISTMODEL_H

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

    /// returns true if the stored variable list contains item
    bool contains(IVariablePtr item);
    QModelIndex indexForIVariable(IVariablePtr variable) const;

    /// Returns the stored IVariable pointer using the provided index row
    IVariablePtr IVariableForIndex(const QModelIndex &index) const;
    IVariablePtr IVAriableForName(const QString &name) const;
    IVariablePtr IVAriableForValue(const QString &value) const;

private:
    IVariablePtrList m_IVariableList;
};

#endif // CGENERICLISTMODEL_H
