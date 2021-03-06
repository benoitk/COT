#include "CVariableOutputFloat.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "IOrgan.h"
#include "ICom.h"
#include "cotautomate_debug.h"
#include "CAutomate.h"
CVariableOutputFloat::CVariableOutputFloat(CAutomate* arg_automate, QObject *parent)
    : CVariableFloat(arg_automate, parent),IVariableOutput()
{

}

CVariableOutputFloat::~CVariableOutputFloat()
{

}

CVariableOutputFloat::CVariableOutputFloat(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject *parent)
    : CVariableFloat(mapVar, arg_automate, parent)
    ,IVariableOutput(arg_automate->getExtensionCard(mapVar.value(QStringLiteral("extension_name")).toString())
                                              ->getOrgan(mapVar.value(QStringLiteral("organ_name")).toString()))
{

}

void CVariableOutputFloat::writeValue(){
    m_organ->getExtCard()->getICom()->writeData(this);
}
void CVariableOutputFloat::setValue(float arg_value){
    CVariableFloat::setValue(arg_value);
    this->writeValue();
}

enumVariableType CVariableOutputFloat::getType()const{
    return e_type_float;
}
IVariable* CVariableOutputFloat::getIVariable(){
    return this;
}

QVariantMap CVariableOutputFloat::serialize()
{
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_float"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    mapSerialise.insert(QStringLiteral("value_min"), m_valueMin);
    mapSerialise.insert(QStringLiteral("value_max"), m_valueMax);
    mapSerialise.insert(QStringLiteral("precision"), m_precision);
    return mapSerialise;
}
enumVariableOrganType CVariableOutputFloat::getOrganType() const {
    return e_type_organ_output;
}
