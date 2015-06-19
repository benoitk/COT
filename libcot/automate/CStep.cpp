#include "CStep.h"
#include "IAction.h"
#include "CAutomate.h"
#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"

#include "qthread.h"

CStep::CStep(const QVariantMap &mapStep)
    : QObject(), m_bWaitForActions(false), m_errorDuringActions(false)
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
    //ne pas supprimer les actions de m_listActions.
}
QVariantMap CStep::serialise(){
    QVariantMap mapSerialise;
//    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("measure"));
    QStringList listActionName;
    foreach(IAction* action, m_listActions){
        listActionName.append(action->getName());
    }
    mapSerialise.insert(QStringLiteral("actions"), listActionName);
    return mapSerialise;
}
void CStep::addAction(IAction* arg_action){
    if(arg_action){
        if (!m_listActions.contains(arg_action)) {
            m_listActions.append(arg_action);
        }
    }
}
void CStep::removeAction(IAction* arg_action){
    if(arg_action){
        m_listActions.removeOne(arg_action);
    }
}

void CStep::setListActions(const QList<IAction *> &actions)
{
    m_listActions = actions;
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
//    return m_nextStep;
//}
//void CStep::setNextStep(CStep* step){
//    m_nextStep = step;
//}

//true si pas d'erreur, false sinon
bool CStep::execStep(){
    m_errorDuringActions = false;

    foreach(IAction* action, m_listActions){
        if(action->waitUnitlFinished()){
            m_listActionsWaited.append(action);
            connect(action, &IAction::signalActionFinished, this, &CStep::slotActionFinished);
            m_bWaitForActions=true;
        }
        action->runAction();
//        if(action->finishedWithError()){
//            m_errorDuringActions = true;
//        }
    }
    while(m_bWaitForActions || m_errorDuringActions){
        QThread::usleep(10000);
    }

    return !m_errorDuringActions;
}

void CStep::slotActionFinished(IAction* action){
    if(m_listActionsWaited.removeOne(action)){
        disconnect(action,0,this,0);
        if(action->finishedWithError()){
            m_errorDuringActions = true;
        }
    }
    if(m_listActionsWaited.isEmpty()) m_bWaitForActions = false;
}


