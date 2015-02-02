#include "ICycle.h"
#include "qvariant.h"
#include "qmap.h"


#include "CCycleAutonome.h"
#include "CCycleIO.h"
#include "CCycleMaintenance.h"
#include "CCycleMesure.h"
#include "CCyclePause.h"

#include "qdebug.h"

ICycle::ICycle(QObject *parent)
	: QObject(parent)
{

}
ICycle::ICycle()
	: QObject()
{

}

ICycle::~ICycle()
{

}
ICycle* ICycle::factory(QVariantMap mapCycle){
	qDebug() << "Pas la bonne factory !!!" ;
	ICycle* cycle = NULL;
	if(mapCycle["type"].toString() == "measure"){
		cycle = new CCycleMesure(mapCycle);
	}else if(mapCycle["type"].toString() == "pause"){
		cycle = new CCyclePause(mapCycle);
	}
	return cycle;
}
ICycle* ICycle::factory(QVariantMap mapCycle,QMap<QString, IAction*> mapAction){
	qDebug() << " ##ICycle::factory " ;
	ICycle* cycle = NULL;
	if(mapCycle["type"].toString() == "measure"){
		cycle = new CCycleMesure(mapCycle, mapAction);
	}else if(mapCycle["type"].toString() == "pause"){
		cycle = new CCyclePause(mapCycle);
	}
	qDebug() << " ## END ICycle::factory " ;
	return cycle;
}