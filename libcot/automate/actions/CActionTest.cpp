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
    m_target = automate->getVariable(mapAction[QStringLiteral("target")].toString());
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    m_waiting = automate->getVariable(mapAction[QStringLiteral("waiting")].toString());
    m_errorMargin = automate->getVariable(mapAction[QStringLiteral("error_margin")].toString());
    m_timeout = automate->getVariable(mapAction[QStringLiteral("timeout")].toString());

    QVariantMap variantMap;
    variantMap.insert(QStringLiteral("name"), QStringLiteral("critical_error"));
    variantMap.insert(QStringLiteral("fr_FR"), tr("Generate critical error"));
    variantMap.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    variantMap.insert(QStringLiteral("value"), mapAction[QStringLiteral("critical_error")].toBool());
    m_criticalError = dynamic_cast<CVariableBool*>(CVariableFactory::build(variantMap));

    QString sCondition = mapAction[QStringLiteral("condition")].toString();
    if(sCondition == QStringLiteral("equal")) m_condition = m_eEqualToSetpoint;
    else if(sCondition == QStringLiteral("diff_up")) m_condition = m_eSuperiorToSetpoint;
    else m_condition = m_eInferiorToSetPoint;

    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}

CActionTest::~CActionTest()
{

}


bool CActionTest::runAction(){
    IAction::runAction();

    QThreadPool::globalInstance()->tryStart(this);
    return true;
}



void CActionTest::run(){

    qCDebug(COTAUTOMATE_LOG)<< "Action test 'qrunnable' "
            << " label fr " << m_label
         ;
    IVariableInput* inputTarget = Q_NULLPTR;

    if(m_target->getOrganType() == type_organ_input)
        inputTarget = dynamic_cast<IVariableInput*>(m_target);

    //envois de la consigne si la carte mesure attend une consigne
    if(m_setpoint->getOrganType() == type_organ_output){
        IVariableOutput* outputSetpoint = dynamic_cast<IVariableOutput*>(m_setpoint);
        if(outputSetpoint) outputSetpoint->writeValue();
    }

    if(inputTarget){
        float target = m_target->toFloat();
        float setpoint_max = m_setpoint->toFloat() + (m_setpoint->toFloat() * m_errorMargin->toFloat());
        float setpoint_min = m_setpoint->toFloat() - (m_setpoint->toFloat() * m_errorMargin->toFloat());
        int timeout = m_timeout->toInt();
        bool result = false;

        qCDebug(COTAUTOMATE_LOG)<< "timeout " << timeout;
        qCDebug(COTAUTOMATE_LOG)<< "result " << result;
        for(int i=0 ; i < timeout /*&& !result*/ && !m_abort; ++i){
            target = inputTarget->readValue()->toFloat();

            QString  sActionInfo =  tr("Lecture ") + QString::number(i+1) + "/"  +QString::number(timeout) + " "
                                    + m_target->getLabel() + " " +  QString::number(target, 'f', 2)
                                    + m_target->getUnit()->getLabel() ;
            emit CAutomate::getInstance()->signalUpdateCurrentAction(sActionInfo);

            qCDebug(COTAUTOMATE_LOG)<< "for timeout " << timeout - i;
            qCDebug(COTAUTOMATE_LOG)<< "for target " << target;
            qCDebug(COTAUTOMATE_LOG)<< "for m_condition " << m_condition;
            qCDebug(COTAUTOMATE_LOG)<< "for setpoint_max " << setpoint_max;
            qCDebug(COTAUTOMATE_LOG)<< "for setpoint_min " << setpoint_min;
            qCDebug(COTAUTOMATE_LOG)<< "for result " << result;


            switch(m_condition){
            case m_eEqualToSetpoint:
                if(target < setpoint_max && target > setpoint_min) {
                    result = true;
                }
                break;
            case m_eInferiorToSetPoint:
                if(target < setpoint_min) {
                    result = true;
                }
                break;
            case m_eSuperiorToSetpoint:
                if(target > setpoint_min) {
                    result = true;
                }
                break;
            }

            QThread::usleep(1000000);
        }
        m_result->setValue(false);
//        m_result->setValue(result);
    }
    else{
        qDebug()<< "pas le type de target attendu";
    }
    emit CAutomate::getInstance()->signalUpdateCurrentAction(m_label + tr(" finit"));
    emit signalActionFinished(this);
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
    listParams.append(m_target);
    listParams.append(m_timeout);
    listParams.append(m_waiting);

    return listParams;
}

QMap<QString, IVariable*> CActionTest::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Setpoint"), m_setpoint);
    map.insert(tr("Target"), m_target);
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
    else if(tr("Target")== arg_key)m_target= arg_parameter;
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
