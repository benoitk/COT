#include "CActionTest.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "cotautomate_debug.h"


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
    m_criticalError = mapAction[QStringLiteral("critical_error")].toBool();

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
    if(m_target->getOrganType() == VariableOrganTypeInput)
        inputTarget = dynamic_cast<IVariableInput*>(m_target);

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
    emit signalActionFinished(this);
}

bool CActionTest::waitUnitlFinished(){
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
actionType CActionTest::getType()const {
    return actionType::type_test;
}

bool CActionTest::variableUsed(IVariable *arg_var)const {
    if(m_setpoint == arg_var) return true;

    return false;
}
