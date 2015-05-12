#include "CActionBlock.h"
#include "IVariable.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"

CActionBlock::CActionBlock(const QVariantMap &mapAction)
	: IAction()
{
	m_label = mapAction[tr("FR_lbl")].toString();
    m_name = mapAction[QStringLiteral("name")].toString();
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


QString CActionBlock::getName()const{
	return m_name; 
}

QList<IVariable*> CActionBlock::getListParameters()const{
	QList<IVariable*> listParams;
	return listParams;
}
QString CActionBlock::getLabel()const{
    return m_label;
}
void CActionBlock::setLabel(const QString& lbl){
    m_label = lbl;
}
actionType CActionBlock::getType()const {
    return actionType::type_block;
}
