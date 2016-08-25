#include "CActionFindBiggerValue.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionFindBiggerValue::CActionFindBiggerValue(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_lowLimit = automate->getVariable(mapAction[QStringLiteral("low_limit")].toString());
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    QStringList list = mapAction[QStringLiteral("variables")].toStringList();
    foreach(QString varName, list){
        IVariable* var = automate->getVariable(varName);
        if(var->getType() != e_type_unknow) m_listVar.append(var);
    }
}
QVariantMap CActionFindBiggerValue::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("low_limit"), m_lowLimit->getIVariable()->getName());
    mapSerialize.insert(QStringLiteral("result"), m_result->getIVariable()->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("find_bigger_value"));
    QStringList list;
    foreach(IVariable* var, m_listVar){
        list.append(var->getName());
    }
    mapSerialize.insert(QStringLiteral("variables"), list);

    return mapSerialize;
}

CActionFindBiggerValue::~CActionFindBiggerValue(){

}


bool CActionFindBiggerValue::runAction(ICycle* arg_stepParent){

    qCDebug(COTAUTOMATE_LOG)<< "Action find_bigger_value ";
    float result = m_lowLimit->toFloat();
    foreach (IVariable* var, m_listVar) {
        if(result < var->toFloat())
            result = var->toFloat();
    }
    m_result->setValue(result);
    return true;
}

QList<IVariable*> CActionFindBiggerValue::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_lowLimit);

    return listParams;
}
actionType CActionFindBiggerValue::getType()const {
    return actionType::type_find_bigger_value;
}

bool CActionFindBiggerValue::variableUsed(IVariable *arg_var)const {
    if(m_lowLimit == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionFindBiggerValue::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("target"), m_lowLimit);
    return map;
}

QMap<QString, IVariable*> CActionFindBiggerValue::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionFindBiggerValue::setParameter(const QString& arg_key, IVariable* arg_parameter){
   if(tr("Target")== arg_key)m_lowLimit= arg_parameter;
 }
enumVariableType CActionFindBiggerValue::getWaitedType(const QString& arg_key){
    if(tr("Target")== arg_key) return e_type_bool;

    return e_type_unknow;
}

