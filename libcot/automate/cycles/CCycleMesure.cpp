#include "CCycleMesure.h"
#include "cotautomate_debug.h"
#include "qtimer.h"
#include "qlist.h"
#include "CLinkAction.h"
#include "CActionFactory.h"
#include "IAction.h"
#include "CStep.h"

CCycleMesure::CCycleMesure(QObject *parent)
    : ICycle(parent)
{
    initTimer();
}

CCycleMesure::CCycleMesure(const QVariantMap &mapCycle): ICycle(){
    qCDebug(COTAUTOMATE_LOG) << "constructor CCycleMesure(const QVariantMap &mapCycle) mapCycle:" << mapCycle;
    if(mapCycle.contains(QStringLiteral("name")))
        m_name = mapCycle[QStringLiteral("name")].toString();
    else
        m_name = QStringLiteral("Action not named");
    m_label = mapCycle[tr("fr_FR")].toString();

    const QVariantList listSteps = mapCycle[QStringLiteral("steps")].toList();
    foreach(const QVariant &varStep, listSteps){
        const QVariantMap mapStep = varStep.toMap();
        CStep* step = new CStep(mapStep);
        m_listSteps.append(step);
    }
    initTimer();
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
    return mapSerialise;
}
void CCycleMesure::initTimer(){
    //m_timer = new QTimer(this);
    //connect(m_timer, &QTimer::timeout, this, &CCycleMesure::slotExecNextStep);
    //m_timer->setInterval(m_timeout);

}

CCycleMesure::~CCycleMesure()
{

}
eTypeCycle CCycleMesure::getType()const{
    return CYCLE_MESURE;
}
void CCycleMesure::slotExecNextStep(){


    if(m_itListStepsPasEnCours != m_listSteps.end()){// && (*m_itListStepsPasEnCours)->getNumStep() == m_iTimer){
        qCDebug(COTAUTOMATE_LOG) << "CCycleMesure slotExecNextStep. Setp : " << (*m_itListStepsPasEnCours)->getLabel() << " step : " << (*m_itListStepsPasEnCours)->getNumStep();
        (*m_itListStepsPasEnCours++)->execStep();

    }

    if(m_itListStepsPasEnCours == m_listSteps.end()) { //fin du cycle
        //m_timer->stop();
        emit signalReadyForPlayNextCycle();
    }else{
        int delay;
        if((m_itListStepsPasEnCours != m_listSteps.begin())){
            m_timeout = (*m_itListStepsPasEnCours)->getNumStep()*1000 - (*m_itListStepsPasEnCours.operator-(1))->getNumStep()*1000;
        }else
            m_timeout = (*m_itListStepsPasEnCours)->getNumStep()*1000;
        qCDebug(COTAUTOMATE_LOG) << "time out before next step : " << m_timeout;
        QTimer::singleShot(m_timeout, this, SLOT(slotExecNextStep()));
    }
    //m_iTimer++;


}
void CCycleMesure::slotRunCycle(){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMesure::slotRunCycle()";

    if(!m_listSteps.isEmpty()){
        m_itListStepsPasEnCours = m_listSteps.begin();
        m_timeout = m_listSteps.first()->getNumStep() * 1000; //step en seconde
        qCDebug(COTAUTOMATE_LOG) << "time out before next step : " << m_timeout;
        QTimer::singleShot(m_timeout, this, SLOT(slotExecNextStep()));
    }

    qCDebug(COTAUTOMATE_LOG) << "FIN CCycleMesure::slotRunCycle()";

}
void CCycleMesure::slotPauseCycle(){

}
void CCycleMesure::slotStopCycle(){

}

QString CCycleMesure::getRelatedStreamName()const{
    return m_streamName;
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

int CCycleMesure::getCurrentStepIndex() const
{
    return -1;
}
QString CCycleMesure::getLabel()const{ return m_label;}
void CCycleMesure::setLbl(const QString &lbl){ m_label = lbl;}

void CCycleMesure::addAction(int arg_step, IAction* action){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMesure::addAction(int arg_step, IAction* action) NE DOIT PLUS ETRE APPELE" ;
    /*if(action){
        CLinkAction* linkAction = new CLinkAction(arg_step, action);
        QList<CLinkAction*>::iterator it = m_ListActions.begin();
        bool bSortie= false;
        while(!bSortie && it != m_ListActions.end()){
            //if((*it)->getStep() > linkAction->getStep()){
            //    m_ListActions.insert(it, linkAction);
            //    bSortie = true;
            //}
            it++;
        }
        if(!bSortie) m_ListActions.append(linkAction);
    }*/

}
void CCycleMesure::setType(eTypeCycle){}

QString CCycleMesure::getName()const{
    return m_name;

}
void CCycleMesure::setName(const QString &name){
    m_name = name;

}

bool CCycleMesure::isRunning(){return true;}
bool CCycleMesure::isPaused(){return true;}

void CCycleMesure::slotUnPauseCycle(){}

void CCycleMesure::slotStopEndCycle(){}
void CCycleMesure::slotGoToEndCycle(){}
void CCycleMesure::slotGoToStepCycle(int numStep){}
void CCycleMesure::slotGetReadyForPlayNextCycle(){}
void CCycleMesure::slotGetReadyForPlayCycle(){}

