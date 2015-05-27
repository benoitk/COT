#include "ICom.h"

comType stringToComType(const QString& type)
{
    if(type == QLatin1String("jbus_over_tcpip")){
        return type_jbus_over_tcpip;
    }else if(type == QLatin1String("jbus")){
        return type_jbus;
    }else if(type == QLatin1String("tcpip")){
        return type_tcpip;
    }
    return type_com_unknow;
}

ICom::ICom(QObject *parent)
    : QObject(parent)
{

}
ICom::~ICom()
{

}
