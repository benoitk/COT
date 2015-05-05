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
#include "ICom.h"
#include "CComFactory.h"
#include "CModelExtensionCard.h"
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
    m_stateCycleMesure = CYCLE_STATE_STOP;
    m_stateCycleIO = CYCLE_STATE_STOP;
    m_stateCycleMaintenance = CYCLE_STATE_STOP;
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
    if(var && var->getType() != type_unknow)
		m_mapVariables.insert(name, var);
}
void CAutomate::addStream(const QString& name, IVariable* var){
    QMutexLocker locker(&m_mutex);
	if(var && var->getType() != type_unknow)
		m_mapStreams.insert(name, var);
}

void CAutomate::addUnit(CUnit* unit){
    QMutexLocker locker(&m_mutex);
    m_listUnits.append(unit);
}

QList<CUnit*> CAutomate::getListUnits(){
    QMutexLocker locker(&m_mutex);
    return m_listUnits; 
}

CModelExtensionCard* CAutomate::getExtensionCard(const QString& name){
    QMutexLocker locker(&m_mutex);
    CModelExtensionCard* extCard = Q_NULLPTR;
    if(m_mapExtCards.contains(name))
        extCard = m_mapExtCards.value(name);
    else{
        if(m_mapExtCards.contains(QStringLiteral("unknown_extension_card")))
            extCard = m_mapExtCards.value(QStringLiteral("unknown_extension_card"));
        else{
            QVariantMap map;
            map.insert(QStringLiteral("name"),QStringLiteral("unknown_extension_card"));
            extCard = new CModelExtensionCard(map);
            m_mapExtCards.insert(QStringLiteral("unknown_extension_card"), extCard);
        }
    }
	return extCard;
}

QMap<QString, CModelExtensionCard*> CAutomate::getMapExtensions(){
    QMutexLocker locker(&m_mutex);
	return m_mapExtCards;
}
QMap<QString, ICom*> CAutomate::getMapComs(){
    QMutexLocker locker(&m_mutex);
    return m_mapComs;
}
void CAutomate::addCom(ICom* com){
    QMutexLocker locker(&m_mutex);
    if(com)    
        m_mapComs.insert(com->getName(), com);
}
ICom* CAutomate::getCom(const QString &arg_name){
    QMutexLocker locker(&m_mutex);
    ICom* com = Q_NULLPTR;
    if(m_mapComs.contains(arg_name))
        com = m_mapComs.value(arg_name);
    else{
        if(m_mapComs.contains(QStringLiteral("unknow_com")))
            com = m_mapComs.value(QStringLiteral("unknow_com"));
        else{
            com = CComFactory::build(QVariantMap());
            m_mapComs.insert(QStringLiteral("unknow_com"), com);
        }
    }
    return com;
}
QList<ICycle*> CAutomate::getListCycles(int cycleType){
    QMutexLocker locker(&m_mutex);
	QList<ICycle*> listAllCycles;

    switch (static_cast<eTypeCycle>(cycleType)) {
        case CYCLE_ALL: {
            listAllCycles << m_listCycleMesures.values();
            listAllCycles << m_listCycleMaintenances.values();
            listAllCycles << m_listlCycleAutonomes.values();
            break;
        }

        case CYCLE_MESURE: {
            listAllCycles << m_listCycleMesures.values();
            break;
        }

        case CYCLE_AUTONOME: {
            listAllCycles << m_listlCycleAutonomes.values();
            break;
        }

        case CYCLE_MAINTENANCE: {
            listAllCycles << m_listCycleMaintenances.values();
            break;
        }

        case CYCLE_PAUSE: {
            break;
        }

        case CYCLE_INVALID:
            Q_ASSERT(false);
            break;
    }

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
QMap<QString, IVariable*> CAutomate::getMapStreams(){
    QMutexLocker locker(&m_mutex);
    return m_mapStreams;
}
void CAutomate::setMapVariables(QMap<QString, IVariable*> mapVariable){
    QMutexLocker locker(&m_mutex);
    m_mapVariables.swap(mapVariable);
}

void CAutomate::addExtensionCard(const QString& name, CModelExtensionCard* extCard){
    QMutexLocker locker(&m_mutex);
    if(extCard && name != QStringLiteral(""))
        m_mapExtCards.insert(name, extCard);
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
        m_listCycleMesures[cycle->getName()] = cycle;
		break;
	case CYCLE_MAINTENANCE :
        m_listCycleMaintenances[cycle->getName()] = cycle;
		break;
	case CYCLE_AUTONOME:
        m_listlCycleAutonomes[cycle->getName()] = cycle;
		break;

    case CYCLE_PAUSE:
    case CYCLE_ALL:
            break;
    }
}

ICycle *CAutomate::getCycle(const QString &name, int type) const
{
    QMutexLocker locker(&m_mutex);

    switch(static_cast<eTypeCycle>(type)){
    case CYCLE_MESURE:
        return m_listCycleMesures.value(name, Q_NULLPTR);
    case CYCLE_MAINTENANCE :
        return m_listCycleMaintenances.value(name, Q_NULLPTR);
    case CYCLE_AUTONOME:
        return m_listlCycleAutonomes.value(name, Q_NULLPTR);
    case CYCLE_PAUSE:
    case CYCLE_ALL:
            break;
    }

    return Q_NULLPTR;
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
    return CAutomate::CYCLE_STATE_STOP;
}

CAutomate::eStateCycle CAutomate::getStateCycleIO( ){
    QMutexLocker locker(&m_mutex);
    // TODO
    return CAutomate::CYCLE_STATE_STOP;
}

CAutomate::eStateCycle CAutomate::getStateCycleMaintenance( ){
    QMutexLocker locker(&m_mutex);
    // TODO
    return CAutomate::CYCLE_STATE_STOP;
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

QString CAutomate::formatHistoryEntry(const QString &name, const QDateTime &dateTime)
{
    IVariable *ivar = getInstance()->getVariable(name);
    Q_ASSERT(ivar);
    return tr("%1: %2 (%3) updated to value %4")
            .arg(dateTime.toString())
            .arg(ivar->getLabel())
            .arg(ivar->getName())
            .arg(ivar->toString());
}

void CAutomate::setDisplayConf(CDisplayConf* displayConf){
    QMutexLocker locker(&m_mutex);
    m_displayConf = displayConf;
}
