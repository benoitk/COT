#include "CSequencer.h"
#include "CCyclePause.h"
#include "CControlerCycle.h"
#include "qthread.h"
#include "cotautomate_debug.h"

CSequencer* CSequencer::singleton = 0;
CSequencer::CSequencer()
    : QObject()
{
    m_bPlaySequenceMesure = false;
    m_bPlayMaintenance = false;
    m_bPlaySequenceAutonome = false;

    m_itListSequenceCyclesMesures = m_listSequenceCyclesMesures.begin();

    m_cycleMesureEnCours = 0;
    m_cycleMaintenanceEnCours = 0;
    m_cycleAutonomeEnCours = 0;

    connect(this, &CSequencer::signalGetReadyForPlayCycleMesure, this, &CSequencer::slotPlaySequenceMesure);
}

CSequencer::~CSequencer()
{

}

void CSequencer::apendSequenceMesureRunCycle(ICycle* arg_cycle, int arg_nbMesure){
    //CControlerCycle* ctrlCycle = new CControlerCycle(this, cycle);
    //this->apendSequenceMesureRunCycle(ctrlCycle, nbMesure);
    if(arg_cycle){
        while(arg_nbMesure>0){
            qCDebug(COTAUTOMATE_LOG) << "nbMesure " << arg_nbMesure;
            m_listSequenceCyclesMesures.append(arg_cycle);
            arg_nbMesure--;
        }

        m_listSequenceCycles << CyclePair(arg_cycle, arg_nbMesure);
    }
}

/*void CSequencer::apendSequenceMesureRunCycle(CControlerCycle* ctrlCycle, int nbMesur    e){
    while(nbMesure--<0){
        m_listSequenceCyclesMesure.append(ctrlCycle );
    }
}*/
void CSequencer::apendSequenceMesurePause(int minute){
    CCyclePause* cyclePause = new CCyclePause(minute, this);
    //CControlerCycle* ctrlCycle = new CControlerCycle(this, cyclePause);
    m_listSequenceCyclesMesures.append(cyclePause);
    m_listSequenceCycles << CyclePair(cyclePause, minute);
}

void CSequencer::setSequenceMesure(){
    qCDebug(COTAUTOMATE_LOG) << "void CSequencer::setSequenceMesure()";
    if(m_cycleMaintenanceEnCours){
        this->signalStopCycleMaintenance();
        while(m_cycleMaintenanceEnCours->isRunning()){
            QThread::msleep(50);
        }
        this->disconnectCycle(m_cycleMaintenanceEnCours);
    }

    this->disconnectCycle(m_cycleMesureEnCours);


    if( m_itListSequenceCyclesMesures != m_listSequenceCyclesMesures.end()){

        // SERES_TODO: Fix null pointers.
        m_cycleMesureEnCours = qobject_cast<ICycle*>(*m_itListSequenceCyclesMesures);
        if (!m_cycleMesureEnCours) {
            return;
        }

        //Si les signaux ne fonctionne pas, vérfier que le cycle à était déplacer dans un QThread à part(movethead)
        connect(this, &CSequencer::signalRunCycleMesure, m_cycleMesureEnCours, &ICycle::slotRunCycle);//, Qt::DirectConnection);
        connect(this, &CSequencer::signalPauseCycleMesure, m_cycleMesureEnCours, &ICycle::slotPauseCycle);
        connect(this, &CSequencer::signalUnPauseCycleMesure, m_cycleMesureEnCours, &ICycle::slotUnPauseCycle); //en double avec play
        connect(this, &CSequencer::signalStopCycleMesure, m_cycleMesureEnCours, &ICycle::slotStopCycle);
        connect(this, &CSequencer::signalGoToEndCycleMesure, m_cycleMesureEnCours, &ICycle::slotGoToEndCycle);
        connect(this, &CSequencer::signalGetReadyForPlayNextCycleMesure, m_cycleMesureEnCours, &ICycle::slotGetReadyForPlayNextCycle);
        connect(this, &CSequencer::signalGetReadyForPlayCycleMesure, m_cycleMesureEnCours, &ICycle::slotGetReadyForPlayCycle);
        connect(m_cycleMesureEnCours, &ICycle::signalRunning, this, &CSequencer::slotCycleMesureIsRunning);
        connect(m_cycleMesureEnCours, &ICycle::signalStopped, this, &CSequencer::slotCycleMesureIsStopped);
        connect(m_cycleMesureEnCours, &ICycle::signalPaused, this, &CSequencer::slotCycleMesureIsPaused);
        connect(m_cycleMesureEnCours, &ICycle::signalReadyForPlayNextCycle, this, &CSequencer::slotPlayNextSequenceMesure);
        disconnect(this, &CSequencer::signalGetReadyForPlayCycleMesure, this, &CSequencer::slotPlaySequenceMesure);
        connect(m_cycleMesureEnCours, &ICycle::signalReadyForPlayCycle, this, &CSequencer::slotPlaySequenceMesure);
    }

}
void CSequencer::disconnectCycle(ICycle* cycle){
    if(cycle){
        disconnect(this, 0, cycle, 0);
        disconnect(cycle, 0, this, 0);
        connect(this, &CSequencer::signalGetReadyForPlayCycleMesure, this, &CSequencer::slotPlaySequenceMesure);
    }
}
void CSequencer::playMaintenance(int id_cycle){

}
void CSequencer::playSequenceAutonome(){

}
//Play Next cycle Mesure
void CSequencer::slotRequestPlayNextSequenceMesure(){
    this->signalGetReadyForPlayNextCycleMesure();
}
void CSequencer::slotPlayNextSequenceMesure(){
    if(m_cycleMesureEnCours){
        if( (++m_itListSequenceCyclesMesures) == m_listSequenceCyclesMesures.end()){
            m_itListSequenceCyclesMesures = m_listSequenceCyclesMesures.begin();
        }
        this->setSequenceMesure();
        emit signalRunCycleMesure();
    }
}
//Fin Play Next  cycle Mesure

