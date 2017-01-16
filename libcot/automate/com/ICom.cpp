#include "ICom.h"

enumComType stringToComType(const QString& type)
{
    if(type == QLatin1String("jbus_over_tcpip")){
        return e_type_jbus_over_tcpip_rtu;
    }else if(type == QLatin1String("jbus")){
        return e_type_jbus;
    }else if(type == QLatin1String("tcpip")){
        return e_type_jbus_over_tcpip;
    }
    return e_type_com_unknow;
}

QString comTypeToString(enumComType arg_eType){
    switch(arg_eType){
    case e_type_jbus_over_tcpip_rtu:
        return QLatin1String("jbus_over_tcpip");
    case e_type_jbus_over_tcpip:
        return QLatin1String("tcpip");
    case e_type_jbus:
        return QLatin1String("jbus");
    }
    return QLatin1String("unknow_com_type");
}

ICom::ICom(QObject *parent)
    : QObject(parent)
{

}
ICom::~ICom()
{

}
QVariantMap ICom::serialize(){

    return QVariantMap();
}
