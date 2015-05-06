#include "CStep.h"
#include "IAction.h"
#include "CAutomate.h"
#include "qvariant.h"
#include "qmap.h"

CStep::CStep(const QMap<QString, QVariant> &mapStep)
	: QObject()
{
	const QVariantList listActions = mapStep.value(QStringLiteral("actions")).toList();
    foreach(const QVariant &varAction, listActions){
        const QVariantMap mapAction = varAction.toMap();
        if(mapAction.contains(QStringLiteral("name"))){
            IAction* action = CAutomate::getInstance()->getAction(mapAction.value(QStringLiteral("name")).toString());
            if(action->getName() != QStringLiteral("unknow_action")){
                m_listActions.append(action);
            }
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
CStep* CStep::getNextStep()const{
	return m_nextStep;
}
void CStep::setNextStep(CStep* step){
	m_nextStep = step;
}
void CStep::execStep(){
    foreach(IAction* action, m_listActions){
        action->runAction();
    }
}