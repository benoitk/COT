#include "CCycleMaintenance.h"

#include "qdebug.h"
CCycleMaintenance::CCycleMaintenance(QObject *parent)
	: ICycle(parent)
{

}
CCycleMaintenance::CCycleMaintenance(QObject* parent, eTypeCycle typeCycle): ICycle(parent){
	m_typeCycle = typeCycle;
}
CCycleMaintenance::~CCycleMaintenance()
{

}
eTypeCycle CCycleMaintenance::getType()const{
	return CYCLE_MAINTENANCE;
}
void CCycleMaintenance::slotRunCycle(){
	qDebug() << "CCycleMaintenance::slotRunCycle()";
	
}
void CCycleMaintenance::slotPauseCycle(){
	
}
void CCycleMaintenance::slotStopCycle(){
}
QString CCycleMaintenance::getLbl()const{ return m_label;}
void CCycleMaintenance::setLbl(QString lbl){ m_label = lbl;}
void CCycleMaintenance::addAction(IAction* action){
	
}
void CCycleMaintenance::setType(eTypeCycle){

}
QString CCycleMaintenance::getName()const{
	return m_name;

}
void CCycleMaintenance::setName(QString name){
	m_name = name;

}

bool CCycleMaintenance::isRunning(){return true;}
bool CCycleMaintenance::isPaused(){return true;}
void CCycleMaintenance::slotUnPauseCycle(){}
void CCycleMaintenance::slotStopEndCycle(){}
void CCycleMaintenance::slotGoToEndCycle(){}
void CCycleMaintenance::slotGoToStepCycle(int numStep){}
void CCycleMaintenance::slotGetReadyForPlayNextCycle(){}
void CCycleMaintenance::slotGetReadyForPlayCycle(){}
void CCycleMaintenance::slotExecNextStep(){}
