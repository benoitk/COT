#include "IVariableOutput.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "IComObserver.h"
#include "CAutomate.h"
IVariableOutput::IVariableOutput(): m_modelExtensionCard(Q_NULLPTR){

}
IVariableOutput::IVariableOutput(const QVariantMap & mapVar){
    CAutomate* automate = CAutomate::getInstance();
    m_modelExtensionCard = automate->getExtensionCard(mapVar.value(QStringLiteral("extension_name")).toString());
    m_organneAddr = m_modelExtensionCard->getOrgan(mapVar.value(QStringLiteral("organ_name")).toString())->getAddress();
    m_organneName = mapVar.value(QStringLiteral("organ_name")).toString();
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
