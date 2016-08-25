#include "CActionWaitForAction.h"
#include "IVariable.h"
#include "CVariableAlarm.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "cotautomate_debug.h"
#include "CUnit.h"
#include "qmap.h"
#include "qthreadpool.h"

CActionWaitForAction::CActionWaitForAction(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    IVariable* var = Q_NULLPTR;

    CAutomate* automate = CAutomate::getInstance();
    m_listActionNamesToWait = mapAction[QStringLiteral("actions")].toStringList();


    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}
QVariantMap CActionWaitForAction::serialize(){
    QVariantMap mapSerialize = IAction::serialize();

    mapSerialize.insert(QStringLiteral("actions"), m_listActionNamesToWait);



    return mapSerialize;
}
CActionWaitForAction::~CActionWaitForAction()
{

}

bool CActionWaitForAction::runAction(ICycle* arg_stepParent){
    IAction::runAction(arg_stepParent);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = QThreadPool::globalInstance()->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CActionAcquisitionCitNpoc::runAction";
        }
    }
    return true;
}

void CActionWaitForAction::run(){
     qCDebug(COTAUTOMATE_LOG)<< "Action CActionWaitForAction 'qrunnable' "
            << " label fr " << m_label
         ;

    m_listActionConnectedToWait.clear();

    foreach(QString actionName, m_listActionNamesToWait){
        IAction *action;
        if( (action = CAutomate::getInstance()->getAction(actionName)) && action->getType() != type_action_unknow){
            connect(action, &IAction::signalActionFinished, this, &CActionWaitForAction::slotActionFinished);
            m_listActionConnectedToWait.append(action);
        }
    }


}

void CActionWaitForAction::slotActionFinished(IAction* arg_action){
    if(m_listActionConnectedToWait.removeOne(arg_action))
        disconnect(arg_action, &IAction::signalActionFinished, this, &CActionWaitForAction::slotActionFinished);

    if(m_listActionConnectedToWait.isEmpty())
        emit signalActionFinished(this);
}

bool CActionWaitForAction::waitUntilFinished(){
    return true;
}


QList<IVariable*> CActionWaitForAction::getListParameters()const{
    QList<IVariable*> listParams;

    return listParams;
}

QMap<QString, IVariable*> CActionWaitForAction::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}

QMap<QString, IVariable*> CActionWaitForAction::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
actionType CActionWaitForAction::getType()const {
    return actionType::type_wait_for_action;
}

bool CActionWaitForAction::variableUsed(IVariable *arg_var)const {

    return false;
}
void CActionWaitForAction::setParameter(const QString& arg_key, IVariable* arg_parameter){

}
enumVariableType CActionWaitForAction::getWaitedType(const QString& arg_key){
    return e_type_unknow;
}
