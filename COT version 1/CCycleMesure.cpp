#include "CCycleMesure.h"
#include "qdebug.h"
#include "qtimer.h"
#include "qlist.h"
#include "CLinkAction.h"
#include "CActionFactory.h"
CCycleMesure::CCycleMesure(QObject *parent)
	: ICycle(parent)
{
	initTimer();
}
CCycleMesure::CCycleMesure(QVariantMap mapCycle, QMap<QString, IAction*> mapActions): ICycle(){
	
	m_label = mapCycle[tr("FR_lbl")].toString();
	m_name = mapCycle["name"].toString();
	
	QVariantList listActions = mapCycle["actions"].toList(); 
	
	foreach(QVariant varAction, listActions){
		QVariantMap variantMap = varAction.toMap();
		IAction* action = mapActions.value(variantMap.value("name").toString());
		if(action) 
			this->addAction(variantMap.value("step").toInt() , action);
	}
	initTimer();
	this->moveToThread(&m_thread);
	m_thread.start();
	
}
CCycleMesure::CCycleMesure(QVariantMap mapCycle): ICycle(){
	
	m_label = mapCycle[tr("FR_lbl")].toString();
	m_name = mapCycle["name"].toString();
	
	QVariantList listActions = mapCycle["actions"].toList(); 
	
	foreach(QVariant varAction, listActions){
		IAction* action = CActionFactory::build(varAction.toMap());
		QVariantMap variantMap = varAction.toMap();
		if(action) 
			this->addAction(variantMap.value("step").toInt(),action);
	}
	initTimer();
	this->moveToThread(&m_thread);
	m_thread.start();
	
}
CCycleMesure::CCycleMesure():ICycle()
{
	initTimer();

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
	qDebug() << "CCycleMesure slotExecNextStep. Setp : " << m_iTimer << " Next step : " << (*m_itListActionPasEnCours)->getStep();
	if(m_itListActionPasEnCours != m_ListAction.end()){
		while(	  m_itListActionPasEnCours != m_ListAction.end() 
			  && (*m_itListActionPasEnCours)->getStep() == m_iTimer){
			(*m_itListActionPasEnCours++)->getAction()->runAction();
		}
	}
	
	if(m_itListActionPasEnCours == m_ListAction.end()) { //fin du cycle
		m_timer->stop();
		emit signalReadyForPlayNextCycle();
	}
	m_iTimer++;
}
void CCycleMesure::slotRunCycle(){

	if(!m_ListAction.isEmpty()){
		m_itListActionPasEnCours = m_ListAction.begin(); 
		m_iTimer = 0;
		m_timer->start();
	}
}
void CCycleMesure::slotPauseCycle(){
	
}
void CCycleMesure::slotStopCycle(){

}

QString CCycleMesure::getLbl()const{ return m_label;}
void CCycleMesure::setLbl(QString lbl){ m_label = lbl;}
	
void CCycleMesure::addAction(int arg_step, IAction* action){
	if(action){
		CLinkAction* linkAction = new CLinkAction(arg_step, action);
		QLinkedList<CLinkAction*>::iterator it = m_ListAction.begin();
		bool bSortie= false;
		while(!bSortie && it != m_ListAction.end()){
			if((*it)->getStep() > linkAction->getStep()){
				m_ListAction.insert(it, linkAction);
				bSortie = true;
			}
			it++;
		}
		if(!bSortie) m_ListAction.append(linkAction); 
	}

}
void CCycleMesure::setType(eTypeCycle){}

QString CCycleMesure::getName()const{
	return m_name;

}
void CCycleMesure::setName(QString name){
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

