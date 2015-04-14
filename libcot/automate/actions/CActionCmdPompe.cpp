#include "CActionCmdPompe.h"

#include "CVariableString.h"
#include "CVariableFactory.h"
#include "CAutomate.h"

#include "qdebug.h"


CActionCmdPompe::CActionCmdPompe(QObject *parent)
	: IAction(parent)
{

}
CActionCmdPompe::CActionCmdPompe(const QVariantMap &mapAction)
	: IAction()
{
    CAutomate* automate = CAutomate::getInstance();
    m_label = mapAction[tr("FR_lbl")].toString();
    m_cmdContinu = automate->getVariable(mapAction[QStringLiteral("cmd_continu_pump")].toString());
    m_stepOrTour = automate->getVariable(mapAction[QStringLiteral("num_step_or_tour_pump")].toString());
    m_numPump = automate->getVariable(mapAction[QStringLiteral("num_pump")].toString());
    m_clockwise =  automate->getVariable(mapAction[QStringLiteral("direction_trigo_pump")].toString());
    m_speed = automate->getVariable(mapAction[QStringLiteral("speed_pump")].toString());
    
    m_name = mapAction[QStringLiteral("name")].toString();
	 

}
CActionCmdPompe::CActionCmdPompe()
	: IAction()
{

}

CActionCmdPompe::~CActionCmdPompe()
{

}
QList<IVariable*> CActionCmdPompe::getListParameters()const{
	QList<IVariable*> listParams;
    listParams.append(m_cmdContinu);
    listParams.append(m_stepOrTour);
    listParams.append(m_numPump);
    listParams.append(m_clockwise);
    listParams.append(m_speed);

	return listParams;
}


bool CActionCmdPompe::runAction(){
	qDebug() <<  "Action pompe "
			<< " label fr " << m_label
            << " m_numero " << m_numPump->toString()
            << " m_speed " << m_speed->toString()
            << " m_clockwise " << m_clockwise->toString()
            << " m_stepOrTour " << m_stepOrTour->toString()
            << " m_ctrlContinu " << m_cmdContinu->toString();
	return true;
}

QString CActionCmdPompe::getName()const{
	return m_name; 
}
QString CActionCmdPompe::getLabel()const{
    return m_label;
}
void CActionCmdPompe::setLabel(const QString& lbl){
    m_label = lbl;
}
