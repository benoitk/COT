#include "CGenericListModel.h"

CGenericListModel::CGenericListModel(const IVariablePtrList &list, QObject *parent)
    : QAbstractListModel(parent),
      m_IVariableList(list)
{

}

CGenericListModel::~CGenericListModel()
{

}

int CGenericListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_IVariableList.count();
}

QVariant CGenericListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_IVariableList.count() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return IVariableForIndex(index)->getLabel();
    }

    return QVariant();
}

bool CGenericListModel::contains(IVariablePtr item)
{
    return m_IVariableList.contains(item);
}

QModelIndex CGenericListModel::indexForIVariable(IVariablePtr variable) const
{
    const int row = m_IVariableList.indexOf(variable);
    return row != -1 ? index(row, 0) : QModelIndex();
}

IVariablePtr CGenericListModel::IVariableForIndex(const QModelIndex &index) const
{
    if (index.row() >= m_IVariableList.count() || index.row() < 0)
        return Q_NULLPTR;
    return m_IVariableList[index.row()];
}

IVariablePtr CGenericListModel::IVAriableForName(const QString &name) const
{
    IVariablePtr ivar = Q_NULLPTR;

    foreach (const IVariablePtr &var, m_IVariableList) {
        if (var->getName() == name) {
            ivar = var;
            break;
        }
    }

    return ivar;
}

IVariablePtr CGenericListModel::IVAriableForValue(const QString &value) const
{
    IVariablePtr ivar = Q_NULLPTR;

    foreach (const IVariablePtr &var, m_IVariableList) {
        if (var->toString() == value) {
            ivar = var;
            break;
        }
    }

    return ivar;
}
