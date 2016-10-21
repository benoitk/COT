#include "CActionTest.h"
#include "IVariable.h"
#include "CVariableAlarm.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "cotautomate_debug.h"
#include "CUnit.h"
#include "qmap.h"
#include "qthreadpool.h"

CActionTest::CActionTest(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{
    IVariable* var = Q_NULLPTR;
    m_setpoint = m_automate->getVariable(mapAction[QStringLiteral("setpoint")].toString());

    m_waiting = m_automate->getVariable(mapAction[QStringLiteral("waiting")].toString());
    m_errorMargin = m_automate->getVariable(mapAction[QStringLiteral("error_margin")].toString());
    m_timeout = m_automate->getVariable(mapAction[QStringLiteral("timeout")].toString());
    m_nbMinimumTry = m_automate->getVariable(mapAction[QStringLiteral("nb_minimum_try")].toString());

    m_result = Q_NULLPTR;
    var =  m_automate->getVariable(mapAction[QStringLiteral("result")].toString());
    if(var->getType() == e_type_alarm)
        m_result = dynamic_cast<CVariableAlarm*>(var);
//    m_target = Q_NULLPTR;
//    var = m_automate->getVariable(mapAction[QStringLiteral("target")].toString());
//    if(var->getOrganType() == e_type_organ_input)
//        m_target = dynamic_cast<IVariableInput*>(var);

    m_target = m_automate->getVariable(mapAction[QStringLiteral("target")].toString());

    QString sCondition = mapAction[QStringLiteral("condition")].toString();
    if(sCondition == QStringLiteral("target_equal_to_setpoint")) m_condition = m_eEqualToSetpoint;
    else if(sCondition == QStringLiteral("target_superior_to_setpoint")) m_condition = m_eSuperiorToSetpoint;
    else m_condition = m_eInferiorToSetPoint;

    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}
QVariantMap CActionTest::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("setpoint"), m_setpoint->getName());
    mapSerialize.insert(QStringLiteral("target"), m_target->getName());
    mapSerialize.insert(QStringLiteral("result"), m_result->getName());
    mapSerialize.insert(QStringLiteral("waiting"), m_waiting->getName());
    mapSerialize.insert(QStringLiteral("error_margin"), m_errorMargin->getName());
    mapSerialize.insert(QStringLiteral("timeout"), m_timeout->getName());
    mapSerialize.insert(QStringLiteral("nb_minimum_try"), m_nbMinimumTry->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("test"));

    switch(m_condition){
    case m_eEqualToSetpoint:
        mapSerialize.insert(QStringLiteral("condition"), QStringLiteral("target_equal_to_setpoint"));
        break;
    case m_eSuperiorToSetpoint:
        mapSerialize.insert(QStringLiteral("condition"), QStringLiteral("target_superior_to_setpoint"));
        break;
    default: // m_eInferiorToSetPoint:
        mapSerialize.insert(QStringLiteral("condition"), QStringLiteral("target_inferior_to_setpoint"));
        break;
    }


    return mapSerialize;
}
CActionTest::~CActionTest()
{

}

bool CActionTest::runAction(ICycle* arg_stepParent){
    IAction::runAction(arg_stepParent);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = QThreadPool::globalInstance()->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CActionAcquisitionCitNpoc::runAction";
        }
    }
    return true;
}

void CActionTest::run(){
    ICycle* stepParent = getStepParent();
    qCDebug(COTAUTOMATE_LOG)<< "Action test 'qrunnable' "
            << " label fr " << m_label
         ;

    if(m_name == "action_control_water_ILS_default"){
        m_name = "action_control_water_ILS_default";
    }
    //envois de la consigne si la carte mesure attend une consigne
    if(m_setpoint->getOrganType() == e_type_organ_output){
        IVariableOutput* outputSetpoint = dynamic_cast<IVariableOutput*>(m_setpoint);
        if(outputSetpoint) outputSetpoint->writeValue();
    }
    if(m_result->getName() == QStringLiteral("var_water_pressure_ILS_default")){
        int test = false;
    }

    if(m_target){

        float setpointMax = m_setpoint->toFloat() + (m_setpoint->toFloat() * (m_errorMargin->toFloat()*0.01));
        float setpointMin = m_setpoint->toFloat() - (m_setpoint->toFloat() *  (m_errorMargin->toFloat()*0.01));
        int timeout = m_timeout->toInt();
        bool result = true;
        bool bSortie = false;
        int nbMiniTry = m_nbMinimumTry->toInt();

        qCDebug(COTAUTOMATE_LOG)<< "timeout " << timeout;
        qCDebug(COTAUTOMATE_LOG)<< "result " << result;

        for(int i=0 ; ( (i < timeout && timeout > 0) || timeout == 0 )&& !m_abort && !bSortie ; ++i){

            setpointMax = m_setpoint->toFloat() + (m_setpoint->toFloat() * (m_errorMargin->toFloat()*0.01));
            setpointMin = m_setpoint->toFloat() - (m_setpoint->toFloat() *  (m_errorMargin->toFloat()*0.01));

            result = acquisitionAndTest(setpointMin, setpointMax);
            m_result->CVariableAlarm::setValue(!result);
            if(result && m_result->toBool() && timeout > 0 && nbMiniTry-- < 0)
                bSortie = true;
            else if(!result)
                nbMiniTry = m_nbMinimumTry->toInt();

            QString  sActionInfo =  tr("Read ") + QString::number(i+1) + "/"  +QString::number(timeout) + " "
                    + m_target->getLabel() + " " +  QString::number(m_target->toFloat(), 'f', 2)
                    + m_target->getUnit()->getLabel() ;
            updateActionInfos(sActionInfo, stepParent);
            QThread::msleep(1000);
        }
    }
    else{
        qDebug()<< "pas le type de target attendu";
    }
    updateActionInfos(m_label + tr(" ending"), stepParent);
    emit signalActionFinished(this);
}

