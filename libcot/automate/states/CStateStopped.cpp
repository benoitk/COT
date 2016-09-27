#include "CStateStopped.h"

CStateStopped::CStateStopped(const QVariantMap &mapSate, QObject *parent):IState(mapSate, parent)
{
    m_type = e_state_type_in_maintenance;
}

void CStateStopped::slotSetStateVaraibles() {
//    if(arg_state == CAutomate::CYCLE_STATE_STOP_END_CYCLE)
//    setStateVariables(true);
}
