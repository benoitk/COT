#include "CAutomate.h"
#include "CControlerCycle.h"
#include "CSequencer.h"
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
#include "CActionFactory.h"
#include "CModelExtensionCard.h"
#include "CUnit.h"
#include "IOrgan.h"
#include "CVariableStream.h"
#include "CVariableMeasure.h"

#include "cotautomate_debug.h"
#include "qtimer.h"
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

    m_mappingCom.insert(QStringLiteral("0xffff"), CVariableFactory::build(QVariantMap())); //unknown address com


    QTimer* timer = new QTimer(this);
    m_iClock = 0;
    connect(timer, &QTimer::timeout, this, &CAutomate::slotClock);
    timer->setInterval(1000);
    timer->start();

 }

void CAutomate::initConfig(){
    CModelConfigFile configFile(this);

    QMap<QString, ICycle*> mapCycles = configFile.getMapCycle();
    m_sequencer = CSequencer::getInstance();
    m_sequencer->setSequenceMesure(configFile.getListSequencesMesure());

    QThread* threadSequencer = new QThread(this);

    m_sequencer->moveToThread(threadSequencer);

    connect(threadSequencer, &QThread::started, m_sequencer, &CSequencer::slotRequestPlaySequenceMesure);
    connect(m_sequencer, &CSequencer::signalUpdated, this, &CAutomate::signalSchedulerUpdated);
    threadSequencer->start();
}


CAutomate::~CAutomate()
{
    QThread* threadSequencer = m_sequencer->thread();
    threadSequencer->quit();
    threadSequencer->wait();
}

void CAutomate::addCyclePrivate(ICycle * cycle)
{
    //CControlerCycle* controlerCycle = new CControlerCycle(this, cycle);
    switch(cycle->getType()){
        case CYCLE_MESURE:
            Q_ASSERT(!m_listCycleMesures.contains(cycle->getName()));
            m_listCycleMesures[cycle->getName()] = cycle;
            break;
        case CYCLE_MAINTENANCE :
            Q_ASSERT(!m_listCycleMaintenances.contains(cycle->getName()));
            m_listCycleMaintenances[cycle->getName()] = cycle;
            break;
        case CYCLE_AUTONOME:
            Q_ASSERT(!m_listlCycleAutonomes.contains(cycle->getName()));
            m_listlCycleAutonomes[cycle->getName()] = cycle;
            break;

        case CYCLE_PAUSE:
            break;

        case CYCLE_ALL:
            Q_ASSERT(false);
            break;
    }
}

