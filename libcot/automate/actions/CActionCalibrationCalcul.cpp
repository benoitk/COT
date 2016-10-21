#include "CActionCalibrationCalcul.h"

#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "cotautomate_debug.h"


CActionCalibrationCalcul::CActionCalibrationCalcul(const QVariantMap &mapAction, CAutomate *parent)
    : IAction(mapAction, parent)
{
    m_measure = m_automate->getVariable(mapAction[QStringLiteral("measure")].toString());
    m_standardValue = m_automate->getVariable(mapAction[QStringLiteral("standard_value")].toString());
    m_coefCalibration = m_automate->getVariable(mapAction[QStringLiteral("coef_calibration")].toString());
    m_coefCalibrationNew = m_automate->getVariable(mapAction[QStringLiteral("new_coef_calibration")].toString());
    m_default= m_automate->getVariable(mapAction[QStringLiteral("default")].toString());
    m_marginDefault = m_automate->getVariable(mapAction[QStringLiteral("margin_default")].toString());
    m_co2g= m_automate->getVariable(mapAction[QStringLiteral("co2g")].toString());
    m_vesselVolume= m_automate->getVariable(mapAction[QStringLiteral("vessel_volume")].toString());
}

CActionCalibrationCalcul::~CActionCalibrationCalcul()
{

}
QVariantMap CActionCalibrationCalcul::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("measure"), m_measure->getName());
    mapSerialize.insert(QStringLiteral("standard_value"), m_standardValue->getName());
    mapSerialize.insert(QStringLiteral("coef_calibration"), m_coefCalibration->getName());
    mapSerialize.insert(QStringLiteral("new_coef_calibration"), m_coefCalibrationNew->getName());
    mapSerialize.insert(QStringLiteral("default"), m_default->getName());
    mapSerialize.insert(QStringLiteral("margin_default"), m_marginDefault->getName());
    mapSerialize.insert(QStringLiteral("co2g"), m_co2g->getName());
    mapSerialize.insert(QStringLiteral("vessel_volume"), m_vesselVolume->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("calibration_calcul"));

    return mapSerialize;
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
    float marginHight = m_coefCalibration->toFloat() * (1 + m_marginDefault->toFloat()/100);
    float marginLow = m_coefCalibration->toFloat() * m_marginDefault->toFloat() /100;
    if(m_coefCalibrationNew->toFloat() < marginLow || m_coefCalibrationNew->toFloat() > marginHight)
        m_default->setValue(true);
    else
        m_default->setValue(false);
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
    return actionType::type_calibration_calcul;
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
enumVariableType CActionCalibrationCalcul::getWaitedType(const QString& arg_key){
    if(tr("Measure")== arg_key) return e_type_float;
    else if(tr("Coef calibration")== arg_key) return e_type_float;
    else if(tr("CO2g")== arg_key) return e_type_float;
    else if(tr("Vessel volume")== arg_key) return e_type_float;

    return e_type_unknow;
}
