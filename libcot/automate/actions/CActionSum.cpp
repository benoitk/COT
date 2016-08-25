#include "CActionSum.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"
CActionSum::CActionSum(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    QStringList listVarName = mapAction[QStringLiteral("input_variables")].toStringList();
    foreach(QString varName, listVarName){
        m_listVar.append(automate->getVariable(varName));
    }
}


QVariantMap CActionSum::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("result"), m_result->getName());

    QStringList listVarName;
    foreach (IVariable* var, m_listVar) {
        listVarName.append(var->getName());
    }
    mapSerialize.insert(QStringLiteral("input_variables"), listVarName);

    return mapSerialize;
}


bool CActionSum::runAction(ICycle* arg_stepParent){

    float tmp=0;
    foreach (IVariable* var, m_listVar) {
        tmp += var->toFloat();
    }
    m_result->setValue(tmp);
    return true;
}


QList<IVariable*> CActionSum::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_result);

    return listParams;
}
actionType CActionSum::getType()const {
    return actionType::type_sum;
}

bool CActionSum::variableUsed(IVariable *arg_var)const {

    if(m_result == arg_var) return true;
     foreach (IVariable* var, m_listVar) {
         if(var == arg_var) return true;
     }

    return false;
}

QMap<QString, IVariable*> CActionSum::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Result"), m_result);
    return map;
}

QMap<QString, IVariable*> CActionSum::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionSum::setParameter(const QString& arg_key, IVariable* arg_parameter){

    if(tr("Result")== arg_key)m_result= arg_parameter;


}
enumVariableType CActionSum::getWaitedType(const QString& arg_key){
    if(tr("Result")== arg_key) return e_type_float;

    return e_type_unknow;
}
