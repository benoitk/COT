#include "CActionCmdPompe.h"
#include "qdebug.h"
CActionCmdPompe::CActionCmdPompe(QObject *parent)
	: IAction(parent)
{

}
CActionCmdPompe::CActionCmdPompe(QVariantMap mapAction)
	: IAction()
{
	m_label = mapAction[tr("FR_lbl")].toString();
	m_ctrlContinu = mapAction["cmd_continu_pump"].toBool();
	m_nbPasTour = mapAction["num_step_or_tour_pump"].toInt();
	m_numero = mapAction["num_pump"].toInt();
	m_sens = mapAction["direction_trigo_pump"].toBool();
	m_timing = mapAction["timing"].toInt();
	m_vitesse = mapAction["speed_pump"].toInt();
	m_name = mapAction["name"].toString();
	 

}
CActionCmdPompe::CActionCmdPompe()
	: IAction()
{

}

CActionCmdPompe::~CActionCmdPompe()
{

}


bool CActionCmdPompe::runAction(){
	qDebug() <<  "Action pompe "
			<< " label fr " << m_label
			<< " m_numero " << m_numero
			<< " m_vitesse " << m_vitesse
			<< " m_sens " << m_sens
			<< " m_nbPasTour " << m_nbPasTour
			<< " m_ctrlContinu " << m_ctrlContinu
			<< " m_timing " << m_timing;
	return true;
}

QString CActionCmdPompe::getName()const{
	return m_name; 
}
