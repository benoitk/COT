#include "CVariableOutputFloat.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "cotautomate_debug.h"
CVariableOutputFloat::CVariableOutputFloat(QObject *parent)
    : CVariableFloat(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableOutputFloat::~CVariableOutputFloat()
{

}

CVariableOutputFloat::CVariableOutputFloat(const QMap<QString, QVariant> &mapVar)
    : CVariableFloat()
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CModelExtensionCard* CVariableOutputFloat::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* CVariableOutputFloat::getComObserver()const{
    return m_modelExtensionCard;
}
QString CVariableOutputFloat::getOrganneName()const{
    return m_organneName;
}
QString CVariableOutputFloat::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableOutputFloat::setOrganne(CModelExtensionCard* arg_model, const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
}

void CVariableOutputFloat::writeValue(){


}


void CVariableOutputFloat::setValue(float value){
    m_fValeur = value;
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
    mapSerialise.insert(QStringLiteral("value"), m_fValeur);
    mapSerialise.insert(QStringLiteral("extension_name"), m_modelExtensionCard->getName());
    mapSerialise.insert(QStringLiteral("organ_name"), m_organneName);
    return mapSerialise;
}
