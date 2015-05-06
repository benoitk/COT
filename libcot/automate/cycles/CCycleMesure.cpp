#include "CCycleMesure.h"
#include "qdebug.h"
#include "qtimer.h"
#include "qlist.h"
#include "CLinkAction.h"
#include "CActionFactory.h"
#include "CAutomate.h"
#include "IAction.h"
#include "CStep.h"

CCycleMesure::CCycleMesure(QObject *parent)
	: ICycle(parent)
{
	initTimer();
}

CCycleMesure::CCycleMesure(const QVariantMap &mapCycle): ICycle(){
    qDebug() << "constructor CCycleMesure(const QVariantMap &mapCycle) mapCycle:" << mapCycle; 
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
void CCycleMesure::initTimer(){
	m_periode = 500;
	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &CCycleMesure::slotExecNextStep);
	m_timer->setInterval(m_periode);
}
CCycleMesure::~CCycleMesure()
{

}
eTypeCycle CCycleMesure::getType()const{
	return CYCLE_MESURE;
}
void CCycleMesure::slotExecNextStep(){	
    qDebug() << "CCycleMesure slotExecNextStep. Setp : " << m_iTimer << " Next step : " << (*m_itListStepsPasEnCours)->getNumStep();
    if(m_itListStepsPasEnCours != m_listSteps.end()){
		/*while(	  m_itListActionPasEnCours != m_ListActions.end() 
			  && (*m_itListActionsPasEnCours)->getStep() == m_iTimer){
			(*m_itListActionsPasEnCours++)->getAction()->runAction();
		}*/
	}
	
	if(m_itListStepsPasEnCours == m_listSteps.end()) { //fin du cycle
		m_timer->stop();
		emit signalReadyForPlayNextCycle();
	}
	m_iTimer++;
}
void CCycleMesure::slotRunCycle(){
    qDebug() << "CCycleMesure::slotRunCycle()";
	if(!m_listSteps.isEmpty()){
		m_itListStepsPasEnCours = m_listSteps.begin(); 
		m_iTimer = 0;
		m_timer->start();
	}
    qDebug() << "FIN CCycleMesure::slotRunCycle()";

}
void CCycleMesure::slotPauseCycle(){
	
}
void CCycleMesure::slotStopCycle(){

}
bool CCycleMesure::isStreamRelated()const{
	return true;
}
QString CCycleMesure::getRelatedStreamName()const{
    return QStringLiteral("stream_1");
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
QString CCycleMesure::getLbl()const{ return m_label;}
void CCycleMesure::setLbl(const QString &lbl){ m_label = lbl;}
	
void CCycleMesure::addAction(int arg_step, IAction* action){
    qDebug() << "CCycleMesure::addAction(int arg_step, IAction* action) NE DOIT PLUS ETRE APPELE" ;
	/*if(action){
		CLinkAction* linkAction = new CLinkAction(arg_step, action);
		QList<CLinkAction*>::iterator it = m_ListActions.begin();
		bool bSortie= false;
		while(!bSortie && it != m_ListActions.end()){
			//if((*it)->getStep() > linkAction->getStep()){
			//	m_ListActions.insert(it, linkAction);
			//	bSortie = true;
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

