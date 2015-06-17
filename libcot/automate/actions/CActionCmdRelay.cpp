#include "CActionCmdRelay.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"



CActionCmdRelay::CActionCmdRelay(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_RelayVar = automate->getVariable(mapAction[QStringLiteral("target")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide
    if(mapAction[QStringLiteral("state")].toString() == QStringLiteral("open"))
        m_stateOpen = true;
    else
        m_stateOpen = false;

}

CActionCmdRelay::~CActionCmdRelay()
{

}


bool CActionCmdRelay::runAction(){
    m_RelayVar->setValue(QVariant(m_stateOpen));
    qCDebug(COTAUTOMATE_LOG)<< "Action relay "
            << " label fr " << m_label
            << " Etat relais " << m_RelayVar->toString();
    return true;
}

QList<IVariable*> CActionCmdRelay::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_RelayVar);

    return listParams;
}
actionType CActionCmdRelay::getType()const {
    return actionType::type_cmd_relay;
}

bool CActionCmdRelay::variableUsed(IVariable *arg_var)const {
    if(m_RelayVar == arg_var) return true;

    return false;
}
