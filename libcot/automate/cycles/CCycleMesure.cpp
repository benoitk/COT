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
    : ICycle(parent), m_mutex(QMutex::Recursive)
{

}

CCycleMesure::CCycleMesure(const QVariantMap &mapCycle): ICycle(), m_mutex(QMutex::Recursive) {
    //qCDebug(COTAUTOMATE_LOG) << "constructor CCycleMesure(const QVariantMap &mapCycle) mapCycle:" << mapCycle;
    if(mapCycle.contains(QStringLiteral("name")))
        m_name = mapCycle[QStringLiteral("name")].toString();
    else
        m_name = QStringLiteral("Action not named");
    m_label = mapCycle[tr("fr_FR")].toString();

    const QVariantList listSteps = mapCycle[QStringLiteral("steps")].toList();
    foreach(const QVariant &varStep, listSteps){
        const QVariantMap mapStep = varStep.toMap();
        CStep* step = new CStep(this, mapStep);
        m_listSteps.append(step);
    }

    this->moveToThread(&m_thread);
    m_thread.start();

}
QVariantMap CCycleMesure::serialise(){
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


CCycleMesure::~CCycleMesure()
{
    delete m_stepStop;
    foreach (CStep* step, m_listSteps) {
        delete step;
    }
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

        m_isRunning = false; //a changer avec m_itListStepsPasEnCours == m_listSteps.end pour savoir si un cycle est en cours ou pas
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
        emit CAutomate::getInstance()->signalUpdateCountStep(m_listSteps.last()->getNumStep());
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

   if(m_itListStepsPasEnCours != m_listSteps.end()){
        (*m_itListStepsPasEnCours)->abortStep(); 
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

QString CCycleMesure::getRelatedStreamName()const{
    return m_streamName;
}
CVariableStream* CCycleMesure::getRelatedStream()const{
    return CAutomate::getInstance()->getStream(m_streamName);
}
void CCycleMesure::setRelatedStreamName(const QString &name)
{
    m_streamName = name;
}
QList<CStep*> CCycleMesure::getListSteps()const{
    return m_listSteps;
}
CStep* CCycleMesure::getStepStop()const{
    return m_stepStop;
}

void CCycleMesure::setListSteps(const QList<CStep *> &steps, CStep *stopStep)
{
    qDeleteAll(m_listSteps);
    delete m_stepStop;
    m_listSteps = steps;
    m_stepStop = stopStep;
}

int CCycleMesure::getCurrentStepIndex() const
{
    return -1;
}
QString CCycleMesure::getLabel()const{ return m_label;}
void CCycleMesure::setLbl(const QString &lbl){ m_label = lbl;}

void CCycleMesure::addAction(float arg_step, IAction* action){
    QMutexLocker lock(&m_mutex);

    QList<CStep*>::iterator itListStep;
    for(itListStep=m_listSteps.begin(); itListStep != m_listSteps.end(); ++itListStep){
        if((*itListStep)->getNumStep() == arg_step){
            (*itListStep)->addAction(action);
            itListStep = m_listSteps.end();
        }
    }
}
//enlève toutes les référence à arg_action
void CCycleMesure::removeAction(IAction* arg_action){
    QMutexLocker lock(&m_mutex);

    QList<CStep*>::iterator itListStep;
    for(itListStep=m_listSteps.begin(); itListStep != m_listSteps.end(); ++itListStep){
        (*itListStep)->removeAction(arg_action);
    }
}

void CCycleMesure::setType(eTypeCycle){}

QString CCycleMesure::getName()const{
    return m_name;

}
void CCycleMesure::setName(const QString &name){
    m_name = name;

}


void CCycleMesure::slotUnPauseCycle(){}

void CCycleMesure::slotStopEndCycle(){}
void CCycleMesure::slotGoToEndCycle(){}
void CCycleMesure::slotGoToStepCycle(int numStep){}
void CCycleMesure::slotGetReadyForPlayNextCycle(){}
void CCycleMesure::slotGetReadyForPlayCycle(){}

