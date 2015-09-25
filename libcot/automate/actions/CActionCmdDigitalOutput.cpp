#include "CActionCmdDigitalOutput.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"



CActionCmdDigitalOutput::CActionCmdDigitalOutput(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_varDigitalOutput = automate->getVariable(mapAction[QStringLiteral("target")].toString()); //l'automate assure qu'il n'y ai pas de pointeur vide

    QVariantMap variantMap;
    variantMap.insert(QStringLiteral("name"), QStringLiteral("state"));
    variantMap.insert(QStringLiteral("fr_FR"), tr("State output"));
    variantMap.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    variantMap.insert(QStringLiteral("value"), mapAction[QStringLiteral("state")].toBool());
    m_state = dynamic_cast<CVariableBool*>(CVariableFactory::build(variantMap));


}

CActionCmdDigitalOutput::~CActionCmdDigitalOutput()
{

}
QVariantMap CActionCmdDigitalOutput::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("target"), m_varDigitalOutput->getName());
    mapSerialize.insert(QStringLiteral("state"), m_state->toBool());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("cmd_digital_output"));
    return mapSerialize;
}

bool CActionCmdDigitalOutput::runAction(ICycle* arg_stepParent){
    m_varDigitalOutput->setValue(QVariant(m_state->toBool()));
    qCDebug(COTAUTOMATE_LOG)<< "Action relay "
            << " label fr " << m_label
            << " Etat relais " << m_varDigitalOutput->toString();
    return true;
}

QList<IVariable*> CActionCmdDigitalOutput::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_varDigitalOutput);

    return listParams;
}
actionType CActionCmdDigitalOutput::getType()const {
    return actionType::type_cmd_digital_output;
}

bool CActionCmdDigitalOutput::variableUsed(IVariable *arg_var)const {
    if(m_varDigitalOutput == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionCmdDigitalOutput::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("target"), m_varDigitalOutput);
    return map;
}

QMap<QString, IVariable*> CActionCmdDigitalOutput::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Open"), m_state);
    return map;
}
void CActionCmdDigitalOutput::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("Target")== arg_key)m_varDigitalOutput= arg_parameter;
    if(tr("Open")== arg_key)m_state->setValue(arg_parameter->toBool());

}
enumVariableType CActionCmdDigitalOutput::getWaitedType(const QString& arg_key){
   //peu importe

    return e_type_unknow;
}
