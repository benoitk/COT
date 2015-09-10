#include "CActionTest.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "IVariableOutput.h"
#include "cotautomate_debug.h"
#include "CUnit.h"
#include "qmap.h"
#include "qthreadpool.h"

CActionTest::CActionTest(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_setpoint = automate->getVariable(mapAction[QStringLiteral("setpoint")].toString());
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    m_waiting = automate->getVariable(mapAction[QStringLiteral("waiting")].toString());
    m_errorMargin = automate->getVariable(mapAction[QStringLiteral("error_margin")].toString());
    m_timeout = automate->getVariable(mapAction[QStringLiteral("timeout")].toString());

    IVariable* var = Q_NULLPTR;
    m_target = Q_NULLPTR;
    var = automate->getVariable(mapAction[QStringLiteral("target")].toString());
    if(var->getOrganType() == type_organ_input)
        m_target = dynamic_cast<IVariableInput*>(var);

    QVariantMap variantMap;
    variantMap.insert(QStringLiteral("name"), QStringLiteral("critical_error"));
    variantMap.insert(QStringLiteral("fr_FR"), tr("Generate critical error"));
    variantMap.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    variantMap.insert(QStringLiteral("value"), mapAction[QStringLiteral("critical_error")].toBool());
    m_criticalError = dynamic_cast<CVariableBool*>(CVariableFactory::build(variantMap));

    QString sCondition = mapAction[QStringLiteral("condition")].toString();
    if(sCondition == QStringLiteral("target_equal_to_setpoint")) m_condition = m_eEqualToSetpoint;
    else if(sCondition == QStringLiteral("target_superior_to_setpoint")) m_condition = m_eSuperiorToSetpoint;
    else m_condition = m_eInferiorToSetPoint;

    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
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


    //envois de la consigne si la carte mesure attend une consigne
    if(m_setpoint->getOrganType() == type_organ_output){
        IVariableOutput* outputSetpoint = dynamic_cast<IVariableOutput*>(m_setpoint);
        if(outputSetpoint) outputSetpoint->writeValue();
    }

    if(m_target){

        float setpointMax = m_setpoint->toFloat() + (m_setpoint->toFloat() * (m_errorMargin->toFloat()*0.01));
        float setpointMin = m_setpoint->toFloat() - (m_setpoint->toFloat() *  (m_errorMargin->toFloat()*0.01));
        int timeout = m_timeout->toInt();
        bool result = false;

        qCDebug(COTAUTOMATE_LOG)<< "timeout " << timeout;
        qCDebug(COTAUTOMATE_LOG)<< "result " << result;

        for(int i=0 ; ( (i < timeout && timeout > 0) || timeout == 0 )&& /*!result &&*/ !m_abort; ++i){
            setpointMax = m_setpoint->toFloat() + (m_setpoint->toFloat() * (m_errorMargin->toFloat()*0.01));
            setpointMin = m_setpoint->toFloat() - (m_setpoint->toFloat() *  (m_errorMargin->toFloat()*0.01));
            result = acquisitionAndTest(setpointMin, setpointMax);
            m_result->setValue(result);
            QString  sActionInfo =  tr("Lecture ") + QString::number(i+1) + "/"  +QString::number(timeout) + " "
                    + m_target->getIVariable()->getLabel() + " " +  QString::number(m_target->getIVariable()->toFloat(), 'f', 2)
                    + m_target->getIVariable()->getUnit()->getLabel() ;
            updateActionInfos(sActionInfo, stepParent);
            if(m_name ==  "control_air_flow"){
                qCDebug(COTAUTOMATE_LOG)<< "for timeout " << timeout - i;
                qCDebug(COTAUTOMATE_LOG)<< "for target " << m_target->getIVariable()->toString();
                qCDebug(COTAUTOMATE_LOG)<< "for m_condition " << m_condition;
                qCDebug(COTAUTOMATE_LOG)<< "for setpoint_max " << setpointMax;
                qCDebug(COTAUTOMATE_LOG)<< "for setpoint_min " << setpointMin;
                qCDebug(COTAUTOMATE_LOG)<< "for result " << result;
            }

        }

//        m_result->setValue(result);
    }
    else{
        qDebug()<< "pas le type de target attendu";
    }
    updateActionInfos(m_label + tr(" finit"), stepParent);
    emit signalActionFinished(this);
}

bool CActionTest::acquisitionAndTest(float arg_setPointMin, float arg_setPointMax){
    float  target = m_target->readValue()->toFloat();
    bool result= false;

    switch(m_condition){
    case m_eEqualToSetpoint:
        if(target < arg_setPointMax && target > arg_setPointMin) {
            result = true;
        }
        break;
    case m_eInferiorToSetPoint:
        if(target < arg_setPointMin) {
            result = true;
        }
        break;
    case m_eSuperiorToSetpoint:
        if(target > arg_setPointMin) {
            result = true;
        }
        break;
    }

    QThread::msleep(1000);
    return result;
}

bool CActionTest::waitUntilFinished(){
    return m_waiting->toBool();
}

bool CActionTest::finishedWithCriticalError(){
    if(m_criticalError && m_result->toBool())
        return true;
    return false;

}
QList<IVariable*> CActionTest::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_errorMargin);
    listParams.append(m_result);
    listParams.append(m_setpoint);
    listParams.append(dynamic_cast<IVariable*>(m_target));
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

    map.insert(tr("Generate critical error"), m_criticalError);

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
    else if(tr("Target")== arg_key && arg_parameter->getOrganType() == type_organ_input )m_target= dynamic_cast<IVariableInput*>(arg_parameter);
    else if(tr("Target")== arg_key && arg_parameter->getOrganType() != type_organ_input )m_target= Q_NULLPTR;
    else if(tr("Result")== arg_key)m_result= arg_parameter;
    else if(tr("Waiting")== arg_key)m_waiting= arg_parameter;
    else if(tr("Error margin")== arg_key)m_errorMargin= arg_parameter;
    else if(tr("Timeout")== arg_key)m_timeout= arg_parameter;
    else if(tr("Generate critical error")== arg_key)m_criticalError->setValue(arg_parameter->toBool());

}
variableType CActionTest::getWaitedType(const QString& arg_key){
    if(tr("Setpoint")== arg_key) return type_float;
    else if(tr("Target")== arg_key) return type_float;
    else if(tr("Result")== arg_key)return type_float;
    else if(tr("Waiting")== arg_key)return type_int;
    else if(tr("Error margin")== arg_key)return type_bool;
    else if(tr("Timeout")== arg_key)return type_int;
    else if(tr("Generate critical error")== arg_key)return type_bool;
    return type_unknow;
}
