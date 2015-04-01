#include "CCycleFactory.h"
#include "CCycleAutonome.h"
#include "CCycleMesure.h"
#include "CCyclePause.h"
#include "CCycleMaintenance.h"

#include "qdebug.h"
#include "qvariant.h"

ICycle* CCycleFactory::build(QVariantMap mapCycle,QMap<QString, IAction*> mapAction){
	ICycle* cycle = NULL;
	if(mapCycle["type"].toString() == "measure"){
		cycle = new CCycleMesure(mapCycle, mapAction);
	}else if(mapCycle["type"].toString() == "pause"){
		cycle = new CCyclePause(mapCycle);
	}else if(mapCycle["type"].toString() == "autonome"){
		cycle = new CCycleAutonome(mapCycle);
	}else{
		qDebug() << "Type cycle INCONNU " << mapCycle["type"].toString();	
	}
	return cycle;
}