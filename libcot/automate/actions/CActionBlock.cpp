#include "CActionBlock.h"
#include "IVariable.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"

CActionBlock::CActionBlock(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{

}

CActionBlock::~CActionBlock()
{

}

void CActionBlock::setActions(const QList<IAction *> &actions)
{
    m_actions = actions;
}

QList<IAction *> CActionBlock::actions() const
{
    return m_actions;
}

bool CActionBlock::runAction(){
    qCDebug(COTAUTOMATE_LOG) << "Running action block" << getName();
    foreach (IAction *action, m_actions) {
        if (!action->runAction())
            return false;
    }
    return true;
}




QList<IVariable*> CActionBlock::getListParameters()const{
    QList<IVariable*> listParams;
    return listParams;
}

actionType CActionBlock::getType()const {
    return actionType::type_block;
}
bool CActionBlock::variableUsed(IVariable *)const {
    //bool bReturn = false;
    //foreach(IAction* action, m_listAction){if(action->variableUsed()) bReturn=true;}
    return false;
}
