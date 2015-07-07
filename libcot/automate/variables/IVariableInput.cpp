#include "IVariableInput.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "CAutomate.h"

IVariableInput::IVariableInput(): m_organ(Q_NULLPTR){
}
IVariableInput::IVariableInput(const QVariantMap & mapVar){
    CAutomate* automate = CAutomate::getInstance();
    CModelExtensionCard* extCard = automate->getExtensionCard(mapVar.value(QStringLiteral("extension_name")).toString());
    m_organ  =extCard->getOrgan(mapVar.value(QStringLiteral("organ_name")).toString());
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



