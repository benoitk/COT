#include "CComFactory.h"
#include "ICom.h"
#include "CComJBus.h"
#include "CComUnknow.h"
#include "qvariant.h"
#include "qmap.h"
#include "qdebug.h"



ICom* CComFactory::build(const QVariantMap &mapCom){
	
    ICom* com = Q_NULLPTR;
    if(mapCom[QStringLiteral("type")].toString() == QStringLiteral("jbus_over_tcpip")){
        com = new CComJBus(mapCom);
	
	}else{
        com = new CComUnknow();
        qDebug() << "Class com unknow :  " << mapCom[QStringLiteral("type")].toString();
	
	}

	return com;
}