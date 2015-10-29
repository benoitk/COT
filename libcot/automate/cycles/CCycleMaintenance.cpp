#include "CCycleMaintenance.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "CAutomate.h"
#include "CVariableStream.h"
#include "qvariant.h"
CCycleMaintenance::CCycleMaintenance(QObject *parent)
    : CCycleMesure(parent)
{

}
CCycleMaintenance::CCycleMaintenance(const QVariantMap& mapCycle,QObject *parent):CCycleMesure(mapCycle, parent){
    if(mapCycle.contains(QStringLiteral("variables_input"))){
        const QVariantList listVariablesInput = mapCycle[QStringLiteral("variables_input")].toList();
        foreach(const QVariant &var, listVariablesInput){
            m_listVariablesInput.append(CAutomate::getInstance()->getVariable(var.toString()));
        }
    }
    if(mapCycle.contains(QStringLiteral("variables_output"))){
        const QVariantList listVariablesOuput = mapCycle[QStringLiteral("variables_output")].toList();
        foreach(const QVariant &var, listVariablesOuput){
            m_listVariablesOutput.append(CAutomate::getInstance()->getVariable(var.toString()));
        }
    }

    if(mapCycle.contains(QStringLiteral("variables_copy_on_validation"))){
        const QVariantList listVariables = mapCycle[QStringLiteral("variables_copy_on_validation")].toList();
        foreach(const QVariant &varMap, listVariables){
            const QVariant src = varMap.toMap().value(QStringLiteral("source"));
            const QVariant trg = varMap.toMap().value(QStringLiteral("target"));
            QPair<IVariable*, IVariable*> pair(CAutomate::getInstance()->getVariable(src.toString())
                          , CAutomate::getInstance()->getVariable(trg.toString()));
            m_listVariablesCopyOnValidation.append(pair);
        }
    }

}

CCycleMaintenance::CCycleMaintenance(enumTypeCycle typeCycle, QObject* parent): CCycleMesure(parent) {

}
CCycleMaintenance::~CCycleMaintenance()
{
    delete m_stepStop;
    foreach (CStep* step, m_listSteps) {
        delete step;
    }
}
QVariantMap CCycleMaintenance::serialize(){
    QVariantMap mapSerialise = ICycle::serialize();

    QStringList listInputVar;
    foreach(IVariable* var, m_listVariablesInput){
        listInputVar.append(var->getName());
    }
    QStringList listOutputVar;
    foreach(IVariable* var, m_listVariablesOutput){
        listOutputVar.append(var->getName());
    }
    mapSerialise.insert(QStringLiteral("variables_output"), listOutputVar);

    QVariantList listMapVarCopyOnValidations;
    for(int i=0; i<m_listVariablesCopyOnValidation.count(); ++i){
        QPair<IVariable*, IVariable*> pair = m_listVariablesCopyOnValidation.at(i);
        QVariantMap map;
        map.insert(QStringLiteral("source"), pair.first->getName());
        map.insert(QStringLiteral("target"), pair.second->getName());
        listMapVarCopyOnValidations.append(map);
    }
    mapSerialise.insert(QStringLiteral("variables_copy_on_validation"), listMapVarCopyOnValidations);

    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("maintenance"));
    return mapSerialise;
}

enumTypeCycle CCycleMaintenance::getType()const{
    return e_cycle_maintenance;
}
QList<IVariable*>  CCycleMaintenance::getListVariablesInput(){
    return m_listVariablesInput;
}

QList<IVariable*>  CCycleMaintenance::getListVariablesOutput(){
    return m_listVariablesOutput;
}

void CCycleMaintenance::doValidationCopies(){
    QPair<IVariable*, IVariable*> pair;
    foreach(pair, m_listVariablesCopyOnValidation){
        pair.second->setValue(pair.first->toVariant());
    }
}
void CCycleMaintenance::slotStepFinished(CStep* arg_step){
    qCDebug(COTAUTOMATE_LOG) << "CCycleMaintenance::slotStepFinished(CStep* arg_step) ";
    QMutexLocker lock(&m_mutex);
    CCycleMesure::slotStepFinished(arg_step);
    if(m_itListStepsPasEnCours == m_listSteps.end()) { //fin du cycle
        QThread* currentThread = QThread::currentThread();
        if(m_mapTimerInfoNumStep.contains(currentThread)){
            m_mapTimerInfoNumStep.value(currentThread)->stop();
        }
    }
}
