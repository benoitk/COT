#include "CAutomate.h"
#include "CControlerCycle.h"
#include "CSequenceur.h"
#include "ICycle.h"
#include "IVariable.h"
#include "CCycleMesure.h"
#include "CCycleMaintenance.h"
#include "CCycleAutonome.h"
#include "CActionCmdPompe.h"
#include "CModelConfigFile.h"
#include "CVariableFactory.h"

#include <qdebug.h>
#include <qthread.h>


CAutomate* CAutomate::singleton = 0;

CAutomate* CAutomate::getInstance(){
	if(!singleton)
		singleton = new CAutomate();
	return singleton;
}

CAutomate::CAutomate()
{
	m_stateCycleMesure = 0;
	m_stateCycleIO = 0;
	m_stateCycleMaintenance = 0;
 }
void CAutomate::initConfig(){
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

IVariable* CAutomate::getVariable(QString name){
	QMutexLocker locker(&m_mutexVariablesAccess);

	IVariable* var = m_mapVariables.value(name);
	if(!var){
		var = CVariableFactory::build(name + "unknow in map");
	}
	return var;
}

void CAutomate::addVariable(QString name, IVariable* var){
	QMutexLocker locker(&m_mutexVariablesAccess);
	if(var)
		m_mapVariables.insert(name, var);
}

CModelExtensionCard* CAutomate::getExtensionCard(QString){
	CModelExtensionCard* modelExtCard;
	return modelExtCard;
}
void CAutomate::addExtensionCard(QString, CModelExtensionCard*){

}
IVariable* CAutomate::getVariable(QString addr_var)const{
	IVariable* modelExtCard;
	return modelExtCard;
}
void CAutomate::setCom(ICom* arg_comObject){

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
void CAutomate::setStateCycleMesure(eStateCycle state){
	
}

void CAutomate::setStateCycleIO(eStateCycle state){
}
void CAutomate::setStateCycleMaintenance(eStateCycle state){

}

CAutomate::eStateCycle CAutomate::getStateCycleMesure(){
    return CAutomate::CYCLE_STOP;
}

CAutomate::eStateCycle CAutomate::getStateCycleIO( ){
    return CAutomate::CYCLE_STOP;
}
CAutomate::eStateCycle CAutomate::getStateCycleMaintenance( ){
    return CAutomate::CYCLE_STOP;

}

void CAutomate::slotRunAutomate(){
	
	while(1){
		QThread::msleep(1000);
	}
}
