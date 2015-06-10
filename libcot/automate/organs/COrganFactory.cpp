#include "COrganFactory.h"
#include "IOrgan.h"
#include "COrgan.h"

#include <QVariantMap>

IOrgan* COrganFactory::build(const QVariantMap &mapCom){

    IOrgan* organ = Q_NULLPTR;
  //  if(mapCom[QStringLiteral("type")].toString() == QStringLiteral("jbus_over_tcpip")){
        organ = new COrgan(mapCom);

//    }
/*else{
        organ = new COrganUnknow();
        qCDebug(COTAUTOMATE_LOG) << "Class organ unknow :  " << mapCom[QStringLiteral("type")].toString();

    }*/

    return organ;
}
