#include "CVariableInputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "ICom.h"
#include "IOrgan.h"
#include "CAutomate.h"
#include "qmutex.h"

CVariableInputInt::CVariableInputInt(CAutomate* arg_automate, QObject *parent)
    : CVariableInt(arg_automate, parent)
{

}

CVariableInputInt::~CVariableInputInt()
{

}

CVariableInputInt::CVariableInputInt(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject* parent)
    : CVariableInt(mapVar, arg_automate, parent)
    ,IVariableInput(arg_automate->getExtensionCard(mapVar.value(QStringLiteral("extension_name")).toString())
                                              ->getOrgan(mapVar.value(QStringLiteral("organ_name")).toString()))
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
