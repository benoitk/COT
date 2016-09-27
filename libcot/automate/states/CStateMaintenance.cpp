#include "CStateMaintenance.h"

CStateMaintenance::CStateMaintenance(const QVariantMap &mapSate, QObject *parent):IState(mapSate, parent)
{
    m_type = e_state_type_in_maintenance;
}

