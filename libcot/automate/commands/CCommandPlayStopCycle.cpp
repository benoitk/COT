#include "CCommandPlayStopCycle.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "CAutomate.h"

#include <QTimer>

CCommandPlayStopCycle::CCommandPlayStopCycle(const QVariantMap &mapCmd, QObject *parent):ICommand(mapCmd, parent)
{
    CAutomate* a = CAutomate::getInstance();
    m_inputVariable = a->getVariable( mapCmd.value(QStringLiteral("input")).toString());
    connect(m_inputVariable, &IVariable::signalVariableChanged, this, &ICommand::slotRunCommand);

    slotReadInput();
    slotRunCommand();

}

void CCommandPlayStopCycle::slotRunCommand(){
    if(m_inputVariable->toBool() && !m_oldValue){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestPlayScheduler();
    }
    else if( (!m_inputVariable->toBool()) && m_oldValue)
    {
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestStopScheduler();
    }

}

void CCommandPlayStopCycle::slotReadInput(){
    if(m_inputVariable && m_inputVariable->getOrganType() == e_type_organ_input){
        dynamic_cast<IVariableInput*>(m_inputVariable)->readValue();
        QTimer::singleShot(500, this, SLOT(slotReadInput()));
    }
}

bool CCommandPlayStopCycle::getStateCommand(){
    return m_inputVariable->toBool();
}
