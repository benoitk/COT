#include "COrganFactory.h"
#include "IOrgan.h"
#include "COrgan.h"

IOrgan* COrganFactory::build(const QVariantMap &mapCom){
	
    IOrgan* organ = Q_NULLPTR;
    if(mapCom[QStringLiteral("type")].toString() == QStringLiteral("jbus_over_tcpip")){
        organ = new COrgan(mapCom);
	
	}/*else{
        organ = new COrganUnknow();
        qDebug() << "Class organ unknow :  " << mapCom[QStringLiteral("type")].toString();
	
	}*/

	return organ;
}