#include "CScheduler.h"
#include "CCyclePause.h"
#include "CControlerCycle.h"
#include "qthread.h"
#include "cotautomate_debug.h"
#include "CAutomate.h"
#include <algorithm>

CScheduler* CScheduler::singleton = 0;
CScheduler::CScheduler()
    : QObject()
{

    m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();

    m_cycleEnCours = Q_NULLPTR;
    m_haveToStopEndCycle = false;

    connect(this, &CScheduler::signalGetReadyForPlayCycleMesure, this, &CScheduler::slotPlaySequenceMeasure);

}

CScheduler::~CScheduler()
{

}

void CScheduler::apendSequenceMeasureRunCycle(ICycle* arg_cycle, int arg_nbMesure){  
    if(arg_cycle){
        while(arg_nbMesure>0){
            qCDebug(COTAUTOMATE_LOG) << "nbMesure " << arg_nbMesure;
            m_listSequenceCyclesMeasures.append(arg_cycle);
            arg_nbMesure--;
        }
    }
}

void CScheduler::apendSequenceMeasurePause(int minute){
    CCyclePause* cyclePause = new CCyclePause(minute, this); 
    m_listSequenceCyclesMeasures.append(cyclePause);
}

//pas de séquence pour les cycles autonomes, il s'éxécute tous d'un coup et se déroule en roue libre
void CScheduler::slotStartAllCyleAutonome(){
    foreach(ICycle* cycle, m_listSequenceCyclesAutonomes){
        connect(this, &CScheduler::signalRunCycleAutonome, cycle, &ICycle::slotRunCycle);
    }
    emit signalRunCycleAutonome();
}

QString CScheduler::getCycleInProgressName(){
    if(m_cycleEnCours)
        return m_cycleEnCours->getLabel();
    else
        return tr("No cycle");
}

void CScheduler::setSequence(bool isMaintenance){
    qCDebug(COTAUTOMATE_LOG) << "void CSequencer::setSequenceMesure()";

    if (!m_cycleEnCours) {
        qCDebug(COTAUTOMATE_LOG) << "m_cycleMesureEnCours ptr null";
        return;
    }
    qCDebug(COTAUTOMATE_LOG) << "Cycle : " << m_cycleEnCours->getName() << m_cycleEnCours->thread();
    //Si les signaux ne fonctionne pas, vérfier que le cycle à était déplacer dans un QThread à part(movethead)
    connect(this, &CScheduler::signalRunCycle, m_cycleEnCours, &ICycle::slotRunCycle);//, Qt::DirectConnection);
    connect(this, &CScheduler::signalPauseCycle, m_cycleEnCours, &ICycle::slotPauseCycle);
    connect(this, &CScheduler::signalUnPauseCycle, m_cycleEnCours,  &ICycle::slotUnPauseCycle); //en double avec play
    connect(this, &CScheduler::signalStopCycle, m_cycleEnCours, &ICycle::slotStopCycle);
    connect(this, &CScheduler::signalGoToEndCycleMesure, m_cycleEnCours, &ICycle::slotGoToEndCycle);
    connect(this, &CScheduler::signalGetReadyForPlayNextCycleMesure, m_cycleEnCours, &ICycle::slotGetReadyForPlayNextCycle);
    connect(this, &CScheduler::signalGetReadyForPlayCycleMesure, m_cycleEnCours, &ICycle::slotGetReadyForPlayCycle);
    connect(m_cycleEnCours, &ICycle::signalRunning, this, &CScheduler::slotCycleMesureIsRunning);
    connect(m_cycleEnCours, &ICycle::signalStopped, this, &CScheduler::slotCycleIsStopped);
    connect(m_cycleEnCours, &ICycle::signalPaused, this, &CScheduler::slotCycleMesureIsPaused);

    if(!isMaintenance)
        connect(m_cycleEnCours, &ICycle::signalReadyForPlayNextCycle, this, &CScheduler::slotPlayNextSequenceMeasure);
    else
        connect(m_cycleEnCours, &ICycle::signalReadyForPlayNextCycle, this, &CScheduler::slotCycleIsStopped);
    disconnect(this, &CScheduler::signalGetReadyForPlayCycleMesure, this, &CScheduler::slotPlaySequenceMeasure);

    qCDebug(COTAUTOMATE_LOG) << "FIN void CSequencer::setSequenceMesure()";
}
void CScheduler::disconnectCycle(ICycle* cycle){
    if(cycle){
        disconnect(this, 0, cycle, 0);
        disconnect(cycle, 0, this, 0);
        connect(this, &CScheduler::signalGetReadyForPlayCycleMesure, this, &CScheduler::slotPlaySequenceMeasure);
    }
}
void CScheduler::playMaintenance(int id_cycle){

}
void CScheduler::playSequenceAutonome(){

}
//Play Next cycle Mesure
void CScheduler::slotRequestPlayNextSequenceMesure(){
    emit signalGetReadyForPlayNextCycleMesure();
}
ISequenceMaintenanceAuto* CScheduler::haveToPlaySequenceMaintenanceAuto(){
    ISequenceMaintenanceAuto* returnedSeq = Q_NULLPTR;
    foreach (ISequenceMaintenanceAuto* seq, m_listSequenceCyclesMaintenancesAuto) {
        if(seq->haveToBeRun()){
            returnedSeq = seq;
            break;
        }
    }
    return returnedSeq;
}

