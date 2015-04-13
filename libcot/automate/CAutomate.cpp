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
	m_sequenceur->setSequenceMesure(configFile.getListSequencesMesure());
	
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
        var = CVariableFactory::build(name + QLatin1String("unknow in map"));
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

QList<CModelExtensionCard*> CAutomate::getListExtensions(){
	return m_listExtCards;
}
QList<ICycle*> CAutomate::getListCycles(){
	QList<ICycle*> listAllCycles;
	listAllCycles.append(m_listCycleMesures);
	listAllCycles.append(m_listCycleMaintenances);
	listAllCycles.append(m_listlCycleAutonomes);
	return listAllCycles;
}
QList<IAction*>  CAutomate::getListActions(){
	return m_listActions;
}
QMap<QString, IVariable*> CAutomate::getMapVariables(){
	return m_mapVariables;
}
void CAutomate::setMapVariables(QMap<QString, IVariable*> mapVariable){
	m_mapVariables.swap(mapVariable);
}
QMap<QString, QList<QString>> CAutomate::getMapStreamsMeasures(){
	return m_mapStreamsMeasures;
}
void CAutomate::getMapStreamsMeasures(QMap<QString, QList<QString>> mapStreamMeasure){
	m_mapStreamsMeasures.swap(mapStreamMeasure);
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
		m_listCycleMesures.append(cycle);
		break;
	case CYCLE_MAINTENANCE :
		m_listCycleMaintenances.append(cycle);
		break;
	case CYCLE_AUTONOME:
		m_listlCycleAutonomes.append(cycle); 
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
