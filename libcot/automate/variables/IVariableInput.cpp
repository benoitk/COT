#include "IVariableInput.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "CAutomate.h"

IVariableInput::IVariableInput(): m_organ(Q_NULLPTR){
}
IVariableInput::IVariableInput(IOrgan* arg_organ)
    :m_organ(arg_organ)
{
}
IVariableInput::~IVariableInput()
{
}

IOrgan* IVariableInput::getOrgan()const{
    return m_organ;
}
QString IVariableInput::getOrganName()const{
    return m_organ ? m_organ->getName() : QString();
}
QString IVariableInput::getOrganAddr()const{
    return m_organ ? m_organ->getAddress() : QString();
}
void IVariableInput::setOrgan(CModelExtensionCard* arg_model,const QString &arg_organName){
    m_organ = arg_model ? arg_model->getOrgan(arg_organName) : Q_NULLPTR;
}



