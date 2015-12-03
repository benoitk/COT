#include "CStep.h"
#include "IAction.h"
#include "ICycle.h"
#include "CAutomate.h"
#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"

#include <unistd.h>
#include "qthread.h"

CStep::CStep(){
    qDebug() << "Ne pas utiliser, uniquement là pour que l'ihm compile"; //A virer
}

CStep::CStep(ICycle *parent, const QVariantMap &mapStep)
    : QObject(parent), m_bWaitForActions(false),  m_parentCycle(parent)
{
    if(!mapStep.isEmpty()){
        m_numStep = mapStep.value(QStringLiteral("step")).toFloat();
        m_label = mapStep.value(tr("en_US")).toString();
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
    }else{
        m_numStep = 0;
        m_label = tr("Start cycle");
    }
}

CStep::~CStep()
{
    //ne pas supprimer les actions de m_listActions.
}
void CStep::abortStep(){
    foreach (IAction* action, m_listActions) {
        action->abortAction();
    }
}

QVariantMap CStep::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(tr("en_US"), m_label);
    QString nameStep = QString("step_") + QString::number(m_numStep*100, 'f', 1);
    mapSerialise.insert(QStringLiteral("name"), nameStep);
    mapSerialise.insert(QStringLiteral("step"), m_numStep);

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


void CStep::execStep(){
    qCDebug(COTAUTOMATE_LOG) << "CStep::execStep()";
    m_bWaitForActions = false;
    m_parentCycle->updateCycleInfosStep(m_numStep, m_label);

    foreach(IAction* action, m_listActions){
        if(action->waitUntilFinished()){
            m_listActionsWaited.append(action);
            connect(action, &IAction::signalActionFinished, this, &CStep::slotActionFinished);
            m_bWaitForActions=true;
        }
        action->runAction(m_parentCycle);
    }

    //si on doit attendre une action de celles lancées
    if(!m_bWaitForActions){
        qCDebug(COTAUTOMATE_LOG) << "CStep::execStep() EMIT ";
        emit signalStepFinished(this); 
    }
    qCDebug(COTAUTOMATE_LOG) << "FIN CStep::execStep()";
}

void CStep::slotActionFinished(IAction* action){

    QMutexLocker lock(&m_mutex);

    if(m_listActionsWaited.removeOne(action)){
        if(action)
            disconnect(action,0,this,0);
        else qDebug() << "fail disconnect " << action;
    }
    if(m_listActionsWaited.isEmpty()){
        emit signalStepFinished(this);
    }
}


