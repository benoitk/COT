#include "CCommandStopEndCycle.h"
#include "IVariable.h"
#include "CAutomate.h"

CCommandStopEndCycle::CCommandStopEndCycle(const QVariantMap &mapCmd, QObject *parent):CCommandPlayStopCycle(mapCmd, parent)
{

}

bool CCommandStopEndCycle::slotRunCommand(IVariable* arg){
    if(!m_inputVariable->toBool() && m_oldValue){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestPlayScheduler();
    }
    else if( (m_inputVariable->toBool()) && !m_oldValue)
    {
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestStopEndCycleScheduler();
    }
    return m_oldValue;
}

