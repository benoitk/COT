#include "CModelExtensionCard.h"
#include "ICom.h"

CModelExtensionCard::CModelExtensionCard(QObject *parent)
	: QObject(parent)
{

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

IVariable* CModelExtensionCard::getVariable(QString addr_var)const{
	IVariable * temp;
	return temp;
}
void CModelExtensionCard::setCom(ICom*){
	m_interfaceCom;
}

QList<IOrgan*>  CModelExtensionCard::getListOrgan()const{
	return m_listOrgan;
}



