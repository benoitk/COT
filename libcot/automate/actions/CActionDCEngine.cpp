#include "CActionDCEngine.h"

#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"

#include "qtimer.h"

CActionDCEngine::CActionDCEngine(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_varPump = automate->getVariable(mapAction[QStringLiteral("target")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide
    m_varClockwise = automate->getVariable(mapAction[QStringLiteral("clockwise")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide
    m_varTimeout = automate->getVariable(mapAction[QStringLiteral("timeout")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide

}

CActionDCEngine::~CActionDCEngine()
{

}


bool CActionDCEngine::runAction(){
    qCDebug(COTAUTOMATE_LOG)<< "Action commande pompe cc "
            << " label fr " << m_label
            << " clockwise " << m_varClockwise->toString()
            << " timout " << m_varTimeout->toString();

    m_varClockwise->setValue(m_varClockwise->toInt()); //évite le cast pour faire un write sur le bus de com
    m_varPump->setValue(true);


    QTimer::singleShot(m_varTimeout->toInt()*1000, this, SLOT(slotTimeout()));
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
void CActionDCEngine::setParameter(QString arg_key, IVariable* arg_parameter){
    if(tr("target engine")== arg_key) m_varPump= arg_parameter;
    else if(tr("Clockwise way")== arg_key)m_varClockwise= arg_parameter;
    else if(tr("Drive time")== arg_key)m_varTimeout= arg_parameter;

}
