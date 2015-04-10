#include "CCycleAutonome.h"
#include "qdebug.h"

CCycleAutonome::CCycleAutonome(QObject *parent)
	:CCycleMesure(parent){}
CCycleAutonome::CCycleAutonome(const QVariantMap &variantMap)
	:CCycleMesure(variantMap){}
CCycleAutonome::CCycleAutonome(const QVariantMap &variantMap, const QMap<QString, IAction *> &actionMap)
	:CCycleMesure(variantMap, actionMap){}
CCycleAutonome::~CCycleAutonome(){}

bool CCycleAutonome::isStreamRelated()const{
	return true;
}
QString CCycleAutonome::getRelatedStreamName()const{
	return "voie 1";
}
QList<CStep*> CCycleAutonome::getListSteps()const{
	return m_listSteps;
}
CStep* CCycleAutonome::getStepStop()const{
	return m_stepStop;
}
//CCycleAutonome::CCycleAutonome(QObject *parent)
//	: ICycle(parent)
//{
//
//}
//CCycleAutonome::CCycleAutonome(QObject* parent, eTypeCycle typeCycle): ICycle(parent){
//	m_typeCycle = typeCycle;
//}
//CCycleAutonome::~CCycleAutonome()
//{
//
//}
//eTypeCycle CCycleAutonome::getType()const{
//	return CYCLE_AUTONOME;
//}
//void CCycleAutonome::slotRunCycle(){
//	qDebug() << "CCycleAutonome::slotRunCycle()";
//	
//}
//QString CCycleAutonome::getLbl()const{ return m_label;}
//void CCycleAutonome::setLbl(const QString &lbl){ m_label = lbl;}
//void CCycleAutonome::slotPauseCycle(){
//	
//}
//void CCycleAutonome::slotStopCycle(){
//}
//
//void CCycleAutonome::addAction(IAction* action){
//	
//}
//void CCycleAutonome::setType(eTypeCycle){
//
//}
//QString CCycleAutonome::getName()const{
//	return m_name;
//}
//void CCycleAutonome::setName(const QString &name){
//	m_name = name;
//}
//
//bool CCycleAutonome::isRunning(){return true;}
//bool CCycleAutonome::isPaused(){return true;}
//void CCycleAutonome::slotUnPauseCycle(){}
//void CCycleAutonome::slotStopEndCycle(){}
//void CCycleAutonome::slotGoToEndCycle(){}
//void CCycleAutonome::slotGoToStepCycle(int numStep){}
//void CCycleAutonome::slotGetReadyForPlayNextCycle(){}
//void CCycleAutonome::slotExecNextStep(){}
//void CCycleAutonome::slotGetReadyForPlayCycle(){}
