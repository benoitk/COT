#include "CStep.h"
#include "IAction.h"
#include "CAutomate.h"
#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"

CStep::CStep(const QMap<QString, QVariant> &mapStep)
	: QObject()
{
    
    m_numStep = mapStep.value(QStringLiteral("step")).toFloat();
    m_label = mapStep.value(tr("fr_FR")).toString();
    const QVariantList listActions = mapStep.value(QStringLiteral("actions")).toList();
    foreach(const QVariant &varAction, listActions){
        const QString actionName = varAction.toString();
        IAction* action = CAutomate::getInstance()->getAction(actionName);
        if(action->getType() != actionType::type_action_unknow){
            m_listActions.append(action);
        }else{
            qCDebug(COTAUTOMATE_LOG) << "CStep::CStep Action inconue";
        }
    }
}

CStep::~CStep()
{

}

QString CStep::getLabel()const{
	return m_label;
}
void CStep::setLabel(const QString &label){
	m_label = label;
}
QList<IAction*> CStep::getListActions()const{
	return m_listActions;
}
float CStep::getNumStep()const{
	return m_numStep;
}
void CStep::setNumStep(float numStep){
	m_numStep = numStep;
}
//CStep* CStep::getNextStep()const{
//	return m_nextStep;
//}
//void CStep::setNextStep(CStep* step){
//	m_nextStep = step;
//}
void CStep::execStep(){
    foreach(IAction* action, m_listActions){
        action->runAction();
    }
}