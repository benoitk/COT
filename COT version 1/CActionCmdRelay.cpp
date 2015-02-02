#include "CActionCmdRelay.h"
#include "qdebug.h"


CActionCmdRelay::CActionCmdRelay(QObject *parent)
	: IAction(parent)
{

}
CActionCmdRelay::CActionCmdRelay(QVariantMap mapAction)
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