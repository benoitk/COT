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
    m_bPlaySequenceMesure = false;
    m_bPlayMaintenance = false;
    m_bPlaySequenceAutonome = false;

    m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();

    m_cycleMeasureEnCours = 0;
    m_cycleMaintenanceEnCours = 0;
    m_cycleAutonomeEnCours = 0;

    connect(this, &CScheduler::signalGetReadyForPlayCycleMesure, this, &CScheduler::slotPlaySequenceMeasure);
}

CScheduler::~CScheduler()
{

}

void CScheduler::apendSequenceMeasureRunCycle(ICycle* arg_cycle, int arg_nbMesure){
    //CControlerCycle* ctrlCycle = new CControlerCycle(this, cycle);
    //this->apendSequenceMesureRunCycle(ctrlCycle, nbMesure);
    if(arg_cycle){
        while(arg_nbMesure>0){
            qCDebug(COTAUTOMATE_LOG) << "nbMesure " << arg_nbMesure;
            m_listSequenceCyclesMeasures.append(arg_cycle);
            arg_nbMesure--;
        }

        //m_listSequenceCycles << CyclePair(arg_cycle, arg_nbMesure);
    }
}

/*void CSequencer::apendSequenceMesureRunCycle(CControlerCycle* ctrlCycle, int nbMesur    e){
    while(nbMesure--<0){
        m_listSequenceCyclesMesure.append(ctrlCycle );
    }
}*/
void CScheduler::apendSequenceMeasurePause(int minute){
    CCyclePause* cyclePause = new CCyclePause(minute, this);
    //CControlerCycle* ctrlCycle = new CControlerCycle(this, cyclePause);
    m_listSequenceCyclesMeasures.append(cyclePause);
    //m_listSequenceCycles << CyclePair(cyclePause, minute);
}

