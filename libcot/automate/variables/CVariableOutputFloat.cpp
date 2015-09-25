#include "CVariableOutputFloat.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "IOrgan.h"
#include "ICom.h"
#include "cotautomate_debug.h"
CVariableOutputFloat::CVariableOutputFloat(QObject *parent)
    : CVariableFloat(parent),IVariableOutput()
{

}

CVariableOutputFloat::~CVariableOutputFloat()
{

}

CVariableOutputFloat::CVariableOutputFloat(const QMap<QString, QVariant> &mapVar)
    : CVariableFloat(mapVar),IVariableOutput(mapVar)
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
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_float"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
enumVariableOrganType CVariableOutputFloat::getOrganType() const {
    return e_type_organ_output;
}
