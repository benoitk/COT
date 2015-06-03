#include "CVariableOutputBool.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"

CVariableOutputBool::CVariableOutputBool(QObject *parent)
    : CVariableBool(parent),IVariableOutput()
{

}

CVariableOutputBool::~CVariableOutputBool()
{

}

CVariableOutputBool::CVariableOutputBool(const QMap<QString, QVariant> &mapVar)
    : CVariableBool(),IVariableOutput()
{

}

void CVariableOutputBool::writeValue(){


}


variableType CVariableOutputBool::getType()const{
    return type_bool;
}
IVariable* CVariableOutputBool::getIVariable(){
    return this;
}


QVariantMap CVariableOutputBool::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_bValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
