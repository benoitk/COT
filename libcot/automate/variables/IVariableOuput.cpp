#include "IVariableOutput.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "IComObserver.h"
#include "CAutomate.h"
IVariableOutput::IVariableOutput(): m_organ(Q_NULLPTR){

}
IVariableOutput::IVariableOutput(const QVariantMap & mapVar){
    CAutomate* automate = CAutomate::getInstance();
    CModelExtensionCard* extCard = automate->getExtensionCard(mapVar.value(QStringLiteral("extension_name")).toString());
    m_organ  =extCard->getOrgan(mapVar.value(QStringLiteral("organ_name")).toString());
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
    return m_organ->getName();
}
QString IVariableOutput::getOrganAddr()const{
    return m_organ->getAddress();
}
void IVariableOutput::setOrgan(CModelExtensionCard* arg_model,const  QString  &arg_organName){

    m_organ = arg_model->getOrgan(arg_organName);
}

