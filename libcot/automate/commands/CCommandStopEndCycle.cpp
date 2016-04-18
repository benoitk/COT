#include "CCommandStopEndCycle.h"
#include "IVariable.h"
#include "CAutomate.h"

CCommandStopEndCycle::CCommandStopEndCycle(const QVariantMap &mapCmd, QObject *parent):CCommandPlayStopCycle(mapCmd, parent)
{

}

void CCommandStopEndCycle::slotRunCommand(){
    if(!m_inputVariable->toBool() && m_oldValue){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestPlayScheduler();
    }
    else if( (m_inputVariable->toBool()) && !m_oldValue)
    {
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestStopEndCycleScheduler();
    }

}