void CScheduler::slotPlayNextSequenceMeasure(){
    if(!m_haveToStopEndCycle){
        if(m_cycleEnCours){
            this->disconnectCycle(m_cycleEnCours);
        }
        ISequenceMaintenanceAuto* seq = Q_NULLPTR;
        if(seq = haveToPlaySequenceMaintenanceAuto()){
            m_cycleEnCours = seq->getCycle();
        }
        else if( (++m_itListSequenceCyclesMesures) == m_listSequenceCyclesMeasures.end()){
            m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
            m_cycleEnCours = (*m_itListSequenceCyclesMesures);
        }
        else{
            m_cycleEnCours = (*m_itListSequenceCyclesMesures);
        }
        this->setSequence();

        CAutomate::getInstance()->setStateScheduler(CAutomate::CYCLE_STATE_RUN);
        emit signalRunCycle();
    }
    else{
        m_haveToStopEndCycle = false;
        m_cycleEnCours->slotStopCycle();
    }
}
//Fin Play Next  cycle Mesure

//Stop cycle Mesure
void CScheduler::slotRequestStopSequence(){
    if(m_cycleEnCours && m_cycleEnCours->isRunning())
        emit signalStopCycle();
}
void  CScheduler::slotRequestStopEndCycleSequence(){
    if(m_cycleEnCours && m_cycleEnCours->isRunning()){
        m_haveToStopEndCycle = true;
        CAutomate::getInstance()->setStateScheduler(CAutomate::CYCLE_STATE_STOP_END_CYCLE);
    }
}
void  CScheduler::slotRequestCancelStopSequenceEndCycle(){
    m_haveToStopEndCycle = false;
    if(m_cycleEnCours && m_cycleEnCours->isRunning()){
        CAutomate::getInstance()->setStateScheduler(CAutomate::CYCLE_STATE_RUN);
    }
}

bool CScheduler::isCyclesRunning(){
    return m_cycleEnCours->isRunning();
}

void CScheduler::slotCycleIsStopped(){
    if(m_cycleEnCours){
        this->disconnectCycle(m_cycleEnCours);
    }
    m_itListSequenceCyclesMesures = m_listCyclesMaintenances.begin();
    foreach (ISequenceMaintenanceAuto* sequence, m_listSequenceCyclesMaintenancesAuto) {
        sequence->reset();
    }
    emit signalCycleIsStopped(m_cycleEnCours->getName());
    CAutomate::getInstance()->setStateScheduler(CAutomate::CYCLE_STATE_STOP);
}

//Fin Stop cycle Mesure

//Pasue cycle Mesure
void CScheduler::slotRequestPauseSequenceMesure(){
    emit signalPauseCycle();
}
//Fin Pause cycle Mesure

//Unpause  cycle Mesure
void CScheduler::slotRequestUnPauseSequenceMesure(){
    emit signalUnPauseCycle();
}
//Fin Unpause cycle Mesure

//Play  cycle Mesure(démarre ou redémarre du début de la séquence)
void CScheduler::slotRequestPlaySequenceMesure(){
    qCDebug(COTAUTOMATE_LOG) << "CSequencer::slotRequestPlaySequenceMesure";
    emit signalGetReadyForPlayCycleMesure();
}
void CScheduler::slotPlaySequenceMeasure(){
    qCDebug(COTAUTOMATE_LOG) << "CSequencer::slotPlaySequenceMesure()" ;
    if(        (!m_cycleEnCours && !m_listSequenceCyclesMeasures.isEmpty())
            || (m_cycleEnCours && !m_cycleEnCours->isRunning() ))
    {

        m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
        this->slotPlayNextSequenceMeasure();

    }
    qCDebug(COTAUTOMATE_LOG) << "FIN CSequencer::slotPlaySequenceMesure()";

}
//fin play cycle Mesure

void CScheduler::slotPlayNextMaintenance(){
}
void CScheduler::slotPlayNextSequenceAutonome(){
}

