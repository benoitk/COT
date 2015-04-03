#include "CSequenceur.h"
#include "CCyclePause.h"
#include "CControlerCycle.h"
#include "qthread.h"
#include "qdebug.h"

CSequenceur* CSequenceur::singleton = 0;
CSequenceur::CSequenceur()
	: QObject()
{
	m_bPlaySequenceMesure = false;
	m_bPlaySequenceMaintenance = false;
	m_bPlaySequenceAutonome = false;

	m_itListSequenceCyclesMesure = m_listSequenceCyclesMesure.begin();

	m_cycleMesureEnCours = 0;
	m_cycleMaintenanceEnCours = 0;
	m_cycleAutonomeEnCours = 0;

	connect(this, &CSequenceur::signalGetReadyForPlayCycleMesure, this, &CSequenceur::slotPlaySequenceMesure);
}

CSequenceur::~CSequenceur()
{

}
void CSequenceur::setSequenceMesure(QList<ICycle*> list){
	m_listSequenceCyclesMesure.swap(list);
}
void CSequenceur::apendSequenceMesureRunCycle(ICycle* cycle, int nbMesure){
	//CControlerCycle* ctrlCycle = new CControlerCycle(this, cycle);
	//this->apendSequenceMesureRunCycle(ctrlCycle, nbMesure);
	while(nbMesure>0){
		qDebug() << "nbMesure " << nbMesure;
		m_listSequenceCyclesMesure.append(cycle);
		nbMesure--;
	}
}

/*void CSequenceur::apendSequenceMesureRunCycle(CControlerCycle* ctrlCycle, int nbMesur	e){
	while(nbMesure--<0){
		m_listSequenceCyclesMesure.append(ctrlCycle );
	}
}*/
void CSequenceur::apendSequenceMesurePause(int minute){
	CCyclePause* cyclePause = new CCyclePause(this, minute);
	//CControlerCycle* ctrlCycle = new CControlerCycle(this, cyclePause);
	m_listSequenceCyclesMesure.append(cyclePause);
}

void CSequenceur::setSequenceMesure(){
	if(m_cycleMaintenanceEnCours){
		this->signalStopCycleMaintenance();
		while(m_cycleMaintenanceEnCours->isRunning()){
			QThread::msleep(50);
		}
		this->disconnectCycle(m_cycleMaintenanceEnCours);
	}

	this->disconnectCycle(m_cycleMesureEnCours);	
	

	if( m_itListSequenceCyclesMesure != m_listSequenceCyclesMesure.end()){

		m_cycleMesureEnCours = (*m_itListSequenceCyclesMesure);

		//Si les signaux ne fonctionne pas, vérfier que le cycle à était déplacer dans un QThread à part(movethead)
		connect(this, &CSequenceur::signalRunCycleMesure, m_cycleMesureEnCours, &ICycle::slotRunCycle);//, Qt::DirectConnection);
		connect(this, &CSequenceur::signalPauseCycleMesure, m_cycleMesureEnCours, &ICycle::slotPauseCycle);
		connect(this, &CSequenceur::signalUnPauseCycleMesure, m_cycleMesureEnCours, &ICycle::slotUnPauseCycle); //en double avec play
		connect(this, &CSequenceur::signalStopCycleMesure, m_cycleMesureEnCours, &ICycle::slotStopCycle);
		connect(this, &CSequenceur::signalGoToEndCycleMesure, m_cycleMesureEnCours, &ICycle::slotGoToEndCycle);
		connect(this, &CSequenceur::signalGetReadyForPlayNextCycleMesure, m_cycleMesureEnCours, &ICycle::slotGetReadyForPlayNextCycle);
		connect(this, &CSequenceur::signalGetReadyForPlayCycleMesure, m_cycleMesureEnCours, &ICycle::slotGetReadyForPlayCycle);
		connect(m_cycleMesureEnCours, &ICycle::signalImRunned, this, &CSequenceur::slotCycleMesureIsRunning);
		connect(m_cycleMesureEnCours, &ICycle::signalImStopped, this, &CSequenceur::slotCycleMesureIsStopped);
		connect(m_cycleMesureEnCours, &ICycle::signalImPaused, this, &CSequenceur::slotCycleMesureIsPaused);
		connect(m_cycleMesureEnCours, &ICycle::signalReadyForPlayNextCycle, this, &CSequenceur::slotPlayNextSequenceMesure);
		disconnect(this, &CSequenceur::signalGetReadyForPlayCycleMesure, this, &CSequenceur::slotPlaySequenceMesure);
		connect(m_cycleMesureEnCours, &ICycle::signalReadyForPlayCycle, this, &CSequenceur::slotPlaySequenceMesure);
	}

}
void CSequenceur::disconnectCycle(ICycle* cycle){
	if(cycle){
		disconnect(this, 0, cycle, 0);
		disconnect(cycle, 0, this, 0);
		connect(this, &CSequenceur::signalGetReadyForPlayCycleMesure, this, &CSequenceur::slotPlaySequenceMesure);
	}
}
void CSequenceur::playSequenceMaintenance(int id_cycle){
	
}
void CSequenceur::playSequenceAutonome(){
	
}
//Play Next cycle Mesure
void CSequenceur::slotRequestPlayNextSequenceMesure(){
	this->signalGetReadyForPlayNextCycleMesure();
}
void CSequenceur::slotPlayNextSequenceMesure(){	
	if(m_cycleMesureEnCours){
		if( (++m_itListSequenceCyclesMesure) == m_listSequenceCyclesMesure.end()){
			m_itListSequenceCyclesMesure = m_listSequenceCyclesMesure.begin();

		}
		this->setSequenceMesure();
		emit signalRunCycleMesure();
	}
}
//Fin Play Next  cycle Mesure

//Stop cycle Mesure
void CSequenceur::slotRequestStopSequenceMesure(){
	this->signalStopCycleMesure();
}
void CSequenceur::slotCycleMesureIsStopped(){
	if(m_cycleMesureEnCours){
		this->disconnectCycle(m_cycleMesureEnCours);
	}
}
//Fin Stop cycle Mesure

//Pasue cycle Mesure
void CSequenceur::slotRequestPauseSequenceMesure(){
	this->signalPauseCycleMesure();
}
//Fin Pause cycle Mesure

//Unpause  cycle Mesure
void CSequenceur::slotRequestUnPauseSequenceMesure(){
	this->signalUnPauseCycleMesure();
}
//Fin Unpause cycle Mesure

//Play  cycle Mesure(démarre ou redémarre du début de la séquence)
void CSequenceur::slotRequestPlaySequenceMesure(){
	emit signalGetReadyForPlayCycleMesure();
}
void CSequenceur::slotPlaySequenceMesure(){
	if(!m_cycleMesureEnCours || (m_cycleMesureEnCours && !m_cycleMesureEnCours->isRunning()))
	{
		m_itListSequenceCyclesMesure = m_listSequenceCyclesMesure.begin();
		this->setSequenceMesure();
		emit signalRunCycleMesure();
	}

}
//fin play cycle Mesure

void CSequenceur::slotPlayNextSequenceMaintenance(){
}
void CSequenceur::slotPlayNextSequenceAutonome(){
}

void CSequenceur::slotCycleMesureIsRunning(){}

void CSequenceur::slotCycleMesureIsPaused(){}

CSequenceur* CSequenceur::getInstance(){
	if(!singleton)
		singleton = new CSequenceur();
	return singleton;
}

void CSequenceur::initListSequenceCyclesMesure(QList<ICycle*> list){
	m_listSequenceCyclesMesure.swap(list);
}
