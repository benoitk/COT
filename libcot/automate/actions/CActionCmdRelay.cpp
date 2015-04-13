#include "CActionCmdRelay.h"
#include "qdebug.h"


CActionCmdRelay::CActionCmdRelay(QObject *parent)
	: IAction(parent)
{

}
CActionCmdRelay::CActionCmdRelay(const QVariantMap &mapAction)
	: IAction()
{
	m_label = mapAction[tr("FR_lbl")].toString();
	m_num_card_output = mapAction["num_card_output"].toInt();
	m_timing = mapAction["timing"].toInt();
	m_card_id = mapAction["card_id"].toInt();
	m_name = mapAction["name"].toString();

}
CActionCmdRelay::CActionCmdRelay()
	: IAction()
{

}

CActionCmdRelay::~CActionCmdRelay()
{

}


bool CActionCmdRelay::runAction(){
	qDebug()<< "Action relay "
			<< " label fr " << m_label
			<< " m_card_id " << m_card_id
			<< " m_num_card_output " << m_num_card_output;
	return true;
}

void CActionCmdRelay::setTiming(int seconde){
	m_timing = seconde;
}

int CActionCmdRelay::getTiming(){
	return m_timing;
}
QString CActionCmdRelay::getName()const{
	return m_name; 
}

QList<IVariable*> CActionCmdRelay::getListParameters()const{
	QList<IVariable*> listParams;
	/*TO DO mettre tout ça en tant que IVariable qui va bien
	m_ctrlContinu = mapAction["cmd_continu_pump"].toBool();
	m_nbPasTour = mapAction["num_step_or_tour_pump"].toInt();
	m_numero = mapAction["num_pump"].toInt();
	m_sens = mapAction["direction_trigo_pump"].toBool();
	m_timing = mapAction["timing"].toInt();
	m_vitesse = mapAction["speed_pump"].toInt();
	m_name = mapAction["name"].toString();
	*/

	return listParams;
}