void CScheduler::slotCycleMesureIsRunning(){}

void CScheduler::slotCycleMesureIsPaused(){}

CScheduler* CScheduler::getInstance(){
    if(!singleton)
        singleton = new CScheduler();
    return singleton;
}

QList<ICycle*>  CScheduler::getListSequenceCyclesMesures(){
    return m_listSequenceCyclesMeasures;
}
QList<ICycle*>  CScheduler::getListSequenceCyclesAutonomes(){
    return m_listSequenceCyclesAutonomes;
}
QList<ICycle*>  CScheduler::getListCyclesMaintenances(){
    return m_listCyclesMaintenances;
}
void  CScheduler::setListSequenceCyclesMesures(QList<ICycle *> listCycles, bool emitSignal){
    // remove null pointers.
    auto itFirst = std::remove_if(listCycles.begin(), listCycles.end(), [](ICycle *cycle) { return cycle == Q_NULLPTR; });
    listCycles.erase(itFirst, listCycles.end());

    m_listSequenceCyclesMeasures.swap(listCycles);
    m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();

    if (emitSignal) {
        emit signalUpdated();
    }
}
void  CScheduler::setListSequenceCyclesAutonomes(QList<ICycle *> listCycles){
    m_listSequenceCyclesAutonomes.swap(listCycles);
}
void  CScheduler::setListCyclesMaintenances(QList<ICycle *> listCycles){
    m_listCyclesMaintenances.swap(listCycles);
}

void CScheduler::addCycleMeasure(int arg_index, ICycle* arg_cycle){
    if(arg_cycle){
        if(arg_index < 0) arg_index = 0;
        else if(arg_index > m_listSequenceCyclesMeasures.size()) arg_index = m_listSequenceCyclesMeasures.size();
        m_listSequenceCyclesMeasures.insert(arg_index, arg_cycle);
    }
}
void CScheduler::addCycleMeasure(ICycle* arg_cycle){
    if(arg_cycle){
        m_listSequenceCyclesMeasures.append(arg_cycle);
        emit signalUpdated();
    }
}
void CScheduler::addCycleAutonome(int arg_index, ICycle* arg_cycle){
    if(arg_cycle){
        if(arg_index < 0) arg_index = 0;
        else if(arg_index > m_listSequenceCyclesAutonomes.size()) arg_index = m_listSequenceCyclesAutonomes.size();
        m_listSequenceCyclesAutonomes.insert(arg_index, arg_cycle);
    }
}
void CScheduler::addCycleAutonome(ICycle* arg_cycle){
    if(arg_cycle){
        int index = m_listSequenceCyclesAutonomes.size();
        this->addCycleAutonome(index, arg_cycle);
    }
}
void CScheduler::addCycleMaintenance(ICycle* arg_cycle){
    if(arg_cycle){
        m_listCyclesMaintenances.append(arg_cycle);
    }
}
void CScheduler::addCycleMaintenanceAuto(ISequenceMaintenanceAuto* arg_sequence){
    if(arg_sequence){
        m_listSequenceCyclesMaintenancesAuto.append(arg_sequence);
    }
}
QList<ISequenceMaintenanceAuto*> CScheduler::getListCycleMaintenanceAuto(){
    return m_listSequenceCyclesMaintenancesAuto;
}

void CScheduler::replaceCycleMeasureAt(int arg_index, ICycle* arg_cycle){
    if(arg_cycle && arg_cycle->getType() != e_cycle_invalid && arg_index > 0 && arg_index < m_listSequenceCyclesMeasures.size()){
        m_listSequenceCyclesMeasures.replace(arg_index, arg_cycle);
    }
}
void CScheduler::replaceCycleAutonomeAt(int arg_index, ICycle* arg_cycle){
    if(arg_cycle && arg_cycle->getType() != e_cycle_invalid && arg_index > 0 && arg_index < m_listSequenceCyclesAutonomes.size()){
        m_listSequenceCyclesAutonomes.replace(arg_index, arg_cycle);
    }
}

void CScheduler::removeCycleMeasureAt(int arg_index){
    if(arg_index >= 0 && arg_index < m_listSequenceCyclesMeasures.size()){
        m_listSequenceCyclesMeasures.removeAt(arg_index);
        m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
    }
}
void CScheduler::removeCycleAutonomeAt(int arg_index){
    if(arg_index >= 0 && arg_index < m_listSequenceCyclesAutonomes.size()){
        m_listSequenceCyclesAutonomes.removeAt(arg_index);
    }
}
void CScheduler::removeCycleMeasure(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listSequenceCyclesMeasures.begin(); itListCycles != m_listSequenceCyclesMeasures.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles)){
            itListCycles = m_listSequenceCyclesMeasures.erase(itListCycles); 
            m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
            if(itListCycles== m_listSequenceCyclesMeasures.end()) break;
        }
    }
}

