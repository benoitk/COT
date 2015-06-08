#include "IVariableOutput.h"
#include "CModelExtensionCard.h"
#include "IComObserver.h"

IVariableOutput::IVariableOutput(): m_modelExtensionCard(Q_NULLPTR){

}

IVariableOutput::~IVariableOutput()
{
}

CModelExtensionCard* IVariableOutput::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* IVariableOutput::getComObserver()const{
    return m_modelExtensionCard;
}
QString IVariableOutput::getOrganneName()const{
    return m_organneName;
}
QString IVariableOutput::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void IVariableOutput::setOrganne(CModelExtensionCard* arg_model,const  QString  &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}
