#include "CStateCycleRunning.h"

CStateCycleRunning::CStateCycleRunning(const QVariantMap &mapSate, QObject *parent):IState(mapSate, parent)
{
//    connect(CAutomate::getInstance(), &CAutomate::signalStateRunning,
//            this, &IState::slotSetStateVaraibles);
    m_type = e_state_type_in_maintenance;
}
