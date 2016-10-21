#include "IVariableOutput.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "IComObserver.h"
#include "CAutomate.h"
IVariableOutput::IVariableOutput(): m_organ(Q_NULLPTR){

}
IVariableOutput::IVariableOutput(IOrgan* arg_organ)
    : m_organ(arg_organ)
{
}

IVariableOutput::~IVariableOutput()
{
}

IOrgan* IVariableOutput::getOrgan()const{
    return m_organ;
}
//IComObserver* IVariableOutput::getComObserver()const{
//    return m_modelExtensionCard;
//}
QString IVariableOutput::getOrganName()const{
    return m_organ ? m_organ->getName() : QString();
}
QString IVariableOutput::getOrganAddr()const{
    return m_organ ? m_organ->getAddress() : QString();
}
void IVariableOutput::setOrgan(CModelExtensionCard* arg_model,const  QString  &arg_organName){

    m_organ = arg_model ? arg_model->getOrgan(arg_organName) : Q_NULLPTR;
}

