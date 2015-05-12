#include "CActionCmdReadInput.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"

#include "cotautomate_debug.h"


CActionCmdReadInput::CActionCmdReadInput(QObject *parent)
	: IAction(parent)
{

}
CActionCmdReadInput::CActionCmdReadInput(const QVariantMap &mapAction)
	: IAction()
{
    CAutomate* automate = CAutomate::getInstance();
    m_name = mapAction[QStringLiteral("name")].toString();
	m_label = mapAction[tr("FR_lbl")].toString();
    m_organneVar =  automate->getVariable(mapAction[QStringLiteral("organne_var")].toString());

    m_variableDestination =  CAutomate::getInstance()->getVariable(mapAction[QStringLiteral("variable_destination_name")].toString());
}
CActionCmdReadInput::CActionCmdReadInput()
	: IAction()
{
}

CActionCmdReadInput::~CActionCmdReadInput()
{
}

bool CActionCmdReadInput::runAction(){
    qCDebug(COTAUTOMATE_LOG)<< QString::fromUtf8("Action lecture entrÃ©e ")
			<< " label fr " << m_label
			<< " Etat du l'entrée " << m_organneVar->toString()
			<< " var name " << m_variableDestination->getLabel()
			<< " value (normalement l'état de l'entrée)" << m_variableDestination->toString();

	
	return true;
}


QString CActionCmdReadInput::getName()const{
	return m_name; 
}

QList<IVariable*> CActionCmdReadInput::getListParameters()const{
	QList<IVariable*> listParams;
    listParams.append(m_organneVar);
    listParams.append(m_variableDestination);
	return listParams;
}
QString CActionCmdReadInput::getLabel()const{
    return m_label;
}
void CActionCmdReadInput::setLabel(const QString& lbl){
    m_label = lbl;
}
actionType CActionCmdReadInput::getType()const {
    return actionType::type_cmd_read_input;
}