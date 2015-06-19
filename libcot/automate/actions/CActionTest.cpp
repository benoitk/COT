#include "CActionTest.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
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

    QString sCondition = mapAction[QStringLiteral("condition")].toString();
    if(sCondition == QStringLiteral("equal")) m_condition = m_eEqual;
    else if(sCondition == QStringLiteral("diff_up")) m_condition = m_eDiffUp;
    else m_condition = m_eDiffDown;

}

CActionTest::~CActionTest()
{

}


bool CActionTest::runAction(){
    qCDebug(COTAUTOMATE_LOG)<< "Action test "
            << " label fr " << m_label
         ;
    QThreadPool::globalInstance()->start(this);
    return true;
}
void CActionTest::run(){
    qCDebug(COTAUTOMATE_LOG)<< "Action test 'qrunnable' "
            << " label fr " << m_label
         ;
    float target = m_target->toFloat();
    float setpoint_max = m_setpoint->toFloat() + (m_setpoint->toFloat() * m_errorMargin->toFloat());
    float setpoint_min = m_setpoint->toFloat() - (m_setpoint->toFloat() * m_errorMargin->toFloat());
    int timeout = m_timeout->toInt();
    bool result = false;

    switch(m_condition){
        case m_eEqual:
            for(int i=0 ; i < timeout & !result; ++i){
                target = m_target->toFloat();
                if(target < setpoint_max && target > setpoint_min) {
                    result = true;
                }
            }
            break;
    case m_eDiffDown:
    case m_eDiffUp:
    default:
        break;
    }


    m_result->setValue(result);
    if(result)
        emit signalActionFinished(this);
    else
        emit signalActionFinishedWithError(this);
}

bool CActionTest::waitUnitlFinished(){
    return m_waiting->toBool();
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
    return actionType::type_cmd_relay;
}

bool CActionTest::variableUsed(IVariable *arg_var)const {
    if(m_setpoint == arg_var) return true;

    return false;
}
