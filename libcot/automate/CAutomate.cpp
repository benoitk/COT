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
#include "CDisplayConf.h"

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

void CAutomate::quit()
{
    QMutexLocker locker(&m_mutex);
    m_quit = true;
}

CAutomate::~CAutomate()
{
    QThread* threadSequenceur = m_sequenceur->thread();
    threadSequenceur->quit();
    threadSequenceur->wait();
}

bool CAutomate::shouldQuit()
{
    QMutexLocker locker(&m_mutex);
    return m_quit;
}

IVariable* CAutomate::getVariable(const QString &name){
    QMutexLocker locker(&m_mutex);

	IVariable* var = m_mapVariables.value(name);
	if(!var){
        var = CVariableFactory::build(name + QLatin1String("unknow in map"));
	}
    return var;
}

QList<IVariable *> CAutomate::getVariables(const QStringList &names)
{
    QMutexLocker locker(&m_mutex);
    QList<IVariable *> ivars;

    foreach (const QString &name, names) {
        IVariable *ivar = m_mapVariables.value(name, 0);
        if(!ivar){
            ivar = CVariableFactory::build(name + QLatin1String("unknow in map"));
        }
        ivars << ivar;
    }

    return ivars;
}

void CAutomate::addVariable(const QString& name, IVariable* var){
    QMutexLocker locker(&m_mutex);
	if(var)
		m_mapVariables.insert(name, var);
}

void CAutomate::addUnit(CUnit* unit){
    QMutexLocker locker(&m_mutex);
    m_listUnits.append(unit);
}

QList<CUnit*> CAutomate::getListUnits(){
    QMutexLocker locker(&m_mutex);
    return m_listUnits; 
}

CModelExtensionCard* CAutomate::getExtensionCard(QString){
    QMutexLocker locker(&m_mutex);
	CModelExtensionCard* modelExtCard = 0;
    // TODO
	return modelExtCard;
}

QList<CModelExtensionCard*> CAutomate::getListExtensions(){
    QMutexLocker locker(&m_mutex);
	return m_listExtCards;
}

QList<ICycle*> CAutomate::getListCycles(){
    QMutexLocker locker(&m_mutex);
	QList<ICycle*> listAllCycles;
	listAllCycles.append(m_listCycleMesures);
	listAllCycles.append(m_listCycleMaintenances);
	listAllCycles.append(m_listlCycleAutonomes);
	return listAllCycles;
}

QList<IAction*>  CAutomate::getListActions(){
    QMutexLocker locker(&m_mutex);
	return m_listActions;
}

QMap<QString, IVariable*> CAutomate::getMapVariables(){
    QMutexLocker locker(&m_mutex);
	return m_mapVariables;
}

void CAutomate::setMapVariables(QMap<QString, IVariable*> mapVariable){
    QMutexLocker locker(&m_mutex);
	m_mapVariables.swap(mapVariable);
}

QMap<QString, QList<QString>> CAutomate::getMapStreamsMeasures() const{
    QMutexLocker locker(&m_mutex);
	return m_mapStreamsMeasures;
}

void CAutomate::setMapStreamsMeasures(QMap<QString, QList<QString>> mapStreamMeasure){
    QMutexLocker locker(&m_mutex);
	m_mapStreamsMeasures.swap(mapStreamMeasure);
}

void CAutomate::addExtensionCard(QString, CModelExtensionCard*){
    QMutexLocker locker(&m_mutex);
    // TODO
}

IVariable* CAutomate::getVariable(const QString &addr_var)const{
    QMutexLocker locker(&m_mutex);
	IVariable* modelExtCard;
    // TODO
	return modelExtCard;
}

void CAutomate::setCom(ICom* arg_comObject){
    QMutexLocker locker(&m_mutex);
    // TODO
}

void CAutomate::addCycle(ICycle* cycle){
    QMutexLocker locker(&m_mutex);
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
    QMutexLocker locker(&m_mutex);
    // TODO
}

void CAutomate::setStateCycleIO(eStateCycle state){
    QMutexLocker locker(&m_mutex);
    // TODO
}

void CAutomate::setStateCycleMaintenance(eStateCycle state){
    QMutexLocker locker(&m_mutex);
    // TODO
}

CAutomate::eStateCycle CAutomate::getStateCycleMesure(){
    QMutexLocker locker(&m_mutex);
    // TODO
    return CAutomate::CYCLE_STOP;
}

CAutomate::eStateCycle CAutomate::getStateCycleIO( ){
    QMutexLocker locker(&m_mutex);
    // TODO
    return CAutomate::CYCLE_STOP;
}

CAutomate::eStateCycle CAutomate::getStateCycleMaintenance( ){
    QMutexLocker locker(&m_mutex);
    // TODO
    return CAutomate::CYCLE_STOP;
}

void CAutomate::slotRunAutomate(){
    while(!shouldQuit()){
        // TODO
        QThread::msleep(100);
	}
}

CDisplayConf* CAutomate::getDisplayConf()const{
    QMutexLocker locker(&m_mutex);
    return m_displayConf;
}

void CAutomate::setDisplayConf(CDisplayConf* displayConf){
    QMutexLocker locker(&m_mutex);
    m_displayConf = displayConf;
}
