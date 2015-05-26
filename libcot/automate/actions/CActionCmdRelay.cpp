#include "CActionCmdRelay.h"
#include "IVariable.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionCmdRelay::CActionCmdRelay(QObject *parent)
    : IAction(parent)
{

}
CActionCmdRelay::CActionCmdRelay(const QVariantMap &mapAction)
    : IAction()
{
    m_label = mapAction[tr("FR_lbl")].toString();
    m_name = mapAction[QStringLiteral("name")].toString();

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


QString CActionCmdRelay::getName()const{
    return m_name;
}

QList<IVariable*> CActionCmdRelay::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_RelayVar);

    return listParams;
}
QString CActionCmdRelay::getLabel()const{
    return m_label;
}
void CActionCmdRelay::setLabel(const QString& lbl){
    m_label = lbl;
}
actionType CActionCmdRelay::getType()const {
    return actionType::type_cmd_relay;
}

bool CActionCmdRelay::variableUsed(IVariable *arg_var)const {
    if(m_RelayVar == arg_var) return true;

    return false;
}
