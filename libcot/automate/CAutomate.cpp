#include "CAutomate.h"
#include "CControlerCycle.h"
#include "CScheduler.h"
#include "ICycle.h"
#include "IVariable.h"
#include "CVariableAlarm.h"
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
#include "CThreadDiag.h"
#include "IConverter.h"

#include "cotautomate_debug.h"
#include "qtimer.h"
#include "qfile.h"
#include "qdir.h"

#include <QJsonDocument>
#ifdef Q_OS_UNIX
#include <QProcess>
#endif

#include <QApplication>
#include <QTranslator>

CAutomate* CAutomate::singleton = 0;

CAutomate* CAutomate::getInstance(){
    if(!singleton)
        singleton = new CAutomate();
    return singleton;
}

CAutomate::CAutomate()
{
    m_debug = false;
    m_schedulerStoppedFromIHM = false;
    m_lang = "en_US";
    m_countBeforeCheckLogFileToDelete = 0;
    m_stateCycleMesure = CYCLE_STATE_STOP;
    m_stateCycleIO = CYCLE_STATE_STOP;
    m_stateCycleMaintenance = CYCLE_STATE_STOP;

   // m_mappingCom.insert(QStringLiteral("0xffff"), CVariableFactory::build(QVariantMap())); //unknown address com


    QTimer* timer = new QTimer(this);
    m_iClock = 0;
    connect(timer, &QTimer::timeout, this, &CAutomate::slotClock);
    timer->setInterval(250);
   // timer->start();

    // for use in queued signal/slot connections
    qRegisterMetaType<CAutomate::eStateAutomate>();
    qRegisterMetaType<CAutomate::eStateStream>();
}
void CAutomate::setDebug(bool arg_debug){
    m_debug = arg_debug;
}

void CAutomate::initConfig(){

}
void CAutomate::slotStartAutomate(){
    m_scheduler = CScheduler::getInstance();
    connect(m_scheduler, &CScheduler::signalUpdated, this, &CAutomate::signalSchedulerUpdated);
    m_threadDiag = new CThreadDiag(this);

    CModelConfigFile configFile(this);

    if(m_debug)
        QTimer::singleShot(1000, this, SLOT(slotLogVariable()));

}

CAutomate::~CAutomate()
{
    QThread* threadSequencer = m_scheduler->thread();
    threadSequencer->quit();
    threadSequencer->wait();
}
CScheduler* CAutomate::getScheduler()const{
    return m_scheduler;
}
void CAutomate::slotTabChanged(int tab_index){
    qDebug() << "slotTabChange " << tab_index;
      if(tab_index == 1) m_threadDiag->slotStart();
      else m_threadDiag->slotStop();
}

void CAutomate::addCyclePrivate(ICycle * cycle)
{
    //CControlerCycle* controlerCycle = new CControlerCycle(this, cycle);
    switch(cycle->getType()){
        case e_cycle_measure:
        case e_cycle_pause:
            Q_ASSERT(!m_listCycleMesures.contains(cycle->getName()));
            m_listCycleMesures[cycle->getName()] = cycle;
            break;
        case e_cycle_maintenance :
            Q_ASSERT(!m_listCycleMaintenances.contains(cycle->getName()));
            m_listCycleMaintenances[cycle->getName()] = cycle;
            break;
        case e_cycle_autonome:
            Q_ASSERT(!m_listlCycleAutonomes.contains(cycle->getName()));
            m_listlCycleAutonomes[cycle->getName()] = cycle;
            break;

        //case e_cycle_pause:
        //    break;

        case e_cycle_all:
            Q_ASSERT(false);
            break;
    }
}
void CAutomate::acquitAlarms(){
    //TO DO : virer la list screen alarm, pour laisser les alarmes s'afficher toutes seul et les
    // ajouter une liste de variable pour les acquiter
    m_mapAlarmWhichStoppedScheduler.clear();
    emit signalAquitAllAlarm();
}