void CScheduler::setSequenceMeasure(){
    qCDebug(COTAUTOMATE_LOG) << "void CSequencer::setSequenceMesure()";
    if(m_cycleMaintenanceEnCours){
        emit this->signalStopCycleMaintenance();
        // A revoir pour ne pas mettre de boucle bloquante
        //        while(m_cycleMaintenanceEnCours->isRunning()){
//            QThread::msleep(50);
//        }
        this->disconnectCycle(m_cycleMaintenanceEnCours);
    }

    this->disconnectCycle(m_cycleMeasureEnCours);


    if( m_itListSequenceCyclesMesures != m_listSequenceCyclesMeasures.end()){

        // SERES_TODO: Fix null pointers.
        m_cycleMeasureEnCours = (*m_itListSequenceCyclesMesures);
        if (!m_cycleMeasureEnCours) {
            qCDebug(COTAUTOMATE_LOG) << "m_cycleMesureEnCours ptr null";
            return;
        }
        qCDebug(COTAUTOMATE_LOG) << "Cycle : " << m_cycleMeasureEnCours->getName() << m_cycleMeasureEnCours->thread();
        //Si les signaux ne fonctionne pas, vérfier que le cycle à était déplacer dans un QThread à part(movethead)
        connect(this, &CScheduler::signalRunCycleMesure, m_cycleMeasureEnCours, &ICycle::slotRunCycle);//, Qt::DirectConnection);
        connect(this, &CScheduler::signalPauseCycleMesure, m_cycleMeasureEnCours, &ICycle::slotPauseCycle);
        connect(this, &CScheduler::signalUnPauseCycleMesure, m_cycleMeasureEnCours, &ICycle::slotUnPauseCycle); //en double avec play
        connect(this, &CScheduler::signalStopCycleMesure, m_cycleMeasureEnCours, &ICycle::slotStopCycle);
        connect(this, &CScheduler::signalGoToEndCycleMesure, m_cycleMeasureEnCours, &ICycle::slotGoToEndCycle);
        connect(this, &CScheduler::signalGetReadyForPlayNextCycleMesure, m_cycleMeasureEnCours, &ICycle::slotGetReadyForPlayNextCycle);
        connect(this, &CScheduler::signalGetReadyForPlayCycleMesure, m_cycleMeasureEnCours, &ICycle::slotGetReadyForPlayCycle);
        connect(m_cycleMeasureEnCours, &ICycle::signalRunning, this, &CScheduler::slotCycleMesureIsRunning);
        connect(m_cycleMeasureEnCours, &ICycle::signalStopped, this, &CScheduler::slotCycleMesureIsStopped);
        connect(m_cycleMeasureEnCours, &ICycle::signalPaused, this, &CScheduler::slotCycleMesureIsPaused);
        connect(m_cycleMeasureEnCours, &ICycle::signalReadyForPlayNextCycle, this, &CScheduler::slotPlayNextSequenceMeasure);
        disconnect(this, &CScheduler::signalGetReadyForPlayCycleMesure, this, &CScheduler::slotPlaySequenceMeasure);
        connect(m_cycleMeasureEnCours, &ICycle::signalReadyForPlayCycle, this, &CScheduler::slotPlaySequenceMeasure);
    }
    else qCDebug(COTAUTOMATE_LOG) << "liste m_listSequenceCyclesMesures vide :" << m_listSequenceCyclesMeasures;
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
void CScheduler::slotPlayNextSequenceMeasure(){
    if(m_cycleMeasureEnCours){
        if( (++m_itListSequenceCyclesMesures) == m_listSequenceCyclesMeasures.end()){
            m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
        }
        this->setSequenceMeasure();
        emit signalRunCycleMesure();
    }
}
//Fin Play Next  cycle Mesure

//Stop cycle Mesure
void CScheduler::slotRequestStopSequenceMesure(){
   emit signalStopCycleMesure();
}
void CScheduler::slotCycleMesureIsStopped(bool withCriticalError){
    if(m_cycleMeasureEnCours){
        this->disconnectCycle(m_cycleMeasureEnCours);
    }
    CAutomate::getInstance()->setStateCycleMesure(CAutomate::CYCLE_STATE_STOP, withCriticalError);
}
//Fin Stop cycle Mesure

//Pasue cycle Mesure
void CScheduler::slotRequestPauseSequenceMesure(){
    emit signalPauseCycleMesure();
}
//Fin Pause cycle Mesure

//Unpause  cycle Mesure
void CScheduler::slotRequestUnPauseSequenceMesure(){
    emit signalUnPauseCycleMesure();
}
//Fin Unpause cycle Mesure

//Play  cycle Mesure(démarre ou redémarre du début de la séquence)
void CScheduler::slotRequestPlaySequenceMesure(){
    qCDebug(COTAUTOMATE_LOG) << "CSequencer::slotRequestPlaySequenceMesure";
    emit signalGetReadyForPlayCycleMesure();
}
void CScheduler::slotPlaySequenceMeasure(){
    qCDebug(COTAUTOMATE_LOG) << "CSequencer::slotPlaySequenceMesure()" << m_cycleMeasureEnCours;
    if(!m_cycleMeasureEnCours || (m_cycleMeasureEnCours && !m_cycleMeasureEnCours->isRunning()))
    {

        m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
        this->setSequenceMeasure();
        emit signalRunCycleMesure();
        CAutomate::getInstance()->setStateCycleMesure(CAutomate::CYCLE_STATE_RUN);
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
void  CScheduler::setListSequenceCyclesMesures(QList<ICycle *> listCycles){
    // remove null pointers.
    auto itFirst = std::remove_if(listCycles.begin(), listCycles.end(), [](ICycle *cycle) { return cycle == Q_NULLPTR; });
    listCycles.erase(itFirst, listCycles.end());

    m_listSequenceCyclesMeasures.swap(listCycles);
    m_itListSequenceCyclesMesures = m_listSequenceCyclesMeasures.begin();
}
void  CScheduler::setListSequenceCyclesAutonomes(QList<ICycle *> listCycles){
    m_listSequenceCyclesAutonomes.swap(listCycles);
}
void  CScheduler::setListCyclesMaintenances(QList<ICycle *> listCycles){
    m_listCyclesMaintenances.swap(listCycles);
}
void CScheduler::addCycle(const CScheduler::CyclePair &pair)
{
//    m_listSequenceCycles << pair;
//    emit signalUpdated();
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
void CScheduler::replaceCycleAt(int index, const CScheduler::CyclePair &pair)
{
//    if (index >= m_listSequenceCycles.count()) {
//        return;
//    }

//    m_listSequenceCycles[index] = pair;
//    emit signalUpdated();
}
void CScheduler::replaceCycleMeasureAt(int arg_index, ICycle* arg_cycle){
    if(arg_cycle && arg_cycle->getType() != CYCLE_INVALID && arg_index > 0 && arg_index < m_listSequenceCyclesMeasures.size()){
        m_listSequenceCyclesMeasures.replace(arg_index, arg_cycle);
    }
}
void CScheduler::replaceCycleAutonomeAt(int arg_index, ICycle* arg_cycle){
    if(arg_cycle && arg_cycle->getType() != CYCLE_INVALID && arg_index > 0 && arg_index < m_listSequenceCyclesAutonomes.size()){
        m_listSequenceCyclesAutonomes.replace(arg_index, arg_cycle);
    }
}
void CScheduler::removeAt(int index)
{
//    if (index >= m_listSequenceCycles.count()) {
//        return;
//    }

//    m_listSequenceCycles.removeAt(index);
//    emit signalUpdated();
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
        }
    }
}

void CScheduler::removeCycleMaintenance(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listCyclesMaintenances.begin(); itListCycles != m_listCyclesMaintenances.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles))
            itListCycles = m_listCyclesMaintenances.erase(itListCycles);
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

CScheduler::CyclePair CScheduler::getCycleAt(int index) const
{
//    return m_listSequenceCyclesMesures.value(index, CyclePair(Q_NULLPTR, -1));
     return CyclePair(Q_NULLPTR, -1);
}

QList<CScheduler::CyclePair> CScheduler::getCycles() const
{
    QList<CScheduler::CyclePair> list; //a virer avec toutes les listes<CyclePair>
    return list;
//    return m_listSequenceCycles;
}
ICycle*  CScheduler::getCycleMeasureAt(int arg_index) const{
    return m_listSequenceCyclesMeasures.value(arg_index, Q_NULLPTR);
}
ICycle*  CScheduler::getCycleAutonomeAt(int arg_index) const{
    return m_listSequenceCyclesAutonomes.value(arg_index, Q_NULLPTR);
}
