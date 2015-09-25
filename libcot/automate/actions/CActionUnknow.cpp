#include "CActionUnknow.h"

#include "cotautomate_debug.h"

CActionUnknow::CActionUnknow(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    m_name =  QStringLiteral("unknow_action");
}

CActionUnknow::~CActionUnknow()
{
}

bool CActionUnknow::runAction(ICycle* arg_stepParent){
    qCDebug(COTAUTOMATE_LOG) <<  "Action inconnu " ;
    return true;
}



QList<IVariable*> CActionUnknow::getListParameters()const{
    QList<IVariable*> listParams;
    return listParams;
}
actionType CActionUnknow::getType()const {
    return actionType::type_action_unknow;
}
bool CActionUnknow::variableUsed(IVariable *)const {
    return false;
}

QMap<QString, IVariable*> CActionUnknow::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}

QMap<QString, IVariable*> CActionUnknow::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionUnknow::setParameter(const QString& arg_key, IVariable* arg_parameter){

}

enumVariableType CActionUnknow::getWaitedType(const QString& arg_key){
    return e_type_unknow;
}
QVariantMap CActionUnknow::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("unknow"));
    return mapSerialize;
}
