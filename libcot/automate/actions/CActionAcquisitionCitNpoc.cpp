#include "CActionAcquisitionCitNpoc.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "cotautomate_debug.h"
#include "math.h"

#include "qthreadpool.h"


CActionAcquisitionCitNpoc::CActionAcquisitionCitNpoc(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_measureCell = automate->getVariable(mapAction[QStringLiteral("cellule")].toString());
    m_coef1 = automate->getVariable(mapAction[QStringLiteral("coef_1")].toString());
    m_coef2 = automate->getVariable(mapAction[QStringLiteral("coef_2")].toString());
    m_coef3 = automate->getVariable(mapAction[QStringLiteral("coef_3")].toString());
    m_coef4 = automate->getVariable(mapAction[QStringLiteral("coef_4")].toString());
    m_coef5 = automate->getVariable(mapAction[QStringLiteral("coef_5")].toString());
    m_Offset = automate->getVariable(mapAction[QStringLiteral("offset")].toString());
    m_CstConversion = automate->getVariable(mapAction[QStringLiteral("co2_ppmv_to_co2_gm3_cst")].toString());
    m_zero = automate->getVariable(mapAction[QStringLiteral("zero_point")].toString());
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    m_airflow = automate->getVariable(mapAction[QStringLiteral("debit_airflow")].toString());
    m_vesselVolume = automate->getVariable(mapAction[QStringLiteral("vessel_volume")].toString());
    m_timeout = automate->getVariable(mapAction[QStringLiteral("timeout")].toString());


    QVariantMap variantMap;
    variantMap.insert(QStringLiteral("name"), QStringLiteral("critical_error"));
    variantMap.insert(QStringLiteral("fr_FR"), tr("Generate critical error"));
    variantMap.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    variantMap.insert(QStringLiteral("value"), mapAction[QStringLiteral("critical_error")].toBool());
    m_criticalError = dynamic_cast<CVariableBool*>(CVariableFactory::build(variantMap));



    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}


bool CActionAcquisitionCitNpoc::runAction(){
    IAction::runAction();

    QThreadPool::globalInstance()->tryStart(this);
    return true;
}



void CActionAcquisitionCitNpoc::run(){
    qCDebug(COTAUTOMATE_LOG)<< "CActionAcquisitionCitNpoc 'qrunnable' ";
    QString sActionInfo;
    IVariableInput* measureCell = Q_NULLPTR;
    if(m_measureCell->getOrganType() == type_organ_input)
        measureCell = dynamic_cast<IVariableInput*>(m_measureCell);

    IVariableInput* measureAirflow = Q_NULLPTR;
    if(m_airflow->getOrganType() == type_organ_input)
        measureAirflow = dynamic_cast<IVariableInput*>(m_airflow);

    if(measureCell && measureAirflow){
        int mesure = 0;
        int x = 0;
        float co2ppmv=0;
        float co2g=0;
        float airflow = 0;
        int zero = measureCell->readValue()->toInt();
        m_zero->setValue(zero);
        for(int i = 0; i < m_timeout->toInt() && !m_abort; ++i){

            sActionInfo =  tr("Mesure ") + QString::number(i+1) + "/"  + m_timeout->toString() + " "
                    + m_measureCell->getLabel() + " " +  QString::number(mesure, 'f', 2)
                    + m_airflow->getLabel() + " " +  QString::number(airflow, 'f', 2)
                    + tr("Co2 g") + QString::number(co2g, 'f', 2);     
            qCDebug(COTAUTOMATE_LOG)<< sActionInfo;
            emit CAutomate::getInstance()->signalUpdateCurrentAction(sActionInfo);

            mesure = measureCell->readValue()->toInt();
            airflow = measureAirflow->readValue()->toFloat();
            x = mesure - zero;
            co2ppmv = m_coef1->toFloat() * pow(x, 5)
                    - m_coef2->toFloat() * pow(x, 4)
                    + m_coef3->toFloat() * pow(x,3)
                    - m_coef4->toFloat() * pow(x,2)
                    + m_coef5->toFloat() * x
                    - m_Offset->toFloat();
            co2g += (co2ppmv * m_CstConversion->toFloat()) * ((airflow/60000)*0.01);

            QThread::msleep(500);
        }
        m_result->setValue( (co2g * 12000) / ( (m_vesselVolume->toFloat() / 1000) * 44));
    }
    emit CAutomate::getInstance()->signalUpdateCurrentAction(m_label + tr(" finit"));
    emit signalActionFinished(this);
}

bool CActionAcquisitionCitNpoc::waitUntilFinished(){
    return true;
}

bool CActionAcquisitionCitNpoc::finishedWithCriticalError(){
    if(m_criticalError)
        return true;
    return false;

}
QList<IVariable*> CActionAcquisitionCitNpoc::getListParameters()const{
    QList<IVariable*> listParams;


    return listParams;
}
actionType CActionAcquisitionCitNpoc::getType()const {
    return actionType::type_acquisition_cit_npoc;
}

bool CActionAcquisitionCitNpoc::variableUsed(IVariable *arg_var)const {
    if(m_measureCell == arg_var) return true;

    return false;
}

QMap<QString, IVariable*> CActionAcquisitionCitNpoc::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;

    map.insert(tr("Cellule"), m_measureCell);
    map.insert(tr("Zero point"), m_zero);
    map.insert(tr("Result"), m_result);
    map.insert(tr("Air flow"), m_airflow);
    map.insert(tr("Vessel volume"), m_vesselVolume);
    map.insert(tr("Coefficient 1"), m_coef1);
    map.insert(tr("Coefficient 2"), m_coef2);
    map.insert(tr("Coefficient 3"), m_coef3);
    map.insert(tr("Coefficient 4"), m_coef4);
    map.insert(tr("Coefficient 5"), m_coef5);
    map.insert(tr("Co2 ppmv to Co2 g/m3"), m_CstConversion);
    map.insert(tr("Time acquisition"), m_timeout);

    return map;
}

QMap<QString, IVariable*> CActionAcquisitionCitNpoc::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    map.insert(tr("Generate critical error"), m_criticalError);
    return map;
}
void CActionAcquisitionCitNpoc::setParameter(QString arg_key, IVariable* arg_parameter){
    if(tr("Cellule")== arg_key) m_measureCell= arg_parameter;
    else if(tr("Zero point")== arg_key)m_zero= arg_parameter;
    else if(tr("Result")== arg_key)m_result= arg_parameter;
    else if(tr("Air flow")== arg_key)m_airflow= arg_parameter;
    else if(tr("Vessel volume")== arg_key)m_vesselVolume= arg_parameter;
    else if(tr("Coefficient 1")== arg_key)m_coef1= arg_parameter;
    else if(tr("Coefficient 2")== arg_key)m_coef2= arg_parameter;
    else if(tr("Coefficient 3")== arg_key)m_coef3= arg_parameter;
    else if(tr("Coefficient 4")== arg_key)m_coef4= arg_parameter;
    else if(tr("Coefficient 5")== arg_key)m_coef5= arg_parameter;
    else if(tr("Co2 ppmv to Co2 g/m3")== arg_key)m_CstConversion= arg_parameter;
    else if(tr("Time acquisition")== arg_key)m_timeout= arg_parameter;

    else if(tr("Generate critical error")== arg_key)m_criticalError->setValue(arg_parameter->toBool());
}