void CScheduler::removeCycleMaintenance(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listCyclesMaintenances.begin(); itListCycles != m_listCyclesMaintenances.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles)){
            itListCycles = m_listCyclesMaintenances.erase(itListCycles);
            if(itListCycles == m_listCyclesMaintenances.end()) break;
        }

    }
}

void CScheduler::removeCycleAutonome(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listSequenceCyclesAutonomes.begin(); itListCycles != m_listSequenceCyclesAutonomes.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles))
            itListCycles = m_listSequenceCyclesAutonomes.erase(itListCycles);
        if(itListCycles == m_listSequenceCyclesAutonomes.end()) break;
    }
}

ICycle*  CScheduler::getCycleMeasureAt(int arg_index) const{
    return m_listSequenceCyclesMeasures.value(arg_index, Q_NULLPTR);
}
ICycle*  CScheduler::getCycleAutonomeAt(int arg_index) const{
    return m_listSequenceCyclesAutonomes.value(arg_index, Q_NULLPTR);
}

void CScheduler::slotPlayMaintenance(const QString& arg_cycleName){
    ICycle* cycle = CAutomate::getInstance()->getCycle(arg_cycleName);
    if(m_cycleEnCours){
        this->disconnectCycle(m_cycleEnCours);
    }
    if(cycle && cycle->getType() != e_cycle_invalid){
        m_cycleEnCours = cycle;
        setSequence(true);
        CAutomate::getInstance()->setStateScheduler(CAutomate::CYCLE_STATE_RUN);
        emit signalRunCycle();
    }
}


//DEFINITION SEQUENCE MAINTENANCE
ISequenceMaintenanceAuto::ISequenceMaintenanceAuto(const QVariantMap& arg_map,  QObject *parent):QObject(parent){
    m_cycle = CAutomate::getInstance()->getCycle(arg_map.value("cycle_name").toString());
}
ICycle* ISequenceMaintenanceAuto::getCycle(){
    return m_cycle;
}
CSequenceMaintenanceAutoEveryNCycles::CSequenceMaintenanceAutoEveryNCycles(const QVariantMap& arg_map,  QObject *parent):
    ISequenceMaintenanceAuto(arg_map, parent){
    m_nbCycle = CAutomate::getInstance()->getVariable(arg_map.value(QStringLiteral("nb_cycles")).toString());
    m_cpt = 0;
}

QVariantMap CSequenceMaintenanceAutoEveryNCycles::serialize(){
    QVariantMap mapSequence;

    mapSequence.insert(QStringLiteral("cycle_name"), m_cycle->getName());
    mapSequence.insert(QStringLiteral("sequence_type"), QStringLiteral("n_cycles"));
    mapSequence.insert(QStringLiteral("nb_cycles"), m_nbCycle->getName());

    return mapSequence;
}

bool CSequenceMaintenanceAutoEveryNCycles::haveToBeRun(){
    bool bHaveToBeRun = false;
    if(m_nbCycle->toInt() != 0 && ++m_cpt > m_nbCycle->toInt()){
        m_cpt = 0;
        bHaveToBeRun = true;
    }

    return bHaveToBeRun;
}
void CSequenceMaintenanceAutoEveryNCycles::reset(){
    m_cpt = 0;
}

CSequenceMaintenanceAutoUnknow::CSequenceMaintenanceAutoUnknow(const QVariantMap& arg_map,  QObject *parent):
    ISequenceMaintenanceAuto(arg_map,  parent){}
bool CSequenceMaintenanceAutoUnknow::haveToBeRun(){  return false; }
void CSequenceMaintenanceAutoUnknow::reset(){  }
QVariantMap CSequenceMaintenanceAutoUnknow::serialize(){
    QVariantMap mapSequence;
    return mapSequence;
}

ISequenceMaintenanceAuto* CSequenceMaintenanceFactory::build(const QVariantMap& arg_map,  QObject *parent){
    ISequenceMaintenanceAuto* sequence = Q_NULLPTR;
    const QString type = arg_map.value(QStringLiteral("sequence_type")).toString();
    if(type == QStringLiteral("n_cycles")){
        sequence = new CSequenceMaintenanceAutoEveryNCycles(arg_map,parent);
    }
    else{
        sequence = new CSequenceMaintenanceAutoUnknow(arg_map,parent);
        qCDebug(COTAUTOMATE_LOG) << "Classe sequence INCONNUE :" << type;
    }

    return sequence;
}
//FIN SEQUENCE MAINTENANCE