QList<ICycle *> CAutomate::getListCyclesPrivate(int cycleType)
{
    QList<ICycle*> listAllCycles;

    switch (static_cast<enumTypeCycle>(cycleType)) {
        case e_cycle_all: {
            listAllCycles << m_listCycleMesures.values();
            listAllCycles << m_listCycleMaintenances.values();
            listAllCycles << m_listlCycleAutonomes.values();
            break;
        }

        case e_cycle_measure:
        case e_cycle_pause:{
            listAllCycles << m_listCycleMesures.values();
            break;
        }

        case e_cycle_autonome: {
            listAllCycles << m_listlCycleAutonomes.values();
            break;
        }

        case e_cycle_maintenance: {
            listAllCycles << m_listCycleMaintenances.values();
            break;
        }

//        case e_cycle_pause: {
//            break;
//        }

        case e_cycle_invalid:
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
    if(!var && !(var = m_mapVariables.value(QStringLiteral("unknown_var")))){
         var = CVariableFactory::build(QVariantMap());
         m_mapVariables.insert(var->getName(), var);
    }
    return var;
}

QList<IVariable *> CAutomate::getVariables(const QStringList &names)
{
    QMutexLocker locker(&m_mutex);
    QList<IVariable *> ivars;

    foreach (const QString &name, names) {
        IVariable *ivar = m_mapVariables.value(name, 0);
        if(!ivar && !(ivar = m_mapVariables.value(QStringLiteral("unknown_var")))){
            ivar = CVariableFactory::build(QVariantMap());
            m_mapVariables.insert(ivar->getName(), ivar);
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
    if(var && var->getType() != e_type_unknow){
        m_mapVariables.insert(name, var);
        if(var->getAddress() != 0){
            m_mappingCom.insert(QString::number(var->getAddress(), 16 /*hexa*/), var);
        }

        connect(var, &IVariable::signalVariableChanged, this, &CAutomate::slotVariableChanged);
    }
}


void CAutomate::addStream(CVariableStream* arg_stream, bool emitSignalOnAdd){
    QMutexLocker locker(&m_mutex);
    if(arg_stream){
        bool bStreamExist = false;
        foreach(CVariableStream* stream, m_listStreams){
            if(arg_stream == stream) bStreamExist = true;
        }
        if(!bStreamExist) {
            m_listStreams.append(arg_stream);
            if (emitSignalOnAdd) {
                locker.unlock();
                emit signalStreamsUpdated();
            }
        }
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
void CAutomate::addAction(IAction* action, bool emitSignal){
    QMutexLocker locker(&m_mutex);
    if(action){
        m_mapActions.insert(action->getName(), action);
        m_listActions.append(action);// en redondance avec m_mapActions pour ne pas casser l'API

        if (emitSignal) {
            locker.unlock();
            emit signalActionsUpdated();
        }
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

    locker.unlock();
    emit signalActionsUpdated();
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
            action = CActionFactory::build(QVariantMap(), this);
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
  //  qCDebug(COTAUTOMATE_LOG) << "Tick " << m_iClock;

    // TEST CODE (for graph and history)
//    getVariable(QStringLiteral("measure_cot"))->setValue(QVariant(m_iClock));
//    IVariable *phosphore = getVariable(QStringLiteral("phosphore"));
//    phosphore->setValue(m_iClock * 2);
    if ((m_iClock++ % 5) == 0) {
        IVariable *var= getVariable(QStringLiteral("var_measure_cot"));
        float tmp = rand() %5000;
        tmp = (tmp + 45000)/1000;
        var->setValue(tmp);

        var= getVariable(QStringLiteral("var_measure_cit"));
        tmp = rand() %5000;
        tmp = (tmp + 45000)/1000;
        var->setValue(tmp);

        var= getVariable(QStringLiteral("var_measure_npoc"));
        tmp = rand() %5000;
        tmp = (tmp + 45000)/1000;
        var->setValue(tmp);
    }
    emit signalUpdatePlotting();
//    if (m_iClock == 6) {
//        emit signalUpdateStateStream("stream_1", WATER_DEFAULT);
//    } else if (m_iClock == 10) {
//        emit signalUpdateStateStream("stream_1", ACTIVE);
//    }

//    // TEST CODE (for the alarms window)
//    if ((m_iClock % 3) == 0) {
//        IVariable *defectVar = getVariable(QStringLiteral("alarm_defaut_eau"));
//        defectVar->setValue(true);
//    }

//    // TEST CODE (for the status widget)
//    if (m_iClock > 5 && m_iClock < 50) {
//        if (m_iClock == 5)
//            emit signalUpdateStateAutomate(RUNNING);
//        else if (m_iClock == 49)
//            emit signalUpdateStateAutomate(GENERAL_DEFAULT);

//        emit signalUpdateCurrentStep(m_iClock / 2, "Step Name Goes Here");
//        if ((m_iClock % 20) == 0)
//            emit signalUpdateCurrentStream(m_iClock / 20, "Stream Name");
//    }
}


void CAutomate::removeVariableFromTree(IVariable* arg_var){
    foreach(CVariableStream* stream, m_listStreams){
        if(stream->getListVariables().contains(arg_var)){
            stream->removeVariable(arg_var);
        }
        foreach(IVariable* measure, stream->getListMeasures()){
            if(static_cast<CVariableMeasure *>(measure)->getListVariables().contains(arg_var)){
                static_cast<CVariableMeasure *>(measure)->removeVariable(arg_var);
            }
        }
    }
}

void CAutomate::changeVariableMeasure(IVariable* arg_var, CVariableMeasure* arg_dest_measure){
    removeVariableFromTree(arg_var);

    if(arg_dest_measure && !arg_dest_measure->getListVariables().contains(arg_var)){
        arg_dest_measure->addVariable(arg_var);
    }
}

CVariableStream *CAutomate::getMeasureStream(CVariableMeasure * arg_measure) const
{
    CVariableStream* returnStream = Q_NULLPTR;
    foreach(CVariableStream* stream, m_listStreams){
        if(stream->getListMeasures().contains(arg_measure)){
            returnStream = stream;
            break;
        }
    }

    return returnStream;
}

void CAutomate::changeCycleStream(ICycle* arg_cycle, CVariableStream* arg_dest_stream){
    foreach(CVariableStream* stream, m_listStreams){
        if(stream->getListCycles().contains(arg_cycle)){
            stream->removeCycle(arg_cycle->getName());
        }
    }

    if(arg_dest_stream && !arg_dest_stream->getListCycles().contains(arg_cycle)){
        arg_dest_stream->addCycle(arg_cycle);
    }

}

void CAutomate::changeVariableStream(IVariable* arg_var, CVariableStream* arg_dest_stream){
   removeVariableFromTree(arg_var);

    if(arg_dest_stream && !arg_dest_stream->getListVariables().contains(arg_var)){
        arg_dest_stream->addVariable(arg_var);
    }
}
CVariableMeasure* CAutomate::getVariableMeasure(IVariable* arg_var) const{
    CVariableMeasure* returnMeasure = Q_NULLPTR;
    foreach(CVariableStream* stream, m_listStreams){
        foreach(IVariable* measure, stream->getListMeasures()){
            if(static_cast<CVariableMeasure *>(measure)->getListVariables().contains(arg_var)){
                returnMeasure = static_cast<CVariableMeasure *>(measure);
                break;
            }
        }
    }
    return returnMeasure;
}
CVariableStream* CAutomate::getCycleStream(ICycle* arg_cycle) const{
    CVariableStream* returnStream = Q_NULLPTR;
    foreach(CVariableStream* stream, m_listStreams){
        if(stream->getListCycles().contains(arg_cycle)){
            returnStream = stream;
            break;
        }
    }

    return returnStream;
}
CVariableStream* CAutomate::getVariableStream(IVariable* arg_var) const{
    CVariableStream* returnStream = Q_NULLPTR;
    foreach(CVariableStream* stream, m_listStreams){
        if(stream->getListVariables().contains(arg_var)){
            returnStream = stream;
            break;
        }
    }

    return returnStream;
}
void CAutomate::requestPlayScheduler(){
    if(m_mapAlarmWhichStoppedScheduler.isEmpty()){
        m_scheduler->slotPlaySequenceMeasure();
        m_schedulerStoppedFromIHM = false;
    }
}

void CAutomate::requestStopScheduler(){
    m_schedulerStoppedFromIHM = true;
    if(m_mapAlarmWhichStoppedScheduler.isEmpty())
    this->stopScheduler();
}

void CAutomate::stopScheduler(){

        m_scheduler->slotRequestStopSequenceMesure();
}
void CAutomate::playNextSequenceMesure(){
    if(m_mapAlarmWhichStoppedScheduler.isEmpty() && !m_schedulerStoppedFromIHM)
        m_scheduler->slotRequestPlayNextSequenceMesure();
}

void CAutomate::requestStopFromNewAlarm(CVariableAlarm* arg_alarm){
    if(!m_mapAlarmWhichStoppedScheduler.contains(arg_alarm->getName())){
        m_mapAlarmWhichStoppedScheduler.insert(arg_alarm->getName(), arg_alarm);
        if(!m_schedulerStoppedFromIHM && m_mapAlarmWhichStoppedScheduler.count()==1){
            stopScheduler();
        }
    }
}

void CAutomate::restartFromCanceledAlarm(CVariableAlarm* arg_alarm){
    if(m_mapAlarmWhichStoppedScheduler.remove(arg_alarm->getName())
            && m_mapAlarmWhichStoppedScheduler.isEmpty()
            && !m_schedulerStoppedFromIHM){
        requestPlayScheduler();
    }

}

void CAutomate::pauseScheduler(){

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

void CAutomate::delVariable(IVariable *arg_var)
{
    // SERES_TODO: To be completed (COT-XX).
    // There is probably more to update, like in CSequencer etc.
    QMutexLocker locker(&m_mutex);
    bool modified = false;

    foreach ( CVariableStream *streamVar, m_listStreams) {

        foreach(IVariable *measureIvar, streamVar->getListMeasures()) {
            CVariableMeasure *measureVar = static_cast<CVariableMeasure *>(measureIvar);
            modified |= measureVar->removeVariable(arg_var);
        }

        modified |= streamVar->removeVariable(arg_var);
    }

    bool bUsed = false;
    foreach(IAction* action, m_listActions){
        if(action->variableUsed(arg_var)) bUsed = true;
    }

    if(!bUsed){
        IVariable *var = m_mapVariables.take(arg_var->getName());

        if (var) {
            modified |= true;
            var->deleteLater();
        }

    }

    locker.unlock();
    if (modified) {
        emit signalVariablesUpdated();
    }
    //gestion d'erreur si on ne peut pas la supprimer ? Checker sur l'IHM en premier avant d'essayer ?
}

void CAutomate::delCycle(ICycle *cycle)
{
    // SERES_TODO: To be completed (COT-58).
    // There is probably more to update, like in CSequencer etc.
    QMutexLocker locker(&m_mutex);

    CVariableStream *stream = cycle->getRelatedStream();

    if (stream) {
        stream->removeCycle(cycle->getName());
    }

    m_scheduler->removeCycleMeasure(cycle);
    m_scheduler->removeCycleMaintenance(cycle);
    m_scheduler->removeCycleAutonome(cycle);

    switch(cycle->getType()){
        case e_cycle_measure:
    case e_cycle_pause:
            delete m_listCycleMesures.take(cycle->getName());
            break;

        case e_cycle_maintenance :
            delete m_listCycleMaintenances.take(cycle->getName());
            break;


        case e_cycle_autonome:
            delete m_listlCycleAutonomes.take(cycle->getName());
            break;

//        case e_cycle_pause:
//            break;

        case e_cycle_all:
            Q_ASSERT(false);
            break;
    }
}

void CAutomate::delStream(CVariableStream *ivar)
{
    // SERES_TODO: To be completed
    QMutexLocker locker(&m_mutex);
    if(ivar){
        m_listStreams.removeAll(ivar);
        locker.unlock();
        emit signalStreamsUpdated();
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
    if(var && var->getType() != e_type_unknow)
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

    switch(static_cast<enumTypeCycle>(type)){
        case e_cycle_measure:
    case e_cycle_pause:
            return m_listCycleMesures.value(name, Q_NULLPTR);
        case e_cycle_maintenance :
            return m_listCycleMaintenances.value(name, Q_NULLPTR);
        case e_cycle_autonome:
            return m_listlCycleAutonomes.value(name, Q_NULLPTR);
//        case e_cycle_pause:
//            break;

        case e_cycle_all: {
            ICycle * cycle = m_listCycleMesures.value(name, Q_NULLPTR);

            if (!cycle) {
                cycle = m_listCycleMaintenances.value(name, Q_NULLPTR);
            }

            if (!cycle) {
                cycle = m_listlCycleAutonomes.value(name, Q_NULLPTR);
            }

            return cycle;
        }
    }

    return Q_NULLPTR;
}

CUnit *CAutomate::getUnit(const QString &name) const
{
    CUnit* unit = Q_NULLPTR;
    foreach (CUnit *u, m_listUnits) {
        if (u->getName() == name) {
            unit = u;
        }
    }

    if(!unit){
        foreach (CUnit *u, m_listUnits) {
            if (u->getName() == QStringLiteral("no_unit")) {
                unit = u;
            }
        }
        if(!unit){
            unit = new CUnit(QStringLiteral("no_unit"), QStringLiteral(""));
        }
    }
    return unit;
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

void CAutomate::setStateCycleMesure(eStateCycle arg_state){
    QMutexLocker locker(&m_mutex);
    m_stateCycleMesure = arg_state;
    switch(arg_state){
    case CYCLE_STATE_STOP:
        emit signalUpdateStateAutomate(STOPPED);
        break;
    case CYCLE_STATE_RUN:
        emit signalUpdateStateAutomate(RUNNING);
        break;
    default:
        break;
    }

}
void CAutomate::slotNewAlarm(CVariableAlarm* arg_alarm){
    switch(arg_alarm->getAlarmType()){
    case e_not_critical_error_skip_cycle_try_again:
        playNextSequenceMesure();
        break;
    case e_critical_error_stop_cycle:
        requestStopFromNewAlarm(arg_alarm);
        break;
    case e_warning_do_nothing:
    default:
        break;
    }

    //intérêt du display conf pour les alarms ?
    if(m_displayConf->getListForScreenAlarms().contains(arg_alarm)){
        emit signalNewAlarm(arg_alarm->getLabel());
    }
}
void CAutomate::slotAcquitedAlarm(CVariableAlarm* arg_alarm){

    //lors d'une reprise après un rétablissement d'un défaut
    switch(arg_alarm->getAlarmType()){
    case e_critical_error_stop_cycle:
        restartFromCanceledAlarm(arg_alarm);
        break;
    case e_not_critical_error_skip_cycle_try_again:
    case e_warning_do_nothing:
    default:
        break;
    }
    if(m_displayConf->getListForScreenAlarms().contains(arg_alarm)){
        emit signalRemoveAlarm(arg_alarm->getLabel());
    }
}
void CAutomate::slotStillInAlarm(CVariableAlarm* arg_alarm){
    switch(arg_alarm->getAlarmType()){

    case e_not_critical_error_skip_cycle_try_again:
        playNextSequenceMesure();
        break;
    case e_warning_do_nothing:
    case e_critical_error_stop_cycle:
    default:
        break;
    }
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
    emit signalVariableChanged(ivar->getName(), QDateTime::currentDateTime());
}

CDisplayConf* CAutomate::getDisplayConf()const{
    QMutexLocker locker(&m_mutex);
    return m_displayConf;
}

void CAutomate::informAboutCycleChanges(ICycle *cycle, const QVariantMap &oldData)
{
    Q_UNUSED(oldData);

    QMutexLocker locker(&m_mutex);

    // SERES_TODO: implement automate internal change handling.
    // There is probably more to update, like in CSequencer etc.
    // SERES_TODO: add api for changing a stream name (COT-52)
    const bool isNew = !getListCyclesPrivate().contains(cycle);

    if (isNew) {
        addCyclePrivate(cycle);
    }

    // Due to api depreciation, moving cycle to new stream is done previsouly.

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
        emit signalVariableChanged(variable->getName(), QDateTime::currentDateTime());
    }

    emit signalVariablesUpdated();
}

QString CAutomate::formatHistoryEntry(const QString &name, const QDateTime &dateTime)
{
    IVariable *ivar = getInstance()->getVariable(name);
    Q_ASSERT(ivar);
    return tr("%1: %2 updated to value %3")
            .arg(dateTime.toString())
            .arg(ivar->getLabel())
            .arg(ivar->toString());
}

void CAutomate::setDisplayConf(CDisplayConf* displayConf){
    QMutexLocker locker(&m_mutex);
    m_displayConf = displayConf;
}

void CAutomate::addLoggedVariable(const QString& arg_varName, bool arg_debug){
    IVariable* var = getVariable(arg_varName);
    if(arg_debug)
        m_listLoggedVarDebug.append(var);
    else
    {
        m_listLoggedVar.append(var);
        if(var && var->getType() != e_type_unknow && !m_debug)
            connect(var, SIGNAL(signalVariableChanged(IVariable*)), this, SLOT(slotLogVariable(IVariable*)));
    }
}



void CAutomate::slotSerializeAndSave(){
    qDebug() << "CAutomate::slotSerializeAndSave(){";
    QVariantMap mapSerialize;
    mapSerialize.insert(QStringLiteral("name"), QStringLiteral("TOC"));
    mapSerialize.insert(tr("en_US"), tr("TOC"));
    mapSerialize.insert(QStringLiteral("version"), QStringLiteral("0.0.1"));
    mapSerialize.insert(QStringLiteral("lang"), m_lang);

    //extensions
    {
        QVariantList listTmp;
        foreach(CModelExtensionCard* ext, m_mapExtCards){
            listTmp.append(ext->serialize());
        }
        mapSerialize.insert(QStringLiteral("extensions"), listTmp);
    }

    //units et convertion
    {
        QVariantList listTmp;
        QVariantList listTmp2;
        foreach(CUnit* unit, m_listUnits){
            listTmp.append(unit->serialize());
//            foreach(IConverter* converter, unit->getConverters()){
//                QVariantMap mapTmp = converter->serialize();
//                mapTmp.insert(QStringLiteral("source"), unit->getName());
//                listTmp2.append(mapTmp);
//            }
        }
        mapSerialize.insert(QStringLiteral("units"), listTmp);
    }
    //variables et binds
    {
        QVariantList listTmp;
        QVariantList listBinds;
        foreach(IVariable* var, m_mapVariables){
            listTmp.append(var->serialize());
            foreach(IVariable* bindedVar, var->getListOutBinds()){
                QVariantMap mapBind;
                mapBind.insert(QStringLiteral("source"), var->getName());
                mapBind.insert(QStringLiteral("target"), bindedVar->getName());
                listBinds.append(mapBind);
            }
        }
        mapSerialize.insert(QStringLiteral("variables"), listTmp);
        mapSerialize.insert(QStringLiteral("binds"), listBinds);
    }
    //Display
    {
        mapSerialize.insert(QStringLiteral("display"), m_displayConf->serialize());
    }

    //action
    {
        QVariantList listTmp;
        foreach(IAction* action, m_listActions){
            listTmp.append(action->serialize());
        }
        mapSerialize.insert(QStringLiteral("actions"), listTmp);
    }

    //cycles
    {
        QVariantList listTmp;
        foreach(ICycle* cycle, m_listCycleMesures){
            listTmp.append(cycle->serialize());
        }
        mapSerialize.insert(QStringLiteral("cycles"), listTmp);
    }

    //Scheduler measure
    {
        QStringList listTmp;
        foreach(ICycle* cycle, m_scheduler->getListSequenceCyclesMesures() ){
            listTmp.append(cycle->getName());
        }
        mapSerialize.insert(QStringLiteral("scheduler_measure"), listTmp);

    }

    //Scheduler autonome
    {
        QStringList listTmp;
        foreach(ICycle* cycle, m_scheduler->getListSequenceCyclesAutonomes() ){
            listTmp.append(cycle->getName());
        }
        mapSerialize.insert(QStringLiteral("scheduler_autonome"), listTmp);

    }

    //Scheduler maintenance
    {
        QStringList listTmp;
        foreach(ICycle* cycle, m_scheduler->getListCyclesMaintenances() ){
            listTmp.append(cycle->getName());
        }
        mapSerialize.insert(QStringLiteral("list_cycles_maintenances"), listTmp);

    }

    //streams
    {
        QVariantList listTmp;
        foreach(CVariableStream* stream, m_listStreams){   
            listTmp.append(stream->serialize());
        }
        mapSerialize.insert(QStringLiteral("streams"), listTmp);
    }

    //logs
    {
          QVariantList listTmp;
          foreach (IVariable* var, m_listLoggedVar) {
              listTmp.append(var->getName());
          }
          mapSerialize.insert(QStringLiteral("logs"), listTmp);
    }

    QJsonDocument doc = QJsonDocument::fromVariant(mapSerialize);
    QFile jsonFile(QString::fromLocal8Bit(JSON_DIRECTORY "/save.json"));

    if(jsonFile.exists()) jsonFile.remove();

    if (!jsonFile.open(QIODevice::ReadWrite)) {
        qCDebug(COTAUTOMATE_LOG) << "Couldn't open save file.";
    }
    jsonFile.write(doc.toJson());
    jsonFile.close();

#ifdef   Q_OS_UNIX
    QProcess process;
    process.start("sync");
    process.waitForFinished();
#endif
}

void CAutomate::slotLogVariable(IVariable* arg_var){
    QMutexLocker locker(&m_mutex);
    qDebug() << "slotLogVariable(arg)";
    QString dirPath = QString(LOG_SOURCE_DIRECTORY);
    QDir dir = QDir(dirPath);
    if(!dir.exists()){
        dir.mkdir(dirPath);
    }
    QString path = dirPath+ "/log_"+QDate::currentDate().toString(Qt::ISODate)+".txt";
    QFile data(path);
    if (data.open(QFile::Append)) {
        QTextStream out(&data);
        out << QDateTime::currentDateTime().toString(Qt::ISODate);
        QString tmp = QString::number(arg_var->toFloat(), 'f', 10);
        out << ";" << arg_var->getLabel() << ";" << tmp;
        // qDebug() << ";" << arg_var->getLabel() << ";" << tmp;
        out << endl;
    }else{
        qDebug() << "Can't open file";
    }
    data.close();

    if(m_countBeforeCheckLogFileToDelete++ > 3600){
        m_countBeforeCheckLogFileToDelete = 0;
        dir.setSorting(QDir::Time|QDir::Reversed);
        if(dir.entryList().count()> 60){ //2 mois de rétention
            int count = dir.entryList().count() -60;
            for(int i=0; i< count; ++i){
                QFile file(dirPath+ "/" + dir.entryList().at(i));
                file.remove();
            }
        }
    }
}

void CAutomate::slotLogVariable(){
    QMutexLocker locker(&m_mutex);
    QTimer::singleShot(1000, this, SLOT(slotLogVariable()));
    QString dirPath = QString(LOG_SOURCE_DIRECTORY);
    QDir dir = QDir(dirPath);
    if(!dir.exists()){
        dir.mkdir(dirPath);
    }
    QString path = dirPath+ "/log_debug_"+QDate::currentDate().toString(Qt::ISODate)+".txt";
    QFile data(path);
    if (data.open(QFile::Append)) {
        QTextStream out(&data);
        out << QDateTime::currentDateTime().toString(Qt::ISODate);
        foreach(IVariable* arg_var, m_listLoggedVarDebug){
            if(arg_var->getOrganType() == e_type_organ_input)
                (dynamic_cast<IVariableInput*>(arg_var))->readValue();
            QString tmp = QString::number(arg_var->toFloat(), 'f', 10);
            out << ";" << arg_var->getLabel() << ";" << tmp;
           // qDebug() << ";" << arg_var->getLabel() << ";" << tmp;
        }
        out << endl;
    }else{
        qDebug() << "Can't open file";
    }
    data.close();

    if(m_countBeforeCheckLogFileToDelete++ > 3600){
        m_countBeforeCheckLogFileToDelete = 0;
        dir.setSorting(QDir::Time|QDir::Reversed);
        if(dir.entryList().count()> 60){ //2 mois de rétention
            int count = dir.entryList().count() -60;
            for(int i=0; i< count; ++i){
                QFile file(dirPath+ "/" + dir.entryList().at(i));
                file.remove();
            }
        }
    }
}

void CAutomate::setLang(const QString& arg){
    m_lang = arg;
}

