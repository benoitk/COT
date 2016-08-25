#include "CActionCopy.h"


#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"
CActionCopy::CActionCopy(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_target = automate->getVariable(mapAction[QStringLiteral("target")].toString());
    m_inputVar = automate->getVariable(mapAction[QStringLiteral("input_variable")].toString());

}


QVariantMap CActionCopy::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("target"), m_target->getName());
    mapSerialize.insert(QStringLiteral("input_variable"), m_inputVar->getName());

    return mapSerialize;
}


bool CActionCopy::runAction(ICycle* arg_stepParent){
    m_target->setValue(m_inputVar->toVariant());
    return true;
}


QList<IVariable*> CActionCopy::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_target);

    return listParams;
}
actionType CActionCopy::getType()const {
    return actionType::type_copy;
}

bool CActionCopy::variableUsed(IVariable *arg_var)const {

    if(m_target == arg_var) return true;
    if(m_inputVar == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionCopy::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Target"), m_target);
    map.insert(tr("Input Var"), m_inputVar);
    return map;
}

QMap<QString, IVariable*> CActionCopy::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionCopy::setParameter(const QString& arg_key, IVariable* arg_parameter){

    if(tr("Target")== arg_key)m_target= arg_parameter;
    if(tr("Input Var")== arg_key)m_inputVar= arg_parameter;


}
enumVariableType CActionCopy::getWaitedType(const QString& arg_key){
    if(tr("Target")== arg_key) return e_type_float;
    if(tr("Input Var")== arg_key) return e_type_float;

    return e_type_unknow;
}
