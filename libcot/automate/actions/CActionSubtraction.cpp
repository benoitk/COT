#include "CActionSubtraction.h"

#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"
CActionSubtraction::CActionSubtraction(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    m_diminuande = automate->getVariable(mapAction[QStringLiteral("diminuende_variable")].toString());
    QStringList listVarName = mapAction[QStringLiteral("subtrahend_variables")].toStringList();
    foreach(QString varName, listVarName){
        m_listVar.append(automate->getVariable(varName));
    }
}


QVariantMap CActionSubtraction::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("result"), m_result->getName());
    mapSerialize.insert(QStringLiteral("diminuende_variable"), m_diminuande->getName());

    QStringList listVarName;
    foreach (IVariable* var, m_listVar) {
        listVarName.append(var->getName());
    }
    mapSerialize.insert(QStringLiteral("subtrahend_variables"), listVarName);
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("subtraction"));
    return mapSerialize;
}


bool CActionSubtraction::runAction(ICycle* arg_stepParent){

    float tmp=m_diminuande->toFloat();
    foreach (IVariable* var, m_listVar) {
        tmp -= var->toFloat();
    }
    m_result->setValue(tmp);
    return true;
}


QList<IVariable*> CActionSubtraction::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_result);

    return listParams;
}
actionType CActionSubtraction::getType()const {
    return actionType::type_subtraction;
}

bool CActionSubtraction::variableUsed(IVariable *arg_var)const {

    if(m_result == arg_var) return true;
     foreach (IVariable* var, m_listVar) {
         if(var == arg_var) return true;
     }

    return false;
}

QMap<QString, IVariable*> CActionSubtraction::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Result"), m_result);
    return map;
}

QMap<QString, IVariable*> CActionSubtraction::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionSubtraction::setParameter(const QString& arg_key, IVariable* arg_parameter){

    if(tr("Result")== arg_key)m_result= arg_parameter;


}
enumVariableType CActionSubtraction::getWaitedType(const QString& arg_key){
    if(tr("Result")== arg_key) return e_type_float;

    return e_type_unknow;
}
