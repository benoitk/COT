#include "COrgan.h"

COrgan::COrgan(const QVariantMap& mapOrgan):IOrgan(){
    if(mapOrgan.contains(QStringLiteral("name")))
        m_name = mapOrgan.value(QStringLiteral("name")).toString();
    else m_name = QStringLiteral("Organ not named");

    if(mapOrgan.contains(QStringLiteral("address_data")))
        m_address = mapOrgan.value(QStringLiteral("address_data")).toInt(); //vérifier si le 0x (ou 0b) est pris en compte
    else m_address = 0;

    if(mapOrgan.contains(QStringLiteral("type"))){
        QString sType = mapOrgan.value(QStringLiteral("type")).toString();
        if(sType == QStringLiteral("output_boolean"))
            m_type = output_bool;
        else if (sType == QStringLiteral("output_float"))
            m_type = output_float;
        else if (sType == QStringLiteral("output_integer"))
            m_type = output_int;
        else if (sType == QStringLiteral("input_boolean"))
            m_type = input_bool;
        else if (sType == QStringLiteral("input_float"))
            m_type = input_float;
        else if (sType == QStringLiteral("input_integer"))
            m_type = input_int;
    }
    else m_type = organType::input_bool;
}
    
QString COrgan::getName()const {
    return m_name;
}
void COrgan::setName(const QString & name) {
   //useless
}
organType COrgan::getType()const {
    return m_type;
}
//adresse physique sur le materiel, varie selon protocol 
QString COrgan::getAddress()const {
    QString sAddress = QStringLiteral("0x") + QString::number(m_address);
    return sAddress;
} 
void COrgan::setAddress(const QString & arg_address) {
    m_address = arg_address.toInt();
}
QString COrgan::toString()const {
    QString sAddress = m_name + QStringLiteral(" addr:0x") + QString::number(m_address);
    return sAddress;
}

