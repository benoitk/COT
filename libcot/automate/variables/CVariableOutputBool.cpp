#include "CVariableOutputBool.h"
#include "CModelExtensionCard.h"
#include "IOrgan.h"
#include "ICom.h"
#include "CUnit.h"
#include "qdebug.h"
CVariableOutputBool::CVariableOutputBool(QObject *parent)
    : CVariableBool(parent),IVariableOutput()
{

}

CVariableOutputBool::~CVariableOutputBool()
{

}

CVariableOutputBool::CVariableOutputBool(const QMap<QString, QVariant> &mapVar)
    : CVariableBool(mapVar),IVariableOutput(mapVar)
{
    m_passive = mapVar.value(QStringLiteral("passive")).toBool(); //false par défaut même si il n'y a de champs passive dans le json
}

void CVariableOutputBool::writeValue(){
    if(m_passive)
        m_organ->getExtCard()->getICom()->writeData(m_value, this->getOrganAddr());
    else
        m_organ->getExtCard()->getICom()->writeData(!m_value, this->getOrganAddr());
}

 void CVariableOutputBool::setValue(bool arg_value){
     CVariableBool::setValue(arg_value);
     this->writeValue();
 }
 void CVariableOutputBool::setToBindedValue(const QVariant & arg_value){
    CVariableBool::setToBindedValue(arg_value);
    this->writeValue();
 }

enumVariableType CVariableOutputBool::getType()const{
    return e_type_bool;
}
IVariable* CVariableOutputBool::getIVariable(){
    return this;
}


QVariantMap CVariableOutputBool::serialize(){
    QVariantMap mapSerialise = CVariableBool::serialize();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("output_boolean"));
    mapSerialise.insert(QStringLiteral("passive"), m_passive);
  //  mapSerialise.insert(QStringLiteral("value"), m_value);

    if(m_organ->getName() != QStringLiteral("unknown_organ")){
        mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
        mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    }
//    mapSerialise.insert(QStringLiteral("extension_name"), m_organ->getExtCard()->getName());
//    mapSerialise.insert(QStringLiteral("organ_name"), m_organ->getName());
    return mapSerialise;
}
enumVariableOrganType CVariableOutputBool::getOrganType() const {
    return e_type_organ_output;
}
