#include "CActionUnknow.h"

#include "cotautomate_debug.h"
CActionUnknow::CActionUnknow(QObject *parent)
    : IAction(parent)
{
    m_name =  QStringLiteral("unknow_action");
}
CActionUnknow::CActionUnknow(const QVariantMap &mapAction)
    : IAction()
{
    m_name =  QStringLiteral("unknow_action");
}
CActionUnknow::CActionUnknow()
    : IAction()
{
    m_name =  QStringLiteral("unknow_action");
}
CActionUnknow::~CActionUnknow()
{
}

bool CActionUnknow::runAction(){
    qCDebug(COTAUTOMATE_LOG) <<  "Action inconnu " ;
    return true;
}



QList<IVariable*> CActionUnknow::getListParameters()const{
    QList<IVariable*> listParams;
    return listParams;
}
actionType CActionUnknow::getType()const {
    return actionType::type_action_unknow;
}
bool CActionUnknow::variableUsed(IVariable *)const {
    return false;
}
