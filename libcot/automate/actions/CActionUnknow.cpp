#include "CActionUnknow.h"

#include "cotautomate_debug.h"
CActionUnknow::CActionUnknow(QObject *parent)
	: IAction(parent)
{
    m_name =  QStringLiteral("unknow_action");
}
CActionUnknow::CActionUnknow(const QVariantMap &mapAction)
	: IAction()
{
    m_name =  QStringLiteral("unknow_action");
}
CActionUnknow::~CActionUnknow()
{
}

bool CActionUnknow::runAction(){
	qCDebug(COTAUTOMATE_LOG) <<  "Action inconnu " ;
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
actionType CActionUnknow::getType()const {
    return actionType::type_action_unknow;
}