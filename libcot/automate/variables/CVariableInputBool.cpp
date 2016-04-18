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
    bool value;
//    if(m_name =="var_entree_2")
//        value = m_organ->getExtCard()->getICom()->readData(this).toFloat();
    if(m_passive)
        value = m_organ->getExtCard()->getICom()->readData(this).toFloat();
    else
        value = !m_organ->getExtCard()->getICom()->readData(this).toFloat();


    CVariableBool::setValue(value);
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
    mapSerialise.insert(QStringLiteral("passive"), m_passive);
    return mapSerialise;
}
enumVariableOrganType CVariableInputBool::getOrganType() const {
    return e_type_organ_input;
}