QList<ICycle *> CAutomate::getListCyclesPrivate(int cycleType)
{
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

QMap<QString, IVariable *> CAutomate::getMapVariablesPrivate()
{
     return m_mapVariables;
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
    addVariablePrivate(name, var);
}

void CAutomate::addVariablePrivate(const QString& name, IVariable* var){
    if(var && var->getType() != type_unknow){
        m_mapVariables.insert(name, var);
        if(var->getAddress() != 0){
            m_mappingCom.insert(QString::number(var->getAddress(), 16 /*hexa*/), var);
        }

        connect(var, &IVariable::signalVariableChanged, this, &CAutomate::slotVariableChanged);
    }
}


void CAutomate::addStream(CVariableStream* arg_stream){
    QMutexLocker locker(&m_mutex);
    if(arg_stream){
        bool bStreamExist = false;
        foreach(CVariableStream* stream, m_listStreams){
            if(arg_stream == stream) bStreamExist = true;
        }
        if(!bStreamExist)
            m_listStreams.append(arg_stream);
    }
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
void CAutomate::addAction(IAction* action){
    QMutexLocker locker(&m_mutex);
    if(action){
        m_mapActions.insert(action->getName(), action);
        m_listActions.append(action);// en redondance avec m_mapActions pour ne pas casser l'API
    }
}

void CAutomate::delAction(IAction* arg_action){
    QMutexLocker locker(&m_mutex);
    if(arg_action){
        if(m_mapActions.contains(arg_action->getName())){
            IAction* action = m_mapActions.take(arg_action->getName());
            if(action){
                foreach(ICycle* cycle, m_listCycleMesures){
                    cycle->removeAction(action);
                }
                foreach(ICycle* cycle, m_listCycleMaintenances){
                    cycle->removeAction(action);
                }
                foreach(ICycle* cycle, m_listlCycleAutonomes){
                    cycle->removeAction(action);
                }
                delete action;
            }
        }
    }
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
IAction* CAutomate::getAction(const QString &arg_name){
    QMutexLocker locker(&m_mutex);
    IAction* action = Q_NULLPTR;
    if(m_mapActions.contains(arg_name))
        action = m_mapActions.value(arg_name);
    else{
        if(m_mapActions.contains(QStringLiteral("unknow_action")))
            action = m_mapActions.value(QStringLiteral("unknow_action"));
        else{
            action = CActionFactory::build(QVariantMap());
            m_mapActions.insert(QStringLiteral("unknow_action"), action);
        }
    }
    return action;
}

// SERES_TODO: delAction (COT-60)

QList<ICycle*> CAutomate::getListCycles(int cycleType){
    QMutexLocker locker(&m_mutex);
    return getListCyclesPrivate(cycleType);
}
void CAutomate::slotClock(){
    qCDebug(COTAUTOMATE_LOG) << "Tick " << m_iClock++%600;
}
QList<IAction*>  CAutomate::getListActions(){
    QMutexLocker locker(&m_mutex);
    return m_listActions;
}
QMap<QString, IAction*> CAutomate::getMapActions(){
    QMutexLocker locker(&m_mutex);
    return m_mapActions;
}

QMap<QString, IVariable*> CAutomate::getMapVariables(){
    QMutexLocker locker(&m_mutex);
    return getMapVariablesPrivate();
}
QList<CVariableStream*> CAutomate::getListStreams(){
    QMutexLocker locker(&m_mutex);
    return m_listStreams;
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

void CAutomate::delVariable(IVariable *ivar)
{
    // SERES_TODO: To be completed (COT-XX).
    // There is probably more to update, like in CSequencer etc.
    QMutexLocker locker(&m_mutex);
    IVariable *var = m_mapVariables.take(ivar->getName());

    foreach ( CVariableStream *streamVar, m_listStreams) {

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            measureVar->delVariable(ivar);
        }
        streamVar->delVariable(ivar);
    }
    locker.unlock();
    if (var) {
        emit signalVariablesUpdated();
        delete var;
    }
}

void CAutomate::delCycle(ICycle *cycle)
{
    // SERES_TODO: To be completed (COT-58).
    // There is probably more to update, like in CSequencer etc.
    QMutexLocker locker(&m_mutex);

    foreach(CVariableStream* stream, m_listStreams){
        if(stream->getName() == cycle->getRelatedStreamName()){

            stream->delCycle(cycle->getName());

            switch(cycle->getType()){
            case CYCLE_MESURE:
                delete m_listCycleMesures.take(cycle->getName());
                break;

            case CYCLE_MAINTENANCE :
                delete m_listCycleMaintenances.take(cycle->getName());
                break;


            case CYCLE_AUTONOME:
                delete m_listlCycleAutonomes.take(cycle->getName());
                break;

            case CYCLE_PAUSE:
                break;

            case CYCLE_ALL:
                Q_ASSERT(false);
                break;
            }
        }
    }
}

IVariable* CAutomate::getVariableByAddr(const QString &addr_var)const{
    QMutexLocker locker(&m_mutex);
    IVariable* var= Q_NULLPTR;
    if(m_mappingCom.contains(addr_var))
        var = m_mappingCom.value(addr_var);
    else if(m_mapActions.contains(QStringLiteral("0xffff")))
        var = m_mappingCom.value(QStringLiteral("0xffff"));
    return var;
}
void CAutomate::addVariableToMappingCom(IVariable* var){
    QMutexLocker locker(&m_mutex);
    if(var && var->getType() != type_unknow)
        m_mappingCom.insert(QString::number(var->getAddress(), 16 /*hexa*/), var);
}

void CAutomate::setCom(ICom* arg_comObject){
    QMutexLocker locker(&m_mutex);
    // TODO
}

void CAutomate::addCycle(ICycle* cycle){
    QMutexLocker locker(&m_mutex);
    addCyclePrivate(cycle);
    locker.unlock();
    emit signalCyclesUpdated();
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
            break;

        case CYCLE_ALL: {
            ICycle * cycle = m_listCycleMesures.value(name, Q_NULLPTR);

            if (!cycle) {
                m_listCycleMaintenances.value(name, Q_NULLPTR);
            }

            if (!cycle) {
                m_listlCycleAutonomes.value(name, Q_NULLPTR);
            }

            return cycle;
        }
    }

    return Q_NULLPTR;
}

CUnit *CAutomate::getUnit(const QString &name) const
{
    foreach (CUnit *unit, m_listUnits) {
        if (unit->getName() == name) {
            return unit;
        }
    }

    return Q_NULLPTR;
}

IOrgan *CAutomate::getOrgan(const QString &name) const
{
    foreach (CModelExtensionCard *card, m_mapExtCards.values()) {
        foreach (IOrgan *organ, card->getListOrgans()) {
            if (organ->getName() == name) {
                return organ;
            }
        }
    }

    return Q_NULLPTR;
}

CVariableStream *CAutomate::getStream(const QString &name) const
{
    foreach (CVariableStream *stream, m_listStreams) {
        if (stream->getName() == name) {
            return stream;
        }
    }

    return Q_NULLPTR;
}

CVariableMeasure *CAutomate::getMeasure(const QString &name) const
{
    foreach (CVariableStream *stream, m_listStreams) {
          foreach (IVariable *ivarMeasure, stream->getListMeasures()) {
            if (ivarMeasure->getName() == name) {
                return static_cast<CVariableMeasure *>(ivarMeasure);
            }
        }
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

void CAutomate::slotVariableChanged()
{
    IVariable *ivar = qobject_cast<IVariable *>(sender());
    emit signalVariableChanged(ivar->getName());
}

CDisplayConf* CAutomate::getDisplayConf()const{
    QMutexLocker locker(&m_mutex);
    return m_displayConf;
}

void CAutomate::informAboutCycleChanges(ICycle *cycle, const QVariantMap &oldData)
{
    QMutexLocker locker(&m_mutex);

    // SERES_TODO: implement automate internal change handling.
    // There is probably more to update, like in CSequencer etc.
    const bool isNew = !getListCyclesPrivate().contains(cycle);
    const QString oldStreamName = oldData.value(QStringLiteral("related_stream_name")).toString();

    if (isNew) {
        addCyclePrivate(cycle);
    }

    CVariableStream *oldStream;
    CVariableStream *newStream;
    foreach (CVariableStream* stream, m_listStreams) {
        if(stream->getName() == oldStreamName) oldStream = stream;
        else if(stream->getName() == cycle->getRelatedStreamName()) newStream = stream;
    }

    if (!oldStreamName.isEmpty() && !oldStream) {
        Q_ASSERT(false);
    }

    if (!cycle->getRelatedStreamName().isEmpty() && !newStream) {
        Q_ASSERT(false);
    }

    if (oldStream) {
        oldStream->delCycle(cycle->getName());
    }

    if (newStream) {
        newStream->addCycle(cycle);
    }

    locker.unlock();

    if (!isNew) {
        emit signalCycleChanged(cycle->getName());
    }

    emit signalCyclesUpdated();
}

void CAutomate::informAboutVariableChanges(IVariable *variable, const QVariantMap &oldData)
{
    QMutexLocker locker(&m_mutex);

    // SERES_TODO: implement automate internal change handling.
    // There is probably more to update, like in CSequencer etc.
    const bool isNew = !getMapVariablesPrivate().values().contains(variable);

    if (isNew) {
        addVariablePrivate(variable->getName(), variable);
    }

    locker.unlock();

    if (!isNew) {
        emit signalVariableChanged(variable->getName());
    }

    emit signalVariablesUpdated();
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
