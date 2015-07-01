#include "CVariableInputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "ICom.h"
#include "IOrgan.h"

#include "qmutex.h"

CVariableInputInt::CVariableInputInt(QObject *parent)
    : CVariableInt(parent)
{

}

CVariableInputInt::~CVariableInputInt()
{

}

CVariableInputInt::CVariableInputInt(const QMap<QString, QVariant> &mapVar)
    : CVariableInt(mapVar), IVariableInput(mapVar)
{

}



IVariable* CVariableInputInt::readValue(){
    QMutexLocker lock(&m_mutex);

    m_value = m_organ->getExtCard()->getICom()->readData(this).toInt();
    CVariableInt::setValue(m_value);
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
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
VariableOrganType CVariableInputInt::getOrganType() const {
    return type_organ_input;
}
