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
    m_iTempsCycle = mapCycle[QStringLiteral("timer")].toInt();

    initTimer();
    this->moveToThread(&m_thread);
    m_thread.start();
}
CCyclePause::CCyclePause(int temps, QObject* parent): ICycle(parent) {
    m_iTempsCycle = temps;
    initTimer();
}
CCyclePause::CCyclePause(int temps): ICycle() {
    m_iTempsCycle = temps;
    initTimer();
}
CCyclePause::~CCyclePause()
{

}
QVariantMap CCyclePause::serialise(){
    QVariantMap mapSerialise = ICycle::serialise();

    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("pause"));
    mapSerialise.insert(QStringLiteral("timer"), m_iTimer);

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

void CCyclePause::slotPauseCycle(){

}
void CCyclePause::slotUnPauseCycle(){

}
void CCyclePause::slotStopCycle(){
}

void CCyclePause::slotStopEndCycle() {}
void CCyclePause::slotGoToEndCycle() {}
void CCyclePause::slotGoToStepCycle(int) {}
void CCyclePause::slotGetReadyForPlayNextCycle()  {}
void CCyclePause::slotGetReadyForPlayCycle()  {}