//Stop cycle Mesure
void CSequencer::slotRequestStopSequenceMesure(){
    this->signalStopCycleMesure();
}
void CSequencer::slotCycleMesureIsStopped(){
    if(m_cycleMesureEnCours){
        this->disconnectCycle(m_cycleMesureEnCours);
    }
}
//Fin Stop cycle Mesure

//Pasue cycle Mesure
void CSequencer::slotRequestPauseSequenceMesure(){
    this->signalPauseCycleMesure();
}
//Fin Pause cycle Mesure

//Unpause  cycle Mesure
void CSequencer::slotRequestUnPauseSequenceMesure(){
    this->signalUnPauseCycleMesure();
}
//Fin Unpause cycle Mesure

//Play  cycle Mesure(démarre ou redémarre du début de la séquence)
void CSequencer::slotRequestPlaySequenceMesure(){
    emit signalGetReadyForPlayCycleMesure();
}
void CSequencer::slotPlaySequenceMesure(){
    qCDebug(COTAUTOMATE_LOG) << "CSequencer::slotPlaySequenceMesure()" << m_cycleMesureEnCours;
    if(!m_cycleMesureEnCours || (m_cycleMesureEnCours && !m_cycleMesureEnCours->isRunning()))
    {
        m_itListSequenceCyclesMesures = m_listSequenceCyclesMesures.begin();
        this->setSequenceMesure();
        emit signalRunCycleMesure();
    }
    qCDebug(COTAUTOMATE_LOG) << "FIN CSequencer::slotPlaySequenceMesure()";

}
//fin play cycle Mesure

void CSequencer::slotPlayNextMaintenance(){
}
void CSequencer::slotPlayNextSequenceAutonome(){
}

void CSequencer::slotCycleMesureIsRunning(){}

void CSequencer::slotCycleMesureIsPaused(){}

CSequencer* CSequencer::getInstance(){
    if(!singleton)
        singleton = new CSequencer();
    return singleton;
}

