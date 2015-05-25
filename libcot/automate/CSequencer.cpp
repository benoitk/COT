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
    m_bPlaySequenceMaintenance = false;
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
void CSequencer::setSequenceMesure(QList<ICycle *> list){
    m_listSequenceCyclesMesures.swap(list);
}
void CSequencer::apendSequenceMesureRunCycle(ICycle* cycle, int nbMesure){
    //CControlerCycle* ctrlCycle = new CControlerCycle(this, cycle);
    //this->apendSequenceMesureRunCycle(ctrlCycle, nbMesure);
    while(nbMesure>0){
        qCDebug(COTAUTOMATE_LOG) << "nbMesure " << nbMesure;
        m_listSequenceCyclesMesures.append(cycle);
        nbMesure--;
    }

    m_listSequenceCycles << CyclePair(cycle, nbMesure);
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

        m_cycleMesureEnCours = (*m_itListSequenceCyclesMesures);

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
void CSequencer::playSequenceMaintenance(int id_cycle){

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

void CSequencer::slotPlayNextSequenceMaintenance(){
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

void CSequencer::initListSequenceCyclesMesures(QList<ICycle *> list){
    m_listSequenceCyclesMesures.swap(list);
}
QList<ICycle*>  CSequencer::getListSequenceCyclesMesures(){
    return m_listSequenceCyclesMesures;
}
void  CSequencer::setListSequenceCyclesMesures(QList<ICycle *> listCycles){
    m_listSequenceCyclesMesures.swap(listCycles);
}

void CSequencer::addCycle(const CSequencer::CyclePair &pair)
{
    m_listSequenceCycles << pair;
    emit signalUpdated();
}

void CSequencer::replaceCycleAt(int index, const CSequencer::CyclePair &pair)
{
    if (index >= m_listSequenceCycles.count()) {
        return;
    }

    m_listSequenceCycles[index] = pair;
    emit signalUpdated();
}

void CSequencer::removeAt(int index)
{
    if (index >= m_listSequenceCycles.count()) {
        return;
    }

    m_listSequenceCycles.removeAt(index);
    emit signalUpdated();
}

void CSequencer::removeCycleMeasure(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listSequenceCyclesMesures.begin(); itListCycles != m_listSequenceCyclesMesures.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles))
            itListCycles = m_listSequenceCyclesMesures.erase(itListCycles);
    }
}

void CSequencer::removeCycleMaintenance(ICycle * arg_cycle){
    QList<ICycle*>::iterator itListCycles;
    for(itListCycles = m_listSequenceCyclesMaintenances.begin(); itListCycles != m_listSequenceCyclesMaintenances.end(); ++itListCycles){
        if(arg_cycle == (*itListCycles))
            itListCycles = m_listSequenceCyclesMaintenances.erase(itListCycles);
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
