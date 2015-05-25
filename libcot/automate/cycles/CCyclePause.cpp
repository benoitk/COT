#include "CCyclePause.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "qthread.h"
#include "qtimer.h"
CCyclePause::CCyclePause(QObject *parent)
    : ICycle(parent)
{
    initTimer();
}
CCyclePause::CCyclePause(const QVariantMap &mapCycle)
    : ICycle()
{
    m_name = mapCycle[QStringLiteral("name")].toString();
    m_label = mapCycle[tr("FR_lbl")].toString();
    m_iTempsCycle = mapCycle[QStringLiteral("timer")].toInt();

    initTimer();
    this->moveToThread(&m_thread);
    m_thread.start();
}
CCyclePause::CCyclePause(int temps, QObject* parent): ICycle(parent){
    m_iTempsCycle = temps;
    initTimer();
}
CCyclePause::CCyclePause(int temps): ICycle(){
    m_iTempsCycle = temps;
    initTimer();
}
CCyclePause::~CCyclePause()
{

}
QVariantMap CCyclePause::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("pause"));
    mapSerialise.insert(QStringLiteral("timer"), m_iTimer);

    QVariantList listSteps;
    foreach(CStep* step, m_listSteps){
        listSteps.append(step->serialise());
    }
    mapSerialise.insert(QStringLiteral("steps"), listSteps);
    return mapSerialise;
}
void CCyclePause::initTimer(){
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CCyclePause::slotExecNextStep);
    m_timer->setInterval(1000);
}
eTypeCycle CCyclePause::getType()const{
    return CYCLE_PAUSE;
}
void CCyclePause::slotRunCycle(){
    qCDebug(COTAUTOMATE_LOG) << "CCyclePause::slotRunCycle()";
    m_iTimer = 0;
    m_timer->start();
}
void CCyclePause::slotExecNextStep(){
    if(m_iTimer++ < m_iTempsCycle){
        qCDebug(COTAUTOMATE_LOG) << "t : " << m_iTimer << " / " << m_iTempsCycle;
    }
    else{
        m_timer->stop();
        emit signalReadyForPlayNextCycle();
    }

}
QString CCyclePause::getLabel()const{ return m_label;}
void CCyclePause::setLbl(const QString &lbl){ m_label = lbl;}
void CCyclePause::slotPauseCycle(){

}
void CCyclePause::slotUnPauseCycle(){

}
void CCyclePause::slotStopCycle(){
}

void CCyclePause::addAction(int arg_step, IAction* action){

}
void CCyclePause::setType(eTypeCycle){

}
bool CCyclePause::isRunning(){ return true;}
bool CCyclePause::isPaused(){ return true;}

QString CCyclePause::getName()const{
    return m_name;
}
void CCyclePause::setName(const QString&){
}
void CCyclePause::slotStopEndCycle(){}
void CCyclePause::slotGoToEndCycle(){}
void CCyclePause::slotGoToStepCycle(int){}
void CCyclePause::slotGetReadyForPlayNextCycle(){}
void CCyclePause::slotGetReadyForPlayCycle(){}

QString CCyclePause::getRelatedStreamName()const{
    return m_streamName;
}

void CCyclePause::setRelatedStreamName(const QString &name)
{
    m_streamName = name;
}
QList<CStep*> CCyclePause::getListSteps()const{
    return m_listSteps;
}
CStep* CCyclePause::getStepStop()const{
    return m_stepStop;
}

int CCyclePause::getCurrentStepIndex() const
{
    return -1;
}
