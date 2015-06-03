#include "CActionCmdRelay.h"
#include "IVariable.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionCmdRelay::CActionCmdRelay(QObject *parent)
    : IAction(parent)
{

}
CActionCmdRelay::CActionCmdRelay(const QVariantMap &mapAction)
    : IAction(mapAction)
{
    CAutomate* automate = CAutomate::getInstance();
    m_RelayVar = automate->getVariable(mapAction[QStringLiteral("num_card_output")].toString());


}
CActionCmdRelay::CActionCmdRelay()
    : IAction()
{

}

CActionCmdRelay::~CActionCmdRelay()
{

}


bool CActionCmdRelay::runAction(){
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
