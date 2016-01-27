#include "IOrgan.h"

QVariantMap IOrgan::serialize(){
    QVariantMap mapSerialize;
    mapSerialize.insert(QStringLiteral("name"), getName());
    switch(getType()){
    case organ_type_output_bool:
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("output_boolean"));
        break;
    case organ_type_output_float:
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("output_float"));
        break;
    case organ_type_output_int:
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("output_integer"));
        break;
    case organ_type_input_bool:
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("input_boolean"));
        break;
    case organ_type_input_float:
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("input_float"));
        break;
    case organ_type_input_int:
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("input_integer"));
        break;
    default :
        mapSerialize.insert(QStringLiteral("type"), QStringLiteral("unknow_type_organ"));
        break;
    }

    mapSerialize.insert(QStringLiteral("address_data"), getAddress());
    return mapSerialize;
}
