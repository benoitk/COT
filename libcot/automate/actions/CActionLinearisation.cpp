#include "CActionLinearisation.h"

#include "CActionLinearisation.h"
#include "IVariable.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "IVariableInput.h"
#include "cotautomate_debug.h"
//#include "qmath.h"

#include "qthreadpool.h"


CActionLinearisation::CActionLinearisation(const QVariantMap &mapAction, QObject *parent)
    : IAction(mapAction, parent)
{
    CAutomate* automate = CAutomate::getInstance();

    m_coefCorrection = automate->getVariable(mapAction[QStringLiteral("coef_correction")].toString());
    m_coefCourbe = automate->getVariable(mapAction[QStringLiteral("coef_courbe")].toString());
    m_Offset = automate->getVariable(mapAction[QStringLiteral("offset")].toString());
    m_zero = automate->getVariable(mapAction[QStringLiteral("zero_point")].toString());

    m_waitUntilFinished = mapAction[QStringLiteral("wait_until_finished")].toBool();

     if(m_coefCourbe->toFloat() == 0) m_coefCourbe->setValue(1);

     QVariantMap variantMapDerivativeCalcul;
     variantMapDerivativeCalcul.insert(QStringLiteral("name"), QStringLiteral("derivative_calcul"));
     variantMapDerivativeCalcul.insert(tr("en_US"), tr("Generate critical error"));
     variantMapDerivativeCalcul.insert(QStringLiteral("type"), QStringLiteral("boolean"));
     variantMapDerivativeCalcul.insert(QStringLiteral("value"), mapAction[QStringLiteral("derivative_calcul")].toBool());
     m_derivativeCalcul = dynamic_cast<CVariableBool*>(CVariableFactory::build(variantMapDerivativeCalcul));

     //si autodelete à true, risque d'utilisation de l'objet alors qu'il est détruit à la fin du run.
     this->setAutoDelete(false);
}


QVariantMap CActionLinearisation::serialize(){
    QVariantMap mapSerialize = IAction::serialize();

    mapSerialize.insert(QStringLiteral("zero_point"), m_zero->getName());


    mapSerialize.insert(QStringLiteral("coef_1"), m_coef1->getName());
    mapSerialize.insert(QStringLiteral("coef_2"), m_coef2->getName());
    mapSerialize.insert(QStringLiteral("coef_3"), m_coef3->getName());
    mapSerialize.insert(QStringLiteral("coef_4"), m_coef4->getName());
    mapSerialize.insert(QStringLiteral("coef_5"), m_coef5->getName());
    mapSerialize.insert(QStringLiteral("coef_correction"), m_coefCorrection->getName());
    mapSerialize.insert(QStringLiteral("coef_courbe"), m_coefCourbe->getName());
    mapSerialize.insert(QStringLiteral("offset"), m_Offset->getName());


    mapSerialize.insert(QStringLiteral("derivative_calcul"), m_derivativeCalcul->toBool());


    mapSerialize.insert(QStringLiteral("type"), QStringLiteral("acquisition_cit_npoc"));
    return mapSerialize;
}

bool CActionLinearisation::runAction(ICycle* arg_stepParent){
    IAction::runAction(arg_stepParent);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = QThreadPool::globalInstance()->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CActionLinearisation::runAction";
        }
    }
    return true;
}



void CActionLinearisation::run(){
    ICycle* stepParent = getStepParent();
    qCDebug(COTAUTOMATE_LOG)<< "CActionLinearisation 'qrunnable' ";
    QString sActionInfo;

    IVariable* varLogZeroMesure = CAutomate::getInstance()->getVariable(QStringLiteral("var_log_zero_mesure"));
    IVariable* varCo2ppmv = CAutomate::getInstance()->getVariable(QStringLiteral("var_co2ppmv"));

    float mesure = 0;
    float x = 0;
    float co2ppmv=0;

    const float zero = m_zero->toFloat();
    const float coefCourbe = m_coefCourbe->toFloat();

    float zeroY = 0; //zero co2ppmv de chaque droite
    float maxY  = 0; //max co2ppmv de chaque droite





        //ou x : co2ppmv
        // f(x) = 1.726130e-20 . x⁵ - 5.614043e-16 . x⁴ + 6.778950e-12 . x³ - 3.980859e-8 . x² + 0.000156 . x + 0.005302

        x = log10(zero/mesure);
        varLogZeroMesure->setValue(x);
        co2ppmv = m_coef1->toFloat() * pow(x, 5) *coefCourbe
                + m_coef2->toFloat() * pow(x, 4) *coefCourbe
                + m_coef3->toFloat() * pow(x,3) *coefCourbe
                + m_coef4->toFloat() * pow(x,2) *coefCourbe
                + m_coef5->toFloat() * x *coefCourbe
                + m_Offset->toFloat();
        varCo2ppmv->setValue(co2ppmv);


        qCDebug(COTAUTOMATE_LOG)<< sActionInfo;
        updateActionInfos(sActionInfo, stepParent);

        zeroY = maxY;


        QThread::msleep(1000);


    updateActionInfos(m_label + tr(" finit"), stepParent);
    emit signalActionFinished(this);
}

bool CActionLinearisation::waitUntilFinished(){
    return m_waitUntilFinished;
}

QList<IVariable*> CActionLinearisation::getListParameters()const{
    QList<IVariable*> listParams;


    return listParams;
}
actionType CActionLinearisation::getType()const {
    return actionType::type_linearisation;
}

bool CActionLinearisation::variableUsed(IVariable *arg_var)const {

    return false;
}

QMap<QString, IVariable*> CActionLinearisation::getMapIVariableParameters(){
    QMap<QString, IVariable*>  map;


    map.insert(tr("Zero point"), m_zero);


    map.insert(tr("Coefficient 1"), m_coef1);
    map.insert(tr("Coefficient 2"), m_coef2);
    map.insert(tr("Coefficient 3"), m_coef3);
    map.insert(tr("Coefficient 4"), m_coef4);
    map.insert(tr("Coefficient 5"), m_coef5);



    return map;
}

QMap<QString, IVariable*> CActionLinearisation::getMapCstParameters(){
    QMap<QString, IVariable*>  map;
    return map;
}
void CActionLinearisation::setParameter(const QString& arg_key, IVariable* arg_parameter){
   if(tr("Zero point")== arg_key)m_zero= arg_parameter;

    else if(tr("Coefficient 1")== arg_key)m_coef1= arg_parameter;
    else if(tr("Coefficient 2")== arg_key)m_coef2= arg_parameter;
    else if(tr("Coefficient 3")== arg_key)m_coef3= arg_parameter;
    else if(tr("Coefficient 4")== arg_key)m_coef4= arg_parameter;
    else if(tr("Coefficient 5")== arg_key)m_coef5= arg_parameter;



}
enumVariableType CActionLinearisation::getWaitedType(const QString& arg_key){
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
