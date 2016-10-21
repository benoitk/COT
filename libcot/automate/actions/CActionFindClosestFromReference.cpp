#include "CActionFindClosestFromReference.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionFindClosestFromReference::CActionFindClosestFromReference(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{

    m_ref = m_automate->getVariable(mapAction[QStringLiteral("reference")].toString());
    m_result = m_automate->getVariable(mapAction[QStringLiteral("result")].toString());
    QStringList list = mapAction[QStringLiteral("variables")].toStringList();
    foreach(QString varName, list){
        IVariable* var = m_automate->getVariable(varName);
        if(var->getType() != e_type_unknow) m_listVar.append(var);
    }
}
QVariantMap CActionFindClosestFromReference::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("reference"), m_ref->getIVariable()->getName());
    mapSerialize.insert(QStringLiteral("result"), m_result->getIVariable()->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("find_closest_from_reference"));
    QStringList list;
    foreach(IVariable* var, m_listVar){
        list.append(var->getName());
    }
    mapSerialize.insert(QStringLiteral("variables"), list);

    return mapSerialize;
}

CActionFindClosestFromReference::~CActionFindClosestFromReference(){

}


bool CActionFindClosestFromReference::runAction(ICycle* arg_stepParent){

    qCDebug(COTAUTOMATE_LOG)<< "Action find_closest_from_reference ";
    if(!m_listVar.isEmpty()){
        QList<IVariable*>::iterator it = m_listVar.begin();
        float diff = 0;
        float diffPrecedent = fabs(m_ref->toFloat() - (*it)->toFloat());
        IVariable* closestVar = (*it++);

        for(;it!=m_listVar.end(); ++it){
            diff= fabs(m_ref->toFloat() - (*it)->toFloat());
            if(diff < diffPrecedent){
                closestVar = (*it);
                diffPrecedent = diff;
            }
        }

        m_result->setValue(closestVar->toVariant());
    }
    return true;
}

QList<IVariable*> CActionFindClosestFromReference::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_ref);

    return listParams;
}
actionType CActionFindClosestFromReference::getType()const {
    return actionType::type_find_closest_value;
}

bool CActionFindClosestFromReference::variableUsed(IVariable *arg_var)const {
    if(m_ref == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionFindClosestFromReference::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("target"), m_ref);
    return map;
}

QMap<QString, IVariable*> CActionFindClosestFromReference::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionFindClosestFromReference::setParameter(const QString& arg_key, IVariable* arg_parameter){
   if(tr("Target")== arg_key)m_ref= arg_parameter;
 }
enumVariableType CActionFindClosestFromReference::getWaitedType(const QString& arg_key){
    if(tr("Target")== arg_key) return e_type_bool;

    return e_type_unknow;
}

