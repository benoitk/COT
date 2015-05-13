#include "CComFactory.h"
#include "ICom.h"
#include "CComJBus.h"
#include "CComUnknow.h"
#include "qvariant.h"
#include "qmap.h"
#include "cotautomate_debug.h"



ICom* CComFactory::build(const QVariantMap &mapCom){

    ICom* com = Q_NULLPTR;
    if(mapCom[QStringLiteral("type")].toString() == QStringLiteral("jbus_over_tcpip")){
        com = new CComJBus(mapCom);

    }else{
        com = new CComUnknow();
        qCDebug(COTAUTOMATE_LOG) << "Class com unknow :  " << mapCom[QStringLiteral("type")].toString();

    }

    return com;
}