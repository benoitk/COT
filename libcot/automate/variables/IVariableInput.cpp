#include "IVariableInput.h"
#include "CModelExtensionCard.h"
#include "IComObserver.h"

IVariableInput::IVariableInput(): m_modelExtensionCard(Q_NULLPTR){
}

CModelExtensionCard* IVariableInput::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* IVariableInput::getComObserver()const{
    return m_modelExtensionCard;
}

QString IVariableInput::getOrganneName()const{
    return m_organneName;
}
QString IVariableInput::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void IVariableInput::setOrganne(CModelExtensionCard* arg_model,const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}




