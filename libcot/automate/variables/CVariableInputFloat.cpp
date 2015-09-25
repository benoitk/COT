#include "CVariableInputFloat.h"
#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "CUnit.h"
#include "IOrgan.h"
#include "ICom.h"

#include "qmutex.h"

CVariableInputFloat::CVariableInputFloat(QObject *parent)
    : CVariableFloat(parent), IVariableInput()
{

}

CVariableInputFloat::~CVariableInputFloat()
{

}

CVariableInputFloat::CVariableInputFloat(const QMap<QString, QVariant> &mapVar)
    : CVariableFloat(mapVar), IVariableInput(mapVar)
{

}

IVariable* CVariableInputFloat::readValue(){
    QMutexLocker lock(&m_mutex);
    m_value = m_organ->getExtCard()->getICom()->readData(this).toFloat();
    CVariableFloat::setValue(m_value);
    return this;
}

enumVariableType CVariableInputFloat::getType()const{
    return e_type_float;
}
IVariable* CVariableInputFloat::getIVariable(){
    return this;
}

QVariantMap CVariableInputFloat::serialize(){
     QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_float"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
enumVariableOrganType CVariableInputFloat::getOrganType() const {
    return e_type_organ_input;
}
