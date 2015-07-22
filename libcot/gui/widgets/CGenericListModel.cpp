#include "CGenericListModel.h"

namespace {
bool lessThanIVariable(IVariable* left, IVariable* right) {
    const QString leftLabel = left->getLabel().isEmpty() ? left->getName() : left->getLabel();
    const QString rightLabel = right->getLabel().isEmpty() ? right->getName() : right->getLabel();
    return leftLabel.compare(rightLabel, Qt::CaseInsensitive) < 0;
}
}

CGenericListModel::CGenericListModel(const IVariablePtrList &list, QObject *parent)
    : QAbstractListModel(parent),
      m_IVariableList(list)
    , m_currentItem(Q_NULLPTR)
{
    qSort(m_IVariableList.begin(), m_IVariableList.end(), lessThanIVariable);
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

    const IVariablePtr ivar = IVariableForIndex(index);

    if (role == Qt::DisplayRole) {
        const QString text = ivar->getLabel();
        return text.isEmpty() ? ivar->getName() : text;
    }
    else if (role == CGenericListModel::IsCurrentItem) {
        return ivar == m_currentItem;
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
    foreach (const IVariablePtr &var, m_IVariableList) {
        if (var->toString() == value || var->getName() == value) {
            return var;
        }
    }

    return Q_NULLPTR;
}

IVariablePtr CGenericListModel::currentItem() const
{
    return m_currentItem;
}

void CGenericListModel::setCurrentItem(IVariablePtr currentItem)
{
    if (m_currentItem != currentItem) {
        if (m_IVariableList.contains(currentItem)) {
            m_currentItem = currentItem;

            if (!m_IVariableList.isEmpty()) {
                emit dataChanged(index(0, 0), index(rowCount() -1, 0));
            }
        }
    }
}
