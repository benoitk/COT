#include "CActionAcquisitionCitNpoc.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "cotautomate_debug.h"
//#include "qmath.h"

#include "qthreadpool.h"


CActionAcquisitionCitNpoc::CActionAcquisitionCitNpoc(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();
    m_measureCell = automate->getVariable(mapAction[QStringLiteral("cellule")].toString());
    m_co2g = automate->getVariable(mapAction[QStringLiteral("co2g")].toString());
    m_coef1 = automate->getVariable(mapAction[QStringLiteral("coef_1")].toString());
    m_coef2 = automate->getVariable(mapAction[QStringLiteral("coef_2")].toString());
    m_coef3 = automate->getVariable(mapAction[QStringLiteral("coef_3")].toString());
    m_coef4 = automate->getVariable(mapAction[QStringLiteral("coef_4")].toString());
    m_coef5 = automate->getVariable(mapAction[QStringLiteral("coef_5")].toString());
    m_coefCorrection = automate->getVariable(mapAction[QStringLiteral("coef_correction")].toString());
    m_coefCourbe = automate->getVariable(mapAction[QStringLiteral("coef_courbe")].toString());
    m_Offset = automate->getVariable(mapAction[QStringLiteral("offset")].toString());
    m_CstConversion = automate->getVariable(mapAction[QStringLiteral("co2_ppmv_to_co2_gm3_cst")].toString());
    m_zero = automate->getVariable(mapAction[QStringLiteral("zero_point")].toString());
    m_result = automate->getVariable(mapAction[QStringLiteral("result")].toString());
    m_airflow = automate->getVariable(mapAction[QStringLiteral("debit_airflow")].toString());
    m_vesselVolume = automate->getVariable(mapAction[QStringLiteral("vessel_volume")].toString());
    m_timeout = automate->getVariable(mapAction[QStringLiteral("timeout")].toString());
    m_derivativeIntervalTx = automate->getVariable(mapAction[QStringLiteral("derivative_interval")].toString());
    m_derivativeThresold = automate->getVariable(mapAction[QStringLiteral("derivative_threshold")].toString());

    m_waitUntilFinished = mapAction[QStringLiteral("wait_until_finished")].toBool();



    QVariantMap variantMapDerivativeCalcul;
    variantMapDerivativeCalcul.insert(QStringLiteral("name"), QStringLiteral("derivative_calcul"));
    variantMapDerivativeCalcul.insert(tr("en_US"), tr("Generate critical error"));
    variantMapDerivativeCalcul.insert(QStringLiteral("type"), QStringLiteral("boolean"));
    variantMapDerivativeCalcul.insert(QStringLiteral("value"), mapAction[QStringLiteral("derivative_calcul")].toBool());
    m_derivativeCalcul = dynamic_cast<CVariableBool*>(CVariableFactory::build(variantMapDerivativeCalcul));



    //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
    this->setAutoDelete(false);
}


QVariantMap CActionAcquisitionCitNpoc::serialize(){
    QVariantMap mapSerialize = IAction::serialize();
    mapSerialize.insert(QStringLiteral("cellule"), m_measureCell->getName());
    mapSerialize.insert(QStringLiteral("result"), m_result->getName());
    mapSerialize.insert(QStringLiteral("zero_point"), m_zero->getName());
    mapSerialize.insert(QStringLiteral("debit_airflow"), m_airflow->getName());
    mapSerialize.insert(QStringLiteral("vessel_volume"), m_vesselVolume->getName());
    mapSerialize.insert(QStringLiteral("coef_1"), m_coef1->getName());
    mapSerialize.insert(QStringLiteral("coef_2"), m_coef2->getName());
    mapSerialize.insert(QStringLiteral("coef_3"), m_coef3->getName());
    mapSerialize.insert(QStringLiteral("coef_4"), m_coef4->getName());
    mapSerialize.insert(QStringLiteral("coef_5"), m_coef5->getName());
    mapSerialize.insert(QStringLiteral("coef_correction"), m_coefCorrection->getName());
    mapSerialize.insert(QStringLiteral("coef_courbe"), m_coefCourbe->getName());
    mapSerialize.insert(QStringLiteral("offset"), m_Offset->getName());
    mapSerialize.insert(QStringLiteral("co2_ppmv_to_co2_gm3_cst"), m_CstConversion->getName());
    mapSerialize.insert(QStringLiteral("co2g"), m_co2g->getName());
    mapSerialize.insert(QStringLiteral("derivative_calcul"), m_derivativeCalcul->toBool());
    mapSerialize.insert(QStringLiteral("derivative_interval"), m_derivativeIntervalTx->getName());
    mapSerialize.insert(QStringLiteral("derivative_threshold"), m_derivativeThresold->getName());
    mapSerialize.insert(QStringLiteral("timeout"), m_timeout->getName());
    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("acquisition_cit_npoc"));
    return mapSerialize;
}

