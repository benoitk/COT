#include "CActionCmdPompe.h"

#include "CVariableString.h"
#include "CVariableFactory.h"
#include "CAutomate.h"

#include "cotautomate_debug.h"


CActionCmdPompe::CActionCmdPompe(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();

    m_alim = Q_NULLPTR;
    m_nbTurns = Q_NULLPTR;
    m_nbSteps = Q_NULLPTR;
    m_clockwise = Q_NULLPTR;
    m_speed = Q_NULLPTR;
    m_OriginReturn = Q_NULLPTR;
    if(automate->getVariable(mapAction[QStringLiteral("alim")].toString())->getOrganType() == type_organ_output)
        m_alim = dynamic_cast<CVariableOutputBool*>(automate->getVariable(mapAction[QStringLiteral("alim")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("nbr_turns")].toString())->getOrganType() == type_organ_output)
        m_nbTurns = dynamic_cast<CVariableOutputInt*>(automate->getVariable(mapAction[QStringLiteral("nbr_turns")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("nbr_steps")].toString())->getOrganType() == type_organ_output)
        m_nbSteps = dynamic_cast<CVariableOutputInt*>(automate->getVariable(mapAction[QStringLiteral("nbr_steps")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("clockwise")].toString())->getOrganType() == type_organ_output)
        m_clockwise =  dynamic_cast<CVariableOutputBool*>(automate->getVariable(mapAction[QStringLiteral("clockwise")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("speed")].toString())->getOrganType() == type_organ_output)
        m_speed =dynamic_cast<CVariableOutputInt*>( automate->getVariable(mapAction[QStringLiteral("speed")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("origin_return_before")].toString())->getOrganType() == type_organ_output)
        m_OriginReturn = dynamic_cast<CVariableOutputBool*>(automate->getVariable(mapAction[QStringLiteral("origin_return_before")].toString()));
    m_stepByStep = automate->getVariable(mapAction[QStringLiteral("pump_persulfate_step_by_step")].toString());


}

CActionCmdPompe::~CActionCmdPompe()
{

}
QList<IVariable*> CActionCmdPompe::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_nbTurns);
    listParams.append(m_stepByStep);
    listParams.append(m_nbSteps);
    listParams.append(m_clockwise);
    listParams.append(m_speed);
    listParams.append(m_OriginReturn);

    return listParams;
}


bool CActionCmdPompe::runAction(){


    if(m_alim && m_OriginReturn && m_clockwise && m_nbTurns && m_speed){
        if(!m_alim->toBool()) m_alim->setValue(true);
        m_alim->writeValue();
        m_clockwise->writeValue();
        m_speed->writeValue();

        if(m_stepByStep->toBool())
            m_nbSteps->writeValue();
        else
            m_nbTurns->writeValue();
        //m_nbSteps->writeValue();
    }

    emit signalActionFinished(this);
    return true;
}

actionType CActionCmdPompe::getType()const {
    return actionType::type_cmd_pump;
}

bool CActionCmdPompe::variableUsed(IVariable * arg_var)const {
    if(m_alim == arg_var) return true;
    if(m_speed == arg_var) return true;
    if(m_nbSteps == arg_var) return true;
    if(m_clockwise == arg_var) return true;
    if(m_stepByStep == arg_var) return true;
    if(m_nbTurns == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionCmdPompe::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}

QMap<QString, IVariable*> CActionCmdPompe::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionCmdPompe::setParameter(const QString& arg_key, IVariable* arg_parameter){
//    if(tr("Setpoint")== arg_key) m_setpoint= arg_parameter;
//    else if(tr("Target")== arg_key)m_target= arg_parameter;
//    else if(tr("Result")== arg_key)m_result= arg_parameter;
//    else if(tr("Waiting")== arg_key)m_waiting= arg_parameter;
//    else if(tr("Error margin")== arg_key)m_errorMargin= arg_parameter;
//    else if(tr("Timeout")== arg_key)m_timeout= arg_parameter;²
//    else if(tr("Generate critical error")== arg_key)m_criticalError->setValue(arg_parameter->toBool());
}
variableType CActionCmdPompe::getWaitedType(const QString& arg_key){
   //peu importe

    return type_unknow;
}
