#include "CCycleMesure.h"
#include "qdebug.h"
#include "qtimer.h"
#include "qlist.h"
#include "CLinkAction.h"
CCycleMesure::CCycleMesure(QObject *parent)
	: ICycle(parent)
{
	initTimer();
}
CCycleMesure::CCycleMesure(QVariantMap mapCycle, QMap<QString, IAction*> mapActions): ICycle(){
	qDebug() << "CCycleMesure::CCycleMesure(QVariantMap mapCycle, QMap<QString, IAction*> mapActions)): ICycle(){" << mapCycle; 
	
	m_label = mapCycle[tr("FR_lbl")].toString();
	m_name = mapCycle["name"].toString();
	
	QVariantList listActions = mapCycle["actions"].toList(); 
	
	qDebug() << "m_label" << m_label; 
	qDebug() << "m_name" << m_name; 
	qDebug() << " mapActions" << mapActions; 
	qDebug() << " mapCycle`Actions" << mapCycle["actions"]; 
	qDebug() << "QVariantList listActions" << listActions; 
	foreach(QVariant varAction, listActions){
		qDebug() << "varAction : " << varAction.toMap();
		QVariantMap variantMap = varAction.toMap();
		qDebug() << "mapActions[varAction.toString()] : " << mapActions.value(variantMap.value("name").toString()) ; 
		IAction* action = mapActions.value(variantMap.value("name").toString());
		if(action) 
			this->addAction(variantMap.value("step").toInt() , action);
	}
	initTimer();
	this->moveToThread(&m_thread);
	m_thread.start();
	
	qDebug() << "FIN CCycleMesure::CCycleMesure(QVariantMap mapCycle): ICycle(){" ; 
}
CCycleMesure::CCycleMesure(QVariantMap mapCycle): ICycle(){
	qDebug() << "CCycleMesure::CCycleMesure(QVariantMap mapCycle): ICycle(){" << mapCycle; 
	
	m_label = mapCycle[tr("FR_lbl")].toString();
	m_name = mapCycle["name"].toString();
	
	QVariantList listActions = mapCycle["actions"].toList(); 
	
	qDebug() << "m_label" << m_label; 
	qDebug() << "m_name" << m_name; 
	qDebug() << " mapCycle`Actions" << mapCycle["actions"]; 
	qDebug() << "QVariantList listActions" << listActions; 
	foreach(QVariant varAction, listActions){
		IAction* action = IAction::factory(varAction.toMap());
		QVariantMap variantMap = varAction.toMap();
		if(action) 
			this->addAction(variantMap.value("step").toInt(),action);
	}
	initTimer();
	this->moveToThread(&m_thread);
	m_thread.start();
	
	qDebug() << "FIN CCycleMesure::CCycleMesure(QVariantMap mapCycle): ICycle(){" ; 
}
CCycleMesure::CCycleMesure():ICycle()
{
	initTimer();

}
void CCycleMesure::initTimer(){
	m_timer = new QTimer(this);
	connect(m_timer, &QTimer::timeout, this, &CCycleMesure::slotExecNextStep);
	m_timer->setInterval(1000);
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
	qDebug() << "CCycleMesure::slotRunCycle() ";

	if(!m_ListAction.isEmpty()){
		m_itListActionPasEnCours = m_ListAction.begin(); 
		m_iTimer = 0;
		m_timer->start();
	}
	qDebug() << "FIN CCycleMesure::slotRunCycle()";
}
void CCycleMesure::slotPauseCycle(){
	
}
void CCycleMesure::slotStopCycle(){

}

QString CCycleMesure::getLbl()const{ return m_label;}
void CCycleMesure::setLbl(QString lbl){ m_label = lbl;}
	
void CCycleMesure::addAction(int arg_step, IAction* action){
	qDebug() << "CCycleMesure::addAction(IAction* action){" ;
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
	qDebug() << "FIN CCycleMesure::addAction(IAction* action){" << m_ListAction.count();

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

