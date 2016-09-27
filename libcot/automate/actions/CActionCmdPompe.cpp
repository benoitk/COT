#include "CActionCmdPompe.h"

#include "CVariableString.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include <QThread>
#include "CVariableAlarm.h"
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
    m_default = Q_NULLPTR;
    m_alarm = Q_NULLPTR;
    if(automate->getVariable(mapAction[QStringLiteral("alim")].toString())->getOrganType() == e_type_organ_output)
        m_alim = dynamic_cast<CVariableOutputBool*>(automate->getVariable(mapAction[QStringLiteral("alim")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("nbr_turns")].toString())->getOrganType() == e_type_organ_output)
        m_nbTurns = dynamic_cast<CVariableOutputInt*>(automate->getVariable(mapAction[QStringLiteral("nbr_turns")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("nbr_steps")].toString())->getOrganType() == e_type_organ_output)
        m_nbSteps = dynamic_cast<CVariableOutputInt*>(automate->getVariable(mapAction[QStringLiteral("nbr_steps")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("clockwise")].toString())->getOrganType() == e_type_organ_output)
        m_clockwise =  dynamic_cast<CVariableOutputBool*>(automate->getVariable(mapAction[QStringLiteral("clockwise")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("speed")].toString())->getOrganType() == e_type_organ_output)
        m_speed =dynamic_cast<CVariableOutputInt*>( automate->getVariable(mapAction[QStringLiteral("speed")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("origin_return_before")].toString())->getOrganType() == e_type_organ_output)
        m_OriginReturn = dynamic_cast<CVariableOutputBool*>(automate->getVariable(mapAction[QStringLiteral("origin_return_before")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("default")].toString())->getOrganType() == e_type_organ_input)
        m_default = dynamic_cast<CVariableInputBool*>(automate->getVariable(mapAction[QStringLiteral("default")].toString()));
    if(automate->getVariable(mapAction[QStringLiteral("alarm")].toString())->getOrganType() == e_type_organ_output)
        m_alarm = dynamic_cast<CVariableAlarm*>(automate->getVariable(mapAction[QStringLiteral("alarm")].toString()));

    m_stepByStep = automate->getVariable(mapAction[QStringLiteral("pump_persulfate_step_by_step")].toString());


}
QVariantMap CActionCmdPompe::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    if(m_alim)
    mapSerialize.insert(QStringLiteral("alim"), m_alim->getName());
    else
        mapSerialize.insert(QStringLiteral("alim"), tr("UNKNOW VAR"));
    if(m_speed)
    mapSerialize.insert(QStringLiteral("speed"), m_speed->getName());
    else
        mapSerialize.insert(QStringLiteral("speed"), tr("UNKNOW VAR"));
    if(m_clockwise)mapSerialize.insert(QStringLiteral("clockwise"), m_clockwise->getName());
    else mapSerialize.insert(QStringLiteral("clockwise"), tr("UNKNOW VAR"));
    if(m_nbTurns)mapSerialize.insert(QStringLiteral("nbr_turns"), m_nbTurns->getName());
    else mapSerialize.insert(QStringLiteral("nbr_turns"), tr("UNKNOW VAR"));
    if(m_nbSteps)mapSerialize.insert(QStringLiteral("nbr_steps"), m_nbSteps->getName());
    else mapSerialize.insert(QStringLiteral("nbr_steps"), tr("UNKNOW VAR"));
    if(m_OriginReturn)mapSerialize.insert(QStringLiteral("origin_return_before"), m_OriginReturn->getName());
    else mapSerialize.insert(QStringLiteral("origin_return_before"), tr("UNKNOW VAR"));
    if(m_stepByStep)mapSerialize.insert(QStringLiteral("step_by_step"), m_stepByStep->getName());
    else mapSerialize.insert(QStringLiteral("step_by_step"), tr("UNKNOW VAR"));
    if(m_default)mapSerialize.insert(QStringLiteral("default"), m_default->getName());
    else mapSerialize.insert(QStringLiteral("default"), tr("UNKNOW VAR"));
    if(m_alarm)mapSerialize.insert(QStringLiteral("alarm"), m_alarm->getName());
    else mapSerialize.insert(QStringLiteral("alarm"), tr("UNKNOW VAR"));
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("cmd_pump"));

    return mapSerialize;
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


bool CActionCmdPompe::runAction(ICycle* arg_stepParent){
    qDebug() << "CActionCmdPompe::runAction" << m_alim->getName();

    if(m_alim && m_OriginReturn && m_clockwise && m_nbTurns && m_speed){
        if(!m_alim->toBool()) m_alim->setValue(true);

        m_alim->writeValue();
        QThread::msleep(5);

        m_clockwise->writeValue();
        QThread::msleep(5);

        m_speed->writeValue();
        QThread::msleep(5);

        if(m_stepByStep->toBool())
            m_nbSteps->writeValue();
        else
            m_nbTurns->writeValue();

        //m_nbSteps->writeValue();
        if(m_alarm)
            m_alarm->setValue(m_default->readValue()->toBool());
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
enumVariableType CActionCmdPompe::getWaitedType(const QString& arg_key){
   //peu importe

    return e_type_unknow;
}
