#include "CActionUnknow.h"

#include "qdebug.h"
CActionUnknow::CActionUnknow(QObject *parent)
	: IAction(parent)
{

}
CActionUnknow::CActionUnknow(const QVariantMap &mapAction)
	: IAction()
{
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
	m_stepOrTour = mapAction["num_step_or_tour_pump"].toInt();
	m_numero = mapAction["num_pump"].toInt();
	m_clockwise = mapAction["direction_trigo_pump"].toBool();
	m_timing = mapAction["timing"].toInt();
	m_speed = mapAction["speed_pump"].toInt();
	m_name = mapAction["name"].toString();
	*/

	return listParams;
}
QString CActionUnknow::getLabel()const{
    return QStringLiteral("unknow lbl");
}
void CActionUnknow::setLabel(const QString& lbl){
}