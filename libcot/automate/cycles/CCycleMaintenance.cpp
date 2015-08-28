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

CCycleMaintenance::CCycleMaintenance(eTypeCycle typeCycle, QObject* parent): CCycleMesure(parent) {

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
