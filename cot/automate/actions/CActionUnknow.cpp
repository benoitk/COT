#include "CActionUnknow.h"

#include "qdebug.h"
CActionUnknow::CActionUnknow(QObject *parent)
	: IAction(parent)
{

}
CActionUnknow::CActionUnknow(const QVariantMap &mapAction)
	: IAction()
{
	m_label = mapAction[tr("FR_lbl")].toString();
	m_name = mapAction["name"].toString();
	 

}
CActionUnknow::~CActionUnknow()
{

}

bool CActionUnknow::runAction(){
	qDebug() <<  "Action inconnu " ;
	return true;
}

QString CActionUnknow::getName()const{
	return m_name; 
}

QList<IVariable*> CActionUnknow::getListParameters()const{
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