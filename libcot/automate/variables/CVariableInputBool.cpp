#include "CVariableInputBool.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "CVariableBool.h"
#include "CUnit.h"

CVariableInputBool::CVariableInputBool(QObject *parent)
    : CVariableBool(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableInputBool::~CVariableInputBool()
{

}
CVariableInputBool::CVariableInputBool(const QMap<QString, QVariant> &mapVar)
    : CVariableBool()
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CModelExtensionCard* CVariableInputBool::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* CVariableInputBool::getComObserver()const{
    return m_modelExtensionCard;
}

QString CVariableInputBool::getOrganneName()const{
    return m_organneName;
}
QString CVariableInputBool::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableInputBool::setOrganne(CModelExtensionCard* arg_model,const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}

IVariable* CVariableInputBool::readValue(){
    if (m_modelExtensionCard) {
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toFloat());
    }

    return this;
}




variableType CVariableInputBool::getType()const{
    return type_bool;
}
IVariable* CVariableInputBool::getIVariable(){
    return this;
}
QVariantMap CVariableInputBool::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_bValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
