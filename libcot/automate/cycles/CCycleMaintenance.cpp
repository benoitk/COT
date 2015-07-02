#include "CCycleMaintenance.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "CAutomate.h"
#include "CVariableStream.h"
CCycleMaintenance::CCycleMaintenance(QObject *parent)
    : ICycle(parent)
{

}
CCycleMaintenance::CCycleMaintenance(const QVariantMap& mapCycle,QObject *parent):ICycle(mapCycle, parent){


}

CCycleMaintenance::CCycleMaintenance(eTypeCycle typeCycle, QObject* parent): ICycle(parent) {

}
CCycleMaintenance::~CCycleMaintenance()
{
    delete m_stepStop;
    foreach (CStep* step, m_listSteps) {
        delete step;
    }
}
QVariantMap CCycleMaintenance::serialise(){
    QVariantMap mapSerialise = ICycle::serialise();

    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("maintenance"));
    return mapSerialise;
}

eTypeCycle CCycleMaintenance::getType()const{
    return CYCLE_MAINTENANCE;
}
void CCycleMaintenance::slotRunCycle(){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMaintenance::slotRunCycle()";

}
void CCycleMaintenance::slotPauseCycle(){

}
void CCycleMaintenance::slotStopCycle(){
}


void CCycleMaintenance::slotUnPauseCycle(){}
void CCycleMaintenance::slotStopEndCycle(){}
void CCycleMaintenance::slotGoToEndCycle(){}
void CCycleMaintenance::slotGoToStepCycle(int numStep){}
void CCycleMaintenance::slotGetReadyForPlayNextCycle(){}
void CCycleMaintenance::slotGetReadyForPlayCycle(){}
void CCycleMaintenance::slotExecNextStep(){}
