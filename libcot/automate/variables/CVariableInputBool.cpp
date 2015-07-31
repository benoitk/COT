#include "CVariableInputBool.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "CVariableBool.h"
#include "CUnit.h"
#include "IOrgan.h"
#include "ICom.h"

#include "qmutex.h"

CVariableInputBool::CVariableInputBool(QObject *parent)
    : CVariableBool(parent), IVariableInput()
{

}

CVariableInputBool::~CVariableInputBool()
{

}
CVariableInputBool::CVariableInputBool(const QMap<QString, QVariant> &mapVar)
    : CVariableBool(mapVar), IVariableInput(mapVar)
{

}

IVariable* CVariableInputBool::readValue(){
    QMutexLocker lock(&m_mutex);
    m_value = m_organ->getExtCard()->getICom()->readData(this).toFloat();
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
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
VariableOrganType CVariableInputBool::getOrganType() const {
    return type_organ_input;
}
