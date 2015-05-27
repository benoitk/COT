#include "CComFactory.h"
#include "ICom.h"
#include "CComJBus.h"
#include "CComUnknow.h"
#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"



ICom* CComFactory::build(const QVariantMap &mapCom){

    ICom* com = Q_NULLPTR;
    switch (stringToComType(mapCom[QStringLiteral("type")].toString()))
    {
        case type_jbus_over_tcpip:
        case type_jbus:
        case type_tcpip:
            com = new CComJBus(mapCom);
            break;
        case type_com_unknow:
            com = new CComUnknow();
            qCDebug(COTAUTOMATE_LOG) << "Class com unknow :  " << mapCom[QStringLiteral("type")].toString();
            break;
    }

    return com;
}
