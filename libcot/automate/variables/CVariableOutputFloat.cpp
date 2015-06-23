#include "CVariableOutputFloat.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "IOrgan.h"
#include "cotautomate_debug.h"
CVariableOutputFloat::CVariableOutputFloat(QObject *parent)
    : CVariableFloat(parent),IVariableOutput()
{

}

CVariableOutputFloat::~CVariableOutputFloat()
{

}

CVariableOutputFloat::CVariableOutputFloat(const QMap<QString, QVariant> &mapVar)
    : CVariableFloat(),IVariableOutput()
{

}

void CVariableOutputFloat::writeValue(){


}

void CVariableOutputFloat::setValue(float value){
    m_value = value;
    if(!m_listBinds.isEmpty()){
        IVariable* var;
        foreach(var,  m_listBinds){
            var->setValue(QVariant(value));
        }
    }

    emit signalVariableChanged();
}

variableType CVariableOutputFloat::getType()const{
    return type_float;
}
IVariable* CVariableOutputFloat::getIVariable(){
    return this;
}

QVariantMap CVariableOutputFloat::serialise()
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
VariableOrganType CVariableOutputFloat::getOrganType() const {
    return VariableOrganTypeOutput;
}
