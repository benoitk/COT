#include "CCycleMesure.h"
#include "cotautomate_debug.h"
#include "qtimer.h"
#include "qlist.h"
#include "CLinkAction.h"
#include "CActionFactory.h"
#include "IAction.h"
#include "CStep.h"
#include "CAutomate.h"
#include "CVariableStream.h"

CCycleMesure::CCycleMesure(QObject *parent)
    : ICycle(parent)
{

}

CCycleMesure::CCycleMesure(const QVariantMap &mapCycle, QObject *parent): ICycle(mapCycle, parent) {
    //qCDebug(COTAUTOMATE_LOG) << "constructor CCycleMesure(const QVariantMap &mapCycle) mapCycle:" << mapCycle;
     qDebug() << "moveThread CCycleMesure";
    this->moveToThread(&m_thread);
    m_thread.start();

}
QVariantMap CCycleMesure::serialise(){

    QVariantMap mapSerialise = ICycle::serialise();
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("measure"));

    return mapSerialise;
}


CCycleMesure::~CCycleMesure()
{
    //TODO supprésion des pas qui fait planter
//    delete m_stepStop;
//    foreach (CStep* step, m_listSteps) {
//        if(step)
//            delete step;
//    }
}
eTypeCycle CCycleMesure::getType()const{
    return CYCLE_MESURE;
}
void CCycleMesure::slotStepFinished(CStep* arg_step){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMesure::slotStepFinished(CStep* arg_step) ";
    QMutexLocker lock(&m_mutex);
    bool criticalErrorOnPreviousStep = false;
    if(arg_step)
        disconnect(arg_step,&CStep::signalStepFinished,this,&CCycleMesure::slotStepFinished);
    if(m_itListStepsPasEnCours != m_listSteps.end()){
        criticalErrorOnPreviousStep = (*m_itListStepsPasEnCours)->finishedWithcriticalError();
        m_itListStepsPasEnCours++;
    }

    if(m_itListStepsPasEnCours == m_listSteps.end()) { //fin du cycle

        m_isRunning = false; //a changer avec m_itListStepsPasEnCours = m_listSteps.end pour savoir si un cycle est en cours ou pas
        if(!criticalErrorOnPreviousStep)
            emit signalReadyForPlayNextCycle();
        else
            emit signalStopped(criticalErrorOnPreviousStep);
    }else{
        if((m_itListStepsPasEnCours != m_listSteps.begin())){
            m_timeout = (*m_itListStepsPasEnCours)->getNumStep()*1000 - (*m_itListStepsPasEnCours.operator-(1))->getNumStep()*1000;
        }else
            m_timeout = (*m_itListStepsPasEnCours)->getNumStep()*1000;
        qCDebug(COTAUTOMATE_LOG) << "time out before next step : " << m_timeout;
        QTimer::singleShot(m_timeout, this, SLOT(slotExecNextStep()));
    }

}

void CCycleMesure::slotExecNextStep(){
    QMutexLocker lock(&m_mutex);
    if(m_itListStepsPasEnCours != m_listSteps.end()){
        qCDebug(COTAUTOMATE_LOG) << "CCycleMesure slotExecNextStep. Setp : " << (*m_itListStepsPasEnCours)->getLabel() << " step : " << (*m_itListStepsPasEnCours)->getNumStep();
        //si true dois attendre la fin du pas pour aller au suivant
        connect((*m_itListStepsPasEnCours),&CStep::signalStepFinished,this,&CCycleMesure::slotStepFinished);
        (*m_itListStepsPasEnCours)->execStep();


    }

}
void CCycleMesure::slotRunCycle(){
    QMutexLocker lock(&m_mutex);
    qCDebug(COTAUTOMATE_LOG) << "CCycleMesure::slotRunCycle()";

    if(!m_listSteps.isEmpty()){
        m_isRunning = true;
        m_itListStepsPasEnCours = m_listSteps.begin();
        m_timeout = m_listSteps.first()->getNumStep() * 1000; //step en seconde
        updateCycleInfosCountStep();
        qCDebug(COTAUTOMATE_LOG) << "time out before next step : " << m_timeout;
        QTimer::singleShot(m_timeout, this, SLOT(slotExecNextStep()));
    }
    else
        qCDebug(COTAUTOMATE_LOG) << "m_listSteps.isEmpty()";

    qCDebug(COTAUTOMATE_LOG) << "FIN CCycleMesure::slotRunCycle()";

}
void CCycleMesure::slotPauseCycle(){

}

void CCycleMesure::slotStopCycle(){
    QMutexLocker lock(&m_mutex);

//   if(m_itListStepsPasEnCours != m_listSteps.end()){
//        (*m_itListStepsPasEnCours)->abortStep();
//    }
    foreach(CStep* step, m_listSteps){
        step->abortStep();
    }

    if(m_stepStop)
        m_stepStop->execStep();

    if(m_itListStepsPasEnCours != m_listSteps.end()){
        emit signalStopped((*m_itListStepsPasEnCours)->finishedWithcriticalError());
        m_itListStepsPasEnCours = m_listSteps.end();
    }else
        emit signalStopped(false);


    m_isRunning = false;

    qCDebug(COTAUTOMATE_LOG) << "Fin slotStopCycle";
}




void CCycleMesure::slotUnPauseCycle(){}
void CCycleMesure::slotStopEndCycle(){}
void CCycleMesure::slotGoToEndCycle(){}
void CCycleMesure::slotGoToStepCycle(int numStep){}
void CCycleMesure::slotGetReadyForPlayNextCycle(){}
void CCycleMesure::slotGetReadyForPlayCycle(){}

