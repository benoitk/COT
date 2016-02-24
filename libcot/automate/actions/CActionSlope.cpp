#include "CActionSlope.h"
#include "CVariableAlarm.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CVariableOutputFloat.h"
#include "CAutomate.h"

#include "cotautomate_debug.h"
#include "QThreadPool"


CActionSlope::CActionSlope(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();

    m_startSetpoint = automate->getVariable(mapAction[QStringLiteral("start_setpoint")].toString());
    m_inibitedAlarm = automate->getVariable(mapAction[QStringLiteral("inhibited_alarm")].toString());
    m_setpoint = automate->getVariable(mapAction[QStringLiteral("setpoint")].toString());
    m_duration = automate->getVariable(mapAction[QStringLiteral("duration")].toString());
    m_nbSection = automate->getVariable(mapAction[QStringLiteral("nb_sections")].toString());

    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}

CActionSlope::~CActionSlope(){

}

QVariantMap CActionSlope::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("start_setpoint"), m_startSetpoint->getName());
    mapSerialize.insert(QStringLiteral("inhibited_alarm"), m_inibitedAlarm->getName());
    mapSerialize.insert(QStringLiteral("setpoint"), m_setpoint->getName());
    mapSerialize.insert(QStringLiteral("duration"), m_duration->getName());
    mapSerialize.insert(QStringLiteral("nb_sections"), m_nbSection->getName());

    QStringList listVarName;
    foreach (IVariable* var, m_listVar) {
        listVarName.append(var->getName());
    }
    mapSerialize.insert(QStringLiteral("input_variables"), listVarName);

    return mapSerialize;
}

bool CActionSlope::runAction(ICycle* arg_stepParent){
    IAction::runAction(arg_stepParent);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = QThreadPool::globalInstance()->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CActionAcquisitionCitNpoc::runAction";
        }
    }
    return true;
}


void CActionSlope::run(){
    if(m_inibitedAlarm && m_inibitedAlarm->getType() == e_type_alarm)
        dynamic_cast<CVariableAlarm*>(m_inibitedAlarm)->setInhibited(true);

    float backupSetpoint = m_setpoint->toFloat();
    float pas = (backupSetpoint - m_startSetpoint->toFloat()) / m_nbSection->toFloat();
    float sleep = m_duration->toFloat() / m_nbSection->toFloat() *1000;
    if(m_setpoint->getOrganType() == e_type_organ_output && m_setpoint->getType() == e_type_float){
        CVariableOutputFloat* outputSetpoint = dynamic_cast<CVariableOutputFloat*>(m_setpoint);

        outputSetpoint->setValue(m_startSetpoint->toVariant());
        for(int i=0; i<m_nbSection->toInt(); ++i){
            QThread::msleep(sleep);
            outputSetpoint->setValue(outputSetpoint->toFloat()+pas);
        }

        outputSetpoint->setValue(backupSetpoint);
    }
    if(m_inibitedAlarm && m_inibitedAlarm->getType() == e_type_alarm)
        dynamic_cast<CVariableAlarm*>(m_inibitedAlarm)->setInhibited(false);

}


QList<IVariable*> CActionSlope::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_startSetpoint);

    return listParams;
}
actionType CActionSlope::getType()const {
    return actionType::type_cmd_dc_engine;
}

bool CActionSlope::variableUsed(IVariable *arg_var)const {

    if(m_startSetpoint == arg_var) return true;
     foreach (IVariable* var, m_listVar) {
         if(var == arg_var) return true;
     }

    return false;
}

QMap<QString, IVariable*> CActionSlope::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Result"), m_startSetpoint);
    return map;
}

QMap<QString, IVariable*> CActionSlope::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionSlope::setParameter(const QString& arg_key, IVariable* arg_parameter){

    if(tr("Result")== arg_key)m_startSetpoint= arg_parameter;


}
enumVariableType CActionSlope::getWaitedType(const QString& arg_key){
    if(tr("Result")== arg_key) return e_type_float;

    return e_type_unknow;
}
