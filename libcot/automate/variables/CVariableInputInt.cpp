#include "CVariableInputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
CVariableInputInt::CVariableInputInt(QObject *parent)
    : CVariableInt(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableInputInt::~CVariableInputInt()
{

}

CVariableInputInt::CVariableInputInt(const QMap<QString, QVariant> &mapVar)
    : CVariableInt()
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CModelExtensionCard* CVariableInputInt::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* CVariableInputInt::getComObserver()const{
    return m_modelExtensionCard;
}
QString CVariableInputInt::getOrganneName()const{
    return m_organneName;
}
QString CVariableInputInt::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableInputInt::setOrganne(CModelExtensionCard* arg_model,const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}

IVariable* CVariableInputInt::readValue(){
    if (m_modelExtensionCard) {
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toFloat());
    }

    return this;
}


variableType CVariableInputInt::getType()const{
    return type_int;
}
IVariable* CVariableInputInt::getIVariable(){
    return this;
}

QVariantMap CVariableInputInt::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_integer"));
    mapSerialise.insert(QStringLiteral("value"), m_iValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
