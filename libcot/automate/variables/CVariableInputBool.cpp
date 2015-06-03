#include "CVariableInputBool.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "CVariableBool.h"
#include "CUnit.h"

CVariableInputBool::CVariableInputBool(QObject *parent)
    : CVariableBool(parent), IVariableInput()
{

}

CVariableInputBool::~CVariableInputBool()
{

}
CVariableInputBool::CVariableInputBool(const QMap<QString, QVariant> &mapVar)
    : CVariableBool(), IVariableInput()
{

}

IVariable* CVariableInputBool::readValue(){
    if (m_modelExtensionCard) {
        QVariant var = m_modelExtensionCard->readOrganneValue(this);
        this->setValue(var.toBool());
    }

    return this;
}
IVariable* CVariableInputBool::getIVariable(){
    return this;
}

variableType CVariableInputBool::getType()const{
    return type_bool;
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