bool CActionTest::acquisitionAndTest(float arg_setPointMin, float arg_setPointMax){
//    float  target = m_target->readValue()->toFloat();
    float  target = 0;
    if(m_target->getOrganType() == e_type_organ_input)
        target = dynamic_cast<IVariableInput*>(m_target)->readValue()->toFloat();
    else
        target = m_target->toFloat();

    bool result= false;

    switch(m_condition){
    case m_eEqualToSetpoint:
        if(target <= arg_setPointMax && target >= arg_setPointMin) {
            result = true;
        }
        break;
    case m_eInferiorToSetPoint:
        if(target <= arg_setPointMin) {
            result = true;
        }
        break;
    case m_eSuperiorToSetpoint:
        if(target >= arg_setPointMin) {
            result = true;
        }
        break;
    }
    return result;
}

bool CActionTest::waitUntilFinished(){
    return m_waiting->toBool();
}


QList<IVariable*> CActionTest::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_errorMargin);
    listParams.append(m_result);
    listParams.append(m_setpoint);
    //listParams.append(dynamic_cast<IVariable*>(m_target));
    listParams.append(m_target);
    listParams.append(m_timeout);
    listParams.append(m_waiting);

    return listParams;
}

QMap<QString, IVariable*> CActionTest::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Setpoint"), m_setpoint);
    map.insert(tr("Target"), dynamic_cast<IVariable*>(m_target));
    map.insert(tr("Result"), m_result);
    map.insert(tr("Waiting"), m_waiting);
    map.insert(tr("Error margin"), m_errorMargin);
    map.insert(tr("Timeout"), m_timeout);
    return map;
}

QMap<QString, IVariable*> CActionTest::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
actionType CActionTest::getType()const {
    return actionType::type_test;
}

bool CActionTest::variableUsed(IVariable *arg_var)const {
    if(m_setpoint == arg_var) return true;

    return false;
}
void CActionTest::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("Setpoint")== arg_key) m_setpoint= arg_parameter;
    else if(tr("Target")== arg_key && arg_parameter->getOrganType() == e_type_organ_input )m_target= arg_parameter;
//    else if(tr("Target")== arg_key && arg_parameter->getOrganType() == e_type_organ_input )m_target= dynamic_cast<IVariableInput*>(arg_parameter);
    else if(tr("Target")== arg_key && arg_parameter->getOrganType() != e_type_organ_input )m_target= Q_NULLPTR;
    else if(tr("Result")== arg_key && arg_parameter->getOrganType() == e_type_alarm )m_result= dynamic_cast<CVariableAlarm*>(arg_parameter);
    else if(tr("Result")== arg_key && arg_parameter->getOrganType() != e_type_alarm )m_result= Q_NULLPTR;
    else if(tr("Waiting")== arg_key)m_waiting= arg_parameter;
    else if(tr("Error margin")== arg_key)m_errorMargin= arg_parameter;
    else if(tr("Timeout")== arg_key)m_timeout= arg_parameter;

}
enumVariableType CActionTest::getWaitedType(const QString& arg_key){
    if(tr("Setpoint")== arg_key) return e_type_float;
    else if(tr("Target")== arg_key) return e_type_float;
    else if(tr("Result")== arg_key)return e_type_float;
    else if(tr("Waiting")== arg_key)return e_type_int;
    else if(tr("Error margin")== arg_key)return e_type_bool;
    else if(tr("Timeout")== arg_key)return e_type_int;
    else if(tr("Generate critical error")== arg_key)return e_type_bool;
    return e_type_unknow;
}
