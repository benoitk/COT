#include "CVariableInputFloat.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "CUnit.h"

CVariableInputFloat::CVariableInputFloat(QObject *parent)
    : CVariableFloat(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableInputFloat::~CVariableInputFloat()
{

}

CVariableInputFloat::CVariableInputFloat(const QMap<QString, QVariant> &mapVar)
    : CVariableFloat()
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CModelExtensionCard* CVariableInputFloat::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* CVariableInputFloat::getComObserver()const{
    return m_modelExtensionCard;
}
QString CVariableInputFloat::getOrganneName()const{
    return m_organneName;
}
QString CVariableInputFloat::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableInputFloat::setOrganne(CModelExtensionCard* arg_model,const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}

IVariable* CVariableInputFloat::readValue(){
    if (m_modelExtensionCard) {
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toFloat());
    }

    return this;
}


variableType CVariableInputFloat::getType()const{
    return type_float;
}
IVariable* CVariableInputFloat::getIVariable(){
    return this;
}

QVariantMap CVariableInputFloat::serialise(){
     QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_float"));
    mapSerialise.insert(QStringLiteral("value"), m_fValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
