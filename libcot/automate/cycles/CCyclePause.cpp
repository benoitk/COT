#include "CCyclePause.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "qthread.h"
#include "qtimer.h"
#include "CAutomate.h"
#include "CVariableStream.h"

CCyclePause::CCyclePause(QObject *parent)
    : ICycle(parent)
{
    initTimer();
}
CCyclePause::CCyclePause(const QVariantMap &mapCycle, QObject* parent)
    : ICycle(mapCycle, parent)
{
    m_fTempsCycle = mapCycle[QStringLiteral("timer")].toInt();
    m_isRunning = false;
    initTimer();
    qDebug() << "moveThread CCyclePause";
    this->moveToThread(&m_thread);
    m_thread.start();
}
CCyclePause::CCyclePause(int temps, QObject* parent): ICycle(parent) {
    m_fTempsCycle = temps;
    initTimer();
}

CCyclePause::CCyclePause(int temps): ICycle() {
    m_fTempsCycle = temps;
    initTimer();
}
CCyclePause::~CCyclePause()
{

}
QVariantMap CCyclePause::serialize(){
    QVariantMap mapSerialise = ICycle::serialize();

    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("pause"));
    mapSerialise.insert(QStringLiteral("timer"), m_fTempsCycle);


    return mapSerialise;
}
void CCyclePause::initTimer(){
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CCyclePause::slotExecNextStep);
    connect(m_timer, &QTimer::timeout, this, &ICycle::slotUpdateCycleInfosNumStep);
    m_timer->setInterval(100);
}
enumTypeCycle CCyclePause::getType()const{
    return e_cycle_pause;
}
void CCyclePause::slotRunCycle(){
    qCDebug(COTAUTOMATE_LOG) << "CCyclePause::slotRunCycle()";
    m_fTimer = 0;

    emit CAutomate::getInstance()->signalUpdateCountStep(m_fTempsCycle);
    updateCycleInfosStep(0, tr("En pause"));

    m_isRunning = true;
    m_timer->start();
}
void CCyclePause::slotExecNextStep(){
    if((m_fTimer+=0.1f) < m_fTempsCycle){
        qCDebug(COTAUTOMATE_LOG) << "t : " << m_fTimer << " / " << m_fTempsCycle;

    }
    else{
        m_timer->stop();
        emit signalReadyForPlayNextCycle(this);
    }

}

void CCyclePause::slotPauseCycle(){

}
void CCyclePause::slotUnPauseCycle(){

}
void CCyclePause::slotStopCycle(){
    m_timer->stop();
    m_isRunning = false;
    emit signalStopped(this);
}

void CCyclePause::slotStopEndCycle() {}
void CCyclePause::slotGoToEndCycle() {}
void CCyclePause::slotGoToStepCycle(int) {}
void CCyclePause::slotGetReadyForPlayNextCycle()  {
    m_timer->stop();
    m_isRunning = false;
    emit signalReadyForPlayNextCycle(this);
}
void CCyclePause::slotGetReadyForPlayCycle()  {}
