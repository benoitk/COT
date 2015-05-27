#include "CCycleMaintenance.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "CAutomate.h"
#include "CVariableStream.h"
CCycleMaintenance::CCycleMaintenance(QObject *parent)
    : ICycle(parent)
{

}
CCycleMaintenance::CCycleMaintenance(eTypeCycle typeCycle, QObject* parent): ICycle(parent){
    m_typeCycle = typeCycle;
}
CCycleMaintenance::~CCycleMaintenance()
{
    delete m_stepStop;
    foreach (CStep* step, m_listSteps) {
        delete step;
    }
}
QVariantMap CCycleMaintenance::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("measure"));

    QVariantList listSteps;
    foreach(CStep* step, m_listSteps){
        listSteps.append(step->serialise());
    }
    mapSerialise.insert(QStringLiteral("steps"), listSteps);
    mapSerialise.insert(QStringLiteral("related_stream_name"), getRelatedStreamName());
    return mapSerialise;
}
//enlève toutes les référence à arg_action
void CCycleMaintenance::removeAction(IAction* arg_action){
    QList<CStep*>::iterator itListStep;
    for(itListStep=m_listSteps.begin(); itListStep != m_listSteps.end(); ++itListStep){
        (*itListStep)->removeAction(arg_action);
    }
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
QString CCycleMaintenance::getLabel()const{ return m_label;}
void CCycleMaintenance::setLbl(const QString &lbl){ m_label = lbl;}
void CCycleMaintenance::addAction(float arg_step, IAction* action){
    //TODO ajouter un mutex
    QList<CStep*>::iterator itListStep;
    for(itListStep=m_listSteps.begin(); itListStep != m_listSteps.end(); ++itListStep){
        if((*itListStep)->getNumStep() == arg_step){
            (*itListStep)->addAction(action);
            itListStep = m_listSteps.end();
        }
    }
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
CVariableStream* CCycleMaintenance::getRelatedStream()const{
    return CAutomate::getInstance()->getStream(m_streamName);
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

void CCycleMaintenance::setListSteps(const QList<CStep *> &steps, CStep *stopStep)
{
    qDeleteAll(m_listSteps);
    delete m_stepStop;
    m_listSteps = steps;
    m_stepStop = stopStep;
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
