#include "CVariableOutputInt.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"

CVariableOutputInt::CVariableOutputInt(QObject *parent)
    : CVariableInt(parent)
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CVariableOutputInt::~CVariableOutputInt()
{

}

CVariableOutputInt::CVariableOutputInt(const QMap<QString, QVariant> &mapVar)
    : CVariableInt()
    , m_modelExtensionCard(Q_NULLPTR)
{

}

CModelExtensionCard* CVariableOutputInt::getExtensionCard()const{
    return m_modelExtensionCard;
}
IComObserver* CVariableOutputInt::getComObserver()const{
    return m_modelExtensionCard;
}
QString CVariableOutputInt::getOrganneName()const{
    return m_organneName;
}
QString CVariableOutputInt::getOrganneAddr()const{
    return QStringLiteral("return ADDR");
}
void CVariableOutputInt::setOrganne(CModelExtensionCard* arg_model, const QString &arg_organneName){
    m_modelExtensionCard = arg_model;
    m_organneName = arg_organneName;
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
