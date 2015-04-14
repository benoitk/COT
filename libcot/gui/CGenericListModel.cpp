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
        return IVariableForIndex(index)->toString();
    }

    return QVariant();
}

bool CGenericListModel::contains(IVariablePtr item)
{
    return m_IVariableList.contains(item);
}

IVariablePtr CGenericListModel::IVariableForIndex(const QModelIndex &index) const
{
    if (index.row() >= m_IVariableList.count() || index.row() < 0)
        return Q_NULLPTR;
    return m_IVariableList[index.row()];
}
