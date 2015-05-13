#include "CCycleMaintenance.h"

#include "cotautomate_debug.h"
CCycleMaintenance::CCycleMaintenance(QObject *parent)
    : ICycle(parent)
{

}
CCycleMaintenance::CCycleMaintenance(eTypeCycle typeCycle, QObject* parent): ICycle(parent){
    m_typeCycle = typeCycle;
}
CCycleMaintenance::~CCycleMaintenance()
{

}
eTypeCycle CCycleMaintenance::getType()const{
    return CYCLE_MAINTENANCE;
}
void CCycleMaintenance::slotRunCycle(){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMaintenance::slotRunCycle()";
    
}
void CCycleMaintenance::slotPauseCycle(){
    
}
void CCycleMaintenance::slotStopCycle(){
}
QString CCycleMaintenance::getLbl()const{ return m_label;}
void CCycleMaintenance::setLbl(const QString &lbl){ m_label = lbl;}
void CCycleMaintenance::addAction(int arg_step, IAction* action){
    
}
void CCycleMaintenance::setType(eTypeCycle){

}
QString CCycleMaintenance::getName()const{
    return m_name;

}
void CCycleMaintenance::setName(const QString &name){
    m_name = name;

}

QString CCycleMaintenance::getRelatedStreamName()const{
    return m_streamName;
}

void CCycleMaintenance::setRelatedStreamName(const QString &name)
{
    m_streamName = name;
}
QList<CStep*> CCycleMaintenance::getListSteps()const{
    return m_listSteps;
}
CStep* CCycleMaintenance::getStepStop()const{
    return m_stepStop;
}

int CCycleMaintenance::getCurrentStepIndex() const
{
    return -1;
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
