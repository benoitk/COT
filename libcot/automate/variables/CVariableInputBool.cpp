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
    m_passive = mapVar.value(QStringLiteral("passive")).toBool(); //false par défaut même si il n'y a de champs passive dans le json

}

IVariable* CVariableInputBool::readValue(){
    QMutexLocker lock(&m_mutex);
    if(m_passive)
        m_value = m_organ->getExtCard()->getICom()->readData(this).toFloat();
    else
        m_value = !m_organ->getExtCard()->getICom()->readData(this).toFloat();

    CVariableBool::setValue(m_value);
    return this;
}

IVariable* CVariableInputBool::getIVariable(){
    return this;
}

enumVariableType CVariableInputBool::getType()const{
    return e_type_bool;
}

QVariantMap CVariableInputBool::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("input_boolean"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
enumVariableOrganType CVariableInputBool::getOrganType() const {
    return e_type_organ_input;
}