QList<ICycle*>  CSequencer::getListSequenceCyclesMesures(){
    return m_listSequenceCyclesMesures;
}
QList<ICycle*>  CSequencer::getListSequenceCyclesAutonomes(){
    return m_listSequenceCyclesAutonomes;
}
QList<ICycle*>  CSequencer::getListCyclesMaintenances(){
    return m_listCyclesMaintenances;
}
void  CSequencer::setListSequenceCyclesMesures(QList<ICycle *> listCycles){
    QList<ICycle *>::iterator itList;
    //vire les pointeurs vides potentiel
    for(itList=listCycles.begin(); itList != listCycles.end(); ++itList){
        if (!qobject_cast<ICycle*>(*itList)) {
            itList = listCycles.erase(itList);
        }
    }
    m_listSequenceCyclesMesures.swap(listCycles);
    m_itListSequenceCyclesMesures = m_listSequenceCyclesMesures.begin();
}
void  CSequencer::setListSequenceCyclesAutonomes(QList<ICycle *> listCycles){
    m_listSequenceCyclesAutonomes.swap(listCycles);
}
void  CSequencer::setListCyclesMaintenances(QList<ICycle *> listCycles){
    m_listCyclesMaintenances.swap(listCycles);
}
void CSequencer::addCycle(const CSequencer::CyclePair &pair)
{
    m_listSequenceCycles << pair;
    emit signalUpdated();
}
void CSequencer::addCycleMeasure(int arg_index, ICycle* arg_cycle){
    if(arg_cycle){
        if(arg_index < 0) arg_index = 0;
        else if(arg_index > m_listSequenceCyclesMesures.size()) arg_index = m_listSequenceCyclesMesures.size();
        m_listSequenceCyclesMesures.insert(arg_index, arg_cycle);
    }
}
void CSequencer::addCycleAutonome(int arg_index, ICycle* arg_cycle){
    if(arg_cycle){
        if(arg_index < 0) arg_index = 0;
        else if(arg_index > m_listSequenceCyclesAutonomes.size()) arg_index = m_listSequenceCyclesAutonomes.size();
        m_listSequenceCyclesAutonomes.insert(arg_index, arg_cycle);
    }
}
void CSequencer::addCycleAutonome(ICycle* arg_cycle){
    if(arg_cycle){
        int index = m_listSequenceCyclesAutonomes.size();
        this->addCycleAutonome(index, arg_cycle);
    }
}
void CSequencer::addCycleMaintenance(ICycle* arg_cycle){
    if(arg_cycle){
        m_listSequenceCyclesAutonomes.append(arg_cycle);
    }
}
void CSequencer::replaceCycleAt(int index, const CSequencer::CyclePair &pair)
{
    if (index >= m_listSequenceCycles.count()) {
        return;
    }

    m_listSequenceCycles[index] = pair;
    emit signalUpdated();
}
void CSequencer::replaceCycleMeasureAt(int arg_index, ICycle* arg_cycle){
    if(arg_cycle && arg_cycle->getType() != CYCLE_INVALID && arg_index > 0 && arg_index < m_listSequenceCyclesMesures.size()){
        m_listSequenceCyclesMesures.replace(arg_index, arg_cycle);
    }
}
void CSequencer::replaceCycleAutonomeAt(int arg_index, ICycle* arg_cycle){
    if(arg_cycle && arg_cycle->getType() != CYCLE_INVALID && arg_index > 0 && arg_index < m_listSequenceCyclesAutonomes.size()){
        m_listSequenceCyclesAutonomes.replace(arg_index, arg_cycle);
    }
}
void CSequencer::removeAt(int index)
{
    if (index >= m_listSequenceCycles.count()) {
        return;
    }

    m_listSequenceCycles.removeAt(index);
    emit signalUpdated();
}
void CSequencer::removeCycleMeasureAt(int arg_index){
    if(arg_index >= 0 && arg_index < m_listSequenceCyclesMesures.size()){
        m_listSequenceCyclesMesures.removeAt(arg_index);
        m_itListSequenceCyclesMesures = m_listSequenceCyclesMesures.begin();
    }
}
void CSequencer::removeCycleAutonomeAt(int arg_index){
    if(arg_index >= 0 && arg_index < m_listSequenceCyclesAutonomes.size()){
        m_listSequenceCyclesAutonomes.removeAt(arg_index);
    }
}
void CSequencer::removeCycleMeasure(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listSequenceCyclesMesures.begin(); itListCycles != m_listSequenceCyclesMesures.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles)){
            itListCycles = m_listSequenceCyclesMesures.erase(itListCycles);
            m_itListSequenceCyclesMesures = m_listSequenceCyclesMesures.begin();
        }
    }
}

void CSequencer::removeCycleMaintenance(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listCyclesMaintenances.begin(); itListCycles != m_listCyclesMaintenances.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles))
            itListCycles = m_listCyclesMaintenances.erase(itListCycles);
    }
}

void CSequencer::removeCycleAutonome(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listSequenceCyclesAutonomes.begin(); itListCycles != m_listSequenceCyclesAutonomes.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles))
            itListCycles = m_listSequenceCyclesAutonomes.erase(itListCycles);
    }
}

CSequencer::CyclePair CSequencer::getCycleAt(int index) const
{
    return m_listSequenceCycles.value(index, CyclePair(Q_NULLPTR, -1));
}

QList<CSequencer::CyclePair> CSequencer::getCycles() const
{
    return m_listSequenceCycles;
}
ICycle*  CSequencer::getCycleMeasureAt(int arg_index) const{
    return m_listSequenceCyclesMesures.value(arg_index, Q_NULLPTR);
}
ICycle*  CSequencer::getCycleAutonomeAt(int arg_index) const{
    return m_listSequenceCyclesAutonomes.value(arg_index, Q_NULLPTR);
}
