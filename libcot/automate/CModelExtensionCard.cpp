#include "CModelExtensionCard.h"
#include "CAutomate.h"
#include "ICom.h"
#include "CComFactory.h"
#include "IOrgan.h"
#include "COrganFactory.h"

#include "cotautomate_debug.h"
#include "qvariant.h"
CModelExtensionCard::CModelExtensionCard(QObject *parent)
    : QObject(parent)
{

}

CModelExtensionCard::CModelExtensionCard(const QVariantMap& mapExt)
    : QObject()
{
    m_interfaceCom = Q_NULLPTR;
    if(mapExt.contains(QStringLiteral("name")))
        m_name = mapExt.value(QStringLiteral("name")).toString();
    else
        m_name = QStringLiteral("unamed_extension_card");

    if(mapExt.contains(tr("en_US")))
        m_label = mapExt.value(tr("en_US")).toString();
    else
        m_label = m_name;
    QVariantMap mapCom;
    if(mapExt.contains(QStringLiteral("com"))){
        mapCom = mapExt.value(QStringLiteral("com")).toMap();
        mapCom .insert(QStringLiteral("is_master"), true);
    }
    m_interfaceCom = CComFactory::build(mapCom);

    if(mapExt.contains(QStringLiteral("organs"))){
        QVariantList listOrgans = mapExt.value(QStringLiteral("organs")).toList();
        foreach(QVariant variantOrgan, listOrgans){
            QVariantMap mapOrgan = variantOrgan.toMap();
            IOrgan* organ = COrganFactory::build(mapOrgan, this);
            if(organ)
                m_mapOrgans.insert(organ->getName(), organ);
        }

    }
}
ICom* CModelExtensionCard::getICom()const{
    return m_interfaceCom;
}

CModelExtensionCard::~CModelExtensionCard(){}

IOrgan* CModelExtensionCard::getOrgan(const QString& arg_name){
    IOrgan* organ;
    if(m_mapOrgans.contains(arg_name))
        organ = m_mapOrgans.value(arg_name);
    else{
        if(m_mapOrgans.contains(QStringLiteral("unknown_organ")))
            organ = m_mapOrgans.value(QStringLiteral("unknown_organ"));
        else{
            QVariantMap map;
            map.insert(QStringLiteral("name"),QStringLiteral("unknown_organ"));
            organ = COrganFactory::build(map, this);
            m_mapOrgans.insert(organ->getName(), organ);
        }
    }
    return organ;
}
QMap<QString, IOrgan*> CModelExtensionCard::getMapOrgans(){
    return m_mapOrgans;
}
QString CModelExtensionCard::getName()const{
    return m_name;
}

QVariant CModelExtensionCard::readOrganneValue(IVariableInput* arg_varInput){
    return m_interfaceCom->readData(arg_varInput);
}

IVariable* CModelExtensionCard::getVariableByAddr(const QString &addr_var)const{
    IVariable * temp = Q_NULLPTR;
    return temp;
}

void CModelExtensionCard::setCom(ICom* com){
    m_interfaceCom = com;
}

QList<IOrgan *> CModelExtensionCard::getListOrgans() const
{
    return m_mapOrgans.values();
}

QString CModelExtensionCard::getLabel() const
{
   // CUSTOMER: Fix me
    return getName();
}

QVariantMap CModelExtensionCard::serialize(){
    QVariantMap mapSerialize;
    mapSerialize.insert(QStringLiteral("name"), m_name);
    mapSerialize.insert(tr("en_US"), m_label);
    mapSerialize.insert(QStringLiteral("com"), m_interfaceCom->serialize());
    QVariantList listSerializedOrgans;
    foreach(IOrgan* organ, m_mapOrgans){
        listSerializedOrgans.append(organ->serialize());
    }
    mapSerialize.insert(QStringLiteral("organs"), listSerializedOrgans);
    return mapSerialize;
}

