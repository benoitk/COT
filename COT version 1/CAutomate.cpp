#include "CAutomate.h"
#include "CControlerCycle.h"
#include "CSequenceur.h"
#include "ICycle.h"
#include "CCycleMesure.h"
#include "CCycleMaintenance.h"
#include "CCycleAutonome.h"
#include "CActionCmdPompe.h"
#include <qdebug.h>
#include <qthread.h>
#include "CModelConfigFile.h"
CAutomate::CAutomate()
{
	m_stateCycleMesure = 0;
	m_stateCycleIO = 0;
	m_stateCycleMaintenance = 0;

	CModelConfigFile configFile(this);
	
	QMap<QString, ICycle*> mapCycles = configFile.getMapCycle();
	m_sequenceur = CSequenceur::getInstance();
	m_sequenceur->setSequenceMesure(configFile.getListSequenceurMesure());
	
	QThread* threadSequenceur = new QThread(this);
	
	m_sequenceur->moveToThread(threadSequenceur);
	
	connect(threadSequenceur, &QThread::started, m_sequenceur, &CSequenceur::slotRequestPlaySequenceMesure);
	threadSequenceur->start();
	
 }

CAutomate::~CAutomate()
{

}


void CAutomate::addCycle(ICycle* cycle){
	//CControlerCycle* controlerCycle = new CControlerCycle(this, cycle);
	switch(cycle->getType()){
	case CYCLE_MESURE:
		m_listCycleMesure.append(cycle);
		break;
	case CYCLE_MAINTENANCE :
		m_listCycleMaintenance.append(cycle);
		break;
	case CYCLE_AUTONOME:
		m_listlCycleAutonome.append(cycle);
		break;

	}
}
void CAutomate::setStateCycleMesure(int state){
	
}

void CAutomate::setStateCycleIO(int state){

}
void CAutomate::setStateMaintenance(int state){

}
void CAutomate::setStateStopCycleMesure(){
	
}
void CAutomate::setStateStopCycleIO(){

}
void CAutomate::setStateStopCycleMaintenance(){

}
void CAutomate::setStatePauseCycleMesure(){

}
void CAutomate::setStatePauseCycleIO(){

}
void CAutomate::setStatePauseCycleMaintenance(){

}
void CAutomate::setStateRunCycleMesure(){

}
void CAutomate::setStateRunCycleIO(){

}
void CAutomate::setStateRunCycleMaintenance(){

}
void CAutomate::slotRunAutomate(){
	qDebug() << "CAutomate::runAutomate()";

	
	while(1){
		//qDebug() << "runAutomate" ;
		QThread::msleep(1000);
	}
}
