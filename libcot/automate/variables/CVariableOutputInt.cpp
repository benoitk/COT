#include "CVariableOutputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "ICom.h"
#include "CAutomate.h"'
#include "IOrgan.h"
CVariableOutputInt::CVariableOutputInt(CAutomate* arg_automate, QObject *parent)
    : CVariableInt(arg_automate, parent),IVariableOutput()
{

}

CVariableOutputInt::~CVariableOutputInt()
{

}

CVariableOutputInt::CVariableOutputInt(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject* parent)
    : CVariableInt(mapVar, arg_automate, parent)
    ,IVariableOutput(arg_automate->getExtensionCard(mapVar.value(QStringLiteral("extension_name")).toString())
                                              ->getOrgan(mapVar.value(QStringLiteral("organ_name")).toString()))
{

}

void CVariableOutputInt::writeValue(){
    m_organ->getExtCard()->getICom()->writeData(this);

}

void CVariableOutputInt::setValue(int arg_value){
    CVariableInt::setValue(arg_value);
    this->writeValue();
}

enumVariableType CVariableOutputInt::getType()const{
    return e_type_int;
}
IVariable* CVariableOutputInt::getIVariable(){
    return this;
}

QVariantMap CVariableOutputInt::serialize(){
    QVariantMap mapSerialise = IVariable::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_integer"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    mapSerialise.insert(QStringLiteral("value_min"), m_valueMin);
    mapSerialise.insert(QStringLiteral("value_max"), m_valueMax);
    return mapSerialise;
}
enumVariableOrganType CVariableOutputInt::getOrganType() const {
    return e_type_organ_output;
}
