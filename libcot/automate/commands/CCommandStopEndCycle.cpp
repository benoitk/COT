#include "CCommandStopEndCycle.h"
#include "IVariable.h"
#include "CAutomate.h"

CCommandStopEndCycle::CCommandStopEndCycle(const QVariantMap &mapCmd, QObject *parent):CCommandPlayStopCycle(mapCmd, parent)
{

}

bool CCommandStopEndCycle::slotRunCommand(bool arg_externalCmdOnly){
    if(m_inputVariable->getType() != e_type_unknow && m_inputVariable->toBool()
            && !m_currentValue && !CAutomate::getInstance()->isLocalControlForced() ){
        m_currentValue = !m_currentValue;
        CAutomate::getInstance()->requestCancelStopEndCycleScheduler();
        if (!m_cmdStop || m_cmdStop->getStateCommand())
            CAutomate::getInstance()->requestPlayScheduler();
    }
    else if( (m_inputVariable->getType() != e_type_unknow && !m_inputVariable->toBool())
             && m_currentValue && !CAutomate::getInstance()->isLocalControlForced()){
        m_currentValue = !m_currentValue;
        CAutomate::getInstance()->requestStopEndCycleScheduler();
    }
    else if( (m_inputVariable->getType() == e_type_unknow || CAutomate::getInstance()->isLocalControlForced())
             && !m_currentValue && !arg_externalCmdOnly ){
        m_currentValue = !m_currentValue;
        CAutomate::getInstance()->requestCancelStopEndCycleScheduler();
        if (!m_cmdStop || m_cmdStop->getStateCommand())
            CAutomate::getInstance()->requestPlayScheduler();
    }
    else if((m_inputVariable->getType() == e_type_unknow || CAutomate::getInstance()->isLocalControlForced())&& m_currentValue && !arg_externalCmdOnly){
        m_currentValue = !m_currentValue;
        CAutomate::getInstance()->requestStopEndCycleScheduler();
    }
    return m_currentValue;
}

