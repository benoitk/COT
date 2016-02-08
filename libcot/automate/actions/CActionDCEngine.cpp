#include "CActionDCEngine.h"

#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"

#include "qtimer.h"
#include "qthread.h"
CActionDCEngine::CActionDCEngine(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{

    CAutomate* automate = CAutomate::getInstance();
    m_varPump = automate->getVariable(mapAction[QStringLiteral("target")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide
    m_varClockwise = automate->getVariable(mapAction[QStringLiteral("clockwise")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide
    m_varTimeout = automate->getVariable(mapAction[QStringLiteral("timeout")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide

}
QVariantMap CActionDCEngine::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("target"), m_varPump->getName());
    mapSerialize.insert(QStringLiteral("clockwise"), m_varClockwise->getName());
    mapSerialize.insert(QStringLiteral("timeout"), m_varTimeout->getName());

    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("cmd_dc_engine"));
    return mapSerialize;
}
CActionDCEngine::~CActionDCEngine()
{
    foreach(QTimer* timer, m_mapTimer){
        while(timer->isActive())
            delete timer;
    }
}

void CActionDCEngine::abortAction(){
    foreach(QTimer* timer, m_mapTimer){
        timer->stop();
    }
    slotTimeout();
}

bool CActionDCEngine::runAction(ICycle* arg_stepParent){
    qCDebug(COTAUTOMATE_LOG)<< "Action commande pompe cc "
            << " label fr " << m_label
            << " clockwise " << m_varClockwise->toString()
            << " timout " << m_varTimeout->toString();
    QThread* currentThread = QThread::currentThread();
    m_varClockwise->setValue(m_varClockwise->toInt()); //évite le cast pour faire un write sur le bus de com
    m_varPump->setValue(true);
    if(!m_mapTimer.contains(currentThread)){
        QTimer* timer = new QTimer();
        m_mapTimer.insert(currentThread, timer);
        timer->setSingleShot(true);
        connect(timer, &QTimer::timeout, this, &CActionDCEngine::slotTimeout);
    }
    m_mapTimer.value(currentThread)->stop();
    m_mapTimer.value(currentThread)->start(m_varTimeout->toInt()*1000);
    return true;
}
void CActionDCEngine::slotTimeout(){
    qCDebug(COTAUTOMATE_LOG)<< "Arrêt pompe cc ";
    m_varPump->setValue(false);
}

QList<IVariable*> CActionDCEngine::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_varPump);
    listParams.append(m_varClockwise);
    listParams.append(m_varTimeout);

    return listParams;
}
actionType CActionDCEngine::getType()const {
    return actionType::type_cmd_dc_engine;
}

bool CActionDCEngine::variableUsed(IVariable *arg_var)const {
    if(m_varPump == arg_var) return true;
    if(m_varTimeout== arg_var) return true;
    if(m_varClockwise == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionDCEngine::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("target engine"), m_varPump);
    map.insert(tr("Clockwise way"), m_varClockwise);
    map.insert(tr("Drive time"), m_varTimeout);
    return map;
}

QMap<QString, IVariable*> CActionDCEngine::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionDCEngine::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("target engine")== arg_key) m_varPump= arg_parameter;
    else if(tr("Clockwise way")== arg_key)m_varClockwise= arg_parameter;
    else if(tr("Drive time")== arg_key)m_varTimeout= arg_parameter;

}
enumVariableType CActionDCEngine::getWaitedType(const QString& arg_key){
    if(tr("target engine")== arg_key) return e_type_bool;
    else if(tr("Clockwise way")== arg_key) return e_type_int;
    else if(tr("Drive time")== arg_key) return e_type_int;

    return e_type_unknow;
}
