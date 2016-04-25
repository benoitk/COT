#include "CCommandPlayStopCycle.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "CAutomate.h"

#include <QTimer>

CCommandPlayStopCycle::CCommandPlayStopCycle(const QVariantMap &mapCmd, QObject *parent):ICommand(mapCmd, parent)
{
    CAutomate* a = CAutomate::getInstance();
    m_inputVariable = a->getVariable( mapCmd.value(QStringLiteral("input_variable")).toString());
    if(m_inputVariable->getType() != e_type_unknow)
        connect(m_inputVariable, &IVariable::signalVariableChanged, this, &ICommand::slotRunCommand);
    m_oldValue = false;
    slotReadInput();
    slotRunCommand();

}

bool CCommandPlayStopCycle::slotRunCommand(IVariable* arg_var){
    //si arg_var =  Q_NULLPTR -> IHM
    if(arg_var==m_inputVariable && m_inputVariable->toBool()
            && !m_oldValue && !CAutomate::getInstance()->isLocalControlForced()){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestPlayScheduler();
    }
    else if( (arg_var==m_inputVariable && !m_inputVariable->toBool())
             && m_oldValue && !CAutomate::getInstance()->isLocalControlForced()){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestStopScheduler();
    }
    else if(arg_var== Q_NULLPTR && (m_inputVariable->getType() == e_type_unknow || CAutomate::getInstance()->isLocalControlForced()) && !m_oldValue){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestPlayScheduler();
    }
    else if(arg_var== Q_NULLPTR && (m_inputVariable->getType() == e_type_unknow || CAutomate::getInstance()->isLocalControlForced())&& m_oldValue){
        m_oldValue = !m_oldValue;
        CAutomate::getInstance()->requestStopScheduler();
    }
    return m_oldValue;
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
QVariantMap CCommandPlayStopCycle::serialize(){
    QVariantMap mapSerialise = ICommand::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("cmd_play_stop_cycle"));
    mapSerialise.insert(QStringLiteral("input_variable"), m_inputVariable->getName());
    return mapSerialise;
}
