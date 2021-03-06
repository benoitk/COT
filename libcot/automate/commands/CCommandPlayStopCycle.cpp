#include "CCommandPlayStopCycle.h"
#include "CCommandStopEndCycle.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "CAutomate.h"

#include <QTimer>

CCommandPlayStopCycle::CCommandPlayStopCycle(const QVariantMap &mapCmd, CAutomate *parent):ICommand(mapCmd, parent)
{
    m_cmdStop = Q_NULLPTR;
    m_inputVariable = m_automate->getVariable( mapCmd.value(QStringLiteral("input_variable")).toString());
    if(m_inputVariable->getType() != e_type_unknow)
        connect(m_inputVariable, &IVariable::signalVariableChanged, this, &ICommand::slotRunCommand);
    m_currentValue = true;


}
void CCommandPlayStopCycle::setOtherCmdStop(CCommandPlayStopCycle* arg_cmd){
    if(arg_cmd)
        m_cmdStop = arg_cmd;

    slotReadInput();
    slotRunCommand(true);
}

bool CCommandPlayStopCycle::slotRunCommand(bool arg_externalCmdOnly){
    //si arg_var =  Q_NULLPTR -> IHM
    if(m_inputVariable->getType() != e_type_unknow && m_inputVariable->toBool()
            && !m_currentValue && !m_automate->isLocalControlForced() ){
        m_currentValue = !m_currentValue;
        if (!m_cmdStop || m_cmdStop->getStateCommand())
            m_automate->requestPlayScheduler();
    }
    else if( (m_inputVariable->getType() != e_type_unknow && !m_inputVariable->toBool())
             && m_currentValue && !m_automate->isLocalControlForced()){
        m_currentValue = !m_currentValue;
        m_automate->requestStopScheduler();
    }
    else if( (m_inputVariable->getType() == e_type_unknow || m_automate->isLocalControlForced())
             && !m_currentValue && !arg_externalCmdOnly ){
        m_currentValue = !m_currentValue;
        if (!m_cmdStop || m_cmdStop->getStateCommand())
        m_automate->requestPlayScheduler();
    }
    else if((m_inputVariable->getType() == e_type_unknow || m_automate->isLocalControlForced())&& m_currentValue && !arg_externalCmdOnly){
        m_currentValue = !m_currentValue;
        m_automate->requestStopScheduler();
    }
    return m_currentValue;
}

void CCommandPlayStopCycle::slotReadInput(){
    if(m_inputVariable && m_inputVariable->getOrganType() == e_type_organ_input){
        dynamic_cast<IVariableInput*>(m_inputVariable)->readValue();
        QTimer::singleShot(500, this, SLOT(slotReadInput()));
    }
}

bool CCommandPlayStopCycle::getStateCommand(){
    return m_currentValue;
}
QVariantMap CCommandPlayStopCycle::serialize(){
    QVariantMap mapSerialise = ICommand::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("cmd_play_stop_cycle"));
    mapSerialise.insert(QStringLiteral("input_variable"), m_inputVariable->getName());
    return mapSerialise;
}
