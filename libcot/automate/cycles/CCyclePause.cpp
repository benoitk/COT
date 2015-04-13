#include "CCyclePause.h"
#include "qdebug.h"
#include "qthread.h"
#include "qtimer.h"
CCyclePause::CCyclePause(QObject *parent)
	: ICycle(parent)
{
	initTimer();
}
CCyclePause::CCyclePause(QVariantMap mapCycle)
	: ICycle()
{
	m_name = mapCycle["name"].toString();
	m_label = mapCycle[tr("FR_lbl")].toString();
	m_iTempsCycle = mapCycle["timer"].toInt();
	
	initTimer();
	this->moveToThread(&m_thread);
	m_thread.start();
}
CCyclePause::CCyclePause(QObject* parent, int temps): ICycle(parent){
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
void CCyclePause::initTimer(){
	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &CCyclePause::slotExecNextStep);
	m_timer->setInterval(1000);
}
eTypeCycle CCyclePause::getType()const{
	return CYCLE_PAUSE;
}
void CCyclePause::slotRunCycle(){
	qDebug() << "CCyclePause::slotRunCycle()";
	m_iTimer = 0;
	m_timer->start();
}
void CCyclePause::slotExecNextStep(){
	if(m_iTimer++ < m_iTempsCycle){
		qDebug() << "t : " << m_iTimer << " / " << m_iTempsCycle;
	}
	else{
		m_timer->stop();
		emit signalReadyForPlayNextCycle();
	}

}
QString CCyclePause::getLbl()const{ return m_label;}
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

bool CCyclePause::isStreamRelated()const{
	return true;
}
QString CCyclePause::getRelatedStreamName()const{
	return "voie 1";
}
QList<CStep*> CCyclePause::getListSteps()const{
	return m_listSteps;
}
CStep* CCyclePause::getStepStop()const{
	return m_stepStop;
}
