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

    m_organ =  automate->getVariable(mapAction[QStringLiteral("organ")].toString());
    m_target =  CAutomate::getInstance()->getVariable(mapAction[QStringLiteral("target")].toString());
}

CActionCmdReadInput::~CActionCmdReadInput()
{
}

bool CActionCmdReadInput::runAction(){
    qCDebug(COTAUTOMATE_LOG)<< QString::fromUtf8("Action lecture entrÃ©e ")
            << " label fr " << m_label
            << " Etat du l'entrée " << m_organ->toString()
            << " var name " << m_target->getLabel()
            << " value (normalement l'état de l'entrée)" << m_target->toString();

    if(m_organ->getOrganType() == type_organ_input){
        IVariableInput* organ = dynamic_cast<IVariableInput*>(m_organ);
        organ->readValue();
    }

    m_target->setValue(m_organ->toVariant());

    return true;
}

QList<IVariable*> CActionCmdReadInput::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_organ);
    listParams.append(m_target);
    return listParams;
}
actionType CActionCmdReadInput::getType()const {
    return actionType::type_cmd_read_input;
}

bool CActionCmdReadInput::variableUsed(IVariable *arg_var)const {
 if(m_organ == arg_var) return true;
    if(m_target == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionCmdReadInput::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Organ input"), m_organ);
    map.insert(tr("Variable destination"), m_target);
    return map;
}

QMap<QString, IVariable*> CActionCmdReadInput::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionCmdReadInput::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("Organ input")== arg_key) m_organ= arg_parameter;
    else if(tr("Variable destination")== arg_key)m_target= arg_parameter;

}
variableType CActionCmdReadInput::getWaitedType(const QString& arg_key){
   //peu importe

    return type_unknow;
}
