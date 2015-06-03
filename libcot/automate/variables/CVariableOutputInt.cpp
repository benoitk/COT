#include "CVariableOutputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"

CVariableOutputInt::CVariableOutputInt(QObject *parent)
    : CVariableInt(parent),IVariableOutput()
{

}

CVariableOutputInt::~CVariableOutputInt()
{

}

CVariableOutputInt::CVariableOutputInt(const QMap<QString, QVariant> &mapVar)
    : CVariableInt(),IVariableOutput()
{

}

void CVariableOutputInt::writeValue(){


}

void CVariableOutputInt::setValue(float value){
    m_iValeur = value;
    if(!m_listBinds.isEmpty()){
        IVariable* var;
        foreach(var,  m_listBinds){
            var->setValue(QVariant(value));
        }
    }

    emit signalVariableChanged();
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
    mapSerialise.insert(QStringLiteral("value"), m_iValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
