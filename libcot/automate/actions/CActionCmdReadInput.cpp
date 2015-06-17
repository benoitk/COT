#include "CActionCmdReadInput.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CModelExtensionCard.h"

#include "cotautomate_debug.h"


CActionCmdReadInput::CActionCmdReadInput(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();

    m_organneVar =  automate->getVariable(mapAction[QStringLiteral("organne_var")].toString());
    m_variableDestination =  CAutomate::getInstance()->getVariable(mapAction[QStringLiteral("variable_destination_name")].toString());
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

QList<IVariable*> CActionCmdReadInput::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_organneVar);
    listParams.append(m_variableDestination);
    return listParams;
}
actionType CActionCmdReadInput::getType()const {
    return actionType::type_cmd_read_input;
}

bool CActionCmdReadInput::variableUsed(IVariable *arg_var)const {
 if(m_organneVar == arg_var) return true;
    if(m_variableDestination == arg_var) return true;

    return false;
}
