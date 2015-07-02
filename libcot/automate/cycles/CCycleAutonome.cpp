#include "CCycleAutonome.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "CVariableStream.h"
#include "CAutomate.h"
CCycleAutonome::CCycleAutonome(QObject *parent)
    :CCycleMesure(parent) {}

CCycleAutonome::CCycleAutonome(const QVariantMap &variantMap, QObject *parent)
    :CCycleMesure(variantMap, parent){}

CCycleAutonome::CCycleAutonome(const QVariantMap &variantMap, const QMap<QString, IAction *> &actionMap, QObject *parent)
    :CCycleMesure(variantMap, parent){}

CCycleAutonome::~CCycleAutonome(){
    delete m_stepStop;
    foreach (CStep* step, m_listSteps) {
        delete step;
    }
}

QString CCycleAutonome::getRelatedStreamName()const{
    return CCycleMesure::getRelatedStreamName();
}
CVariableStream* CCycleAutonome::getRelatedStream()const{
    return CAutomate::getInstance()->getStream(CCycleMesure::getRelatedStreamName());
}
QVariantMap CCycleAutonome::serialise(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);
    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("autonome"));

    QVariantList listSteps;
    foreach(CStep* step, m_listSteps){
        listSteps.append(step->serialise());
    }
    mapSerialise.insert(QStringLiteral("steps"), listSteps);
    mapSerialise.insert(QStringLiteral("related_stream_name"), getRelatedStreamName());
    return mapSerialise;
}
void CCycleAutonome::setRelatedStreamName(const QString &name)
{
    CCycleMesure::setRelatedStreamName(name);
}
QList<CStep*> CCycleAutonome::getListSteps()const{
    return m_listSteps;
}
CStep* CCycleAutonome::getStepStop()const{
    return m_stepStop;
}

void CCycleAutonome::setListSteps(const QList<CStep *> &steps, CStep *stopStep)
{
    qDeleteAll(m_listSteps);
    delete m_stepStop;
    m_listSteps = steps;
    m_stepStop = stopStep;
}

int CCycleAutonome::getCurrentStepIndex() const
{
    return -1;
}
//CCycleAutonome::CCycleAutonome(QObject *parent)
//    : ICycle(parent)
//{
//
//}
//CCycleAutonome::CCycleAutonome(QObject* parent, eTypeCycle typeCycle): ICycle(parent){
//    m_typeCycle = typeCycle;
//}
//CCycleAutonome::~CCycleAutonome()
//{
//
//}
//eTypeCycle CCycleAutonome::getType()const{
//    return CYCLE_AUTONOME;
//}
//void CCycleAutonome::slotRunCycle(){
//    qCDebug(COTAUTOMATE_LOG) << "CCycleAutonome::slotRunCycle()";
//
//}
//QString CCycleAutonome::getLabel()const{ return m_label;}
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
//    return m_name;
//}
//void CCycleAutonome::setName(const QString &name){
//    m_name = name;
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
