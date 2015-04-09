#include "CActionCmdReadInput.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"

#include "qdebug.h"


CActionCmdReadInput::CActionCmdReadInput(QObject *parent)
	: IAction(parent)
{

}
CActionCmdReadInput::CActionCmdReadInput(QVariantMap mapAction)
	: IAction()
{
	m_name = mapAction["name"].toString();
	m_label = mapAction[tr("FR_lbl")].toString();
	m_extentionName = mapAction["extention_name"].toString();
	m_organneName = mapAction["organne_name"].toString();

	m_variableDestination =  CAutomate::getInstance()->getVariable(mapAction["variable_destination_name"].toString());
	//m_extensionCard = CAutomate::getInstance()->getExtensionCard(mapAction["extention_name"].toString());
}
CActionCmdReadInput::CActionCmdReadInput()
	: IAction()
{
}

CActionCmdReadInput::~CActionCmdReadInput()
{
}

bool CActionCmdReadInput::runAction(){
	qDebug()<< QString("Action lecture entrÃ©e ")
			<< " label fr " << m_label
			<< " m_card_id " << m_extentionName
			<< " m_num_card_output " << m_organneName
			<< " var name " << m_variableDestination->getLabel()
			<< " value " << m_variableDestination->toString();

	
	return true;
}


QString CActionCmdReadInput::getName()const{
	return m_name; 
}

QList<IVariable*> CActionCmdReadInput::getListParameters()const{
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