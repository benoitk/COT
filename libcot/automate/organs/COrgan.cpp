#include "COrgan.h"
#include "CModelExtensionCard.h"
#include "qdebug.h"
COrgan::COrgan(const QVariantMap& mapOrgan, CModelExtensionCard* arg_extCard):IOrgan(){
    if(arg_extCard) m_extCard = arg_extCard;
    if(mapOrgan.contains(QStringLiteral("name")))
        m_name = mapOrgan.value(QStringLiteral("name")).toString();
    else m_name = QStringLiteral("Organ not named");

    if(mapOrgan.contains(QStringLiteral("address_data")))
        m_address = mapOrgan.value(QStringLiteral("address_data")).toString();//toInt(0, 16); //vérifier si le 0x (ou 0b) est pris en compte
    else m_address = QStringLiteral("0x00");
    if(mapOrgan.contains(QStringLiteral("type"))){
        QString sType = mapOrgan.value(QStringLiteral("type")).toString();
        if(sType == QStringLiteral("output_boolean"))
            m_type = organ_type_output_bool;
        else if (sType == QStringLiteral("output_float"))
            m_type = organ_type_output_float;
        else if (sType == QStringLiteral("output_integer"))
            m_type = organ_type_output_int;
        else if (sType == QStringLiteral("input_boolean"))
            m_type = organ_type_input_bool;
        else if (sType == QStringLiteral("input_float"))
            m_type = organ_type_input_float;
        else if (sType == QStringLiteral("input_integer"))
            m_type = organ_type_input_int;
    }
    else m_type = organType::organ_type_input_bool;
}
CModelExtensionCard* COrgan::getExtCard(){
    return m_extCard;
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
QString COrgan::typeToString()const{
    switch(m_type){
    case organ_type_input_bool: return tr("Digital input");
    case organ_type_input_float: return tr("Float input");
    case organ_type_input_int: return tr("Integer input");
    case organ_type_output_bool: return tr("Digital input");
    case organ_type_output_float: return tr("Float input");
    case organ_type_output_int : return tr("Integer input");

    }
}
//adresse physique sur le materiel, varie selon protocol
QString COrgan::getAddress()const {
//    QString sAddress = QStringLiteral("0x") + QString::number(m_address);
//    return sAddress;
    return m_address;
}
void COrgan::setAddress(const QString & arg_address) {
    m_address = arg_address.toInt();
}
QString COrgan::toString()const {
    QString sAddress = m_name + QStringLiteral(" addr:0x") + m_address;//QString::number(m_address);
    return sAddress;
}

