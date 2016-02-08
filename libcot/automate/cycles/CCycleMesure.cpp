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
    //m_timer = Q_NULLPTR;
     qDebug() << "moveThread CCycleMesure";
    this->moveToThread(&m_thread);
    m_thread.start();



}
QVariantMap CCycleMesure::serialize(){

    QVariantMap mapSerialise = ICycle::serialize();
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
enumTypeCycle CCycleMesure::getType()const{
    return e_cycle_measure;
}
void CCycleMesure::slotStepFinished(CStep* arg_step){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMesure::slotStepFinished(CStep* arg_step) ";
    QMutexLocker lock(&m_mutex);

    if(arg_step)
        disconnect(arg_step,&CStep::signalStepFinished,this,&CCycleMesure::slotStepFinished);
    if(m_itListStepsPasEnCours != m_listSteps.end()){
        m_itListStepsPasEnCours++;
    }

    if(m_itListStepsPasEnCours == m_listSteps.end()) { //fin du cycle
        m_isRunning = false; //a changer avec m_itListStepsPasEnCours = m_listSteps.end pour savoir si un cycle est en cours ou pas

        emit CAutomate::getInstance()->signalUpdatePlotting();
        slotGetReadyForPlayNextCycle();
    }else{
        if((m_itListStepsPasEnCours != m_listSteps.begin())){
            m_timeout = (*m_itListStepsPasEnCours)->getNumStep()*1000 - (*m_itListStepsPasEnCours.operator-(1))->getNumStep()*1000;
        }else
            m_timeout = (*m_itListStepsPasEnCours)->getNumStep()*1000;
        qCDebug(COTAUTOMATE_LOG) << "time out before next step : " << m_timeout;
        QThread* currentThread = QThread::currentThread();
        if(m_mapTimerSchedulerStep.contains(currentThread)){
            m_mapTimerSchedulerStep.value(currentThread)->start(m_timeout);
        }
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

    QThread* currentThread = QThread::currentThread();
    if(!m_mapTimerSchedulerStep.contains(currentThread)){
        QTimer* timer = new QTimer();
        m_mapTimerSchedulerStep.insert(currentThread, timer);
        timer->setSingleShot(true);
        connect(timer, &QTimer::timeout, this, &CCycleMesure::slotExecNextStep);
    }
    if(!m_mapTimerInfoNumStep.contains(currentThread)){
        QTimer* timer = new QTimer();
        m_mapTimerInfoNumStep.insert(currentThread, timer);
        m_numStepInfo =0;
        connect(timer, &QTimer::timeout, this, &ICycle::slotUpdateCycleInfosNumStep);
        timer->start(100);
    }else{
        m_mapTimerInfoNumStep.value(currentThread)->start();
    }
    qCDebug(COTAUTOMATE_LOG) << "CCycleMesure::slotRunCycle()";

    if(!m_listSteps.isEmpty()){
        m_isRunning = true;
        m_itListStepsPasEnCours = m_listSteps.begin();
        m_timeout = m_listSteps.first()->getNumStep() * 1000; //step en seconde
        updateCycleInfosCountStep();
        qCDebug(COTAUTOMATE_LOG) << "time out before next step : " << m_timeout;
        m_mapTimerSchedulerStep.value(currentThread)->start(m_timeout);
    }
    else
        qCDebug(COTAUTOMATE_LOG) << "m_listSteps.isEmpty()";

    qCDebug(COTAUTOMATE_LOG) << "FIN CCycleMesure::slotRunCycle()";

}
void CCycleMesure::slotPauseCycle(){

}

void CCycleMesure::slotStopCycle(){
    QMutexLocker lock(&m_mutex);

    if(m_itListStepsPasEnCours != m_listSteps.end()){
        abortCycle();
        if(m_stepStop)
            m_stepStop->execStep();
    }

    m_isRunning = false;

    qCDebug(COTAUTOMATE_LOG) << "Fin slotStopCycle";
    lock.unlock();
    emit signalStopped(this);
}

void CCycleMesure::slotGetReadyForPlayNextCycle(){
    abortCycle();
    emit signalReadyForPlayNextCycle(this);
}


void CCycleMesure::slotUnPauseCycle(){}
void CCycleMesure::slotStopEndCycle(){}
void CCycleMesure::slotGoToEndCycle(){}
void CCycleMesure::slotGoToStepCycle(int numStep){}

void CCycleMesure::slotGetReadyForPlayCycle(){}

