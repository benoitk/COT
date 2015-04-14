#include "CCycleFactory.h"
#include "CCycleAutonome.h"
#include "CCycleMesure.h"
#include "CCyclePause.h"
#include "CCycleMaintenance.h"

#include "qdebug.h"
#include "qvariant.h"

ICycle* CCycleFactory::build(const QVariantMap &mapCycle, const QMap<QString, IAction*> &mapAction){
	ICycle* cycle = NULL;
    if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("measure")){
		cycle = new CCycleMesure(mapCycle, mapAction);
    }else if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("pause")){
		cycle = new CCyclePause(mapCycle);
    }else if(mapCycle[QStringLiteral("type")].toString() == QStringLiteral("autonome")){
		cycle = new CCycleAutonome(mapCycle);
	}else{
        qDebug() << "Type cycle INCONNU " << mapCycle[QStringLiteral("type")].toString();
	}
	return cycle;
}
