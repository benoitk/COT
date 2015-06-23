#include "CActionCmdDigitalOutput.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"



CActionCmdDigitalOutput::CActionCmdDigitalOutput(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_varDigitalOutput = automate->getVariable(mapAction[QStringLiteral("target")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide
    m_state = mapAction[QStringLiteral("state")].toBool();

}

CActionCmdDigitalOutput::~CActionCmdDigitalOutput()
{

}


bool CActionCmdDigitalOutput::runAction(){
    m_varDigitalOutput->setValue(QVariant(m_state));
    qCDebug(COTAUTOMATE_LOG)<< "Action relay "
            << " label fr " << m_label
            << " Etat relais " << m_varDigitalOutput->toString();
    return true;
}

QList<IVariable*> CActionCmdDigitalOutput::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_varDigitalOutput);

    return listParams;
}
actionType CActionCmdDigitalOutput::getType()const {
    return actionType::type_cmd_digital_output;
}

bool CActionCmdDigitalOutput::variableUsed(IVariable *arg_var)const {
    if(m_varDigitalOutput == arg_var) return true;

    return false;
}