bool CActionAcquisitionCitNpoc::runAction(ICycle* arg_stepParent){
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



void CActionAcquisitionCitNpoc::run(){
    ICycle* stepParent = getStepParent();
    qCDebug(COTAUTOMATE_LOG)<< "CActionAcquisitionCitNpoc 'qrunnable' ";
    QString sActionInfo;
    IVariableInput* measureCell = Q_NULLPTR;
    if(m_measureCell->getOrganType() == e_type_organ_input)
        measureCell = dynamic_cast<IVariableInput*>(m_measureCell);

    IVariableInput* measureAirflow = Q_NULLPTR;
    if(m_airflow->getOrganType() == e_type_organ_input)
        measureAirflow = dynamic_cast<IVariableInput*>(m_airflow);

    IVariable* varLogZeroMesure = CAutomate::getInstance()->getVariable(QStringLiteral("var_log_zero_mesure"));
    IVariable* varCo2ppmv = CAutomate::getInstance()->getVariable(QStringLiteral("var_co2ppmv"));
    IVariable* varDerivee = CAutomate::getInstance()->getVariable(QStringLiteral("var_derivee"));

    if(measureCell && measureAirflow){

        float mesure = 0;
        float x = 0;
        float co2ppmv=0;
        float co2g=0;
        float airflow = 0;
        float derivative =0;
        float derivativePrevious =0;
        float co2ppmvPrevious = 0;
        float co2ppmvPrevious2 = 0;

        float integral = 0;
        float integralPrevious = 0;


        //        const float zero = measureCell->readValue()->toFloat();
//        m_zero->setValue(zero);

        const float zero = m_zero->toFloat();
        const float coefCourbe = m_coefCourbe->toFloat();

        for(int i = 0; i < m_timeout->toInt() && !m_abort; ++i){

            mesure = measureCell->readValue()->toFloat();

            airflow = measureAirflow->readValue()->toFloat();

            if(mesure != 0){
                x = log10(zero/mesure);
                varLogZeroMesure->setValue(x);
                co2ppmv = m_coef1->toFloat() * pow(x, 5) *coefCourbe
                        + m_coef2->toFloat() * pow(x, 4) *coefCourbe
                        + m_coef3->toFloat() * pow(x,3) *coefCourbe
                        + m_coef4->toFloat() * pow(x,2) *coefCourbe
                        + m_coef5->toFloat() * x *coefCourbe
                        + m_Offset->toFloat();
                varCo2ppmv->setValue(co2ppmv);
                co2g += (co2ppmv * m_CstConversion->toFloat()) * ((airflow*0.001)/60000);
                //co2g += mesure;
                m_co2g->setValue(co2g);

                co2ppmv += 100; //ajoute un pied pour le calcul de l'intégral
                if(m_derivativeCalcul->toBool() && m_derivativeIntervalTx->toBool()){
                    if(co2ppmvPrevious2 > 0 && co2ppmvPrevious > 0 && co2ppmv > 0){
                        integral +=abs((2.0f/6.0f) * (co2ppmvPrevious2 + 4 * co2ppmvPrevious + co2ppmv));
                    }
                    if(( i % m_derivativeIntervalTx->toInt()) == 0 ){

                        if( integral > 0 && integralPrevious > 0){
                            derivativePrevious = derivative;
                            derivative = (integral - integralPrevious) / m_derivativeIntervalTx->toFloat();
                            varDerivee->setValue(derivative);
                        }
                        integralPrevious = integral;
                    }
                    co2ppmvPrevious2 = co2ppmvPrevious;
                    co2ppmvPrevious = co2ppmv;
                }
                sActionInfo =  tr("Measure ") + QString::number(i+1) + "/"  + QString::number(m_timeout->toInt()) + " "
                        + tr("Co2 g") + QString::number(co2g, 'f', 8)
                        + tr("Derivate ") + QString::number(derivative, 'f', 4);
                qCDebug(COTAUTOMATE_LOG)<< sActionInfo;
                updateActionInfos(sActionInfo, stepParent);

                if(derivative < m_derivativeThresold->toFloat() && derivative < derivativePrevious ) m_abort = true;

            }
            QThread::msleep(1000);
        }
        m_result->setValue( (co2g * 12000) / ( (m_vesselVolume->toFloat() / 1000) * 44) * m_coefCorrection->toFloat());
    }

    updateActionInfos(m_label + tr(" finit"), stepParent);
    emit signalActionFinished(this);
}

bool CActionAcquisitionCitNpoc::waitUntilFinished(){
    return m_waitUntilFinished;
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
    return map;
}
void CActionAcquisitionCitNpoc::setParameter(const QString& arg_key, IVariable* arg_parameter){
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

}
enumVariableType CActionAcquisitionCitNpoc::getWaitedType(const QString& arg_key){
    if(tr("Cellule")== arg_key) return e_type_float;
    else if(tr("Zero point")== arg_key) return e_type_float;
    else if(tr("Result")== arg_key) return e_type_float;
    else if(tr("Air flow")== arg_key)return e_type_float;
    else if(tr("Vessel volume")== arg_key)return e_type_float;
    else if(tr("Coefficient 1")== arg_key)return e_type_float;
    else if(tr("Coefficient 2")== arg_key)return e_type_float;
    else if(tr("Coefficient 3")== arg_key)return e_type_float;
    else if(tr("Coefficient 4")== arg_key)return e_type_float;
    else if(tr("Coefficient 5")== arg_key)return e_type_float;
    else if(tr("Co2 ppmv to Co2 g/m3")== arg_key)return e_type_float;
    else if(tr("Time acquisition")== arg_key)return e_type_int;

    else if(tr("Generate critical error")== arg_key)return e_type_bool;

    return e_type_unknow;
}
