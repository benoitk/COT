#include "CActionRewriteOutput.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionRewriteOutput::CActionRewriteOutput(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{
    m_varDigitalOutput = m_automate->getVariable(mapAction[QStringLiteral("target")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide

}
QVariantMap CActionRewriteOutput::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("target"), m_varDigitalOutput->getIVariable()->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("rewrite_output"));
    return mapSerialize;
}
CActionRewriteOutput::~CActionRewriteOutput()
{

}


bool CActionRewriteOutput::runAction(ICycle* arg_stepParent){
    m_varDigitalOutput->setValue(m_varDigitalOutput->toVariant());
    qCDebug(COTAUTOMATE_LOG)<< "Action rewrite output "
            << " label fr " << m_label
            << " Etat relais " << m_varDigitalOutput->toString();
    return true;
}

QList<IVariable*> CActionRewriteOutput::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_varDigitalOutput);

    return listParams;
}
actionType CActionRewriteOutput::getType()const {
    return actionType::type_rewrite_output;
}

bool CActionRewriteOutput::variableUsed(IVariable *arg_var)const {
    if(m_varDigitalOutput == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionRewriteOutput::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("target"), m_varDigitalOutput);
    return map;
}

QMap<QString, IVariable*> CActionRewriteOutput::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionRewriteOutput::setParameter(const QString& arg_key, IVariable* arg_parameter){
   if(tr("Target")== arg_key)m_varDigitalOutput= arg_parameter;
 }
enumVariableType CActionRewriteOutput::getWaitedType(const QString& arg_key){
    if(tr("Target")== arg_key) return e_type_bool;

    return e_type_unknow;
}
