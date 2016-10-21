#include "CCommandStopEndCycle.h"
#include "IVariable.h"
#include "CAutomate.h"

CCommandStopEndCycle::CCommandStopEndCycle(const QVariantMap &mapCmd, CAutomate *parent):CCommandPlayStopCycle(mapCmd, parent)
{

}

bool CCommandStopEndCycle::slotRunCommand(bool arg_externalCmdOnly){
    if(m_inputVariable->getType() != e_type_unknow && m_inputVariable->toBool()
            && !m_currentValue && !m_automate->isLocalControlForced() ){
        m_currentValue = !m_currentValue;
        m_automate->requestCancelStopEndCycleScheduler();
        if (!m_cmdStop || m_cmdStop->getStateCommand())
            m_automate->requestPlayScheduler();
    }
    else if( (m_inputVariable->getType() != e_type_unknow && !m_inputVariable->toBool())
             && m_currentValue && !m_automate->isLocalControlForced()){
        m_currentValue = !m_currentValue;
        m_automate->requestStopEndCycleScheduler();
    }
    else if( (m_inputVariable->getType() == e_type_unknow || m_automate->isLocalControlForced())
             && !m_currentValue && !arg_externalCmdOnly ){
        m_currentValue = !m_currentValue;
        m_automate->requestCancelStopEndCycleScheduler();
        if (!m_cmdStop || m_cmdStop->getStateCommand())
            m_automate->requestPlayScheduler();
    }
    else if((m_inputVariable->getType() == e_type_unknow || m_automate->isLocalControlForced())&& m_currentValue && !arg_externalCmdOnly){
        m_currentValue = !m_currentValue;
        m_automate->requestStopEndCycleScheduler();
    }
    return m_currentValue;
}

