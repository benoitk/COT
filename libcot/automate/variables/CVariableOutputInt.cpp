#include "CVariableOutputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "ICom.h"
#include "IOrgan.h"
CVariableOutputInt::CVariableOutputInt(QObject *parent)
    : CVariableInt(parent),IVariableOutput()
{

}

CVariableOutputInt::~CVariableOutputInt()
{

}

CVariableOutputInt::CVariableOutputInt(const QMap<QString, QVariant> &mapVar)
    : CVariableInt(mapVar),IVariableOutput(mapVar)
{

}

void CVariableOutputInt::writeValue(){
    m_organ->getExtCard()->getICom()->writeData(this);

}

void CVariableOutputInt::setValue(float arg_value){
    CVariableInt::setValue(arg_value);
    this->writeValue();
}

variableType CVariableOutputInt::getType()const{
    return type_int;
}
IVariable* CVariableOutputInt::getIVariable(){
    return this;
}

QVariantMap CVariableOutputInt::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_integer"));
    mapSerialise.insert(QStringLiteral("value"), m_value);
    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
VariableOrganType CVariableOutputInt::getOrganType() const {
    return type_organ_output;
}
