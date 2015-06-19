#include "CActionCmdPompe.h"

#include "CVariableString.h"
#include "CVariableFactory.h"
#include "CAutomate.h"

#include "cotautomate_debug.h"


CActionCmdPompe::CActionCmdPompe(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();

    if(mapAction.contains(QStringLiteral("pump")))
        m_pump = automate->getVariable(mapAction[QStringLiteral("pump")].toString());
    if(mapAction.contains(QStringLiteral("pump")))
        m_cmdContinu = automate->getVariable(mapAction[QStringLiteral("cmd_continu_pump")].toString());
    else
    {

    }
    if(mapAction.contains(QStringLiteral("pump")))
        m_stepOrTour = automate->getVariable(mapAction[QStringLiteral("num_step_or_tour_pump")].toString());
    if(mapAction.contains(QStringLiteral("pump")))
        m_nbStepOrTour = automate->getVariable(mapAction[QStringLiteral("num_pump")].toString());
    if(mapAction.contains(QStringLiteral("pump")))
        m_clockwise =  automate->getVariable(mapAction[QStringLiteral("direction_trigo_pump")].toString());
    if(mapAction.contains(QStringLiteral("pump")))
        m_speed = automate->getVariable(mapAction[QStringLiteral("speed_pump")].toString());

}

CActionCmdPompe::~CActionCmdPompe()
{

}
QList<IVariable*> CActionCmdPompe::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_cmdContinu);
    listParams.append(m_stepOrTour);
    listParams.append(m_nbStepOrTour);
    listParams.append(m_clockwise);
    listParams.append(m_speed);

    return listParams;
}


bool CActionCmdPompe::runAction(){
    qCDebug(COTAUTOMATE_LOG) <<  "Action pompe "
            << " label fr " << m_label
            << " m_numero " << m_nbStepOrTour->toString()
            << " m_speed " << m_speed->toString()
            << " m_clockwise " << m_clockwise->toString()
            << " m_stepOrTour " << m_stepOrTour->toString()
            << " m_ctrlContinu " << m_cmdContinu->toString();
    emit signalActionFinished(this);
    return true;
}

actionType CActionCmdPompe::getType()const {
    return actionType::type_cmd_pump;
}

bool CActionCmdPompe::variableUsed(IVariable * arg_var)const {
    if(m_pump == arg_var) return true;
    if(m_speed == arg_var) return true;
    if(m_nbStepOrTour == arg_var) return true;
    if(m_clockwise == arg_var) return true;
    if(m_stepOrTour == arg_var) return true;
    if(m_cmdContinu == arg_var) return true;

    return false;
}
