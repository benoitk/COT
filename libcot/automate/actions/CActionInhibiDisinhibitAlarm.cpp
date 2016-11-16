#include "CActionInhibiDisinhibitAlarm.h"
#include "IVariable.h"
#include "CVariableAlarm.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"
CActionInhibiDisinhibitAlarm::CActionInhibiDisinhibitAlarm(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{

    IVariable* var = m_automate->getVariable(mapAction[QStringLiteral("alarm")].toString());
    m_state = mapAction[QStringLiteral("state")].toBool();

    if(var->getType() == e_type_alarm)
        m_alarm = dynamic_cast<CVariableAlarm*>(var);
    else
        m_alarm = Q_NULLPTR;
}


QVariantMap CActionInhibiDisinhibitAlarm::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("cmd_inhibit_desinhibit_alarm"));
    if(m_alarm)
        mapSerialize.insert(QStringLiteral("alarm"), m_alarm->getName());
    else
        mapSerialize.insert(QStringLiteral("alarm"), tr("No alarm set"));
    mapSerialize.insert(QStringLiteral("state"), m_state);

    return mapSerialize;
}


bool CActionInhibiDisinhibitAlarm::runAction(ICycle* arg_stepParent){
    if(m_alarm)
        m_alarm->setInhibited(m_state);
    return true;
}


QList<IVariable*> CActionInhibiDisinhibitAlarm::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_alarm);

    return listParams;
}
actionType CActionInhibiDisinhibitAlarm::getType()const {
    return actionType::type_inhibit_disinhibit_alarm;
}

bool CActionInhibiDisinhibitAlarm::variableUsed(IVariable *arg_var)const {

    if(m_alarm == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionInhibiDisinhibitAlarm::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("alarm"), m_alarm);
    return map;
}

QMap<QString, IVariable*> CActionInhibiDisinhibitAlarm::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionInhibiDisinhibitAlarm::setParameter(const QString& arg_key, IVariable* arg_parameter){




}
enumVariableType CActionInhibiDisinhibitAlarm::getWaitedType(const QString& arg_key){
    if(tr("alarm")== arg_key) return e_type_float;

    return e_type_unknow;
}
