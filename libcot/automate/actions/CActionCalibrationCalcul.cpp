#include "CActionCalibrationCalcul.h"

#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionCalibrationCalcul::CActionCalibrationCalcul(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_measure = automate->getVariable(mapAction[QStringLiteral("measure")].toString());
    m_standardValue = automate->getVariable(mapAction[QStringLiteral("standard_value")].toString());
    m_coefCalibration = automate->getVariable(mapAction[QStringLiteral("coef_calibration")].toString());
    m_coefCalibrationNew = automate->getVariable(mapAction[QStringLiteral("new_coef_calibration")].toString());
    m_co2g= automate->getVariable(mapAction[QStringLiteral("co2g")].toString());
    m_vesselVolume= automate->getVariable(mapAction[QStringLiteral("vessel_volume")].toString());
}

CActionCalibrationCalcul::~CActionCalibrationCalcul()
{

}


bool CActionCalibrationCalcul::runAction(ICycle* arg_stepParent){
    qCDebug(COTAUTOMATE_LOG)<< "Action commande pompe cc "
            << " label fr " << m_label
            << " Mesure " << m_measure->toString()
            << " co2g " << m_co2g->toString()
            << " vessel_volume " << m_vesselVolume->toString()
            << " coef calib " << m_coefCalibration->toString();


    //Calcul calibration inverse
    m_coefCalibrationNew->setValue( (m_standardValue->toFloat() * m_coefCalibration->toFloat() ) / m_measure->toFloat() );

    return true;
}


QList<IVariable*> CActionCalibrationCalcul::getListParameters()const{
    QList<IVariable*> listParams;
    listParams.append(m_measure);
    listParams.append(m_coefCalibration);
    listParams.append(m_co2g);
    listParams.append(m_vesselVolume);
    return listParams;
}
actionType CActionCalibrationCalcul::getType()const {
    return actionType::type_cmd_dc_engine;
}

bool CActionCalibrationCalcul::variableUsed(IVariable *arg_var)const {
    if(m_measure == arg_var) return true;
    if(m_coefCalibration == arg_var) return true;
    if(m_co2g == arg_var) return true;
    if(m_vesselVolume == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionCalibrationCalcul::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Measure"), m_measure);
    map.insert(tr("Coef calibration"), m_coefCalibration);
    map.insert(tr("CO2g"), m_co2g);
    map.insert(tr("Vessel volume"), m_vesselVolume);
    return map;
}

QMap<QString, IVariable*> CActionCalibrationCalcul::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionCalibrationCalcul::setParameter(const QString& arg_key, IVariable* arg_parameter){
    if(tr("Measure")== arg_key) m_measure= arg_parameter;
    else if(tr("Coef calibration")== arg_key)m_coefCalibration= arg_parameter;
    else if(tr("CO2g")== arg_key)m_co2g= arg_parameter;
    else if(tr("Vessel volume")== arg_key)m_vesselVolume= arg_parameter;

}
variableType CActionCalibrationCalcul::getWaitedType(const QString& arg_key){
    if(tr("Measure")== arg_key) return type_float;
    else if(tr("Coef calibration")== arg_key) return type_float;
    else if(tr("CO2g")== arg_key) return type_float;
    else if(tr("Vessel volume")== arg_key) return type_float;

    return type_unknow;
}
