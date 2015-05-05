#include "CModelExtensionCard.h"
#include "ICom.h"

CModelExtensionCard::CModelExtensionCard(QObject *parent)
	: QObject(parent)
{

}

CModelExtensionCard::CModelExtensionCard(const QVariantMap& mapExt)
	: QObject()
{
    if(mapExt.contains(QStringLiteral("name")))
        m_name = mapExt.value(QStringLiteral("name")).toString();
    else
        m_name = QStringLiteral("unamed_extension_card");

    //TO DO : feed objects
}
CModelExtensionCard::~CModelExtensionCard()
{

}

QString CModelExtensionCard::getName()const{
	return m_name;
}

QVariant CModelExtensionCard::readOrganneValue(IVariableInput* arg_varInput){
	return m_interfaceCom->readData(arg_varInput);
}

IVariable* CModelExtensionCard::getVariable(const QString &addr_var)const{
    IVariable * temp = Q_NULLPTR;
	return temp;
}

void CModelExtensionCard::setCom(ICom* com){
	m_interfaceCom = com;
}

QList<IOrgan*>  CModelExtensionCard::getListOrgans()const{
    return m_listOrgans;
}

QString CModelExtensionCard::getLabel() const
{
   // CUSTOMER: Fix me
    return getName();
}



