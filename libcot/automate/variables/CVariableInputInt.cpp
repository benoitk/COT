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

enumVariableType CVariableInputInt::getType()const{
    return e_type_int;
}
IVariable* CVariableInputInt::getIVariable(){
    return this;
}

QVariantMap CVariableInputInt::serialize(){
   QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_integer"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    mapSerialise.insert(QStringLiteral("value_min"), m_valueMin);
    mapSerialise.insert(QStringLiteral("value_max"), m_valueMax);
    return mapSerialise;
}
enumVariableOrganType CVariableInputInt::getOrganType() const {
    return e_type_organ_input;
}
